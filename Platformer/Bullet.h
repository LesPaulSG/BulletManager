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
	void Update(float, std::vector<Wall>*);
	CircleShape GetBody();
	float GetRadius();
	float GetSpeed();
	float GetTime();
	float GetLifeTime();
	Vector2f GetPos();
	Vector2f GetGetDir();
	bool GetAlive();
	void ChangeDirection(float, bool);

	//void SetRadius();
	//void SetSpeed();
	//void SetTime();
	//void SetLifeTime();
	//void SetPos();
	//void SetDir();

	Bullet(Vector2f, Vector2f, float, float);
	~Bullet();
};