//========================================================================================================
//
//�����̏���[basket.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "basket.h"
#include "cargo.h"
#include "transform.h"
#include "benlib.h"
#include "rigidbody.h"
#include "waypoint.h"
#include "score.h"

//========================================================================================================
//����������
//========================================================================================================
void Basket::Init()
{
}

//========================================================================================================
//�X�V����
//========================================================================================================
void Basket::Update()
{
	//�X�R�A���m�F����
	if (this->m_pScore == nullptr)
	{//�X�R�A���Ȃ��ꍇ
		//�X�R�A����������
		this->m_pScore = Object::Find("Score");
	}

	//�ݕ����擾����
	std::vector<Cargo*> vCargo = Component::Get<Cargo>();

	//�ݕ��̐����J��Ԃ�
	for (unsigned int i = 0; i < vCargo.size(); i++)
	{
		//�^�O���m�F����
		if (vCargo[i]->GetObj()->GetTag() == Object::TAG::IS_FRUIT)
		{//�t���[�c�̏ꍇ
			//�ݕ��Ɏ��g�̈ʒu��ݒ肷��
			vCargo[i]->SetWaypointGoal(Waypoint::Get()[0]);
		}
	}
}

//========================================================================================================
//�Փˎ�
//========================================================================================================
void Basket::Collision(Object* pObject, Physics::CONTACT contact)
{
	//�Փ˂����I�u�W�F�N�g�̃^�O���m�F����
	if (pObject->GetTag() == Object::TAG::IS_FRUIT)
	{//�ݕ��̏ꍇ
		//����t���O���m�F����
		if (!pObject->GetComponent<Cargo>()->GetCollect())
		{//�������Ă��Ȃ��ꍇ
			//�ݕ����������
			pObject->GetComponent<Cargo>()->Collect();
			pObject->GetComponent<Rigidbody>()->AddMove(-pObject->GetComponent<Rigidbody>()->GetMove());   //�ړ��ʂ�ł�����
			this->m_pScore->GetComponent<Score>()->Add(100);
		}
	}
}