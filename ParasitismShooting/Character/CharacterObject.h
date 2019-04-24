#pragma once
//#include <string>
#include <vector>
//#include <map>
#include "../Geometry.h"

class Camera;


// ｷｬﾗｸﾀｰ基底ｸﾗｽ
class CharacterObject
{
protected:
	//Vector2f _vel;		// 自分の速度
	//Rect _rect;			// 中心、幅と高さ

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
	//Position2f _pos;	// 自分の座標

	//const Camera& _camera;

public:
	//const float g = 0.5f;	// 間に合わせ


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
};

