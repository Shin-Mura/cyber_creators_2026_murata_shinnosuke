//========================================================================================================
//
//���̃j���[�g������Ԃ̏���[insect_state_neutral.cpp]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "insect_state.h"
#include "insect.h"
#include "cargo.h"
#include "obstacle.h"
#include "transform.h"
#include "benlib.h"

//�ÓI�����o�ϐ�������������
const float	InsectNeutralState::DIS_SEARCH = 100.0f;

//========================================================================================================
//�n���h��
//========================================================================================================
void InsectNeutralState::Handle()
{
	//�I�u�W�F�N�g��T��
	this->SeatchObject();
}

//========================================================================================================
//�Ă�
//========================================================================================================
void InsectNeutralState::Call(Object* pPlayer)
{
	//��Ԃ�ύX����
	this->GetIncect()->GetComponent<Insect>()->ChangeState(new InsectFollowState(this->GetIncect(), pPlayer));
}

//========================================================================================================
//�t���[�c��T��
//========================================================================================================
void InsectNeutralState::SeatchObject()
{
	//�t���[�c���擾����
	std::vector<Cargo*> vCargo = Component::Get<Cargo>();

	//�t���[�c�̐����J��Ԃ�
	for (unsigned int i = 0; i < vCargo.size(); i++)
	{
		//�t���[�c�Ƃ̋������m�F����
		D3DXVECTOR3 posCargo = vCargo[i]->GetObj()->GetComponent<Transform>()->GetPos();
		float fDisCargo = Benlib::Distance(this->GetIncect()->GetComponent<Transform>()->GetPos(), posCargo).y;
		if (fDisCargo <= InsectNeutralState::DIS_SEARCH)
		{//�T�[�`�͈͓��̏ꍇ
			//�t���[�c�̉���t���O���m�F����
			if (vCargo[i]->GetCollect() == false)
			{
				//�ړ���ԂɕύX����
				this->GetIncect()->GetComponent<Insect>()->ChangeState(new InsectMoveState(this->GetIncect(), posCargo));
				return;   //�����I��
			}
		}
	}

	//��Q�����擾����
	std::vector<Obstacle*> vObstacle = Component::Get<Obstacle>();

	//��Q���̐����J��Ԃ�
	for (unsigned int i = 0; i < vObstacle.size(); i++)
	{
		//��Q���Ƃ̋������m�F����
		D3DXVECTOR3 posObstacle = vObstacle[i]->GetObj()->GetComponent<Transform>()->GetPos();
		float fDisObstacle = Benlib::Distance(this->GetIncect()->GetComponent<Transform>()->GetPos(), posObstacle).y;
		if (fDisObstacle <= InsectNeutralState::DIS_SEARCH)
		{//�T�[�`�͈͓��̏ꍇ
			//��Q���̔j��t���O���m�F����
			if (vObstacle[i]->GetBreak() == false)
			{//�j�󂳂�Ă��Ȃ��ꍇ
				//�ړ���ԂɕύX����
				this->GetIncect()->GetComponent<Insect>()->ChangeState(new InsectMoveState(this->GetIncect(), posObstacle));
				return;   //�����I��
			}
		}
	}
}

//========================================================================================================
//�t���[�c��T��
//========================================================================================================
void InsectNeutralState::SearchFruit()
{
	//�t���[�c���擾����
	std::vector<Cargo*> vCargo = Component::Get<Cargo>();

	//�t���[�c�̐����J��Ԃ�
	for (unsigned int i = 0; i < vCargo.size(); i++)
	{
		//�t���[�c�Ƃ̋������m�F����
		D3DXVECTOR3 posCargo = vCargo[i]->GetObj()->GetComponent<Transform>()->GetPos();
		float fDisCargo = Benlib::Distance(this->GetIncect()->GetComponent<Transform>()->GetPos(), posCargo).y;
		if (fDisCargo <= InsectNeutralState::DIS_SEARCH)
		{//�T�[�`�͈͓��̏ꍇ
			//�t���[�c�̉���t���O���m�F����
			if (vCargo[i]->GetCollect() == false)
			{
				//�ړ���ԂɕύX����
				this->GetIncect()->GetComponent<Insect>()->ChangeState(new InsectMoveState(this->GetIncect(), posCargo));
				break;
			}
		}
	}
}

//========================================================================================================
//��Q����T��
//========================================================================================================
void InsectNeutralState::SearchObstacle()
{
	//��Q�����擾����
	std::vector<Obstacle*> vObstacle = Component::Get<Obstacle>();

	//��Q���̐����J��Ԃ�
	for (unsigned int i = 0; i < vObstacle.size(); i++)
	{
		//��Q���Ƃ̋������m�F����
		D3DXVECTOR3 posObstacle = vObstacle[i]->GetObj()->GetComponent<Transform>()->GetPos();
		float fDisObstacle = Benlib::Distance(this->GetIncect()->GetComponent<Transform>()->GetPos(), posObstacle).y;
		if (fDisObstacle <= InsectNeutralState::DIS_SEARCH)
		{//�T�[�`�͈͓��̏ꍇ
			//��Q���̔j��t���O���m�F����
			if (vObstacle[i]->GetBreak() == false)
			{//�j�󂳂�Ă��Ȃ��ꍇ
				//�ړ���ԂɕύX����
				this->GetIncect()->GetComponent<Insect>()->ChangeState(new InsectMoveState(this->GetIncect(), posObstacle));
				break;   //�����𔲂��o��
			}
		}
	}
}