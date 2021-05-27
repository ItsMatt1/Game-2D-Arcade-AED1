#include "Game.h"

int tiroForaDaTela = 0, meteoroForaDaTela = 700;
float b = 0, xmin = 0, xmax = 800, ymin = 0, ymax = 600;
int a1 = 0, a2 = 800;
bool gameOver = false;

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
	int HP;
	Sprite shape;
	Texture *texture;
	vector<Bullet> bullets;

	Nave(Texture* texture)
	{
		this->HP = 1;
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
		this->HPMax = rand () % 3 + 1; // ANTES
		//this->HPMax = 1;  DEPOIS
		this->HP = this->HPMax;

		this->shape.setOrigin(24.f, 24.f);
		this->shape.setTexture(*texture);
		this->shape.setScale(1.5f, 1.5f);
		srand(rand());
		this->shape.setPosition(rand() % a2 + a1,b);
		b -= 50.f;
		a1 -= 17;
	}

	~Meteoro(){}
};

// Principal
int main()
{
	 
	// Janela
	RenderWindow window(VideoMode(800, 600), "Meteoro", Style::Titlebar | Style::Close);
	window.setFramerateLimit(60);

	Clock deltaClock;
	Font font;
	font.loadFromFile("Assets/upheavtt.ttf");
	
	// Iniciando texturas
	Texture playerTex;
	playerTex.loadFromFile("Assets/Spaceship.png");

	Texture enemyTex;
	enemyTex.loadFromFile("Assets/Asteroid.png");

	Texture bulletTex;
	bulletTex.loadFromFile("Assets/bullet.png");

	Texture background_tex;
	background_tex.loadFromFile("Assets/Background.png");

	//Iniciando UI
	Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(25);
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(7.f, 7.f);

	Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(40);
	gameOverText.setFillColor(Color::Red);
	gameOverText.setPosition(290.f, 0.f);
	gameOverText.setString("GAME OVER!");

	Text pauseText;
	pauseText.setFont(font);
	pauseText.setCharacterSize(40);
	pauseText.setFillColor(Color::Yellow);
	pauseText.setPosition(290.f, 0.f);
	pauseText.setString("PAUSED");

	// Iniciando jogador
	int score = 0;
	Nave player(&playerTex);
	int shootTimer = 20;

	//Iniciando inimigo
	int enemySpawnTimer = 0;
	vector<Meteoro> enemies;
	//enemies.push_back(Meteoro(&enemyTex, window.getSize()));

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

	// Musica
	Music music;
	if (!music.openFromFile("OST/LOL.ogg"))
		return -1; 

	music.play();
	music.setLoop(true);	

	// Som
	SoundBuffer buffer;
	if (!buffer.loadFromFile("OST/Bullet2.wav"))
		return -1;

	Sound bullet_sound;
	bullet_sound.setBuffer(buffer);
	bullet_sound.setVolume(50.f);


	// som game over
	SoundBuffer buffer2;
	if (!buffer2.loadFromFile("OST/GameOver.wav"))
		return -1;

	Sound sound2;
	sound2.setBuffer(buffer2);
	sound2.setVolume(40.f);


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
		if (player.HP > 0)
		{
			// correção do movimento involuntário da nave/score/gameover
			player.shape.move(-50.f * dt.asSeconds(), -50.f * dt.asSeconds());
			scoreText.move(-50.f * dt.asSeconds(), -50.f * dt.asSeconds());
			gameOverText.move(-50.f * dt.asSeconds(), -50.f * dt.asSeconds());
			pauseText.move(-50.f * dt.asSeconds(), -50.f * dt.asSeconds());

			//Correção do movimento involuntario do asteroide e adicionando rotação
			for (size_t i = 0; i < enemies.size(); i++)
			{
				enemies[i].shape.move(-50.f * dt.asSeconds(), -50.f * dt.asSeconds());
				enemies[i].shape.rotate(2.f);
			}

			//Player
			if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up))
			{
				player.shape.move(0.f, -5.f);
			}
			if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left))
			{
				player.shape.move(-5.f, 0.f);
			}
			if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down))
			{
				player.shape.move(0.f, 5.f);
			}
			if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right))
			{
				player.shape.move(5.f, 0.f);
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

			/*
			if (player.shape.getPosition().x <= xmin * dt.asSeconds())
			{
				player.shape.setPosition(xmin + (1 * dt.asSeconds()), player.shape.getPosition().y);
			}
			if (player.shape.getPosition().x >= xmax * dt.asSeconds())
			{
				player.shape.setPosition(xmax - (1 * dt.asSeconds()), player.shape.getPosition().y);
			}
			if (player.shape.getPosition().y <= ymin * dt.asSeconds())
			{
				player.shape.setPosition(player.shape.getPosition().x, ymin + (1 * dt.asSeconds()));
			}
			if (player.shape.getPosition().y >= ymax * dt.asSeconds())
			{
				player.shape.setPosition(player.shape.getPosition().x, ymin - (1 * dt.asSeconds()));
			}

			xmin -= 50 * dt.asSeconds();
			xmax -= 50 * dt.asSeconds();
			ymin -= 50 * dt.asSeconds();
			ymax -= 50 * dt.asSeconds();
			*/

			// Atirando
			if (shootTimer < 20)
			{
				shootTimer++;
			}
			if (Keyboard::isKeyPressed(Keyboard::Space) && shootTimer >= 20)
			{
				bullet_sound.play();
				player.bullets.push_back(Bullet(&bulletTex, player.shape.getPosition().x + 17.f, player.shape.getPosition().y - 17.f));
				shootTimer = 0; //resetar cooldows bala
			}

			// Bullets
			for (size_t i = 0; i < player.bullets.size(); i++)
			{
				player.bullets[i].shape.move(0.f + -50.f * dt.asSeconds(), -15.f + -50.f * dt.asSeconds());

				// Se o tiro for pra fora da tela
				if (player.bullets[i].shape.getPosition().y < tiroForaDaTela)
				{
					player.bullets.erase(player.bullets.begin() + i);
					break;
				}

				//Se o tiro acertar o inimigo
				for (size_t k = 0; k < enemies.size(); k++)
				{
					if (player.bullets[i].shape.getGlobalBounds().intersects(enemies[k].shape.getGlobalBounds()))
					{
						if (enemies[k].HP <= 1)
						{
							score += enemies[k].HPMax;
							enemies.erase(enemies.begin() + k);
						}
						else
						{
							enemies[k].HP--; //Inimigo toma dano
						}
						player.bullets.erase(player.bullets.begin() + i);
						break;
					}
				}
			}
			tiroForaDaTela--;

			//Inimigos

			if (enemySpawnTimer < 20)
			{
				enemySpawnTimer++;
			}
			if (enemySpawnTimer >= 20)
			{
				enemies.push_back(Meteoro(&enemyTex, window.getSize()));
				enemySpawnTimer = 0; //respawn cooldown 
			}
			for (size_t i = 0; i < enemies.size(); i++)
			{
				//Movimentação dos inimigos
				enemies[i].shape.move(0.f, 5.f);

				//Apaga inimigos fora da tela
				if (enemies[i].shape.getPosition().y > meteoroForaDaTela)
				{
					enemies.erase(enemies.begin() + i);
				}
				// Colisão com inimigos
				if (enemies[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
				{
					enemies.erase(enemies.begin() + i);
					player.HP--; //player leva dano
					break;
				}
			}
			meteoroForaDaTela -= dt.asSeconds() / 2;

			// Configurações da Visão 

			View.move(-50.f * dt.asSeconds(), -50.f * dt.asSeconds()); // just move the view here in any direction-the tiles will follow automatically
			const Vector2f viewOffset(viewStart - View.getCenter());
			Vector2f spriteOffset;
			spriteOffset.x = floor(viewOffset.x / background_tex.getSize().x) * background_tex.getSize().x;
			spriteOffset.y = floor(viewOffset.y / background_tex.getSize().y) * background_tex.getSize().y;
			background.setPosition(spriteStart - spriteOffset);
		}
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
		scoreText.setString("Score: " + to_string(score));
		window.draw(scoreText);
		if (player.HP <= 0)
		{
			window.draw(gameOverText);
			music.stop();

			if (player.HP == 0)
			{
				sound2.play();
				player.HP--;
			}

		}

		// Terminar o Frame
		window.display();
	}

	// Fim do aplicativo
	return 0;
}