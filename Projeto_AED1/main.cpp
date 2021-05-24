#include "Game.h"

// Principal
int main()
{
	RenderWindow window(VideoMode(800, 600), "Projeto AED1", Style::Titlebar | Style::Close);
	window.setFramerateLimit(60);
	


	//Assets

	//Asteroid
	Texture textura1;
	textura1.loadFromFile("Assets/Spaceship.png");

	Sprite nave(textura1);

	nave.setPosition(Vector2f(384.f, 284.f));

	

	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();

			}
		}

			
		//Limpar a janela
		window.clear(Color::Black);

		//Desenhar
		window.draw(nave);

		//Terminar o Frame
		window.display();

	}
	//Desenhar

	//window.clear();
	//window.display();

	//Fim do aplicativo
	return 0;
}