#pragma once
#include "Geometry.h"
#include <memory>
#include <vector>

const int SHOT_MAX = 2000;

class Player;
class Peripheral;

enum class SHOT_PTN
{
	NON,
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
	Vector2 pos;
	Vector2 vel;
	Vector2 Dir;
	int level;
	int ptn;
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

public:
	Shot();
	~Shot();

	void Update();
	void cSHOT(Vector2 pos);
private:
	void setBullet(Vector2 pos,	Vector2 vel,Vector2 Dir,int level,int ptn);
	void Draw(void);
	int SearchBullet(void);
	void OutofScreen(void);
};

