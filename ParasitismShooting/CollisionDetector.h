#pragma once
#include "Geometry.h"
#include "Character/CharacterObject.h"

// �����蔻��׽
class CollisionDetector
{
public:
	CollisionDetector();
	~CollisionDetector();

	bool IsCollision(const Rect& rcA ,const Rect& rcB);
};

