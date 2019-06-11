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

CircleShape Bullet::GetBody() {
	return this->body_;
}

bool Bullet::GetAlive() {
	return this->alive_;
}

void Bullet::Update(float time, std::vector<Wall> * walls) {
	Vector2f oldPos = this->pos_;					//position before update
	this->pos_ += this->dir_ * this->speed_ * time;	//new position
	this->body_.setPosition(this->pos_);

	for (std::vector<Wall>::iterator iter = walls->begin(); iter != walls->end(); ++iter) {
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