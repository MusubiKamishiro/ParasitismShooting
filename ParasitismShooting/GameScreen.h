#pragma once
#include "Geometry.h"
class GameScreen
{
private:
	Vector2 gssize;
	int screen;
	Vector2f swing;

public:
	GameScreen();
	~GameScreen();

	void SetAndClearScreen();
	void DrawAndChangeScreen();
	const Vector2 GetGSSize()const;

	const int outscreen;	// 画面には映らないスクリーンの幅
};

