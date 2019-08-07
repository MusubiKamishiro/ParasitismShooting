#pragma once
#include "Scene.h"
#include "../Geometry.h"


class TitleMenu;


class TitleScene : public Scene
{
private:
	int titleImage;	// À²ÄÙ‰æ‘œ
	int titleNameImage;

	void (TitleScene::*updater)(const Peripheral& p);

	void FadeinUpdate(const Peripheral& p);
	void FadeoutUpdate(const Peripheral& p);
	void WaitUpdate(const Peripheral& p);

	std::shared_ptr<TitleMenu> tmenu;
	bool optionflag;
	Vector2 ssize;
	int time;

public:
	TitleScene();
	~TitleScene();

	void Update(const Peripheral& p);
	void Draw();
};

