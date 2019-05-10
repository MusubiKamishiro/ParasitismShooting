#pragma once
#include "Character/CharacterObject.h"
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
	Vector2f pos;
	double angle;
	int Speed;
	int movePtn;
	int level;
	int shotPtn;
	std::string shotname;
}shot_st;

class Shot : public CharacterObject
{
private:
	int up;
	int right;
	int left;
	int down;

	int interval;

	std::shared_ptr<Player> player;

	std::vector<shot_st> cShot;

	int NormalPosPtnX[4] = { -10, 10,-30, 30 };
	int NormalPosPtnY[4] = { -30,-30,-10,-10 };
	
public:
	Shot();
	~Shot();

	void Update();
	void Draw(void);
	void setBullet(Vector2f pos, float angle, int Speed, int movePtn, int level, int shotPtn);

	void ShotBullet(const Peripheral& p, const Vector2f& pos);
private:
	void OutofScreen(void);
	double ShotAngle(Vector2f pos);
	void NormalUpdate(int n);
	void ShotgunUpdate(int n);
	void TrackingUpdate(int n);
	void RadiationUpdate(int n);
	void RandomUpdate(int n);
	void LaserUpdate(int n);
};

