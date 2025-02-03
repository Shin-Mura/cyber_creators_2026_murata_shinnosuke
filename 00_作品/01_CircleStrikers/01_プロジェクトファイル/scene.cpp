//========================================================================================================
//
//�V�[������[scene.cpp]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "scene.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "ranking.h"

//========================================================================================================
//��������
//========================================================================================================
Scene* Scene::Create(MODE mode)
{
	Scene* pScene = nullptr;   //�C���X�^���X�i�[�p

	switch (mode)
	{
	case Scene::MODE::IS_TITLE:
		//�^�C�g���𐶐�����
		pScene = new Title;
		pScene->Init();

		//�����𔲂��o��
		break;

	case Scene::MODE::IS_GAME:
		//�Q�[���𐶐�����
		pScene = new Game;
		pScene->Init();

		//�����𔲂��o��
		break;

	case Scene::MODE::IS_RESULT:
		//���U���g�𐶐�����
		pScene = new Result;
		pScene->Init();

		//�����𔲂��o��
		break;

	case Scene::MODE::IS_RANKIGN:
		//�����L���O�𐶐�����
		pScene = new Ranking;
		pScene->Init();

		//�����𔲂��o��
		break;
	}

	//�V�[����Ԃ�
	return pScene;
}