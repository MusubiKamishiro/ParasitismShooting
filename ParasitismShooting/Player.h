#pragma once
#include "Geometry.h"
//#include "CharacterObject.h"
//#include <memory>
//#include <vector>

enum Dir
{
	DIR_UP,
	DIR_RIGHT,
	DIR_DOWN,
	DIR_LEFT,
	DIR_MAX
};

class Peripheral;
//class GamePlayingScene;

class Player// : public CharacterObject
{
	//friend GamePlayingScene;
private:
	// 状態遷移のためのメンバ関数ポインタ
	void (Player::*updater)(const Peripheral &p);
	void Move(const Peripheral &p);
	void Shot(const Peripheral &p);			// 攻撃
	void Die(const Peripheral &p);			// 敵機に当たって死んだ

	void Draw(Vector2& pos);				// プレイヤーの描画

	void DebugDraw();
	
	void NotOutOfRange();

	Vector2 startPos;			// 開始座標
	Vector2 pos;				// 現在座標
	Vector2 vel;				// 移動速度
	int moveVel;				// 移動量
	
	// 移動範囲内
	int up;
	int right;
	int left;
	int down;

	int img;
	
public:
	Player();
	~Player();

	void Update(const Peripheral &p);

	Vector2 GetPos()const;
};

