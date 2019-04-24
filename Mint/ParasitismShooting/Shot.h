#pragma once
#include "Geometry.h"
#include <memory>
#include <vector>

const int SHOT_MAX = 2000;

class Player;
class Peripheral;

enum SHOT_PTN
{
	WEAK,
	NORMAL,
	SHOTGUN,
	TRACKING,
	RADIATION,
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
	int img[8];
	int cnt;

	int up;
	int right;
	int left;
	int down;

	std::shared_ptr<Player> player;

	bool sFlag[10];

	shot_st cShot[SHOT_MAX];

	int NormalPosPtnX[4] = { -10, 10,-30, 30 };
	int NormalPosPtnY[4] = { -30,-30,-10,-10 };
	int ShotGunPosPtnX[3] = { 10, 80, 0};
	int ShotGunPosPtnY[4];
	int TrackingPosPtnX[4];
	int TrackingPosPtnY[4];
	int RadiationPosPtnX[4];
	int RadiationPosPtnY[4];
	int LaserPosPtnX[4];
	int LaserPosPtnY[4];

public:
	Shot();
	~Shot();

	void Update();
	void cSHOT(Vector2f pos, int level, int shotPtn);
	void Draw(void);
private:
	void setBullet(Vector2f pos, double angle, int Speed, int movePtn, int level, int shotPtn);
	int SearchBullet(void);
	void OutofScreen(void);
};

