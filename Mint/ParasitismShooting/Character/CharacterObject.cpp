#include "CharacterObject.h"
#include <DxLib.h>


void CharacterObject::ReadActionFile(const char * actionPath)
{
	int h = DxLib::FileRead_open(actionPath, false);
	int hData;		// Ši”[‚·‚×‚«•Ï”‚ğì‚é

	float version = 0.0f;
	DxLib::FileRead_read(&version, sizeof(version), h);

	// DxLib::FileRead_read(“Ç‚İ‚ŞÊŞ¯Ì§‚Ìæ“ª±ÄŞÚ½, »²½Ş(ÊŞ²Ä”), Ì§²ÙÊİÄŞÙ);
	DxLib::FileRead_read(&hData, sizeof(hData), h);

	std::string FilePath = "";	// ‰Šú‰»

	// Ø»²½Ş‚µ‚Ä“Ç‚Ş
	FilePath.resize(hData);
	DxLib::FileRead_read(&FilePath[0], hData, h);

	std::string actPath = actionPath;
	// w’è‚µ‚½”ÍˆÍ‚ğŒã‚ë‚©‚ç’Tõ‚µw’è‚µ‚½•¶š—ñ‚ÉŠÜ‚Ü‚ê‚é•¶š‚ªÅ‰‚ÉoŒ»‚·‚éˆÊ’u‚ğ•Ô‚·
	// +1‚µ‚È‚¢‚Æ'/'‚ª“ü‚ç‚È‚¢
	int ipos = actPath.find_last_of('/') + 1;

	// substr(a, b)	a•¶š–Ú‚©‚çb•¶š–Ú‚Ì•”•ª•¶š‚ğ¶¬
	// ¡‰ñ‚Ìê‡Aæ“ª‚©‚çfind_last_of‚ÅŒ©‚Â‚¯‚½’·‚³‚Ü‚Å + ‚·‚é
	actData.imgFilePath = actPath.substr(0, ipos) + FilePath;

	int actionCnt = 0;
	DxLib::FileRead_read(&actionCnt, sizeof(actionCnt), h);

	for (int i = 0; i < actionCnt; i++)
	{
		int actionNameSize;
		DxLib::FileRead_read(&actionNameSize, sizeof(actionNameSize), h);

		// ±¸¼®İ–¼‚ğ‚Æ‚Á‚Ä‚­‚é
		std::string actionName;
		actionName.resize(actionNameSize);
		DxLib::FileRead_read(&actionName[0], actionName.size(), h);

		// Ù°Ìß‚¾‚¯1ÊŞ²ÄØ°ÄŞ
		ActionInfo actInfo;
		DxLib::FileRead_read(&actInfo.isLoop, sizeof(actInfo.isLoop), h);

		// ¶¯ÄÃŞ°À‚ª‚¢‚­‚Â‚©æ“¾
		int cutCount = 0;
		DxLib::FileRead_read(&cutCount, sizeof(cutCount), h);
		actInfo.cuts.resize(cutCount);

		// ¶¯ÄÃŞ°À“Ç‚İ‚İ
		for (int a = 0; a < cutCount; a++)
		{
			DxLib::FileRead_read(&actInfo.cuts[a], (sizeof(actInfo.cuts[a]) - sizeof(actInfo.cuts[a].actrects)), h);

			// UŒ‚‹éŒ`“™‚ÌÃŞ°À‚ª‚¢‚­‚Â‚©æ“¾
			int actrccnt = 0;
			DxLib::FileRead_read(&actrccnt, sizeof(actrccnt), h);

			// Ù°Ìß‚·‚éUŒ‚‹éŒ`“™‚ª‚È‚¯‚ê‚ÎA‚±‚êˆÈ~‚ÌÙ°Ìß‚Ì“à—e‚ğ½·¯Ìß‚·‚é
			if (actrccnt == 0)
			{
				continue;
			}
			actInfo.cuts[a].actrects.resize(actrccnt);
			DxLib::FileRead_read(&actInfo.cuts[a].actrects[0], (sizeof(ActRect) * actrccnt), h);
		}

		// ±¸¼®İÏ¯Ìß‚É“o˜^
		actData.animInfo[actionName] = actInfo;
	}
	DxLib::FileRead_close(h);
}

void CharacterObject::ChangeAction(const char * name)
{
	flame = 0;
	nowCutIdx = 0;
	nowActionName = name;
}

void CharacterObject::SetCharaSize(const float& size)
{
	charaSize = size;
}

CharacterObject::CharacterObject()
{
	lifeFlag = true;
}


CharacterObject::~CharacterObject()
{
}


void CharacterObject::Draw(int img)
{
	auto& actInfo = actData.animInfo[nowActionName];
	auto& cut = actInfo.cuts[nowCutIdx];
	auto& rc = cut.rect;
	
	DxLib::DrawRectRotaGraph2F(pos.x, pos.y, rc.Left(), rc.Top(), rc.Width(), rc.Height(), cut.center.x, cut.center.y, charaSize, 0.0, img, true, false);


#ifdef _DEBUG
	//DxLib::DrawBox(pos.x - 2, pos.y - 2, pos.x + 2, pos.y + 2, 0x0000ff, true);

	for (auto& actrect : cut.actrects)
	{
		DebugDraw(actrect);
	}
#endif // DEBUG
}

void CharacterObject::DebugDraw(ActRect actrect)
{
	auto rc = actrect.rc;

	if (actrect.rt == RectType::circle)
	{
		DxLib::DrawCircle(rc.center.x * charaSize + pos.x - (rc.Width() * charaSize) / 2, rc.center.y * charaSize + pos.y - (rc.Height() * charaSize) / 2, (rc.Width() * charaSize) / 2, 0x00ff00, false);
	}
	else if (actrect.rt == RectType::box)
	{
		DxLib::DrawBox(rc.Left() * charaSize + pos.x, rc.Top() * charaSize + pos.y, rc.Right() * charaSize + pos.x, rc.Bottom() * charaSize + pos.y, 0x00ff00, false);
	}
}

Rect CharacterObject::GetRects(Rect& rect)const
{
	Rect rc = rect;
	rc.center.x = rc.center.x * charaSize + pos.x;
	rc.center.y = rc.center.y * charaSize + pos.y;
	rc.size.height *= charaSize;
	rc.size.width *= charaSize;

	return rc;
}

std::vector<ActRect> CharacterObject::GetActRect() const
{
	return actData.animInfo.at(nowActionName).cuts[nowCutIdx].actrects;
}

ActionData CharacterObject::GetActionData() const
{
	return actData;
}

Vector2f CharacterObject::GetPos() const
{
	return pos;
}

int CharacterObject::GetHP() const
{
	return HP;
}

int CharacterObject::GetSP() const
{
	return SP;
}

int CharacterObject::GetImg() const
{
	return img;
}

float CharacterObject::GetCharaSize() const
{
	return charaSize;
}

bool CharacterObject::GetLifeFlag() const
{
	return lifeFlag;
}
