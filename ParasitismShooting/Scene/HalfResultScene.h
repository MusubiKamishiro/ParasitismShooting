#pragma once
#include <memory>
#include "Scene.h"
#include "../Character/CharacterObject.h"

class HUD;

class HalfResultScene : public Scene
{
private:
	void (HalfResultScene::*updater)(const Peripheral& p);

	void FadeinUpdate(const Peripheral& p);
	void FadeoutUpdate(const Peripheral& p);

	unsigned int nextstage;
	CharaData nowstate;

	std::shared_ptr<HUD> hud;

public:
	HalfResultScene(const unsigned int& nowstagenum, const CharaData& cdata);
	~HalfResultScene();

	void Update(const Peripheral& p);
};

