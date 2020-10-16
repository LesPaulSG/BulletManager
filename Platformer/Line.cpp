#include "Line.h"

Line::Line(sf::Vector2f A, sf::Vector2f B) : pointA(A), pointB(B) {}

Line::~Line() {}

sf::Vector2f Line::MidPoint() {
	return sf::Vector2f(MidX(), MidY());
}

float Line::MidX() {
	return  pointB.x - pointA.x;
}

float Line::MidY() {
	return  pointB.y - pointA.y;
}

float Line::Lenght() {
	return sqrt(pow(MidX(), 2) + pow(MidY(), 2));
}

bool Line::Intersection(Line B, sf::Vector2f* iPoint) {
	double kA = MidY() / MidX();
	double kB = B.MidY() / B.MidX();
	if (kA == kB) {
		return false;
	}
	double bA = pointA.y - kA * pointA.x;
	double bB = B.pointA.y - kB * B.pointA.x;
	double xInter;
	if (pointB.x == pointA.x) {
		xInter = pointA.x;
	}
	else if (B.pointB.x == B.pointA.x) {
		xInter = B.pointA.x;
	}
	else {
		xInter = (bB - bA) / (kA - kB);
	}
	double yInter = kA * xInter + bA;
	sf::Vector2f result(xInter, yInter);
	if (HasPoint(result) && B.HasPoint(result)) {
		*iPoint = result;
		return true;
	}
	return false;
}

float Line::AngleOfIntersec(Line B) {
	sf::Vector2f first(MidPoint()), second(B.MidPoint());

	float fMod = VectorsModule(first);
	float sMod = VectorsModule(second);

	return acos((first.x * second.x + first.y * second.y) / (fMod * sMod));
}

bool Line::HasPoint(sf::Vector2f point) {
	if (!isPointInRange(point.x, pointA.x, pointB.x)) {
		return false;
	}
	if (!isPointInRange(point.y, pointA.y, pointB.y)) {
		return false;
	}
	return true;
}

//function checks point position relative to line (left or right)
bool Line::isPointRight(sf::Vector2f point) {
	float D = (point.x - pointA.x) * MidY() - (point.y - pointA.y) * MidX();
	if (D > 0) {
		return false;
	}
	return true;
}
