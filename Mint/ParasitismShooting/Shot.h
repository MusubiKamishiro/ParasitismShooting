#pragma once
#include "Geometry.h"
#include <memory>
#include <vector>

const int SHOT_MAX = 20000;

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

enum MOVE_PTN
{
	FAST,
	SLOW,
	MAX
};

typedef struct ShotST
{
	int flag;
	Vector2 pos;
	Vector2 vel;
	Vector2 Dir;
	int movePtn;
	int level;
	int shotPtn;
}shot_st;

class Shot
{
private:
	Vector2 pos;
	Vector2 vel;
	Vector2 Dir;

	int img[8];
	int cnt;

	int up;
	int right;
	int left;
	int down;

	std::shared_ptr<Player> player;

	bool sFlag[10];

	shot_st cShot[SHOT_MAX];

	int NormalPosPtnX[4];
	int NormalPosPtnY[4];
	int ShotGunPosPtnX[4];
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
	void cSHOT(Vector2 pos,int shotPtn);
	void Draw(void);
private:
	void setBullet(Vector2 pos,	Vector2 vel,Vector2 Dir,int movePtn,int level,int shotPtn);
	int SearchBullet(void);
	void OutofScreen(void);
};

