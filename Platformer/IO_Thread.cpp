#include "IO_Thread.h"
#include <iostream>
#include <mutex>
#include <SFML\Audio.hpp>

std::mutex mtxIO;

Vector2i LmbStartPos, RmbStartPos;			//mouse positions for firing
Vector2i LmbReleasedPos, RmbReleasedPos;	//and creating walls

void input(BulletManager* bm, std::chrono::duration<float>* t, bool* gameOver) {
	Font font;									//text obj for UI
	font.loadFromFile("OpenSans-Bold.ttf");		//
	Text ui("",font,16);						//
	ui.setPosition(5, 5);						//
	ui.setFillColor(Color::Red);				//

	SoundBuffer sb, rb;
	sb.loadFromFile("shot.wav");
	rb.loadFromFile("ric.wav");
	Sound shot, ric;
	shot.setBuffer(sb);
	ric.setBuffer(rb);

	RenderWindow window(VideoMode(WIDTH, HEIGHT), "BulletManager", Style::Fullscreen);
	window.setVerticalSyncEnabled(true);

	std::chrono::duration<float> time;
	auto start = std::chrono::high_resolution_clock::now();
	auto end = start;

	while (true) {
		start = std::chrono::high_resolution_clock::now();

		if (Keyboard::isKeyPressed(Keyboard::P)) {
			bm->WallTrancform();
		}

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			else if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Left) {
					LmbStartPos = Mouse::getPosition();					//save coordinates of LMB pressed
				}
				else if (event.mouseButton.button == Mouse::Right) {
					RmbStartPos = Mouse::getPosition();					//save coordinates of RMB pressed
				}
			}
			else if (event.type == Event::MouseButtonReleased) {
				if (event.mouseButton.button == Mouse::Left) {
					LmbReleasedPos = Mouse::getPosition();
					float x = LmbReleasedPos.x - LmbStartPos.x;
					float y = LmbReleasedPos.y - LmbStartPos.y;
					Vector2f direction(x, y);
					float speed = (sqrt((x * x) + (y * y)))/100;
					bm->Fire(Vector2f(LmbStartPos), direction, speed, 30, ric);//firing when LMB released
					shot.play();
				}
				else if (event.mouseButton.button == Mouse::Right) {
					RmbReleasedPos = Mouse::getPosition();
					bm->CreateWall(Vector2f(RmbStartPos), Vector2f(RmbReleasedPos), true);//build a wall when RMB released
				}
			}
		}

		window.clear();

		bm->SetProcessed(false);

		for (std::vector<Wall>::iterator iter = bm->GetWalls()->begin(); iter != bm->GetWalls()->end(); ++iter) {
			window.draw(iter->GetBody());
		}
		for (std::vector<Bullet>::iterator iter = bm->GetBullets()->begin(); iter != bm->GetBullets()->end(); ++iter) {
			window.draw(iter->GetBody());
		}

		ui.setString("bullest:  " + std::to_string(bm->GetBullets()->size())	//bullets quantity
					+ "\nwalls:     " + std::to_string(bm->GetWalls()->size())	//walls quantity
					+ "\nfps:         " + std::to_string(1 / time.count())		//GUI FPS
					+ "\npFps:       " + std::to_string(1 / t->count()));		//physics FPS

		bm->SetProcessed(true);
		bm->GetCv()->notify_one();

		window.draw(ui);
		window.display();

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			*gameOver = true;
		}

		end = std::chrono::high_resolution_clock::now();
		time = end - start;
	}
}
