#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Line {
public:
	Vector2f pointA;
	Vector2f pointB;
	Line();
	Line(Vector2f, Vector2f);
	~Line();
};

bool PointBelongsLine(Vector2f, Line, Line);

Vector2f Intersection(Line, Line);

float AngleOfIntersec(Line, Line);

bool isPointRight(Line, Vector2f);