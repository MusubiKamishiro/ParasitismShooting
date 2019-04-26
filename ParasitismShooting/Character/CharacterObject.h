#pragma once
//#include <string>
#include <vector>
//#include <map>
#include "../Geometry.h"


// ｷｬﾗｸﾀｰ基底ｸﾗｽ
class CharacterObject
{
protected:
	int HP;			// 体力
	int SP;			// スタミナ

	Vector2f pos;	// 座標
	Vector2f vel;	// 移動速度
	Rect rect;		// 中心、幅と高さ

	int img;		// 画像
	//shottype
	//bombtype

	//std::string nowActionName;	// 現在再生中のｱｸｼｮﾝ名
	//unsigned int nowCutIdx;		// 現在表示中のｶｯﾄ番号
	//unsigned int flame;			// そのｶｯﾄ番号における経過時間

public:
	CharacterObject();
	virtual ~CharacterObject();

	// ｷｬﾗｸﾀｰを表示
	void Draw(int img);
	// 当たり矩形を表示
	void DebugDraw();

	// 矩形の情報をもらう
	Rect GetRects()const;
	Vector2f GetPos()const;
};

