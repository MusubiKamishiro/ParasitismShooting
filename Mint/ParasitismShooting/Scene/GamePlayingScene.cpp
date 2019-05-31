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
#include "HalfResultScene.h"
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
#include "../KeyConfig.h"
#include "../EffectFactory.h"
#include "../Effect.h"
#include "../Sound.h"


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

void GamePlayingScene::IdleUpdate(const Peripheral & p)
{
	time = 0;
	if (!hresult->Update(p))
	{
		hresult.reset(new HalfResultScene());
		
		if (!allClearFlag)
		{
			updater = &GamePlayingScene::GameUpdate;
		}
		else
		{
			updater = &GamePlayingScene::MoveResultUpdate;
		}
	}
}

void GamePlayingScene::GameUpdate(const Peripheral & p)
{
	if (player->updater == &Player::Die)
	{
		continueFlag = true;
		updater = &GamePlayingScene::ContinueUpdate;
	}
}

void GamePlayingScene::ClearUpdate(const Peripheral & p)
{
	if (hresult->Update(p))
	{
		if (!allClearFlag)
		{
			Init(nowStageNum + 1, difficult);

			player.reset(new Player(player->GetCharaData()));
			ef.reset(new EnemyFactory(*player));
			sf.reset(new ShotFactory(*player, *ef));

			clearFlag = false;
		}
		
		updater = &GamePlayingScene::IdleUpdate;
	}
}

void GamePlayingScene::ContinueUpdate(const Peripheral & p)
{
	if (!continueFlag)
	{
		score.InitScore();
		++cCount;
		++totalCCount;
		player->Reborn(p);
		updater = &GamePlayingScene::GameUpdate;
	}
}

void GamePlayingScene::MoveResultUpdate(const Peripheral & p)
{
	Game::Instance().ChangeScene(new ResultScene(score.GetNowScore(), totalCCount));
}

void GamePlayingScene::Init(const unsigned int & stagenum, const int& difficult)
{
	Sound::Instance().AddBGM("stage.mp3");

	// ステージ名の作成
	nowStageNum = stagenum;
	std::string s = "stage/stage" + std::to_string(nowStageNum) + ".csv";

	std::ifstream ifs(s);
	assert(ifs);


	std::string Bank[100][13];
	std::string str = "";
	int i = 0;
	int j = 0;

	bankCnt = 3;
	cBank.resize(0);

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
			Bank[i][2],Bank[i][3],Vector2f(atof(Bank[i][4].c_str()),atof(Bank[i][5].c_str())),
			atoi(Bank[i][6].c_str()),atoi(Bank[i][7].c_str()),atoi(Bank[i][8].c_str()),
			atoi(Bank[i][9].c_str()),atoi(Bank[i][10].c_str()),atoi(Bank[i][11].c_str()),atoi(Bank[i][12].c_str())
			});
		j = 0;
		i++;

	}
	cBank.push_back({ -1, 5,"weakfishN", "WeakNormal", Vector2f(450, 60), 3, 1, 1, 0, 240, 60, 1 });
	cBank.push_back({ -1, 5,"weakfishS", "WeakShotgun", Vector2f(50, 60), 3, 1, 1, 0, 240, 60, 3 });
	time = 0;
	parasCnt = 0;
	cCount = 0;
	pauseFlag = false;
	continueFlag = false;
	clearFlag = false;
	allClearFlag = false;

	gs.reset(new GameScreen());
	hud.reset(new HUD());
	bg.reset(new BackGround(stagenum));
	pmenu.reset(new PauseMenu());
	cmenu.reset(new ContinueMenu());
	cd.reset(new CollisionDetector());
	eff.reset(new EffectFactory());

	ssize = Game::Instance().GetScreenSize();

	moveCnt = 0;
}

GamePlayingScene::GamePlayingScene(const unsigned int& stagenum, const int& diff)
{
	Sound::Instance().AddSE("shot.mp3");

	difficult = diff;
	Init(stagenum, diff);

	totalParasCnt = 0;
	totalCCount = 0;

	DuringParasitism = false;

	hresult.reset(new HalfResultScene());
	player.reset(new Player());
	ef.reset(new EnemyFactory(*player));
	sf.reset(new ShotFactory(*player, *ef));

	updater = &GamePlayingScene::FadeinUpdate;
}


GamePlayingScene::~GamePlayingScene()
{
}

