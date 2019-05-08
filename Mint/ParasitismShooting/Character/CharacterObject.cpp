#include "CharacterObject.h"
#include <DxLib.h>


void CharacterObject::ReadActionFile(const char * actionPath)
{

}

CharacterObject::CharacterObject()
{
}


CharacterObject::~CharacterObject()
{
}


void CharacterObject::Draw(int img)
{
	//auto& actInfo = _actionData.animInfo[_nowActionName];
	//auto& cut = actInfo.cuts[_nowCutIdx];
	//auto& rc = cut.rect;
	//// íÜêSÇïœÇ¶Ç»Ç¢ÇÊÇ§Ç…
	//int centerX = _isTurn ? rc.Width() - cut.center.x : cut.center.x;

	//DxLib::DrawRectRotaGraph2(pos.x + cPos.x, cPos.y, rc.Left(), rc.Top(), rc.Width(), rc.Height(), centerX, cut.center.y, 2.0f, 0.0, img, true, _isTurn);

	////////////////////////////////////////////////////////////////////////////////////////////////////////
	rect.center = pos;
	DxLib::DrawExtendGraph(rect.Left(), rect.Top(), rect.Right(), rect.Bottom(), img, true);


#ifdef _DEBUG
	DxLib::DrawBox(pos.x - 2, pos.y - 2, pos.x + 2, pos.y + 2, 0x0000ff, true);
	DebugDraw();
#endif // DEBUG
}

void CharacterObject::DebugDraw()
{
	rect.center = pos;
	DxLib::DrawBox(rect.Left(), rect.Top(), rect.Right(), rect.Bottom(), 0x00ff00, false);
}

Rect CharacterObject::GetRects() const
{
	Rect rc = rect;
	rc.center = pos;

	return rc;
}

Vector2f CharacterObject::GetPos() const
{
	return pos;
}
