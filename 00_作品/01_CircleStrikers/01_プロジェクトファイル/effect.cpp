//========================================================================================================
//
//�G�t�F�N�g�̏���[effect.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "effect.h"
#include "manager.h"
#include "texture.h"

//========================================================================================================
//�R���X�g���N�^
//========================================================================================================
Effect::Effect()
{
	//�����o�ϐ�������������
	this->m_pVtxBuffer = nullptr;   //���_�o�b�t�@
	this->m_pTexture = nullptr;   //�e�N�X�`��
	D3DXMatrixIdentity(&this->m_mtxWorld);   //���[���h�}�g���b�N�X
	this->m_pos = { 0.0f, 0.0f, 0.0f };   //�ʒu
	this->m_color = { 1.0f, 1.0f, 1.0f, 1.0f };   //�F
	this->m_fRadius = 0.0f;   //���a
}

//========================================================================================================
//�f�X�g���N�^
//========================================================================================================
Effect::~Effect()
{
}

//========================================================================================================
//����������
//========================================================================================================
void Effect::Init()
{
	//�f�o�C�X���擾����
	LPDIRECT3DDEVICE9 pDevice = Manager::Get()->GetRenderer()->GetDevice();

	//���_�o�b�t�@�𐶐�����
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,   //�m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&this->m_pVtxBuffer,
		nullptr);

	//�X�V�������s��
	this->Update();
}

//========================================================================================================
//�I������
//========================================================================================================
void Effect::Uninit()
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
void Effect::Update()
{
	//���_���W�����b�N���āA���_���ւ̃|�C���^���擾����
	VERTEX_3D* pVtx;   //���_���W
	this->m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W��ݒ肷��
	pVtx[0].pos = { -this->m_fRadius, +this->m_fRadius, 0.0f };
	pVtx[1].pos = { +this->m_fRadius, +this->m_fRadius, 0.0f };
	pVtx[2].pos = { -this->m_fRadius, -this->m_fRadius, 0.0f };
	pVtx[3].pos = { +this->m_fRadius, -this->m_fRadius, 0.0f };

	//�@���x�N�g����ݒ肷��
	pVtx[0].nor = { 0.0f, 0.0f, -1.0f };
	pVtx[1].nor = { 0.0f, 0.0f, -1.0f };
	pVtx[2].nor = { 0.0f, 0.0f, -1.0f };
	pVtx[3].nor = { 0.0f, 0.0f, -1.0f };

	//���_�J���[��ݒ肷��
	pVtx[0].col = this->m_color;
	pVtx[1].col = this->m_color;
	pVtx[2].col = this->m_color;
	pVtx[3].col = this->m_color;

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
void Effect::Draw()
{
	D3DXMATRIX mtxTrans;   //�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;   //�r���[�}�g���b�N�X�擾�p

	//�f�o�C�X���擾����
	Renderer* pRenderer = Manager::Get()->GetRenderer();   //�����_���[
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();   //�f�o�C�X�ւ̃|�C���^

	//���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�A���t�@�e�X�g��L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//Z�o�b�t�@�̏������݂𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//���[���h�}�g���b�N�X������������
	D3DXMatrixIdentity(&m_mtxWorld);

	//�r���[�}�g���b�N�X���擾����
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�|���S�����J�����ɑ΂��Đ��ʂɂ���
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);   //�t�s������߂�

	//�ړ����̑ł�����
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	//�ʒu�𔽉f����
	D3DXMatrixTranslation(&mtxTrans, this->m_pos.x, this->m_pos.y, this->m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X��ݒ肷��
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���e�[�^�X�g���[���ɐݒ肷��
	pDevice->SetStreamSource(0, m_pVtxBuffer, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g��ݒ肷��
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`����ݒ肷��
	pDevice->SetTexture(0, m_pTexture);   //�ݒ�

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