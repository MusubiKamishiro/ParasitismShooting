#pragma once
//#include <string>
#include <vector>
#include <map>
#include "../Geometry.h"


// ｱｸｼｮﾝ矩形定義
struct ActRect
{
	RectType rt;	// 矩形の形
	Rect rc;		// 幅,高さ
};

// 切り抜き情報
struct CutInfo
{
	Rect rect;						// 切り抜き矩形
	Vector2 center;					// 中心点
	int duration;					// 表示時間		// ここまで28ﾊﾞｲﾄ
	std::vector<ActRect> actrects;	// ｱｸｼｮﾝ矩形
};// 44ﾊﾞｲﾄ
typedef std::vector<CutInfo> CutInfoes_t;

struct ActionInfo {
	bool isLoop;				// ﾙｰﾌﾟする
	CutInfoes_t cuts;			// ｶｯﾄ情報配列
};
struct ActionData {
	std::string imgFilePath;					// 画像ﾌｧｲﾙﾊﾟｽ
	std::map<std::string, ActionInfo> animInfo;	// ｱｸｼｮﾝ情報
};

// ｷｬﾗｸﾀｰ基底ｸﾗｽ
class CharacterObject
{
protected:
	ActionData actData;
	// ﾌｧｲﾙの読み込み
	void ReadActionFile(const char* actionPath);
	// アニメーション切り替え
	void ChangeAction(const char* name);

	void SetCharaSize(const float& size);

	int HP;			// 体力
	int SP;			// スタミナ

	int movePtn;	// 移動パターン
	int cnt;		// キャラクターごとのカウント
	int wait;		// キャラクターごとの待機時間

	bool lifeFlag;	// 生きてるか死んでるか

	Vector2f pos;	// 座標
	Vector2f vel;	// 移動速度
	Rect rect;		// 中心、幅と高さ

	int img;		// 画像
	//shottype
	//bombtype

	std::string nowActionName;	// 現在再生中のｱｸｼｮﾝ名
	unsigned int nowCutIdx;		// 現在表示中のｶｯﾄ番号
	unsigned int flame;			// そのｶｯﾄ番号における経過時間

	float charaSize;

public:
	CharacterObject();
	virtual ~CharacterObject();

	// ｷｬﾗｸﾀｰを表示
	void Draw(int img);
	// 当たり矩形を表示
	void DebugDraw(ActRect actrect);

	// 矩形の情報をもらう
	Rect GetRects(Rect& rect)const;
	std::vector<ActRect> GetActRect()const;

	Vector2f GetPos()const;
	int GetHP()const;
	bool GetLifeFlag()const;
};

