//=============================================================
//
// �X�^�[�g�V�[�� [start_scene.h]
// Author: Ito Kotaro
// 
// �A�v���P�[�V�����J�n��A�ŏ��ɓǂݍ��܂��V�[���ł�
//
//=============================================================
#ifndef _START_SCENE_H_
#define _START_SCENE_H_

#include "scene.h"

// �X�^�[�g�V�[��
class CStartScene : public CScene
{
public:
	void Init() override;			// ������
	void Uninit() override;			// �I��
	void Update() override;		// �X�V
	void Draw() override;			// �`��
};

#endif // !_START_SCENE_H_
