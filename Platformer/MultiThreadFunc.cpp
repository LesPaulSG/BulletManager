#include <SFML/Graphics.hpp>
#include "MultiThreadDef.h"
#include <iostream>

void DrawFrame(RenderWindow* window, BulletManager* bM) {
	//window->clear();
	for (std::vector<Wall>::iterator iter = bM->GetWalls()->begin(); iter != bM->GetWalls()->end(); ++iter) {
		//window->draw(iter->GetBody());
	}
	for (std::vector<Bullet>::iterator iter = bM->GetBullets()->begin(); iter != bM->GetBullets()->end(); ++iter) {
		//window->draw(iter->GetBody());
	}
	//window->display();
	std::cout << "thread" << std::endl;
}