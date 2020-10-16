#pragma once
#include "Functions.h"

class Line {
public:
	sf::Vector2f pointA;
	sf::Vector2f pointB;

	Line(sf::Vector2f A, sf::Vector2f B);
	~Line();

	sf::Vector2f MidPoint();
	float MidX();
	float MidY();
	float Lenght();
	bool isPointRight(sf::Vector2f point);
	bool Intersection(Line B, sf::Vector2f* iPoint);
	float AngleOfIntersec(Line B);
	bool HasPoint(sf::Vector2f point);
};