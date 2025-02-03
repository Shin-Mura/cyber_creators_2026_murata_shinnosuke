//=============================================================
//
// �J�����̓��� [camera_move.cpp]
// Author: Ito Kotaro
//
//=============================================================
#include "camera_move.h"

#include "manager.h"
#include "component/3d/camera.h"

//=============================================================
// [CCameraMove] ������
//=============================================================
void CCameraMove::Init()
{
	m_cameraRot = { 0.0f, 0.0f, 0.0f };
}

//=============================================================
// [CCameraMove] �X�V
//=============================================================
void CCameraMove::Update()
{
	// �^�[�Q�b�g�����݂��邩�m�F����
	if (m_pTarget == nullptr)
	{ // �^�[�Q�b�g�����݂��Ȃ��Ƃ�
		return;
	}

	// �J�[�\��
	if (GetActiveWindow() == CManager::GetInstance()->GetHWND())
	{
		// ���݂̃J�[�\���ʒu���擾����
		CManager::CursorPos cursor = CManager::GetInstance()->GetCursorClientPos();

		// �O��̃J�[�\���ʒu�ƈقȂ�Ƃ�
		if (cursor.x != m_oldCursor.x || cursor.y != m_oldCursor.y)
		{ // �O��̈ʒu�ƈقȂ�Ƃ�
			m_cameraRot.y += (cursor.x - m_oldCursor.x) * 0.002f;
			m_cameraRot.x += (cursor.y - m_oldCursor.y) * 0.002f;
		}

		// �E�B���h�E�O�Ƀ}�E�X���s�����Ƃ�
		CManager::GetInstance()->SetCursorClientPos(static_cast<float>(CRenderer::SCREEN_WIDTH / 2), static_cast<float>(CRenderer::SCREEN_HEIGHT / 2));
		m_oldCursor = CManager::GetInstance()->GetCursorClientPos();
	}

	// �R���g���[���[�̏����擾����
	auto pGamepadDev = INPUT_INSTANCE->GetInputDevice<CGamepadDevice>();
	short stickRX = pGamepadDev->GetState().Gamepad.sThumbRX;
	short stickRY = pGamepadDev->GetState().Gamepad.sThumbRY;
	if (GetActiveWindow() == CManager::GetInstance()->GetHWND())
	{
		if (stickRX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		{
			m_cameraRot.y += -0.05f;
		}
		if (stickRX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		{
			m_cameraRot.y += 0.05f;
		}
		if (stickRY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		{
			m_cameraRot.x += 0.02f;
		}
		if (stickRY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		{
			m_cameraRot.x += -0.02f;
		}
	}

	UpdateTPS();

	transform->SetPos(m_posS);

	//�J�����̎��_�ړ��𐧌��������ł��I
	if (this->m_cameraRot.x <= 0.1f)
	{
		this->m_cameraRot.x = 0.1f;
	}
	if (this->m_cameraRot.x >= D3DX_PI - 1.0f)
	{
		this->m_cameraRot.x = D3DX_PI - 1.0f;
	}
}

//=============================================================
// [CCameraMove] �X�V
//=============================================================
void CCameraMove::UpdateTPS()
{
	// �J�����̎擾
	CCamera* pCamera = gameObject->GetComponent<CCamera>();
	pCamera->SetCustomPosR(true);
	pCamera->SetPosR(m_pTarget->transform->GetWPos() + D3DXVECTOR3(0.0f, 9.0f, 0.0f));

	// ���K��
	if (m_cameraRot.x < -D3DX_PI * 0.5f)
	{
		m_cameraRot.x = -D3DX_PI * 0.5f;
	}
	if (m_cameraRot.x > D3DX_PI * 0.5f)
	{
		m_cameraRot.x = D3DX_PI * 0.5f;
	}

	// ���_�̈ʒu���v�Z����
	float distance = 100.0f;
	D3DXVECTOR3 posS = { 0.0f, 0.0f, -distance };
	D3DXMATRIX mtxY, mtxX, mtxS;
	D3DXMatrixRotationX(&mtxX, m_cameraRot.x);
	D3DXMatrixRotationY(&mtxY, m_cameraRot.y);
	mtxS = mtxX * mtxY;
	D3DXVec3TransformCoord(&posS, &posS, &mtxS);

	posS += m_pTarget->transform->GetWPos();
	m_posS = posS;
}


//=============================================================
// [CCameraMove] �I�u�W�F�N�g���j�����ꂽ�Ƃ��̏���
//=============================================================
void CCameraMove::OnDestroyOtherObject(GameObject* other)
{
	if (other == m_pTarget)
	{ // �^�[�Q�b�g�̂Ƃ�
		m_pTarget = nullptr;
	}
}