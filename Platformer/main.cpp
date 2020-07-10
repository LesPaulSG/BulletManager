#include <iostream>
#include <fstream>
#include <thread>
#include <SFML/Graphics.hpp>
#include "BulletManager.h"
#include "IO_Thread.h"

using namespace sf;

int main(){
	BulletManager bulletManager;

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
		bulletManager.CreateWall(Vector2f(A, B), Vector2f(C, D), false);
	}
	fin.close();

	std::chrono::duration<float> time;
	auto start = std::chrono::high_resolution_clock::now();
	auto end = start;
	bool gameOver = false;

	std::thread IOThread(input, &bulletManager, & time, & gameOver);		//input output thread
	IOThread.detach();

	while (!gameOver){
		start = std::chrono::high_resolution_clock::now();

		bulletManager.Update(time.count());

		end = std::chrono::high_resolution_clock::now();
		time = end - start;
	}

	return 0;
}