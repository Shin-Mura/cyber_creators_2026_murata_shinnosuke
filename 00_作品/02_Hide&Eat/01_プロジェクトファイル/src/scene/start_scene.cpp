//=============================================================
//
// �X�^�[�g�V�[�� [start_scene.cpp]
// Author: Ito Kotaro
// 
// �A�v���P�[�V�����J�n��A�ŏ��ɓǂݍ��܂��V�[���ł�
// �V�[���̓o�^���s�����Ƃ������߂��܂�
//
//=============================================================
#include "start_scene.h"
#include "manager.h"

// �V�[���̃C���N���[�h
#include "title.h"
#include "game.h"
#include "result.h"
#include "ranking.h"

//=============================================================
// [CStartScene] ������
//=============================================================
void CStartScene::Init()
{
	// �V�[���}�l�[�W���[�̎擾
	CSceneManager* pSceneManager = CSceneManager::GetInstance();

	// �V�[���̓o�^
	pSceneManager->RegistScene<CTitleScene>("title");
	pSceneManager->RegistScene<CGameScene>("game");
	pSceneManager->RegistScene<CResultScene>("result");
	pSceneManager->RegistScene<CRankingScene>("ranking");

	// �V�[���̍Đ�
	pSceneManager->SetScene("title");
}

//=============================================================
// [CStartScene] �I��
//=============================================================
void CStartScene::Uninit()
{
}

//=============================================================
// [CStartScene] �X�V
//=============================================================
void CStartScene::Update()
{
}

//=============================================================
// [CStartScene] �`��
//=============================================================
void CStartScene::Draw()
{
}