#pragma once
#include "Geometry.h"

// �����蔻��׽
class CollisionDetector
{
public:
	CollisionDetector();
	~CollisionDetector();

	bool IsCollision(const Rect& rcA ,const Rect& rcB);
};

