//=======================================================================================================
//
//�{�[���̏���[ball.h]
// Author MurataShinnosuke
//
//=======================================================================================================
#ifndef _BALL_H_
#define _BALL_H_

#include "behavior.h"

//�{�[���̋���
class Ball : public Behavior   //�i�e�j����
{
public:
	static const float MOVE;   //�ړ���

	//�R���X�g���N�^
	Ball(Object* pObject) : Behavior(pObject)
	{
		//�����o�ϐ�������������
		this->m_bReflection = false;
		this->m_pHeart = nullptr;
	}

	//�f�X�g���N�^
	~Ball()
	{
	}

	void Init() override;   //����������
	void Update() override;   //�X�V����
	void Collision(Object* pObject, Physics::CONTACT contact) override;

private:
	void Damage();

	bool m_bReflection;   //���˃t���O
	Object* m_pHeart;   //�n�[�g
};

#endif // !_BALL_H_
