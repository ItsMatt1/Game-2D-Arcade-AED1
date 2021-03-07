#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

using namespace std;

// Principal
int main()
{
	//Janela
	sf::RenderWindow window(sf::VideoMode(800, 600), "Projeto AED1", sf::Style::Titlebar | sf::Style::Close);


	//Game Loop
	while (window.isOpen()) 
	{
		sf::Event eventPlayer;

		while (window.pollEvent(eventPlayer))
		{
			switch (eventPlayer.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (eventPlayer.key.code == sf::Keyboard::Escape)
					window.close();
				break;
			}
		}
	}

	//Update

	//Render

	//Limpa o Frame antigo
	window.clear(); 

	// Desenha na tela o jogo


	// Mostra na tela o que foi renderizado para a janela até agora
	window.display(); 

	//Fim do aplicativo
	return 0;
}