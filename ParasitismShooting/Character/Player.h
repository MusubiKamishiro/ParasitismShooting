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
	void Die(const Peripheral &p);			// 敵機又は弾に当たって死んだ
	void Reborn(const Peripheral &p);		// 復活
	void Parasitic(const Peripheral &p, const CharaData& cdata);	// 寄生
	void ParasiticCancel(const Peripheral &p);		// 寄生解除

	void NotOutOfRange();		// 範囲外に行かせない

	CharaData originData;		// 寄生前の元々のデータ
	Vector2f startPos;			// 開始座標

	bool parasFlag;				// 寄生中か否か
	bool pinchFlag;				// 寄生解除されたらtrueになる

	int icount;
	int ccount;
	int efect;

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
};

