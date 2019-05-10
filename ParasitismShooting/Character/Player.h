#pragma once
#include "../Geometry.h"
#include "CharacterObject.h"
#include <memory>

enum Dir
{
	DIR_UP,
	DIR_RIGHT,
	DIR_DOWN,
	DIR_LEFT,
	DIR_MAX
};

class Peripheral;
class GamePlayingScene;
class GameScreen;


class Player : public CharacterObject
{
	friend GamePlayingScene;
private:
	// 状態遷移のためのメンバ関数ポインタ
	void (Player::*updater)(const Peripheral &p);
	void Move(const Peripheral &p);
	void Damage(const Peripheral &p);		// ダメージくらった
	void Invincible(const Peripheral &p);	// 無敵時間
	void Die(const Peripheral &p);			// 敵機に当たって死んだ

	void NotOutOfRange();		// 範囲外に行かせない

	Vector2f startPos;			// 開始座標
	float moveVel;				// 移動量
	int count;

	// 移動範囲限界値
	int up;
	int right;
	int left;
	int down;

	std::shared_ptr<GameScreen> gs;
	
public:
	Player();
	~Player();

	void Update(const Peripheral &p);
	void Draw(const int& time);

	int& GetHP();
};

