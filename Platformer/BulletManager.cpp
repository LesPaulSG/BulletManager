#include "BulletManager.h"
#include <iostream>
#include <cmath>

#include <ctime>
#include <mutex>

std::mutex mtx;

BulletManager::BulletManager() {
	this->bullets_.reserve(BULLETS_MAX_CAPACITY);
	this->walls_.reserve(WALLS_MAX_CAPACITY);
}

std::vector<Bullet>* BulletManager::GetBullets() {
	return &this->bullets_;
}

std::vector<Wall>* BulletManager::GetWalls() {
	return &this->walls_;
}

bool BulletManager::GetProcessed() {
	return this->processed;
}

bool BulletManager::GetUpdated() {
	return this->updated;
}

void BulletManager::AddWall(Wall* wall) {
	this->processed = false;

	std::unique_lock<std::mutex> lock(mtx);
	cv.wait(lock, [this] {return updated; });

	if (this->walls_.size() < WALLS_MAX_CAPACITY) {
		this->walls_.push_back(*wall);
	}

	this->processed = true;
	this->cv.notify_one();
}

void BulletManager::CreateWall(Vector2f start, Vector2f end, bool destructable) {
	this->processed = false;

	std::unique_lock<std::mutex> lock(mtx);
	cv.wait(lock, [this] {return updated; });

	if (this->walls_.size() < WALLS_MAX_CAPACITY) {
		if (LenghtOfLine(start, end) > 10) {	//check lengtn of wall for visible value
			this->walls_.push_back(Wall(start, end, destructable));
		}
	}

	this->processed = true;
	this->cv.notify_one();
}

void BulletManager::Update(float time) {
	std::unique_lock<std::mutex> lock(mtx);
	cv.wait(lock, [this]{return GetProcessed();});

	this->updated = false;

	for (std::vector<Bullet>::iterator iter = this->bullets_.begin(); iter != this->bullets_.end(); ++iter) {
		iter->Update(time, &this->walls_);
		if (!iter->GetAlive()) {
			this->bullets_.erase(iter);
			break;
		}
	}

	this->updated = true;
	cv.notify_one();
}

void BulletManager::Fire(Vector2f pos, Vector2f dir, float speed, float lifeTime) {
	this->processed = false;

	std::unique_lock<std::mutex> lock(mtx);
	cv.wait(lock, [this] {return updated; });

	if (this->bullets_.size() < BULLETS_MAX_CAPACITY) {
		this->bullets_.push_back(Bullet(pos, dir, std::min(speed, 30.f), lifeTime));
	}

	this->processed = true;
	this->cv.notify_one();
}

void BulletManager::WallTrancform() {
	for (std::vector<Wall>::iterator iter = this->walls_.begin(); iter != this->walls_.end(); ++iter) {
		iter->Transform();
	}
}

BulletManager::~BulletManager() {
	this->bullets_.~vector();
	this->walls_.~vector();
}