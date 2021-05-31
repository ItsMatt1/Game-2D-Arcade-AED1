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
	this->shape.setPosition(Vector2f(376.f, 552.f));
}

Bullet::Bullet(Texture* texture, float posx, float posy)
{
	this->shape.setTexture(*texture);
	this->shape.setScale(2.0f, 2.0f);
	this->shape.setPosition(posx, posy);
}

Menu::Menu(float x, float y)
{
	if (!font.loadFromFile("Assets/upheavtt.ttf"))
	{
		//error
	}
	menu[0].setFont(font);
	menu[0].setFillColor(Color::Red);
	menu[0].setString("Play");
	menu[0].setPosition(Vector2f((x / 2) - 37, y / (itens + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(Color::White);
	menu[1].setString("Controls");
	menu[1].setPosition(Vector2f((x / 2) - 74, y / (itens + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(Color::White);
	menu[2].setString("Exit");
	menu[2].setPosition(Vector2f((x / 2) - 38, y / (itens + 1) * 3));

	selectedItem = 0;
}

Menu::~Menu()
{
}

void Menu::draw(RenderWindow& window)
{
	for (int i = 0; i < itens; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::MoveUp()
{
	if (selectedItem - 1 >= 0)
	{
		menu[selectedItem].setFillColor(Color::White);
		selectedItem--;
		menu[selectedItem].setFillColor(Color::Red);
	}
}

void Menu::MoveDown()
{
	if (selectedItem + 1 < itens)
	{
		menu[selectedItem].setFillColor(Color::White);
		selectedItem++;
		menu[selectedItem].setFillColor(Color::Red);
	}
}