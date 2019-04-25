#pragma once
#include "Geometry.h"
#include <memory>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

class Player;
class Peripheral;

enum SHOT_PTN
{
	WEAK,
	NORMAL,
	SHOTGUN,
	TRACKING,
	RADIATION,
	RANDOM,
	LASER,
	PTN_MAX

};

typedef struct ShotST
{
	int flag;
	Vector2f pos;
	double angle;
	int Speed;
	int movePtn;
	int level;
	int shotPtn;
}shot_st;

class Shot
{
private:
	Vector2f pos;
	Vector2f vel;
	Vector2f Dir;

	int img[8];
	int cnt;

	int up;
	int right;
	int left;
	int down;

	std::shared_ptr<Player> player;

	bool sFlag[10];

	std::vector<shot_st> cShot;

	int NormalPosPtnX[4] = { -10, 10,-30, 30 };
	int NormalPosPtnY[4] = { -30,-30,-10,-10 };
	double ShotGunAngle[3] = { M_PI / 1.5,M_PI / 2,M_PI / 3 };

	int a, b, c, d;
public:
	Shot();
	~Shot();

	void Update();
	void Draw(void);
	void setBullet(Vector2f pos, float angle, int Speed, int movePtn, int level, int shotPtn);
private:
	void OutofScreen(void);
	double ShotAngle(Vector2f pos);
};

