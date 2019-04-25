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

	//shottype
	//bombtype

	//std::string _nowActionName;	// 現在再生中のｱｸｼｮﾝ名
	//int _nowCutIdx;				// 現在表示中のｶｯﾄ番号
	//unsigned int _flame;		// そのｶｯﾄ番号における経過時間

public:
	///// ｷｬﾗｸﾀｰを表示
	//void Draw(int _img);
	///// 当たり矩形を表示
	//void DebugDraw();

	CharacterObject();
	virtual ~CharacterObject();

	Vector2f GetPos()const;
};