void GamePlayingScene::Update(const Peripheral& p)
{
	Sound::Instance().PlayBGM(false);

	if (updater != &GamePlayingScene::ContinueUpdate)
	{
		if (p.IsTrigger(KeyConfig::Instance().GetNowKey(PAUSE)) && (updater == &GamePlayingScene::GameUpdate))
		{
			pauseFlag = !pauseFlag;
		}

		// ポーズしてたら通らないよ
		// アップデート関連
		if (!pauseFlag)
		{
			if (cBank[bankCnt].time == ((int)time/*%650*/))
			{

				ef->Create(cBank[bankCnt].enemyname.c_str(), cBank[bankCnt].shotType.c_str(), Vector2f(gs->outscreen + cBank[bankCnt].pos.x, gs->outscreen + cBank[bankCnt].pos.y),
					cBank[bankCnt].movePtn, cBank[bankCnt].cnt, cBank[bankCnt].wait, cBank[bankCnt].HP, cBank[bankCnt].SP, cBank[bankCnt].Speed, cBank[bankCnt].shotCnt, cBank[bankCnt].shotLevel);
				if (cBank.size() - 1 > bankCnt)
				{
					bankCnt++;
				}
				/*if (cBank.size() > bankCnt)
				{
					bankCnt++;
					if (bankCnt == cBank.size())
					{
						bankCnt--;
					}
				}*/
				//bankCnt = bankCnt % (cBank.size()-2) + 2;
			}

			if (!DuringParasitism)
			{
				for (auto& shot : sf->GetLegion())
				{
					shot->Update();
				}

				if (!clearFlag)
				{
					player->Update(p);

					if (p.IsPressing(KeyConfig::Instance().GetNowKey(ATTACK)) && ((int)time % 6 == 1))
					{
						Sound::Instance().PlaySE("shot");
						sf->Create(player->GetCharaData().shotType, player->GetPos(), 8, 1, player->GetCharaData().shotLevel, SHOOTER::PLAYER);
						//sf->Create(player->GetCharaData().shotTypeSub, player->GetPos(), 8, 1, player->GetCharaData().shotLevel, SHOOTER::PLAYER);
					}

					for (auto& enemy : ef->GetLegion())
					{
						if (enemy->GetShotReady())
						{
							if (enemy->actFlag)
							{
								Sound::Instance().PlaySE("shot");
								sf->Create(enemy->GetCharaData().shotType, enemy->GetPos(), 2, 1, enemy->GetCharaData().shotLevel, (enemy->GetCharaData().shotType == (enemy->GetCharaData().shotType == "WeakNormal" ? "WeakNormal" : "WeakShotgun") ? SHOOTER::PLAYER : SHOOTER::ENEMY));
							}
						}
						enemy->Update();

						if (enemy->bossFlag)
						{
							if ((int)time % 350 == 0)
							{
								ef->Create(cBank[bankCnt + (cBank[bankCnt - 1].shotType.c_str() == "WeakNormal" ? 1 : 0)].enemyname.c_str(), cBank[bankCnt + (cBank[bankCnt - 1].shotType.c_str() == "WeakNormal" ? 1 : 0)].shotType.c_str(), Vector2f(gs->outscreen + cBank[bankCnt + (cBank[bankCnt - 1].shotType.c_str() == "WeakNormal" ? 1 : 0)].pos.x, gs->outscreen + cBank[bankCnt + (cBank[bankCnt - 1].shotType.c_str() == "WeakNormal" ? 1 : 0)].pos.y),
									cBank[bankCnt + (cBank[bankCnt - 1].shotType.c_str() == "WeakNormal" ? 1 : 0)].movePtn, cBank[bankCnt + (cBank[bankCnt - 1].shotType.c_str() == "WeakNormal" ? 1 : 0)].cnt, cBank[bankCnt + (cBank[bankCnt - 1].shotType.c_str() == "WeakNormal" ? 1 : 0)].wait, cBank[bankCnt + (cBank[bankCnt - 1].shotType.c_str() == "WeakNormal" ? 1 : 0)].HP, cBank[bankCnt + (cBank[bankCnt - 1].shotType.c_str() == "WeakNormal" ? 1 : 0)].SP, cBank[bankCnt + (cBank[bankCnt - 1].shotType.c_str() == "WeakNormal" ? 1 : 0)].Speed, cBank[bankCnt + (cBank[bankCnt - 1].shotType.c_str() == "WeakNormal" ? 1 : 0)].shotCnt, cBank[bankCnt + (cBank[bankCnt - 1].shotType.c_str() == "WeakNormal" ? 1 : 0)].shotLevel);
								if (cBank[bankCnt].enemyname == "weakfishN")
								{
									bankCnt++;
								}
								else
								{
									bankCnt--;
								}
							}
						}
					}

					HitCol(p);

					for (auto& enemy : ef->GetLegion())
					{
						if (enemy->scoreFlag)
						{
							if (enemy->nextStageFlag)
							{
								nextstageFlag = enemy->nextStageFlag;
							}
							score.AddScore(enemy->GetScore());
						}
					}
				}
				hud->Update();

				// スコアで次のステージへ(デバックのため一時的なもの)
				
				if (nextstageFlag)
				{
					if (nowStageNum == 5)
					{
						allClearFlag = true;
					}

					if (moveCnt > 120)
					{
						if (!clearFlag)
						{
							Score::Instance().AddClearBonus(nowStageNum, parasCnt, 0, cCount, difficult);

							clearFlag = true;
							updater = &GamePlayingScene::ClearUpdate;
							nextstageFlag = false;
						}
					}
					++moveCnt;
				}
				++time;
			}
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
	ef->OutofScreen();
	sf->ShotDelete();
	//ef->EnemyDelete();
	
	for (int i = 0; i < ef->GetLegion().size(); ++i)
	{
		auto enemy = *std::next(ef->GetLegion().begin(), i);
		if (!enemy->GetLifeFlag())
		{
			ef->GetLegion().erase(std::next(ef->GetLegion().begin(), i));
			--i;

			// 倒してるならエフェクト発動
			if (enemy->scoreFlag)
			{
				eff->Create("dieEffect", enemy->GetPos(), (int)time, 30);
			}
		}
	}

	for (auto& effect : eff->GetLegion())
	{
		effect->Update((int)time);
	}
	eff->EffectDelete();

	Draw(p, (int)time);
	
	(this->*updater)(p);

	// フェードイン,アウトのための幕
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs(pal - 255));
	DxLib::DrawBox(0, 0, ssize.x, ssize.y, 0x000000, true);

}

void GamePlayingScene::HitCol(const Peripheral& p)
{
	// キャラクターと弾
	for (auto& shot : sf->GetLegion())
	{
		if (shot->GetShooter() == SHOOTER::ENEMY)
		{
			// 自機と敵の弾
			for (auto& pRect : player->GetActRect())
			{
				for (auto& sRect : shot->GetActRect())
				{
					if (cd->IsCollision(shot->GetRects(sRect.rc), player->GetRects(pRect.rc), cd->GetRectCombi(sRect.rt, pRect.rt)))
					{
						player->Damage(p);
					}
				}
			}
		}
		else if (shot->GetShooter() == SHOOTER::PLAYER)
		{
			// 敵機と自機の弾
			for (auto& enemy : ef->GetLegion())
			{
				for (auto& eRect : enemy->GetActRect())
				{
					for (auto& sRect : shot->GetActRect())
					{
						if (cd->IsCollision(shot->GetRects(sRect.rc), enemy->GetRects(eRect.rc), cd->GetRectCombi(sRect.rt, eRect.rt)))
						{
							if (shot->GetShotName() != "WeakNormal" && shot->GetShotName() != "WeakShotgun")
							{
								if (shot->GetShotName() != "Weak")
								{
									enemy->Damage();
									if (enemy->GetCharaData().HP == 0 || enemy->actFlag == false)
									{
										enemy->ShotStop();
									}
								}
								else
								{
									enemy->StunDamage();
								}
								shot->Delete();
							}
						}
					}
				}
			}
		}
	}

	// 敵とプレイヤー
	for (auto& enemy : ef->GetLegion())
	{
		for (auto& eRect : enemy->GetActRect())
		{
			for (auto& pRect : player->GetActRect())
			{
				if (cd->IsCollision(player->GetRects(pRect.rc), enemy->GetRects(eRect.rc), cd->GetRectCombi(pRect.rt, eRect.rt)))
				{
					// 敵に気力があればダメージ
					if (enemy->GetCharaData().SP > 0)
					{
						player->Damage(p);
					}
					else
					{
						// プレイヤーが寄生中ならダメージ
						if (player->parasFlag)
						{
							player->Damage(p);
						}
						else
						{
							// 敵の力を手に入れる
							player->Parasitic(p, enemy->GetCharaData());
							++parasCnt;
							++totalParasCnt;
							DuringParasitism = true;
							score.AddScore(enemy->GetScore() * 1.2);
							enemy->Die();
						}
					}
				}
			}
		}
	}
}

void GamePlayingScene::Draw(const Peripheral& p, const int & time)
{
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	hud->Draw(player->GetCharaData().HP, player->parasFlag, parasCnt, cCount);

	// ゲーム画面の描画準備
	gs->SetAndClearScreen();

	bg->Draw(time);
	player->Draw(time);

	for (auto& shot : sf->GetLegion())
	{
		if (shot->GetShooter() == SHOOTER::PLAYER)
		{
			DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
			shot->Draw();
			DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		}
		else if (shot->GetShooter() == SHOOTER::ENEMY)
		{
			shot->Draw();
		}
	}

	for (auto& enemy : ef->GetLegion())
	{
		enemy->Draw(time);
	}
	for (auto& effect : eff->GetLegion())
	{
		effect->Draw();
	}

	if (DuringParasitism)
	{
		static int t = 0;
		DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
		DxLib::DrawBox(0, 0, ssize.x + gs->outscreen, ssize.y + gs->outscreen, 0x000000, true);
		DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		player->ParasDraw(t);
		
		++t;
		if ((t % 60) == 0)
		{
			DuringParasitism = false;
		}
	}

	if((updater == &GamePlayingScene::IdleUpdate) || (updater == &GamePlayingScene::ClearUpdate))
	{
		hresult->Draw(allClearFlag);
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
	gs->DrawAndChangeScreen(player->pinchFlag);
}