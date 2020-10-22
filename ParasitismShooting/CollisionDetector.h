#pragma once
#include "Geometry.h"
#include "Character/CharacterObject.h"

enum class RectCombi {
	nothingcombi,		// ƒRƒ“ƒr‚È‚µ
	circleANDcircle,	// Z‚ÆZ
	circleANDbox,		// Z‚Æ 
	boxANDcircle,		//  ‚ÆZ
	boxANDbox,			//  ‚Æ 
};

// “–‚½‚è”»’è¸×½
class CollisionDetector
{
public:
	CollisionDetector();
	~CollisionDetector();

	// 2‚Â‚Ì‹éŒ`‚Ì‘g‚İ‡‚í‚¹‚ğ’²‚×‚é
	RectCombi GetRectCombi(const RectType& rtA, const RectType& rtB);

	// “–‚½‚è”»’è
	bool IsCollision(const Rect& rcA ,const Rect& rcB, const RectCombi& rcombi);
};
