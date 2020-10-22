#pragma once
#include "Geometry.h"
#include "Character/CharacterObject.h"

enum class RectCombi {
	nothingcombi,		// �R���r�Ȃ�
	circleANDcircle,	// �Z�ƁZ
	circleANDbox,		// �Z�Ɓ�
	boxANDcircle,		// ���ƁZ
	boxANDbox,			// ���Ɓ�
};

// �����蔻��׽
class CollisionDetector
{
public:
	CollisionDetector();
	~CollisionDetector();

	// 2�̋�`�̑g�ݍ��킹�𒲂ׂ�
	RectCombi GetRectCombi(const RectType& rtA, const RectType& rtB);

	// �����蔻��
	bool IsCollision(const Rect& rcA ,const Rect& rcB, const RectCombi& rcombi);
};
