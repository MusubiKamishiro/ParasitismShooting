#pragma once
#include "Scene.h"


class TitleMenu;


class TitleScene : public Scene
{
private:
	int titleImage;	// ���ى摜

	void (TitleScene::*updater)(const Peripheral& p);

	void FadeinUpdate(const Peripheral& p);
	void FadeoutUpdate(const Peripheral& p);
	void WaitUpdate(const Peripheral& p);

	std::shared_ptr<TitleMenu> tmenu;
	bool optionflag;

public:
	TitleScene();
	~TitleScene();

	void Update(const Peripheral& p);
	void Draw();
};

