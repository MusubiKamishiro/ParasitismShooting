#pragma once
#include "Geometry.h"
#include "Character/CharacterObject.h"

// “–‚½‚è”»’è¸×½
class CollisionDetector
{
public:
	CollisionDetector();
	~CollisionDetector();

	bool IsCollision(const Rect& rcA ,const Rect& rcB);
};

