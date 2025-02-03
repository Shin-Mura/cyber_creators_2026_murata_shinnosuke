//========================================================================================================
//
//TPS���_�J�����̏���[camera_tps.cpp]
// Auhtor Murata Shinnosuke
//
//========================================================================================================
#include "camera_tps.h"
#include "camera.h"
#include "object.h"
#include "transform.h"
#include "manager.h"
#include "joypad.h"
#include "mouse.h"

//�ÓI�����o�ϐ�������������
const float CameraTPS::DISTANCE_VIEW_TO_REGARD = 200.0f;   //���_�̒����_�̋���
const float CameraTPS::DISTANCE_TARGET_TO_FULCRUM = 0.0f;

//======================================================================================================
//����������
//======================================================================================================
void CameraTPS::Init()
{
	//�J�������擾����
	this->m_pCamera = this->GetObj()->GetComponent<Camera>();
}

//======================================================================================================
//�X�V����
//======================================================================================================
void CameraTPS::Update()
{
	//���쏈�����s��
	this->Control();

	//�G�C���t���O���m�F����
	if (this->m_isAim)
	{
		//���_��Ώۂ̈ʒu�ɂ���
		this->m_pCamera->SetPosView(this->m_posTarget);

		//�J�����̒����_�����߂�
		D3DXVECTOR3 posView = this->m_pCamera->GetPosView();
		D3DXVECTOR3 rotCamera = this->m_pCamera->GetRot();
		D3DXVECTOR3 posRegard =
		{
			posView.x - CameraTPS::DISTANCE_VIEW_TO_REGARD * sinf(rotCamera.x) * sinf(rotCamera.y),
			posView.y - CameraTPS::DISTANCE_VIEW_TO_REGARD * cosf(rotCamera.x),
			posView.z - CameraTPS::DISTANCE_VIEW_TO_REGARD * sinf(rotCamera.x) * cosf(rotCamera.y),
		};
	}
	else
	{
		//�J�����̌������擾����
		D3DXVECTOR3 rotCamera = this->m_pCamera->GetRot();

		//�J�����̎x�_�����߂�
		this->m_posFulcrum =
		{
			this->m_posTarget.x - sinf(rotCamera.y + (D3DX_PI * 0.5f)) * CameraTPS::DISTANCE_TARGET_TO_FULCRUM,
			this->m_posTarget.y,
			this->m_posTarget.z - cosf(rotCamera.y + (D3DX_PI * 0.5f)) * CameraTPS::DISTANCE_TARGET_TO_FULCRUM
		};

		//�J�����̎��_�����߂�
		D3DXVECTOR3 posView =
		{
			this->m_posFulcrum.x + CameraTPS::DISTANCE_VIEW_TO_REGARD * sinf(rotCamera.x) * sinf(rotCamera.y),
			this->m_posFulcrum.y + CameraTPS::DISTANCE_VIEW_TO_REGARD * cosf(rotCamera.x),
			this->m_posFulcrum.z + CameraTPS::DISTANCE_VIEW_TO_REGARD * sinf(rotCamera.x) * cosf(rotCamera.y),
		};

		//�J�����̒����_�����߂�
		D3DXVECTOR3 posRegard =
		{
			this->m_posFulcrum.x - CameraTPS::DISTANCE_VIEW_TO_REGARD * sinf(rotCamera.x) * sinf(rotCamera.y),
			this->m_posFulcrum.y - CameraTPS::DISTANCE_VIEW_TO_REGARD * cosf(rotCamera.x),
			this->m_posFulcrum.z - CameraTPS::DISTANCE_VIEW_TO_REGARD * sinf(rotCamera.x) * cosf(rotCamera.y),
		};

		//����ݒ肷��
		this->m_pCamera->SetPosView(posView);
		this->m_pCamera->SetPosRegard(posRegard);
	}
}

//======================================================================================================
//���쏈��
//======================================================================================================
void CameraTPS::Control()
{
	//--------------------------------------------------------------------------------------------------
	//�W���C�p�b�h�̑��쏈��
	//--------------------------------------------------------------------------------------------------
	{
		//�W���C�p�b�h���擾����
		Joypad* pJoypad = Manager::Get()->GetJoypad();

		//�E�X�e�B�b�N�̓��͏����擾����
		short sThumbRX = pJoypad->GetState(0)->Gamepad.sThumbRX;   //���E����
		short sThumbRY = pJoypad->GetState(0)->Gamepad.sThumbRY;   //�㉺����

		//���g���K�[���m�F����
		if (pJoypad->GetState(0)->Gamepad.bLeftTrigger != 0)
		{//���g���K�[��������Ă���ꍇ
			//�G�C���t���O�𗧂Ă�
			this->m_isAim = true;
		}
		else
		{//������Ă��Ȃ��ꍇ
			//�G�C���t���O�����낷
			this->m_isAim = false;
		}

		//�|���Ă�������v�Z����
		float fDireThumbR = atan2f(sThumbRX, sThumbRY);
		if (sThumbRX != 0 || sThumbRY != 0)
		{//���X�e�B�b�N�����͂���Ă���ꍇ
			//���������Z����
			D3DXVECTOR3 rotAdd;
			rotAdd.x = cosf(fDireThumbR) * this->m_fSensi;
			rotAdd.y = sinf(fDireThumbR) * this->m_fSensi;
			this->m_pCamera->AddRot(rotAdd);
		}
	}

	//--------------------------------------------------------------------------------------------------
	//�}�E�X�̑��쏈��
	//--------------------------------------------------------------------------------------------------
	{
		//�}�E�X���擾����
		Mouse* pMouse = Manager::Get()->GetMouse();

		//�}�E�X�̈ړ��ʂ��m�F����
		D3DXVECTOR2 moveMouse = pMouse->GetMove();
		if (moveMouse != D3DXVECTOR2(0.0f, 0.0f))
		{//���͂���Ă���ꍇ
			//�����ɉ��Z����
			D3DXVECTOR3 rotAdd;
			rotAdd.x = (moveMouse.y * 0.001f);
			rotAdd.y = (moveMouse.x * 0.001f);
			this->m_pCamera->AddRot(rotAdd);
		}
	}
}