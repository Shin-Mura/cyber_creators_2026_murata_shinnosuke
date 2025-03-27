//========================================================================================================
//
//�J�[�\���̏���[cursor.cpp]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "cursor.h"
#include "manager.h"
#include "benlib.h"
#include "plane.h"
#include "transform.h"

//�ÓI�����o�ϐ�������������
const float Cursor::INIT_RANGE = 25.0f;
const float Cursor::ADD_RANGE = 5.0f;
const float Cursor::MOVE_SPEED = 20.0f;
const float Cursor::MAX_DISTANCE = 200.0f;

//========================================================================================================
//����������
//========================================================================================================
void Cursor::Init()
{

}

//========================================================================================================
//�X�V����
//========================================================================================================
void Cursor::Update()
{
	//�v���C���[���m�F����
	if (this->m_pPlayer == nullptr)
	{
		//�v���C���[���擾����
		this->m_pPlayer = Object::Find("Player");
	}

	//���쏈�����s��
	this->Control();
}

//========================================================================================================
//���쏈��
//========================================================================================================
void Cursor::Control()
{
	//�W���C�p�b�h���擾����
	Joypad* pJoypad = Manager::Get()->GetJoypad();

	//�g�������X�t�H�[�����擾����
	Transform* pTransform = this->GetObj()->GetComponent<Transform>();

	//���X�e�B�b�N�̓��͏����擾����
	short sThumbLX = pJoypad->GetState(0)->Gamepad.sThumbLX;   //���E����
	short sThumbLY = pJoypad->GetState(0)->Gamepad.sThumbLY;   //�㉺����

	//�|���Ă�������v�Z����
	float fDireThumb = atan2f(sThumbLX, sThumbLY);

	//���X�e�B�b�N���͂���͂��m�F����
	if (sThumbLX != 0 || sThumbLY != 0)
	{
		//�ړ�����
		pTransform->AddPos({ sinf(fDireThumb) * Cursor::MOVE_SPEED, 0.0f, cosf(fDireThumb) * Cursor::MOVE_SPEED });

		//�v���C���[�Ƃ̋������m�F����
		D3DXVECTOR3 posCursor = pTransform->GetPos();
		D3DXVECTOR3 posPlayer = this->m_pPlayer->GetComponent<Transform>()->GetPos();
		if (Benlib::Distance(posCursor, posPlayer).y > Cursor::MAX_DISTANCE)
		{//�v���C���[�Ƃ̋����̍ő�l�𒴂��Ă���ꍇ
			//�v���C���[�̕������v�Z����
			float fDirePlayer = Benlib::Direction(posCursor, posPlayer).y + D3DX_PI;

			//�ő�l�ɕ␳����
			pTransform->SetPos({ posPlayer.x + sinf(fDirePlayer) * Cursor::MAX_DISTANCE, 0.01f, posPlayer.z + cosf(fDirePlayer) * Cursor::MAX_DISTANCE });
		}
	}

	//A�{�^���̓��͂��m�F����
	if (pJoypad->GetPress(Joypad::JOYKEY::IS_A, 0))
	{//A�{�^���������ꂽ�ꍇ
		//�T�[�`�͈͂��L����
		this->m_fRange += Cursor::ADD_RANGE;
		if (this->m_fRange > Cursor::MAX_DISTANCE)
		{//�T�[�`�͈͂��K��l�𒴂����ꍇ
			//��������
			this->m_fRange = Cursor::MAX_DISTANCE;
		}
	}
	else
	{//������Ă��Ȃ��ꍇ
		//�����T�C�Y�ɖ߂�
		this->m_fRange = Cursor::INIT_RANGE;
	}

	//�T�C�Y��ݒ肷��
	float fScale = (this->m_fRange * 2.0f) / Plane::BASE_SIZE.x;
	pTransform->SetScale({ fScale, 1.0f, fScale });
}