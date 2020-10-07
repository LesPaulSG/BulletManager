#pragma once
#include <SFML/Graphics.hpp>

#include "Functions.h"
#include "Wall.h"

enum MoveDir{ FWD, BWD, RGH, LFT };

class Player{
private:
	sf::Vector2f pos;
	sf::Vector2f forwardVector;
	sf::Vector2f rightVector;
	float rotation;

	sf::CircleShape body;
	sf::RectangleShape fwdVecBody;
	sf::RectangleShape rghVecBody;

public:
	Player(sf::Vector2f pos, float rotation);
	~Player();

	sf::CircleShape GetBody();
	sf::RectangleShape GetFwdVecBody();
	sf::RectangleShape GetRghVecBody();
	sf::Vector2f GetPosition();
	sf::Vector2f GetForwardVector();

	void SetRotation(float angle);

	void Rotate(float angle);
	void Rotate(sf::Vector2f mousePos);
	void Move(MoveDir dir, float time, std::vector<Wall>* walls);
	void CheckCollision(float time, std::vector<Wall>* walls, sf::Vector2f oldPos);
};

