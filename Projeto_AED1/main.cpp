#include <iostream>
#include "Game.h"

using namespace std;

// Principal
int main()
{
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