//==========================================================================================================
//
//�o�[�h���_�J�����̏���[camera_bird.h]
// Author MurataShinnosuke
//
//==========================================================================================================
#ifndef _CAMERA_BIRD_H_
#define _CAMERA_BIRD_H_

#include "behavior.h"

//�O���錾
class Camera;
//�o�[�h���_�J����
class CameraBird : public Behavior   //(�e)����
{
public:
	static const D3DXVECTOR3 OFFSET_POS_REGARD;   //���_�̒����_�̋���

	//�R���X�g���N�^
	CameraBird(Object* pObject) : Behavior(pObject)
	{
		//�����o�ϐ�������������
		this->m_pCamera = nullptr;   //�J����
		this->m_pPlayer = nullptr;   //�v���C���[
	}

	//�f�X�g���N�^
	~CameraBird()
	{
	}

	void Init() override;
	void Update() override;

private:
	Object* m_pPlayer;   //�v���C���[
	Camera* m_pCamera;   //�J����
};

#endif // !_CAMERA_BIRD_H_
