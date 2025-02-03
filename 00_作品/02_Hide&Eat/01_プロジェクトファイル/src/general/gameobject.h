//=============================================================
//
// �Q�[���I�u�W�F�N�g [gameobject.h]
// Author: Ito Kotaro
//
//=============================================================
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "transform.h"
#include "data_field.h"

// �}�N����`
#define TAG_NODESTROY	"NoDestroy"	// �V�[����ύX���Ă��폜���Ȃ�

class Component;

// �Q�[���I�u�W�F�N�g�N���X�̒�`
class GameObject
{
public:
	/*
	@brief �Q�[���I�u�W�F�N�g���쐬����
	*/
	GameObject(const std::string& name = "", const std::string& tag = "");
	~GameObject();

	/*
	@brief �Q�[���I�u�W�F�N�g�̖��O���擾����
	@return ���O
	*/
	std::string& GetName() { return m_name; }

	/*
	@brief �Q�[���I�u�W�F�N�g�̃^�O�����擾����
	@return �^�O��
	*/
	std::string& GetTag() { return m_tag; }

	/*
	@brief �Q�[���I�u�W�F�N�g�̗D��x���擾����
	@return �D��x
	*/
	int GetPriority() { return m_nPriority; }

	/*
	@brief �Q�[���I�u�W�F�N�g�̃A�N�e�B�u��Ԃ��擾����
	@retval �A�N�e�B�u=true, ��A�N�e�B�u=false
	*/
	bool GetActive() { return m_active; }

	/*
	@brief �Q�[���I�u�W�F�N�g�̕\����Ԃ��擾����
	@retval �\��=true, ��\��=false
	*/
	bool GetVisible() { return m_visible; }

	/*
	@brief �Q�[���I�u�W�F�N�g�̖��O��ݒ肷��
	@param[in] name : ���O
	*/
	void SetName(std::string name) { m_name = name; }

	/*
	@brief �Q�[���I�u�W�F�N�g�̃^�O��ݒ肷��
	@param[in] tag : �^�O��
	*/
	void SetTag(std::string tag) { m_tag = tag; }

	/*
	@brief �Q�[���I�u�W�F�N�g�̗D��x��ݒ肷��
	@param[in] nPriority : �D��x
	*/
	void SetPriority(int nPriority);

	/*
	@brief �Q�[���I�u�W�F�N�g�̃A�N�e�B�u��Ԃ�ݒ肷��
	@param[in] bActive : �A�N�e�B�u��Ԃɂ��邩
	*/
	void SetActive(bool bActive) { m_active = bActive; }

	/*
	@brief �Q�[���I�u�W�F�N�g�̕\����Ԃ�ݒ肷��
	@param[in] bActive : �\����Ԃɂ��邩
	*/
	void SetVisible(bool bVisible) { m_visible = bVisible; }

	/*
	@brief �Q�[���I�u�W�F�N�g�̐e��ݒ肷��
	@param[in] gameObject : �e�̃Q�[���I�u�W�F�N�g
	*/
	void SetParent(GameObject* gameObject) { transform->SetParent(gameObject->transform); }

	/*
	@brief �Q�[���I�u�W�F�N�g�̐e���擾����
	@return GameObject : �e�̃Q�[���I�u�W�F�N�g
	*/
	GameObject* GetParent() {
		for (auto itr = m_gameObjects.begin(); itr != m_gameObjects.end(); itr++)
		{
			if ((*itr)->transform == this->transform->GetParent())
			{ // �e�ƈ�v����Ƃ�
				return *itr;
			}
		}
		return nullptr;
	}

	static void UpdateAll();
	static void DrawAll();
	static void DrawUIAll();

	/*
	@brief �Q�[���I�u�W�F�N�g����������
	@param[in] name : �Q�[���I�u�W�F�N�g��
	@return GameObject�̃|�C���^
	*/
	static GameObject* Find(const std::string& name);

	/*
	@brief �Q�[���I�u�W�F�N�g����������
	@param[in] name : �Q�[���I�u�W�F�N�g��
	@param[in] tag : �^�O
	@return GameObject�̃|�C���^
	*/
	static GameObject* Find(const std::string& name, const std::string& tag);

	/*
	@brief �q�̃Q�[���I�u�W�F�N�g���擾����
	@param[in] includeTreeChildren : �q�̎q�ȏ���܂߂邩
	@return �q�̃Q�[���I�u�W�F�N�g�z��
	*/
	std::vector<GameObject*> GetChildren(const bool& includeTreeChildren = false);

	/*
	@brief ���O����q�̃Q�[���I�u�W�F�N�g���擾����
	@return �q�̃Q�[���I�u�W�F�N�g
	*/
	GameObject* FindNameChildren(const std::string& sName);

