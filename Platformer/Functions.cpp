#include "Functions.h"

Line::Line(sf::Vector2f A, sf::Vector2f B) : pointA(A), pointB(B) {}

Line::~Line() {}

sf::Vector2f Line::MidPoint(){
	return sf::Vector2f(MidX(), MidY());
}

float Line::MidX(){
	return  pointB.x - pointA.x;
}

float Line::MidY(){
	return  pointB.y - pointA.y;
}

float LenghtOfLine(sf::Vector2f A, sf::Vector2f B) {
	return sqrt(pow((B.x - A.x), 2) + pow((B.y - A.y), 2));
}

bool isPointBeetwenPoints(float x, float a, float b) {
	return (x >= std::min(a, b) && x <= std::max(a, b));
}

bool PointBelongsLine(sf::Vector2f point, Line A, Line B) {
	if (!isPointBeetwenPoints(point.x, A.pointA.x, A.pointB.x)) {
		return false;
	}
	if (!isPointBeetwenPoints(point.x, B.pointA.x, B.pointB.x)) {
		return false;
	}
	if (!isPointBeetwenPoints(point.y, A.pointA.y, A.pointB.y)) {
		return false;
	}
	if (!isPointBeetwenPoints(point.y, B.pointA.y, B.pointB.y)) {
		return false;
	}
	return true;
}

bool Intersection(Line A, Line B, sf::Vector2f* iPoint) {
	double kA = A.MidY() / A.MidX();
	double kB = B.MidY() / B.MidX();
	if (kA == kB) {
		return false;
	}
	double bA = A.pointA.y - kA * A.pointA.x;
	double bB = B.pointA.y - kB * B.pointA.x;
	double xInter = (bB - bA) / (kA - kB);
	if (A.pointB.x == A.pointA.x) {
		xInter = A.pointA.x;
	}
	else if (B.pointB.x == B.pointA.x) {
		xInter = B.pointA.x;
	}
	double yInter = kA * xInter + bA;
	sf::Vector2f result(xInter, yInter);
	if (PointBelongsLine(result, A, B)) {
		*iPoint = result;
		return true;						
	}
	return false;
}

float AngleOfIntersec(Line A, Line B) {
	sf::Vector2f first(A.MidPoint()), second(B.MidPoint());

	float fMod = VectorsModule(first);
	float sMod = VectorsModule(second);

	return acos((first.x * second.x + first.y * second.y) / (fMod * sMod));	
}

//function checks point position relative to line (left or right)
bool isPointRight(Line line, sf::Vector2f point) {
	float D = (point.x - line.pointA.x) * (line.MidY()) - (point.y - line.pointA.y) * (line.MidX());
	if (D > 0) {
		return false;
	}
	return true;
}

float VectorsModule(sf::Vector2f vec){
	return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}

void RotateVector(sf::Vector2f* vec, float angle){
	float xNew = vec->x * cos(angle) - vec->y * sin(angle);
	float yNew = vec->x * sin(angle) + vec->y * cos(angle);
	vec->x = xNew;
	vec->y = yNew;
}

void RotateUnitVector(sf::Vector2f* vec, float angle){
	vec->x = sin(angle);
	vec->y = -cos(angle);
}