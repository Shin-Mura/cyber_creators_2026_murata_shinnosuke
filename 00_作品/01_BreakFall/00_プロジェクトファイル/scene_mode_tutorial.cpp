//========================================================================================================
//
//�`���[�g���A���V�[��[scene_mode_tutorial.h]
// Author ItoKotaro
//
//========================================================================================================
#include "scene_mode.h"
#include "prefab.h"
#include "sound.h"

//========================================================================================================
//����������
//========================================================================================================
void SceneModeTutorial::Init()
{
	//�w�i�𐶐�����
	m_pTutorial = Background2DPrefab::Create(Manager::Get()->GetTexture()->Get("tutorial0.png"));
	m_pTutorial->GetComponent<Transform2D>()->SetPos({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 });
	m_pTutorial->GetComponent<Transform2D>()->SetSize({ SCREEN_WIDTH, SCREEN_HEIGHT });

	//�t�F�[�h�𐶐�����
	FadePrefab::Create();
}

//========================================================================================================
//�I������
//========================================================================================================
void SceneModeTutorial::Uninit()
{
	//�I�u�W�F�N�g���ꊇ�j������
	Object::DestroyAll();
}

//========================================================================================================
//�X�V����
//========================================================================================================
void SceneModeTutorial::Update()
{
	//�I�u�W�F�N�g���ꊇ�X�V����
	Object::UpdateAll();

	Keyboard* pKeyboard = Manager::Get()->GetKeyboard();
	Joypad* pJoypad = Manager::Get()->GetJoypad();
	
	//���̃y�[�W��
	if (pKeyboard->GetTrigger(DIK_SPACE) || pKeyboard->GetTrigger(DIK_RETURN))
	{
		m_page++;

		//�y�[�W�̃e�N�X�`���ύX
		switch (m_page)
		{
		case 1:
			m_pTutorial->GetComponent<Square>()->SetTexture(Manager::Get()->GetTexture()->Get("tutorial1.png"));
			break;
		case 2:
			//��ʑJ�ڃt���O�𗧂Ă�
			this->GetScene()->Next(Scene::MODE::IS_GAME);
			break;
		}

		//����炷
		PlaySound(SOUND_LABEL_SELECT_DECIDE);
	}
}

//========================================================================================================
//�`�揈��
//========================================================================================================
void SceneModeTutorial::Draw()
{
	//�I�u�W�F�N�g���ꊇ�`�悷��
	Object::DrawAll();
}