#pragma once
#include "Scene.h"
#include <memory>

class OptionMenu;


class OptionScene : public Scene
{
private:
	void (OptionScene::*updater)(const Peripheral& p);

	void FadeinUpdate(const Peripheral& p);
	void FadeoutUpdate(const Peripheral& p);

	std::shared_ptr<OptionMenu> omenu;

public:
	OptionScene();
	~OptionScene();

	void Update(const Peripheral& p);
};

