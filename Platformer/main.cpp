#include <fstream>

#include "IO_Thread.h"

int main(){
	BulletManager bulletManager;

	bulletManager.CreateWall(sf::Vector2f(0, 0), sf::Vector2f(0, HEIGHT), false);						//default border undestructable walls
	bulletManager.CreateWall(sf::Vector2f(WIDTH - 5, 0), sf::Vector2f(WIDTH - 5, HEIGHT), false);		//
	bulletManager.CreateWall(sf::Vector2f(0, 5), sf::Vector2f(WIDTH, 5), false);						//
	bulletManager.CreateWall(sf::Vector2f(0, HEIGHT), sf::Vector2f(WIDTH, HEIGHT), false);				//

	for (int i = 0; i <= 50; ++i) {
		bulletManager.Fire(sf::Vector2f(10+i + i, 10 + i + i), sf::Vector2f(110 + i + i, 110 + i + i), 10, 10);
	}

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
	
	std::chrono::duration<float> time{ 0 };
	auto clock = std::chrono::high_resolution_clock::now();
	bool gameOver = false;

	//VisualThread vt(&bulletManager, &time, &gameOver);

	std::thread IOThread(input, std::ref(bulletManager), std::ref(time), std::ref(gameOver));		//input output thread
	//std::thread IOThread(&VisualThread::Update, &vt);
	IOThread.detach();

	std::this_thread::sleep_for(std::chrono::nanoseconds(3000000000));

	while (!gameOver){
		//bulletManager.Fire(sf::Vector2f(10, 10), sf::Vector2f(110, 110), 10, 10);
		bulletManager.Update(time.count());

		time  = std::chrono::high_resolution_clock::now() - clock;
		clock = std::chrono::high_resolution_clock::now();
	}

	return 0;
}