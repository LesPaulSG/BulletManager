#include "Player.h"

Player::Player(sf::Vector2f pos, float cRotation) : pos(std::move(pos)), rotation(0.f) {
	forwardVector = sf::Vector2f(0.f, -1.f);
	rightVector   = sf::Vector2f(1.f, 0.f);

	Rotate(cRotation);

	body.setPosition(pos);
	body.setOrigin(sf::Vector2f(body.getOrigin().x + 5.f, body.getOrigin().y + 5.f));
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

void Player::Rotate(const sf::Vector2f& mousePos){
	float angle = Line(sf::Vector2f(0, 0), (sf::Vector2f(1920, 0))).AngleOfIntersec(Line(pos, mousePos));
	angle += 3.14159f;
	if (mousePos.y < pos.y) {
		angle *= -1.f;
	}
	Rotate(angle);
}

void Player::Move(float time){
	sf::Vector2f oldPos = pos;
	switch (dir){
	case STP:
		return;
	case FWD:
		pos += forwardVector * time * 50.f;
		break;
	case BWD:
		pos -= forwardVector * time * 50.f;
		break;
	case RGH:
		pos += rightVector * time * 50.f;
		break;
	case LFT:
		pos -= rightVector * time * 50.f;
		break;
	default:
		break;
	}
	body.setPosition(pos);
}

const sf::CircleShape& Player::GetBody() const {return body;}

const sf::Vector2f& Player::GetPosition() const {return pos;}

const sf::Vector2f& Player::GetForwardVector() const {return forwardVector;}

void Player::SetDir(MoveDir nDir){
	dir = nDir;
}
