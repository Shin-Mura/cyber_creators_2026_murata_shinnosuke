//========================================================================================================
//
//���ʏ���[plane.cpp]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "plane.h"
#include "manager.h"
#include "object.h"
#include "transform.h"

//�ÓI�����o�ϐ�������������
const D3DXVECTOR2 Plane::BASE_SIZE = { 200.0f, 200.0f };   //��{�T�C�Y

//========================================================================================================
//����������
//========================================================================================================
void Plane::Init()
{
	//�f�o�C�X���擾����
	Renderer* pRenderer = Manager::Get()->GetRenderer();   //�����_���[
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();   //�f�o�C�X�ւ̃|�C���^

	//���_�o�b�t�@�𐶐�����
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,   //�m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffer,
		NULL);
}

//========================================================================================================
//�I������
//========================================================================================================
void Plane::Uninit()
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
void PlaneXZ::Update()
{
	//���_���W�����b�N���āA���_���ւ̃|�C���^���擾����
	VERTEX_3D* pVtx;   //���_���W
	this->GetVtxBuffer()->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W��ݒ肷��
	pVtx[0].pos = { -Plane::BASE_SIZE.x / 2, 0.0f, +Plane::BASE_SIZE.y / 2 };
	pVtx[1].pos = { +Plane::BASE_SIZE.x / 2, 0.0f, +Plane::BASE_SIZE.y / 2 };
	pVtx[2].pos = { -Plane::BASE_SIZE.x / 2, 0.0f, -Plane::BASE_SIZE.y / 2 };
	pVtx[3].pos = { +Plane::BASE_SIZE.x / 2, 0.0f, -Plane::BASE_SIZE.y / 2 };

	//�@���x�N�g����ݒ肷��
	pVtx[0].nor = { 0.0f, 1.0f, 0.0f };
	pVtx[1].nor = { 0.0f, 1.0f, 0.0f };
	pVtx[2].nor = { 0.0f, 1.0f, 0.0f };
	pVtx[3].nor = { 0.0f, 1.0f, 0.0f };

	//���_�J���[��ݒ肷��
	D3DXCOLOR color = GetColor();   //�F
	pVtx[0].col = color;
	pVtx[1].col = color;
	pVtx[2].col = color;
	pVtx[3].col = color;

	//�e�N�X�`�����W��ݒ肷��
	pVtx[0].tex = { 0.0f, 0.0f };
	pVtx[1].tex = { 1.0f, 0.0f };
	pVtx[2].tex = { 0.0f, 1.0f };
	pVtx[3].tex = { 1.0f, 1.0f };

	//���_�o�b�t�@���A�����b�N����
	this->GetVtxBuffer()->Unlock();
}

//========================================================================================================
//�X�V����
//========================================================================================================
void PlaneY::Update()
{
	//���_���W�����b�N���āA���_���ւ̃|�C���^���擾����
	VERTEX_3D* pVtx;   //���_���W
	this->GetVtxBuffer()->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W��ݒ肷��
	pVtx[0].pos = { -Plane::BASE_SIZE.x / 2, +Plane::BASE_SIZE.y / 2, 0.0f };
	pVtx[1].pos = { +Plane::BASE_SIZE.x / 2, +Plane::BASE_SIZE.y / 2, 0.0f };
	pVtx[2].pos = { -Plane::BASE_SIZE.x / 2, -Plane::BASE_SIZE.y / 2, 0.0f };
	pVtx[3].pos = { +Plane::BASE_SIZE.x / 2, -Plane::BASE_SIZE.y / 2, 0.0f };

	//�@���x�N�g����ݒ肷��
	pVtx[0].nor = { 0.0f, 1.0f, 0.0f };
	pVtx[1].nor = { 0.0f, 1.0f, 0.0f };
	pVtx[2].nor = { 0.0f, 1.0f, 0.0f };
	pVtx[3].nor = { 0.0f, 1.0f, 0.0f };

	//���_�J���[��ݒ肷��
	D3DXCOLOR color = GetColor();   //�F
	pVtx[0].col = color;
	pVtx[1].col = color;
	pVtx[2].col = color;
	pVtx[3].col = color;

	//�e�N�X�`�����W��ݒ肷��
	pVtx[0].tex = { 0.0f, 0.0f };
	pVtx[1].tex = { 1.0f, 0.0f };
	pVtx[2].tex = { 0.0f, 1.0f };
	pVtx[3].tex = { 1.0f, 1.0f };

	//���_�o�b�t�@���A�����b�N����
	this->GetVtxBuffer()->Unlock();
}

//========================================================================================================
//�`�揈��
//========================================================================================================
void Plane::Draw()
{
	//�f�o�C�X���擾����
	Renderer* pRenderer = Manager::Get()->GetRenderer();   //�����_���[
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();   //�f�o�C�X�ւ̃|�C���^

	//���[���h�}�g���b�N�X��ݒ肷��
	D3DXMATRIX mtxWorld = this->GetObj()->GetComponent<Transform>()->GetMtxWorld();
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//���_�o�b�t�@���e�[�^�X�g���[���ɐݒ肷��
	pDevice->SetStreamSource(0, this->m_pVtxBuffer, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g��ݒ肷��
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`����ݒ肷��
	pDevice->SetTexture(0, this->GetTexture());

	//�`�悷��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//========================================================================================================
//�`�揈��
//========================================================================================================
void Billboard::Draw()
{
	D3DXMATRIX mtxTrans;   //�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView, mtxViewInverse;   //�r���[�}�g���b�N�X�擾�p

	//�f�o�C�X���擾����
	LPDIRECT3DDEVICE9 pDevice = Manager::Get()->GetRenderer()->GetDevice();   //�f�o�C�X�ւ̃|�C���^

	//���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�A���t�@�e�X�g��L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//Z�o�b�t�@�̏������݂𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	if (this->m_isMultiply)
	{//���Z��������ꍇ
		//���u�����f�B���O�����Z�����ɐݒ�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	//�J�����̋t�s������߂�
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);
	D3DXMatrixInverse(&mtxViewInverse, NULL, &mtxView);

	//Y���r���{�[�h���m�F����
	if (this->m_isYAxis)
	{
		//Y����]���̑ł�����
		mtxViewInverse._21 = 0.0f;
		mtxViewInverse._22 = 1.0f;
		mtxViewInverse._23 = 0.0f;
	}

	//�ړ����̑ł�����
	mtxViewInverse._41 = 0.0f;
	mtxViewInverse._42 = 0.0f;
	mtxViewInverse._43 = 0.0f;

	//���[���h�}�g���b�N�X���擾����
	D3DXMATRIX mtxWorld = this->GetObj()->GetComponent<Transform>()->GetMtxWorld();

	//�t�s��𔽉f����
	D3DXMatrixMultiply(&mtxViewInverse, &mtxViewInverse, &mtxWorld);

	//���[���h�}�g���b�N�X��ݒ肷��
	pDevice->SetTransform(D3DTS_WORLD, &mtxViewInverse);

	//���_�o�b�t�@���e�[�^�X�g���[���ɐݒ肷��
	pDevice->SetStreamSource(0, this->GetVtxBuffer(), 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g��ݒ肷��
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`����ݒ肷��
	pDevice->SetTexture(0, this->GetTexture());   //�ݒ�

	//�`�悷��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//Z�o�b�t�@�̏������݂�L���ɂ���
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//�A���t�@�e�X�g�𖳌��ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//���C�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}