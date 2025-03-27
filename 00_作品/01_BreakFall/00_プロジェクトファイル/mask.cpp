//========================================================================================================
//
//�}�X�N�̏���[mask.cpp]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "mask.h"
#include "manager.h"
#include "object.h"
#include "transform.h"

//========================================================================================================
//����������
//========================================================================================================
void Mask::Init()
{
	//�f�o�C�X���擾����
	Renderer* pRenderer = Manager::Get()->GetRenderer();   //�����_���[
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();   //�f�o�C�X�ւ̃|�C���^

	//���_�o�b�t�@�𐶐�����
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,   //�m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&this->m_pVtxBuffer,
		NULL);
}

//========================================================================================================
//�I������
//========================================================================================================
void Mask::Uninit()
{
	//���_�o�b�t�@��j������
	if (this->m_pVtxBuffer != nullptr)
	{
		this->m_pVtxBuffer->Release();
		this->m_pVtxBuffer = nullptr;
	}
}

//========================================================================================================
//�X�V����
//========================================================================================================
void Mask::Update()
{
	//���_���W�����b�N���āA���_���ւ̃|�C���^���擾����
	VERTEX_2D* pVtx;   //���_���W
	this->m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W��ݒ肷��
	D3DXVECTOR2 pos = this->GetObj()->GetComponent<Transform2D>()->GetPos();
	D3DXVECTOR2 size = this->GetObj()->GetComponent<Transform2D>()->GetSize();
	pVtx[0].pos = { pos.x - (size.x / 2), pos.y - (size.x / 2), 0.0f };
	pVtx[1].pos = { pos.x + (size.x / 2), pos.y - (size.x / 2), 0.0f };
	pVtx[2].pos = { pos.x - (size.x / 2), pos.y + (size.x / 2), 0.0f };
	pVtx[3].pos = { pos.x + (size.x / 2), pos.y + (size.x / 2), 0.0f };

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[��ݒ肷��
	D3DXCOLOR col = this->GetColor();   //�F
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//�e�N�X�`�����W��ݒ肷��
	pVtx[0].tex = { 0.0f, 0.0f };
	pVtx[1].tex = { 1.0f, 0.0f };
	pVtx[2].tex = { 0.0f, 1.0f };
	pVtx[3].tex = { 1.0f, 1.0f };

	//���_�o�b�t�@���A�����b�N����
	this->m_pVtxBuffer->Unlock();
}

//========================================================================================================
//�`�揈��
//========================================================================================================
void Mask::Draw()
{
	//�f�o�C�X���擾����
	Renderer* pRenderer = Manager::Get()->GetRenderer();   //�����_���[
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();   //�f�o�C�X�ւ̃|�C���^

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ肷��
	pDevice->SetStreamSource(0, this->m_pVtxBuffer, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g��ݒ肷��
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`����ݒ肷��
	pDevice->SetTexture(0, this->GetTexture());

	//�|���S����`�悷��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}