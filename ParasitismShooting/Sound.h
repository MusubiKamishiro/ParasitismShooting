#pragma once
#include <vector>
#include <string>

struct SoundData
{
	int soundHandle;
	std::string soundName;
};

class Sound
{
private:
	Sound();						// �����֎~
	Sound(const Sound&);			// ��߰�֎~
	void operator=(const Sound&);	// ����֎~

	std::vector<SoundData> bgms;
	std::vector<SoundData> ses;

public:
	// �ݸ���ݲ���̪��
	static Sound& Instance()
	{
		static Sound instance;
		return instance;
	}
	~Sound();

	void AddBGM(const char* filename);
	void AddSE(const char* filename);

	void PlayBGM(const bool& bossflag);
	void PlaySE();

	void DeleteBGM();

	void DeleteSoundAll();
};

