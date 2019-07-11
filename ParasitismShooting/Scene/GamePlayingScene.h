#pragma once
#include <vector>
#include "Scene.h"
#include "../Geometry.h"
#include "../Score.h"
#include "../Character/CharacterObject.h"


class GameScreen;
class Player;
class ShotFactory;
class HUD;
class BackGround;
class ContinueMenu;
class EnemyFactory;
class CollisionDetector;
class EffectFactory;
class HalfResultScene;

typedef struct CSV
{
	int time;
	int movePtn;
	std::string enemyname;
	std::string shotType;
	Vector2f pos;
	int Speed;
	int HP;
	int SP;
	int cnt;
	int wait;
	int shotCnt;
	int shotLevel;
}CharacterBank;


class GamePlayingScene : public Scene
{
private:
	void (GamePlayingScene::*updater)(const Peripheral& p);

	void FadeinUpdate(const Peripheral& p);
	void FadeoutUpdate(const Peripheral& p);
	void WaitUpdate(const Peripheral& p);


	void IdleUpdate(const Peripheral& p);
	void GameUpdate(const Peripheral& p);
	void ClearUpdate(const Peripheral& p);
	void ContinueUpdate(const Peripheral& p);
	void MoveResultUpdate(const Peripheral& p);

	void HitCol(const Peripheral& p);			// 当たり判定まとめ
	void Draw(const int& time);	// 描画まとめ

	void Init(const unsigned int& stagenum, const int& diff);	// 2つのコンストラクタの共通部分

	int difficult;				// 難易度
	float time;					// 時間
	unsigned int nowStageNum;	// 現在ステージ
	int parasCnt;				// 寄生回数
	int totalParasCnt;			// 累計寄生回数
	unsigned int cCount;		// コンティニュー回数
	unsigned int totalCCount;	// 累計コンティニュー回数
	Vector2 ssize;
	bool continueFlag, clearFlag, allClearFlag,nextstageFlag;
	bool DuringParasitism;

	std::vector<CharacterBank> cBank;

	int bankCnt;
	int moveCnt;

	std::shared_ptr<GameScreen> gs;
	std::shared_ptr<Player> player;
	std::shared_ptr<ShotFactory> sf;
	std::shared_ptr<HUD> hud;
	std::shared_ptr<BackGround> bg;
	std::shared_ptr<ContinueMenu> cmenu;
	std::shared_ptr<EnemyFactory> ef;
	std::shared_ptr<CollisionDetector> cd;
	std::shared_ptr<EffectFactory> eff;
	std::shared_ptr<HalfResultScene> hresult;

	Score& score = Score::Instance();

public:
	GamePlayingScene(const unsigned int& stagenum, const int& diff);
	~GamePlayingScene();

	void Update(const Peripheral& p);
	void Draw();
};
