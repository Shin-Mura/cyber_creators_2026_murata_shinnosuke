//=============================================================
//
// ���U���g�V�[�� [result.cpp]
// Author: Ito Kotaro
// 
//=============================================================
#include "result.h"
#include "component/2d/polygon.h"
#include "component/2d/text.h"
#include "scripts/ranking_system.h"
#include "ranking.h"
#include "renderer.h"

//=============================================================
// [CResultScene] ������
//=============================================================
void CResultScene::Init()
{
	// ���U���g�w�i
	GameObject* bgObj = new GameObject("BG");
	bgObj->AddComponent<CPolygon>()->SetTexture("data\\TEXTURE\\result.png");
	bgObj->transform->SetSize(CRenderer::SCREEN_WIDTH, CRenderer::SCREEN_HEIGHT);

	// ���U���g�e�L�X�g
	GameObject* resultText = new GameObject();
	resultText->AddComponent<CText>()->SetText("<size=200>���U���g");
	resultText->GetComponent<CText>()->SetFont("���m�xPOP v2");
	resultText->GetComponent<CText>()->SetAlign(CText::CENTER);
	resultText->transform->SetPos(CRenderer::SCREEN_WIDTH / 2, 100.0f);

	// �^�C��
	// ���ƕb
	int min = (m_score - m_score % 60) / 60;
	int sec = m_score % 60;

	// ���Ԃ̕\���`����ύX����
	char* timeText = new char[128];
	sprintf(timeText, "<size=400>%d:%02d", min, sec);

	m_timeNumText = new GameObject();
	m_timeNumText->AddComponent<CText>()->SetText(timeText);
	m_timeNumText->GetComponent<CText>()->SetFont("���m�xPOP v2");
	m_timeNumText->GetComponent<CText>()->SetFontSize(200);
	m_timeNumText->GetComponent<CText>()->SetAlign(CText::CENTER);
	m_timeNumText->transform->SetPos(CRenderer::SCREEN_WIDTH / 2, 450.0f);

	// �X�R�A��o�^����
	RankingSystem rankSystem;
	rankSystem.RegisterData(m_score);

	// �����L���O�ɃX�R�A���󂯓n��
	static_cast<CRankingScene*>(CSceneManager::GetInstance()->GetScene("ranking")->pScene)->SetRank(rankSystem.GetRanking(m_score));

	// �����_�[�o�b�t�@��ݒ肷��
	CRenderer::GetInstance()->RegisterRenderBuffer<CameraRenderBuffer>("main");
	static_cast<CameraRenderBuffer*>(CRenderer::GetInstance()->GetRenderBuffer("main"))->SetCamera(nullptr);
}

//=============================================================
// [CResultScene] �I��
//=============================================================
void CResultScene::Uninit()
{
}

//=============================================================
// [CResultScene] �X�V
//=============================================================
void CResultScene::Update()
{
	if (INPUT_INSTANCE->onTrigger("enter") || INPUT_INSTANCE->onTrigger("p:a"))
	{
		CSceneManager::GetInstance()->SetScene("ranking");
	}
}

//=============================================================
// [CResultScene] �`��
//=============================================================
void CResultScene::Draw()
{
}
