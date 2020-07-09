#include "IO_Thread.h"
#include <iostream>

#include <ctime>
#include <mutex>

std::mutex mtxIO;

const int HEIGHT = VideoMode::getDesktopMode().height;
const int WIDTH = VideoMode::getDesktopMode().width;

Vector2i LmbStartPos, RmbStartPos;			//mouse positions for firing
Vector2i LmbReleasedPos, RmbReleasedPos;	//and creating walls

void input(BulletManager* bm, std::chrono::duration<float>* t, bool* gameOver) {
	Text bullets, walls, fps, pFps;
	Font font;
	font.loadFromFile("OpenSans-Bold.ttf");
	bullets.setPosition(5, 5);
	bullets.setFont(font);
	bullets.setFillColor(Color::Red);
	bullets.setCharacterSize(16);
	walls.setPosition(5, 20);
	walls.setFont(font);
	walls.setFillColor(Color::Red);
	walls.setCharacterSize(16);
	fps.setPosition(5, 35);
	fps.setFont(font);
	fps.setFillColor(Color::Red);
	fps.setCharacterSize(16);
	pFps.setPosition(5, 50);
	pFps.setFont(font);
	pFps.setFillColor(Color::Red);
	pFps.setCharacterSize(16);

	RenderWindow window(VideoMode(WIDTH, HEIGHT), "BulletManager", Style::Fullscreen);
	window.setVerticalSyncEnabled(true);

	while (true) {
		std::chrono::duration<float> time;
		auto t_start = std::chrono::high_resolution_clock::now();

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
					//bMThread = std::thread(&BulletManager::Fire, &bulletManager, Vector2f(LmbStartPos), direction, speed, 1);	//firing when LMB released
					bm->Fire(Vector2f(LmbStartPos), direction, speed, 30);
					//bMThread.detach();
				}
				else if (event.mouseButton.button == Mouse::Right) {
					RmbReleasedPos = Mouse::getPosition();
					//bMThread = std::thread(&BulletManager::CreateWall, &bulletManager, Vector2f(RmbStartPos), Vector2f(RmbReleasedPos), true);	//build a wall when RMB released
					bm->CreateWall(Vector2f(RmbStartPos), Vector2f(RmbReleasedPos), false);
					//bMThread.detach();
				}
			}
		}

		window.clear();

		std::unique_lock<std::mutex> lock(mtxIO);
		bm->cv.wait(lock, [bm] {return bm->GetUpdated(); });
		bm->processed = false;

		for (std::vector<Wall>::iterator iter = bm->GetWalls()->begin(); iter != bm->GetWalls()->end(); ++iter) {
			window.draw(iter->GetBody());
		}
		for (std::vector<Bullet>::iterator iter = bm->GetBullets()->begin(); iter != bm->GetBullets()->end(); ++iter) {
			window.draw(iter->GetBody());
		}

		bullets.setString("bullest:  " + std::to_string(bm->GetBullets()->size()));
		walls.setString("walls:     " + std::to_string(bm->GetWalls()->size()));

		bm->processed = true;
		bm->cv.notify_one();

		fps.setString("fps:         " + std::to_string(1 / time.count()));
		pFps.setString("pFps:       " + std::to_string(1 / t->count()));

		window.draw(bullets);
		window.draw(walls);
		window.draw(fps);
		window.draw(pFps);
		window.display();

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
			*gameOver = true;
		}

		auto t_end = std::chrono::high_resolution_clock::now();
		time = t_end - t_start;
	}
}
