#pragma once
#include "Geometry.h"
#include "Character/CharacterObject.h"

enum class RectCombi {
	nothingcombi,		// コンビなし
	circleANDcircle,	// 〇と〇
	circleANDbox,		// 〇と□
	boxANDcircle,		// □と〇
	boxANDbox,			// □と□
};

// 当たり判定ｸﾗｽ
class CollisionDetector
{
public:
	CollisionDetector();
	~CollisionDetector();

	// 2つの矩形の組み合わせを調べる
	RectCombi GetRectCombi(const RectType& rtA, const RectType& rtB);

	// 当たり判定
	bool IsCollision(const Rect& rcA ,const Rect& rcB, const RectCombi& rcombi);
};
