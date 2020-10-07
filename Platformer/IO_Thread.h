#pragma once
#include <SFML/System.hpp>

#include "BulletManager.h"

const int HEIGHT = sf::VideoMode::getDesktopMode().height;
const int WIDTH = sf::VideoMode::getDesktopMode().width;

void input(BulletManager* bm, std::chrono::duration<float>* t, bool* gameOver);