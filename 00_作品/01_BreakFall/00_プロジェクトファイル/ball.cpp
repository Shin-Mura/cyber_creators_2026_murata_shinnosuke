//=======================================================================================================
//
//�{�[���̏���[ball.cpp]
// Author MurataShinnosuke
//
//=======================================================================================================
#include "ball.h"
#include "transform.h"
#include "rigidbody.h"
#include "collider.h"
#include "block.h"
#include "heart.h"
#include "benlib.h"
#include "sound.h"

//�ÓI�����o�ϐ�������������
const float Ball::MOVE = 6.0f;

//=======================================================================================================
//����������
//=======================================================================================================
void Ball::Init()
{
	//�ړ��ʂ����Z����
	this->GetComponent<Rigidbody>()->SetMove({ sinf(0.0f) * Ball::MOVE, cosf(0.0f) * Ball::MOVE, 0.0f });
}

//=======================================================================================================
//�X�V����
//=======================================================================================================
void Ball::Update()
{
	//�n�[�g���m�F����
	if (this->m_pHeart == nullptr)
	{
		//�n�[�g���擾����
		this->m_pHeart = Object::Find("HeartUI");
	}

	//���˃t���O�����낷
	this->m_bReflection = false;

	//�R���|�[�l���g���擾����
	Transform* pTransform = this->GetObj()->GetComponent<Transform>();   //�g�����X�t�H�[��
	Rigidbody* pRigidbody = this->GetObj()->GetComponent<Rigidbody>();   //���W�b�g�{�f�B
	BoxCollider* pBoxCollider = this->GetObj()->GetComponent<BoxCollider>();   //�{�b�N�X�R���C�_�[

	//�����蔻��͈̔͂��擾����
	BoxCollider::Range range = pBoxCollider->GetRange();

	//�E�̊m�F������
	if (range.posMax.x > SCREEN_WIDTH / 2)
	{
		//�ʒu���C������
		D3DXVECTOR3 posNew = pTransform->GetPos();
		posNew.x = SCREEN_WIDTH / 2 - (pBoxCollider->GetSize().x / 2);
		this->GetObj()->GetComponent<Transform>()->SetPos(posNew);

		//���˂���
		pRigidbody->AddMove({ -pRigidbody->GetMove().x * 2, 0.0f, 0.0f });
	}

	//���̊m�F������
	if (range.posMin.x < -SCREEN_WIDTH / 2)
	{
		//�ʒu���C������
		D3DXVECTOR3 posNew = pTransform->GetPos();
		posNew.x = -SCREEN_WIDTH / 2 + (pBoxCollider->GetSize().x / 2);
		pTransform->SetPos(posNew);

		//���˂���
		pRigidbody->AddMove({ -pRigidbody->GetMove().x * 2, 0.0f, 0.0f });
	}

	//��̊m�F������
	if (range.posMax.y > SCREEN_HEIGHT / 2)
	{
		//�ʒu���C������
		D3DXVECTOR3 posNew = pTransform->GetPos();
		posNew.y = SCREEN_HEIGHT / 2 - (pBoxCollider->GetSize().y / 2);
		pTransform->SetPos(posNew);

		//���˂���
		pRigidbody->AddMove({ 0.0f, -pRigidbody->GetMove().y * 2, 0.0f });
	}

	//���̊m�F������
	if (range.posMin.y < -SCREEN_HEIGHT / 2)
	{
		//����������
		this->Init();
		this->GetComponent<Transform>()->SetPos({ 0.0f, 0.0f, 0.0f });   //�ʒu

		//�_���[�W��^����
		this->Damage();
	}
}

//=======================================================================================================
//�Փˎ��̏���
//=======================================================================================================
void Ball::Collision(Object* pObject, Physics::CONTACT contact)
{
	//�Փ˂����I�u�W�F�N�g�̃^�O���m�F����
	Object::TAG tagObject = pObject->GetTag();   //�^�O�̎擾
	if (tagObject == Object::TAG::IS_BLOCK || tagObject == Object::TAG::IS_ITEM)
	{//�{�[���̏ꍇ
		//���W�b�g�{�f�B���擾����
		Rigidbody* pRigidbody = this->GetComponent<Rigidbody>();
		D3DXVECTOR3 move = pRigidbody->GetMove();   //�ړ��ʂ��擾

		//���˃t���O���m�F����
		if (this->m_bReflection == false)
		{//���˂��Ă��Ȃ��ꍇ
			//�Փ˂����ʒu���m�F����
			switch (contact)
			{
			case Physics::CONTACT::IS_LEFT:   //���̏ꍇ
			case Physics::CONTACT::IS_RIGHT:   //�E�̏ꍇ

				//���˂���
				move.x *= -1;   //X���̈ړ��ʂ𔽓]����
				pRigidbody->SetMove(move);   //�ړ��ʂ�ݒ�

				//�����𔲂��o��
				break;

			case Physics::CONTACT::IS_TOP:   //��̏ꍇ
			case Physics::CONTACT::IS_BOTTOM:   //���̏ꍇ

				//���˂���
				move.y *= -1;   //Y���̈ړ��ʂ𔽓]����
				pRigidbody->SetMove(move);   //�ړ��ʂ�ݒ�

				//�����𔲂��o��
				break;
			}

			//���˃t���O�𗧂Ă�
			this->m_bReflection = true;
		}

		//�^�O���m�F����
		if (tagObject == Object::TAG::IS_BLOCK)
		{
			//�u���b�N�̃q�b�g�������s��
			pObject->GetComponent<Block>()->Hit();
		}
	}
	else if (tagObject == Object::TAG::IS_STICK)
	{//�_�̏ꍇ
		//�_�̕������v�Z����
		float fDireStick = Benlib::Direction(this->GetComponent<Transform>()->GetPos(), pObject->GetComponent<Transform>()->GetPos()).z;

		//�{�[�����{�[���̕����ɔ��˂�����
		Rigidbody* pRigidbody = this->GetComponent<Rigidbody>();  //���W�b�g�{�f�B���擾
		pRigidbody->SetMove({ -sinf(fDireStick) * Ball::MOVE, -cosf(fDireStick) * Ball::MOVE, 0.0f });

		//����炷
		PlaySound(SOUND_LABEL_STICK_HIT);
	}
	else if (tagObject == Object::TAG::IS_STICK_ASSIST)
	{
		//�{�[���𔽎˂�����
		Rigidbody* pRigidbody = this->GetComponent<Rigidbody>();   //���W�b�g�{�f�B
		D3DXVECTOR3 moveBall = pRigidbody->GetMove();   //�{�[���̈ړ���
		moveBall.y *= -1;   //X�����]
		pRigidbody->SetMove(moveBall);

		//����炷
		PlaySound(SOUND_LABEL_STICK_HIT);
	}
}

//=======================================================================================================
//�_���[�W����
//=======================================================================================================
void Ball::Damage()
{
	//�n�[�g�����炷
	this->m_pHeart->GetComponent<HeartManager>()->DamageHeart();
}