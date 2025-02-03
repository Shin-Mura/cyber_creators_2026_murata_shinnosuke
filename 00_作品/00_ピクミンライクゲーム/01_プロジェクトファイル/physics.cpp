//========================================================================================================
//
//�����蔻��̏���[physics.cpp]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "physics.h"
#include "collider.h"
#include "rigidbody.h"

//�ÓI�����o�ϐ�������������
Physics* Physics::m_pInstance = nullptr;

//========================================================================================================
//�X�V����
//========================================================================================================
void Physics::Calc(Collider* pCollider)
{
	//�R���C�_�[���擾����
	std::vector<Collider*> vCollider = Component::Get<Collider>();

	//�I�u�W�F�N�g�̐����J��Ԃ�
	bool isCollision = false;   //�Փ˃t���O
	for (unsigned int i = 0; i < vCollider.size(); i++)
	{
		//�R���C�_�[���������m�F����
		if (pCollider == vCollider[i])
		{
			//���̃��[�v�Ɉڍs����
			continue;
		}

		//�R���C�_�[�̎�ނ��m�F����
		if (pCollider->GetType() == Collider::TYPE::IS_BOX)
		{//�Ώۂ̏Փ˔͈͂��{�b�N�X�̏ꍇ
			//�{�b�N�X�ƃ{�b�N�X�̏Փ˔��菈�����s��
			if (this->BoxToBox((BoxCollider*)pCollider, (BoxCollider*)vCollider[i]))
			{
				//�Փ˃t���O�𗧂Ă�
				isCollision = true;
			}
		}
	}

	//���W�b�g�{�f�B���m�F����
	Rigidbody* pRigidbody = pCollider->GetObj()->GetComponent<Rigidbody>();
	if (pRigidbody != nullptr)
	{
		//�Փ˃t���O���m�F����
		if (isCollision == true)
		{
			//�󒆃t���O�����낷
			pRigidbody->SetAir(false);
		}
		else
		{
			//�󒆃t���O�𗧂Ă�
			pRigidbody->SetAir(true);
		}
	}
}

