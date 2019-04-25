#pragma once
#include "Scene.h"
#include "../Geometry.h"
#include <memory>

class GameScreen;
class Player;
class HUD;
class BackGround;
class PauseMenu;
class EnemyFactory;


class GamePlayingScene : public Scene
{
private:
	void (GamePlayingScene::*updater)(const Peripheral& p);

	void FadeinUpdate(const Peripheral& p);
	void FadeoutUpdate(const Peripheral& p);

	float time;
	Vector2 ssize;
	bool pauseFlag;

	std::shared_ptr<GameScreen> gameScreen;
	std::shared_ptr<Player> player;
	std::shared_ptr<HUD> hud;
	std::shared_ptr<BackGround> bg;
	std::shared_ptr<PauseMenu> pmenu;
	std::shared_ptr<EnemyFactory> efactory;


public:
	GamePlayingScene();
	~GamePlayingScene();

	void Update(const Peripheral& p);
};
