//=============================================================
//
// �X�J�C�{�b�N�X [skybox.cpp]
// Author: Ito Kotaro
// 
//=============================================================
#include "skybox.h"
#include "manager.h"
#include <fstream>

// �ÓI�����o�ϐ��̏�����
const float CSkybox::SKYBOX_SIZE = 10.0f;

//=============================================================
// [CSkybox] ������
//=============================================================
void CSkybox::Init()
{
	// �ϐ��̏�����
	for (int i = 0; i < 6; i++)
	{
		m_pVtxBuff[i] = nullptr;		// ���_�o�b�t�@
		m_pTexture[i] = nullptr;		// �e�N�X�`��
	}
	m_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// �J���[

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	for (int i = 0; i < 6; i++)
	{
		//���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff[i], NULL);
		VERTEX_3D* pVtx; //���_���ւ̃|�C���^

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff[i]->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		switch (i)
		{
		case UP:
			pVtx[0].pos = D3DXVECTOR3(-SKYBOX_SIZE / 2, SKYBOX_SIZE / 2, -SKYBOX_SIZE / 2);
			pVtx[1].pos = D3DXVECTOR3(SKYBOX_SIZE / 2, SKYBOX_SIZE / 2, -SKYBOX_SIZE / 2);
			pVtx[2].pos = D3DXVECTOR3(-SKYBOX_SIZE / 2, SKYBOX_SIZE / 2, SKYBOX_SIZE / 2);
			pVtx[3].pos = D3DXVECTOR3(SKYBOX_SIZE / 2, SKYBOX_SIZE / 2, SKYBOX_SIZE / 2);
			break;
		case DOWN:
			pVtx[0].pos = D3DXVECTOR3(-SKYBOX_SIZE / 2, -SKYBOX_SIZE / 2, SKYBOX_SIZE / 2);
			pVtx[1].pos = D3DXVECTOR3(SKYBOX_SIZE / 2, -SKYBOX_SIZE / 2, SKYBOX_SIZE / 2);
			pVtx[2].pos = D3DXVECTOR3(-SKYBOX_SIZE / 2, -SKYBOX_SIZE / 2, -SKYBOX_SIZE / 2);
			pVtx[3].pos = D3DXVECTOR3(SKYBOX_SIZE / 2, -SKYBOX_SIZE / 2, -SKYBOX_SIZE / 2);
			break;
		case FRONT:
			pVtx[0].pos = D3DXVECTOR3(-SKYBOX_SIZE / 2, SKYBOX_SIZE / 2, SKYBOX_SIZE / 2);
			pVtx[1].pos = D3DXVECTOR3(SKYBOX_SIZE / 2, SKYBOX_SIZE / 2, SKYBOX_SIZE / 2);
			pVtx[2].pos = D3DXVECTOR3(-SKYBOX_SIZE / 2, -SKYBOX_SIZE / 2, SKYBOX_SIZE / 2);
			pVtx[3].pos = D3DXVECTOR3(SKYBOX_SIZE / 2, -SKYBOX_SIZE / 2, SKYBOX_SIZE / 2);
			break;
		case BACK:
			pVtx[0].pos = D3DXVECTOR3(SKYBOX_SIZE / 2, SKYBOX_SIZE / 2, -SKYBOX_SIZE / 2);
			pVtx[1].pos = D3DXVECTOR3(-SKYBOX_SIZE / 2, SKYBOX_SIZE / 2, -SKYBOX_SIZE / 2);
			pVtx[2].pos = D3DXVECTOR3(SKYBOX_SIZE / 2, -SKYBOX_SIZE / 2, -SKYBOX_SIZE / 2);
			pVtx[3].pos = D3DXVECTOR3(-SKYBOX_SIZE / 2, -SKYBOX_SIZE / 2, -SKYBOX_SIZE / 2);
			break;
		case LEFT:
			pVtx[0].pos = D3DXVECTOR3(-SKYBOX_SIZE / 2, SKYBOX_SIZE / 2, -SKYBOX_SIZE / 2);
			pVtx[1].pos = D3DXVECTOR3(-SKYBOX_SIZE / 2, SKYBOX_SIZE / 2, SKYBOX_SIZE / 2);
			pVtx[2].pos = D3DXVECTOR3(-SKYBOX_SIZE / 2, -SKYBOX_SIZE / 2, -SKYBOX_SIZE / 2);
			pVtx[3].pos = D3DXVECTOR3(-SKYBOX_SIZE / 2, -SKYBOX_SIZE / 2, SKYBOX_SIZE / 2);
			break;
		case RIGHT:
			pVtx[0].pos = D3DXVECTOR3(SKYBOX_SIZE / 2, SKYBOX_SIZE / 2, SKYBOX_SIZE / 2);
			pVtx[1].pos = D3DXVECTOR3(SKYBOX_SIZE / 2, SKYBOX_SIZE / 2, -SKYBOX_SIZE / 2);
			pVtx[2].pos = D3DXVECTOR3(SKYBOX_SIZE / 2, -SKYBOX_SIZE / 2, SKYBOX_SIZE / 2);
			pVtx[3].pos = D3DXVECTOR3(SKYBOX_SIZE / 2, -SKYBOX_SIZE / 2, -SKYBOX_SIZE / 2);
			break;
		}

		//�@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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
		m_pVtxBuff[i]->Unlock();
	}

	// �e�N�X�`���^�C�v
	SetTextureType(TEXTURETYPE::SINGLE);
}

