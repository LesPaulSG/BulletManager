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

	const sf::CircleShape& GetBody() const;
	const sf::Vector2f& GetPosition() const;
	const sf::Vector2f& GetForwardVector() const;

	void SetDir(MoveDir nDir);

	void Rotate(float angle);
	void Rotate(const sf::Vector2f& mousePos);
	void Move(float time);	
};

