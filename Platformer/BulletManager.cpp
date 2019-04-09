#include "BulletManager.h"
#include <iostream>

///////////// BulletManager /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BulletManager::BulletManager(){
	
}

std::vector<Bullet>* BulletManager::GetBullets() {
	return &this->bullets_;
}

std::vector<Wall>* BulletManager::GetWalls() {
	return &this->walls_;
}

void BulletManager::AddBullet(Bullet* bullet) {
	this->bullets_.push_back(*bullet);
}

void BulletManager::RemoveBullet(std::vector<Bullet>::iterator iter) {
	this->bullets_.erase(iter);
}

int BulletManager::GetBulletsQuntity() {
	return this->bullets_.size();
}

void BulletManager::AddWall(Wall* wall) {
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
		}
	}
}

void BulletManager::Fire(Vector2f pos, Vector2f dir, float speed, float lifeTime) {
	Bullet b(pos, dir, speed, lifeTime);
	this->bullets_.push_back(b);
}

BulletManager::~BulletManager() {

}

///////////// Bullet ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Bullet::Bullet(Vector2f pos, Vector2f dir, float speed, float lifeTime) : pos_(pos), dir_(dir), speed_(speed), lifeTime_(lifeTime), time_(0), alive_(true) {
	//this->pos_ = pos;
	//this->dir_ = dir;
	//this->speed_ = speed;
	//this->lifeTime_ = lifeTime;
	this->body_.setPosition(pos);
	this->body_.setOrigin(Vector2f(this->body_.getOrigin().x+5.0,this->body_.getOrigin().y+5.0));
	this->body_.setRadius(10.0);
	this->body_.setFillColor(Color::Red);
}

void Bullet::Update(float time, std::vector<Wall>* walls) {
	this->pos_ += this->dir_*this->speed_*time;
	this->body_.setPosition(this->pos_);
	for (int i = 0; i < walls->size(); i++) {
		Vector2f wallPos = walls->at(i).GetBody().getPosition();
		Vector2f wallsSize = walls->at(i).GetBody().getSize();
	}
	this->speed_ -= time;
	this->time_ += time;
	//std::cout << time << "\t" << time_ << "\t" << lifeTime_ << "\t &boolean" << this->alive_ << std::endl;
	if (time_ >= lifeTime_) {
		this->alive_ = false;
	}
}

CircleShape Bullet::GetBody() {
	return this->body_;
}

float Bullet::GetRadius() {
	return this->body_.getRadius();
}

float Bullet::GetSpeed() {
	return this->speed_;
}

float Bullet::GetTime() {
	return this->time_;
}

float Bullet::GetLifeTime() {
	return this->lifeTime_;
}

Vector2f Bullet::GetPos() {
	return this->pos_;
}

Vector2f Bullet::GetGetDir() {
	return this->dir_;
}

bool Bullet::GetAlive() {
	return this->alive_;
}


Bullet::~Bullet() {
	this->body_.~CircleShape();
	std::cout << "destructor" << std::endl;
}

///////////// Wall //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Wall::Wall() : destructable_(true) {
	//this->destructable_ = true;
	this->body_.setSize(Vector2f(0,0));
	this->body_.setRotation(0);
	this->body_.setFillColor(Color::White);
}

Wall::Wall(Vector2f pos, Vector2f size, float angle) {
	this->body_.setPosition(pos);
	this->body_.setSize(size);
	this->body_.setRotation(angle);
	this->body_.setFillColor(Color::Yellow);
}

Wall::Wall(Vector2f pos, Vector2f size, float angle, bool destructable) : destructable_(destructable) {
	//this->destructable_ = destructable;
	this->body_.setPosition(pos);
	this->body_.setSize(size);
	this->body_.setRotation(angle);
	if (destructable) {
		this->body_.setFillColor(Color::Yellow);
	} else {
		this->body_.setFillColor(Color::Green);
	}
}

RectangleShape Wall::GetBody() {
	return this->body_;
}

Wall::~Wall() {

}