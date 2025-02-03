//=============================================================
//
// �^�C�g�� [title.cpp]
// Author: Ito Kotaro
//
//=============================================================
#include "title.h"

#include "component/2d/text.h"
#include "component/2d/polygon.h"
#include "renderer.h"

#include "render/shadow_rb.h"

//=============================================================
// [CTitleScene] ������
//=============================================================
void CTitleScene::Init()
{
	m_tutorial = false;

	m_tutorialImg = new GameObject();
	m_tutorialImg->AddComponent<CPolygon>()->SetTexture("data\\TEXTURE\\tutorial.png");
	m_tutorialImg->transform->SetSize(static_cast<float>(CRenderer::SCREEN_WIDTH), static_cast<float>(CRenderer::SCREEN_HEIGHT));
	m_tutorialImg->SetPriority(10);
	m_tutorialImg->SetVisible(false);

	// �w�i
	GameObject* pBG = new GameObject;
	pBG->AddComponent<CPolygon>();
	pBG->GetComponent<CPolygon>()->SetTexture("data\\TEXTURE\\title.png");
	pBG->transform->SetSize(static_cast<float>(CRenderer::SCREEN_WIDTH), static_cast<float>(CRenderer::SCREEN_HEIGHT));

	// �I�����𐶐�����
	for (int i = 0; i < SELECT::MAX; i++)
	{
		// ���ڂ̕\�������i�[����
		std::string sShowName;
		switch (i)
		{
		case SELECT::START:
			sShowName = "�J�n";
			break;
		case SELECT::EXIT:
			sShowName = "�I��";
			break;
		}

		// �I�u�W�F�N�g�𐶐�����
		m_pSelectObj[i] = new GameObject;
		m_pSelectObj[i]->AddComponent<CText>();
		m_pSelectObj[i]->GetComponent<CText>()->SetFont("���m�xPOP v2");
		m_pSelectObj[i]->GetComponent<CText>()->SetText("<size=200><color=255,255,255>" + sShowName);
		m_pSelectObj[i]->GetComponent<CText>()->SetAlign(CText::ALIGN::CENTER);
		m_pSelectObj[i]->transform->SetPos(static_cast<float>(CRenderer::SCREEN_WIDTH) / 2 + 480.0f, 400.0f + i * 250.0f);
	}

	// �����_�[�o�b�t�@��ݒ肷��
	CRenderer::GetInstance()->RegisterRenderBuffer<CameraRenderBuffer>("main");
	static_cast<CameraRenderBuffer*>(CRenderer::GetInstance()->GetRenderBuffer("main"))->SetCamera(nullptr);
}

//=============================================================
// [CTitleScene] �I��
//=============================================================
void CTitleScene::Uninit()
{
}

//=============================================================
// [CTitleScene] �X�V
//=============================================================
void CTitleScene::Update()
{
	// �I���̍X�V
	UpdateSelect();

	// �I�������Ƃ��̏���
	if (INPUT_INSTANCE->onTrigger("space") ||
		INPUT_INSTANCE->onTrigger("enter") ||
		INPUT_INSTANCE->onTrigger("p:a"))
	{
		switch (m_select)
		{
		case CTitleScene::START:

			if (m_tutorial)
			{
				CSceneManager::GetInstance()->SetScene("game");
			}

			if (!m_tutorial)
			{
				m_tutorialImg->SetVisible(true);
				m_tutorial = true;
			}

			break;
		case CTitleScene::EXIT:
			DestroyWindow(CRenderer::GetInstance()->GetHWND());
			break;
		}
	}
}

//=============================================================
// [CTitleScene] �`��
//=============================================================
void CTitleScene::Draw()
{
}


//=============================================================
// [CTitleScene] �I���̍X�V
//=============================================================
void CTitleScene::UpdateSelect()
{
	// �R���g���[���[�p
	short controlStickLx = INPUT_INSTANCE->GetInputDevice<CGamepadDevice>()->GetState().Gamepad.sThumbLX;
	short controlStickLy = INPUT_INSTANCE->GetInputDevice<CGamepadDevice>()->GetState().Gamepad.sThumbLY;

	// �R���g���[���[�̃f�b�h�]�[��
	if ((controlStickLx <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		controlStickLx > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(controlStickLy <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			controlStickLy > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		controlStickLx = 0;
		controlStickLy = 0;
	}

	// ��I��
	if (INPUT_INSTANCE->onTrigger("w") ||
		INPUT_INSTANCE->onTrigger("up") ||
		controlStickLy > 0.0f)
	{
		if (m_select > 0)
		{
			m_select = static_cast<SELECT>(m_select - 1);
		}
	}

	// ���I��
	if (INPUT_INSTANCE->onTrigger("s") ||
		INPUT_INSTANCE->onTrigger("down") ||
		controlStickLy < 0.0f)
	{
		if (m_select < SELECT::MAX - 1)
		{
			m_select = static_cast<SELECT>(m_select + 1);
		}
	}

	// UI�̍X�V
	for (int i = 0; i < SELECT::MAX; i++)
	{
		m_pSelectObj[i]->GetComponent<CText>()->SetAlpha(i == m_select ? 1.0f : 0.2f);
	}
}
