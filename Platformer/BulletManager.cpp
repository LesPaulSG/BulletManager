#include "BulletManager.h"
#include <iostream>
#include <cmath>

bool PointBelongsLine(Vector2f point, Line A, Line B) {
	if (!(point.x >= std::min(A.pointA.x, A.pointB.x) && point.x <= std::max(A.pointA.x, A.pointB.x))) {
		//std::cout << "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111" << std::endl;
		return false;
	}
	if (!(point.x >= std::min(B.pointA.x, B.pointB.x) && point.x <= std::max(B.pointA.x, B.pointB.x))) {
		//std::cout << "2222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222" << std::endl;
		return false;
	}
	if (!(point.y >= std::min(A.pointA.y, A.pointB.y) && point.y <= std::max(A.pointA.y, A.pointB.y))) {
		//std::cout << "3333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333" << std::endl;
		return false;
	}
	if (!(point.y >= std::min(B.pointA.y, B.pointB.y) && point.y <= std::max(B.pointA.y, B.pointB.y))) {
		//std::cout << "4444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444" << std::endl;
		return false;
	}
	return true;
}

Vector2f Intersection(Line A, Line B) {
	float kA = (A.pointB.y - A.pointA.y) / (A.pointB.x - A.pointA.x);
	float kB = (B.pointB.y - B.pointA.y) / (B.pointB.x - B.pointA.x);
	if (kA == kB) { // || kA == 0 || kB == 0
		return Vector2f(-9999, -9999);
	}
	float bA = A.pointA.y - kA * A.pointA.x;
	//(A.pointB.x * A.pointA.y - A.pointA.x * A.pointB.y) / (A.pointB.x - A.pointA.x);
	float bB = B.pointA.y - kB * B.pointA.x;
	//(B.pointB.x * B.pointA.y - B.pointA.x * B.pointB.y) / (B.pointB.x - B.pointA.x);
	float xInter = (bB - bA) / (kA - kB);
	if (A.pointB.x == A.pointA.x) {
		xInter = A.pointA.x;
	} else if (B.pointB.x == B.pointA.x) {
		xInter = B.pointA.x;
	}
	float yInter = kA * xInter + bA;
	Vector2f result(xInter, yInter);
	if (PointBelongsLine(result, A, B)) {
		return result;
	}
	return Vector2f(-9999, -9999);
}

float AngleOfIntersec(Line A, Line B) {
	Vector2f first, second;
	first.x = A.pointB.x - A.pointA.x;
	first.y = A.pointB.y - A.pointA.y;
	second.x = B.pointB.x - B.pointA.x;
	second.y = B.pointB.y - B.pointA.y;
	std::cout << first.x << " " << first.y << " | " << second.x << " " << second.y << std::endl;
	float fMod = std::sqrt(first.x * first.x + first.y * first.y);
	float sMod = std::sqrt(second.x * second.x + second.y * second.y);
	return acos((first.x * second.x + first.y * second.y) / (fMod * sMod));
	//return angRad *= (180 / 3.14);
}

bool isPointRight(Line line, Vector2f point) {
	float D = (point.x - line.pointA.x) * (line.pointB.y - line.pointA.y) - (point.y - line.pointA.y) * (line.pointB.x - line.pointA.x);
	if (D > 0) {
		return false;
	}
	return true;
}

///////////// Line //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Line::Line() {

}

Line::Line(Vector2f A, Vector2f B) : pointA(A), pointB(B) {

}

Line::~Line() {

}

///////////// BulletManager /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

///////////// Bullet ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
	for (int i = 0; i < walls->size(); i++) {
		Vector2f wallPosA = walls->at(i).pointA;
		Vector2f wallPosB = walls->at(i).pointB;
		Vector2f iPoint = Intersection(Line(oldPos, this->pos_), Line(wallPosA, wallPosB));
		if (iPoint.x != -9999 && iPoint.y != -9999) {
			float angle = AngleOfIntersec(Line(oldPos, this->pos_), Line(wallPosA, wallPosB));
			std::cout << iPoint.x << " " << iPoint.y << std::endl;
			std::cout << angle << std::endl;
			this->ChangeDirection(angle, isPointRight(Line(wallPosA, wallPosB), oldPos));
			this->pos_ = iPoint + this->dir_ * time;
			this->body_.setPosition(iPoint);
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
	} else if (!cond) {
		xNew = this->dir_.x * cos(-angle) - this->dir_.y * sin(-angle);
		yNew = this->dir_.x * sin(-angle) + this->dir_.y * cos(-angle);
	}
	this->dir_.x = xNew;
	this->dir_.y = yNew;
}

Bullet::~Bullet() {
	this->body_.~CircleShape();
}

///////////// Wall //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Wall::Wall() : destructable_(true) {
	this->body_.setSize(Vector2f(0, 0));
	this->body_.setRotation(0);
	this->body_.setFillColor(Color::White);
}

Wall::Wall(Vector2f A, Vector2f B) : pointA(A), pointB(B), destructable_(true) {
	float lenght = sqrt(pow((B.x - A.x), 2) + pow((B.y - A.y), 2));
	CalculateVector();
	CalculateRotation();
	this->body_.setPosition(A);
	this->body_.setSize(Vector2f(5, lenght));
	this->body_.setFillColor(Color::Yellow);
	std::cout << pointA.x << " " << pointA.y << std::endl;
	std::cout << pointB.x << " " << pointB.y << std::endl;
	std::cout << std::endl;
}

Wall::Wall(Vector2f A, Vector2f B, bool destructable) : pointA(A), pointB(B), destructable_(destructable) {
	float lenght = sqrt(pow((B.x - A.x), 2) + pow((B.y - A.y), 2));
	CalculateVector();
	CalculateRotation();
	this->body_.setPosition(A);
	this->body_.setSize(Vector2f(5, lenght));
	if (destructable) {
		this->body_.setFillColor(Color::Yellow);
	}
	else {
		this->body_.setFillColor(Color::Green);
	}
	std::cout << pointA.x << " " << pointA.y << std::endl;
	std::cout << pointB.x << " " << pointB.y << std::endl;
	std::cout << std::endl;
}

void Wall::CalculateVector() {
	this->vector_.x = this->pointB.x - this->pointA.x;
	this->vector_.y = this->pointB.y - this->pointA.y;
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