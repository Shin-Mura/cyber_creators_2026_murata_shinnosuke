//=============================================================
//
// �v���C���[ [player.cpp]
// Author: Ito Kotaro
// 
//=============================================================
#include "player.h"
#include "component/3d/collision.h"
#include "component/2d/bar.h"
#include "component/2d/text.h"
#include "component/3d/motion.h"
#include "component/other/sound.h"

//=============================================================
// [PlayerControl] ������
//=============================================================
void PlayerControl::Init()
{
	m_camera = GameObject::Find("Camera");

	// ���x���A�b�v�o�[
	m_lvBar = new GameObject();
	m_lvBar->AddComponent<CBar>();
	m_lvBar->GetComponent<CBar>()->SetBold(50.0f);
	m_lvBar->GetComponent<CBar>()->GetPolyBar()->SetColor(D3DCOLOR_RGBA(0, 255, 255, 255));
	m_lvBar->GetComponent<CBar>()->GetPolyBG()->transform->SetSize(810.0f, 60.0f);
	m_lvBar->GetComponent<CBar>()->GetPolyBG()->transform->SetPos(-5.0f, -5.0f);
	m_lvBar->transform->SetPos(50.0f, 50.0f);

	// ���x���A�b�v�o�[�̔w�i
	GameObject* lvBarBG = new GameObject();
	lvBarBG->AddComponent<CPolygon>()->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	lvBarBG->transform->SetSize(820.0f, 70.0f);
	lvBarBG->SetParent(m_lvBar);
	lvBarBG->transform->SetPos(-10.0f, -10.0f);
	lvBarBG->SetPriority(5);

	// ���x���e�L�X�g
	m_lvText = new GameObject();
	m_lvText->AddComponent<CText>()->SetText("Lv." + std::to_string(m_level));
	m_lvText->GetComponent<CText>()->SetFont("���m�xPOP v2");
	m_lvText->GetComponent<CText>()->SetFontSize(130);
	m_lvText->GetComponent<CText>()->SetFontColor(D3DCOLOR_RGBA(226, 174, 0, 255));
	m_lvText->GetComponent<CText>()->SetOutlineColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	m_lvText->GetComponent<CText>()->SetOutlineSize(3);
	m_lvText->transform->SetPos(900.0f, 40.0f);
}

//=============================================================
// [PlayerControl] �X�V
//=============================================================
void PlayerControl::Update()
{
	float axisX = 0.0f;
	float axisY = 0.0f;

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

	// ����
	if (INPUT_INSTANCE->onPress("a")) axisX += -1.0f;
	if (INPUT_INSTANCE->onPress("d")) axisX += 1.0f;
	if (INPUT_INSTANCE->onPress("w")) axisY += 1.0f;
	if (INPUT_INSTANCE->onPress("s")) axisY += -1.0f;

	// �n�C�h
	m_hide = INPUT_INSTANCE->onPress("space") || INPUT_INSTANCE->onPress("p:a");
	if (m_hide)
	{
		gameObject->GetComponent<CMotionManager>()->Play("hiding");
		return;
	}

	// �������v�Z����
	float angle = 0.0f;
	if (controlStickLx == 0 && controlStickLy == 0)
	{
		angle = atan2f(axisX, axisY) + Benlib::PosAngle(m_camera->transform->GetWPos(), transform->GetWPos());
	}
	else
	{
		angle = atan2f(controlStickLx, controlStickLy) + Benlib::PosAngle(m_camera->transform->GetWPos(), transform->GetWPos());
	}
	

	// �ړ�
	float speed = 1.0f - m_level * 0.05f;
	if ((axisX != 0.0f || axisY != 0.0f) || (controlStickLx != 0 || controlStickLy != 0))
	{
		gameObject->GetComponent<CMotionManager>()->Play("move");
		transform->Translate(sinf(angle) * speed, 0.0f, cosf(angle) * speed);

		if (m_soundCounter == 29)
		{
			GameObject* sound = new GameObject;
			sound->AddComponent<CSound>()->LoadWav("data\\SE\\move_00.wav");
			sound->GetComponent<CSound>()->IsStoppedDestroy();
			sound->GetComponent<CSound>()->Play();
		}
	}
	else
	{
		gameObject->GetComponent<CMotionManager>()->Play("neutral");
	}

	// �v���C���[�̉�]��ݒ肷��
	transform->SetRot(0.0f, angle + D3DX_PI, 0.0f);

	// ���x����UI
	m_progress += ((m_score % 7) / (float)7 - m_progress) * 0.08f;
	m_lvBar->GetComponent<CBar>()->SetProgress(m_progress);


	m_soundCounter++;
	if (m_soundCounter >= 30)
	{
		m_soundCounter = 0;
	}
}

//=============================================================
// [PlayerControl] �X�R�A�̉��Z
//=============================================================
void PlayerControl::AddScore(const int& score)
{
	// �X�R�A�����Z����
	m_score += score;

	int oldLv = m_level;

	// ���x�����v�Z����
	m_level = 1 + (m_score - (m_score % 7)) / 7;
	m_lvText->GetComponent<CText>()->SetText("Lv." + std::to_string(m_level));

	if (m_level != oldLv)
	{
		GameObject* sound = new GameObject();
		sound->AddComponent<CSound>()->LoadWav("data\\SE\\lvup_00.wav");
		sound->GetComponent<CSound>()->IsStoppedDestroy();
		sound->GetComponent<CSound>()->Play();
	}

	if (m_level == 8)
	{
		GameObject* sound = new GameObject();
		sound->AddComponent<CSound>()->LoadWav("data\\SE\\caneat_00.wav");
		sound->GetComponent<CSound>()->IsStoppedDestroy();
		sound->GetComponent<CSound>()->Play();
	}

	// �v���C���[�̍X�V
	UpdatePlayer();
}

//=============================================================
// [PlayerControl] �v���C���[�̍X�V
//=============================================================
void PlayerControl::UpdatePlayer()
{
	gameObject->GetComponent<CBoxCollider>()->SetSize(D3DXVECTOR3(5.0f, 5.0f, 5.0f) * (m_level * 0.3f + 1));
	gameObject->GetComponent<CBoxCollider>()->SetOffset(D3DXVECTOR3(0.0f, 5.0f * (m_level * 0.3f + 1), 0.0f));
	CCollision::GetCollision(gameObject)->UpdateCollision();
	CCollision::GetCollision(gameObject)->GetRigidBody()->setActivationState(DISABLE_DEACTIVATION);

	gameObject->transform->SetScale(0.1f * (m_level * 0.3f + 1));
}