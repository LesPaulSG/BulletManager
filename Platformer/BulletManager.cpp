#include "BulletManager.h"
#include <iostream>
#include <cmath>

BulletManager::BulletManager() {

}

std::vector<Bullet>* BulletManager::GetBullets() {
	return &this->bullets_;
}

std::vector<Wall>* BulletManager::GetWalls() {
	return &this->walls_;
}

void BulletManager::AddBullet(Bullet * bullet) {
	this->bullets_.push_back(*bullet);
}

void BulletManager::RemoveBullet(std::vector<Bullet>::iterator iter) {
	this->bullets_.erase(iter);
}

int BulletManager::GetBulletsQuntity() {
	return this->bullets_.size();
}

void BulletManager::AddWall(Wall * wall) {
	this->walls_.push_back(*wall);
}

void BulletManager::RemoveWall(std::vector<Wall>::iterator iter) {
	this->walls_.erase(iter);
}

int BulletManager::GetWallsQuntity() {
	return this->walls_.size();
}

void BulletManager::Update(float time) {
	std::vector<Bullet>::iterator iter = this->bullets_.begin();
	for (iter; iter != this->bullets_.end(); ++iter) {
		//std::cout << this->bullets_.capacity() << "\t" << &iter << "\t" << &this->bullets_.end() << std::endl;
		iter->Update(time, &this->walls_);
		if (!iter->GetAlive()) {
			//std::cout << iter->GetAlive() << std::endl;
			this->bullets_.erase(iter);
			break;
		}
	}
}

void BulletManager::Fire(Vector2f pos, Vector2f dir, float speed, float lifeTime) {
	Bullet b(pos, dir, speed, lifeTime);
	this->bullets_.push_back(b);
}

BulletManager::~BulletManager() {

}