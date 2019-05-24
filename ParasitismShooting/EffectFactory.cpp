#include "EffectFactory.h"
#include "DieEffect.h"


EffectFactory::EffectFactory()
{
	originalEffect["dieEffect"] = new DieEffect();
}


EffectFactory::~EffectFactory()
{
}

Effect * EffectFactory::Create(const char * effectname, const char * effecttype, Vector2f pos, int starttime, int drawtime)
{
	if (originalEffect.find(effectname) != originalEffect.end())
	{
		auto effect = originalEffect[effectname]->Clone();
		effect->pos = pos;
		effect->effectType = effecttype;
		effect->startTime = starttime;
		effect->drawTime = drawtime;
		legion.push_back(effect);

		return effect;
	}

	return nullptr;
}

EffLegion & EffectFactory::GetLegion()
{
	return legion;
}

void EffectFactory::EffectDelete()
{
	for (int i = 0; i < legion.size(); ++i)
	{
		auto effect = *std::next(legion.begin(), i);
		if (effect->time == effect->drawTime)
		{
			legion.erase(std::next(legion.begin(), i));
			--i;
		}
	}
}
