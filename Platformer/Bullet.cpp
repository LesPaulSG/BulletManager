#include <SFML/Graphics.hpp>
#include <iostream>
#include "Bullet.h"
#include "Wall.h"
#include "Definitions.h"

Bullet::Bullet(Vector2f pos, Vector2f dir, float speed, float lifeTime) : pos_(pos), dir_(dir), speed_(speed), lifeTime_(lifeTime), time_(0), alive_(true) {
	this->body_.setPosition(pos);
	this->body_.setOrigin(Vector2f(this->body_.getOrigin().x + 5.0, this->body_.getOrigin().y + 5.0));
	this->body_.setRadius(10.0);
	this->body_.setFillColor(Color::Red);
}

void Bullet::Update(float time, std::vector<Wall> * walls) {
	//Vector2f newPos = this->pos_ + this->dir_ * this->speed_ * time;
	Vector2f oldPos = this->pos_;
	this->pos_ += this->dir_ * this->speed_ * time;
	this->body_.setPosition(this->pos_);
	std::vector<Wall>::iterator iter = walls->begin();
	for (iter; iter != walls->end(); ++iter) {
		Vector2f wallPosA = iter->pointA;
		Vector2f wallPosB = iter->pointB;
		Vector2f iPoint = Intersection(Line(oldPos, this->pos_), Line(wallPosA, wallPosB));
		if (iPoint.x != -9999 && iPoint.y != -9999) {
			float angle = AngleOfIntersec(Line(oldPos, this->pos_), Line(wallPosA, wallPosB));
			//std::cout << iPoint.x << " " << iPoint.y << std::endl;
			//std::cout << angle << std::endl;
			this->ChangeDirection(angle, isPointRight(Line(wallPosA, wallPosB), oldPos));
			this->pos_ = iPoint + this->dir_ * time;
			this->body_.setPosition(iPoint);
			if (iter->GetDestructable()) {
				walls->erase(iter);
				break;
			}
		}
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

void Bullet::ChangeDirection(float beta, bool cond) {
	float alpha = 90 - beta;
	float angle = 180 - (2 * alpha);
	float xNew, yNew;
	if (cond) {
		xNew = this->dir_.x * cos(angle) - this->dir_.y * sin(angle);
		yNew = this->dir_.x * sin(angle) + this->dir_.y * cos(angle);
	}
	else if (!cond) {
		xNew = this->dir_.x * cos(-angle) - this->dir_.y * sin(-angle);
		yNew = this->dir_.x * sin(-angle) + this->dir_.y * cos(-angle);
	}
	this->dir_.x = xNew;
	this->dir_.y = yNew;
}

Bullet::~Bullet() {
	this->body_.~CircleShape();
}