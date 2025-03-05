//========================================================================================================
//
//�Q�[���V�[��[scene_mode_game.h]
// Author MurataShinnosuke
//
//========================================================================================================
#include "scene_mode.h"
#include "prefab.h"
#include "physics.h"
#include "waypoint.h"

//========================================================================================================
//����������
//========================================================================================================
void SceneModeGame::Init()
{
	//�����蔻��𐶐�����
	Physics::Create();

	//�|�[�Y�𐶐�����
	this->m_pPause = new Pause;
	this->m_pPause->Init();   //������

	//�J�����𐶐�����
	CameraPrefab::Create();

	//�f�B���N�V���i�����C�g�𐶐�����
	DireLightPrefab::Create({ 0.22f, -0.87f, 0.44f }, { 1.0f, 1.0f, 1.0f, 1.0f });
	DireLightPrefab::Create({ -0.18f, 0.88f, -0.44f }, { 0.65f, 0.65f, 0.65f, 1.0f });
	DireLightPrefab::Create({ 0.89f, 0.11f, 0.44f }, { 0.15f, 0.15f, 0.15f, 0.15f });

	//�X�e�[�W��ǂݍ���
	Manager::Get()->GetStage()->Load(Stage::TYPE::IS_DEMO);

	//�t�F�[�h�𐶐�����
	FadePrefab::Create();
}

//========================================================================================================
//�I������
//========================================================================================================
void SceneModeGame::Uninit()
{
	//�E�F�C�|�C���g���ꊇ�������
	Waypoint::ReleaseAll();

	//�I�u�W�F�N�g���ꊇ�j������
	Object::DestroyAll();

	//�|�[�Y��j������
	this->m_pPause->Uninit();
	delete this->m_pPause;
	this->m_pPause = nullptr;

	//�����蔻���j������
	Physics::Destroy();
}

//========================================================================================================
//�X�V����
//========================================================================================================
void SceneModeGame::Update()
{
	Keyboard* pKeyboard = Manager::Get()->GetKeyboard();   //�L�[�{�[�h����
	Joypad* pJoypad = Manager::Get()->GetJoypad();   //�W���C�p�b�h

	//P�L�[���m�F����
	if (pKeyboard->GetTrigger(DIK_P) || pJoypad->GetTrigger(Joypad::IS_START, 0))
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
			//�I�����m�F����
			int nSelect = pPauseMenu->GetSelect();
			if (nSelect == PauseMenu::MENU::IS_CONTINUE)
			{//�R���e�j���[�̏ꍇ
				//�|�[�Y��؂�ւ���
				this->m_pPause->SwitchPause();
			}
			else if (nSelect == PauseMenu::MENU::IS_REPLAY)
			{//���v���C�̏ꍇ
				//�Q�[����ʂɑJ�ڂ���
				this->GetScene()->Next(Scene::MODE::IS_GAME);
			}
			else if (nSelect == PauseMenu::MENU::IS_QUIT)
			{//�I���̏ꍇ
				//�^�C�g����ʂɑJ�ڂ���
				this->GetScene()->Next(Scene::MODE::IS_TITLE);
			}
		}
	}
	else
	{//�����Ă��Ȃ��ꍇ
		Object::UpdateAll();
	}
}

//========================================================================================================
//�`�揈��
//========================================================================================================
void SceneModeGame::Draw()
{
	//�I�u�W�F�N�g�̈ꊇ�`����s��
	Object::DrawAll();
}