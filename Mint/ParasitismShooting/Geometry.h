#pragma once

struct Vector2
{
	Vector2() : x(0), y(0) {}
	Vector2(float inx, float iny) : x(inx), y(iny) {}
	float x;
	float y;

	Vector2 operator+(const Vector2& in)
	{
		return Vector2(in.x + x, in.y + y);
	}
	void operator+=(const Vector2& in)
	{
		x += in.x;
		y += in.y;
	}
	void operator-=(const Vector2& in)
	{
		x -= in.x;
		y -= in.y;
	}
	void operator/=(const float& in)
	{
		x /= in;
		y /= in;
	}
	bool operator==(const Vector2& in)const
	{
		return ((x == in.x) && (y == in.y));
	}
	bool operator!=(const Vector2& in)const
	{
		return ((x != in.x) || (y != in.y));
	}
	bool operator|=(const Vector2& in)const
	{
		return ((x == in.x) || (y == in.y));
	}
};


struct Box
{
	Box() : dotA(0, 0), dotB(0, 0) {};
	Box(Vector2 invecA, Vector2 invecB);
	Box(int ax, int ay, int bx, int by);

	Vector2 dotA;
	Vector2 dotB;

	bool operator==(const Box& box)
	{
		return ((box.dotA == dotA) && (box.dotB == dotB));
	}
};

struct Circle
{
	Circle() : pos(0, 0), radius(0) {};
	Circle(Vector2 invec, int inr) : pos(invec), radius(inr) {};

	Vector2 pos;	// 座標
	int radius;		// 半径

	// 他の円との当たり判定
	// @param True...当たってる, False...当たってない
	bool HitCircle(Circle& c);
	
};

class Geometry
{
public:
	Geometry();
	~Geometry();
};

