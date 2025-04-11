//=============================================================
//
// �o�[ [bar.cpp]
// Author: Ito Kotaro
//
//=============================================================
#include "bar.h"
#include "renderer.h"
#include "internal/data_manager.h"

// �ÓI�����o�ϐ��̏�����
const float CBar::DEFAULT_BAR_LENGTH = 800.0f;
const float CBar::DEFAULT_BAR_BOLD = 80.0f;
const float CProgressBar::DEFAULT_BAR_SPACE = 8.0f;
const D3DXCOLOR CProgressBar::DEFAULT_FILL_COLOR = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
const D3DXCOLOR CProgressBar::DEFAULT_NONFILL_COLOR = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

//=============================================================
// [CBar] ������
//=============================================================
void CBar::Init()
{
	m_pBgObj = new GameObject();
	m_pBarObj = new GameObject();
	m_pBgObj->transform->SetParent(transform);
	m_pBarObj->transform->SetParent(transform);
	m_pBgObj->AddComponent<CPolygon>();
	m_pBarObj->AddComponent<CPolygon>();

	// �ϐ��̏�����
	m_fBarLength = DEFAULT_BAR_LENGTH;
	m_fBarBold = DEFAULT_BAR_BOLD;
	m_pBarObj->GetComponent<CPolygon>()->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	m_fBarProgress = 1.0f;

	// �T�C�Y�̐ݒ�
	m_pBgObj->transform->SetSize(m_fBarLength, m_fBarBold);
	m_pBarObj->transform->SetSize(m_fBarLength * m_fBarProgress, m_fBarBold);
}

//=============================================================
// [CBar] �X�V
//=============================================================
void CBar::Update()
{
	m_pBarObj->transform->SetSize(m_fBarLength * m_fBarProgress, m_fBarBold);
}


//=============================================================
// [CProgressBar] �R���X�g���N�^
//=============================================================
CProgressBar::CProgressBar(const int& nNumBar)
{
	m_nNumBar = nNumBar;
}

//=============================================================
// [CProgressBar] ������
//=============================================================
void CProgressBar::Init()
{
	// �Q�[���I�u�W�F�N�g���쐬����
	m_pBgObj = new GameObject();
	m_pBgObj->SetParent(gameObject);
	m_pBgObj->AddComponent<CPolygon>();

	// �o�[�̍쐬
	for (int i = 0; i < m_nNumBar; i++)
	{
		GameObject* pBar = new GameObject();
		pBar->SetParent(gameObject);
		pBar->SetPriority(8);
		pBar->AddComponent<CPolygon>();
		pBar->GetComponent<CPolygon>()->SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		m_pBars.push_back(pBar);
	}

	// �ϐ��̏�����
	m_fBarLength = CBar::DEFAULT_BAR_LENGTH;
	m_fBarBold = CBar::DEFAULT_BAR_BOLD;
	m_fBarSpace = CProgressBar::DEFAULT_BAR_SPACE;
	m_fSpace = 5;
	m_fBarProgress = 1.0f;
	m_fillColor = DEFAULT_FILL_COLOR;
	m_nonFillCollor = DEFAULT_NONFILL_COLOR;
	m_fAlpha = 1.0f;

	// �T�C�Y�̐ݒ�
	m_pBgObj->transform->SetSize(m_fBarLength, m_fBarBold);
}

//=============================================================
// [CProgressBar] �I��
//=============================================================
void CProgressBar::Uninit()
{
	gameObject->Destroy(true);
}

//=============================================================
// [CProgressBar] �w�i�̐F�ύX
//=============================================================
void CProgressBar::SetBGColor(const D3DXCOLOR& color)
{
	m_pBgObj->GetComponent<CPolygon>()->SetColor(color);
}

//=============================================================
// [CProgressBar] �����x
//=============================================================
void CProgressBar::SetAlpha(const float& fAlpha)
{
	m_fAlpha = fAlpha;

	// �o�[
	m_fillColor.a = fAlpha;
	m_nonFillCollor.a = fAlpha;

	// �w�i
	D3DXCOLOR bgColor = m_pBgObj->GetComponent<CPolygon>()->GetColor();
	bgColor.a = fAlpha;
	m_pBgObj->GetComponent<CPolygon>()->SetColor(bgColor);
}

