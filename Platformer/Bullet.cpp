#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>

#include "Bullet.h"
#include "Wall.h"
#include "Functions.h"

Bullet::Bullet(sf::Vector2f pos, sf::Vector2f dir, float speed, float lifeTime)
	: pos(pos), dir(dir), speed(speed), lifeTime(lifeTime), time(0), alive(true) {
	body.setPosition(pos);
	body.setOrigin(sf::Vector2f(body.getOrigin().x + 5.0, body.getOrigin().y + 5.0));
	body.setRadius(10);
	body.setFillColor(sf::Color::Red);
}

sf::CircleShape Bullet::GetBody() {
	return body;
}

bool Bullet::GetAlive() {
	return alive;
}

void Bullet::CheckCollision(float time, std::vector<Wall>* walls, sf::Vector2f oldPos) {
	for (auto iter = walls->begin(); iter != walls->end(); ++iter) {
		sf::Vector2f iPoint = Intersection(Line(oldPos, pos), Line(*iter->GetLine()));				//if no intersection returns (-9999, -9999)
		if (iPoint.x > -1000 && iPoint.y > -1000) {													//checks for intersection
			float angle = AngleOfIntersec(Line(oldPos, pos), Line(*iter->GetLine()));
			ChangeDirection(angle, isPointRight(Line(*iter->GetLine()), oldPos));
			pos = iPoint + dir * 0.00001f;				//update positon to intersection point + small distance
			body.setPosition(pos);
			speed *= 0.95;								//-5% of speed every collision
			if (iter->GetDestructable()) {
				walls->erase(iter);
				break;
			}
			CheckCollision(time, walls, oldPos);
		}
	}
}

void Bullet::Update(float t, std::vector<Wall> * walls) {
	sf::Vector2f oldPos = pos;							//position before update
	pos += dir * speed * t;								//new position
	body.setPosition(pos);

	CheckCollision(t, walls, oldPos);

	speed -= t/30;										//braking over time
	time += t;
	if (time >= lifeTime) {
		alive = false;
	}
	else if (speed <= 0) {
		alive = false;
	}
}

void Bullet::ChangeDirection(float beta, bool right) {
	float alpha = 1.5708 - beta;			//calculate alpha angle	
	float angle = 3.14159 - (2.0 * alpha);	//rotation angle
	if (!right) {
		angle *= -1;
	}
	float xNew = dir.x * cos(angle) - dir.y * sin(angle);
	float yNew = dir.x * sin(angle) + dir.y * cos(angle);
	dir.x = xNew;
	dir.y = yNew;
}

Bullet::~Bullet() {}