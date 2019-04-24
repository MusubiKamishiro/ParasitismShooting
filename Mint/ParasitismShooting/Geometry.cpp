#include "Geometry.h"
#include <cmath>


Geometry::Geometry()
{
}


Geometry::~Geometry()
{
}


Box::Box(Vector2 invecA, Vector2 invecB)
{
	if (invecA.x < invecB.x)
	{
		if (invecA.y < invecB.y)
		{
			dotA = invecA;
			dotB = invecB;
		}
		else
		{
			dotA = Vector2(invecA.x, invecB.y);
			dotB = Vector2(invecB.x, invecA.y);
		}
	}
	else
	{
		if (invecA.y < invecB.y)
		{
			dotA = Vector2(invecB.x, invecA.y);
			dotB = Vector2(invecA.x, invecB.y);
		}
		else
		{
			dotA = invecB;
			dotB = invecA;
		}
	}
}

Box::Box(int ax, int ay, int bx, int by)
{
	if (ax < bx)
	{
		if (by < by)
		{
			dotA = Vector2(ax, ay);
			dotB = Vector2(bx, by);
		}
		else
		{
			dotA = Vector2(ax, by);
			dotB = Vector2(bx, ay);
		}
	}
	else
	{
		if (by < by)
		{
			dotA = Vector2(bx, ay);
			dotB = Vector2(ax, by);
		}
		else
		{
			dotA = Vector2(bx, by);
			dotB = Vector2(ax, ay);
		}

	}
}


bool Circle::HitCircle(Circle& c)
{
	Vector2 line = Vector2(std::abs(c.pos.x - pos.x), std::abs(c.pos.y - pos.y));

	float distance = std::pow(line.x, 2.0) + std::pow(line.y, 2.0);
	distance = std::sqrt(distance);
	
	if(distance < radius + c.radius)
	{ 
		return true;
	}

	return false;
}
