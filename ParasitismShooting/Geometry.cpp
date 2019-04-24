#include "Geometry.h"
#include <cmath>


Geometry::Geometry()
{
}


Geometry::~Geometry()
{
}


Box::Box(Vector2f invecA, Vector2f invecB)
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
			dotA = Vector2f(invecA.x, invecB.y);
			dotB = Vector2f(invecB.x, invecA.y);
		}
	}
	else
	{
		if (invecA.y < invecB.y)
		{
			dotA = Vector2f(invecB.x, invecA.y);
			dotB = Vector2f(invecA.x, invecB.y);
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
			dotA = Vector2f(ax, ay);
			dotB = Vector2f(bx, by);
		}
		else
		{
			dotA = Vector2f(ax, by);
			dotB = Vector2f(bx, ay);
		}
	}
	else
	{
		if (by < by)
		{
			dotA = Vector2f(bx, ay);
			dotB = Vector2f(ax, by);
		}
		else
		{
			dotA = Vector2f(bx, by);
			dotB = Vector2f(ax, ay);
		}

	}
}


bool Circle::HitCircle(Circle& c)
{
	Vector2f line = Vector2f(std::abs(c.pos.x - pos.x), std::abs(c.pos.y - pos.y));

	float distance = std::pow(line.x, 2.0) + std::pow(line.y, 2.0);
	distance = std::sqrt(distance);
	
	if(distance < radius + c.radius)
	{ 
		return true;
	}

	return false;
}
