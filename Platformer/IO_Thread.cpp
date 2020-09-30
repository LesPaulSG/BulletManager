#include "IO_Thread.h"
#include <iostream>
#include <mutex>

#include "Player.h"

std::mutex mtxIO;

Vector2i LmbStartPos, RmbStartPos;			//mouse positions for firing
Vector2i LmbReleasedPos, RmbReleasedPos;	//and creating walls
Vector2i lookAt(0,0);

void input(BulletManager* bm, std::chrono::duration<float>* t, bool* gameOver) {
	Font font;									//text obj for UI
	font.loadFromFile("OpenSans-Bold.ttf");		//
	Text ui("",font,16);						//
	ui.setPosition(5, 5);						//
	ui.setFillColor(Color::Red);				//

	RenderWindow window(VideoMode(WIDTH, HEIGHT), "BulletManager", Style::Fullscreen);
	window.setVerticalSyncEnabled(true);

	std::chrono::duration<float> time;
	auto start = std::chrono::high_resolution_clock::now();
	auto end = start;

	std::cout << "test" << std::endl;
	Player player(Vector2f(960, 540), 0);

	while (true) {
		start = std::chrono::high_resolution_clock::now();

		if (lookAt != Mouse::getPosition()) {
			lookAt = Mouse::getPosition();
			player.Rotate(Vector2f(lookAt));
		}

		if (Keyboard::isKeyPressed(Keyboard::P)) {
			bm->WallTrancform();
		}

		if (Keyboard::isKeyPressed(Keyboard::W)) {
			player.Move(FWD, time.count(), bm->GetWalls());
		} else if (Keyboard::isKeyPressed(Keyboard::S)) {
			player.Move(BWD, time.count(), bm->GetWalls());
		} else if (Keyboard::isKeyPressed(Keyboard::D)) {
			player.Move(RGH, time.count(), bm->GetWalls());
		} else if (Keyboard::isKeyPressed(Keyboard::A)) {
			player.Move(LFT, time.count(), bm->GetWalls());
		} else {
			//player.SetRotation(AngleOfIntersec(Line(Vector2f(0, 0), Vector2f(0, 1)), Line(player.GetPosition(), Vector2f(Mouse::getPosition()))));
		}

		Event event;
		while (window.pollEvent(event)) {
			//player.SetRotation(AngleOfIntersec(Line(Vector2f(0, 0), Vector2f(0, 1)), Line(player.GetPosition(), Vector2f(Mouse::getPosition()))));
			if (event.type == Event::Closed) {
				window.close();
			} else if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Left) {
					LmbStartPos = Mouse::getPosition();					//save coordinates of LMB pressed
				} else if (event.mouseButton.button == Mouse::Right) {
					RmbStartPos = Mouse::getPosition();					//save coordinates of RMB pressed		
					//player.Rotate(Vector2f(RmbStartPos));
				}
			} else if (event.type == Event::MouseButtonReleased) {
				if (event.mouseButton.button == Mouse::Left) {
					LmbReleasedPos = Mouse::getPosition();
					float x = LmbReleasedPos.x - player.GetPosition().x;
					float y = LmbReleasedPos.y - player.GetPosition().y;
					Vector2f direction(x, y);
					float speed = 10;
					bm->Fire(player.GetPosition(), direction, speed, 30);//firing when LMB released
				} else if (event.mouseButton.button == Mouse::Right) {
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

		window.draw(player.GetBody());
		window.draw(player.GetFwdVecBody());
		window.draw(player.GetRghVecBody());

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
