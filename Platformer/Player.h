#pragma once
#include "Wall.h"

enum MoveDir{ STP, FWD, BWD, RGH, LFT };

class Player{
private:
	sf::Vector2f pos;
	sf::Vector2f forwardVector;
	sf::Vector2f rightVector;
	float rotation;
	MoveDir dir;

	sf::CircleShape body;

public:
	Player(sf::Vector2f pos, float rotation);
	~Player() = default;

	sf::CircleShape GetBody();
	sf::Vector2f GetPosition();
	sf::Vector2f GetForwardVector();

	void SetDir(MoveDir nDir);

	void Rotate(float angle);
	void Rotate(sf::Vector2f mousePos);
	void Move(float time);	
};

