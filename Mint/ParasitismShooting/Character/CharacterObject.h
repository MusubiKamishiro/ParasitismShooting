#pragma once
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

// キャラクターが持つべきデータ
// 寄生の際に使用する
struct CharaData
{
	ActionData actData;		// アクションデータ
	int img;				// 画像
	float charaSize;		// キャラクターの拡大率
	int HP;					// 体力
	int SP;					// スタミナ
	float moveVel;			// 移動量
	const char* shotType;	// 弾の名前
	bool ShotReady;			// ショットを打つかどうかのフラグ
};

// ｷｬﾗｸﾀｰ基底ｸﾗｽ
class CharacterObject
{
protected:
	// ﾌｧｲﾙの読み込み
	void ReadActionFile(const char* actionPath);
	// アニメーション切り替え
	void ChangeAction(const char* name);

	void SetCharaSize(const float& size);


	CharaData charaData;

	int movePtn;	// 移動パターン
	int cnt;		// キャラクターごとのカウント
	int wait;		// キャラクターごとの待機時間

	bool lifeFlag;	// 生きてるか死んでるか
	bool shotReady;

	Vector2f pos;	// 座標
	Vector2f vel;	// 移動速度
	Rect rect;		// 中心、幅と高さ

	//shottype

	std::string nowActionName;	// 現在再生中のｱｸｼｮﾝ名
	unsigned int nowCutIdx;		// 現在表示中のｶｯﾄ番号
	unsigned int flame;			// そのｶｯﾄ番号における経過時間

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
	
	CharaData GetCharaData()const;
	Vector2f GetPos()const;
	bool GetLifeFlag()const;
	bool GetShotReady()const;
};

