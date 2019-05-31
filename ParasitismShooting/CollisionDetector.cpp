#include "CollisionDetector.h"
#include <cmath>
#include <DxLib.h>
#include <cassert>


CollisionDetector::CollisionDetector()
{
}


CollisionDetector::~CollisionDetector()
{
}

RectCombi CollisionDetector::GetRectCombi(const RectType& rtA, const RectType& rtB)
{
	if (rtA == RectType::circle)
	{
		if (rtB == RectType::circle)
		{
			return RectCombi::circleANDcircle;
		}
		else if (rtB == RectType::box)
		{
			return RectCombi::circleANDbox;
		}
	}
	else if(rtA == RectType::box)
	{
		if (rtB == RectType::circle)
		{
			return RectCombi::boxANDcircle;
		}
		else if (rtB == RectType::box)
		{
			return RectCombi::boxANDbox;
		}
	}

	return RectCombi::nothingcombi;
}

bool CollisionDetector::IsCollision(const Rect& rcA, const Rect& rcB, const RectCombi& rcombi)
{
	assert(rcombi != RectCombi::nothingcombi);

	if (rcombi == RectCombi::circleANDcircle)
	{
		float a = std::abs(rcA.center.x - rcB.center.x);
		float b = std::abs(rcA.center.y - rcB.center.y);
		return ((rcA.Height() / 2 + rcB.Height() / 2) > std::hypot(a, b));
	}
	else if (rcombi == RectCombi::circleANDbox)
	{
		return false;
	}
	else if (rcombi == RectCombi::boxANDcircle)
	{
		return false;
	}
	else if (rcombi == RectCombi::boxANDbox)
	{
		return (((std::abs(rcA.center.x - rcB.center.x)) < (rcA.Width() + rcB.Width()) / 2) && ((std::abs(rcA.center.y - rcB.center.y)) < (rcA.Height() + rcB.Height()) / 2));
	}

	return false;
}
