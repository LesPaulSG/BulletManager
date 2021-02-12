#pragma once
#include "Line.h"

class Wall {
private:
	bool destructable;
	bool alive;
	sf::Vector2f vector;
	sf::RectangleShape body;
	Line line;
	double rotation;

public:
	Wall(sf::Vector2f A, sf::Vector2f B, bool);
	~Wall() = default;

	bool GetDestructable() const;
	bool GetAlive() const;
	const sf::RectangleShape& GetBody() const;
	const Line& GetLine() const;
	double GetRotation() const;

	void Destroy();
	void CalculateRotation();
	void Transform();
	void UpdateColor();
};