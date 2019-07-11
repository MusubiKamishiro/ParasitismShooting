#pragma once
#include "Scene.h"


class ContinueMenu;


class ContinueScene : public Scene
{
private:
	void (ContinueScene::*updater)(const Peripheral& p);

	void FadeinUpdate(const Peripheral& p);
	void FadeoutUpdate(const Peripheral& p);
	void WaitUpdate(const Peripheral& p);

	std::shared_ptr<ContinueMenu> cmenu;
	bool flag;

public:
	ContinueScene();
	~ContinueScene();

	void Update(const Peripheral& p);
	void Draw();
};