//=============================================================
// [CProgressBar] �X�V
//=============================================================
void CProgressBar::Update()
{
	// �o�[�̃T�C�Y���v�Z����
	D3DXVECTOR2 barSize;
	barSize.x = (m_fBarLength - m_fBarSpace * m_pBars.size() - m_fSpace * 2) / m_pBars.size();
	barSize.y = m_fBarBold - m_fSpace * 2;

	// �w�i�̃T�C�Y
	m_pBgObj->transform->SetSize(m_fBarLength, m_fBarBold);

	// ���߂鐔�i�����j
	int nFillNum = static_cast<int>(m_nNumBar * m_fBarProgress);

	for (unsigned int i = 0; i < m_pBars.size(); i++)
	{
		// �F
		if (i < static_cast<unsigned int>(nFillNum))
			m_pBars[i]->GetComponent<CPolygon>()->SetColor(m_fillColor);
		else
			m_pBars[i]->GetComponent<CPolygon>()->SetColor(m_nonFillCollor);

		// �T�C�Y��ݒ肷��
		m_pBars[i]->transform->SetSize(barSize);

		// ���Ԋu�Ƀo�[��z�u����
		m_pBars[i]->transform->SetPos(m_fSpace * 2.0f + (barSize.x + m_fBarSpace) * i, m_fSpace);
	}
}


//=============================================================
// [CAdvancedBar] ������
//=============================================================
void CAdvancedBar::Init()
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^

	// �f�o�C�X�̎擾
	pDevice = CRenderer::GetInstance()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBar, nullptr);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBG, nullptr);

	VERTEX_2D* pVtx = nullptr; //���_���ւ̃|�C���^

	for (int i = 0; i < 2; i++)
	{
		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		if (i == 0)
			m_pVtxBG->Lock(0, 0, (void**)&pVtx, 0);
		else if (i == 1)
			m_pVtxBar->Lock(0, 0, (void**)&pVtx, 0);

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
		if (i == 0)
			m_pVtxBG->Unlock();
		else if (i == 1)
			m_pVtxBar->Unlock();
	}

	// ���_�̍X�V
	UpdateVertex();
}

//=============================================================
// [CAdvancedBar] �I��
//=============================================================
void CAdvancedBar::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBar != nullptr)
	{
		m_pVtxBar->Release();
		m_pVtxBar = nullptr;
	}
	if (m_pVtxBG != nullptr)
	{
		m_pVtxBG->Release();
		m_pVtxBG = nullptr;
	}
}

//=============================================================
// [CAdvancedBar] �`��
//=============================================================
void CAdvancedBar::DrawUI()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CRenderer::GetInstance()->GetDevice();

	for (int i = 0; i < 2; i++)
	{
		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		if (i == 0)
			pDevice->SetStreamSource(0, m_pVtxBG, 0, sizeof(VERTEX_2D));
		else if (i ==1)
			pDevice->SetStreamSource(0, m_pVtxBar, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		if (i == 1)
		{
			pDevice->SetTexture(0, m_texture);
		}
		else
		{
			pDevice->SetTexture(0, nullptr);
		}
		

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, //�v���~�e�B�u�̎��
			0, //�`�悷��ŏ��̒��_�C���f�b�N�X
			2); //�`�悷��v���~�e�B�u��
	}
}

