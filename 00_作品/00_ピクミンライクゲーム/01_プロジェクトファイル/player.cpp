//========================================================================================================
//
//�v���C���[����[player.cpp]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "player.h"
#include "manager.h"
#include "Xfile.h"
#include "keyboard.h"
#include "joypad.h"
#include "camera.h"
#include "model.h"
#include "motioneer.h"
#include "transform.h"
#include "cursor.h"
#include "insect.h"
#include "num_insect.h"
#include "benlib.h"

//�ÓI�����o�ϐ�������������
const int Player::MAX_INSECT = 100;   //���̍ő吔
const float Player::MOVE_SPEED = 2.5f;   //�ړ����x

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
	//�J�[�\�����m�F����
	if (this->m_pCursor == nullptr)
	{
		//�J�[�\������������
		this->m_pCursor = Object::Find("Cursor");
	}

	//���̐����m�F����
	if (this->m_pNumInsect == nullptr)
	{//�Ȃ��ꍇ
		//���̐�����������
		this->m_pNumInsect = Object::Find("NumInsect");
	}

	//�R���g���[���������s��
	this->Control();

	//���̐���ݒ肷��
	this->m_pNumInsect->GetComponent<NumInsect>()->SetNumInsect(this->m_vInsect.size());

	//���[�V������K�p����
	this->GetObj()->GetComponent<Motioneer>()->StartMotion(this->m_motionPlay);
}

//========================================================================================================
//�R���g���[������
//========================================================================================================
void Player::Control()
{
	//�W���C�p�b�h���擾����
	Joypad* pJoypad = Manager::Get()->GetJoypad();

	//���X�e�B�b�N�̓��͏����擾����
	short sThumbLX = pJoypad->GetState(0)->Gamepad.sThumbLX;   //���E����
	short sThumbLY = pJoypad->GetState(0)->Gamepad.sThumbLY;   //�㉺����

	//���X�e�B�b�N�̓��͂��m�F����
	if (sThumbLX != 0 || sThumbLY != 0)
	{//���X�e�B�b�N�����͂���Ă���ꍇ
		//�|���Ă�������v�Z����
		float fDireThumbL = atan2f(sThumbLX, sThumbLY);

		//�ړ�����
		Transform* pTransform = this->GetObj()->GetComponent<Transform>();
		pTransform->AddPos({ sinf(fDireThumbL) * Player::MOVE_SPEED, 0.0f, cosf(fDireThumbL) * Player::MOVE_SPEED });
		pTransform->SetRot({ 0.0f, fDireThumbL + D3DX_PI, 0.0f });    //�ړ������Ɍ���

		//�ړ����[�V�����ɕύX����
		this->ChangeMotion(Player::MOTION::IS_MOVE);
	}
	else
	{//���͂���Ă��Ȃ��ꍇ
		//�ҋ@���[�V�����ɕύX����
		this->ChangeMotion(Player::MOTION::IS_NEUTRAL);
	}

	//A�{�^���̓��͂��m�F����
	if (pJoypad->GetPress(Joypad::JOYKEY::IS_A, 0))
	{
		//����T��
		this->SearchInsect();
	}

	//B�{�^���̓��͂��m�F����
	if (pJoypad->GetTrigger(Joypad::JOYKEY::IS_B, 0))
	{
		//���𓊂���
		this->ThrowInsect();
	}

	//�����I��
	return;
}

//========================================================================================================
//����T��
//========================================================================================================
void Player::SearchInsect()
{
	//���̋������t���Ă���I�u�W�F�N�g���擾����
	std::vector<Insect*> vInsect = Component::Get<Insect>();

	//���̐����J��Ԃ�
	for (unsigned int i = 0; i < vInsect.size(); i++)
	{
		//���̋��������߂�
		float fDisInsect = Benlib::Distance(this->m_pCursor->GetComponent<Transform>()->GetPos(), vInsect[i]->GetObj()->GetComponent<Transform>()->GetPos()).y;
		if (fDisInsect <= this->m_pCursor->GetComponent<Cursor>()->GetRange())
		{
			//���������Ă��邩�m�F����
			if (this->HasInsect(vInsect[i]->GetObj()) == false)
			{
				//���̐����m�F����
				if (this->m_vInsect.size() < Player::MAX_INSECT)
				{
					//�����Ă�
					vInsect[i]->Call(this->GetObj());
					this->m_vInsect.push_back(vInsect[i]->GetObj());   //�R���e�i�ɓ����
				}
			}
		}
	}
}

//========================================================================================================
//���𓊂���
//========================================================================================================
void Player::ThrowInsect()
{
	//�����m�F����
	if (this->m_vInsect.empty())
	{
		//�������I������
		return;
	}

	//�擪�ɂ��钎�𓊂���
	Transform* pTransform = this->GetObj()->GetComponent<Transform>();   //�g�����X�t�H�[��
	D3DXVECTOR3 pos = pTransform->GetPos();   //������ʒu
	float fDire = Benlib::Direction(pos, this->m_pCursor->GetComponent<Transform>()->GetPos()).y;   //���������
	float fDist = Benlib::Distance(pos, this->m_pCursor->GetComponent<Transform>()->GetPos()).y;
	this->m_vInsect.front()->GetComponent<Insect>()->Throw({ pos.x, pos.y + 50.0f, pos.z }, fDire, fDist);
	pTransform->SetRot({ 0.0f, fDire + D3DX_PI, 0.0f });   //����������Ɍ���
	this->m_vInsect.erase(this->m_vInsect.begin());   //�����������R���e�i����폜
}

//========================================================================================================
//���[�V�����̕ύX
//========================================================================================================
void Player::ChangeMotion(Player::MOTION motion)
{
	//�Đ����̃��[�V�������m�F����
	if (this->m_motionPlay == Player::MOTION::IS_ATTACK)
	{//�U���̃��[�V�����̏ꍇ

	}
	else
	{//����ȊO�̏ꍇ
		//���[�V������ݒ肷��
		this->m_motionPlay = motion;
	}
}

//========================================================================================================
//���[�V�����I�����̏���
//========================================================================================================
void Player::EndMotion()
{
	//�j���[�g�����ɖ߂�
	this->m_motionPlay = Player::MOTION::IS_NEUTRAL;
}