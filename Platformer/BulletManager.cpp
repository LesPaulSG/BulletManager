#include "BulletManager.h"
#include <iostream>
#include <cmath>

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

void BulletManager::AddWall(Wall* wall) {
	if (this->walls_.size() < WALLS_MAX_CAPACITY) {
		this->walls_.push_back(*wall);
	}
}

void BulletManager::CreateWall(Vector2f start, Vector2f end, bool destructable) {
	if (this->walls_.size() < WALLS_MAX_CAPACITY) {
		if (LenghtOfLine(start, end) > 10) {	//check lengtn of wall for visible value
			this->walls_.push_back(Wall(start, end, destructable));
		}
	}
}

void BulletManager::Update(float time) {
	for (std::vector<Bullet>::iterator iter = this->bullets_.begin(); iter != this->bullets_.end(); ++iter) {
		iter->Update(time, &this->walls_);
		if (!iter->GetAlive()) {
			this->bullets_.erase(iter);
			break;
		}
	}
}

void BulletManager::Fire(Vector2f pos, Vector2f dir, float speed, float lifeTime) {
	if (this->bullets_.size() < BULLETS_MAX_CAPACITY) {
		this->bullets_.push_back(Bullet(pos, dir, std::min(speed, 80.f), lifeTime));
	}
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