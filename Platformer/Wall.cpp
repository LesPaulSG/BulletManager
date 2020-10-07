#include <SFML/Graphics.hpp>
#include <iostream>

#include "Wall.h"

Wall::Wall(sf::Vector2f A, sf::Vector2f B, bool destructable) 
	: line(A, B), destructable(destructable) {
	float lenght = LenghtOfLine(A, B);
	vector = line.MidPoint();
	CalculateRotation();
	body.setPosition(A);
	body.setSize(sf::Vector2f(5, lenght));
	if (destructable) {
		body.setFillColor(sf::Color::Yellow);
	} else {
		body.setFillColor(sf::Color::Green);
	}
}

bool Wall::GetDestructable() {
	return destructable;
}

sf::RectangleShape Wall::GetBody() {
	return body;
}

Line* Wall::GetLine(){
	return &line;
}

void Wall::CalculateRotation() {
	double angle = acos(vector.y / VectorsModule(vector));
	angle *= -(180 / 3.14);
	if (line.pointA.x > line.pointB.x) {
		angle *= -1;
	}
	body.setRotation(angle);
}

void Wall::Transform() {
	destructable = !destructable;
	if (destructable) {
		body.setFillColor(sf::Color::Yellow);
	} else {
		body.setFillColor(sf::Color::Green);
	}
}

Wall::~Wall() {}