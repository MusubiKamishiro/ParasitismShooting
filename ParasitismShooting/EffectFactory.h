#pragma once
#include "Geometry.h"
#include <list>
#include <map>

class Effect;

typedef std::list<Effect*> EffLegion;

class EffectFactory
{
private:
	std::map<std::string, Effect*> originalEffect;	// “G‚ÌŒ³‚Æ‚È‚émap‚Ìì¬
	EffLegion legion;

public:
	EffectFactory();
	~EffectFactory();

	Effect* Create(const char * effectname, const char * effecttype, Vector2f pos, int starttime, int drawtime);

	// “G‚ÌW‡‘Ì‚ğ•Ô‚·
	EffLegion& GetLegion();
	void EffectDelete();
};

