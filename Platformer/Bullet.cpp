#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include "Bullet.h"
#include "Wall.h"
#include "Definitions.h"

Bullet::Bullet(Vector2f pos, Vector2f dir, float speed, float lifeTime) : pos_(pos), dir_(dir), speed_(speed), lifeTime_(lifeTime), time_(0), alive_(true) {
	this->body_.setPosition(pos);
	this->body_.setOrigin(Vector2f(this->body_.getOrigin().x + 5.0, this->body_.getOrigin().y + 5.0));
	this->body_.setRadius(10.0);
	this->body_.setFillColor(Color::Red);
}

CircleShape Bullet::GetBody() {
	return this->body_;
}

bool Bullet::GetAlive() {
	return this->alive_;
}

void Bullet::CheckCollision(float time, int start, int end, std::vector<Wall>* walls, Vector2f oldPos) {
	for (std::vector<Wall>::iterator iter = walls->begin() + start; iter != walls->begin() + end; ++iter) {
		Vector2f iPoint = Intersection(Line(oldPos, this->pos_), Line(iter->pointA, iter->pointB)); //if no intersection returns (-9999, -9999)
		if (iPoint.x > -1000 && iPoint.y > -100) {													//checks for intersection
			float angle = AngleOfIntersec(Line(oldPos, this->pos_), Line(iter->pointA, iter->pointB));
			this->ChangeDirection(angle, isPointRight(Line(iter->pointA, iter->pointB), oldPos));
			this->pos_ = iPoint + this->dir_ * this->speed_ * time;	//update positon to intersection point + update distance
			this->body_.setPosition(this->pos_);
			if (iter->GetDestructable()) {
				walls->erase(iter);
				break;
			}
		}
	}
}

void Bullet::Update(float time, std::vector<Wall> * walls) {
	Vector2f oldPos = this->pos_;					//position before update
	Vector2f newPos = this->pos_ + this->dir_ * this->speed_ * time;	//new position
	this->body_.setPosition(this->pos_);
	bool dirChanged = false;

	/*std::thread th1(&Bullet::CheckCollision, this, time, 0, std::min(WALLS_MAX_CAPACITY/5, int(walls->size())), walls, oldPos);
	th1.join();
	if (walls->size() >= 10) {
		std::thread th2(&Bullet::CheckCollision, this, time, 10, std::min(2*WALLS_MAX_CAPACITY/5, int(walls->size())), walls, oldPos);
		th2.join();
	} else if (walls->size() >= 20) {
		std::thread th3(&Bullet::CheckCollision, this, time, 20, std::min(3*WALLS_MAX_CAPACITY/5, int(walls->size())), walls, oldPos);
		th3.join();
	} else if (walls->size() >= 30) {
		std::thread th4(&Bullet::CheckCollision, this, time, 30, std::min(3*WALLS_MAX_CAPACITY/5, int(walls->size())), walls, oldPos);
		th4.join();
	} else if (walls->size() >= 40) {
		std::thread th5(&Bullet::CheckCollision, this, time, 40, std::min(WALLS_MAX_CAPACITY, int(walls->size())), walls, oldPos);
		th5.join();
	}*/
	for (std::vector<Wall>::iterator iter = walls->begin(); iter != walls->end(); ++iter) {
		Vector2f iPoint = Intersection(Line(oldPos, newPos), Line(iter->pointA, iter->pointB)); //if no intersection returns (-9999, -9999)
		if (iPoint.x != -9999.0 && iPoint.y != -9999.0) {													//checks for intersection
			float angle = AngleOfIntersec(Line(oldPos, newPos), Line(iter->pointA, iter->pointB));
			this->ChangeDirection(angle, isPointRight(Line(iter->pointA, iter->pointB), oldPos));
			this->pos_ = iPoint + this->dir_ * this->speed_ * time;	//update positon to intersection point + update distance
			this->body_.setPosition(this->pos_);
			dirChanged = true;
			if (iter->GetDestructable()) {
				walls->erase(iter);
				break;
			}
		}
	}
	
	if (!dirChanged) {
		this->pos_ = newPos;
		this->body_.setPosition(this->pos_);
	}

	this->speed_ -= time;	
	this->time_ += time;	
	if (this->time_ >= this->lifeTime_) {
		this->alive_ = false;
	}
}

void Bullet::ChangeDirection(float beta, bool right) {
	float alpha = 90 - beta;			//calculate alpha angle	
	float angle = 180 - (2 * alpha);	//rotation angle
	if (!right) {
		angle *= -1;
	}
	float xNew = this->dir_.x * cos(angle) - this->dir_.y * sin(angle);
	float yNew = this->dir_.x * sin(angle) + this->dir_.y * cos(angle);
	this->dir_.x = xNew;
	this->dir_.y = yNew;
}

Bullet::~Bullet() {
	this->body_.~CircleShape();
}