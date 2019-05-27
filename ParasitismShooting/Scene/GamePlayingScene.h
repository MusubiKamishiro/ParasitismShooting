#pragma once
#include <memory>
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
class PauseMenu;
class ContinueMenu;
class EnemyFactory;
class CollisionDetector;
class EffectFactory;

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
}CharacterBank;


class GamePlayingScene : public Scene
{
private:
	void (GamePlayingScene::*updater)(const Peripheral& p);

	void FadeinUpdate(const Peripheral& p);
	void FadeoutUpdate(const Peripheral& p);
	void GameUpdate(const Peripheral& p);
	void ClearUpdate(const Peripheral& p);
	void ContinueUpdate(const Peripheral& p);
	void MoveResultUpdate(const Peripheral& p);

	void HitCol(const Peripheral& p);			// �����蔻��܂Ƃ�
	void Draw(const Peripheral& p, const int& time);	// �`��܂Ƃ�

	void Init(const unsigned int& stagenum);	// 2�̃R���X�g���N�^�̋��ʕ���

	float time;
	unsigned int nowStageNum;
	Vector2 ssize;
	bool pauseFlag, continueFlag;

	std::vector<CharacterBank> cBank;

	int bankCnt;

	std::shared_ptr<GameScreen> gs;
	std::shared_ptr<Player> player;
	std::shared_ptr<ShotFactory> sf;
	std::shared_ptr<HUD> hud;
	std::shared_ptr<BackGround> bg;
	std::shared_ptr<PauseMenu> pmenu;
	std::shared_ptr<ContinueMenu> cmenu;
	std::shared_ptr<EnemyFactory> ef;
	std::shared_ptr<CollisionDetector> cd;
	std::shared_ptr<EffectFactory> eff;

	Score& score = Score::Instance();

public:
	// �Z���N�g�V�[���Ŏg���R���X�g���N�^
	GamePlayingScene(const unsigned int& stagenum);
	// ���ԃ��U���g�Ŏg���R���X�g���N�^
	GamePlayingScene(const unsigned int& stagenum, const CharaData& cdata);
	~GamePlayingScene();

	void Update(const Peripheral& p);
};
