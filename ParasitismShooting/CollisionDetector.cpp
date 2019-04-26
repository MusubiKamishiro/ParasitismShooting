#include "CollisionDetector.h"
#include <cmath>


CollisionDetector::CollisionDetector()
{
}


CollisionDetector::~CollisionDetector()
{
}

bool CollisionDetector::IsCollision(const Rect& rcA, const Rect& rcB)
{
	//auto a = (std::abs(rcA.center.x - rcB.center.x));
	//auto b = (rcA.Width() + rcB.Width()) / 2;
	//auto c = (std::abs(rcA.center.y - rcB.center.y));
	//auto d = (rcA.Height() + rcB.Height()) / 2;

	//bool x = false;
	//bool y = false;

	//if (a < b)
	//{
	//	x = true;
	//}
	//if (c < d)
	//{
	//	y = true;
	//}

	//bool z = (x && y);

	//return z;

	return (((std::abs(rcA.center.x - rcB.center.x)) < (rcA.Width() + rcB.Width()) / 2)) && (((std::abs(rcA.center.y - rcB.center.y)) < (rcA.Height() + rcB.Height()) / 2));
}
