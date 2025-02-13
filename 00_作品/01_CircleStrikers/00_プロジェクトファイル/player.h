//========================================================================================================
//
//�v���C���[����[player.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "behavior.h"

//�v���C���[�N���X
class Player : public Behavior   //(�e)����
{
public:
	const static float MOVE_SPEED;   //�ړ����x

	//�R���X�g���N�^
	Player(Object* pObject, int nId) : Behavior(pObject)
	{
		//�����o�ϐ�������������
		this->m_nId = nId;
		this->m_isHit = false;
	}

	//�f�X�g���N�^
	~Player() override
	{
	}

	void Init() override;   //����������
	void Update() override;   //�X�V����
	void Hit();   //�q�b�g����

private:
	void Control();   //�R���g���[������
	void LimitMove();   //�s������

	int m_nId;   //�ԍ�
	bool m_isHit;   //�q�b�g�t���O
};

#endif // !_PLAYER_H_
