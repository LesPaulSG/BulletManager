#include <SFML/Graphics.hpp>
#include <iostream>
#include "Definitions.h"

Line::Line(Vector2f A, Vector2f B) : pointA(A), pointB(B) {}

Line::~Line() {}

float LenghtOfLine(Vector2f A, Vector2f B) {
	return sqrt(pow((B.x - A.x), 2) + pow((B.y - A.y), 2));
}

bool isPointBeetwenPoints(float x, float a, float b) {
	return (x >= std::min(a, b) && x <= std::max(a, b));
}

bool PointBelongsLine(Vector2f point, Line A, Line B) {
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

Vector2f Intersection(Line A, Line B) {
	float kA = (A.pointB.y - A.pointA.y) / (A.pointB.x - A.pointA.x);
	float kB = (B.pointB.y - B.pointA.y) / (B.pointB.x - B.pointA.x);
	if (kA == kB) {
		return Vector2f(-9999, -9999);
	}
	float bA = A.pointA.y - kA * A.pointA.x;
	float bB = B.pointA.y - kB * B.pointA.x;
	float xInter = (bB - bA) / (kA - kB);
	if (A.pointB.x == A.pointA.x) {
		xInter = A.pointA.x;
	}
	else if (B.pointB.x == B.pointA.x) {
		xInter = B.pointA.x;
	}
	float yInter = kA * xInter + bA;
	Vector2f result(xInter, yInter);
	if (PointBelongsLine(result, A, B)) {	
		return result;						
	}
	return Vector2f(-9999, -9999);			
}

float AngleOfIntersec(Line A, Line B) {
	Vector2f first, second;
	first.x = A.pointB.x - A.pointA.x;	//calculating vectors first and second from A and B lines
	first.y = A.pointB.y - A.pointA.y;	//
	second.x = B.pointB.x - B.pointA.x;	//
	second.y = B.pointB.y - B.pointA.y;	//

	float fMod = std::sqrt(first.x * first.x + first.y * first.y);		//vectors' modules
	float sMod = std::sqrt(second.x * second.x + second.y * second.y);	//

	return acos((first.x * second.x + first.y * second.y) / (fMod * sMod));	
}

//function checks point position relative to line (left or right)
bool isPointRight(Line line, Vector2f point) {
	float D = (point.x - line.pointA.x) * (line.pointB.y - line.pointA.y) - (point.y - line.pointA.y) * (line.pointB.x - line.pointA.x);
	if (D > 0) {
		return false;
	}
	return true;
}