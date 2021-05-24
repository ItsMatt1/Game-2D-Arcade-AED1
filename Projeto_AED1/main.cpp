#include "Game.h"

// Principal
int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Projeto AED1");
	window.setFramerateLimit(60);


	//Assets

	//Asteroid
	sf::Texture t1;
	t1.loadFromFile("Assets/Spaceship.png");

	sf::Sprite Asteroid(t1);

	Asteroid.setPosition(sf::Vector2f(384.f, 284.f));

	

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();

			}
		}

			
		//Limpar a janela
		window.clear(sf::Color::Black);

		//Desenhar
		window.draw(Asteroid);

		//Terminar o Frame
		window.display();

	}
	//Desenhar

	//window.clear();
	//window.display();

	//Fim do aplicativo
	return 0;
}