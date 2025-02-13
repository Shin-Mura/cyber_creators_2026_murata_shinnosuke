//========================================================================================================
//
//���W�b�g�{�f�B�̏���[rigidbody.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _RIGIDBODY_H_
#define _RIGIDBODY_H_

#include "component.h"
#include "object.h"
#include "transform.h"

//���W�b�g�{�f�B
class Rigidbody : public Component
{
public:
	//�R���X�g���N�^
	Rigidbody(Object* pObject) : Component(pObject)
	{
		//�����o�ϐ�������������
		this->m_move = { 0.0f, 0.0f, 0.0f };   //�ړ���
		this->m_isAir = false;   //�󒆃t���O
		this->m_fGravity = -1.0f;   //�d��
		this->m_fFriction = 0.5f;   //���C
		this->m_fFrictionAir = this->m_fFriction;
	}

	//�f�X�g���N�^
	~Rigidbody() override
	{
	}

	//�X�V����
	void Update() override
	{
		//�󒆃t���O���m�F����
		if (this->m_isAir == true)
		{//�󒆃t���O�������Ă���ꍇ
			//�󒆗p�̖��C�Ŋ������v�Z����
			this->m_move.x += (0.0f - this->m_move.x) * this->m_fFrictionAir;
			this->m_move.y += (0.0f - this->m_move.y) * this->m_fFrictionAir;
		}
		else
		{//�����Ă��Ȃ��ꍇ
			//�������v�Z����
			this->m_move.x += (0.0f - this->m_move.x) * this->m_fFriction;
			this->m_move.y += (0.0f - this->m_move.y) * this->m_fFriction;
		}

		//�d�͂����Z����
		this->m_move.y += this->m_fGravity;;

		//�ړ��ʂ��g�����X�t�H�[���̈ʒu�ɉ��Z����
		this->GetObj()->GetComponent<Transform>()->AddPos(this->m_move);
	}

	void AddMove(D3DXVECTOR3 move) { this->m_move += move; };   //�ړ��ʂ̉��Z����

	void SetAir(bool isAir) { this->m_isAir = isAir; };
	void SetGravity(float fGravity) { this->m_fGravity = fGravity; };   //�d��
	void SetFriction(float fFriction) { this->m_fFriction = fFriction; };   //���C
	void SetFrictionAir(float fFriction) { this->m_fFrictionAir = fFriction; };   //�󒆗p�̖��C

	D3DXVECTOR3 GetMove() { return this->m_move; };   //�ړ���

private:
	D3DXVECTOR3 m_move;   //�ړ���
	bool m_isAir;   //�󒆃t���O
	float m_fGravity;   //�d��
	float m_fFriction;   //���C
	float m_fFrictionAir;   //�󒆂ł̖��C
};

#endif // !_RIGIDBODY_H_