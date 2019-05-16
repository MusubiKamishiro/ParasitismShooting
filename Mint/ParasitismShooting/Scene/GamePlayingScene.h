#pragma once
#include "Scene.h"
#include "../Geometry.h"
#include <memory>
#include <vector>

class GameScreen;
class Player;
class ShotFactory;
class HUD;
class BackGround;
class PauseMenu;
class ContinueMenu;
class EnemyFactory;
class CollisionDetector;

typedef struct CSV
{
	int time;
	int movePtn;
	std::string enemyname;
	Vector2f pos;
	int Speed;
	int HP;
	int SP;
	int cnt;
	int wait;
}CharacterBank;


class GamePlayingScene : public Scene
{
private:
	void (GamePlayingScene::*updater)(const Peripheral& p);

	void FadeinUpdate(const Peripheral& p);
	void FadeoutUpdate(const Peripheral& p);
	void GameUpdate(const Peripheral& p);
	void ContinueUpdate(const Peripheral& p);
	void MoveResultUpdate(const Peripheral& p);

	void Draw(const Peripheral& p, const int& time);

	float time;
	Vector2 ssize;
	bool pauseFlag, continueFlag;

	std::vector<CharacterBank> cBank;

	int bankCnt = 2;

	std::shared_ptr<GameScreen> gs;
	std::shared_ptr<Player> player;
	std::shared_ptr<ShotFactory> sf;
	std::shared_ptr<HUD> hud;
	std::shared_ptr<BackGround> bg;
	std::shared_ptr<PauseMenu> pmenu;
	std::shared_ptr<ContinueMenu> cmenu;
	std::shared_ptr<EnemyFactory> ef;
	std::shared_ptr<CollisionDetector> cd;


public:
	GamePlayingScene();
	~GamePlayingScene();

	void Update(const Peripheral& p);
};
