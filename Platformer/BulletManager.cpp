#include "BulletManager.h"
#include <iostream>
#include <cmath>

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

///////////// Bullet ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Bullet::Bullet(Vector2f pos, Vector2f dir, float speed, float lifeTime) : pos_(pos), dir_(dir), speed_(speed), lifeTime_(lifeTime), time_(0), alive_(true) {
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
	this->body_.setSize(Vector2f(0,0));
	this->body_.setRotation(0);
	this->body_.setFillColor(Color::White);
}

Wall::Wall(Vector2f A, Vector2f B) : pointA_(A), pointB_(B), destructable_(true) {
	float lenght = sqrt(pow((B.x - A.x), 2) + pow((B.y - A.y), 2));
	CalculateVector();
	CalculateRotation();
	this->body_.setPosition(A);
	this->body_.setSize(Vector2f(5, lenght));
	this->body_.setFillColor(Color::Yellow);
}

Wall::Wall(Vector2f A, Vector2f B, bool destructable) : pointA_(A), pointB_(B), destructable_(destructable) {
	float lenght = sqrt(pow((B.x - A.x), 2) + pow((B.y - A.y), 2));
	CalculateVector();
	CalculateRotation();
	this->body_.setPosition(A);
	this->body_.setSize(Vector2f(5, lenght));
	if (destructable) {
		this->body_.setFillColor(Color::Yellow);
	} else {
		this->body_.setFillColor(Color::Green);
	}
}

void Wall::CalculateVector() {
	this->vector_.x = this->pointB_.x - this->pointA_.x;
	this->vector_.y = this->pointB_.y - this->pointA_.y;
}

void Wall::CalculateRotation() {
	double angle = acos(this->vector_.y / (sqrt(this->vector_.x * this->vector_.x + this->vector_.y * this->vector_.y)));
	angle *= -(180 / 3.14);
	this->body_.setRotation(angle);
}

RectangleShape Wall::GetBody() {
	return this->body_;
}

Wall::~Wall() {

}