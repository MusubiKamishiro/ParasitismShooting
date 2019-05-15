#pragma once
#include "Geometry.h"

class Credit
{
private:
	unsigned int credit;
	const Vector2 ssize;

public:
	Credit();
	~Credit();

	void AddCredit();
	void SubCredit();
	unsigned int GetCredit()const;

	void Draw();
};

