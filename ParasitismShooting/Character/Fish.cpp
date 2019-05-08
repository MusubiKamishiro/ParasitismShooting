#include "Fish.h"
#include "../Game.h"
#include <DxLib.h>


Fish::Fish(const Player& player) : Enemy(player), player(player)
{
	ReadActionFile("action/fish.act");
	ChangeAction("Idle");

	//pos.x = 0;
	//pos.y = 0;
	//rect = Rect(pos.x, pos.y, 30, 30);

	wait = 60;

	img = DxLib::LoadGraph(actData.imgFilePath.c_str());

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

}
