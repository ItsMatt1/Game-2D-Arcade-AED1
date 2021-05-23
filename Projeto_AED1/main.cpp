#include "Game.h"

// Principal
int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "Projeto AED1");
	window.setFramerateLimit(60);

	sf::Texture t1;
	//t1.loadFromFile("image/spaceship.png");

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

		//Terminar o Frame
		window.display();

	}

	


	//Desenhar

	//window.clear();
	//window.display();

	//Fim do aplicativo
	return 0;
}