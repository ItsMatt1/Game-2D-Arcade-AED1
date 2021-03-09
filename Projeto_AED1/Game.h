#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

/*
	Classe empacotadora que age como a Game Engine
*/
class Game
{
private:
	//Variáveis
	//Janela
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event eventPlayer;

	//Game Objects

	sf::RectangleShape enemy;

	//Funcões Privadas.
	void initVariables();
	void initWindow();
	void initEnimies();
public:

	//Construtores e Destruidores 

	Game();
	virtual ~Game();

	//Acessores

	const bool running() const;

	//Funçoes

	void pollEvents();
	void update();
	void render();
};

