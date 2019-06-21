#include <DxLib.h>
#include "Game.h"


int main(void)
{
	SetBackgroundColor(255, 255, 255);
	Game& game = Game::Instance();
	game.Initialize();
	game.Run();
	game.Terminate();
}

