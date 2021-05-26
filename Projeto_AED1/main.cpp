#include "Game.h"

class Bullet
{
public:
	Sprite shape;

	Bullet(Texture *texture, float posx, float posy)
	{
		this->shape.setTexture(*texture);
		this->shape.setScale(2.0f, 2.0f);
		this->shape.setPosition(posx, posy);
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
	Sprite shape;

	int HP;
	int HPMax;

	Meteoro(Texture* texture, Vector2u windowSize)
	{
		this->HPMax = rand() % 3 + 1;
		this->HP = this->HPMax;

		this->shape.setOrigin(24.f, 24.f);
		this->shape.setTexture(*texture);
		this->shape.setScale(1.5f, 1.5f);
		this->shape.setPosition(windowSize.y - this->shape.getGlobalBounds().height, rand()% windowSize.x - this->shape.getGlobalBounds().width);
	}

	~Meteoro(){}
};


// Principal
int main()
{
	//srand(time(NULL));
	 
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
	int shootTimer = 20;

	//Iniciando inimigo
	int enemySpawnTimer = 0;
	vector<Meteoro> enemies;
	enemies.push_back(Meteoro(&enemyTex, window.getSize()));

	// Vis�o do mapa
	View View(window.getDefaultView());
	FloatRect fBounds(0.f, 0.f, 3200.f, 2400.f);
	IntRect	iBounds(fBounds);
	background_tex.setRepeated(true);

	// Sprite do Background
	Sprite background(background_tex, iBounds);

	// Limites da Vis�o
	const Vector2f viewStart(fBounds.left + (fBounds.width / 2), fBounds.top + (fBounds.height / 2));
	const Vector2f spriteStart(fBounds.left, fBounds.top);

	int tiroForaDaTela = 0, meteoroForaDaTela = 673;

	// Enquanto Janela est� aberta
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
	
		// corre��o do movimento involunt�rio da nave
		player.shape.move(-50.f * dt.asSeconds(), -50.f * dt.asSeconds());

		//Corre��o do movimento involuntario do asteroide e adicionando rota��o
		for (size_t i = 0; i < enemies.size(); i++)
		{
			enemies[i].shape.move(-50.f * dt.asSeconds(), -50.f * dt.asSeconds());
			enemies[i].shape.rotate(2.f);
		}

		//Player
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			player.shape.move(0.f, -5.f);
		}
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			player.shape.move(-5.f, 0.f);
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			player.shape.move(0.f, 5.f);
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			player.shape.move(5.f, 0.f);
		}

		// Colis�o com a janela 
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
		
		// Atirando

		if (shootTimer < 20)
		{
			shootTimer++;
		}
		if (Keyboard::isKeyPressed(Keyboard::Space) && shootTimer >=20)
		{
			player.bullets.push_back(Bullet(&bulletTex, player.shape.getPosition().x + 17.f, player.shape.getPosition().y - 17.f));
			shootTimer = 0; //resetar cooldows bala
		}

		// Bullets

		// Fora da tela
		for (size_t i = 0; i < player.bullets.size(); i++)
		{
			player.bullets[i].shape.move(0.f + -50.f * dt.asSeconds(), -15.f+ -50.f * dt.asSeconds());

			if (player.bullets[i].shape.getPosition().y < tiroForaDaTela)
			{
				player.bullets.erase(player.bullets.begin() + i);
			}
		}
		tiroForaDaTela--;

		//Inimigos
		/*
		if (enemySpawnTimer < 20)
		{
			enemySpawnTimer++;
		}
		if (enemySpawnTimer >= 20)
		{
			enemies.push_back(Meteoro(&enemyTex, window.getSize()));
			enemySpawnTimer = 0; //respawn cooldown 
		}*/
		for (size_t i = 0; i < enemies.size(); i++)
		{
			//Movimenta��o dos inimigos
			enemies[i].shape.move(0.f, 2.f);

			//Apaga inimigos fora da tela
			if (enemies[i].shape.getPosition().y > meteoroForaDaTela)
			{
				enemies.erase(enemies.begin() + i);
			}
			// Colis�o com inimigos
			if (enemies[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
			{
				enemies.erase(enemies.begin() + i);
				player.shape.setColor(Color(0,0,0,0));
			}
		}
		meteoroForaDaTela--;

		// Configura��es da Vis�o 
		
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
		for (size_t i = 0; i < enemies.size(); i++)
		{
			window.draw(enemies[i].shape);
		}

		// Terminar o Frame
		window.display();
	}

	// Fim do aplicativo
	return 0;
}