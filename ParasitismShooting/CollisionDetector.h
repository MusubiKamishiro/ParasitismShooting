#pragma once
#include "Geometry.h"
#include "Character/CharacterObject.h"

// ½θ»θΈΧ½
class CollisionDetector
{
public:
	CollisionDetector();
	~CollisionDetector();

	bool IsCollision(const Rect& rcA ,const Rect& rcB);
};

