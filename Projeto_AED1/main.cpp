#include "Game.h"

// Principal
int main()
{
	//Inicializar o srand

	srand(static_cast<unsigned>(time(NULL)));

	//Inicializar o jogo
	Game game;

	//Game Loop
	while (game.running()) 
	{
		//Update
		game.update();

		//Render
		game.render();
		
	}

	//Fim do aplicativo
	return 0;
}