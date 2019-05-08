#include "CharacterObject.h"
#include <DxLib.h>


void CharacterObject::ReadActionFile(const char * actionPath)
{
	int h = DxLib::FileRead_open(actionPath, false);
	int hData;		// 格納すべき変数を作る

	float version = 0.0f;
	DxLib::FileRead_read(&version, sizeof(version), h);

	// DxLib::FileRead_read(読み込むﾊﾞｯﾌｧの先頭ｱﾄﾞﾚｽ, ｻｲｽﾞ(ﾊﾞｲﾄ数), ﾌｧｲﾙﾊﾝﾄﾞﾙ);
	DxLib::FileRead_read(&hData, sizeof(hData), h);

	std::string FilePath = "";	// 初期化

	// ﾘｻｲｽﾞして読む
	FilePath.resize(hData);
	DxLib::FileRead_read(&FilePath[0], hData, h);

	std::string actPath = actionPath;
	// 指定した範囲を後ろから探索し指定した文字列に含まれる文字が最初に出現する位置を返す
	// +1しないと'/'が入らない
	int ipos = actPath.find_last_of('/') + 1;

	// substr(a, b)	a文字目からb文字目の部分文字を生成
	// 今回の場合、先頭からfind_last_ofで見つけた長さまで + する
	actData.imgFilePath = actPath.substr(0, ipos) + FilePath;

	int actionCnt = 0;
	DxLib::FileRead_read(&actionCnt, sizeof(actionCnt), h);

	for (int i = 0; i < actionCnt; i++)
	{
		int actionNameSize;
		DxLib::FileRead_read(&actionNameSize, sizeof(actionNameSize), h);

		// ｱｸｼｮﾝ名をとってくる
		std::string actionName;
		actionName.resize(actionNameSize);
		DxLib::FileRead_read(&actionName[0], actionName.size(), h);

		// ﾙｰﾌﾟだけ1ﾊﾞｲﾄﾘｰﾄﾞ
		ActionInfo actInfo;
		DxLib::FileRead_read(&actInfo.isLoop, sizeof(actInfo.isLoop), h);

		// ｶｯﾄﾃﾞｰﾀがいくつか取得
		int cutCount = 0;
		DxLib::FileRead_read(&cutCount, sizeof(cutCount), h);
		actInfo.cuts.resize(cutCount);

		// ｶｯﾄﾃﾞｰﾀ読み込み
		for (int a = 0; a < cutCount; a++)
		{
			DxLib::FileRead_read(&actInfo.cuts[a], (sizeof(actInfo.cuts[a]) - sizeof(actInfo.cuts[a].actrects)), h);

			// 攻撃矩形等のﾃﾞｰﾀがいくつか取得
			int actrccnt = 0;
			DxLib::FileRead_read(&actrccnt, sizeof(actrccnt), h);

			// ﾙｰﾌﾟする攻撃矩形等がなければ、これ以降のﾙｰﾌﾟの内容をｽｷｯﾌﾟする
			if (actrccnt == 0)
			{
				continue;
			}
			actInfo.cuts[a].actrects.resize(actrccnt);
			DxLib::FileRead_read(&actInfo.cuts[a].actrects[0], (sizeof(ActRect) * actrccnt), h);
		}
		// forﾙｰﾌﾟを使わないやり方↓
		// DxLib::FileRead_read(&actInfo.cuts[0], sizeof(actInfo.cuts[0]) * cutCount, h);

		// ｱｸｼｮﾝﾏｯﾌﾟに登録
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
	//// 中心を変えないように
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
