#include "Sound.h"
#include <DxLib.h>
#include <assert.h>


Sound::Sound()
{
	bgms.resize(0);
	ses.resize(0);
}


Sound::~Sound()
{
}

void Sound::AddBGM(const char* filename)
{
	std::string s = "sound/BGM/";
	s += filename;
	int h = DxLib::LoadSoundMem(s.c_str());
#ifdef _DEBUG
	assert(h != -1);
#endif
	bool same = false;

	// ìØÇ∂Ç‡ÇÃÇ™Ç†Ç¡ÇΩÇÁì«Ç›çûÇ‹Ç»Ç¢
	for (auto& bgm: bgms)
	{
		if (bgm.soundName == filename)
		{
			same = true;
		}
	}
	if (!same)
	{
		bgms.push_back({ h, filename });
		DxLib::ChangeVolumeSoundMem(100, h);
	}
}

void Sound::AddSE(const char* filename)
{
	std::string s = "sound/SE/";
	s += filename;
	int h = DxLib::LoadSoundMem(s.c_str());
#ifdef _DEBUG
	assert(h != -1);
#endif
	// ìØÇ∂Ç‡ÇÃÇ™Ç†Ç¡ÇΩÇÁì«Ç›çûÇ‹Ç»Ç¢
	bool same = false;

	for (auto& se : ses)
	{
		if (se.soundName == filename)
		{
			same = true;
		}
	}
	if (!same)
	{
		ses.push_back({ h, filename });
		DxLib::ChangeVolumeSoundMem(100, h);
	}
}

void Sound::PlayBGM(const bool& bossflag)
{
	DxLib::PlaySoundMem(bgms.at(0).soundHandle, DX_PLAYTYPE_LOOP, false);
}

void Sound::PlaySE()
{
	DxLib::PlaySoundMem(ses.at(0).soundHandle, DX_PLAYTYPE_BACK, true);
}

void Sound::DeleteBGM()
{
	DxLib::DeleteSoundMem(bgms.at(0).soundHandle);
	bgms.erase(bgms.begin());
}

void Sound::DeleteSoundAll()
{
	for (auto& bgm : bgms)
	{
		DxLib::DeleteSoundMem(bgm.soundHandle);
	}
	for (auto& se : ses)
	{
		DxLib::DeleteSoundMem(se.soundHandle);
	}
}
