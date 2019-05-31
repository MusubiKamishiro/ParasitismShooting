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
	Sound();						// ê∂ê¨ã÷é~
	Sound(const Sound&);			// ∫Àﬂ∞ã÷é~
	void operator=(const Sound&);	// ë„ì¸ã÷é~

	std::vector<SoundData> bgms;
	std::vector<SoundData> ses;

public:
	// º›∏ﬁŸƒ›≤›¿∞Ã™∞Ω
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

