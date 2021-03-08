#include "Game.h"

//Funções privadas
void Game::initVariables()
{
	this->window = nullptr;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "Projeto AED1", sf::Style::Titlebar | sf::Style::Close);
}

//Construtores e Destrutores
Game::Game()
{
	this->initVariables();
	this->initWindow();
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

void Game::update()
{
	this->pollEvents();
}


void Game::render()
{
	//Limpa
	this->window->clear(sf::Color(0,0,255,255));

	//Desenha


	//Mostra
	this->window->display();
}


