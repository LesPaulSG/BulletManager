#include <SFML/Graphics.hpp>
#include <iostream>
#include "Wall.h"

Wall::Wall(Vector2f A, Vector2f B) : pointA(A), pointB(B), destructable_(true) {
	float lenght = LenghtOfLine(A, B);
	CalculateVector();
	CalculateRotation();
	this->body_.setPosition(A);
	this->body_.setSize(Vector2f(5, lenght));
	this->body_.setFillColor(Color::Yellow);
}

Wall::Wall(Vector2f A, Vector2f B, bool destructable) : pointA(A), pointB(B), destructable_(destructable) {
	float lenght = LenghtOfLine(A, B);
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
}

bool Wall::GetDestructable() {
	return this->destructable_;
}

RectangleShape Wall::GetBody() {
	return this->body_;
}

void Wall::CalculateVector() {	//vector by coordinates of wall					
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

Wall::~Wall() {

}