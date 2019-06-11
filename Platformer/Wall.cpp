#include <SFML/Graphics.hpp>
#include <iostream>
#include "Wall.h"

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

bool Wall::GetDestructable() {
	return this->destructable_;
}

void Wall::CalculateVector() {
	this->vector_.x = this->pointB.x - this->pointA.x;
	this->vector_.y = this->pointB.y - this->pointA.y;
}

void Wall::CalculateRotation() {
	double angle = acos(this->vector_.y / (sqrt(this->vector_.x * this->vector_.x + this->vector_.y * this->vector_.y)));
	angle *= -(180 / 3.14);
	if (this->pointA.x > this->pointB.x) {
		angle *= -1;
	}
	this->body_.setRotation(angle);
}

RectangleShape Wall::GetBody() {
	return this->body_;
}

Wall::~Wall() {

}