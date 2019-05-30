#pragma once
#include "Geometry.h"

class Score
{
private:
	Score();						// �����֎~
	Score(const Score&);			// ��߰�֎~
	void operator=(const Score&);	// ����֎~

	unsigned int nowScore;		// ���݂̃X�R�A
	unsigned int upScore;		// �X�R�A�̏㏸�l
	unsigned int highScore;		// ���̍ō��X�R�A
	

public:
	static Score& Instance()
	{
		static Score instance;
		return instance;
	}
	~Score();

	void Update();
	void Draw(const Vector2& pos);

	// �X�R�A�̏�����, �R���e�B�j���[���Ɏg��
	void InitScore();

	void AddScore(const unsigned int& inscore);

	// �X�e�[�W�N���A�{�[�i�X
	void AddClearBonus(const unsigned int& stagenum, const unsigned int& parasnum, const int& bosshp, const unsigned int& ccount, const int& diff);
	
	unsigned int GetNowScore()const;
	unsigned int GetHighScore()const;

	unsigned int stageBonus;
	unsigned int parasBonus;
	unsigned int bossHpBonus;
	int contBonus;
	float diffBonus;
	int bonusScore;
};

