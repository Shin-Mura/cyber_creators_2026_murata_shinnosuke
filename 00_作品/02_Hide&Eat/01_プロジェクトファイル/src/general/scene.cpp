//=============================================================
//
// �V�[�� [scene.h]
// Author: Ito Kotaro
// 
// ����: �V�[���̊Ǘ����s���܂�
//
//=============================================================
#include "scene.h"
#include "scene/start_scene.h"
#include "gameobject.h"

// �ÓI�����o�̏�����
const std::string CSceneManager::START_SCENE_NAME = "start";


//=============================================================
// [CSceneManager] �R���X�g���N�^
//=============================================================
CSceneManager::CSceneManager()
{
	m_pCurrentScene = nullptr;
	m_pNextScene = nullptr;
	m_bReload = false;
	m_apScene = {};
}

//=============================================================
// [CSceneManager] �V�[���̎擾
//=============================================================
CSceneManager::SceneData* CSceneManager::GetScene(std::string sName)
{
	for (unsigned int i = 0; i < m_apScene.size(); i++)
	{
		if (m_apScene[i]->sName == sName)
		{ // ���O����v�����Ƃ�
			return m_apScene[i];		// �V�[���f�[�^��Ԃ�
		}
	}
	return nullptr;	// ������Ȃ������Ƃ�
}

//=============================================================
// [CSceneManager] ������
//=============================================================
void CSceneManager::Init()
{
	// �ŏ��̃V�[����o�^����
	RegistScene<CStartScene>(START_SCENE_NAME);
}

//=============================================================
// [CSceneManager] �I��
//=============================================================
void CSceneManager::Uninit()
{
	// ���݃V�[���̏I������
	if (m_pCurrentScene != nullptr)
	{
		m_pCurrentScene->pScene->Uninit();
		m_pCurrentScene->pScene->LastUninit();
		m_pCurrentScene = nullptr;
	}

	// ���ׂẴV�[���f�[�^�̔j��
	for (unsigned int i = 0; i < m_apScene.size(); i++)
	{
		if (m_apScene[i] != nullptr)
		{
			// �V�[���̔j��
			if (m_apScene[i]->pScene != nullptr)
			{
				delete m_apScene[i]->pScene;
				m_apScene[i]->pScene = nullptr;
			}

			// ���O�̏�����
			m_apScene[i]->sName = "";

			// �V�[���f�[�^�̔j��
			delete m_apScene[i];
			m_apScene[i] = nullptr;
		}
	}
	m_apScene.clear();	// ��ɂ���
}

//=============================================================
// [CSceneManager] �X�V
//=============================================================
void CSceneManager::Update()
{
	// ���݃V�[���̍X�V����
	if (m_pCurrentScene != nullptr)
	{
		m_pCurrentScene->pScene->Update();
	}
}

//=============================================================
// [CSceneManager] �`��
//=============================================================
void CSceneManager::Draw()
{
	// ���݃V�[���̕`�揈��
	if (m_pCurrentScene != nullptr)
	{
		m_pCurrentScene->pScene->Draw();
	}
}

//=============================================================
// [CSceneManager] �V�[���̕ύX
//=============================================================
HRESULT CSceneManager::SetScene(std::string sName, bool bIsDestroy)
{
	// �V�[�������݂��邩���m�F����
	SceneData* pNewScene = GetScene(sName);
	if (pNewScene == nullptr)
	{ // ���݂��Ȃ��Ƃ�
		return E_FAIL;	// ���s
	}

	// ���̃V�[���ɑ������
	m_pNextScene = pNewScene;
	m_bNoDestroy = bIsDestroy;

	return S_OK;		// ����
}

//=============================================================
// [CSceneManager] ���݃V�[���̍ēǂݍ���
//=============================================================
void CSceneManager::ReloadScene()
{
	m_bReload = true;
}

//=============================================================
// [CSceneManager] �O�V�[���̏I���A���V�[���̏������i���S������邽�߁A���s���Ȃ��ł��������j
//=============================================================
void CSceneManager::ChangingScene()
{
	// �ēǂݍ���
	if (m_bReload)
	{
		// ���݃V�[���̏I������
		if (m_pCurrentScene != nullptr)
		{
			m_pCurrentScene->pScene->Uninit();
		}

		// ���ׂẴI�u�W�F�N�g�̍폜
		GameObject::DestroyAll();
		GameObject::DestroyDeathFlag();

		// �V�[���̏�����
		m_pCurrentScene->pScene->Init();
		m_bReload = false;
		return;
	}

	if (m_pNextScene == nullptr)
	{ // ���̃V�[���ɉ��������Ă��Ȃ��Ƃ�
		return;
	}

	// ���݃V�[���̏I������
	if (m_pCurrentScene != nullptr)
	{
		m_pCurrentScene->pScene->Uninit();
		m_pCurrentScene = nullptr;
	}

	// ���ׂẴI�u�W�F�N�g�̍폜
	if (m_bNoDestroy)
	{
		GameObject::DestroyAll();
	}

	// �V�����V�[�������݂̃V�[���ɑ��
	m_pCurrentScene = m_pNextScene;
	m_pNextScene = nullptr;

	// �V�����V�[���̏���������
	m_pCurrentScene->pScene->Init();
}





////=============================================================
//// �V�[���̏���������
////=============================================================
//void InitScene()
//{
//	// �X�^�[�g�A�b�v��True�ɂ���
//	g_bIsStartupScene = true;
//
//	// �ŏ��̃V�[���̓ǂݍ���
//	SetScene(FIRST_SCENE);
//}
//
////=============================================================
//// �V�[���̏I������
////=============================================================
//void UninitScene()
//{
//	switch (g_currentScene)
//	{
//	case SCENE_GAME:
//		UninitGame();
//		break;
//	}
//}
//
////=============================================================
//// �V�[���̍X�V����
////=============================================================
//void UpdateScene()
//{
//	switch (g_currentScene)
//	{
//	case SCENE_GAME:
//		UpdateGame();
//		break;
//	}
//}
//
////=============================================================
//// �V�[���̕`�揈��
////=============================================================
//void DrawScene()
//{
//	switch (g_currentScene)
//	{
//	case SCENE_GAME:
//		DrawGame();
//		break;
//	}
//}
//
////=============================================================
//// �V�[���̐ݒ菈��
////=============================================================
//void SetScene(SCENE scene)
//{
//	// ���݂̃V�[�����I������
//	if (!g_bIsStartupScene)
//		switch (g_currentScene)
//		{
//		case SCENE_GAME:
//			UninitGame();
//			break;
//		}
//	else g_bIsStartupScene = false;
//
//	// �V�����V�[��������������
//	switch (scene)
//	{
//	case SCENE_GAME:
//		InitGame();
//		break;
//	}
//
//	// ���݂̃V�[����V�����V�[���ɒu��������
//	g_currentScene = scene;
//}