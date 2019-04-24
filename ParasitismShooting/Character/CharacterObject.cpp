#include "CharacterObject.h"
#include <DxLib.h>
//#include <cassert>
//#include "Camera.h"


//void CharacterObject::ChangeAction(const char * name)
//{
//	_flame = 0;
//	_nowCutIdx = 0;
//	_nowActionName = name;
//}
//
//bool CharacterObject::ProceedAnimationFile()
//{
//	if (_flame < _actionData.animInfo[_nowActionName].cuts[_nowCutIdx].duration)
//	{
//		_flame++;
//	}
//	else
//	{
//		_flame = 0;
//		if (_nowCutIdx < _actionData.animInfo[_nowActionName].cuts.size() - 1)
//		{
//			_nowCutIdx++;
//		}
//		else
//		{
//			if (_actionData.animInfo[_nowActionName].isLoop)
//			{
//				_nowCutIdx = 0;
//			}
//			else
//			{
//				return true;
//			}
//		}
//	}
//	return false;
//}
//
//void CharacterObject::ReadActionFile(const char * actionPath)
//{
//	int h = DxLib::FileRead_open(actionPath, false);
//	int hData;		// �i�[���ׂ��ϐ������
//
//	float version = 0.0f;
//	DxLib::FileRead_read(&version, sizeof(version), h);
//	assert(version == 1.01f);
//
//	// DxLib::FileRead_read(�ǂݍ����ޯ̧�̐擪���ڽ, ����(�޲Đ�), ̧�������);
//	DxLib::FileRead_read(&hData, sizeof(hData), h);
//
//	std::string FilePath = "";	// ������
//
//	// ػ��ނ��ēǂ�
//	FilePath.resize(hData);
//	DxLib::FileRead_read(&FilePath[0], hData, h);
//
//	std::string actPath = actionPath;
//	// �w�肵���͈͂���납��T�����w�肵��������Ɋ܂܂�镶�����ŏ��ɏo������ʒu��Ԃ�
//	// +1���Ȃ���'/'������Ȃ�
//	int ipos = actPath.find_last_of('/') + 1;
//
//	// substr(a, b)	a�����ڂ���b�����ڂ̕��������𐶐�
//	// ����̏ꍇ�A�擪����find_last_of�Ō����������܂� + ����
//	_actionData.imgFilePath = actPath.substr(0, ipos) + FilePath;
//
//	int actionCnt = 0;
//	DxLib::FileRead_read(&actionCnt, sizeof(actionCnt), h);
//
//	for (int i = 0; i < actionCnt; i++)
//	{
//		int actionNameSize;
//		DxLib::FileRead_read(&actionNameSize, sizeof(actionNameSize), h);
//
//		// ����ݖ����Ƃ��Ă���
//		std::string actionName;
//		actionName.resize(actionNameSize);
//		DxLib::FileRead_read(&actionName[0], actionName.size(), h);
//
//		// ٰ�߂���1�޲�ذ��
//		ActionInfo actInfo;
//		DxLib::FileRead_read(&actInfo.isLoop, sizeof(actInfo.isLoop), h);
//
//		// ����ް����������擾
//		int cutCount = 0;
//		DxLib::FileRead_read(&cutCount, sizeof(cutCount), h);
//		actInfo.cuts.resize(cutCount);
//
//		// ����ް��ǂݍ���
//		for (int a = 0; a < cutCount; a++)
//		{
//			DxLib::FileRead_read(&actInfo.cuts[a], (sizeof(actInfo.cuts[a]) - sizeof(actInfo.cuts[a].actrects)), h);
//
//			// �U����`�����ް����������擾
//			int actrccnt = 0;
//			DxLib::FileRead_read(&actrccnt, sizeof(actrccnt), h);
//
//			// ٰ�߂���U����`�����Ȃ���΁A����ȍ~��ٰ�߂̓��e�𽷯�߂���
//			if (actrccnt == 0)
//			{
//				continue;
//			}
//			actInfo.cuts[a].actrects.resize(actrccnt);
//			DxLib::FileRead_read(&actInfo.cuts[a].actrects[0], (sizeof(ActRect) * actrccnt), h);
//		}
//		// forٰ�߂��g��Ȃ�������
//		// DxLib::FileRead_read(&actInfo.cuts[0], sizeof(actInfo.cuts[0]) * cutCount, h);
//
//		// �����ϯ�߂ɓo�^
//		_actionData.animInfo[actionName] = actInfo;
//	}
//	DxLib::FileRead_close(h);
//}
//
//Position2f CharacterObject::GetPos()const
//{
//	return Position2f(_pos);
//}
//
//std::vector<ActRect> CharacterObject::GetAcutRect()const
//{
//	// .at	�ǂݍ��ݐ�p�ɂȂ���
//	return _actionData.animInfo.at(_nowActionName).cuts[_nowCutIdx].actrects;
//}
//
//void CharacterObject::Draw(int _img)
//{
//	auto cPos = _camera.CalculatePos(_pos);
//
//	auto& actInfo = _actionData.animInfo[_nowActionName];
//	auto& cut = actInfo.cuts[_nowCutIdx];
//	auto& rc = cut.rect;
//	// ���S��ς��Ȃ��悤��
//	int centerX = _isTurn ? rc.Width() - cut.center.x : cut.center.x;
//
//	DxLib::DrawRectRotaGraph2(_pos.x + cPos.x, cPos.y, rc.Left(), rc.Top(), rc.Width(), rc.Height(), centerX, cut.center.y, 2.0f, 0.0, _img, true, _isTurn);
//}
//
//void CharacterObject::DebugDraw()
//{
//	auto cPos = _camera.CalculatePos(_pos);
//
//	auto& actrcInfo = _actionData.animInfo[_nowActionName];
//	auto& rcCut = actrcInfo.cuts[_nowCutIdx];
//
//	// �E���̂��̂������̌`�ɓ���čŏ�����Ō�܂Ō���
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
//
//// ���A�����A���W��Ԃ�
//Rect CharacterObject::GetActionRects(Rect& rc)const
//{
//	Rect rect = rc;
//
//	rect.center.x = _isTurn ? -rect.center.x : rect.center.x;
//	
//	rect.center.x += _pos.x;
//	rect.center.y += _pos.y;
//	rect.size.height *= 2;
//	rect.size.width *= 2;
//
//
//
//	return rect;
//}

CharacterObject::CharacterObject() //: _nowCutIdx(0), _pos(150, 340), _flame(0), _isTurn(false), _camera(camera)
{
}


CharacterObject::~CharacterObject()
{
}
