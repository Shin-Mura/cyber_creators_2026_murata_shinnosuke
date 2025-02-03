//========================================================================================================
//
//�Q�[���V�[������[game.cpp]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "game.h"
#include "manager.h"
#include "keyboard.h"
#include "prefab.h"
#include "game_manager.h"

//========================================================================================================
//����������
//========================================================================================================
void Game::Init()
{
	//�Փ˔���𐶐�����
	this->m_pPhysics = new Physics;

	//�|�[�Y�𐶐�����
	this->m_pPause = new Pause;
	this->m_pPause->Init();   //������

	//�J�����𐶐�����
	CameraPrefab::Create();

	//�f�B���N�V���i�����C�g�𐶐�����
	DireLightPrefab::Create({ 0.22f, -0.87f, 0.44f }, {1.0f, 1.0f, 1.0f, 1.0f});
	DireLightPrefab::Create({ -0.18f, 0.88f, -0.44f }, { 0.65f, 0.65f, 0.65f, 1.0f });
	DireLightPrefab::Create({ 0.89f, 0.11f, 0.44f }, { 0.15f, 0.15f, 0.15f, 0.15f });

	//�w�i��ǉ�����
	Background3DPrefab::Create(Manager::Get()->GetTexture()->Get("field_00.png"));

	//�v���C���[�𐶐�����
	PlayerPrefab::Create({ 300.0f, 0.0f, 0.0f }, 0);
	PlayerPrefab::Create({ -300.0f, 0.0f, 0.0f }, 1);

	//�^�C�}�[�𐶐�����
	TimerPrefab::Create();

	//�t�F�[�h�𐶐�����
	FadePrefab::Create();
}

//========================================================================================================
//�I������
//========================================================================================================
void Game::Uninit()
{
	//�I�u�W�F�N�g���ꊇ�j������
	Object::ReleaseAll();

	//�|�[�Y��j������
	this->m_pPause->Uninit();
	delete this->m_pPause;
	this->m_pPause = nullptr;

	//�Փ˔����j������
	delete this->m_pPhysics;
	this->m_pPhysics = nullptr;
}

//========================================================================================================
//�X�V����
//========================================================================================================
void Game::Update()
{
	Keyboard* pKeyboard = Manager::Get()->GetKeyboard();   //�L�[�{�[�h����
	Joypad* pJoypad = Manager::Get()->GetJoypad();   //�W���C�p�b�h

	//P�L�[���m�F����
	if (pKeyboard->GetTrigger(DIK_P) || pJoypad->GetTrigger(Joypad::JOYKEY_START, 0))
	{//P�L�[��������Ă���ꍇ
		//�|�[�Y�t���O��؂�ւ���
		this->m_pPause->SwitchPause();
	}

	//�|�[�Y�t���O���m�F����
	if (this->m_pPause->GetPause() == true)
	{//�|�[�Y�t���O�������Ă���ꍇ
		//�|�[�Y�̍X�V�������s��
		this->m_pPause->Update();

		//�|�[�Y���j���[���擾����
		Menu* pPauseMenu = this->m_pPause->GetMenu();

		//�I���t���O���m�F����
		if (pPauseMenu->GetDecide() == true)
		{//�I���t���O�������Ă���ꍇ
			//�|�[�Y���j���[�̑I�𒆂̃��j���[�ɂ���ď�����ς���
			switch (pPauseMenu->GetSelect())
			{
			case  PauseMenu::MENU::IS_CONTINUE:
				//�|�[�Y��؂�ւ���
				this->m_pPause->SwitchPause();

				//�����𔲂��o��
				break;

			case PauseMenu::MENU::IS_REPLAY:  //���v���C�̏ꍇ
				//�Q�[����ʂɑJ�ڂ���
				Manager::Get()->SetSceneMode(Scene::MODE::IS_GAME);

				//�����𔲂��o��
				break;

			case PauseMenu::MENU::IS_QUIT:   //�I���̏ꍇ
				//�^�C�g����ʂɑJ�ڂ���
				Manager::Get()->SetSceneMode(Scene::MODE::IS_TITLE);

				//�����𔲂��o��
				break;
			}

			//�����I��
			return;
		}
	}
	else
	{//�����Ă��Ȃ��ꍇ
		Object::UpdateAll();

		//���̃V�[���t���O���m�F����
		if (this->GetEnd())
		{
			//���U���g��ʂɑJ�ڂ���
			Manager::Get()->SetSceneMode(Scene::MODE::IS_RESULT);
		}
	}
}

//========================================================================================================
//�`�揈��
//========================================================================================================
void Game::Draw()
{
	//�I�u�W�F�N�g�̈ꊇ�`����s��
	Object::DrawAll();
}