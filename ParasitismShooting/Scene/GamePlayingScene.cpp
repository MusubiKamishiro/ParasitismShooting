#include "GamePlayingScene.h"
#include <DxLib.h>
#include <stdlib.h>
#include <cassert>
#include <fstream>
#include <string>
#include <sstream>

#include "../Peripheral.h"
#include "../Game.h"
#include "ResultScene.h"

#include "../GameScreen.h"
#include "../HUD.h"
#include "../Character/Player.h"
#include "../Character/Shot/ShotFactory.h"
#include "../Character/Shot/Shot.h"
#include "../BackGround.h"
#include "../PauseMenu.h"
#include "../Character/EnemyFactory.h"
#include "../Character/Enemy.h"
#include "../CollisionDetector.h"


void GamePlayingScene::FadeinUpdate(const Peripheral & p)
{
	if ((player->HP == 0) && (!pauseFlag))
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
	std::ifstream ifs("stage/stage1.csv");
	assert(ifs);


	std::string Bank[100][10];
	std::string str = "";
	int i = 0;
	int j = 0;


	while (std::getline(ifs, str))
	{
		std::string tmp = "";
		std::istringstream stream(str);


		while (std::getline(stream, tmp, ','))
		{
			Bank[i][j] = tmp;
			j++;
		}

		cBank.push_back({ atoi(Bank[i][0].c_str()),atoi(Bank[i][1].c_str()),
			Bank[i][2],Vector2f(atof(Bank[i][3].c_str()),atof(Bank[i][4].c_str())),
			atoi(Bank[i][5].c_str()),atoi(Bank[i][6].c_str()),
			atoi(Bank[i][7].c_str()),atoi(Bank[i][8].c_str()),atoi(Bank[i][9].c_str()) });
		j = 0;
		i++;

	}
	time = 0;
	pauseFlag = false;

	GetJoypadInputState(DX_INPUT_KEY_PAD1);		// パッドもしくはキーボードで動かせる

	gs.reset(new GameScreen());
	player.reset(new Player());
	sf.reset(new ShotFactory(*player));
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
		if (cBank[bankCnt].time == time)
		{
			ef->Create(cBank[bankCnt].enemyname.c_str(), Vector2f(gs->outscreen + cBank[bankCnt].pos.x, gs->outscreen + cBank[bankCnt].pos.y), 
				cBank[bankCnt].movePtn, cBank[bankCnt].cnt, cBank[bankCnt].wait, cBank[bankCnt].HP, cBank[bankCnt].SP, cBank[bankCnt].Speed);
			if (cBank.size() > bankCnt)
			{
				bankCnt++;
				if (bankCnt == cBank.size())
				{
					bankCnt--;
				}
			}
		}

		//shot->Update();
		player->Update(p);
		//shot->ShotBullet(p, player->pos);
		for (auto& enemy : ef->GetLegion())
		{
			enemy->Update();
		}

		// 当たり判定
		for (auto& enemy : ef->GetLegion())
		{
			// 当たり判定ﾙｰﾌﾟ
			for (auto& eRect : enemy->GetActRect())
			{
				// 敵とプレイヤー
				for (auto& pRect : player->GetActRect())
				{
					if (cd->IsCollision(player->GetRects(pRect.rc), enemy->GetRects(eRect.rc), cd->GetRectCombi(pRect.rt, eRect.rt)))
					{
						if (player->updater != &Player::Invincible)
						{
							player->Damage(p);
						}
					}
				}

				// 敵と弾
//				for (int s = 0; s < shot->cShot.size(); ++s)
				{
					/*for (auto& sRect : shot->GetActRect())
					{
						if (cd->IsCollision(shot->GetRects(sRect.rc), enemy->GetRects(eRect.rc), cd->GetRectCombi(sRect.rt, eRect.rt)))
						{
							enemy->Damage();
						}
					}*/
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
	//shot->Draw();
	for (auto& enemy : ef->GetLegion())
	{
		auto h = enemy->GetHP();
		if (h > 0)
		{
			enemy->Draw();
		}
		
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

