//=============================================================
//
// �R���|�[�l���g [component.cpp]
// Author: Ito Kotaro
// 
// �Q�[���I�u�W�F�N�g�ɒǉ��ł���v�f���\��������̂ł�
//
//=============================================================
#include "component.h"
std::vector<Component*> Component::m_pComponents;

//=============================================================
// [Component] �Q�[���I�u�W�F�N�g�ɃA�^�b�`����
//=============================================================
void Component::AttachGameObject(GameObject* attachObj)
{
	if (!m_attached)
	{ // �A�^�b�`����Ă��Ȃ��Ƃ�
		gameObject = attachObj;
		transform = gameObject->transform;
		m_attached = true;
		m_pComponents.push_back(this);
	}
}

//=============================================================
// [Component] ���݂��邩
//=============================================================
bool Component::IsExist(Component* pComponent)
{
	for (auto itr = m_pComponents.begin(); itr != m_pComponents.end(); itr++)
	{
		if (*itr == pComponent)
		{	// ���݂��Ă���Ƃ�
			return true;
		}
	}
	return false;
}

//=============================================================
// [Component] �\�[�g
//=============================================================
void Component::Sort()
{
	// �A�^�b�`����Ă���Q�[���I�u�W�F�N�g�̗D��x�Ŕ�r���A�\�[�g����
	std::sort(m_pComponents.begin(), m_pComponents.end(), [](Component* com1, Component* com2) {return com1->gameObject->GetPriority() < com2->gameObject->GetPriority(); });
}

//=============================================================
// [Component] �p�X�̊J�n
//=============================================================
void Component::BeginPass()
{
	if (m_shader != nullptr)
	{
		m_shader->BeginPass(m_pass);
	}
}

//=============================================================
// [Component] �p�X�̏I��
//=============================================================
void Component::EndPass()
{
	if (m_shader != nullptr)
	{
		m_shader->EndPass();
	}

	// �V�F�[�_�[�������Z�b�g����
	m_shader = nullptr;
	m_pass = 0;
}

//=============================================================
// [Component] �V�F�[�_�[�ɏ���n��
//=============================================================
void Component::SetParam(Shader::ParamData data)
{
	if (m_shader != nullptr)
	{
		data.component = this;
		m_shader->SetParam(data);
	}
}