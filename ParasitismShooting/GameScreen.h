#pragma once
#include <vector>
#include "Geometry.h"


class GameScreen
{
private:
	Vector2 luPos;		// ゲーム画面の左上の座標
	Vector2 gssize;		// ゲーム画面のサイズ
	int screen;			// ゲーム画面
	Vector2f swing;		// 揺れ幅
	int screenBorderWidth;	// ゲーム画面の縁の幅

	int count, countMax;

public:
	GameScreen();
	~GameScreen();

	// ゲーム画面の描画準備
	void SetAndClearScreen();
	
	// ゲーム画面の描画
	void DrawAndChangeScreen(bool& swingflag);
	
	// 画面にフィルターをかける
	void SetGaussFilter();
	
	// ゲームスクリーンのサイズ取得
	// 画面のサイズとは違うので注意
	const Vector2 GetGSSize()const;

	const int outscreen;	// 画面には映らないスクリーンの幅
};

