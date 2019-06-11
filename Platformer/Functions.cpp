#include <SFML/Graphics.hpp>
#include <iostream>
#include "BulletManager.h"
#include "Bullet.h"
#include "Wall.h"
#include "Definitions.h"

bool PointBelongsLine(Vector2f point, Line A, Line B) {
	if (!(point.x >= std::min(A.pointA.x, A.pointB.x) && point.x <= std::max(A.pointA.x, A.pointB.x))) {
		//std::cout << "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111" << std::endl;
		return false;
	}
	if (!(point.x >= std::min(B.pointA.x, B.pointB.x) && point.x <= std::max(B.pointA.x, B.pointB.x))) {
		//std::cout << "2222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222" << std::endl;
		return false;
	}
	if (!(point.y >= std::min(A.pointA.y, A.pointB.y) && point.y <= std::max(A.pointA.y, A.pointB.y))) {
		//std::cout << "3333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333" << std::endl;
		return false;
	}
	if (!(point.y >= std::min(B.pointA.y, B.pointB.y) && point.y <= std::max(B.pointA.y, B.pointB.y))) {
		//std::cout << "4444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444" << std::endl;
		return false;
	}
	return true;
}

Vector2f Intersection(Line A, Line B) {
	float kA = (A.pointB.y - A.pointA.y) / (A.pointB.x - A.pointA.x);
	float kB = (B.pointB.y - B.pointA.y) / (B.pointB.x - B.pointA.x);
	if (kA == kB) { // || kA == 0 || kB == 0
		return Vector2f(-9999, -9999);
	}
	float bA = A.pointA.y - kA * A.pointA.x;
	//(A.pointB.x * A.pointA.y - A.pointA.x * A.pointB.y) / (A.pointB.x - A.pointA.x);
	float bB = B.pointA.y - kB * B.pointA.x;
	//(B.pointB.x * B.pointA.y - B.pointA.x * B.pointB.y) / (B.pointB.x - B.pointA.x);
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
	first.x = A.pointB.x - A.pointA.x;
	first.y = A.pointB.y - A.pointA.y;
	second.x = B.pointB.x - B.pointA.x;
	second.y = B.pointB.y - B.pointA.y;
	std::cout << first.x << " " << first.y << " | " << second.x << " " << second.y << std::endl;
	float fMod = std::sqrt(first.x * first.x + first.y * first.y);
	float sMod = std::sqrt(second.x * second.x + second.y * second.y);
	return acos((first.x * second.x + first.y * second.y) / (fMod * sMod));
	//return angRad *= (180 / 3.14);
}

bool isPointRight(Line line, Vector2f point) {
	float D = (point.x - line.pointA.x) * (line.pointB.y - line.pointA.y) - (point.y - line.pointA.y) * (line.pointB.x - line.pointA.x);
	if (D > 0) {
		return false;
	}
	return true;
}

///////////// Line //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Line::Line() {

}

Line::Line(Vector2f A, Vector2f B) : pointA(A), pointB(B) {

}

Line::~Line() {

}
