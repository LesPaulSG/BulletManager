#include "Player.h"
#include <iostream>
#include "Wall.h"

Player::Player(sf::Vector2f pos, float cRotation) : pos(pos), rotation(0.0f) {
	forwardVector = sf::Vector2f(0, -1);
	rightVector = sf::Vector2f(1, 0);

	SetRotation(cRotation);

	body.setPosition(pos);
	body.setOrigin(sf::Vector2f(body.getOrigin().x + 5.0, body.getOrigin().y + 5.0));
	body.setRadius(10);
	body.setFillColor(sf::Color::Blue);

	fwdVecBody.setSize(sf::Vector2f(2, 70));
	fwdVecBody.setFillColor(sf::Color::Green);

	rghVecBody.setSize(sf::Vector2f(2, 2));
	rghVecBody.setFillColor(sf::Color::Yellow);
}

Player::~Player() {}

void Player::Rotate(float angle){
	rotation = angle - 1.5708;

	float fxNew = sin(rotation);
	float fyNew = -cos(rotation);
	forwardVector.x = fxNew;
	forwardVector.y = fyNew;

	float rxNew = cos(rotation);
	float ryNew = sin(rotation);
	rightVector.x = rxNew;
	rightVector.y = ryNew;

	fwdVecBody.setRotation(rotation*180/3.14);
	fwdVecBody.setPosition(pos + forwardVector);
	rghVecBody.setPosition(pos + rightVector);
}

void Player::Rotate(sf::Vector2f mousePos){
	float angle = AngleOfIntersec(Line(Vector2f(0, 0), Vector2f(1920, 0)), Line(pos, mousePos));
	angle += 3.14159;
	if (mousePos.y < pos.y) {
		angle *= -1.0;
	}
	Rotate(angle);
}

void Player::Move(MoveDir dir, float time, std::vector<Wall>* walls){
	Vector2f oldPos = pos;
	switch (dir){
	case FWD:
		pos += forwardVector * 5.0f;
		break;
	case BWD:
		pos -= forwardVector * 5.0f;
		break;
	case RGH:
		pos += rightVector * 5.0f;
		break;
	case LFT:
		pos -= rightVector * 5.0f;
		break;
	default:
		break;
	}
	CheckCollision(time, walls, oldPos);
	body.setPosition(pos);
	fwdVecBody.setPosition(pos + forwardVector);
	rghVecBody.setPosition(pos + rightVector);
}

void Player::CheckCollision(float time, std::vector<Wall>* walls, Vector2f oldPos) {
	for (std::vector<Wall>::iterator iter = walls->begin(); iter != walls->end(); ++iter) {
		Vector2f iPoint = Intersection(Line(oldPos, pos), Line(iter->pointA, iter->pointB)); //if no intersection returns (-9999, -9999)
		if (iPoint.x > -1000 && iPoint.y > -1000) {													//checks for intersection
			float angle = AngleOfIntersec(Line(oldPos, pos), Line(iter->pointA, iter->pointB));
			//ChangeDirection(angle, isPointRight(Line(iter->pointA, iter->pointB), oldPos));
			pos = iPoint + forwardVector * 0.00001f;	//update positon to intersection point + small distance
			body.setPosition(pos);
			//speed *= 0.95;                           //-5% of speed every collision
			if (iter->GetDestructable()) {
				walls->erase(iter);
				break;
			}
			CheckCollision(time, walls, oldPos);
		}
	}
}

sf::CircleShape Player::GetBody(){
	return body;
}

sf::RectangleShape Player::GetFwdVecBody(){
	return fwdVecBody;
}

sf::RectangleShape Player::GetRghVecBody(){
	return rghVecBody;
}

sf::Vector2f Player::GetPosition(){
	return pos;
}

sf::Vector2f Player::GetForwardVector()
{
	return forwardVector;
}

void Player::SetRotation(float angle){
	std::cout << angle << "   ";
	//float alpha = 90 - beta;			//calculate alpha angle	
	//float angle = 180 - (2 * alpha);
	//angle *= -(180 / 3.14);
	//std::cout << angle << "   ";
	Rotate(angle);
}
