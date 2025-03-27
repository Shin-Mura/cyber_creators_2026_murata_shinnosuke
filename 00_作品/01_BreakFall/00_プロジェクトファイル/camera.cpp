//========================================================================================================
//
//�J��������[camera.cpp]
// Auhtor Murata Shinnosuke
//
//========================================================================================================
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "object.h"
#include "transform.h"

//======================================================================================================
//�X�V
//======================================================================================================
void Camera::Update()
{
	//�J�����̌������m�F����
	D3DXVECTOR3 rot = this->GetObj()->GetComponent<Transform>()->GetRot();
	if (rot.x > D3DX_PI - 0.1f)
	{
		//�����𒲐�����
		rot.x = D3DX_PI - 0.1f;
		this->GetObj()->GetComponent<Transform>()->SetRot(rot);
	}
	else if (rot.x < 0.1f)
	{
		//�����𒲐�����
		rot.x = 0.1f;
		this->GetObj()->GetComponent<Transform>()->SetRot(rot);
	}
}

//======================================================================================================
//�ݒ菈��
//======================================================================================================
void Camera::Set()
{
	//�f�o�C�X���擾����
	Renderer* pRenderer = Manager::Get()->GetRenderer();   //�����_���[
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();   //�f�o�C�X�ւ̃|�C���^

	//�v���W�F�N�V�����}�g���b�N�X������������
	D3DXMatrixIdentity(&this->m_mtxProjection);

	//���e���@���m�F����
	if (this->m_mtx == Camera::MATRIX::IS_PERSPECTIVE)
	{//�������e�̏ꍇ
		//�������e���s��
		D3DXMatrixPerspectiveFovLH(&this->m_mtxProjection,
			D3DXToRadian(45.0f),   //����p
			(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
			10.0f,   //Z�l�̍ŏ��l
			4000.0f);   //Z�l�̍ő�l
	}
	else if (this->m_mtx == Camera::MATRIX::IS_ORTHO)
	{//���s���e�̏ꍇ
		//���s���e���s��
		D3DXMatrixOrthoLH(&this->m_mtxProjection,
			(float)SCREEN_WIDTH,
			(float)SCREEN_HEIGHT,
			10.0f,
			1000.0f);
	}

	//�v���W�F�N�V�����}�g���b�N�X��ݒ肷��
	pDevice->SetTransform(D3DTS_PROJECTION, &this->m_mtxProjection);

	//�r���[�}�g���b�N�X������������
	D3DXMatrixIdentity(&this->m_mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXVECTOR3 pos = this->GetObj()->GetComponent<Transform>()->GetPos();
	D3DXMatrixLookAtLH(&this->m_mtxView, &pos, &this->m_posRegard, &this->m_vecUp);

	//�r���[�}�g���b�N�X��ݒ肷��
	pDevice->SetTransform(D3DTS_VIEW, &this->m_mtxView);
}