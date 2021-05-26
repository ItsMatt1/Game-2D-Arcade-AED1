#include "Game.h"

// Principal
int main()
{
	//Janela

	RenderWindow window(VideoMode(800, 600), "Meteoro", Style::Titlebar | Style::Close);
	window.setFramerateLimit(60);

	Clock deltaClock;

	//** Assets

	//** Nave
	Texture ship_tex;
	ship_tex.loadFromFile("Assets/Spaceship.png");

	Sprite nave(ship_tex);

	//Configuraçoes da nave.
	nave.setPosition(Vector2f(384.f, 552.f));
	nave.setScale(1.5f, 1.5f);

	//** Tiro
	Texture tiro_tex;
	tiro_tex.loadFromFile("Assets/bullet.png");

	Sprite tiro(tiro_tex);

	//** Asteroide
	Texture ast_tex;
	ast_tex.loadFromFile("Assets/Asteroid.png");

	Sprite asteroide(ast_tex);
	asteroide.setScale(1.5f, 1.5f);

	//Posicao do asteroide.
	srand(time(0));
	asteroide.setOrigin(24.f, 24.f);
	asteroide.setPosition(((rand() % 640) + 1), -(rand() % 600));

	//** Background
	Texture bg_tex;
	bg_tex.loadFromFile("Assets/Background.png");

	//** Visão do mapa

	View View(window.getDefaultView());
	FloatRect fBounds(0.f, 0.f, 3200.f, 2400.f);
	IntRect	iBounds(fBounds);
	bg_tex.setRepeated(true);

	//** Sprite do Background
	Sprite bg(bg_tex, iBounds);

	//** Limites da Visão
	const sf::Vector2f viewStart(fBounds.left + (fBounds.width / 2), fBounds.top + (fBounds.height / 2));
	const sf::Vector2f spriteStart(fBounds.left, fBounds.top);

	//** Enquanto Janela está aberta
	while (window.isOpen())
	{
		Event evento;

		Time dt = deltaClock.restart();

		//** Velocidades 

		float Ast_Velocity = (10.f) * dt.asSeconds();

		float Ship_Velocity_Right = (200.f - 50.f) * dt.asSeconds();
		float Ship_Velocity_Left = (200.f + 50.f) * dt.asSeconds();

		
		//** Movimentação do Asteroide

		asteroide.move(-50.f * dt.asSeconds(), Ast_Velocity);

		asteroide.rotate(2.f);

		//** Movimento involuntário da nave
		if (!(Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::W)
			|| Keyboard::isKeyPressed(Keyboard::S)))
		{
			nave.move(-50.f * dt.asSeconds(), -50.f * dt.asSeconds());
		}

		//** Movimentos do tiro
		if (!Keyboard::isKeyPressed(Keyboard::Space))
		{
			tiro.move(-50.f * dt.asSeconds(), -50.f * dt.asSeconds());
		}

		if (Keyboard::isKeyPressed(Keyboard::Key::Space))
		{	
			tiro.setPosition(nave.getPosition().x + 17.f, nave.getPosition().y + -17.f);
			tiro.setScale(2.0f, 2.0f);

		}

		//** Movimentos de controle da nave

		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			nave.move(-Ship_Velocity_Left, -50.f * dt.asSeconds());
		}

		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			nave.move(Ship_Velocity_Right, -50.f * dt.asSeconds());
		}

		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			nave.move(-50.f * dt.asSeconds(), -Ship_Velocity_Left);
		}

		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			nave.move(-50.f * dt.asSeconds(), Ship_Velocity_Right);
		}


		if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::S))
		{
			nave.move(-Ship_Velocity_Left * 0.00005, Ship_Velocity_Right * 0.00005);
			cout << "LEFT - DOWN" << endl;
		}
		else if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::W))
		{
			nave.move(-Ship_Velocity_Left * 0.05, -Ship_Velocity_Left * 0.05);
			cout << "LEFT - UP" << endl;
		}

		else if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::S))
		{
			nave.move(Ship_Velocity_Right * 0.2, Ship_Velocity_Right * 0.2);
			cout << "RIGHT - DOWN" << endl;
		}
		else if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::W))
		{
			nave.move(Ship_Velocity_Right * 0.3, -Ship_Velocity_Left * 0.05);
			cout << "RIGHT - UP" << endl;
		}


		//** Polling Eventos

		while (window.pollEvent(evento))
		{
			switch (evento.type)
			{
			case Event::Closed:
				{
					window.close();
					break;
				}
			}
		}

		//** Configurações da Visão 

		View.move(-50.f * dt.asSeconds(), -50.f * dt.asSeconds()); // just move the view here in any direction-the tiles will follow automatically
		const sf::Vector2f viewOffset(viewStart - View.getCenter());
		sf::Vector2f spriteOffset;
		spriteOffset.x = floor(viewOffset.x / bg_tex.getSize().x) * bg_tex.getSize().x;
		spriteOffset.y = floor(viewOffset.y / bg_tex.getSize().y) * bg_tex.getSize().y;
		bg.setPosition(spriteStart - spriteOffset);

			
		//** Limpar a janela
		window.clear(Color::Black);
		window.setView(View);

		//** Desenhar
		window.draw(bg);
		window.draw(nave);
		window.draw(tiro);
		window.draw(asteroide);

		//** Terminar o Frame
		window.display();
	}

	//** Fim do aplicativo
	return 0;
}