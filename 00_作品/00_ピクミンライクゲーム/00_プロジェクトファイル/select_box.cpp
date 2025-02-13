//========================================================================================================
//
//�I�����̏���[select_box.cpp]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "select_box.h"
#include "manager.h"
#include "renderer.h"

//�ÓI�����o�ϐ�������������
float SelectBox::INIT_FADE = 0.025f;

//========================================================================================================
//�R���X�g���N�^
//========================================================================================================
SelectBox::SelectBox()
{
	//�����o�ϐ�������������
	this->m_pVtxBuffer = nullptr;   //�o�b�t�@
	this->m_nPattern = 0;
	this->m_nOder = 0;
	this->m_pos = { 0.0f, 0.0f };   //�ʒu
	this->m_size = { 0.0f, 0.0f };   //�T�C�Y
	this->m_color = { 1.0f, 1.0f, 1.0f, 0.5f };   //�F
	this->m_isSelect = false;
	this->m_fFade = INIT_FADE;
}

//========================================================================================================
//�f�X�g���N�^
//========================================================================================================
SelectBox::~SelectBox()
{
}

//========================================================================================================
//����������
//========================================================================================================
void SelectBox::Init()
{
	//�f�o�C�X���擾����
	Renderer* pRenderer = Manager::Get()->GetRenderer();   //�����_���[
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();   //�f�o�C�X�ւ̃|�C���^

	//���_�o�b�t�@�𐶐�����
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,   //�m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffer,
		NULL);
}

//========================================================================================================
//�I������
//========================================================================================================
void SelectBox::Uninit()
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
void SelectBox::Update()
{
	//�I���t���O���m�F����
	if (this->m_isSelect == true)
	{//�I���t���O�������Ă���ꍇ
		//�����x���t�F�[�h����
		this->m_color.a += this->m_fFade;
		if (this->m_color.a >= 1.0f || this->m_color.a <= 0.0f)
		{//�ő�l or �ŏ��l�ɒB�����ꍇ
			//�t�F�[�h�𔽓]������
			this->m_fFade *= -1;
		}
	}
	else
	{//�����Ă��Ȃ��ꍇ
		//���Z�b�g����
		this->Reset();
	}

	//�I���t���O�����낷
	this->m_isSelect = false;

	//���_���W�����b�N���āA���_���ւ̃|�C���^���擾����
	VERTEX_2D* pVtx;   //���_���W
	this->m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W��ݒ肷��
	pVtx[0].pos = { this->m_pos.x - (this->m_size.x / 2), this->m_pos.y - (this->m_size.y / 2), 0.0f };
	pVtx[1].pos = { this->m_pos.x + (this->m_size.x / 2), this->m_pos.y - (this->m_size.y / 2), 0.0f };
	pVtx[2].pos = { this->m_pos.x - (this->m_size.x / 2), this->m_pos.y + (this->m_size.y / 2), 0.0f };
	pVtx[3].pos = { this->m_pos.x + (this->m_size.x / 2), this->m_pos.y + (this->m_size.y / 2), 0.0f };

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[��ݒ肷��
	pVtx[0].col = this->m_color;
	pVtx[1].col = this->m_color;
	pVtx[2].col = this->m_color;
	pVtx[3].col = this->m_color;

	//�e�N�X�`�����W��ݒ肷��
	pVtx[0].tex = { 0.0f, (1.0f / this->m_nPattern) * this->m_nOder };
	pVtx[1].tex = { 1.0f, (1.0f / this->m_nPattern) * this->m_nOder };
	pVtx[2].tex = { 0.0f, (1.0f / this->m_nPattern) * (this->m_nOder + 1) };
	pVtx[3].tex = { 1.0f, (1.0f / this->m_nPattern) * (this->m_nOder + 1) };

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuffer->Unlock();
}

//========================================================================================================
//�`�揈��
//========================================================================================================
void SelectBox::Draw(LPDIRECT3DTEXTURE9 pTexture)
{
	//�f�o�C�X���擾����
	LPDIRECT3DDEVICE9 pDevice = Manager::Get()->GetRenderer()->GetDevice();   //�f�o�C�X�ւ̃|�C���^

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ肷��
	pDevice->SetStreamSource(0, this->m_pVtxBuffer, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g��ݒ肷��
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`����ݒ肷��
	pDevice->SetTexture(0, pTexture);

	//�|���S����`�悷��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//========================================================================================================
//��������
//========================================================================================================
SelectBox* SelectBox::Create(D3DXVECTOR2 pos, D3DXVECTOR2 size)
{
	//�����𐶐�����
	SelectBox* pSelectBox = new SelectBox;

	//����ݒ肷��
	pSelectBox->m_pos = pos;   //�ʒu
	pSelectBox->m_size = size;   //�T�C�Y

	//����������
	pSelectBox->Init();

	//������Ԃ�
	return pSelectBox;
}