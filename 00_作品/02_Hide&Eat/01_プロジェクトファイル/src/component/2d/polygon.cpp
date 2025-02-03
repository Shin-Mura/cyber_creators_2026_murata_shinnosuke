//=============================================================
//
// �摜�R���|�[�l���g [polygon.cpp]
// Author: Ito Kotaro
//
//=============================================================
#include "polygon.h"
#include "renderer.h"
#include "manager.h"

//=============================================================
// [CPolygon] �R���X�g���N�^
//=============================================================
CPolygon::CPolygon()
{
	m_pVtxBuff = nullptr;
	m_pTexture = nullptr;
	m_anchorPoint = { 0.0f, 0.0f };
	m_nSplit = 1;
	m_nTime = 0;
	m_nextTime = timeGetTime();
	m_nAnimIdx = 0;
	m_bReverse = false;
}

//=============================================================
// [CPolygon] �����t���R���X�g���N�^
//=============================================================
CPolygon::CPolygon(std::string sTexPath) : CPolygon()
{
	SetTexture(sTexPath.c_str());
}

//=============================================================
// [CPolygon] �f�X�g���N�^
//=============================================================
CPolygon::~CPolygon()
{

}

//=============================================================
// [CPolygon] ������
//=============================================================
void CPolygon::Init()
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = CRenderer::GetInstance()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, nullptr);
	VERTEX_2D* pVtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================
// [CPolygon] �I��
//=============================================================
void CPolygon::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//=============================================================
// [CPolygon] �X�V
//=============================================================
void CPolygon::Update()
{
	UpdateAnim();
	UpdateVertex();
}

//=============================================================
// [CPolygon] �`��
//=============================================================
void CPolygon::DrawUI()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice; 
	pDevice = CRenderer::GetInstance()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, //�v���~�e�B�u�̎��
		0, //�`�悷��ŏ��̒��_�C���f�b�N�X
		2); //�`�悷��v���~�e�B�u��
}

//=============================================================
// [CPolygon] �e�N�X�`���̐ݒ�
//=============================================================
void CPolygon::SetTexture(std::string sPath)
{
	if (sPath != "")
	{
		CDataTexture* pTex = CDataManager::GetInstance()->RefTexture(sPath);

		if (pTex != nullptr)
		{
			m_pTexture = pTex->GetTexture();
		}
	}
	else
	{
		m_pTexture = nullptr;
	}
}

//=============================================================
// [CPolygon] �F�̐ݒ�
//=============================================================
void CPolygon::SetColor(const D3DXCOLOR& color)
{
	VERTEX_2D* pVtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[
	pVtx[0].col = color;
	pVtx[1].col = color;
	pVtx[2].col = color;
	pVtx[3].col = color;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	m_color = color;
}

//=============================================================
// [CPolygon] �F�̐ݒ�
//=============================================================
void CPolygon::SetColor(const int& idx, const D3DXCOLOR& color)
{
	if (0 <= idx && idx < 4)
	{
		VERTEX_2D* pVtx; //���_���ւ̃|�C���^

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_�J���[
		pVtx[idx].col = color;

		// ���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}
}

//=============================================================
// [CPolygon] �A�j���[�V�����ݒ�
//=============================================================
void CPolygon::SetAnim(int nSplit, int nTime)
{
	if (nSplit > 0)
	{
		m_nSplit = nSplit;
		m_nTime = nTime;
		m_nextTime = timeGetTime() + m_nTime;
	}
}

//=============================================================
// [CPolygon] �A�j���[�V�����̍X�V
//=============================================================
void CPolygon::UpdateAnim()
{
	VERTEX_2D* pVtx; //���_���ւ̃|�C���^
	float fSplitSize = 1.0f / (float)m_nSplit;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	if (!m_bReverse)
	{
		pVtx[0].tex = D3DXVECTOR2(fSplitSize * m_nAnimIdx, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(fSplitSize * (m_nAnimIdx + 1), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(fSplitSize * m_nAnimIdx, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(fSplitSize * (m_nAnimIdx + 1), 1.0f);
	}
	else
	{
		pVtx[0].tex = D3DXVECTOR2(fSplitSize * (m_nAnimIdx + 1), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(fSplitSize * m_nAnimIdx, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(fSplitSize * (m_nAnimIdx + 1), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(fSplitSize * m_nAnimIdx, 1.0f);
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	// �A�j���[�V������i�߂�
	if (timeGetTime() >= m_nextTime)
	{
		// ���̃A�j���[�V�����Ɉڂ�
		m_nAnimIdx++;

		// ���̎��Ԃ�ݒ肷��
		m_nextTime = timeGetTime() + m_nTime;

		if (m_nAnimIdx >= m_nSplit)
		{ // �A�j���[�V�������ő吔�ɒB�����Ƃ�
			m_nAnimIdx = 0;
		}
	}
}

//=============================================================
// [CPolygon] ���_���W�̍X�V
//=============================================================
void CPolygon::UpdateVertex()
{
	VERTEX_2D* pVtx; //���_���ւ̃|�C���^

	D3DXMATRIX mtx;
	D3DXMatrixIdentity(&mtx);
	D3DXMatrixRotationZ(&mtx, transform->GetWRot().z);

	// ���_�ʒu���i�[����
	D3DXVECTOR3 convPos[4] =
	{
		{0.0f, 0.0f, 0.0f},
		{transform->GetSize().x, 0.0f, 0.0f},
		{0.0f, transform->GetSize().y, 0.0f},
		{transform->GetSize().x, transform->GetSize().y, 0.0f}
	};

	// �A���J�[�|�C���g����������
	for (int i = 0; i < 4; i++)
	{
		convPos[i].x -= m_anchorPoint.x;
		convPos[i].y -= m_anchorPoint.y;
	}


	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �T�C�Y�Ɖ�]
	D3DXVec3TransformCoord(&pVtx[0].pos, &convPos[0], &mtx);
	D3DXVec3TransformCoord(&pVtx[1].pos, &convPos[1], &mtx);
	D3DXVec3TransformCoord(&pVtx[2].pos, &convPos[2], &mtx);
	D3DXVec3TransformCoord(&pVtx[3].pos, &convPos[3], &mtx);

	// �ʒu
	for (int i = 0; i < 4; i++)
	{
		pVtx[i].pos.x += transform->GetWPos().x;
		pVtx[i].pos.y += transform->GetWPos().y;
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}