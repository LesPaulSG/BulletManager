#pragma once
#include <SFML/Graphics.hpp>
#include "Wall.h"

class Bullet {
private:
	CircleShape body_;
	float speed_;
	float time_;
	float lifeTime_;
	Vector2f pos_;
	Vector2f dir_;
	bool alive_;

public:
	CircleShape GetBody();
	bool GetAlive();

	void Update(float, std::vector<Wall>*);
	void ChangeDirection(float, bool);

	Bullet(Vector2f, Vector2f, float, float);
	~Bullet();
};