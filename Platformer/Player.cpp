#include "Player.h"
#include <iostream>

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

void Player::Move(MoveDir dir){
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
	body.setPosition(pos);
	fwdVecBody.setPosition(pos + forwardVector);
	rghVecBody.setPosition(pos + rightVector);
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