	/*
	@brief �^�O����q�̃Q�[���I�u�W�F�N�g���擾����
	@return �q�̃Q�[���I�u�W�F�N�g
	*/
	GameObject* FindTagChildren(const std::string& sTag);

	/*
	@brief �R���|�[�l���g��ǉ�����
	*/
	template<class T, typename ...Args > inline T* AddComponent(Args... args) {
		// �R���|�[�l���g���쐬����
		T* component = new T(args...);

		// �Q�[���I�u�W�F�N�g�ɃA�^�b�`����
		component->AttachGameObject(this);

		// �R���|�[�l���g��ǉ�����
		m_components.push_back(component);

		// �\�[�g���s��
		Component::Sort();

		// �R���|�[�l���g�̏��������������s����
		component->Init();

		// �쐬�����R���|�[�l���g��Ԃ�
		return component;
	}

	/*
	@brief �R���|�[�l���g���擾����
	@param[in] includeChild : �q�N���X���܂߂邩
	*/
	template<class T> inline T* GetComponent(const bool& includeChild = false) {
		for (auto itr = m_components.begin(); itr != m_components.end(); itr++)
		{
			if (includeChild)
			{ // �q���܂ނƂ�
				if (T* pComp = dynamic_cast<T*>(*itr))
					return (T*)*itr;
			}
			else
			{ // �q���܂܂Ȃ��Ƃ�
				if (typeid(T) == typeid(**itr))
					return (T*)*itr;
			}
		}
		return nullptr;
	}

	/*
	@brief �����̃R���|�[�l���g���擾����
	@param[in] includeChild : �q�N���X���܂߂邩
	*/
	template<class T> inline std::vector<T*> GetComponents(const bool& includeChild = false) {
		std::vector<T*> result;
		for (auto itr = m_components.begin(); itr != m_components.end(); itr++)
		{
			if (includeChild)
			{ // �q���܂ނƂ�
				if (T* pComp = dynamic_cast<T*>(*itr))
					result.push_back((T*)*itr);
			}
			else
			{ // �q���܂܂Ȃ��Ƃ�
				if (typeid(T) == typeid(**itr))
					result.push_back((T*)*itr);
			}
		}
		return result;
	}

	/*
	@brief ���ׂẴR���|�[�l���g���擾����
	*/
	std::vector<Component*>& GetComponents() {
		return m_components;
	}

	/*
	@brief ���ׂẴQ�[���I�u�W�F�N�g���擾����
	*/
	static std::vector<GameObject*> GetAllGameObjects() {
		return m_gameObjects;
	}

	/*
	@brief �I�u�W�F�N�g�����擾����
	*/
	static int GetNumObjects() { return (int)m_gameObjects.size(); }

	/*
	@brief �Q�[���I�u�W�F�N�g��j������
	*/
	void Destroy(const bool& includeChild = false);

	/*
	@brief �R���|�[�l���g��j������
	@param[in] component : �R���|�[�l���g�̃|�C���^
	*/
	void Destroy(Component* component);

	/*
	@brief ���ׂẴR���|�[�l���g��j������
	@param[in] bIncludeNot : �폜�Ώۂ�NoDestroy���܂ނ�
	*/
	static void DestroyAll(bool bIncludeNot = false);

	/*
	@brief ���S�t���O�̂����I�u�W�F�N�g��j������
	*/
	static void DestroyDeathFlag();

	/*
	@brief �Q�[���I�u�W�F�N�g�����݂��邩
	@param[in] pGameObject : �Q�[���I�u�W�F�N�g�̃|�C���^
	*/
	static bool IsExist(GameObject* pGameObject);

	/*
	@brief �v���n�u�̓ǂݍ���
	@param[in] sPath : �v���n�u�̃p�X
	*/
	static GameObject* LoadPrefab(const std::string& sPath, Transform transform = Transform());

	// @brief �g�����X�t�H�[�����
	Transform* transform;

	static const int DEFAULT_PRIORITY;		// �f�t�H���g�̗D��x
private:
	bool m_visible;														// �\��
	bool m_active;														// �A�N�e�B�u
	std::string m_name;												// ���O
	std::string m_tag;													// �^�O
	int m_nPriority;														// �D��x
	bool m_bDeathFlag;												// ���S�t���O
	std::vector<Component*> m_components;				// �R���|�[�l���g
	static std::vector<GameObject*> m_gameObjects;	// ���ׂẴQ�[���I�u�W�F�N�g�̃|�C���^���Ǘ�
};

#endif // !_GAMEOBJECT_H_