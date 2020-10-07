#include <iostream>
#include <fstream>
#include <thread>
#include <SFML/Graphics.hpp>

#include "BulletManager.h"
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
		bulletManager.CreateWall(sf::Vector2f(A, B), sf::Vector2f(C, D), false);
	}
	fin.close();

	std::chrono::duration<float> time;
	auto start = std::chrono::high_resolution_clock::now();
	auto end = start;
	bool gameOver = false;

	std::thread IOThread(input, &bulletManager, &time, &gameOver);		//input output thread
	IOThread.detach();

	while (!gameOver){
		start = std::chrono::high_resolution_clock::now();

		bulletManager.Update(time.count());

		end = std::chrono::high_resolution_clock::now();
		time = end - start;
	}

	return 0;
}