#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

const int BULLETS_MAX_CAPACITY = 10;
const int WALLS_MAX_CAPACITY = 50;

//helper class
class Line {
public:
	Vector2f pointA;
	Vector2f pointB;

	Line(Vector2f, Vector2f);
	~Line();
};

float LenghtOfLine(Vector2f, Vector2f);

bool isPointBeetwenPoints(float, float, float);

bool PointBelongsLine(Vector2f, Line, Line);

Vector2f Intersection(Line, Line);

float AngleOfIntersec(Line, Line);

bool isPointRight(Line, Vector2f);

void FormatText(Text*);