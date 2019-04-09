#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

///////////// Wall //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Wall {
private:
	bool destructable_;
	RectangleShape body_;
	Vector2f pos_;
	float height_;
	float width;

public:
	RectangleShape GetBody();

	Wall();
	Wall(Vector2f, Vector2f, float);
	Wall(Vector2f, Vector2f, float, bool);
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

class BulletManager{
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
