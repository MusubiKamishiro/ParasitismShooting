#include "CharacterObject.h"
#include <DxLib.h>


void CharacterObject::ReadActionFile(const char * actionPath)
{
	int h = DxLib::FileRead_open(actionPath, false);
	int hData;		// �i�[���ׂ��ϐ������

	float version = 0.0f;
	DxLib::FileRead_read(&version, sizeof(version), h);

	// DxLib::FileRead_read(�ǂݍ����ޯ̧�̐擪���ڽ, ����(�޲Đ�), ̧�������);
	DxLib::FileRead_read(&hData, sizeof(hData), h);

	std::string FilePath = "";	// ������

	// ػ��ނ��ēǂ�
	FilePath.resize(hData);
	DxLib::FileRead_read(&FilePath[0], hData, h);

	std::string actPath = actionPath;
	// �w�肵���͈͂���납��T�����w�肵��������Ɋ܂܂�镶�����ŏ��ɏo������ʒu��Ԃ�
	// +1���Ȃ���'/'������Ȃ�
	int ipos = actPath.find_last_of('/') + 1;

	// substr(a, b)	a�����ڂ���b�����ڂ̕��������𐶐�
	// ����̏ꍇ�A�擪����find_last_of�Ō����������܂� + ����
	charaData.actData.imgFilePath = actPath.substr(0, ipos) + FilePath;

	int actionCnt = 0;
	DxLib::FileRead_read(&actionCnt, sizeof(actionCnt), h);

	for (int i = 0; i < actionCnt; i++)
	{
		int actionNameSize;
		DxLib::FileRead_read(&actionNameSize, sizeof(actionNameSize), h);

		// ����ݖ����Ƃ��Ă���
		std::string actionName;
		actionName.resize(actionNameSize);
		DxLib::FileRead_read(&actionName[0], actionName.size(), h);

		// ٰ�߂���1�޲�ذ��
		ActionInfo actInfo;
		DxLib::FileRead_read(&actInfo.isLoop, sizeof(actInfo.isLoop), h);

		// ����ް����������擾
		int cutCount = 0;
		DxLib::FileRead_read(&cutCount, sizeof(cutCount), h);
		actInfo.cuts.resize(cutCount);

		// ����ް��ǂݍ���
		for (int a = 0; a < cutCount; a++)
		{
			DxLib::FileRead_read(&actInfo.cuts[a], (sizeof(actInfo.cuts[a]) - sizeof(actInfo.cuts[a].actrects)), h);

			// �U����`�����ް����������擾
			int actrccnt = 0;
			DxLib::FileRead_read(&actrccnt, sizeof(actrccnt), h);

			// ٰ�߂���U����`�����Ȃ���΁A����ȍ~��ٰ�߂̓��e�𽷯�߂���
			if (actrccnt == 0)
			{
				continue;
			}
			actInfo.cuts[a].actrects.resize(actrccnt);
			DxLib::FileRead_read(&actInfo.cuts[a].actrects[0], (sizeof(ActRect) * actrccnt), h);
		}

		// �����ϯ�߂ɓo�^
		charaData.actData.animInfo[actionName] = actInfo;
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
	charaData.charaSize = size;
}

CharacterObject::CharacterObject()
{
	lifeFlag = true;
	shotReady = false;
}


CharacterObject::~CharacterObject()
{
}


void CharacterObject::Draw(int img)
{
	auto& actInfo = charaData.actData.animInfo[nowActionName];
	auto& cut = actInfo.cuts[nowCutIdx];
	auto& rc = cut.rect;
	
	DxLib::DrawRectRotaGraph2F(pos.x, pos.y, rc.Left(), rc.Top(), rc.Width(), rc.Height(), cut.center.x, cut.center.y, charaData.charaSize, 0.0, img, true, false);


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
		DxLib::DrawCircle(rc.center.x * charaData.charaSize + pos.x - (rc.Width() * charaData.charaSize) / 2,
			rc.center.y * charaData.charaSize + pos.y - (rc.Height() * charaData.charaSize) / 2, (rc.Width() * charaData.charaSize) / 2, 0x00ff00, false);
	}
	else if (actrect.rt == RectType::box)
	{
		DxLib::DrawBox(rc.Left() * charaData.charaSize + pos.x, rc.Top() * charaData.charaSize + pos.y,
			rc.Right() * charaData.charaSize + pos.x, rc.Bottom() * charaData.charaSize + pos.y, 0x00ff00, false);
	}
}

Rect CharacterObject::GetRects(Rect& rect)const
{
	Rect rc = rect;
	rc.center.x = rc.center.x * charaData.charaSize + pos.x;
	rc.center.y = rc.center.y * charaData.charaSize + pos.y;
	rc.size.height *= charaData.charaSize;
	rc.size.width *= charaData.charaSize;

	return rc;
}

std::vector<ActRect> CharacterObject::GetActRect() const
{
	return charaData.actData.animInfo.at(nowActionName).cuts[nowCutIdx].actrects;
}

CharaData CharacterObject::GetCharaData() const
{
	return charaData;
}


Vector2f CharacterObject::GetPos() const
{
	return pos;
}

bool CharacterObject::GetLifeFlag() const
{
	return lifeFlag;
}

bool CharacterObject::GetShotReady() const
{
	return charaData.ShotReady;
}