//========================================================================================================
//�{�b�N�X�ƃ{�b�N�X�̏Փ˔��菈��
//========================================================================================================
bool Physics::BoxToBox(BoxCollider* pBoxCollider, BoxCollider* pBoxColliderTarget)
{
	//�͈͂��擾����
	BoxCollider::Range range = pBoxCollider->GetRange();
	BoxCollider::Range rangeTarget = pBoxColliderTarget->GetRange();

	bool isCollison = false;   //�Փ˃t���O

	//��ɏՓ˂��Ă��邩�m�F����
	if (rangeTarget.posMax.y > range.posMin.y &&
		rangeTarget.posMax.y <= range.posMinOld.y &&
		rangeTarget.posMax.x > range.posMinOld.x &&
		rangeTarget.posMin.x < range.posMaxOld.x &&
		rangeTarget.posMax.z > range.posMinOld.z &&
		rangeTarget.posMin.z < range.posMaxOld.z)
	{//��ɏՓ˂����ꍇ
		//�Փˎ��̏������s��
		pBoxCollider->Collision(pBoxColliderTarget, Physics::CONTACT::IS_TOP);

		//�Փ˃t���O�𗧂Ă�
		isCollison = true;
	}

	//���ɏՓ˂��Ă��邩�m�F����
	if (rangeTarget.posMin.y < range.posMax.y &&
		rangeTarget.posMin.y >= range.posMaxOld.y &&
		rangeTarget.posMax.x > range.posMinOld.x &&
		rangeTarget.posMin.x < range.posMaxOld.x &&
		rangeTarget.posMax.z > range.posMinOld.z &&
		rangeTarget.posMin.z < range.posMaxOld.z)
	{//���ɏՓ˂����ꍇ
		//�Փˎ��̏������s��
		pBoxCollider->Collision(pBoxColliderTarget, Physics::CONTACT::IS_BOTTOM);

		//�Փ˃t���O�𗧂Ă�
		isCollison = true;
	}

	//�E�ɏՓ˂��Ă��邩�m�F����
	if (rangeTarget.posMax.x > range.posMin.x &&
		rangeTarget.posMax.x <= range.posMinOld.x &&
		rangeTarget.posMax.y > range.posMinOld.y &&
		rangeTarget.posMin.y < range.posMaxOld.y &&
		rangeTarget.posMax.z > range.posMinOld.z &&
		rangeTarget.posMin.z < range.posMaxOld.z)
	{//�E�ɏՓ˂����ꍇ
		//�Փˎ��̏������s��
		pBoxCollider->Collision(pBoxColliderTarget, Physics::CONTACT::IS_RIGHT);

		//�Փ˃t���O�𗧂Ă�
		isCollison = true;
	}

	//���ɏՓ˂��Ă��邩�m�F����
	if (rangeTarget.posMin.x < range.posMax.x &&
		rangeTarget.posMin.x >= range.posMaxOld.x &&
		rangeTarget.posMax.y > range.posMinOld.y &&
		rangeTarget.posMin.y < range.posMaxOld.y &&
		rangeTarget.posMax.z > range.posMinOld.z &&
		rangeTarget.posMin.z < range.posMaxOld.z)
	{//���ɏՓ˂����ꍇ
		//�Փˎ��̏������s��
		pBoxCollider->Collision(pBoxColliderTarget, Physics::CONTACT::IS_LEFT);
		//�Փ˃t���O�𗧂Ă�
		isCollison = true;
	}

	//���ɏՓ˂��Ă��邩�m�F����
	if (rangeTarget.posMax.z > range.posMin.z &&
		rangeTarget.posMax.z <= range.posMinOld.z &&
		rangeTarget.posMax.y > range.posMinOld.y &&
		rangeTarget.posMin.y < range.posMaxOld.y &&
		rangeTarget.posMax.x > range.posMinOld.x &&
		rangeTarget.posMin.x < range.posMaxOld.x)
	{//���ɏՓ˂����ꍇ
		//�Փˎ��̏������s��
		pBoxCollider->Collision(pBoxColliderTarget, Physics::CONTACT::IS_BACK);

		//�Փ˃t���O�𗧂Ă�
		isCollison = true;
	}

	//�O�ɏՓ˂��Ă��邩�m�F����
	if (rangeTarget.posMin.z < range.posMax.z &&
		rangeTarget.posMin.z >= range.posMaxOld.z &&
		rangeTarget.posMax.y > range.posMinOld.y &&
		rangeTarget.posMin.y < range.posMaxOld.y &&
		rangeTarget.posMax.x > range.posMinOld.x &&
		rangeTarget.posMin.x < range.posMaxOld.x)
	{//��O�ɏՓ˂����ꍇ
		//�Փˎ��̏������s��
		pBoxCollider->Collision(pBoxColliderTarget, Physics::CONTACT::IS_FRONT);

		//�Փ˃t���O�𗧂Ă�
		isCollison = true;
	}

	//�Փ˃t���O���m�F����
	if (isCollison == false)
	{//�Փ˃t���O�������Ă��Ȃ��ꍇ
		//���ɓ��荞��ł��邩�m�F����
		if (rangeTarget.posMaxOld.y > range.posMinOld.y &&
			rangeTarget.posMinOld.y < range.posMaxOld.y &&
			rangeTarget.posMaxOld.x > range.posMinOld.x &&
			rangeTarget.posMinOld.x < range.posMaxOld.x &&
			rangeTarget.posMaxOld.z > range.posMinOld.z &&
			rangeTarget.posMinOld.z < range.posMaxOld.z)
		{//���ɓ��荞��ł���ꍇ
			//�Փˎ��̏������s��
			pBoxCollider->Collision(pBoxColliderTarget, Physics::CONTACT::IS_IN);

			//�Փ˃t���O�𗧂Ă�
			isCollison = true;
		}
	}

	//�Փ˃t���O��Ԃ�
	return isCollison;
}

//========================================================================================================
//����
//========================================================================================================
void Physics::Create()
{
	//�C���X�^���X���m�F����
	if (Physics::m_pInstance != nullptr)
	{
		//�����I��
		return;
	}

	//�C���X�^���X�𐶐�����
	Physics::m_pInstance = new Physics;
}