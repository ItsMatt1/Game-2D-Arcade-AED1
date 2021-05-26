#include "Game.h"

class Bullet
{
public:
	Sprite shape;

	Bullet(Texture *texture, Vector2f pos)
	{
		this->shape.setTexture(*texture);
		this->shape.setScale(2.0f, 2.0f);
		this->shape.setPosition(pos);
	}
};

class Nave
{
public:
	Sprite shape;
	Texture *texture;

	vector<Bullet> bullets;

	Nave(Texture* texture)
	{
		this->texture = texture;
		this->shape.setTexture(*texture);

		this->shape.setScale(1.5f, 1.5f);
		this->shape.setPosition(Vector2f(384.f, 552.f));

	}
};

class Meteoro
{
public:
};


// Principal
int main()
{
	// Janela

	RenderWindow window(VideoMode(800, 600), "Meteoro", Style::Titlebar | Style::Close);
	window.setFramerateLimit(60);

	Clock deltaClock;

	// Iniciando texturas
	Texture playerTex;
	playerTex.loadFromFile("Assets/Spaceship.png");

	Texture enemyTex;
	enemyTex.loadFromFile("Assets/Asteroid.png");

	Texture bulletTex;
	bulletTex.loadFromFile("Assets/bullet.png");

	Texture background_tex;
	background_tex.loadFromFile("Assets/Background.png");

	// Iniciando jogador
	Nave player(&playerTex);

	// Visão do mapa

	View View(window.getDefaultView());
	FloatRect fBounds(0.f, 0.f, 3200.f, 2400.f);
	IntRect	iBounds(fBounds);
	background_tex.setRepeated(true);

	// Sprite do Background
	Sprite background(background_tex, iBounds);

	// Limites da Visão
	const Vector2f viewStart(fBounds.left + (fBounds.width / 2), fBounds.top + (fBounds.height / 2));
	const Vector2f spriteStart(fBounds.left, fBounds.top);
	

	// Enquanto Janela está aberta
	while (window.isOpen())
	{
		Event evento;

		Time dt = deltaClock.restart();

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
		// Movimento involuntário da nave
		if (!(Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::W)
			|| Keyboard::isKeyPressed(Keyboard::S)))
		{
			player.shape.move(-50.f * dt.asSeconds(), -50.f * dt.asSeconds());
		}

		//Player
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			player.shape.move(0.f + -50.f * dt.asSeconds(), -5.f + -50.f * dt.asSeconds());
		}
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			player.shape.move(-5.f + -50.f * dt.asSeconds(), 0.f + -50.f * dt.asSeconds());
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			player.shape.move(0.f + -50.f * dt.asSeconds(), 5.f + -50.f * dt.asSeconds());
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			player.shape.move(5.f + -50.f * dt.asSeconds(), 0.f + -50.f * dt.asSeconds());
		}

		// Colisão com a janela 
		//nao funciona devido ao efeito paralaxe

		/*
		if (player.shape.getPosition().x <= 0) //esquerda
			player.shape.setPosition(0.f, player.shape.getPosition().y);
		if (player.shape.getPosition().x >= window.getSize().x - -player.shape.getGlobalBounds().width) //direita
			player.shape.setPosition(window.getSize().x - player.shape.getGlobalBounds().width, player.shape.getPosition().y);
		if (player.shape.getPosition().y <= 0) //cima
			player.shape.setPosition(player.shape.getPosition().x, 0.f);
		if (player.shape.getPosition().y >= window.getSize().y - player.shape.getGlobalBounds().height) //baixo
			player.shape.setPosition(player.shape.getPosition().x, window.getSize().y - player.shape.getGlobalBounds().height);
		*/
		

		// Update
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			player.bullets.push_back(Bullet(&bulletTex, player.shape.getPosition()));
		}

		// Bullets
		// Fora da tela
		for (size_t i = 0; i < player.bullets.size(); i++)
		{
			if (player.bullets[i].shape.getPosition().x > window.getSize().x)
			{
				player.bullets.erase(player.bullets.begin() + i);
			}
		}
		// Colisão com inimigos


		// Configurações da Visão 
		
		View.move(-50.f * dt.asSeconds(), -50.f * dt.asSeconds()); // just move the view here in any direction-the tiles will follow automatically
		const Vector2f viewOffset(viewStart - View.getCenter());
		Vector2f spriteOffset;
		spriteOffset.x = floor(viewOffset.x / background_tex.getSize().x) * background_tex.getSize().x;
		spriteOffset.y = floor(viewOffset.y / background_tex.getSize().y) * background_tex.getSize().y;
		background.setPosition(spriteStart - spriteOffset);
		

			
		// Limpar a janela
		window.clear(Color::Black);
		window.setView(View);

		// Desenhar
		window.draw(background);
		window.draw(player.shape);
		for (size_t i = 0; i < player.bullets.size(); i++)
		{
			window.draw(player.bullets[i].shape);
		}
		
	


		// Terminar o Frame
		window.display();
	}

	// Fim do aplicativo
	return 0;
}