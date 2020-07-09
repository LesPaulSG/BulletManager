#pragma once
#include <vector>
#include "Bullet.h"
#include "Wall.h"
#include "Definitions.h"
#include <condition_variable>

class BulletManager {
private:
	std::vector<Bullet> bullets_;
	std::vector<Wall> walls_;

public:
	std::vector<Bullet>* GetBullets();
	std::vector<Wall>* GetWalls();
	bool GetProcessed();
	bool GetUpdated();

	void AddWall(Wall*);
	void CreateWall(Vector2f, Vector2f, bool);
	void Update(float);
	void Fire(Vector2f, Vector2f, float, float);
	void WallTrancform();

	std::condition_variable cv;
	bool processed = true;
	bool updated = true;

	BulletManager();
	~BulletManager();
};
