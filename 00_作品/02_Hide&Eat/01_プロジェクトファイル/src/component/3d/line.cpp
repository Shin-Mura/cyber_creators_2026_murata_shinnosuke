//=============================================================
//
// ���C�� [line.cpp]
// Author: Ito Kotaro
// 
//=============================================================
#include "line.h"
#include "manager.h"

//=============================================================
// [CLine] �R���X�g���N�^
//=============================================================
CLine::CLine()
{
	m_start = { 0.0f, 0.0f, 0.0f };
	m_end = { 0.0f, 0.0f, 0.0f };
	m_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

//=============================================================
// [CLine] �����t���R���X�g���N�^
//=============================================================
CLine::CLine(const D3DXVECTOR3& start, const D3DXVECTOR3& end, const D3DXCOLOR& color)
{
	m_start = start;
	m_end = end;
	m_color = color;
}

//=============================================================
// [CLine] �f�X�g���N�^
//=============================================================
CLine::~CLine()
{

}

//=============================================================
// [CLine] ������
//=============================================================
void CLine::Init()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 2, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, nullptr);

	// ���C���̃Z�b�g
	SetLine(m_start, m_end, m_color);
}

//=============================================================
// [CLine] �I��
//=============================================================
void CLine::Uninit()
{
	// �j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//=============================================================
// [CLine] �X�V
//=============================================================
void CLine::Update()
{

}

//=============================================================
// [CLine] �`��
//=============================================================
void CLine::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();		// �f�o�C�X���擾

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &transform->GetMatrix());

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, nullptr);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_LINELIST, //�v���~�e�B�u�̎��
		0, //�`�悷��ŏ��̒��_�C���f�b�N�X
		1);				//�`�悷��v���~�e�B�u��
}

//=============================================================
// [CLine] �ݒ�
//=============================================================
void CLine::SetLine(const D3DXVECTOR3& start, const D3DXVECTOR3& end, const D3DXCOLOR& color)
{
	m_start = start;
	m_end = end;
	m_color = color;

	VERTEX_3D* pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = m_start;
	pVtx[1].pos = m_end;

	// �@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	// ���_�J���[
	pVtx[0].col = m_color;
	pVtx[1].col = m_color;

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================
// [CLine] �F�̐ݒ�
//=============================================================
void CLine::SetColor(const D3DXCOLOR& color)
{
	m_color = color;
}