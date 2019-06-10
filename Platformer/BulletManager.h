#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

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

///////////// Wall //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Wall {
private:
	bool destructable_;
	RectangleShape body_;
	Vector2f vector_;
	//float height_;
	//float width;

public:
	Vector2f pointA, pointB;

	RectangleShape GetBody();
	void CalculateVector();
	void CalculateRotation();
	Wall();
	Wall(Vector2f, Vector2f);
	Wall(Vector2f, Vector2f, bool);
	~Wall();
};

///////////// Bullet ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Bullet {
private:
	CircleShape body_;
	float speed_;
	float time_;
	float lifeTime_;
	Vector2f pos_;
	Vector2f dir_;
	bool alive_;

public:
	void Update(float, std::vector<Wall>*);
	CircleShape GetBody();
	float GetRadius();
	float GetSpeed();
	float GetTime();
	float GetLifeTime();
	Vector2f GetPos();
	Vector2f GetGetDir();
	bool GetAlive();
	void ChangeDirection(float, bool);

	//void SetRadius();
	//void SetSpeed();
	//void SetTime();
	//void SetLifeTime();
	//void SetPos();
	//void SetDir();

	Bullet(Vector2f, Vector2f, float, float);
	~Bullet();
};

///////////// BulletManager /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class BulletManager {
private:
	std::vector<Bullet> bullets_;
	std::vector<Wall> walls_;
public:
	BulletManager();

	std::vector<Bullet>* GetBullets();
	std::vector<Wall>* GetWalls();
	void AddBullet(Bullet*);
	void RemoveBullet(std::vector<Bullet>::iterator);
	int GetBulletsQuntity();
	void AddWall(Wall*);
	void RemoveWall(std::vector<Wall>::iterator);
	int GetWallsQuntity();
	void Update(float);
	void Fire(Vector2f, Vector2f, float, float);

	~BulletManager();
};
