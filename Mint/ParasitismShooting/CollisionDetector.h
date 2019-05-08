#pragma once
#include "Geometry.h"

// “–‚½‚è”»’è¸×½
class CollisionDetector
{
public:
	CollisionDetector();
	~CollisionDetector();

	bool IsCollision(const Rect& rcA ,const Rect& rcB);
};

