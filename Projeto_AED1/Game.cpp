#include "Game.h"

//Funções privadas
void Game::initVariables()
{
	this->window = nullptr;
}

void Game::initWindow()
{
	this->videoMode.width = 800;
	this->videoMode.height = 600;
	this->window = new sf::RenderWindow(this->videoMode, "Projeto AED1", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(60);
}

void Game::initEnemies()
{
	this->enemy.setPosition(400.f, 300.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setFillColor(sf::Color::Red);
	this->enemy.setOutlineThickness(1.f);
	this->enemy.setOutlineColor(sf::Color::Cyan);
}

//Construtores e Destrutores
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
}

//Acessores

const bool Game::running() const
{
	return this->window->isOpen();
}



//Funções
void Game::pollEvents()
{
	//Polling
	while (this->window->pollEvent(this->eventPlayer))
	{
		switch (this->eventPlayer.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->eventPlayer.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::updateMousePositions()
{
}

void Game::update()
{
	this->pollEvents();

	//Atualiza a posição do mouse
	//Relativo a tela
	//printf("%d %d\n", sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);

	//Relativo a janela
	printf("%d %d\n", sf::Mouse::getPosition(*this->window).x, sf::Mouse::getPosition(*this->window).y);
}


void Game::render()
{
	//Limpa
	this->window->clear();

	//Desenha
	this->window->draw(this->enemy);

	//Mostra
	this->window->display();
}


