#include "Game.h"

int a1 = 0, a2 = 800;
float b = 0;

	Meteoro::Meteoro(Texture* texture, Vector2u windowSize)
	{
		this->HPMax = rand() % 3 + 1; // ANTES
		this->HP = this->HPMax;

		this->shape.setOrigin(24.f, 24.f);
		this->shape.setTexture(*texture);
		this->shape.setScale(1.5f, 1.5f);
		srand(rand());
		this->shape.setPosition(rand() % a2 + a1, b);
	}

	Nave::Nave(Texture* texture)
	{
		this->HP = 1;
		this->texture = texture;
		this->shape.setTexture(*texture);

		this->shape.setScale(1.5f, 1.5f);
		this->shape.setPosition(Vector2f(384.f, 552.f));
	}

	Bullet::Bullet(Texture* texture, float posx, float posy)
	{
		this->shape.setTexture(*texture);
		this->shape.setScale(2.0f, 2.0f);
		this->shape.setPosition(posx, posy);
	}