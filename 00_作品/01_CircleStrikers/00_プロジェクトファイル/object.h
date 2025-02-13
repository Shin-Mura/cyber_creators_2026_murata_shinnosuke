//========================================================================================================
//
//�I�u�W�F�N�g����[object.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"
#include "component.h"

//�I�u�W�F�N�g�N���X
class Object
{
public:
	static const int PRIORITY = 6;   //�D��x

	//�^�O�̗�
	enum TAG
	{
		IS_DEFAULT = 0,
		IS_PLAYER,
	};

	//�R���X�g���N�^
	Object(std::string sName = "Object")
	{
		//�����o�ϐ�������������
		this->m_sName = sName;   //���O
		this->m_tag = TAG::IS_DEFAULT;   //�^�O
		this->m_nPriority = 3;   //�D��x
		this->m_isDeath = false;   //���S�t���O
		this->m_isActive = true;   //�A�N�e�B�u�t���O
		this->m_vComponent.clear();

		//�I�u�W�F�N�g�Ǘ��̍Ō���ɕۑ�����
		Object::m_vObject.push_back(this);
	}

	//�f�X�g���N�^
	virtual ~Object()
	{
	}

	virtual void Init();   //����������
	virtual void Uninit();   //�I������
	virtual void Update();   //�X�V����
	virtual void Draw();   //�`�揈��
	void Death() { this->m_isDeath = true; };   //���S�t���O�𗧂Ă鏈��

	//�R���|�[�l���g�̒ǉ�����
	void AddComponent(Component* pComponent)
	{
		//�R���|�[�l���g�ɒǉ�����
		this->m_vComponent.push_back(pComponent);
	}

	void SetTag(TAG tag) { this->m_tag = tag; };   //�^�O�̐ݒ菈��
	void SetActive(bool isActive) { this->m_isActive = isActive; };   //�A�N�e�B�u�t���O�̐ݒ�

	TAG GetTag() { return this->m_tag; };   //�^�O�̎擾����
	int GetPriority() { return this->m_nPriority; };   //�D��x�̎擾����

	//�R���|�[�l���g�̎擾����
	template<class T> T* GetComponent()
	{
		//�R���|�[�l���g�̐����J��Ԃ�
		for (unsigned int i = 0; i < this->m_vComponent.size(); i++)
		{
			//�w��̃R���|�[�l���g���m�F����
			if (T* pComponent = dynamic_cast<T*>(this->m_vComponent[i]))
			{//�w��̃R���|�[�l���g�̏ꍇ
				//�R���|�[�l���g��Ԃ�
				return (T*)this->m_vComponent[i];
			}
		}

		//null��Ԃ�
		return nullptr;
	}

	//�I�u�W�F�N�g����
	static Object* Find(std::string sName)
	{
		Object* pObject = nullptr;   //�Ԃ��I�u�W�F�N�g�i�[�p

		//�I�u�W�F�N�g�̐����J��Ԃ�
		for (unsigned int i = 0; i < Object::m_vObject.size(); i++)
		{
			//���O���m�F����
			if (Object::m_vObject[i]->m_sName == sName)
			{
				//�Ԃ��I�u�W�F�N�g�i�[�p�ɕۑ�����
				pObject = Object::m_vObject[i];

				//���[�v�𔲂��o��
				break;
			}
		}

		//�I�u�W�F�N�g��Ԃ�
		return pObject;
	}

	//�ꊇ�������
	static void ReleaseAll()
	{
		//�I�u�W�F�N�g�̐����J��Ԃ�
		for (unsigned int i = 0; i < Object::m_vObject.size(); i++)
		{
			//�I���������s��
			Object::m_vObject[i]->Uninit();
			delete Object::m_vObject[i];
		}

		//�I�u�W�F�N�g���폜����
		Object::m_vObject.clear();
	}

	//�ꊇ�X�V����
	static void UpdateAll()
	{
		//�I�u�W�F�N�g�̐����J��Ԃ�
		for (unsigned int i = 0; i < Object::m_vObject.size(); i++)
		{
			//�A�N�e�B�u�t���O���m�F����
			if (Object::m_vObject[i]->m_isActive)
			{
				//�X�V�������s��
				Object::m_vObject[i]->Update();
				if (Object::m_vObject[i]->m_isDeath == true)
				{//���S�t���O�������Ă���ꍇ
					//�폜����
					Object::m_vObject[i]->Release();
				}
			}
		}
	}

	//�ꊇ�`�揈��
	static void DrawAll()
	{
		//�D��x�̕��J��Ԃ�
		for (int i = 0; i < Object::PRIORITY; i++)
		{
			//�I�u�W�F�N�g�̐����J��Ԃ�
			for (unsigned int j = 0; j < Object::m_vObject.size(); j++)
			{
				//�D��x���m�F����
				if (Object::m_vObject[j]->GetPriority() == i)
				{//���݂̎���ƈ�v�����ꍇ
					//�A�N�e�B�u�t���O���m�F����
					if (Object::m_vObject[j]->m_isActive)
					{
						//�`�揈�����s��
						Object::m_vObject[j]->Draw();
					}
				}
			}
		}
	}

	static Object* Get(int nId) { return m_vObject[nId]; };   //�擾����

	//�w��R���|�[�l���g���t���Ă���I�u�W�F�N�g�̎擾
	template<class T> static std::vector<Object*> Get()
	{
		std::vector<Object*> vObject;   //�Ԃ��p�R���e�i

		//�I�u�W�F�N�g�̐����J��Ԃ�
		for (unsigned int i = 0; i < Object::m_vObject.size(); i++)
		{
			Object* pObject = Object::m_vObject[i];

			//�R���|�[�l���g�̐����J��Ԃ�
			for (unsigned int j = 0; j < pObject->m_vComponent.size(); j++)
			{
				//�L���X�g�o���邩�m�F����
				if (T* pComponent = dynamic_cast<T*>(pObject->m_vComponent[j]))
				{
					//�R���e�i�ɕۑ�����
					vObject.push_back(Object::m_vObject[i]);
				}
			}
		}

		//�R���e�i��Ԃ�
		return vObject;
	}

private:
	//�������
	void Release()
	{
		//�j������
		this->Uninit();
		Object::m_vObject.erase(Object::m_vObject.begin() + this->GetOder());
		delete this;
	}

	//���Ԃ̎擾����
	int GetOder()
	{
		int nOder = -1;   //����

		//�I�u�W�F�N�g�̐����J��Ԃ�
		for (unsigned int i = 0; i < Object::m_vObject.size(); i++)
		{
			//�ۑ����ꂽ�I�u�W�F�N�g���m�F����
			if (Object::m_vObject[i] == this)
			{//���g�̏ꍇ
				nOder = i;

				//���[�v�𔲂��o��
				break;
			}
		}

		//���Ԃ�Ԃ�
		return nOder;
	}

	std::string m_sName;   //���O
	TAG m_tag;   //�^�O
	int m_nPriority;   //�D��x
	bool m_isDeath;   //���S�t���O
	bool m_isActive;   //�A�N�e�B�u�t���O
	std::vector<Component*> m_vComponent;

	static std::vector<Object*> m_vObject;   //�I�u�W�F�N�g�Ǘ�
};

#endif // !_OBJECT_H_
