#pragma once
#include <vector>
#include <condition_variable>

#include "Bullet.h"
#include "Player.h"

class BulletManager {
private:
	std::vector<Bullet> bullets;
	std::vector<Wall> walls;
	std::condition_variable cv;
	bool processed = true;
	bool updated = true;
	Player player;

public:
	BulletManager();
	~BulletManager() = default;

	std::vector<Bullet>* GetBullets();
	std::vector<Wall>* GetWalls();
	bool GetProcessed();
	bool GetUpdated();
	std::condition_variable* GetCv();
	Player* GetPlayer();

	void AddWall(Wall* wall);
	void CreateWall(sf::Vector2f start, sf::Vector2f end, bool destructable);
	void Update(float time);
	void Fire(sf::Vector2f pos, sf::Vector2f dir, float speed, float lifeTime);
	void WallTrancform();
	void SetProcessed(bool nP);
};
