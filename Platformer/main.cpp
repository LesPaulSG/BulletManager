#include <fstream>

#include "IO_Thread.h"

int main(){
	BulletManager bulletManager;

	bulletManager.CreateWall(sf::Vector2f(0, 0), sf::Vector2f(0, HEIGHT), false);						//default border undestructable walls
	bulletManager.CreateWall(sf::Vector2f(WIDTH - 5, 0), sf::Vector2f(WIDTH - 5, HEIGHT), false);		//
	bulletManager.CreateWall(sf::Vector2f(0, 5), sf::Vector2f(WIDTH, 5), false);						//
	bulletManager.CreateWall(sf::Vector2f(0, HEIGHT), sf::Vector2f(WIDTH, HEIGHT), false);				//

	std::ifstream fin;
	fin.open("Walls.txt");
	int quantity;
	fin >> quantity;
	for (int i = 0; i < quantity; ++i) {
		int A, B, C, D;
		fin >> A >> B >> C >> D;
		bulletManager.CreateWall(sf::Vector2f(A, B), sf::Vector2f(C, D), true);
	}
	fin.close();

	std::chrono::duration<float> time;
	auto clock = std::chrono::high_resolution_clock::now();
	bool gameOver = false;

	std::thread IOThread(input, &bulletManager, &time, &gameOver);		//input output thread
	IOThread.detach();

	while (!gameOver){
		bulletManager.Update(time.count());

		time = std::chrono::high_resolution_clock::now() - clock;
		clock = std::chrono::high_resolution_clock::now();
	}

	return 0;
}