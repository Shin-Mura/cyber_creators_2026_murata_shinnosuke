//========================================================================================================
//
//���̍U����Ԃ̏���[insect_state_attack.cpp]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "insect_state.h"
#include "insect.h"
#include "rigidbody.h"
#include "obstacle.h"

//�ÓI�����o�ϐ�������������
const int InsectAttackState::CNT_ATTACK = 30;   //�U���J�E���^�[

//========================================================================================================
//�n���h��
//========================================================================================================
void InsectAttackState::Handle()
{
	//�U�����̃I�u�W�F�N�g���m�F����
	if (this->m_pObjAttack->GetComponent<Obstacle>()->GetBreak())
	{//�A�N�e�B�u����Ȃ��ꍇ
		//�j���[�g������ԂɕύX����
		this->GetIncect()->GetComponent<Insect>()->ChangeState(new InsectNeutralState(this->GetIncect()));
		return;   //�����I��
	}

	//�U���J�E���^�[��i�߂�
	this->m_nCntAttack++;
	if (this->m_nCntAttack >= InsectAttackState::CNT_ATTACK)
	{//�U���J�E���^�[�����B������
		//�U������
		this->m_pObjAttack->GetComponent<Obstacle>()->Hit(1);
		this->m_nCntAttack = 0;   //�U���J�E���^�[�����Z�b�g
	}
}

//========================================================================================================
//�Ă�
//========================================================================================================
void InsectAttackState::Call(Object* pPlayer)
{
	//��Ԃ�ύX����
	this->GetIncect()->GetComponent<Insect>()->ChangeState(new InsectFollowState(this->GetIncect(), pPlayer));
}