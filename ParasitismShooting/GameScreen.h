#pragma once
#include <vector>
#include "Geometry.h"


 struct SMALL_BOX
{
	 Box box;
	 bool drawflag;
};


class GameScreen
{
private:
	Vector2 luPos;		// �Q�[����ʂ̍���̍��W
	Vector2 gssize;		// �Q�[����ʂ̃T�C�Y
	int screen;			// �Q�[�����
	Vector2f swing;		// �h�ꕝ

	int count, countMax;

	std::vector<SMALL_BOX> sboxes;	// �����̏W�܂�, ��ʑJ�ڂɎg��

public:
	GameScreen();
	~GameScreen();

	void SetAndClearScreen();
	void DrawAndChangeScreen(bool& swingflag);
	void SetGaussFilter();
	const Vector2 GetGSSize()const;

	const int outscreen;	// ��ʂɂ͉f��Ȃ��X�N���[���̕�
};

