#include "Line.h"

Line::Line(sf::Vector2f A, sf::Vector2f B) {
	pointA = (A.y >= B.y) ? A : B;
	pointB = (A.y >= B.y) ? B : A;
	midX = pointB.x - pointA.x;
	midY = pointB.y - pointA.y;
	midPoint.x = midX;
	midPoint.y = midY;
	lenght = sqrt(pow(midX, 2) + pow(midY, 2));
}

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

bool Line::CircleIntersection(const sf::Vector2f& circle, float radius, sf::Vector2f& iPoint) const {
	/*sf::Vector2f oc = pointA - circle;
	float b = pointA.x * pointB.x + pointA.y * pointB.y;
	float c = (pointA.x * pointA.x + pointA.y * pointA.y) - pow(radius, 2);
	float h = pow(b, 2) - c;
	if (h < 0.f) {
		return false;
	}
	h = sqrt(h);
	iPoint.x = -b - h;
	iPoint.y = -b + h;
	return true;*/
	double k = midY / midX;
	double b = pointA.y - k * pointA.x;
	//a = (1 + M ^ 2)
	double A = (1 + pow(k, 2));
	//� = 2 * (M � - � C.y - C.x)
	double B = 2 * (k * b - k * circle.y - circle.x);
	//c = (C.x ^ 2 + C.y ^ 2 + B ^ 2 - r ^ 2 - 2B * C.y)
	double C = (pow(circle.x, 2) + pow(circle.y, 2) + pow(b, 2) - pow(radius, 2) - 2 * (b * circle.y));
	double xInter1 = (B * -1 + sqrt(pow(B, 2) - 4 * A * C)) / (2 * A);
	double xInter2 = (B * -1 - sqrt(pow(B, 2) - 4 * A * C)) / (2 * A);
	double yInter1 = k * xInter1 + b;
	double yInter2 = k * xInter2 + b;
	sf::Vector2f result1(xInter1, yInter1);
	sf::Vector2f result2(xInter2, yInter2);
	//std::cout << "collision" << xInter1 << " " << yInter1 << '\n';
	if (HasPoint(result1) /*&& B.HasPoint(result)*/) {
		//std::cout << "collision res1" << std::endl;
		iPoint = result1;
		return true;
	} else if (HasPoint(result2)) {
		//std::cout << "collision res2" << std::endl;
		iPoint = result2;
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
