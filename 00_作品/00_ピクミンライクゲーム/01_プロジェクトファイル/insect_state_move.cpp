//========================================================================================================
//
//���̃j���[�g������Ԃ̏���[insect_state_move.cpp]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "insect_state.h"
#include "insect.h"
#include "transform.h"
#include "cargo.h"
#include "obstacle.h"
#include "benlib.h"

//========================================================================================================
//�n���h��
//========================================================================================================
void InsectMoveState::Handle()
{
	//�ړ���Ɍ������Ĉړ�����
	Transform* pTransfrom = this->GetIncect()->GetComponent<Transform>();
	float fDire = Benlib::Direction(pTransfrom->GetPos(), this->m_posTarget).y;
	pTransfrom->AddPos({ sinf(fDire) * Insect::MOVE_SPEED, 0.0f, cosf(fDire) * Insect::MOVE_SPEED });
}

//========================================================================================================
//�Ă�
//========================================================================================================
void InsectMoveState::Call(Object* pPlayer)
{
	//��Ԃ�ύX����
	this->GetIncect()->GetComponent<Insect>()->ChangeState(new InsectFollowState(this->GetIncect(), pPlayer));
}

//========================================================================================================
//�Փˎ�
//========================================================================================================
void InsectMoveState::Collision(Object* pObject)
{
	//�Փ˂����I�u�W�F�N�g�̃^�O���m�F����
	Object::TAG tagObject = pObject->GetTag();
	if (tagObject == Object::TAG::IS_FRUIT || tagObject == Object::TAG::IS_JELLY)
	{//�t���[�c�̏ꍇ
		//����t���O���m�F����
		if (!pObject->GetComponent<Cargo>()->GetCollect())
		{
			//��Ԃ��^����ԂɕύX����
			this->GetIncect()->GetComponent<Insect>()->ChangeState(new InsectCarryState(this->GetIncect(), pObject));

			//�t���[�c�̎����グ����͂����Z����
			pObject->GetComponent<Cargo>()->AddILiftPower(1);
		}
	}
	else if (tagObject == Object::TAG::IS_OBSTACLE)
	{//��Q���̏ꍇ
		//�I�u�W�F�N�g��j��t���O���m�F����
		if (!pObject->GetComponent<Obstacle>()->GetBreak())
		{//�j�󂳂�ċ��Ȃ�������
			//�U����ԂɕύX����
			this->GetIncect()->GetComponent<Insect>()->ChangeState(new InsectAttackState(this->GetIncect(), pObject));
		}
	}
}