#include "Game.h"

//Funções privadas
void Game::initVariables()
{
	this->window = nullptr;


	//Game logic

	this->points = 0;
	this->enemySpawnTimerMax = 1000.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;

	this->maxEnemies = 5;
}

//Configuração da janela
void Game::initWindow()
{
	this->videoMode.width = 800;
	this->videoMode.height = 600;
	this->window = new sf::RenderWindow(this->videoMode, "Projeto AED1", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(60);
}

//Configuração do inimigo
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

void Game::spawnEnemies()
{
	/*
	Nasce os inimigos e define a cor e posiçoes
	*/

	this->enemy.setPosition
	(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		(0.f)
	);

	this->enemy.setFillColor(sf::Color::Red);

	//Spawn
	this->enemies.push_back(this->enemy);

	//Remove os inimigos no fim da tela


}
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
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
}

void Game::updateEnemies()
{
	/*
	Atualiza o timer do nascer de inimigos e nasce inimigos
	quando o total de inimigos é menor que o maximo
	Move o inimigo
	*/

	//Atualizando o timer para o inimigo nascer

	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			//Nasce o inimigo e reseta o timer
			this->spawnEnemies();
			this->enemySpawnTimer = 0.f;
		}
		else
		{
			this->enemySpawnTimer += 1.f;
		}
	}
	
	//Move o inimigo
	for (auto &e : this->enemies)
	{
		e.move(0.f, 1.f);
	}

}

//Todos os updates

void Game::update()
{
	this->pollEvents();

	this->updateMousePositions();

	this->updateEnemies();
}

void Game::renderEnemies()
{
	//Renderizando o inimigo
	for (auto& e : this->enemies)
	{
		this->window->draw(e);
	}
}


void Game::render()
{
	//Limpa
	this->window->clear();

	//Desenha
	//this->window->draw(this->enemy);
	this->renderEnemies();

	//Mostra
	this->window->display();
}


