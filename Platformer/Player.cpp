#include "Player.h"

Player::Player(sf::Vector2f pos, float cRotation) : pos(pos), rotation(0.0f) {
	forwardVector = sf::Vector2f(0, -1);
	rightVector = sf::Vector2f(1, 0);

	Rotate(cRotation);

	body.setPosition(pos);
	body.setOrigin(sf::Vector2f(body.getOrigin().x + 5.0, body.getOrigin().y + 5.0));
	body.setRadius(10);
	body.setFillColor(sf::Color::Blue);
}

void Player::Rotate(float angle){
	rotation = angle - 1.5708;

	float fxNew = sin(rotation);
	float fyNew = -cos(rotation);
	forwardVector.x = fxNew;
	forwardVector.y = fyNew;
	//RotateUnitVector(&forwardVector, angle);
	//RotateUnitVector(&rightVector, angle);
	float rxNew = cos(rotation);
	float ryNew = sin(rotation);
	rightVector.x = rxNew;
	rightVector.y = ryNew;
}

void Player::Rotate(sf::Vector2f mousePos){
	float angle = AngleOfIntersec(Line(sf::Vector2f(0, 0), sf::Vector2f(1920, 0)), Line(pos, mousePos));
	angle += 3.14159;
	if (mousePos.y < pos.y) {
		angle *= -1.0;
	}
	Rotate(angle);
}

void Player::Move(MoveDir dir, float time, std::vector<Wall>* walls){
	sf::Vector2f oldPos = pos;
	switch (dir){
	case FWD:
		pos += forwardVector;
		break;
	case BWD:
		pos -= forwardVector;
		break;
	case RGH:
		pos += rightVector;
		break;
	case LFT:
		pos -= rightVector;
		break;
	default:
		break;
	}
	body.setPosition(pos);
}

sf::CircleShape Player::GetBody(){return body;}

sf::Vector2f Player::GetPosition() {return pos;}

sf::Vector2f Player::GetForwardVector(){return forwardVector;}