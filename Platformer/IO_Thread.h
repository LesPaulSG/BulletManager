#pragma once
#include <mutex>

#include "BulletManager.h"

class VisualThread {
private:
	sf::RenderWindow window;
	BulletManager* bm;
	sf::Event evt;
	std::mutex mtxIO;
	sf::Vector2i LmbStartPos, RmbStartPos;				//mouse positions for firing
	sf::Vector2i LmbReleasedPos, RmbReleasedPos;
	bool* gameOver;
	std::chrono::duration<float>* pTime;
	std::chrono::duration<float> time;
	//std::chrono::ti
	sf::Font font;
	sf::Text uiText;

public:
	VisualThread(BulletManager* b, std::chrono::duration<float>* t, bool* gOver);
	~VisualThread();

	void Render();
	void Update();
	void CheckEvent();
	void MouseCheck();
	void KeyboardCheck();
};

void input(BulletManager* bm, std::chrono::duration<float>* t, bool* gameOver);

void CheckEvent(sf::Event* event, BulletManager* bm, float t);

void MouseCheck();

void KeyboardCheck(sf::Event* event, BulletManager* bm, float t);