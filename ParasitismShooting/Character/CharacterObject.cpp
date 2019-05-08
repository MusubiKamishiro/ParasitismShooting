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
	actData.imgFilePath = actPath.substr(0, ipos) + FilePath;

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
		// forٰ�߂��g��Ȃ�������
		// DxLib::FileRead_read(&actInfo.cuts[0], sizeof(actInfo.cuts[0]) * cutCount, h);

		// �����ϯ�߂ɓo�^
		actData.animInfo[actionName] = actInfo;
	}
	DxLib::FileRead_close(h);
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
	//// ���S��ς��Ȃ��悤��
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
