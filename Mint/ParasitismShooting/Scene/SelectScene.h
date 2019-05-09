#pragma once
#include "Scene.h"

class SelectScene : public Scene
{
private:

	int img;
	void (SelectScene::*updater)(const Peripheral& p);

	void FadeinUpdate(const Peripheral& p);
	void FadeoutUpdate(const Peripheral& p);

public:
	SelectScene();
	~SelectScene();

	void Update(const Peripheral& p);
};

