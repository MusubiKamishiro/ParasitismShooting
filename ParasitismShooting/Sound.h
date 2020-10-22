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
	Sound(const Sound&);			// �R�s�[�֎~
	void operator=(const Sound&);	// ����֎~

	std::vector<SoundData> bgms;
	std::vector<SoundData> ses;

public:
	static Sound& Instance()
	{
		static Sound instance;
		return instance;
	}
	~Sound();

	void AddBGM(const std::string& filename);
	void AddSE(const std::string& filename);

	void PlayBGM(const bool& bossflag);
	void PlaySE(const std::string& name);

	void DeleteBGM();

	void DeleteSoundAll();
};
