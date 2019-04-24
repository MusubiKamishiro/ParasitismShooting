#pragma once

struct Vector2
{
	Vector2() : x(0), y(0) {}
	Vector2(int inx, int iny) : x(inx), y(iny) {}
	int x;
	int y;

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
	bool operator==(const Vector2& in)const
	{
		return ((x == in.x) && (y == in.y));
	}
	bool operator!=(const Vector2& in)const
	{
		return ((x != in.x) || (y != in.y));
	}
};

struct Vector2f
{
	Vector2f() : x(0), y(0) {}
	Vector2f(float inx, float iny) : x(inx), y(iny) {}
	float x;
	float y;

	Vector2f operator+(const Vector2f& in)
	{
		return Vector2f(in.x + x, in.y + y);
	}
	void operator+=(const Vector2f& in)
	{
		x += in.x;
		y += in.y;
	}
	void operator-=(const Vector2f& in)
	{
		x -= in.x;
		y -= in.y;
	}
	void operator/=(const float& in)
	{
		x /= in;
		y /= in;
	}
	bool operator==(const Vector2f& in)const
	{
		return ((x == in.x) && (y == in.y));
	}
	bool operator!=(const Vector2f& in)const
	{
		return ((x != in.x) || (y != in.y));
	}
	bool operator|=(const Vector2f& in)const
	{
		return ((x == in.x) || (y == in.y));
	}
};


struct Box
{
	Box() : dotA(0, 0), dotB(0, 0) {};
	Box(Vector2f invecA, Vector2f invecB);
	Box(int ax, int ay, int bx, int by);

	Vector2f dotA;
	Vector2f dotB;

	bool operator==(const Box& box)
	{
		return ((box.dotA == dotA) && (box.dotB == dotB));
	}
};

struct Circle
{
	Circle() : pos(0, 0), radius(0) {};
	Circle(Vector2f invec, int inr) : pos(invec), radius(inr) {};

	Vector2f pos;	// ç¿ïW
	int radius;		// îºåa

	// ëºÇÃâ~Ç∆ÇÃìñÇΩÇËîªíË
	// @param True...ìñÇΩÇ¡ÇƒÇÈ, False...ìñÇΩÇ¡ÇƒÇ»Ç¢
	bool HitCircle(Circle& c);
	
};

class Geometry
{
public:
	Geometry();
	~Geometry();
};

