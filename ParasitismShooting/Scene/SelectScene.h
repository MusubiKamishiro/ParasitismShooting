#pragma once
#include "Scene.h"
#include <memory>

class SelectMenu;

class SelectScene : public Scene
{
private:
	std::shared_ptr<SelectMenu> smenu;

	int img;
	int difficult;
	void (SelectScene::*updater)(const Peripheral& p);

	void FadeinUpdate(const Peripheral& p);
	void FadeoutUpdate(const Peripheral& p);

public:
	SelectScene();
	~SelectScene();

	void Update(const Peripheral& p);
};

