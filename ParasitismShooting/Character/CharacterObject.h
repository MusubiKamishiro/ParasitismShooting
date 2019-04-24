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

	//// ｱｸｼｮﾝ切り替え
	//void ChangeAction(const char* name);
	//// ｱﾆﾒｰｼｮﾝのﾌﾚｰﾑを1進める
	//bool ProceedAnimationFile();

	//// ﾌｧｲﾙの読み込み
	//void ReadActionFile(const char* actionPath);

	//bool _isTurn;		// 反転ﾌﾗｸﾞ

public:
	//bool _isAerial;			// 空中ﾌﾗｸﾞ


	///// ｷｬﾗｸﾀｰを表示
	//void Draw(int _img);
	///// 当たり矩形を表示
	//void DebugDraw();
	//// 矩形の情報をもらう
	//Rect GetActionRects(Rect& rc)const;

	//std::vector<ActRect> GetAcutRect()const;

	//Position2f GetPos()const;

	CharacterObject();
	virtual ~CharacterObject();

	Vector2f GetPos()const;
};

