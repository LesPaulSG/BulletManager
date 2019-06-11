#include <iostream>
#include <SFML/Graphics.hpp>
#include "BulletManager.h"
#include "Bullet.h"
#include "Wall.h"
#include "Definitions.h"

using namespace sf;

const int height = VideoMode::getDesktopMode().height;
const int width = VideoMode::getDesktopMode().width;
RenderWindow window(VideoMode(width, height), "BulletManager", Style::Fullscreen);

int main()
{
	BulletManager bulletManager;
	Vector2i LmbStartPos, RmbStartPos;
	Vector2i LmbReleasedPos, RmbReleasedPos;

	Wall left(Vector2f(0, 0), Vector2f(0, height), false);
	Wall right(Vector2f(width - 5, 0), Vector2f(width - 5, height), false);
	Wall up(Vector2f(0, 5), Vector2f(width, 5), false);
	Wall down(Vector2f(0, height), Vector2f(width, height), false);
	Wall test(Vector2f(0, 0), Vector2f(width, height));

	bulletManager.AddWall(&left);
	bulletManager.AddWall(&right);
	bulletManager.AddWall(&up);
	bulletManager.AddWall(&down);
	bulletManager.AddWall(&test);

	window.setVerticalSyncEnabled(true);

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
					LmbStartPos = Mouse::getPosition();
				}
				else if (event.mouseButton.button == Mouse::Right) {
					RmbStartPos = Mouse::getPosition();
				}
			}
			else if (event.type == Event::MouseButtonReleased) {
				if (event.mouseButton.button == Mouse::Left) {
					LmbReleasedPos = Mouse::getPosition();
					Vector2f startPos(LmbStartPos);
					float x = LmbReleasedPos.x - LmbStartPos.x;
					float y = LmbReleasedPos.y - LmbStartPos.y;
					Vector2f direction(x, y);
					float distance = sqrt((x * x) + (y * y));
					bulletManager.Fire(startPos, direction, distance, 10);
				}
				else if (event.mouseButton.button == Mouse::Right) {
					RmbReleasedPos = Mouse::getPosition();
					bulletManager.AddWall(&Wall(Vector2f(RmbStartPos), Vector2f(RmbReleasedPos)));
				}
			}
		}

		bulletManager.Update(0.1 / CLOCKS_PER_SEC);

		window.clear();
		for (int i = 0; i < bulletManager.GetWallsQuntity(); i++) {
			if (bulletManager.GetWallsQuntity() > 0) {
				window.draw(bulletManager.GetWalls()->at(i).GetBody());
			}
		}
		for (int i = 0; i < bulletManager.GetBulletsQuntity(); i++) {
			if (bulletManager.GetBulletsQuntity() > 0) {
				window.draw(bulletManager.GetBullets()->at(i).GetBody());
			}
		}
		window.display();

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}
	}

	return 0;
}