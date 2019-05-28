#pragma once
#include <memory>
#include <vector>
#include "../Character/CharacterObject.h"
#include "../Geometry.h"

class GameScreen;
class Peripheral;

struct SMALL_BOX
{
	Box box;
	bool drawflag;
};

class HalfResultScene
{
private:
	std::vector<SMALL_BOX> sboxes;	// è¨î†ÇÃèWÇ‹ÇË, âÊñ ëJà⁄Ç…égÇ§
	int boxCnt;
	Vector2 boxlength;
	Vector2 gssize;

	int img;
	Vector2 imgSize;

	std::shared_ptr<GameScreen> gs;

	bool AddBox();
	bool SubBox();

	bool flag;
	bool returnFlag;

public:
	HalfResultScene();
	~HalfResultScene();

	bool Update(const Peripheral& p);
	void Draw();
};

