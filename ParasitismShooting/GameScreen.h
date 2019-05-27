#pragma once
#include <vector>
#include "Geometry.h"


 struct SMALL_BOX
{
	 Box box;
	 bool drawflag;
};


class GameScreen
{
private:
	Vector2 luPos;		// ゲーム画面の左上の座標
	Vector2 gssize;		// ゲーム画面のサイズ
	int screen;			// ゲーム画面
	Vector2f swing;		// 揺れ幅

	int count, countMax;

	std::vector<SMALL_BOX> sboxes;	// 小箱の集まり, 画面遷移に使う

public:
	GameScreen();
	~GameScreen();

	void SetAndClearScreen();
	void DrawAndChangeScreen(bool& swingflag);
	void SetGaussFilter();
	const Vector2 GetGSSize()const;

	const int outscreen;	// 画面には映らないスクリーンの幅
};

