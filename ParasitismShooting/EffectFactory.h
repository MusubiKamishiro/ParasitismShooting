#pragma once
#include "Geometry.h"
#include <list>
#include <map>

class Effect;

typedef std::list<Effect*> EffLegion;

class EffectFactory
{
private:
	std::map<std::string, Effect*> originalEffect;	// �G�̌��ƂȂ�map�̍쐬
	EffLegion legion;

public:
	EffectFactory();
	~EffectFactory();

	Effect* Create(const char * effectname, const char * effecttype, Vector2f pos, int starttime, int drawtime);

	// �G�̏W���̂�Ԃ�
	EffLegion& GetLegion();
	void EffectDelete();
};

