//========================================================================================================
//
//�R���|�[�l���g�̏���[component.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "object.h"

//�R���|�[�l���g
class Component
{
public:
	//�R���X�g���N�^
	Component(Object* pObject)
	{
		//�����o�ϐ�������������
		this->m_pObject = pObject;   //�I�u�W�F�N�g

		//�R���e�i�ɕۑ�����
		Component::m_vComponent.push_back(this);
	}

	//�f�X�g���N�^
	virtual ~Component()
	{
		//�R���|�[�l���g�̐����J��Ԃ�
		for (unsigned int i = 0; i < Component::m_vComponent.size(); i++)
		{
			//�R���|�[�l���g���m�F����
			if (Component::m_vComponent[i] != this)
			{//�Ⴄ�R���|�[�l���g�̏ꍇ
				//���̃��[�v�Ɉڍs����
				continue;
			}

			//�R���e�i����폜����
			Component::m_vComponent.erase(Component::m_vComponent.begin() + i);
			break;   //���[�v�𔲂��o��
		}
	}
	
	virtual void Init() {};   //����������
	virtual void Uninit() {};   //�I������
	virtual void Update() {};   //�X�V����
	virtual void Draw() {};   //�`�揈��

	Object* GetObj() { return this->m_pObject; };   //�I�u�W�F�N�g�̎擾
	template<class T> T* GetComponent() { return this->m_pObject->GetComponent<T>(); };   //�R���|�[�l���g�̎擾

	static std::vector<Component*> Get() { return Component::m_vComponent; };   //�R���e�i�̎擾
	
	//�w��R���|�[�l���g�̎擾
	template<class T> static std::vector<T*> Get()
	{
		std::vector<T*> vComponent;   //�Ԃ��p�R���e�i

		//�I�u�W�F�N�g�̐����J��Ԃ�
		for (unsigned int i = 0; i < Component::m_vComponent.size(); i++)
		{
			//�w��̃R���|�[�l���g���m�F����
			if (T* pComponent = dynamic_cast<T*>(Component::m_vComponent[i]))
			{//�w��̃R���|�[�l���g�̏ꍇ
				//�Ԃ��p�R���e�i�ɕۑ�����
				vComponent.push_back((T*)Component::m_vComponent[i]);
			}
		}

		//�R���e�i��Ԃ�
		return vComponent;
	}

private:
	Object* m_pObject;

	static std::vector<Component*> m_vComponent;   //�R���e�i
};

#endif // !_COMPONENT_H_
