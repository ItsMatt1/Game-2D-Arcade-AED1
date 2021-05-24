#include "Game.h"

// Principal
int main()
{
	RenderWindow window(VideoMode(800, 600), "Projeto AED1", Style::Titlebar | Style::Close);
	window.setFramerateLimit(60);

	//Assets

	//Nave
	Texture textura1;
	textura1.loadFromFile("Assets/Spaceship.png");

	Sprite nave(textura1);

	nave.setPosition(Vector2f(384.f, 284.f));

	//Background
	Texture textura2;
	textura2.loadFromFile("Assets/Background.png");

	Sprite bg(textura2);


	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();

			}

			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				// left key is pressed: move our character
				nave.move(-5.f, 0.f);
			}

			if (Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				// left key is pressed: move our character
				nave.move(5.f, 0.f);
			}
		}

			
		//Limpar a janela
		window.clear(Color::Black);

		//Desenhar
		window.draw(bg);
		window.draw(nave);

		//Terminar o Frame
		window.display();

	}

	//Fim do aplicativo
	return 0;
}