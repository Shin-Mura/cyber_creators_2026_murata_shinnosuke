//========================================================================================================
//
//�o�[�h���_�J�����̏���[camera_bird.cpp]
// Auhtor Murata Shinnosuke
//
//========================================================================================================
#include "camera_bird.h"
#include "camera.h"
#include "transform.h"
#include "manager.h"
#include "joypad.h"
#include "mouse.h"

//�ÓI�����o�ϐ�������������
const D3DXVECTOR3 CameraBird::OFFSET_POS_REGARD = { 0.0f, 500.0f, -250.0f };   //���_�̒����_�̋���

//======================================================================================================
//����������
//======================================================================================================
void CameraBird::Init()
{
	//�J�������擾����
	this->m_pCamera = this->GetObj()->GetComponent<Camera>();
}

//======================================================================================================
//�X�V����
//======================================================================================================
void CameraBird::Update()
{
	//�v���C���[���m�F����
	if (this->m_pPlayer == nullptr)
	{
		//�v���C���[���擾����
		this->m_pPlayer = Object::Find("Player");
	}
	else
	{
		//�J�����̈ʒu���v���C���[�ɍ��킹��
		D3DXVECTOR3 posPlayer = this->m_pPlayer->GetComponent<Transform>()->GetPos();
		this->m_pCamera->SetPosRegard(posPlayer);
		this->m_pCamera->GetObj()->GetComponent<Transform>()->SetPos({ posPlayer + CameraBird::OFFSET_POS_REGARD });
	}
}