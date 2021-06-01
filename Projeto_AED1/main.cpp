#include "Game.h"

float  xmin = 0, xmax = 800, ymin = 0, ymax = 600;
float xinit = 384.f, yinit = 552.f;
bool pause, play = false, options = false, menuscrn = true;

// Principal
int main()
{
	//Janela
	RenderWindow window(VideoMode(800, 600), "Meteoro", Style::Titlebar | Style::Close);
	window.setFramerateLimit(60);

	//Colocando icone na janela
	Image windowIcon = Image{};
	if (windowIcon.loadFromFile("Assets/Asteroid.png"))
	{
		window.setIcon(windowIcon.getSize().x, windowIcon.getSize().y, windowIcon.getPixelsPtr());
	}

	//Menu 

	Menu menu(window.getSize().x, window.getSize().y);

	Clock deltaClock;
	Font font;
	font.loadFromFile("Assets/upheavtt.ttf");

	//Iniciando texturas
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

	// Text Game over
	Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(40);
	gameOverText.setFillColor(Color::Red);
	gameOverText.setPosition(290.f, 0.f);
	gameOverText.setString("GAME OVER!");

	// Text Pause
	Text pauseText;
	pauseText.setFont(font);
	pauseText.setCharacterSize(40);
	pauseText.setFillColor(Color::Yellow);
	pauseText.setPosition(320.f, 0.f);
	pauseText.setString("PAUSED");

	//Texto Controle R

	Text controlsR;
	controlsR.setFont(font);
	controlsR.setCharacterSize(35);
	controlsR.setFillColor(Color::Yellow);
	controlsR.setPosition(320.f, 100.f);
	controlsR.setString("R = RESTART");

	//Texto Controles Espaço

	Text controlsSpace;
	controlsSpace.setFont(font);
	controlsSpace.setCharacterSize(35);
	controlsSpace.setFillColor(Color::Yellow);
	controlsSpace.setPosition(320.f, 200.f);
	controlsSpace.setString("SPACEBAR = SHOOT");

	//Texto Back

	Text back;
	back.setFont(font);
	back.setCharacterSize(35);
	back.setFillColor(Color::Red);
	back.setPosition(360.f, 450.f);
	back.setString("BACK");

	//Texto Press R

	Text pressR;
	pressR.setFont(font);
	pressR.setCharacterSize(35);
	pressR.setFillColor(Color::Yellow);
	pressR.setPosition(220.f, 490.f);
	pressR.setString("PRESS 'R' TO RESTART");

	//Iniciando jogador
	Nave player(&playerTex);
	int score = 0;
	int shootTimer = 20;

	//Iniciando inimigo
	vector<Meteoro> enemies;
	int enemySpawnTimer = 0;

	//Visão do mapa
	View View(window.getDefaultView());
	FloatRect fBounds(0.f, 0.f, 3200.f, 2400.f);
	IntRect	iBounds(fBounds);
	background_tex.setRepeated(true);

	//Sprite do Background
	Sprite background(background_tex, iBounds);

	//Limites da Visão
	const Vector2f viewStart(fBounds.left + (fBounds.width / 2), fBounds.top + (fBounds.height / 2));
	const Vector2f spriteStart(fBounds.left, fBounds.top);

	//Musica
	Music music;
	if (!music.openFromFile("OST/Sidereal Chaos.ogg"))
	{
		return -1;
	}
	music.setVolume(30.f);

	if (play == true)
	{
		music.play();
		music.setLoop(true);
	}

	//Som
	SoundBuffer buffer;
	if (!buffer.loadFromFile("OST/Bullet.wav"))
	{
		return -1;
	}

	Sound bullet_sound;
	bullet_sound.setBuffer(buffer);
	bullet_sound.setVolume(20.f);

	//Som Game over
	SoundBuffer buffer2;
	if (!buffer2.loadFromFile("OST/GameOver.wav"))
	{
		return -1;
	}

	Sound sound2;
	sound2.setBuffer(buffer2);
	sound2.setVolume(20.f);

	// Enquanto Janela está aberta
	while (window.isOpen())
	{
		Event evento;

		Time dt = deltaClock.restart();

		//pollEvent

		while (window.pollEvent(evento))
		{
			switch (evento.type)
			{
				//Clicar no 'X'
			case Event::Closed:
			{
				window.close();
				break;
			}
			//Soltar essas teclas
			case Event::KeyReleased:

				if (options == true)
				{
					if (evento.key.code == Keyboard::Return)
					{
						options = false;
						menuscrn = true;
					}
				}

				else if (menuscrn == true)
				{
					switch (evento.key.code)
					{
					case Keyboard::Up:
						menu.MoveUp();
						break;
					case Keyboard::Down:
						menu.MoveDown();
						break;

					case Keyboard::Return:
						switch (menu.getPressedItem())
						{
						case 0:
							music.play();
							menuscrn = false;
							play = true;
							break;
						case 1:
							options = true;
							menuscrn = false;
							break;
						case 2:
							window.close();
							break;
						}
					}
				}

			if (evento.key.code == Keyboard::P && menuscrn == false && options == false)
			{
				pause = !pause;

				if (pause == true)
				{
					music.pause();
				}
				else
				{
					music.play();
				}
			}

			}
		} 

		if (player.HP > 0 && pause == false && play == true)
		{
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

			if (player.shape.getPosition().x <= xmin)
			{
				player.shape.setPosition(xmin + (1), player.shape.getPosition().y);
			}
			if (player.shape.getPosition().x >= xmax - 48)
			{
				player.shape.setPosition(xmax - (48), player.shape.getPosition().y);
			}
			if (player.shape.getPosition().y <= ymin)
			{
				player.shape.setPosition(player.shape.getPosition().x, ymin + (1));
			}
			if (player.shape.getPosition().y >= ymax - 48)
			{
				player.shape.setPosition(player.shape.getPosition().x, ymax - 48);
			}

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
				player.bullets[i].shape.move(0.f, -15.f);

				// Se o tiro for pra fora da tela
				if (player.bullets[i].shape.getPosition().y < 0)
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
				enemies[i].shape.rotate(200.f * dt.asSeconds());

				//Apaga inimigos fora da tela
				if (enemies[i].shape.getPosition().y > 700)
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
		window.draw(background);
		window.setView(window.getDefaultView());

		// Desenhar
		if (options == true)
		{
			window.draw(controlsR);
			window.draw(controlsSpace);
			window.draw(back);
		}

		if (menuscrn == true)
		{		
			menu.draw(window);
		}

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

		if (play == true)
		{
			window.draw(scoreText);
		}

		if (player.HP <= 0)
		{
			window.draw(gameOverText);
			music.stop();
			window.draw(pressR);

			if (player.HP == 0)
			{
				sound2.play();
				player.HP--;
			}
			if (Keyboard::isKeyPressed(Keyboard::R) && sound2.getStatus() == SoundSource::Status::Stopped)
			{
				enemies.clear();
				player.HP = 1;
				score = 0;
				player.shape.setPosition(Vector2f(xinit, yinit));
				music.play();
				enemySpawnTimer = 0;
			}
		}
		else
		{
			if (pause == true)
			{
				window.draw(pauseText);
			}
		}

		// Terminar o Frame
		window.display();
	}

	// Fim do aplicativo
	return 0;
}
