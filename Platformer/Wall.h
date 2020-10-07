#pragma once
#include <SFML/Graphics.hpp>

#include "Functions.h"

class Wall {
private:
	bool destructable;
	sf::RectangleShape body;
	sf::Vector2f vector;
	Line line;

public:
	Wall(sf::Vector2f, sf::Vector2f, bool);
	~Wall();

	bool GetDestructable();
	sf::RectangleShape GetBody();
	Line* GetLine();

	void CalculateRotation();
	void Transform();
};