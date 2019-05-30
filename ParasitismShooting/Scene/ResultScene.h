#pragma once
#include "Scene.h"

class ResultScene : public Scene
{
private:
	void (ResultScene::*updater)(const Peripheral& p);

	void FadeinUpdate(const Peripheral& p);
	void FadeoutUpdate(const Peripheral& p);

	unsigned int totalScore;
	unsigned int continueNum;

	int resultImage;

public:
	ResultScene(const unsigned int& score, const unsigned int& cnum);
	~ResultScene();

	void Update(const Peripheral& p);
};

