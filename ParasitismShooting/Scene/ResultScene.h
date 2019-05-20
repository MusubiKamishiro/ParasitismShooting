#pragma once
#include "Scene.h"

class ResultScene : public Scene
{
private:
	void (ResultScene::*updater)(const Peripheral& p);

	void FadeinUpdate(const Peripheral& p);
	void FadeoutUpdate(const Peripheral& p);

	unsigned int totalScore;

public:
	ResultScene(const unsigned int& score);
	~ResultScene();

	void Update(const Peripheral& p);
};

