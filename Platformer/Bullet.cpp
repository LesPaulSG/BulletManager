#include "Bullet.h"

Bullet::Bullet(sf::Vector2f pos, sf::Vector2f dir, float speed, float lifeTime)
	: pos(pos), dir(dir), speed(speed), lifeTime(lifeTime), time(0), alive(true) {
	body.setPosition(pos);
	body.setOrigin(sf::Vector2f(body.getOrigin().x + 5.0, body.getOrigin().y + 5.0));
	body.setRadius(10);
	body.setFillColor(sf::Color::Red);
}

sf::CircleShape* Bullet::GetBody() {return &body;}

bool Bullet::GetAlive() {return alive;}

void Bullet::CheckCollision(float time, std::vector<Wall>* walls, sf::Vector2f oldPos) {
	sf::Vector2f iPoint(0, 0);
	for (auto iter = walls->begin(); iter != walls->end(); ++iter) {
		if (Line(oldPos, pos).Intersection(Line(*iter->GetLine()), &iPoint)) {
			Collision(iPoint, oldPos, *iter->GetLine());
			if (iter->GetDestructable()) {
				walls->erase(iter);
				break;
			}
			CheckCollision(time, walls, oldPos);
		}
	}
}

void Bullet::Update(float t, std::vector<Wall> * walls) {
	sf::Vector2f oldPos = pos;			//position before update
	pos += dir * speed * t;				//new position
	body.setPosition(pos);

	CheckCollision(t, walls, oldPos);

	speed -= t/30;						//braking over time
	time += t;
	
	LifeCheck();
}

void Bullet::Collision(sf::Vector2f iPoint, sf::Vector2f oldPos, Line wall) {
	float angle = wall.AngleOfIntersec(Line(oldPos, pos));
	ChangeDirection(angle, wall.isPointRight(oldPos));
	pos = iPoint + dir * 0.00001f;		//update positon to intersection point + small distance
	body.setPosition(pos);
	speed *= 0.95;
}

void Bullet::ChangeDirection(float beta, bool right) {
	float alpha = 1.5708 - beta;			//calculate alpha angle	
	float angle = 3.14159 - (2.0 * alpha);	//rotation angle
	if (!right) {
		angle *= -1;
	}
	RotateVector(&dir, angle);
}

void Bullet::LifeCheck(){
	if (time >= lifeTime) {
		alive = false;
	} else if (speed <= 0) {
		alive = false;
	}
}