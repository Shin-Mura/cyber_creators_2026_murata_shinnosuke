//========================================================================================================
//
//�}�l�[�W���[����[manager.cpp]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "manager.h"
#include "object.h"

#include <time.h>

//�ÓI�����o�ϐ�������������
Manager* Manager::m_pInstance = nullptr;

//=======================================================================================================
//����������
//=======================================================================================================
HRESULT Manager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//�����_���[�𐶐�����
	this->m_pRenderer = new Renderer;
	this->m_pRenderer->Init(hWnd, TRUE);   //������

	//�e�N�X�`���𐶐�����
	this->m_pTexture = new Texture;
	this->m_pTexture->Init();   //������

	//X�t�@�C���𐶐�����
	this->m_pXFile = new XFile;
	this->m_pXFile->Init();   //������

	//�L�[�{�[�h�𐶐�����
	this->m_pKeyboard = new Keyboard;
	this->m_pKeyboard->Init(hInstance, hWnd);   //������

	//�}�E�X�𐶐�����
	this->m_pMouse = new Mouse;
	this->m_pMouse->Init(hInstance, hWnd);   //������

	//�W���C�p�b�h�𐶐�����
	this->m_pJoypad = new Joypad;
	this->m_pJoypad->Init(hInstance, hWnd);   //������

	//�X�e�[�W�𐶐�����
	this->m_pStage = new Stage;

	//�V�[���𐶐�����
	this->m_pScene = new Scene;
	this->m_pScene->ChangeMode(new SceneModeTitle(this->m_pScene));   //�^�C�g���V�[���ɕύX

	return S_OK;
}

//=======================================================================================================
//�I������
//=======================================================================================================
void Manager::Uninit()
{
	//�X�e�[�W��j������
	delete this->m_pStage;
	this->m_pStage = nullptr;

	//�V�[����j������
	this->m_pScene->Uninit();   //�I������
	delete this->m_pScene;
	this->m_pScene = nullptr;

	//�W���C�p�b�h��j������
	this->m_pJoypad->Uninit();
	delete this->m_pJoypad;
	this->m_pJoypad = nullptr;

	//�}�E�X��j������
	this->m_pMouse->Uninit();
	delete this->m_pMouse;
	this->m_pMouse = nullptr;

	//�L�[�{�[�h��j������
	this->m_pKeyboard->Uninit();
	delete this->m_pKeyboard;
	this->m_pKeyboard = nullptr;

	//X�t�@�C����j������
	this->m_pXFile->Uninit();   //�I������
	delete this->m_pXFile;
	this->m_pXFile = nullptr;

	//�e�N�X�`����j������
	this->m_pTexture->Uninit();   //�I������
	delete this->m_pTexture;
	this->m_pTexture = nullptr;

	//�����_���[��j������
	this->m_pRenderer->Uninit();
	delete this->m_pRenderer;
	this->m_pRenderer = nullptr;
}

//=======================================================================================================
//�X�V����
//=======================================================================================================
void Manager::Update()
{
	//�����̎��ݒ�
	srand((unsigned int)clock());

	//�L�[�{�[�h�̍X�V�������s��
	this->m_pKeyboard->Update();

	//�}�E�X�̍X�V�������s��
	this->m_pMouse->Update();

	//�W���C�p�b�h�̍X�V�������s��
	this->m_pJoypad->Update();

	//�����_���[�̍X�V�������s��
	this->m_pRenderer->Update();

	//�V�[���̍X�V�������s��
	this->m_pScene->Update();
}

//=======================================================================================================
//�`�揈��
//=======================================================================================================
void Manager::Draw()
{
	//�����_���[�̕`�揈�����s��
	this->m_pRenderer->Draw();

	//�V�[���̑J�ڃt���O���m�F����
	if (this->m_pScene->GetNext())
	{//�J�ڃt���O�������Ă���ꍇ
		//���̃V�[�����m�F����
		Scene::MODE modeNext = this->m_pScene->GetNextMode();
		if (modeNext == Scene::MODE::IS_TITLE)
		{//�^�C�g���̏ꍇ
			//�^�C�g����ʂɕύX����
			this->m_pScene->ChangeMode(new SceneModeTitle(this->m_pScene));
		}
		else if (modeNext == Scene::MODE::IS_GAME)
		{//�Q�[����ʂ̏ꍇ
			//�Q�[����ʂɕύX����
			this->m_pScene->ChangeMode(new SceneModeGame(this->m_pScene));
		}
		else if (modeNext == Scene::MODE::IS_RESULT)
		{//���U���g��ʂ̏ꍇ
			//���U���g��ʂɕύX����
			this->m_pScene->ChangeMode(new SceneModeResult(this->m_pScene));
		}
		else if (modeNext == Scene::MODE::IS_RANKIGN)
		{//�����L���O��ʂ̏ꍇ
			//�����L���O��ʂɕύX����
			this->m_pScene->ChangeMode(new SceneModeResult(this->m_pScene));
		}
	}
}