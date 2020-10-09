#pragma once
#include <SFML/Graphics.hpp>

const int BULLETS_MAX_CAPACITY = 50;
const int WALLS_MAX_CAPACITY = 50;

const int HEIGHT = sf::VideoMode::getDesktopMode().height;
const int WIDTH = sf::VideoMode::getDesktopMode().width;

//helper class
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

bool isPointInRange(float x, float a, float b);

bool PointBelongsLine(sf::Vector2f point, Line A, Line B);

float VectorsModule(sf::Vector2f vec);

void RotateVector(sf::Vector2f* vec, float angle);

void RotateUnitVector(sf::Vector2f* vec, float angle);