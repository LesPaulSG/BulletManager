#include <iostream>
#include <SFML/Graphics.hpp>
#include "BulletManager.h"

using namespace sf;

int main()
{
	BulletManager bulletManager;
	Vector2i bulletStartPos;
	Vector2i mouseReleasedPos;

	int height = VideoMode::getDesktopMode().height;
	int width = VideoMode::getDesktopMode().width;

	Wall left(Vector2f(0,0), Vector2f(10,height), 0, false);
	Wall right(Vector2f(width-10,0), Vector2f(10, height), 0, false);
	Wall up(Vector2f(0,10), Vector2f(10,width), 270, false);
	Wall down(Vector2f(10,height), Vector2f(10, width), 270, false);
	
	bulletManager.AddWall(&left);
	bulletManager.AddWall(&right);
	bulletManager.AddWall(&up);
	bulletManager.AddWall(&down);

	RenderWindow window(VideoMode(width,height), "Platformer", Style::Fullscreen);
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
					bulletStartPos = Mouse::getPosition();
				}
			}
			else if (event.type == Event::MouseButtonReleased) {
				if (event.mouseButton.button == Mouse::Left) {
					mouseReleasedPos = Mouse::getPosition();
					Vector2f startPos(bulletStartPos.x, bulletStartPos.y);
					float x = mouseReleasedPos.x - bulletStartPos.x;
					float y = mouseReleasedPos.y - bulletStartPos.y;
					Vector2f direction(x, y);
					float distance = sqrt((x*x) + (y*y));
					bulletManager.Fire(startPos, direction, distance * 100, 10);
				}
			}
		}

		bulletManager.Update(1.0/CLOCKS_PER_SEC);

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