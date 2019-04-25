#include "CharacterObject.h"
#include <DxLib.h>



//void CharacterObject::DebugDraw()
//{
//	auto cPos = _camera.CalculatePos(_pos);
//
//	auto& actrcInfo = _actionData.animInfo[_nowActionName];
//	auto& rcCut = actrcInfo.cuts[_nowCutIdx];
//
//	// 右側のものを左側の形に入れて最初から最後まで見る
//	for (auto& i : rcCut.actrects)
//	{
//		auto& actRc = i;
//
//		Rect rc = actRc.rc;
//		rc.center.x = _isTurn ? -rc.center.x : rc.center.x;
//
//		DxLib::DrawBox(rc.Left() * 2 + _pos.x + cPos.x, rc.Top() * 2 + _pos.y, rc.Right() * 2 + _pos.x + cPos.x, rc.Bottom() * 2 + _pos.y, 0xff0000, false);
//	}
//}


void CharacterObject::Draw(int img)
{
	//auto& actInfo = _actionData.animInfo[_nowActionName];
	//auto& cut = actInfo.cuts[_nowCutIdx];
	//auto& rc = cut.rect;
	//// 中心を変えないように
	//int centerX = _isTurn ? rc.Width() - cut.center.x : cut.center.x;

	//DxLib::DrawRectRotaGraph2(pos.x + cPos.x, cPos.y, rc.Left(), rc.Top(), rc.Width(), rc.Height(), centerX, cut.center.y, 2.0f, 0.0, img, true, _isTurn);

	////////////////////////////////////////////////////////////////////////////////////////////////////////
	rect.center = pos;
	//if (updater != &Player::Invincible)
	{
		DxLib::DrawExtendGraph(rect.Left(), rect.Top(), rect.Right(), rect.Bottom(), img, true);
	}
	//else
	//{
	//	if ((time / 5) % 2)
	//	{
	//		DxLib::DrawExtendGraph(rect.Left(), rect.Top(), rect.Right(), rect.Bottom(), img, true);
	//	}
	//}

#ifdef _DEBUG
	DxLib::DrawBox(pos.x - 2, pos.y - 2, pos.x + 2, pos.y + 2, 0x0000ff, true);
#endif // DEBUG

}

CharacterObject::CharacterObject()
{
}


CharacterObject::~CharacterObject()
{
}

Vector2f CharacterObject::GetPos() const
{
	return pos;
}
