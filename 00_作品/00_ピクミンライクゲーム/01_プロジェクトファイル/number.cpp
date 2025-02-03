//========================================================================================================
//
//�����̏���[number.cpp]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "number.h"
#include "manager.h"
#include "object.h"
#include "transform.h"

//========================================================================================================
//����������
//========================================================================================================
void Number::Init()
{
}

//========================================================================================================
//�I������
//========================================================================================================
void Number::Uninit()
{
	//�����̕��J��Ԃ�
	for (unsigned int i = 0; i < this->m_vDigid.size(); i++)
	{
		//���̏I���������s��
		this->m_vDigid[i]->Uninit();
		delete this->m_vDigid[i];
	}

	//�����N���A����
	this->m_vDigid.clear();
}

//========================================================================================================
//�X�V����
//========================================================================================================
void Number::Update()
{
	//�����̕��J��Ԃ�
	for (unsigned int i = 0; i < this->m_vDigid.size(); i++)
	{
		//���̍X�V�������s��
		this->m_vDigid[i]->Update();
	}
}

//========================================================================================================
//�`�揈��
//========================================================================================================
void Number::Draw()
{
	//�f�o�C�X���擾����
	LPDIRECT3DDEVICE9 pDevice = Manager::Get()->GetRenderer()->GetDevice();   //�f�o�C�X�ւ̃|�C���^

	//�A���t�@�e�X�g��L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//�����̕��J��Ԃ�
	for (unsigned int i = 0; i < this->m_vDigid.size(); i++)
	{
		//���̕`�揈�����s��
		this->m_vDigid[i]->Draw(this->GetTexture());
	}
	//�A���t�@�e�X�g�𖳌��ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//========================================================================================================
//�e�N�X�`���̐ݒ菈��
//========================================================================================================
void Number::SetNumber(int nNumber)
{
	//������ݒ肷��
	this->m_nNumber = nNumber;
	int nKeepNumber = this->m_nNumber;   //���l�̕ێ��p

	//�����̕��J��Ԃ�
	for (unsigned int i = 0; i < this->m_vDigid.size(); i++) 
	{
		//���ɐ�����ݒ肷��
		int nBara = nKeepNumber % 10;
		nKeepNumber /= 10;
		this->m_vDigid[this->m_vDigid.size() - (i + 1)]->SetValue(nBara);
	}
}

//========================================================================================================
//�����̐ݒ菈��
//========================================================================================================
void Number::SetDigit(int nDigit)
{
	//���T�C�Y���v�Z����
	D3DXVECTOR2 sizeDigit = this->GetObj()->GetComponent<Transform2D>()->GetSize();
	sizeDigit.x /= nDigit;

	for (int i = 0; i < nDigit; i++)
	{
		//���𐶐�����
		Digit* pDigid = new Digit;
		pDigid->SetSize(sizeDigit);   //�T�C�Y
		pDigid->SetPos({ this->GetObj()->GetComponent<Transform2D>()->GetPos().x + (sizeDigit.x * i), this->GetObj()->GetComponent<Transform2D>()->GetPos().y });   //�ʒu
		pDigid->Init();

		//���̍Ō���ɕۑ�����
		this->m_vDigid.push_back(pDigid);
	}
}