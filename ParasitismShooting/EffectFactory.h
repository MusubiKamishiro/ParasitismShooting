#pragma once
#include "Geometry.h"
#include <list>
#include <map>
#include <string>

class Effect;

typedef std::list<Effect*> EffLegion;

class EffectFactory
{
private:
	std::map<std::string, Effect*> originalEffect;	// 敵の元となるmapの作成
	EffLegion legion;

public:
	EffectFactory();
	~EffectFactory();

	Effect* Create(const char * effectname, Vector2f pos, int starttime, int drawtime);

	// 敵の集合体を返す
	EffLegion& GetLegion();
	void EffectDelete();
};
