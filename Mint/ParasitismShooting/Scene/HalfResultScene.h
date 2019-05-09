#pragma once
#include "Scene.h"

class HalfResultScene : public Scene
{
private:
	void (HalfResultScene::*updater)(const Peripheral& p);

	void FadeinUpdate(const Peripheral& p);
	void FadeoutUpdate(const Peripheral& p);

public:
	HalfResultScene();
	~HalfResultScene();

	void Update(const Peripheral& p);
};

