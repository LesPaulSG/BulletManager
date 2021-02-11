#include "Line.h"

Line::Line(sf::Vector2f A, sf::Vector2f B) 
	: pointA(std::move(A)),
	pointB(std::move(B)),
	midX(pointB.x - pointA.x),
	midY(pointB.y - pointA.y),
	midPoint(midX, midY),
	lenght(sqrt(pow(midX, 2) + pow(midY, 2)))
{}

Line::~Line() {}

/*sf::Vector2f Line::MidPoint() {
	//static sf::Vector2f midPoint(MidX(), MidY());
	return sf::Vector2f(MidX(), MidY());
}

float Line::MidX() {
	//static float midX = pointB.x - pointA.x;
	return  pointB.x - pointA.x;
}

float Line::MidY() {
	//static float midY = pointB.y - pointA.y;
	return  pointB.y - pointA.y;
}

float Line::Lenght() {
	//static float length = sqrt(pow(MidX(), 2) + pow(MidY(), 2));
	return sqrt(pow(MidX(), 2) + pow(MidY(), 2));
}*/

bool Line::Intersection(const Line& B, sf::Vector2f& iPoint) const {
	double kA = midY / midX;
	double kB = B.midY / B.midX;
	if (kA == kB) {
		return false;
	}
	double bA = pointA.y   - kA * pointA.x;
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
		iPoint = result;
		return true;
	}
	return false;
}

float Line::AngleOfIntersec(const Line& B) const {
	sf::Vector2f first(midPoint), second(B.midPoint);

	float fMod = VectorsModule(first);
	float sMod = VectorsModule(second);

	return acos((first.x * second.x + first.y * second.y) / (fMod * sMod));
}

bool Line::HasPoint(const sf::Vector2f& point) const {
	if (!isPointInRange(point.x, pointA.x, pointB.x)) {
		return false;
	}
	if (!isPointInRange(point.y, pointA.y, pointB.y)) {
		return false;
	}
	return true;
}

//function checks point position relative to line (left or right)
bool Line::isPointRight(const sf::Vector2f& point) const {
	float D = (point.x - pointA.x) * midY - (point.y - pointA.y) * midX;
	if (D > 0) {
		return false;
	}
	return true;
}
