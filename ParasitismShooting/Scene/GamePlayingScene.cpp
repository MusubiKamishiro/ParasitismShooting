#include "GamePlayingScene.h"
#include <DxLib.h>
#include <stdlib.h>
#include "../Peripheral.h"
#include "../Game.h"
#include "ResultScene.h"

#include "../GameScreen.h"
#include "../HUD.h"
#include "../Character/Player.h"
#include "../BackGround.h"
#include "../PauseMenu.h"
#include "../Character/EnemyFactory.h"
#include "../Character/Enemy.h"


void GamePlayingScene::FadeinUpdate(const Peripheral & p)
{
	if (p.IsTrigger(PAD_INPUT_7) && (!pauseFlag))
	{
		pal = 255;
		updater = &GamePlayingScene::FadeoutUpdate;
	}

	if (pal == 255)
	{
		;
	}
	else
	{
		pal++;
	}
}

void GamePlayingScene::FadeoutUpdate(const Peripheral & p)
{
	if (pal <= 0)
	{
		Game::Instance().ChangeScene(new ResultScene());
	}
	else
	{
		pal -= 20;
	}
}

GamePlayingScene::GamePlayingScene()
{
	time = 0;
	pauseFlag = false;

	GetJoypadInputState(DX_INPUT_KEY_PAD1);		// �p�b�h�������̓L�[�{�[�h�œ�������

	gs.reset(new GameScreen());
	player.reset(new Player());
	hud.reset(new HUD());
	bg.reset(new BackGround());
	pmenu.reset(new PauseMenu());
	efactory.reset(new EnemyFactory(*player));
	
	ssize = Game::Instance().GetScreenSize();
	updater = &GamePlayingScene::FadeinUpdate;
}


GamePlayingScene::~GamePlayingScene()
{
}

void GamePlayingScene::Update(const Peripheral& p)
{
	if (p.IsTrigger(PAD_INPUT_8))
	{
		pauseFlag = !pauseFlag;
	}

	// �|�[�Y���Ă���ʂ�Ȃ���
	// �A�b�v�f�[�g�֘A
	if (!pauseFlag)
	{
		if (time == 0)
		{
			efactory->Create("fish", Vector2f(gs->outscreen + 45, gs->outscreen + 45));
		}

		player->Update(p);
		for (auto& enemy : efactory->GetLegion())
		{
			enemy->Update();
		}

		time++;
	}
	if (p.IsTrigger(PAD_INPUT_3) && (player->updater != &Player::Invincible))
	{
		player->Damage(p);
	}

	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	hud->Draw();
	
	// �Q�[����ʂ̕`�揀��
	gs->SetAndClearScreen();
	
	bg->Draw((int)time);
	player->Draw((int)time);
	for (auto& enemy : efactory->GetLegion())
	{
		enemy->Draw();
	}

	// �Q�[����ʂ̕`��
	gs->DrawAndChangeScreen();


	if (pauseFlag)
	{
		pmenu->Update();
		pmenu->Draw();
	}

	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs(pal - 255));
	DxLib::DrawBox(0, 0, ssize.x, ssize.y, 0x000000, true);
	(this->*updater)(p);
}

