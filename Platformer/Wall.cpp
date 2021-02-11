#include "Wall.h"

Wall::Wall(sf::Vector2f A, sf::Vector2f B, bool destructable) 
	:	destructable(destructable),
		alive(true),
		line(A, B) {
	vector = line.midPoint;
	CalculateRotation();
	body.setPosition(A);
	body.setSize(sf::Vector2f(5, line.lenght));
	UpdateColor();
}

bool Wall::GetDestructable() const {return destructable;}

bool Wall::GetAlive() const {return alive;}

const sf::RectangleShape& Wall::GetBody() const {return body;}

const Line& Wall::GetLine() const {return line;}

void Wall::Destroy() { alive = false; }

void Wall::CalculateRotation() {
	double angle = acos(vector.y / VectorsModule(vector));
	angle *= -(180.0 / 3.14);
	if (line.pointA.x > line.pointB.x) {
		angle *= -1.0;
	}
	body.setRotation(angle);
}

void Wall::Transform() {
	destructable = !destructable;
	UpdateColor();
}

void Wall::UpdateColor(){
	if (destructable) {
		body.setFillColor(sf::Color::Yellow);
	} else {
		body.setFillColor(sf::Color::Green);
	}
}