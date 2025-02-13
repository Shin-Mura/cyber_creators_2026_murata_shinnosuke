//==========================================================================================================
//
//TPS���_�J�����̏���[camera_tps.h]
// Author MurataShinnosuke
//
//==========================================================================================================
#ifndef _CAMERA_TPS_H_
#define _CAMERA_TPS_H_

#include "behavior.h"

//�O���錾
class Camera;
//TPS���_�J����
class CameraTPS : public Behavior   //(�e)����
{
public:
	static const float DISTANCE_VIEW_TO_REGARD;   //���_�̒����_�̋���
	static const float DISTANCE_TARGET_TO_FULCRUM;   //���_�̒����_�̋���

	//�R���X�g���N�^
	CameraTPS(Object* pObject) : Behavior(pObject)
	{
		//�����o�ϐ�������������
		this->m_pCamera = nullptr;   //�J����
		this->m_posFulcrum = { 0.0f, 0.0f, 0.0f };   //�x�_�̈ʒu
		this->m_posTarget = { 0.0f, 0.0f, 0.0f };   //�Ώۂ̈ʒu
		this->m_fSensi = 0.02f;   //���x
		this->m_isAim = false;   //�G�C���t���O
	}

	//�f�X�g���N�^
	~CameraTPS()
	{
	}

	void Init() override;
	void Update() override;

private:
	void Control();

	Camera* m_pCamera;   //�J����
	D3DXVECTOR3 m_posFulcrum;   //�x�_�̈ʒu
	D3DXVECTOR3 m_posTarget;   //�Ώۂ̈ʒu
	float m_fSensi;   //���x
	bool m_isAim;   //�G�C���t���O
};

#endif // !_CAMERA_TPS_H_
