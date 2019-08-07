#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <SFML/Graphics.hpp>
#include "BulletManager.h"

using namespace sf;

const int HEIGHT = VideoMode::getDesktopMode().height;
const int WIDTH = VideoMode::getDesktopMode().width;

int main()
{
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "BulletManager", Style::Fullscreen);
	window.setVerticalSyncEnabled(true);

	BulletManager bulletManager;
	Vector2i LmbStartPos, RmbStartPos;			//mouse positions for firing
	Vector2i LmbReleasedPos, RmbReleasedPos;	//and creating walls

	Wall left(Vector2f(0, 0), Vector2f(0, HEIGHT), false);						//default border undestructable walls
	Wall right(Vector2f(WIDTH - 5, 0), Vector2f(WIDTH - 5, HEIGHT), false);		//
	Wall up(Vector2f(0, 5), Vector2f(WIDTH, 5), false);							//
	Wall down(Vector2f(0, HEIGHT), Vector2f(WIDTH, HEIGHT), false);				//

	bulletManager.AddWall(&left);
	bulletManager.AddWall(&right);
	bulletManager.AddWall(&up);
	bulletManager.AddWall(&down);

	std::ifstream fin;
	fin.open("Walls.txt");
	int quantity;
	fin >> quantity;
	for (int i = 0; i < quantity; ++i) {
		int A, B, C, D;
		fin >> A >> B >> C >> D;
		bulletManager.AddWall(&Wall(Vector2f(A, B), Vector2f(C, D)));
	}
	fin.close();

	std::thread bMThread;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
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
					float speed = sqrt((x * x) + (y * y));
					bMThread = std::thread(&BulletManager::Fire, &bulletManager, Vector2f(LmbStartPos), direction, speed, 1);	//firing when LMB released
					bMThread.detach();
				}
				else if (event.mouseButton.button == Mouse::Right) {
					RmbReleasedPos = Mouse::getPosition();
					bMThread = std::thread(&BulletManager::CreateWall, &bulletManager, Vector2f(RmbStartPos), Vector2f(RmbReleasedPos));	//build a wall when RMB released
					bMThread.detach();
				}
			}
		}

		bulletManager.Update(1.0 / CLOCKS_PER_SEC);

		window.clear();
		for (std::vector<Wall>::iterator iter = bulletManager.GetWalls()->begin(); iter != bulletManager.GetWalls()->end(); ++iter) {
			window.draw(iter->GetBody());
		}
		for (std::vector<Bullet>::iterator iter = bulletManager.GetBullets()->begin(); iter != bulletManager.GetBullets()->end(); ++iter) {
			window.draw(iter->GetBody());
		}
		window.display();

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}
	}

	return 0;
}