//=============================================================
// [CSkybox] �I��
//=============================================================
void CSkybox::Uninit()
{
	// �j������
	for (int i = 0; i < 6; i++)
	{
		// ���_�o�b�t�@�̔j��
		if (m_pVtxBuff[i] != nullptr)
		{
			m_pVtxBuff[i]->Release();
			m_pVtxBuff[i] = nullptr;
		}
	}
}

//=============================================================
// [CSkybox] �`��
//=============================================================
void CSkybox::Draw()
{
	if (m_pTexture[0] == nullptr)
	{ // �e�N�X�`�����ݒ肳��Ă��Ȃ��Ƃ��͖���
		return;
	}

	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();		// �f�o�C�X���擾
	D3DXMATRIX mtx = m_pCameraTransform->GetTranslationMatrix();

	// ���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtx);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	for (int i = 0; i < 6; i++)
	{
		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, m_pVtxBuff[i], 0, sizeof(VERTEX_3D));

		// �e�N�X�`���̐ݒ�
		if (m_textureType == TEXTURETYPE::SINGLE)
		{
			pDevice->SetTexture(0, m_pTexture[0]);
		}
		else
		{
			pDevice->SetTexture(0, m_pTexture[i]);
		}

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, //�v���~�e�B�u�̎��
			0, //�`�悷��ŏ��̒��_�C���f�b�N�X
			2);				//�`�悷��v���~�e�B�u��
	}

	// ���C�g��L���ɖ߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//=============================================================
