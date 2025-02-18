//========================================================================================================
//
//�g�����X�t�H�[���̏���[transform.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "component.h"

//�g�����X�t�H�[��
class Transform : public Component
{
public:
	//�R���X�g���N�^
	Transform(Object * pObject) : Component(pObject)
	{
		//�����o�ϐ�������������
		this->m_pos = { 0.0f, 0.0f, 0.0f };   //�ʒu
		this->m_posOld = this->m_posOld;   //�O��̈ʒu
		this->m_rot = { 0.0f, 0.0f, 0.0f };   //����
		this->m_scale = { 1.0f, 1.0f, 1.0f };   //�g�嗦
	}

	//�f�X�g���N�^
	~Transform() override
	{
	}

	void Update() override { this->m_posOld = this->m_pos; };   //�X�V����
	void AddPos(D3DXVECTOR3 posAdd) { this->m_pos += posAdd; };   //�ʒu�̉��Z

	void SetPos(D3DXVECTOR3 pos) { this->m_pos = pos; };   //�ʒu�̐ݒ菈��
	void SetRot(D3DXVECTOR3 rot) { this->m_rot = rot; };   //�����̐ݒ菈��
	void SetScale(D3DXVECTOR3 scale) { this->m_scale = scale; };   //�g�嗦�̐ݒ菈��

	D3DXVECTOR3 GetPos() { return this->m_pos; };   //�ʒu�̎擾
	D3DXVECTOR3 GetPosOld() { return this->m_posOld; };   //�O��̈ʒu�̎擾
	D3DXVECTOR3 GetRot() { return this->m_rot; };   //�����̎擾
	D3DXVECTOR3 GetScale() { return this->m_scale; };   //�g�嗦�̎擾

	//���[���h�}�g���b�N�X�̎擾����
	D3DXMATRIX GetMtxWorld()
	{
		D3DXMATRIX mtxWorld;   //���[���h�}�g���b�N�X
		D3DXMATRIX mtxRot, mtxTrans;   //�v�Z�p�}�g���b�N�X

		//�X�P�[�����O�𔽉f����
		D3DXMatrixScaling(&mtxWorld, this->m_scale.x, this->m_scale.y, this->m_scale.z);

		//�����𔽉f����		
		D3DXMatrixRotationYawPitchRoll(&mtxRot, this->m_rot.y, this->m_rot.x, this->m_rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		//�ʒu�𔽉f����		
		D3DXMatrixTranslation(&mtxTrans, this->m_pos.x, this->m_pos.y, this->m_pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X��Ԃ�
		return mtxWorld;
	}

private:
	D3DXVECTOR3 m_pos;   //�ʒu
	D3DXVECTOR3 m_posOld;   //�O��̈ʒu
	D3DXVECTOR3 m_rot;   //����
	D3DXVECTOR3 m_scale;   //�g�嗦
};

//2D�g�����X�t�H�[��
class Transform2D : public Component
{
public:
	//�R���X�g���N�^
	Transform2D(Object* pObject) : Component(pObject)
	{
		//�����o�ϐ�������������
		this->m_pos = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };   //�ʒu
		this->m_size = { 0.0f, 0.0f };   //�T�C�Y
		this->m_fRot = 0.0f;   //����
	}

	//�f�X�g���N�^
	~Transform2D() override
	{
	}

	void SetPos(D3DXVECTOR2 pos) { this->m_pos = pos; };   //�ʒu�̐ݒ菈��
	void SetRot(float fRot) { this->m_fRot = fRot; };   //�����̐ݒ菈��
	void SetSize(D3DXVECTOR2 size) { this->m_size = size; };   //�g�嗦�̐ݒ菈��

	D3DXVECTOR2 GetPos() { return this->m_pos; };   //�ʒu�̎擾
	D3DXVECTOR2 GetSize() { return this->m_size; };   //�g�嗦�̎擾
	float GetRot() { return this->m_fRot; };   //�����̎擾

private:
	D3DXVECTOR2 m_pos;   //�ʒu
	D3DXVECTOR2 m_size;   //�T�C�Y
	float m_fRot;   //����
};

#endif // !_TRANSFORM_H_