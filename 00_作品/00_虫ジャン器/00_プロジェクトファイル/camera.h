//********************************************************************************************************
//
//�J�����̏���[camera.h]
// Auhtor Murata Shinnosuke
//
//********************************************************************************************************
#ifndef _CAMERA_H_
#define _CAMERA_H_ 

#include "component.h"

//�J�����N���X
class Camera : public Component
{
public:
	//���e���@�̗�
	enum MATRIX
	{
		IS_PERSPECTIVE = 0,   //�������e
		IS_ORTHO,   //���s���e
		IS_MAX
	};

	//�R���X�g���N�^
	Camera(Object* pObject) : Component(pObject)
	{
		this->m_posRegard = { 0.0f, 0.0f, 0.0f };   //�����_
		this->m_vecUp = { 0.0f, 1.0f, 0.0f };   //������x�N�g��
		this->m_mtxProjection;   //�v���W�F�N�V�����}�g���b�N�X
		this->m_mtxView;   //�r���[�}�g���b�N�X
		this->m_mtx = Camera::MATRIX::IS_PERSPECTIVE;
	}

	//�f�X�g���N�^
	~Camera()
	{
	}

	void Update() override;   //�X�V
	void Set();   //�ݒ菈��

	void SetPosRegard(D3DXVECTOR3 pos) { this->m_posRegard = pos; };   //�����_�̈ʒu�̐ݒ�

	D3DXVECTOR3 GetPosRegard() { return this->m_posRegard; };   //�����_�̎擾����

private:
	D3DXVECTOR3 m_posRegard;   //�����_�̈ʒu
	D3DXVECTOR3 m_vecUp;   //������x�N�g��
	D3DXMATRIX m_mtxProjection;   //�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;   //�r���[�}�g���b�N�X
	MATRIX m_mtx;   //���e���@
};

#endif // !_CAMERA_H_