// [CSkybox] �e�N�X�`���^�C�v�̕ύX
//=============================================================
void CSkybox::SetTextureType(TEXTURETYPE textureType)
{
	VERTEX_3D* pVtx; // ���_���ւ̃|�C���^
	m_textureType = textureType;

	for (int i = 0; i < 6; i++)
	{
		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff[i]->Lock(0, 0, (void**)&pVtx, 0);

		// �e�N�X�`�����W�̐ݒ�
		switch (m_textureType)
		{
		case CSkybox::SINGLE:
			switch (i)
			{
			case UP:
				pVtx[0].tex = D3DXVECTOR2(1.0f / 4 * 1, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f / 4 * 2, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(1.0f / 4 * 1, 1.0f / 3 * 1);
				pVtx[3].tex = D3DXVECTOR2(1.0f / 4 * 2, 1.0f / 3 * 1);
				break;
			case DOWN:
				pVtx[0].tex = D3DXVECTOR2(1.0f / 4 * 1, 1.0f / 3 * 2);
				pVtx[1].tex = D3DXVECTOR2(1.0f / 4 * 2, 1.0f / 3 * 2);
				pVtx[2].tex = D3DXVECTOR2(1.0f / 4 * 1, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f / 4 * 2, 1.0f);
				break;
			case BACK:
				pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f / 3 * 1);
				pVtx[1].tex = D3DXVECTOR2(1.0f / 4 * 1, 1.0f / 3 * 1);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f / 3 * 2);
				pVtx[3].tex = D3DXVECTOR2(1.0f / 4 * 1, 1.0f / 3 * 2);
				break;
			case LEFT:
				pVtx[0].tex = D3DXVECTOR2(1.0f / 4 * 1, 1.0f / 3 * 1);
				pVtx[1].tex = D3DXVECTOR2(1.0f / 4 * 2, 1.0f / 3 * 1);
				pVtx[2].tex = D3DXVECTOR2(1.0f / 4 * 1, 1.0f / 3 * 2);
				pVtx[3].tex = D3DXVECTOR2(1.0f / 4 * 2, 1.0f / 3 * 2);
				break;
			case FRONT:
				pVtx[0].tex = D3DXVECTOR2(1.0f / 4 * 2, 1.0f / 3 * 1);
				pVtx[1].tex = D3DXVECTOR2(1.0f / 4 * 3, 1.0f / 3 * 1);
				pVtx[2].tex = D3DXVECTOR2(1.0f / 4 * 2, 1.0f / 3 * 2);
				pVtx[3].tex = D3DXVECTOR2(1.0f / 4 * 3, 1.0f / 3 * 2);
				break;
			case RIGHT:
				pVtx[0].tex = D3DXVECTOR2(1.0f / 4 * 3, 1.0f / 3 * 1);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f / 3 * 1);
				pVtx[2].tex = D3DXVECTOR2(1.0f / 4 * 3, 1.0f / 3 * 2);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f / 3 * 2);
				break;
			}
			break;
		case CSkybox::SPLIT:
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			break;
		}

		// ���_�o�b�t�@���A�����b�N����
		m_pVtxBuff[i]->Unlock();
	}
}

//=============================================================
// [CSkybox] �e�N�X�`���̐ݒ�
//=============================================================
void CSkybox::SetTexture(const int& idx, const std::string& path)
{
	if (0 <= idx && idx < 6)
	{
		CDataTexture* pTexData = CDataManager::GetInstance()->RefTexture(path);
		m_pTexture[idx] = pTexData->GetTexture();
	}
}

//=============================================================
// [CSkybox] �X�J�C�{�b�N�X�̓ǂݍ���
//=============================================================
void CSkybox::LoadSkybox(const std::string& sPath)
{
	// json�t�@�C����ǂݍ���
	std::ifstream ifs(sPath.c_str());

	if (ifs.fail())
	{ // �t�@�C���̓ǂݍ��݂Ɏ��s
		return;
	}

	// json�`���ɕϊ�
	std::string sInputData((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	auto jSkybox = json::parse(sInputData);

	// �^�C�v��ݒ肷��
	if (jSkybox.contains("type"))
	{
		if (jSkybox["type"] == "single")
		{ // 1��
			SetTextureType(TEXTURETYPE::SINGLE);
		}
		else if (jSkybox["type"] == "split")
		{ // �������i6���j
			SetTextureType(TEXTURETYPE::SPLIT);
		}
	}

	// �e�N�X�`����ύX����
	if (jSkybox.contains("texture"))
	{
		for (unsigned int i = 0; i < jSkybox["texture"].size(); i++)
		{
			SetTexture(i, jSkybox["texture"][i]);
		}
	}

	ifs.close();
}