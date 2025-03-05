//==========================================================================================================
//
//���̏���[line.cpp]
// Author Murata Shinnosuke
//
//==========================================================================================================
#include "line.h"
#include "manager.h"

//==========================================================================================================
//����������
//==========================================================================================================
void Line::Init()
{
	//�f�o�C�X���擾����
	LPDIRECT3DDEVICE9 pDevice = Manager::Get()->GetRenderer()->GetDevice();

	//���_�o�b�t�@�𐶐�����
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 2, 
		D3DUSAGE_WRITEONLY, 
		FVF_VERTEX_3D, 
		D3DPOOL_MANAGED, 
		&this->m_pVtxBuffer, 
		nullptr);
}

//==========================================================================================================
//�I������
//==========================================================================================================
void Line::Uninit()
{
	//���_�o�b�t�@��j������
	if (m_pVtxBuffer != nullptr)
	{
		m_pVtxBuffer->Release();
		m_pVtxBuffer = nullptr;
	}
}

//==========================================================================================================
//�X�V����
//==========================================================================================================
void Line::Update()
{
	//���_���W�����b�N���āA���_���ւ̃|�C���^���擾����
	VERTEX_3D* pVtx;   //���_���W
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W��ݒ肷��
	pVtx[0].pos = this->m_posStart;
	pVtx[1].pos = this->m_posEnd;

	//�@���x�N�g����ݒ肷��
	pVtx[0].nor = { 0.0f, 0.0f, -1.0f };
	pVtx[1].nor = { 0.0f, 0.0f, -1.0f };

	//���_�J���[��ݒ肷��
	pVtx[0].col = this->m_color;
	pVtx[1].col = this->m_color;

	//�e�N�X�`�����W��ݒ肷��
	pVtx[0].tex = { 0.0f, 0.0f };
	pVtx[1].tex = { 0.0f, 0.0f };

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuffer->Unlock();
}

//==========================================================================================================
//�`�揈��
//==========================================================================================================
void Line::Draw()
{
	D3DXMATRIX mtxRot, mtxTrans;   //�v�Z�p�}�g���b�N�X

	//�f�o�C�X���擾����
	Renderer* pRenderer = Manager::Get()->GetRenderer();   //�����_���[
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();   //�f�o�C�X�ւ̃|�C���^

	//���[���h�}�g���b�N�X��ݒ肷��
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���e�[�^�X�g���[���ɐݒ肷��
	pDevice->SetStreamSource(0, this->m_pVtxBuffer, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g��ݒ肷��
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`����ݒ肷��
	pDevice->SetTexture(0, nullptr);

	//�`�悷��
	pDevice->DrawPrimitive(D3DPT_LINELIST, 0, 1);
}