#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <math.h>
#include <thread>
#include <chrono>
using namespace std;

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class Bullet
{
public:
	Sprite shape;

	Bullet(Texture* texture, float posx, float posy);
};
class Nave
{
public:
	int HP;
	Sprite shape;
	Texture* texture;
	vector<Bullet> bullets;

	Nave(Texture* texture);
};
class Meteoro
{
public:
	Sprite shape;

	int HP;
	int HPMax;

	Meteoro(Texture* texture, Vector2u windowSize);
};