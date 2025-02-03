//========================================================================================================
//
//�v���C���[����[player.cpp]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "player.h"
#include "benlib.h"
#include "manager.h"
#include "joypad.h"
#include "component.h"
#include "rigidbody.h"
#include "collider.h"
#include "rendering.h"
#include "game_manager.h"
#include "prefab.h"

//�ÓI�����o�ϐ�������������
const float Player::MOVE_SPEED = 2.0f;

//========================================================================================================
//����������
//========================================================================================================
void Player::Init()
{
}

//========================================================================================================
//�X�V����
//========================================================================================================
void Player::Update()
{
	//�q�b�g�t���O���m�F����
	if (this->m_isHit)
	{
		//�������I������
		return;
	}

	//�R���g���[���������s��
	this->Control();

	//�s�������������s��
	this->LimitMove();

	//�̂𐶐�����
	BodyPrefab::Create(this->GetObj(), this->GetObj()->GetComponent<Transform>()->GetPos());
}

//========================================================================================================
//�q�b�g����
//========================================================================================================
void Player::Hit()
{
	//�q�b�g�t���O�𗧂Ă�
	this->m_isHit = true;
	this->GetObj()->GetComponent<Rendering>()->SetColor({ 1.0f, 0.0f, 0.0f, 1.0f });   //�Ԃ�����
}

//========================================================================================================
//�R���g���[������
//========================================================================================================
void Player::Control()
{
	Joypad* pJoypad = Manager::Get()->GetJoypad();

	//----------------------------------------------------------------------------------------------------
	//�ړ�����
	//----------------------------------------------------------------------------------------------------
	{
		short sThumbLX = pJoypad->GetState(this->m_nId)->Gamepad.sThumbLX;   //���E����
		short sThumbLY = pJoypad->GetState(this->m_nId)->Gamepad.sThumbLY;   //�㉺����

		//�|���Ă�������v�Z����
		float fDireThumbL = atan2f(sThumbLX, sThumbLY);
		if (sThumbLX != 0 || sThumbLY != 0)
		{//���X�e�B�b�N�����͂���Ă���ꍇ
			//�ړ��ʂ𑝂₷
			this->GetObj()->GetComponent<Rigidbody>()->AddMove({ sinf(fDireThumbL) * Player::MOVE_SPEED, cosf(fDireThumbL) * Player::MOVE_SPEED, 0.0f });
		}
	}

	//----------------------------------------------------------------------------------------------------
	//��������
	//----------------------------------------------------------------------------------------------------
	{
		//A�{�^�����m�F����
		if (pJoypad->GetTrigger(Joypad::JOYKEY::JOYKEY_A, this->m_nId))
		{
			//��������
			this->GetObj()->GetComponent<Rigidbody>()->AddMove(this->GetObj()->GetComponent<Rigidbody>()->GetMove());
		}
	}
}

//========================================================================================================
//�s����������
//========================================================================================================
void Player::LimitMove()
{
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
		//�ʒu���C������
		D3DXVECTOR3 posNew = pTransform->GetPos();
		posNew.y = -SCREEN_HEIGHT / 2 + (pBoxCollider->GetSize().y / 2);
		pTransform->SetPos(posNew);

		//���˂���
		pRigidbody->AddMove({ 0.0f, -pRigidbody->GetMove().y * 2, 0.0f });
	}
}