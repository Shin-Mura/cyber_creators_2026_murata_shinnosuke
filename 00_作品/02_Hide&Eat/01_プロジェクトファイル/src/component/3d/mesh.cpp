//=============================================================
//
// ���b�V���R���|�[�l���g [mesh.cpp]
// Author: Ito Kotaro
//
//=============================================================
#include "mesh.h"
#include "manager.h"
#include <Shlwapi.h>								// �t�@�C�����݃`�F�b�N�Ɏg�p
#pragma comment(lib, "Shlwapi.lib")			// �t�@�C�����݃`�F�b�N�Ɏg�p

//=============================================================
// [CMesh] �R���X�g���N�^
//=============================================================
CMesh::CMesh()
{
	m_pMesh = nullptr;
	m_pShadowMesh = nullptr;
	m_pBuffMat = nullptr;
	m_dwNumMat = 0;
	m_fAlpha = nullptr;
}

//=============================================================
// [CMesh] �����t���R���X�g���N�^
//=============================================================
CMesh::CMesh(std::string sPath, bool bShadow) : CMesh()
{
	LoadMeshX(sPath, bShadow);
}

//=============================================================
// [CMesh] ������
//=============================================================
void CMesh::Init()
{
	
}

//=============================================================
// [CMesh] �I��
//=============================================================
void CMesh::Uninit()
{
	// ���[�J���}�e���A���̔j��
	if (m_fAlpha != nullptr)
	{
		delete m_fAlpha;
		m_fAlpha = nullptr;
	}
}

//=============================================================
// [CMesh] �`��
//=============================================================
void CMesh::Draw()
{
	if (CShadow::USE_SHADOW)
	{ // �e�g�p���̓X�L�b�v����
		return;
	}

	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();
	D3DMATERIAL9 matDef;					// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;					// �}�e���A���f�[�^�ւ̃|�C���^

	if (m_pMesh == NULL || m_pBuffMat == NULL)
		return;

	// ���[���h�}�g���b�N�X�̐ݒ�
	if (!IsEnabledShader()) pDevice->SetTransform(D3DTS_WORLD, &transform->GetMatrix());

	// ���݂̃}�e���A�����擾
	if (!IsEnabledShader()) pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	Component::BeginPass();
	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		// �s�����x
		float fAlpha, fBeforeAlpha;
		fBeforeAlpha = pMat[nCntMat].MatD3D.Diffuse.a;
		if (m_fAlpha != nullptr)
		{
			fAlpha = *m_fAlpha;
		}
		else
		{
			fAlpha = pMat[nCntMat].MatD3D.Diffuse.a;
		}

		// �}�e���A���̐ݒ�
		pMat[nCntMat].MatD3D.Diffuse.a = fAlpha;
		if (!IsEnabledShader()) pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		LPDIRECT3DTEXTURE9 tex;
		if (pMat[nCntMat].pTextureFilename != NULL)
		{ // �e�N�X�`��������Ƃ�
			tex = m_apTexture[nCntMat];
		}
		else
		{
			tex = NULL;
		}
		if (!IsEnabledShader()) pDevice->SetTexture(0, tex);

		// �V�F�[�_�[�ɏ���n��
		Shader::ParamData paramData;
		paramData.color = { pMat[nCntMat].MatD3D.Diffuse.r, pMat[nCntMat].MatD3D.Diffuse.g, pMat[nCntMat].MatD3D.Diffuse.b, pMat[nCntMat].MatD3D.Diffuse.a };
		paramData.texture = tex;
		paramData.mtx = transform->GetMatrix();
		Component::SetParam(paramData);

		// ���f���i�p�[�c�j�̕`��
		m_pMesh->DrawSubset(nCntMat);

		// �}�e���A���ݒ��߂�
		pMat[nCntMat].MatD3D.Diffuse.a = fBeforeAlpha;
	}
	Component::EndPass();

	// �ۑ����Ă����}�e���A���ɖ߂�
	if (!IsEnabledShader()) pDevice->SetMaterial(&matDef);
}

