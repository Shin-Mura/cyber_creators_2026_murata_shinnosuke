//========================================================================================================
//
//���̏���[nest.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "nest.h"
#include "cargo.h"
#include "prefab.h"
#include "transform.h"
#include "benlib.h"
#include "rigidbody.h"

//�ÓI�����o�ϐ�������������
const int Nest::NUM_SPAWN = 5;
const float Nest::MOVE_SPAWN = 1.0f;

//========================================================================================================
//����������
//========================================================================================================
void Nest::Init()
{
}

//========================================================================================================
//�X�V����
//========================================================================================================
void Nest::Update()
{
	//�ݕ����擾����
	std::vector<Cargo*> vCargo = Component::Get<Cargo>();

	//�ݕ��̐����J��Ԃ�
	for (unsigned int i = 0; i < vCargo.size(); i++)
	{
		//�^�O���m�F����
		if (vCargo[i]->GetObj()->GetTag() == Object::TAG::IS_JELLY)
		{//�t���[�c�̏ꍇ
			//�ݕ��Ɏ��g�̈ʒu��ݒ肷��
			vCargo[i]->SetWaypointGoal(Waypoint::Get()[6]);
		}
	}
}

//========================================================================================================
//�Փˎ�
//========================================================================================================
void Nest::Collision(Object* pObject, Physics::CONTACT contact)
{
	//�Փ˂����I�u�W�F�N�g�̃^�O���m�F����
	if (pObject->GetTag() == Object::TAG::IS_JELLY)
	{//�ݕ��̏ꍇ
		if (!pObject->GetComponent<Cargo>()->GetCollect())
		{//�������Ă��Ȃ��ꍇ
			//�ݕ����������
			pObject->GetComponent<Cargo>()->Collect();
			pObject->GetComponent<Rigidbody>()->AddMove(-pObject->GetComponent<Rigidbody>()->GetMove());   //�ړ��ʂ�ł�����

			//�����X�|�[��������
			this->SpawnInsect();
		}
	}
}

//========================================================================================================
//���̃X�|�[��
//========================================================================================================
void Nest::SpawnInsect()
{
	//�X�|�[�������J��Ԃ�
	for (int i = 0; i < Nest::NUM_SPAWN; i++)
	{
		//���𐶐�����
		D3DXVECTOR3 pos = this->GetComponent<Transform>()->GetPos();
		Object* pInsect = InsectPrefab::Create({ pos.x, pos.y + 100.0f, pos.z });
		float fDireSpawn = Benlib::CreateRand((int)D3DX_PI, 0);
		pInsect->GetComponent<Rigidbody>()->AddMove({ sinf(fDireSpawn) * Nest::MOVE_SPAWN, 100.0f, cosf(fDireSpawn) * Nest::MOVE_SPAWN });
	}
}