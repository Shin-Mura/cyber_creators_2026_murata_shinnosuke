//=============================================================
//
// �{�^�� [button.cpp]
// Author: Ito Kotaro
//
//=============================================================
#include "button.h"
#include "manager.h"

//=============================================================
// [ButtonUI] �X�V
//=============================================================
void ButtonUI::Update()
{
	CPolygon::Update();

	// �}�E�X�ʒu�̎擾
	CManager::CursorPos mousePos = CManager::GetInstance()->GetCursorClientPos();
	D3DXVECTOR3 wPos = transform->GetWPos();

	if (wPos.x <= mousePos.x && mousePos.x <= wPos.x + transform->GetSize().x &&
		wPos.y <= mousePos.y && mousePos.y <= wPos.y + transform->GetSize().y)
	{ // �N���b�N�͈͓��ɂ���Ƃ�
		if (INPUT_INSTANCE->onTrigger("lclick"))
		{
			// �N���b�N�C�x���g
			if (m_onClick != nullptr)
			{
				m_onClick();
			}
		}

		// �{�^���̐F��ύX
		SetColor(D3DCOLOR_RGBA(190, 190, 190, 255));
	}
	else
	{
		// �{�^���̐F��ύX
		SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
	}
}