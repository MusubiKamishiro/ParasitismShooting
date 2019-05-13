#pragma once
#include "../Geometry.h"
class Player;

class EnemyActionPattern
{
public:
	EnemyActionPattern();
	~EnemyActionPattern();
	void ActPattern0(Vector2f &pos, float speed, int cnt, int wait);		// ã‰ºˆÚ“®
	void ActPattern1(void);		// ¶‰E‚É—š‚¯‚é
	void ActPattern2(void);		// ©‹@‚É“ÁU‚ğdŠ|‚¯‚é
	void ActPattern3(void);		// ”góˆÚ“®
	void ActPattern4(Vector2f &pos, float speed);		// ‹Câó‘Ô
};
