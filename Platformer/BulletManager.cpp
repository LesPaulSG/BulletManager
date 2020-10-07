#include "BulletManager.h"

#include <iostream>
#include <cmath>
#include <mutex>

std::mutex mtx;

BulletManager::BulletManager() {
	bullets.reserve(BULLETS_MAX_CAPACITY);
	walls.reserve(WALLS_MAX_CAPACITY);
}

std::vector<Bullet>* BulletManager::GetBullets() {
	return &bullets;
}

std::vector<Wall>* BulletManager::GetWalls() {
	return &walls;
}

bool BulletManager::GetProcessed() {
	return processed;
}

bool BulletManager::GetUpdated() {
	return updated;
}

std::condition_variable* BulletManager::GetCv() {
	return &cv;
}

void BulletManager::AddWall(Wall* wall) {
	processed = false;

	std::unique_lock<std::mutex> lock(mtx);
	cv.wait(lock, [this] {return updated; });

	if (walls.size() < WALLS_MAX_CAPACITY) {
		walls.push_back(*wall);
	}

	processed = true;
	cv.notify_one();
}

void BulletManager::CreateWall(sf::Vector2f start, sf::Vector2f end, bool destructable) {
	if (LenghtOfLine(start, end) > 10) {	//check lengtn of wall for visible value
		AddWall(&Wall(start, end, destructable));
	}
}

void BulletManager::Update(float time) {
	std::unique_lock<std::mutex> lock(mtx);
	cv.wait(lock, [this]{return processed; });

	updated = false;

	for (auto iter = bullets.begin(); iter != bullets.end(); ++iter) {
		iter->Update(time, &walls);
		if (!iter->GetAlive()) {
			bullets.erase(iter);
			break;
		}
	}

	updated = true;
	cv.notify_one();
}

void BulletManager::Fire(sf::Vector2f pos, sf::Vector2f dir, float speed, float lifeTime) {
	processed = false;

	std::unique_lock<std::mutex> lock(mtx);
	cv.wait(lock, [this] {return updated; });

	if (bullets.size() < BULLETS_MAX_CAPACITY) {
		bullets.push_back(Bullet(pos, dir, std::min(speed, 30.f), lifeTime));
	}

	processed = true;
	cv.notify_one();
}

void BulletManager::SetProcessed(bool nP) {
	processed = nP;
}

void BulletManager::WallTrancform() {
	for (auto iter = walls.begin(); iter != walls.end(); ++iter) {
		iter->Transform();
	}
}

BulletManager::~BulletManager() {}