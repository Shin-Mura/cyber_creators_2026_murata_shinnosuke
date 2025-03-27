//========================================================================================================
//
//�����L���O�V�[������[scene_mode_ranking.cpp]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "scene_mode.h"
#include "scene.h"
#include "keyboard.h"
#include "joypad.h"
#include "prefab.h"
#include "ranking.h"
//#include "rank.h"

//========================================================================================================
//����������
//========================================================================================================
void SceneModeRanking::Init()
{
	//�w�i�𐶐�����
	{
		//�w�i�𐶐�����
		Object* bg = new Object("Background2D");

		//�g�����X�t�H�[����ǉ�����
		Transform2D* pTransform2D = new Transform2D(bg);
		pTransform2D->SetPos({ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f});
		pTransform2D->SetSize({ SCREEN_WIDTH, SCREEN_HEIGHT});
		bg->AddComponent(pTransform2D);

		//�l�p�`�����_�����O��ǉ�����
		Square* pSquare = new Square(bg);
		pSquare->SetTexture(Manager::Get()->GetTexture()->Get("ranking_bg.png"));
		bg->AddComponent(pSquare);

		//����������
		bg->Init();
	}

	//�����L���O�𐶐�����
	for (int i = 0; i < RankingSystem::MAX_DATA; i++)
	{
		Object* rank = ScorePrefab::Create({ SCREEN_WIDTH /2 - 180.0f, 220.0f + i * 100.0f }, {400.0f, 80.0f});

		//�X�R�A
		int score = RankingSystem::GetInstance()->GetScore(i);
		rank->GetComponent<Score>()->Add(score != -1 ? score : 0);
	}

	////���ʂ𐶐�����
	//Rank::Create();

	//�t�F�[�h�𐶐�����
	FadePrefab::Create();
}

//========================================================================================================
//�I������
//========================================================================================================
void SceneModeRanking::Uninit()
{
	//�I�u�W�F�N�g�̈ꊇ�j�����s��
	Object::DestroyAll();
}

//========================================================================================================
//�X�V����
//========================================================================================================
void SceneModeRanking::Update()
{
	//�I�u�W�F�N�g�̈ꊇ�X�V���s��
	Object::UpdateAll();

	//���쏈�����s��
	this->Control();
}

//========================================================================================================
//�`�揈��
//========================================================================================================
void SceneModeRanking::Draw()
{
	//�I�u�W�F�N�g�̈ꊇ�`����s��
	Object::DrawAll();
}

//========================================================================================================
//����
//========================================================================================================
void SceneModeRanking::Control()
{
	//----------------------------------------------------------------------------------------------------
	//���͏������s��
	//----------------------------------------------------------------------------------------------------
	Keyboard* pKeyboard = Manager::Get()->GetKeyboard();   //�L�[�{�[�h
	Joypad* pJoypad = Manager::Get()->GetJoypad();   //�W���C�p�b�h

	//SPASE�L�[���m�F����
	if (pKeyboard->GetTrigger(DIK_SPACE) || pJoypad->GetTrigger(Joypad::JOYKEY::IS_A, 0))
	{//SPASE�L�[�������ꂽ�ꍇ
		//�I���t���O�𗧂Ă�
		this->GetScene()->Next(Scene::MODE::IS_TITLE);
	}
}