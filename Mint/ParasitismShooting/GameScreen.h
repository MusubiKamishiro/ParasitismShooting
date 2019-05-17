#pragma once
#include "Geometry.h"
class GameScreen
{
private:
	Vector2 gssize;
	int screen;
	Vector2f swing;

	int count, countMax;

public:
	GameScreen();
	~GameScreen();

	void SetAndClearScreen();
	void DrawAndChangeScreen(bool& swingflag);
	void SetGaussFilter();
	const Vector2 GetGSSize()const;

	const int outscreen;	// ��ʂɂ͉f��Ȃ��X�N���[���̕�
};