//=============================================================
// [CAdvancedBar] ���_�̍X�V
//=============================================================
void CAdvancedBar::UpdateVertex()
{
	VERTEX_2D* pVtx; //���_���ւ̃|�C���^

	// ���_���W�𓱂��o��
	D3DXVECTOR3 vtxPos[4];
	switch (m_align)
	{
	case CAdvancedBar::LEFT:
		vtxPos[0] = { 0.0f, -m_fBold / 2, 0.0f };
		vtxPos[1] = { m_fLength, -m_fBold / 2, 0.0f };
		vtxPos[2] = { 0.0f, m_fBold / 2, 0.0f };
		vtxPos[3] = { m_fLength, m_fBold / 2, 0.0f };
		break;
	case CAdvancedBar::CENTER:
		vtxPos[0] = { -m_fLength / 2, -m_fBold / 2, 0.0f };
		vtxPos[1] = { m_fLength / 2, -m_fBold / 2, 0.0f };
		vtxPos[2] = { -m_fLength / 2, m_fBold / 2, 0.0f };
		vtxPos[3] = { m_fLength / 2, m_fBold / 2, 0.0f };
		break;
	}

	//----------------------------------------------------------------------
	// �o�[

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBar->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = vtxPos[0];
	pVtx[1].pos = vtxPos[1];
	pVtx[2].pos = vtxPos[2];
	pVtx[3].pos = vtxPos[3];

	// �o�[�̒�����ύX����
	pVtx[1].pos.x -= (1.0f - m_fProgress) * m_fLength;
	pVtx[3].pos.x -= (1.0f - m_fProgress) * m_fLength;

	// �w��ʒu�Ɉړ�������
	pVtx[0].pos += transform->GetWPos();
	pVtx[1].pos += transform->GetWPos();
	pVtx[2].pos += transform->GetWPos();
	pVtx[3].pos += transform->GetWPos();

	//���_�J���[
	pVtx[0].col = m_color[0];
	pVtx[1].col = m_color[1] + m_color[0] * (1.0f - m_fProgress);
	pVtx[2].col = m_color[2];
	pVtx[3].col = m_color[3] + m_color[2] * (1.0f - m_fProgress);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_fProgress, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_fProgress, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBar->Unlock();

	//----------------------------------------------------------------------
	// �w�i

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBG->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = vtxPos[0];
	pVtx[1].pos = vtxPos[1];
	pVtx[2].pos = vtxPos[2];
	pVtx[3].pos = vtxPos[3];

	// �w��ʒu�Ɉړ�������
	pVtx[0].pos += transform->GetWPos();
	pVtx[1].pos += transform->GetWPos();
	pVtx[2].pos += transform->GetWPos();
	pVtx[3].pos += transform->GetWPos();

	//���_�J���[
	pVtx[0].col = m_bgColor;
	pVtx[1].col = m_bgColor;
	pVtx[2].col = m_bgColor;
	pVtx[3].col = m_bgColor;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBG->Unlock();
}

//=============================================================
// [CAdvancedBar] �F�ύX
//=============================================================
void CAdvancedBar::SetColor(int index, D3DXCOLOR color)
{
	if (0 <= index && index < 4)
	{
		m_color[index] = color;
	}

	// �X�V
	UpdateVertex();
}

//=============================================================
// [CAdvancedBar] �F�ύX
//=============================================================
void CAdvancedBar::SetColor(D3DXCOLOR color)
{
	for (int i = 0; i < 4; i++)
	{
		m_color[i] = color;
	}

	// �X�V
	UpdateVertex();
}

//=============================================================
// [CAdvancedBar] �w�i�F�ύX
//=============================================================
void CAdvancedBar::SetBGColor(D3DXCOLOR color)
{
	m_bgColor = color;

	// �X�V
	UpdateVertex();
}

//=============================================================
// [CAdvancedBar] �i���x�ύX
//=============================================================
void CAdvancedBar::SetProgress(const float& percent)
{
	m_fProgress = percent;

	// �X�V
	UpdateVertex();
}

//=============================================================
// [CAdvancedBar] �����̕ύX
//=============================================================
void CAdvancedBar::SetLength(const float& length)
{
	m_fLength = length;

	// �X�V
	UpdateVertex();
}

//=============================================================
// [CAdvancedBar] �����̕ύX
//=============================================================
void CAdvancedBar::SetBold(const float& bold)
{
	m_fBold = bold;

	// �X�V
	UpdateVertex();
}

//=============================================================
// [CAdvancedBar] �e�N�X�`���̐ݒ�
//=============================================================
void CAdvancedBar::SetTexture(std::string sPath)
{
	CDataTexture* pTex = CDataManager::GetInstance()->RefTexture(sPath);

	if (pTex != nullptr)
	{
		m_texture = pTex->GetTexture();
	}
}

//=============================================================
// [CAdvancedBar] ����̕ύX
//=============================================================
void CAdvancedBar::SetAlign(const ALIGN& align)
{
	m_align = align;

	// �X�V
	UpdateVertex();
}