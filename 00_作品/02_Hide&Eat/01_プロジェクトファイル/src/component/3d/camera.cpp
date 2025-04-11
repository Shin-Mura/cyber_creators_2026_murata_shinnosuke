//=============================================================
//
// �J�����R���|�[�l���g [camera.cpp]
// Author: Ito Kotaro
//
//=============================================================
#include "camera.h"
#include "manager.h"

//=============================================================
// [CCamera] ������
//=============================================================
void CCamera::Init()
{
	m_fClippingPlanesNear = 0.3f;
	m_fClippingPlanesFar = 800.0f;
	m_backColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	m_vecU = { 0.0f, 1.0f, 0.0f };
	m_posR = { 0.0f, 0.0f, 0.0f };
	m_fLength = 120.0f;
	m_viewport.MinZ = 0.0f;
	m_viewport.MaxZ = 1.0f;
	SetViewportPosition(0.0f, 0.0f);
	SetViewportSize((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT);
	m_bParallel = false;
	m_bVisible = true;
	m_bCustomPosR = false;
	m_fAmbient = 0.8f;

	// �X�J�C�{�b�N�X�̏�����
	m_pSkybox = new CSkybox(transform);
	m_pSkybox->Init();
}

//=============================================================
// [CCamera] �I��
//=============================================================
void CCamera::Uninit()
{
	// �X�J�C�{�b�N�X��j������
	if (m_pSkybox != nullptr)
	{
		m_pSkybox->Uninit();
		delete m_pSkybox;
		m_pSkybox = nullptr;
	}
}

//=============================================================
// [CCamera] �J�����̍X�V
//=============================================================
void CCamera::Update()
{
	if (!m_bCustomPosR)
	{
		D3DXMATRIX rotMtx = transform->GetRotationMatrix();
		m_posR = { 0.0f, 0.0f, m_fLength };
		D3DXVec3TransformCoord(&m_posR, &m_posR, &rotMtx);
		m_posR += transform->GetWPos();
	}

	// Z��]�i������x�N�g���j
	//D3DXVECTOR3 defUp = { 0.0f, 1.0f, 0.0f };
	//D3DXMATRIX mtxUp;
	//D3DXMatrixIdentity(&mtxUp);
	//D3DXMatrixRotationZ(&mtxUp, transform->GetWRot().z);
	//D3DXMatrixInverse(&mtxUp, NULL, &mtxUp);
	//D3DXVec3TransformCoord(&m_vecU, &defUp, &mtxUp);
	//D3DXVec3Normalize(&m_vecU, &m_vecU);

	//m_vecU = { sinf(transform->GetWRot().z), cosf(transform->GetWRot().z), tanf(transform->GetWRot().z) };
	//D3DXVec3Normalize(&m_vecU, &m_vecU);
}


//=============================================================
// [CCamera] �J�����̐ݒ菈��
//=============================================================
void CCamera::SetCamera(const bool& isSet)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	D3DXVECTOR2 rect = CManager::GetInstance()->GetWindowSize();
	// �v���W�F�N�V�����}�g���b�N�X���쐬
	if (!m_bParallel)
	{ // �������e
		D3DXMatrixPerspectiveFovLH(
			&m_mtxProjection,
			D3DXToRadian(45.0f),
			rect.x / rect.y,
			m_fClippingPlanesNear,
			m_fClippingPlanesFar);
	}
	else
	{ // ���s���e
		D3DXMatrixOrthoLH(
			&m_mtxProjection,
			rect.x,
			rect.y,
			m_fClippingPlanesNear,
			m_fClippingPlanesFar);

		// �X�P�[�����O����
		D3DXMATRIX mtxScale;
		D3DXMatrixIdentity(&mtxScale);
		D3DXMatrixScaling(&mtxScale, 10.0f, 10.0f, 1.0f);	//	�������e�̏ꍇZ������{�}�C�i�X�Ȃ̂�fabsf���g�p
		D3DXMatrixMultiply(&m_mtxProjection, &m_mtxProjection, &mtxScale);
	}


	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	if (isSet)
		pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXVECTOR3 pos = transform->GetWPos();
	D3DXMatrixLookAtLH(&m_mtxView, &pos, &m_posR, &m_vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	if (isSet)
		pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	// �r���[�|�[�g�̐ݒ�
	if (isSet)
		pDevice->SetViewport(&m_viewport);
}
