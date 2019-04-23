#pragma once
#include "Geometry.h"
class Shot
{
private:
	Vector2 pos;
	Vector2 vel;
	Vector2 Dir;

	int img[8];

public:
	Shot();
	~Shot();

	void Update(void);
	void Draw(void);
};

