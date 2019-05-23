#pragma once
#include "Scene.h"
#include "../Character/CharacterObject.h"

class HalfResultScene : public Scene
{
private:
	void (HalfResultScene::*updater)(const Peripheral& p);

	void FadeinUpdate(const Peripheral& p);
	void FadeoutUpdate(const Peripheral& p);

	unsigned int nextstage;
	CharaData nowstate;

public:
	HalfResultScene(const unsigned int& nowstagenum, const CharaData& cdata);
	~HalfResultScene();

	void Update(const Peripheral& p);
};

