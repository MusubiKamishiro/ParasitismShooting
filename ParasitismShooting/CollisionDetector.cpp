#include "CollisionDetector.h"
#include <cmath>
#include <DxLib.h>


CollisionDetector::CollisionDetector()
{
}


CollisionDetector::~CollisionDetector()
{
}

bool CollisionDetector::IsCollision(const Rect& rcA, const Rect& rcB)
{
	return (((std::abs(rcA.center.x - rcB.center.x)) < (rcA.Width() + rcB.Width()) / 2) && ((std::abs(rcA.center.y - rcB.center.y)) < (rcA.Height() + rcB.Height()) / 2));
}
