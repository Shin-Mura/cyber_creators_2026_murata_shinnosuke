//========================================================================================================
//
//���̉^����Ԃ̏���[insect_state_carry.cpp]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "insect_state.h"
#include "insect.h"
#include "cargo.h"
#include "rigidbody.h"

//========================================================================================================
//�n���h��
//========================================================================================================
void InsectCarryState::Handle()
{
	//�^���I�u�W�F�N�g�̉���t���O���m�F����
	if (this->m_pCarry->GetComponent<Cargo>()->GetCollect())
	{//�������Ă���ꍇ
		//�j���[�g������ԂɕύX����
		this->GetIncect()->GetComponent<Insect>()->ChangeState(new InsectNeutralState(this->GetIncect()));
	}
	else
	{
		//�^���I�u�W�F�N�g�̈ړ��ʂ����g�ɂ����Z����
		D3DXVECTOR3 moveCarry = this->m_pCarry->GetComponent<Rigidbody>()->GetMove();
		this->GetIncect()->GetComponent<Transform>()->AddPos(moveCarry);
	}
}

//========================================================================================================
//�Ă�
//========================================================================================================
void InsectCarryState::Call(Object* pPlayer)
{
	//��Ԃ�ύX����
	this->m_pCarry->GetComponent<Cargo>()->AddILiftPower(-1);   //�͂����炷
	this->GetIncect()->GetComponent<Insect>()->ChangeState(new InsectFollowState(this->GetIncect(), pPlayer));
}