#pragma once
#include "Scene.h"
#include "../Geometry.h"
#include <memory>

class Player;
class HUD;


class GamePlayingScene : public Scene
{
private:
	void (GamePlayingScene::*updater)(const Peripheral& p);

	void FadeinUpdate(const Peripheral& p);
	void FadeoutUpdate(const Peripheral& p);

	int img;
	Vector2 ssize;

	std::shared_ptr<Player> player;
	std::shared_ptr<HUD> hud;


public:
	GamePlayingScene();
	~GamePlayingScene();

	void Update(const Peripheral& p);

};
