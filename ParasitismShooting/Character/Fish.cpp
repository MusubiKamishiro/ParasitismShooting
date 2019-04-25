#include "Fish.h"
#include "../Game.h"
#include <DxLib.h>


Fish::Fish(const Player& player) : Enemy(player), player(player)
{
	//_nowActionName = ("Walk");

	pos.x = 0;
	pos.y = 0;
	rect = Rect(15, 15, 30, 30);

	wait = 60;

	//ReadActionFile("Action/deadman.act");

	//img = DxLib::LoadGraph(_actionData.imgFilePath.c_str());
	img = DxLib::LoadGraph("img/fish.png");

	updater = &Fish::Move;
}

Fish::Fish(const Fish& d) : Enemy(d.player), player(player)
{
	*this = d;
}

void Fish::operator=(const Fish& d)
{
	memcpy(this, &d, sizeof(Fish));
}

Enemy * Fish::Clone()
{
	return new Fish(*this);
}

void Fish::Move()
{
}

Fish::~Fish()
{
}

void Fish::Update()
{
	//ProceedAnimationFile();

	(this->*updater)();
}

void Fish::Draw()
{
	CharacterObject::Draw(img);

#ifdef _DEBUG
	//DebugDraw();
#endif
}
