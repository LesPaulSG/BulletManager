#pragma once
#include <vector>
#include <queue>

#include "Bullet.h"
#include "Player.h"

enum class TaskType {
	ADD_BULLET,
	ADD_WALL,
	DELETE_BULLET,
	DELETE_WALL
};

struct AddWall {//: public PackagedTask {
	sf::Vector2f pos;
	sf::Vector2f dir;
	bool destructable;
};

struct AddBullet {//: public PackagedTask {
	sf::Vector2f pos;
	sf::Vector2f dir;
	float speed;
	float lifeTime;
};

struct DeleteBullet {//: public PackagedTask {
	//std::vector<Bullet>::iterator iter;
};

struct DeleteWall {//: public PackagedTask {
	//std::vector<Wall>::iterator iter;
};

union PackagedTask {
	AddBullet    ab;
	AddWall		 aw;
};

struct Task {
	TaskType type;
	PackagedTask pt;
};

class BulletManager {
private:
	std::vector<Bullet> bullets;
	std::vector<Wall> walls;

	std::queue<Task> tasks;

	mutable std::mutex bmMutex;

	//std::condition_variable cv;
	//bool processed = true;
	//bool updated = true;
	Player player;

public:
	std::vector<std::vector<Bullet>::iterator> bulletsToDelete;
	std::vector<std::vector<Wall>::iterator> wallsToDelete;

	BulletManager();
	~BulletManager() = default;

	const std::vector<Bullet>& GetBullets() const;
	const std::vector<Wall>& GetWalls() const;
	//bool GetProcessed();
	//bool GetUpdated();
	std::mutex& GetBmMutex();
	//std::condition_variable* GetCv();
	const Player& GetPlayer() const;

	void AddTask(Task& pt);
	void AddWall(Wall&& wall);
	void CreateWall(const sf::Vector2f& start, const sf::Vector2f& end, bool destructable = true);
	void Update(float time);
	void Fire(const sf::Vector2f& pos, const sf::Vector2f& dir, float speed, float lifeTime);
	void WallTrancform();
	//void SetProcessed(bool nP);
};
