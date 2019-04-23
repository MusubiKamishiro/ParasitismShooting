#include <DxLib.h>
#include "Game.h"


int main(void)
{
	int ans = MessageBox(nullptr, "フルスクリーンで表示しますか？", "画面の大きさどうしようか", MB_YESNO | MB_ICONQUESTION);

	Game& game = Game::Instance();
	game.Initialize(ans);
	game.Run();
	game.Terminate();
}

