#pragma once
#include "Wall.h"

class Bullet {
private:
	sf::CircleShape body;
	float speed;
	float time;
	float lifeTime;
	sf::Vector2f pos;
	sf::Vector2f dir;
	bool alive;

public:
	sf::CircleShape* GetBody();
	bool GetAlive();

	Bullet(sf::Vector2f pos, sf::Vector2f dir, float speed, float lifeTime);
	~Bullet() = default;

	void CheckCollision(float time, std::vector<Wall>* walls, sf::Vector2f oldPos);
	void Update(float t, std::vector<Wall>* walls);
	void Collision(sf::Vector2f iPoint, sf::Vector2f oldPos, Line wall);
	void ChangeDirection(float beta, bool right);
	void LifeCheck();
};