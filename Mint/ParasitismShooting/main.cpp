#include <DxLib.h>
#include "Game.h"


int main(void)
{
	int ans = MessageBox(nullptr, "�t���X�N���[���ŕ\�����܂����H", "��ʂ̑傫���ǂ����悤��", MB_YESNO | MB_ICONQUESTION);

	Game& game = Game::Instance();
	game.Initialize(ans);
	game.Run();
	game.Terminate();
}

