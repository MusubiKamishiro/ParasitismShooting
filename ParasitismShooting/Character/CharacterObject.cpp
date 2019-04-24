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
//	int hData;		// 格納すべき変数を作る
//
//	float version = 0.0f;
//	DxLib::FileRead_read(&version, sizeof(version), h);
//	assert(version == 1.01f);
//
//	// DxLib::FileRead_read(読み込むﾊﾞｯﾌｧの先頭ｱﾄﾞﾚｽ, ｻｲｽﾞ(ﾊﾞｲﾄ数), ﾌｧｲﾙﾊﾝﾄﾞﾙ);
//	DxLib::FileRead_read(&hData, sizeof(hData), h);
//
//	std::string FilePath = "";	// 初期化
//
//	// ﾘｻｲｽﾞして読む
//	FilePath.resize(hData);
//	DxLib::FileRead_read(&FilePath[0], hData, h);
//
//	std::string actPath = actionPath;
//	// 指定した範囲を後ろから探索し指定した文字列に含まれる文字が最初に出現する位置を返す
//	// +1しないと'/'が入らない
//	int ipos = actPath.find_last_of('/') + 1;
//
//	// substr(a, b)	a文字目からb文字目の部分文字を生成
//	// 今回の場合、先頭からfind_last_ofで見つけた長さまで + する
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
//		// ｱｸｼｮﾝ名をとってくる
//		std::string actionName;
//		actionName.resize(actionNameSize);
//		DxLib::FileRead_read(&actionName[0], actionName.size(), h);
//
//		// ﾙｰﾌﾟだけ1ﾊﾞｲﾄﾘｰﾄﾞ
//		ActionInfo actInfo;
//		DxLib::FileRead_read(&actInfo.isLoop, sizeof(actInfo.isLoop), h);
//
//		// ｶｯﾄﾃﾞｰﾀがいくつか取得
//		int cutCount = 0;
//		DxLib::FileRead_read(&cutCount, sizeof(cutCount), h);
//		actInfo.cuts.resize(cutCount);
//
//		// ｶｯﾄﾃﾞｰﾀ読み込み
//		for (int a = 0; a < cutCount; a++)
//		{
//			DxLib::FileRead_read(&actInfo.cuts[a], (sizeof(actInfo.cuts[a]) - sizeof(actInfo.cuts[a].actrects)), h);
//
//			// 攻撃矩形等のﾃﾞｰﾀがいくつか取得
//			int actrccnt = 0;
//			DxLib::FileRead_read(&actrccnt, sizeof(actrccnt), h);
//
//			// ﾙｰﾌﾟする攻撃矩形等がなければ、これ以降のﾙｰﾌﾟの内容をｽｷｯﾌﾟする
//			if (actrccnt == 0)
//			{
//				continue;
//			}
//			actInfo.cuts[a].actrects.resize(actrccnt);
//			DxLib::FileRead_read(&actInfo.cuts[a].actrects[0], (sizeof(ActRect) * actrccnt), h);
//		}
//		// forﾙｰﾌﾟを使わないやり方↓
//		// DxLib::FileRead_read(&actInfo.cuts[0], sizeof(actInfo.cuts[0]) * cutCount, h);
//
//		// ｱｸｼｮﾝﾏｯﾌﾟに登録
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
//	// .at	読み込み専用になるやつ
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
//	// 中心を変えないように
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
//
//// 幅、高さ、座標を返す
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
