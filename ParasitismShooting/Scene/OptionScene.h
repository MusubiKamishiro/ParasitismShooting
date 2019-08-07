#pragma once
#include "Scene.h"


class OptionMenu;


class OptionScene : public Scene
{
private:
	void (OptionScene::*updater)(const Peripheral& p);

	void FadeinUpdate(const Peripheral& p);
	void FadeoutUpdate(const Peripheral& p);
	void WaitUpdate(const Peripheral& p);

	std::shared_ptr<OptionMenu> omenu;

public:
	OptionScene();
	~OptionScene();

	void Update(const Peripheral& p);
	void Draw();
};

