#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

/*
	Classe empacotadora que age como a Game Engine
*/
class Game
{
	


private:



public:



};

class Bullet
{
public:
	Bullet(Vector2f size)
	{
		bullet.setSize(size);
	}

	void fire(int speed)
	{
		bullet.move(speed, 0);
	}

	int getRight() {
		return bullet.getPosition().x + bullet.getSize().x;
	}

	int getLeft() {
		return bullet.getPosition().x;
	}

	int getTop() {
		return bullet.getPosition().y;
	}

	int getBottom() {
		return bullet.getPosition().y + bullet.getSize().y;
	}
private:
	RectangleShape bullet;

};

class Enemy {
public:
	Enemy(Vector2f size) {
		enemy.setSize(size);
	}

	void setPos(Vector2f newPos) {
		enemy.setPosition(newPos);
	}

	void checkCollision(Bullet bullet) {
		if (bullet.getRight() > enemy.getPosition().x &&
			bullet.getTop() < enemy.getPosition().y + enemy.getSize().y
			&& bullet.getBottom() > enemy.getPosition().y) {
			enemy.setPosition(Vector2f(4234432, 4234423));
		}
	}

	void draw(sf::RenderWindow &window) {
		window.draw(enemy);
	}
private:
	RectangleShape enemy;
};

