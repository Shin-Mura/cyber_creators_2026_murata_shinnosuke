//========================================================================================================
//
//���U���g�V�[��[scene_mode_game.h]
// Author MurataShinnosuke
//
//========================================================================================================
#include "scene_mode.h"
#include "scene.h"
#include "prefab.h"
#include "ranking.h"
#include "sound.h"

//========================================================================================================
//����������
//========================================================================================================
void SceneModeResult::Init()
{
	//�w�i�𐶐�����
	Background2DPrefab::Create(Manager::Get()->GetTexture()->Get("result_bg.png"));

	//�X�R�A�������L���O�ɓo�^����
	RankingSystem::GetInstance()->RegisterData(SceneModeGame::GetScore());

	//�X�R�A��\������
	Object* score = ScorePrefab::Create({ SCREEN_WIDTH / 2 - 350.0f, SCREEN_HEIGHT / 2 }, {800.0f, 150.0f});
	score->GetComponent<Score>()->Add(SceneModeGame::GetScore());

	//�t�F�[�h�𐶐�����
	FadePrefab::Create();

	//BGM�Đ�
	PlaySound(SOUND_LABEL_RESULT);
}

//========================================================================================================
//�I������
//========================================================================================================
void SceneModeResult::Uninit()
{
	//�I�u�W�F�N�g���ꊇ�j������
	Object::DestroyAll();

	//BGM��~
	StopSound();
}

//========================================================================================================
//�X�V����
//========================================================================================================
void SceneModeResult::Update()
{
	Keyboard* pKeyboard = Manager::Get()->GetKeyboard();   //�L�[�{�[�h

	//�I�u�W�F�N�g���ꊇ�X�V����
	Object::UpdateAll();

	if (pKeyboard->GetTrigger(DIK_RETURN))
	{//Enter�L�[�������ꂽ�ꍇ
		//�I���t���O�𗧂Ă�
		this->GetScene()->Next(Scene::MODE::IS_TITLE);
	}
}

//========================================================================================================
//�`�揈��
//========================================================================================================
void SceneModeResult::Draw()
{
	//�I�u�W�F�N�g���ꊇ�`�悷��
	Object::DrawAll();
}