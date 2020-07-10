#pragma once
#include <SFML/System.hpp>
#include "BulletManager.h"

const int HEIGHT = VideoMode::getDesktopMode().height;
const int WIDTH = VideoMode::getDesktopMode().width;

void input(BulletManager*, std::chrono::duration<float>*, bool*);