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

#define itens 3

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

class Menu
{
public:
	Menu(float x, float y);
	~Menu();

	void draw(RenderWindow& window);
	void MoveUp();
	void MoveDown();

	int getPressedItem() { return selectedItem; }

private:
	int selectedItem;
	Font font;
	Text menu[itens];
};