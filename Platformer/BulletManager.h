#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Bullet.h"
#include "Wall.h"
#include "Definitions.h"

const int BULLETS_MAX_CAPACITY = 10;
const int WALLS_MAX_CAPACITY = 50;

class BulletManager {
private:
	std::vector<Bullet> bullets_;
	std::vector<Wall> walls_;
public:
	std::vector<Bullet>* GetBullets();
	std::vector<Wall>* GetWalls();

	void AddWall(Wall*);
	void Update(float);
	void Fire(Vector2f, Vector2f, float, float);

	BulletManager();
	~BulletManager();
};
