#pragma once
#include <SFML/Graphics.hpp>

class Wall {
private:
	bool destructable_;
	RectangleShape body_;
	Vector2f vector_;
	//float height_;
	//float width;

public:
	Vector2f pointA, pointB;

	bool GetDestructable();
	RectangleShape GetBody();
	void CalculateVector();
	void CalculateRotation();
	Wall();
	Wall(Vector2f, Vector2f);
	Wall(Vector2f, Vector2f, bool);
	~Wall();
};