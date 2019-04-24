#pragma once


// 型が未確定のまま使える(使うときに型が決定する)
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

// 整数型ﾍﾞｸﾄﾙ
typedef Vector2D<int> Vector2;

// 実数型ﾍﾞｸﾄﾙ
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

	Vector2f pos;	// 座標
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

