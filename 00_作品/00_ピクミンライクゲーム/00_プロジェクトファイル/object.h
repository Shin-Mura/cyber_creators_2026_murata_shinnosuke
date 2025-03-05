//========================================================================================================
//
//�I�u�W�F�N�g����[object.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"

//�O���錾
class Component;   //�R���|�[�l���g
//�I�u�W�F�N�g�N���X
class Object
{
public:
	static const int PRIORITY = 6;   //�D��x

	//�^�O�̗�
	enum TAG
	{
		IS_DEFAULT = 0,   //�f�t�H���g
		IS_PLAYER,   //�v���C���[
		IS_FRUIT,   //�t���[�c
		IS_JELLY,   //�[���[
		IS_OBSTACLE,   //��Q��
	};

	//�R���X�g���N�^
	Object(std::string sName, int nPriority = 3)
	{
		//�����o�ϐ�������������
		this->m_sName = sName;   //���O
		this->m_tag = TAG::IS_DEFAULT;   //�^�O
		this->m_nPriority = 3;   //�D��x
		this->m_tag = Object::TAG::IS_DEFAULT;   //�^�O
		this->m_nPriority = nPriority;   //�D��x
		this->m_isDeath = false;   //���S�t���O
		this->m_isActive = true;   //�A�N�e�B�u�t���O
		this->m_vComponent.clear();

		//�I�u�W�F�N�g�Ǘ��̍Ō���ɕۑ�����
		Object::m_vObject.push_back(this);
	}

	//�f�X�g���N�^
	virtual ~Object()
	{
		//�R���e�i���玩�g���폜����
		Object::m_vObject.erase(Object::m_vObject.begin() + this->GetOder());
	}

	virtual void Init();   //����������
	virtual void Uninit();   //�I������
	virtual void Update();   //�X�V����
	virtual void Draw();   //�`�揈��
	void Death() { this->m_isDeath = true; };   //���S�t���O�𗧂Ă鏈��
	void AddComponent(Component* pComponent) { this->m_vComponent.push_back(pComponent); };   //�R���|�[�l���g�̒ǉ�����
	void SetTag(Object::TAG tag) { this->m_tag = tag; };   //�^�O�̐ݒ菈��
	void SetActive(bool isActive) { this->m_isActive = isActive; };   //�A�N�e�B�u�t���O�̐ݒ�
	Object::TAG GetTag() { return this->m_tag; };   //�^�O�̎擾����
	int GetPriority() { return this->m_nPriority; };   //�D��x�̎擾����
	bool GetActive() { return this->m_isActive; };   //�A�N�e�B�u�t���O�̎擾

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

	static void UpdateAll();   //�ꊇ�X�V
	static void DrawAll();   //�ꊇ�`��
	static void DestroyAll();   //�ꊇ�j��
	static Object* Find(std::string sName);   //����
	static Object* Get(int nId) { return m_vObject[nId]; };   //�擾����

private:
	//���Ԃ̎擾����
	int GetOder()
	{
		//�I�u�W�F�N�g�̐����J��Ԃ�
		for (unsigned int i = 0; i < Object::m_vObject.size(); i++)
		{
			//�ۑ����ꂽ�I�u�W�F�N�g���m�F����
			if (Object::m_vObject[i] != this)
			{//���g����Ȃ��ꍇ
				//���̃��[�v�Ɉڍs����
				continue;
			}

			//�����Ԃ�
			return i;
		}

		//-1��Ԃ�
		return -1;
	}

	std::string m_sName;   //���O
	TAG m_tag;   //�^�O
	int m_nPriority;   //�D��x
	bool m_isDeath;   //���S�t���O
	bool m_isActive;   //�A�N�e�B�u�t���O
	std::vector<Component*> m_vComponent;

	static std::vector<Object*> m_vObject;   //�R���e�i
};

//��̃I�u�W�F�N�g
class ObjectEmpty : public Object   //(�e)�I�u�W�F�N�g
{
public:
	//�R���X�g���N�^
	ObjectEmpty(std::string sName, int nPriority) : Object(sName, nPriority)
	{
	}

	//�f�X�g���N�^
	~ObjectEmpty() override
	{
	}

private:

};

//2D�I�u�W�F�N�g
class Object2D : public Object   //(�e)�I�u�W�F�N�g
{
public:
	//�R���X�g���N�^
	Object2D(std::string sName, int nPriority) : Object(sName, nPriority)
	{
	}

	//�f�X�g���N�^
	~Object2D()
	{
	}

private:

};

//3D�I�u�W�F�N�g
class Object3D : public Object   //(�e)�I�u�W�F�N�g
{
public:
	//�R���X�g���N�^
	Object3D(std::string sName, int nPriority) : Object(sName, nPriority)
	{
	}

	//�f�X�g���N�^
	~Object3D() override
	{
	}

private:

};

//�J�����I�u�W�F�N�g
class ObjectCamera : public Object   //(�e)�I�u�W�F�N�g
{
public:
	//�R���X�g���N�^
	ObjectCamera(std::string sName, int nPriority) : Object(sName, nPriority)
	{
	}

	//�f�X�g���N�^
	~ObjectCamera() override
	{
	}

private:

};

//��̃I�u�W�F�N�g
class ObjectLight : public Object   //(�e)�I�u�W�F�N�g
{
public:
	//�R���X�g���N�^
	ObjectLight(std::string sName, int nPriority) : Object(sName, nPriority)
	{
	}

	//�f�X�g���N�^
	~ObjectLight() override
	{
	}

private:

};

#endif // !_OBJECT_H_