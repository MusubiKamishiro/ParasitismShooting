#pragma once


// Œ^‚ª–¢Šm’è‚Ì‚Ü‚Üg‚¦‚é(g‚¤‚Æ‚«‚ÉŒ^‚ªŒˆ’è‚·‚é)
template<typename T>
struct Vector2D
{
	Vector2D() : x(0), y(0) {}
	Vector2D(T inx, T iny) : x(inx), y(iny) {}
	T x;
	T y;

	Vector2D<T> operator+(const Vector2D<T>& in)
	{
		return Vector2D<T>(in.x + x, in.y + y);
	}
	void operator+=(const Vector2D<T>& in)
	{
		x += in.x;
		y += in.y;
	}
	void operator-=(const Vector2D<T>& in)
	{
		x -= in.x;
		y -= in.y;
	}
	void operator/=(const T& in)
	{
		x /= in;
		y /= in;
	}
	bool operator==(const Vector2D<T>& in)const
	{
		return ((x == in.x) && (y == in.y));
	}
	bool operator!=(const Vector2D<T>& in)const
	{
		return ((x != in.x) || (y != in.y));
	}
	bool operator|=(const Vector2D<T>& in)const
	{
		return ((x == in.x) || (y == in.y));
	}
};

// ®”Œ^ÍŞ¸ÄÙ
typedef Vector2D<int> Vector2;

// À”Œ^ÍŞ¸ÄÙ
typedef Vector2D<float> Vector2f;


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

	Vector2f pos;	// À•W
	int radius;		// ”¼Œa

	// ‘¼‚Ì‰~‚Æ‚Ì“–‚½‚è”»’è
	// @param True...“–‚½‚Á‚Ä‚é, False...“–‚½‚Á‚Ä‚È‚¢
	bool HitCircle(Circle& c);
	
};

class Geometry
{
public:
	Geometry();
	~Geometry();
};

