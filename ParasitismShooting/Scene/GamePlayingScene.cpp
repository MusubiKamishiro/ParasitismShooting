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
#include "../CollisionDetector.h"


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

	GetJoypadInputState(DX_INPUT_KEY_PAD1);		// パッドもしくはキーボードで動かせる

	gs.reset(new GameScreen());
	player.reset(new Player());
	hud.reset(new HUD());
	bg.reset(new BackGround());
	pmenu.reset(new PauseMenu());
	ef.reset(new EnemyFactory(*player));
	cd.reset(new CollisionDetector());
	
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

	// ポーズしてたら通らないよ
	// アップデート関連
	if (!pauseFlag)
	{
		if (time == 0)
		{
			ef->Create("fish", Vector2f(gs->outscreen + 250, gs->outscreen + 345));
		}

		player->Update(p);
		for (auto& enemy : ef->GetLegion())
		{
			enemy->Update();
		}

		// 当たり判定
		for (auto& enemy : ef->GetLegion())
		{
			// 当たり判定ﾙｰﾌﾟ
			for (auto& pRect : player->GetAcutRect())
			{
				for (auto& eRect : enemy->GetAcutRect())
				{
					if (cd->IsCollision(enemy->GetRects(eRect.rc), player->GetRects(pRect.rc)))
					{
						if (player->updater != &Player::Invincible)
						{
							player->Damage(p);
						}
					}
				}
			}
		}
		
		time++;
	}

	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	hud->Draw(player->GetHP());
	
	// ゲーム画面の描画準備
	gs->SetAndClearScreen();
	
	bg->Draw((int)time);
	player->Draw((int)time);
	for (auto& enemy : ef->GetLegion())
	{
		enemy->Draw();
	}

	// ゲーム画面の描画
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

