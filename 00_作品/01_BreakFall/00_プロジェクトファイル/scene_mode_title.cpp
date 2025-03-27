//========================================================================================================
//
//�^�C�g���V�[��[scene_mode_title.h]
// Author MurataShinnosuke
//
//========================================================================================================
#include "scene_mode.h"
#include "prefab.h"
#include "menu.h"
#include "sound.h"

//�萔
constexpr float END_LOGO_HEIGHT = 350.0f;	//���S�̍ŏI���B����

//========================================================================================================
//����������
//========================================================================================================
void SceneModeTitle::Init()
{
	//�w�i�𐶐�����
	pBG = Background2DPrefab::Create(Manager::Get()->GetTexture()->Get("title_bg.png"));
	pBG->GetComponent<Transform2D>()->SetPos({ SCREEN_WIDTH / 2, 0.0f });
	pBG->GetComponent<Transform2D>()->SetSize({ SCREEN_WIDTH, SCREEN_HEIGHT });

	//�^�C�g�����j���[�𐶐�����
	this->pTitleMenu = TitleMenuPrefab::Create();

	//�t�F�[�h�𐶐�����
	FadePrefab::Create();

	//BGM�Đ�
	PlaySound(SOUND_LABEL_TITLE);
}

//========================================================================================================
//�I������
//========================================================================================================
void SceneModeTitle::Uninit()
{
	//�I�u�W�F�N�g���ꊇ�j������
	Object::DestroyAll();

	//BGM��~
	StopSound();
}

//========================================================================================================
//�X�V����
//========================================================================================================
void SceneModeTitle::Update()
{
	//�I�u�W�F�N�g���ꊇ�X�V����
	Object::UpdateAll();

	//�w�i�����낷
	D3DXVECTOR2 bgPos = pBG->GetComponent<Transform2D>()->GetPos();
	if (bgPos.y < END_LOGO_HEIGHT)
	{
		bgPos.y += (END_LOGO_HEIGHT - bgPos.y) * 0.08f;
		pBG->GetComponent<Transform2D>()->SetPos(bgPos);
	}

	//����t���O���m�F����
	Menu* pMenu = this->pTitleMenu->GetComponent<Menu>();
	if (pMenu->GetDecide() == true)
	{//����t���O�������Ă���ꍇ
		//�I�����m�F����
		int nSelect = pMenu->GetSelect();
		if (nSelect == TitleMenu::MENU::IS_START)
		{//�X�^�[�g�̏ꍇ
			//��ʑJ�ڃt���O�𗧂Ă�
			this->GetScene()->Next(Scene::MODE::IS_TUTORIAL);
		}
		else if (nSelect == TitleMenu::MENU::IS_RANKING)
		{//�����L���O�̏ꍇ
			//��ʑJ�ڃt���O�𗧂Ă�
			this->GetScene()->Next(Scene::MODE::IS_RANKIGN);
		}

		//����炷
		PlaySound(SOUND_LABEL_SELECT_DECIDE);
	}

	//�I�����ύX����Ă�������ʉ���炷
	if (pMenu->GetSelect() != m_oldSelect)
	{
		//����炷
		PlaySound(SOUND_LABEL_SELECT_MOVE);

		//�X�V
		m_oldSelect = pMenu->GetSelect();
	}
}

//========================================================================================================
//�`�揈��
//========================================================================================================
void SceneModeTitle::Draw()
{
	//�I�u�W�F�N�g���ꊇ�`�悷��
	Object::DrawAll();
}