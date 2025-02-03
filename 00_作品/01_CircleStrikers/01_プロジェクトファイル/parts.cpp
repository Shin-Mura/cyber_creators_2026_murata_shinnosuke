//========================================================================================================
//
//�p�[�c����[parts.cpp]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "parts.h"
#include "manager.h"
#include "renderer.h"

//========================================================================================================
//�R���X�g���N�^
//========================================================================================================
Parts::Parts(int nPriority)
{
	//�����o�ϐ�������������
	this->m_nId = -1;
	this->m_mesh.pMesh = nullptr;   //���b�V��
	this->m_mesh.pBuffMat = nullptr;   //�}�e���A��
	this->m_mesh.dwMat = 0;   //�}�e���A���̐�
	this->m_pTexture = nullptr;   //�e�N�X�`��
	D3DXMatrixIdentity(&this->m_mtxWorld);   //���[���h�}�g���b�N�X
	this->m_nIdParent = -1;   //�e
	this->m_pos = { 0.0f, 0.0f, 0.0f };   //�ʒu
	this->m_rot = { 0.0f, 0.0f, 0.0f };   //����
}

//========================================================================================================
//�f�X�g���N�^
//========================================================================================================
Parts::~Parts()
{
}

//========================================================================================================
//����������
//========================================================================================================
void Parts::Init()
{
}

//========================================================================================================
//�I������
//========================================================================================================
void Parts::Uninit()
{
}

//========================================================================================================
//�X�V����
//========================================================================================================
void Parts::Update()
{
}

//========================================================================================================
//�`�揈��
//========================================================================================================
void Parts::Draw(D3DXMATRIX mtxWorldParent)
{
	D3DXMATRIX mtxRot, mtxTrans;   //�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;   //���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;   //�}�e���A���f�[�^�ւ̃|�C���^

	//�f�o�C�X���擾����
	LPDIRECT3DDEVICE9 pDevice = Manager::Get()->GetRenderer()->GetDevice();   //�f�o�C�X�ւ̃|�C���^

	//���[���h�}�g���b�N�X������������
	D3DXMatrixIdentity(&this->m_mtxWorld);

	//�����𔽉f����
	D3DXMatrixRotationYawPitchRoll(&mtxRot, this->m_rot.y, this->m_rot.x, this->m_rot.z);
	D3DXMatrixMultiply(&this->m_mtxWorld, &this->m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f����
	D3DXMatrixTranslation(&mtxTrans, this->m_pos.x, this->m_pos.y, this->m_pos.z);
	D3DXMatrixMultiply(&this->m_mtxWorld, &this->m_mtxWorld, &mtxTrans);

	//���Βl�ʒu�𔽉f����
	D3DXMatrixMultiply(&this->m_mtxWorld, &this->m_mtxWorld, &mtxWorldParent);

	//���[���h�}�g���b�N�X��ݒ肷��
	pDevice->SetTransform(D3DTS_WORLD, &this->m_mtxWorld);

	//���݂̃}�e���A�����擾����
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾����
	pMat = (D3DXMATERIAL*)this->m_mesh.pBuffMat->GetBufferPointer();

	for (int i = 0; i < (int)this->m_mesh.dwMat; i++)
	{
		//�}�e���A����ݒ肷��
		pDevice->SetMaterial(&pMat[i].MatD3D);

		//�e�N�X�`����ݒ肷��
		pDevice->SetTexture(0, this->m_pTexture);

		//�p�[�c�̕`��
		this->m_mesh.pMesh->DrawSubset(i);
	}
}