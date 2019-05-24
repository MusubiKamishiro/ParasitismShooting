#include "DieEffect.h"
#include "EffectFactory.h"
#include <DxLib.h>


DieEffect::DieEffect() : Effect()
{
	effect = DxLib::LoadGraph("img/eff1.png");
}

DieEffect::DieEffect(const DieEffect& d) : Effect()
{
	*this = d;
}

void DieEffect::operator=(const DieEffect & d)
{
	memcpy(this, &d, sizeof(DieEffect));
}

Effect * DieEffect::Clone()
{
	return new DieEffect(*this);
}


DieEffect::~DieEffect()
{
}

void DieEffect::Update(const int& t)
{
	time = t - startTime;
}

void DieEffect::Draw()
{
	float size = time / (float)drawTime;

	float b = (drawTime - time) * 8;

	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, (b));
	DxLib::SetDrawBright(0, 255, 0);
	DxLib::DrawRotaGraph(pos.x, pos.y, size, size, effect, true);
	DxLib::SetDrawBright(255, 255, 255);

	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}
