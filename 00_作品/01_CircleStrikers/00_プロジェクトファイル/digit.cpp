//========================================================================================================
//
//���̏���[digit.cpp]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "digit.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//========================================================================================================
//����������
//========================================================================================================
void Digit::Init()
{
	//�f�o�C�X���擾����
	Renderer* pRenderer = Manager::Get()->GetRenderer();   //�����_���[
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();   //�f�o�C�X�ւ̃|�C���^

	//���_�o�b�t�@�𐶐�����
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,   //�m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffer,
		NULL);

	//�X�V�������s��
	this->Update();
}

//========================================================================================================
//�I������
//========================================================================================================
void Digit::Uninit()
{
	//���_�o�b�t�@��j������
	if (m_pVtxBuffer != nullptr)
	{
		m_pVtxBuffer->Release();
		m_pVtxBuffer = nullptr;
	}
}

//========================================================================================================
//�X�V����
//========================================================================================================
void Digit::Update()
{
	//���_���W�����b�N���āA���_���ւ̃|�C���^���擾����
	VERTEX_2D* pVtx;   //���_���W
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W��ݒ肷��
	pVtx[0].pos = { this->m_pos.x - (this->m_size.x / 2), this->m_pos.y - (this->m_size.y / 2), 0.0f };
	pVtx[1].pos = { this->m_pos.x + (this->m_size.x / 2), this->m_pos.y - (this->m_size.y / 2), 0.0f };
	pVtx[2].pos = { this->m_pos.x - (this->m_size.x / 2), this->m_pos.y + (this->m_size.y / 2), 0.0f };
	pVtx[3].pos = { this->m_pos.x + (this->m_size.x / 2), this->m_pos.y + (this->m_size.y / 2), 0.0f };

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[��ݒ肷��
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W��ݒ肷��
	pVtx[0].tex = { (1.0f / 10) * this->m_nValue, 0.0f };
	pVtx[1].tex = { (1.0f / 10) * (this->m_nValue + 1), 0.0f };
	pVtx[2].tex = { (1.0f / 10) * this->m_nValue, 1.0f };
	pVtx[3].tex = { (1.0f / 10) * (this->m_nValue + 1), 1.0f };

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuffer->Unlock();
}

//========================================================================================================
//�`�揈��
//========================================================================================================
void Digit::Draw(LPDIRECT3DTEXTURE9 pTexutre)
{
	//�f�o�C�X���擾����
	LPDIRECT3DDEVICE9 pDevice = Manager::Get()->GetRenderer()->GetDevice();   //�f�o�C�X�ւ̃|�C���^

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ肷��
	pDevice->SetStreamSource(0, this->m_pVtxBuffer, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g��ݒ肷��
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`����ݒ肷��
	pDevice->SetTexture(0, pTexutre);

	//�|���S����`�悷��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}