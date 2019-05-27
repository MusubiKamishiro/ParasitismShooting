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
	bool parasFlag;

	std::shared_ptr<HUD> hud;

public:
	HalfResultScene(const unsigned int& nowstagenum, const CharaData& cdata, const bool& pflag);
	~HalfResultScene();

	void Update(const Peripheral& p);
};