//=============================================================
// [CMesh] X�t�@�C���̓ǂݍ���
//=============================================================
HRESULT CMesh::LoadMeshX(std::string sPath, bool bShadow)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	// �t�@�C���̑��݃`�F�b�N
	if (!PathFileExistsA(sPath.c_str())) return E_FAIL;

	// ���b�V������j��
	Uninit();

	// ���b�V����ǂݍ���
	CDataMesh* pMeshData = CDataManager::GetInstance()->RefMesh(sPath);
	if (pMeshData == nullptr)
	{ // ���s
		return E_FAIL;
	}

	// ���b�V���̃f�[�^���Q�Ƃ���
	m_pMesh = pMeshData->GetMesh();
	m_pBuffMat = pMeshData->GetBuffMat();
	m_dwNumMat = pMeshData->GetNumMat();

	// �e�p���b�V���̎擾
	if (CShadow::USE_SHADOW && bShadow)
	{
		m_pShadowMesh = pMeshData->GetShadowMesh();
	}

	// ���f���e�N�X�`���̓ǂݍ���
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	m_apTexture.resize(m_dwNumMat);
	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != nullptr)
		{ // �e�N�X�`��������Ƃ�

			// �e�N�X�`���̑��݃`�F�b�N
			if (!PathFileExistsA(pMat[nCntMat].pTextureFilename))
			{ // ���݂��Ȃ��Ƃ�
				pMat[nCntMat].pTextureFilename = nullptr;
				m_apTexture[nCntMat] = nullptr;
				continue;
			}

			// �e�N�X�`�����쐬
			m_apTexture[nCntMat] = CDataManager::GetInstance()->RefTexture(pMat[nCntMat].pTextureFilename)->GetTexture();
		}
		else
		{
			m_apTexture[nCntMat] = nullptr;
		}
	}

	return S_OK;
}

//=============================================================
// [CMesh] ���b�V���̃Z�b�g
//=============================================================
HRESULT CMesh::SetMesh(LPD3DXMESH pMesh)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	// ���b�V������j��
	Uninit();

	// ���b�V���̃f�[�^���Q�Ƃ���
	m_pMesh = pMesh;

	// ���f���e�N�X�`���̓ǂݍ���
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	m_apTexture.resize(m_dwNumMat);
	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != nullptr)
		{ // �e�N�X�`��������Ƃ�

			// �e�N�X�`���̑��݃`�F�b�N
			if (!PathFileExistsA(pMat[nCntMat].pTextureFilename))
			{ // ���݂��Ȃ��Ƃ�
				pMat[nCntMat].pTextureFilename = nullptr;
				m_apTexture[nCntMat] = nullptr;
				continue;
			}

			// �e�N�X�`�����쐬
			m_apTexture[nCntMat] = CDataManager::GetInstance()->RefTexture(pMat[nCntMat].pTextureFilename)->GetTexture();
		}
		else
		{
			m_apTexture[nCntMat] = nullptr;
		}
	}

	return S_OK;
}

//=============================================================
// [CMesh] �e�N�X�`���̐ݒ�
//=============================================================
void CMesh::SetTexture(int nIdx, LPDIRECT3DTEXTURE9 pTexture)
{
	if (0 <= nIdx && nIdx < (int)m_dwNumMat &&
		pTexture != nullptr)
	{ // �C���f�b�N�X�����e�l�̂Ƃ�
		m_apTexture[nIdx] = pTexture;
	}
}

//=============================================================
// [CMesh] ���[�J���}�e���A���̐ݒ�
//=============================================================
void CMesh::SetAlpha(const float& fAlpha)
{
	// �܂��쐬����Ă��Ȃ��ꍇ�͍쐬����
	if (m_fAlpha == nullptr)
	{
		m_fAlpha = new float;
	}

	// �ݒ��������
	*m_fAlpha = fAlpha;
}