//========================================================================================================
//
//���j���[�̏���[menu.cpp]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "menu.h"
#include "manager.h"
#include "joypad.h"
#include "keyboard.h"
#include "object.h"
#include "transform.h"

//========================================================================================================
//����������
//========================================================================================================
void Menu::Init()
{
	//�I�����̐����J��Ԃ�
	for (unsigned int i = 0; i < this->m_vSelectBox.size(); i++)
	{
		//�I�𒆂̑I���{�b�N�X�����Z�b�g����
		this->m_vSelectBox[i]->Reset();
	}

	//����t���O�����낷
	this->m_isDecide = false;

	//�I����0��
	this->m_nSelect = 0;
}

//========================================================================================================
//�I������
//========================================================================================================
void Menu::Uninit()
{
	//�I�����̐����J��Ԃ�
	for (unsigned int i = 0; i < this->m_vSelectBox.size(); i++)
	{
		//�I���������s��
		this->m_vSelectBox[i]->Uninit();
		delete this->m_vSelectBox[i];
	}

	//�I�������폜����
	this->m_vSelectBox.clear();
}

//========================================================================================================
//�X�V����
//========================================================================================================
void Menu::Update()
{
	//���쏈�����s��
	this->Control();

	//�I�����̐����J��Ԃ�
	for (unsigned int i = 0; i < this->m_vSelectBox.size(); i++)
	{
		//�I�����̍X�V�������s��
		this->m_vSelectBox[i]->Update();
	}
}

//========================================================================================================
//�`�揈��
//========================================================================================================
void Menu::Draw()
{
	//�f�o�C�X���擾����
	LPDIRECT3DDEVICE9 pDevice = Manager::Get()->GetRenderer()->GetDevice();   //�f�o�C�X�ւ̃|�C���^

	//�A���t�@�e�X�g��L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//�I�����̐����J��Ԃ�
	for (unsigned int i = 0; i < this->m_vSelectBox.size(); i++)
	{
		//�I�����̕`�揈�����s��
		this->m_vSelectBox[i]->Draw(this->GetTexture());
	}

	//�A���t�@�e�X�g�𖳌��ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//========================================================================================================
//�I�����̐��̐ݒ菈��
//========================================================================================================
void Menu::SetSelectBox(int nNum)
{
	//�ݒ肷������J��Ԃ�
	for (int i = 0; i < nNum; i++)
	{
		//�I�����𐶐�����
		SelectBox* pSelectBox = new SelectBox;

		//����ݒ肷��
		pSelectBox->SetSize(this->GetObj()->GetComponent<Transform2D>()->GetSize());
		pSelectBox->SetPos({ this->GetObj()->GetComponent<Transform2D>()->GetPos().x, this->GetObj()->GetComponent<Transform2D>()->GetPos().y + ((this->GetObj()->GetComponent<Transform2D>()->GetSize().y + this->m_fGap) * i) });   //�ʒu
		pSelectBox->SetPattern(nNum);
		pSelectBox->SetOder(i);

		//�������������s��
		pSelectBox->Init();

		//�I�����̍Ō���ɏ���ۑ�����
		this->m_vSelectBox.push_back(pSelectBox);
	}
}

//========================================================================================================
//���쏈��
//========================================================================================================
void Menu::Control()
{
	//----------------------------------------------------------------------------------------------------
	//���͏������s��
	//----------------------------------------------------------------------------------------------------
	{
		Keyboard* pKeyboard = Manager::Get()->GetKeyboard();
		Joypad* pJoypad = Manager::Get()->GetJoypad();

		//W�L�[���m�F����
		if (pKeyboard->GetTrigger(DIK_W) || pJoypad->GetTrigger(Joypad::JOYKEY::IS_UP, 0))
		{//W�L�[��������Ă���ꍇ
			//���̑I�����Ɉړ�����
			this->m_nSelect--;
			if (this->m_nSelect < 0)
			{//0��菬�����ꍇ
				//�I�����������
				this->m_nSelect = this->m_vSelectBox.size() - 1;
			}
		}

		//S�L�[���m�F����
		if (pKeyboard->GetTrigger(DIK_S) || pJoypad->GetTrigger(Joypad::JOYKEY::IS_DOWN, 0))
		{//S�L�[��������Ă���ꍇ
			//���̑I�����Ɉړ�����
			this->m_nSelect++;
			if (this->m_nSelect >= (int)this->m_vSelectBox.size())
			{//�I�����𒴂����ꍇ
				//�I�����������
				this->m_nSelect = 0;
			}
		}

		//�I���t���O�𗧂Ă�
		this->m_vSelectBox[this->m_nSelect]->Select();

		//SPACE�L�[���m�F����
		if (pKeyboard->GetTrigger(DIK_SPACE) || pJoypad->GetTrigger(Joypad::JOYKEY::IS_A, 0))
		{//SPACE�L�[��������Ă���ꍇ
			//����t���O�𗧂Ă�
			this->m_isDecide = true;
		}
	}
}