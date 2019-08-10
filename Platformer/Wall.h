#pragma once
#include <SFML/Graphics.hpp>
#include "Definitions.h"

class Wall {
private:
	bool destructable_;
	RectangleShape body_;
	Vector2f vector_;

public:
	Vector2f pointA, pointB;

	bool GetDestructable();
	RectangleShape GetBody();

	void CalculateVector();
	void CalculateRotation();
	void Transform();

	Wall(Vector2f, Vector2f);
	Wall(Vector2f, Vector2f, bool);
	~Wall();
};