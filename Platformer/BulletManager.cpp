#include "BulletManager.h"
#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>

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

void BulletManager::CreateWall(Vector2f start, Vector2f end) {
	if (this->walls_.size() < WALLS_MAX_CAPACITY) {
		this->walls_.push_back(Wall(start, end));
	}
}

void BulletManager::Update(float time) {
	/*std::thread update1(&BulletManager::UpdateThread, this, 0, std::min(BULLETS_MAX_CAPACITY/2, int(this->bullets_.size())), time);
	if (this->bullets_.size() >= BULLETS_MAX_CAPACITY / 2) {
		std::thread update2(&BulletManager::UpdateThread, this, BULLETS_MAX_CAPACITY/2, std::min(BULLETS_MAX_CAPACITY, int(this->bullets_.size())), time);
		update2.join();
	}
	update1.join();*/
	#pragma omp parallel for num_threads (6)
	for (std::vector<Bullet>::iterator iter = this->bullets_.begin(); iter != this->bullets_.end(); ++iter) {
		iter->Update(time, &this->walls_);
		if (!iter->GetAlive()) {
			this->bullets_.erase(iter);
			break;
		}
		//std::this_thread::sleep_for(std::chrono::microseconds(30000));
		//std::cout << std::this_thread::get_id() << std::endl;
	}
}

/*void BulletManager::UpdateThread(int from, int to, float time) {
	for (std::vector<Bullet>::iterator iter = this->bullets_.begin() + from; iter != this->bullets_.begin() + to; ++iter) {
		iter->Update(time, &this->walls_);
		if (!iter->GetAlive()) {
			this->bullets_.erase(iter);
			break;
		}
	}
}*/

void BulletManager::Fire(Vector2f pos, Vector2f dir, float speed, float lifeTime) {
	if (this->bullets_.size() < BULLETS_MAX_CAPACITY) {
		this->bullets_.push_back(Bullet(pos, dir, std::min(speed, 80.f), lifeTime));
	}
}

BulletManager::~BulletManager() {
	this->bullets_.~vector();
	this->walls_.~vector();
}