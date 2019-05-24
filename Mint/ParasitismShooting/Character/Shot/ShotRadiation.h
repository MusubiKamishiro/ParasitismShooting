#pragma once
#include "Shot.h"

class EnemyFactory;
class ShotFactory;

class ShotRadiation : public Shot
{
	friend ShotFactory;
private:
	ShotRadiation(const Player& player, const EnemyFactory& enemyfactory/*, const Enemy& enemy*/);
	ShotRadiation(const ShotRadiation&);
	void operator=(const ShotRadiation&);

	Shot* Clone();

	void Move();
	void Delete();
	
	void (ShotRadiation::*updater)();

	const Player& player;
	const EnemyFactory& enemyfactory;

	// ���W(x,y)��(xc,yc)�𒆐S��theta���W�A����]���������W��(*xp,*yp)�ɕԂ��֐�
	void rotation2D(float * xp, float * yp, float x, float y, float xc, float yc, float theta);

	float range;
public:
	~ShotRadiation();

	void Update();
	void Draw();
	
};
