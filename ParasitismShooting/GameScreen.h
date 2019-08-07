#pragma once
#include <vector>
#include "Geometry.h"


class GameScreen
{
private:
	Vector2 luPos;		// �Q�[����ʂ̍���̍��W
	Vector2 gssize;		// �Q�[����ʂ̃T�C�Y
	int screen;			// �Q�[�����
	Vector2f swing;		// �h�ꕝ
	int screenBorderWidth;	// �Q�[����ʂ̉��̕�

	int count, countMax;

public:
	GameScreen();
	~GameScreen();

	// �Q�[����ʂ̕`�揀��
	void SetAndClearScreen();
	
	// �Q�[����ʂ̕`��
	void DrawAndChangeScreen(bool& swingflag);
	
	// ��ʂɃt�B���^�[��������
	void SetGaussFilter();
	
	// �Q�[���X�N���[���̃T�C�Y�擾
	// ��ʂ̃T�C�Y�Ƃ͈Ⴄ�̂Œ���
	const Vector2 GetGSSize()const;

	const int outscreen;	// ��ʂɂ͉f��Ȃ��X�N���[���̕�
};

