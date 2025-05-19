//========================================================================================================
//
//���W�b�g�{�f�B�̏���[rigidbody.cpp]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "rigidbody.h"
#include "object.h"

//========================================================================================================
//�X�V
//========================================================================================================
void Rigidbody::Update()
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