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
#include "TitleScene.h"

#include "../GameScreen.h"
#include "../HUD.h"
#include "../Character/Player.h"
#include "../Character/Shot/ShotFactory.h"
#include "../Character/Shot/Shot.h"
#include "../BackGround.h"
#include "../PauseMenu.h"
#include "../ContinueMenu.h"
#include "../Character/EnemyFactory.h"
#include "../Character/Enemy.h"
#include "../CollisionDetector.h"


void GamePlayingScene::FadeinUpdate(const Peripheral & p)
{
	if (pal > 255)
	{
		pal = 255;
		updater = &GamePlayingScene::GameUpdate;
	}
	else
	{
		pal += 20;
	}
}

void GamePlayingScene::FadeoutUpdate(const Peripheral & p)
{
	if (pal <= 0)
	{
		Game::Instance().ChangeScene(new TitleScene());
	}
	else
	{
		pal -= 20;
	}
}

void GamePlayingScene::GameUpdate(const Peripheral & p)
{
	pal = 255;
	if ((player->updater == &Player::Die))
	{
		continueFlag = true;
		updater = &GamePlayingScene::ContinueUpdate;
	}
}

void GamePlayingScene::ContinueUpdate(const Peripheral & p)
{
	if (!continueFlag)
	{
		player->Reborn(p);
		updater = &GamePlayingScene::GameUpdate;
	}
}

void GamePlayingScene::MoveResultUpdate(const Peripheral & p)
{
	Game::Instance().ChangeScene(new ResultScene());
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
	continueFlag = false;

	GetJoypadInputState(DX_INPUT_KEY_PAD1);		// パッドもしくはキーボードで動かせる

	gs.reset(new GameScreen());
	player.reset(new Player());
	sf.reset(new ShotFactory(*player));
	hud.reset(new HUD());
	bg.reset(new BackGround());
	pmenu.reset(new PauseMenu());
	cmenu.reset(new ContinueMenu());
	ef.reset(new EnemyFactory(*player));
	cd.reset(new CollisionDetector());
	
	ef->Create("fish", Vector2f(250, 100), 0, 0, 0, 1, 1, 3);
	ef->Create("fish", Vector2f(100, 100), 0, 0, 0, 1, 1, 3);
	ef->Create("fish", Vector2f(150, 100), 0, 0, 0, 1, 1, 3);
	ef->Create("fish", Vector2f(200, 100), 0, 0, 0, 1, 1, 3);

	ssize = Game::Instance().GetScreenSize();
	updater = &GamePlayingScene::FadeinUpdate;
}


GamePlayingScene::~GamePlayingScene()
{
}

void GamePlayingScene::Update(const Peripheral& p)
{
	if (updater != &GamePlayingScene::ContinueUpdate)
	{
		if (p.IsTrigger(PAD_INPUT_8))
		{
			pauseFlag = true;
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

			for (auto& shot : sf->GetLegion())
			{
				shot->Update();
			}

			player->Update(p);

			if (p.IsPressing(PAD_INPUT_2) && ((int)time % 3 ==0))
			{
				sf->Create(player->GetCharaData().shotType, player->GetPos(), 180, 5, 1, 4, SHOT_PTN::NORMAL, SHOOTER::PLAYER);
			}
			
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
							// 敵に気力があればダメージ
							if (enemy->GetCharaData().SP > 0)
							{
								if (player->updater != &Player::Invincible)
								{
									player->Damage(p);
								}
							}
							else
							{
								// プレイヤーが寄生中ならダメージ
								if (player->parasFlag)
								{
									if (player->updater != &Player::Invincible)
									{
										player->Damage(p);
									}
								}
								else
								{
									// 敵の力を手に入れる
									player->Parasitic(p, enemy->GetCharaData());
									enemy->Die();
								}
							}
						}
					}

					// 敵と弾
					for (auto& shot : sf->GetLegion())
					{
						for (auto& sRect : shot->GetActRect())
						{
							if (cd->IsCollision(shot->GetRects(sRect.rc), enemy->GetRects(eRect.rc), cd->GetRectCombi(sRect.rt, eRect.rt)))
							{
								//enemy->Damage();
								enemy->StunDamage();
								shot->Delete();
							}
						}
					}
				}
			}
			time++;
		}
		else
		{
			if (pmenu->Update(p, pauseFlag))
			{
				updater = &GamePlayingScene::FadeoutUpdate;
			}
		}
	}
	else
	{
		if (cmenu->Update(p, continueFlag))
		{
			updater = &GamePlayingScene::MoveResultUpdate;
		}
	}

	sf->OutofScreen();
	sf->ShotDelete();
	ef->EnemyDelete();

	Draw(p, time);
	
	(this->*updater)(p);
}

void GamePlayingScene::Draw(const Peripheral& p, const int & time)
{
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	hud->Draw(player->GetCharaData().HP);

	// ゲーム画面の描画準備
	gs->SetAndClearScreen();

	bg->Draw((int)time);
	player->Draw((int)time);

	for (auto& shot : sf->GetLegion())
	{
		shot->Draw();
	}
	for (auto& enemy : ef->GetLegion())
	{
		enemy->Draw((int)time);
	}

	if (pauseFlag)
	{
		gs->SetGaussFilter();
		pmenu->Draw();
	}
	else if (continueFlag)
	{
		gs->SetGaussFilter();
		cmenu->Draw();
	}

	// ゲーム画面の描画
	gs->DrawAndChangeScreen();


	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs(pal - 255));
	DxLib::DrawBox(0, 0, ssize.x, ssize.y, 0x000000, true);
}