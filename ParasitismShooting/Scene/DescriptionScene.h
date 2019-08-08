#pragma once
#include "Scene.h"
#include "../Geometry.h"
#include "../KeyConfig.h"


class DescriptionScene : public Scene
{
private:
	void (DescriptionScene::*updater)(const Peripheral& p);

	void FadeinUpdate(const Peripheral& p);
	void FadeoutUpdate(const Peripheral& p);
	void WaitUpdate(const Peripheral& p);

	int img;
	KeyConfig& key = KeyConfig::Instance();

public:
	DescriptionScene();
	~DescriptionScene();

	void Update(const Peripheral& p);
	void Draw();
};

