//=============================================================
//
// �Q�[���I�u�W�F�N�g [gameobject.cpp]
// Author: Ito Kotaro
//
//=============================================================
#include "gameobject.h"
#include "component.h"
#include "internal/physics.h"
#include "component/3d/motion.h"
#include "component/3d/mesh.h"
#include "component/3d/collision.h"
#include "component/3d/light.h"
#include "scene.h"
#include <fstream>
using namespace std;


// �ÓI�����o�ϐ��̏�����
std::vector<GameObject*> GameObject::m_gameObjects;
const int GameObject::DEFAULT_PRIORITY = 6;

//=============================================================
// �Q�[���I�u�W�F�N�g�̍X�V����
//=============================================================
void GameObject::UpdateAll()
{
	// �X�V�������s��
	for (auto itr = m_gameObjects.begin(); itr != m_gameObjects.end(); itr++)
	{
		if ((*itr)->GetActive())
		{ // �A�N�e�B�u�̂Ƃ�
			// �R���|�[�l���g�̍X�V�������s��
			for (auto itrComp = (*itr)->m_components.begin(); itrComp != (*itr)->m_components.end(); itrComp++)
			{
				if ((*itrComp)->enabled)
				{
					(*itrComp)->Update();
				}
			}
		}
	}
}

//=============================================================
// �Q�[���I�u�W�F�N�g�̕`�揈��
//=============================================================
void GameObject::DrawAll()
{
	// �`�揈�����s��
	for (auto itr = m_gameObjects.begin(); itr != m_gameObjects.end(); itr++)
	{
		if ((*itr)->GetActive() && (*itr)->GetVisible())
		{ // �A�N�e�B�u�̂Ƃ�
			// �R���|�[�l���g�̕`�揈�����s��
			for (auto itrComp = (*itr)->m_components.begin(); itrComp != (*itr)->m_components.end(); itrComp++)
			{
				if ((*itrComp)->enabled)
				{
					(*itrComp)->BeforeDraw();
					(*itrComp)->Draw();
					(*itrComp)->AfterDraw();
				}
			}
		}
	}
}

//=============================================================
// �Q�[���I�u�W�F�N�g��UI�`�揈��
//=============================================================
void GameObject::DrawUIAll()
{
	// UI�`�揈�����s��
	for (auto itr = m_gameObjects.begin(); itr != m_gameObjects.end(); itr++)
	{
		if ((*itr)->GetActive() && (*itr)->GetVisible())
		{ // �A�N�e�B�u�̂Ƃ�
			// �R���|�[�l���g��UI�`�揈�����s��
			for (auto itrComp = (*itr)->m_components.begin(); itrComp != (*itr)->m_components.end(); itrComp++)
			{
				if ((*itrComp)->enabled)
				{
					(*itrComp)->BeforeDrawUI();
					(*itrComp)->DrawUI();
					(*itrComp)->AfterDrawUI();
				}
			}
		}
	}
}

//=============================================================
// [GameObject] �Q�[���I�u�W�F�N�g�̌���
//=============================================================
GameObject* GameObject::Find(const std::string& name)
{
	for (auto itr = m_gameObjects.begin(); itr != m_gameObjects.end(); itr++)
	{
		if ((*itr)->GetName() == name)
		{	// ���������Ƃ�
			return *itr;
		}
	}
	return nullptr;
}

//=============================================================
// [GameObject] �Q�[���I�u�W�F�N�g�̌���
//=============================================================
GameObject* GameObject::Find(const std::string& name, const std::string& tag)
{
	for (auto itr = m_gameObjects.begin(); itr != m_gameObjects.end(); itr++)
	{
		if ((*itr)->GetName() == name && (*itr)->GetTag() == tag)
		{	// ���������Ƃ�
			return *itr;
		}
	}
	return nullptr;
}

//=============================================================
// [GameObject] �Q�[���I�u�W�F�N�g�̎q���擾����
//=============================================================
std::vector<GameObject*> GameObject::GetChildren(const bool& includeTreeChildren)
{
	std::vector<GameObject*> pChildren;
	for (auto itr = m_gameObjects.begin(); itr != m_gameObjects.end(); itr++)
	{
		if ((*itr)->transform->GetParent() == this->transform)
		{ // �q�̂Ƃ�
			pChildren.push_back(*itr);

			// �q�̎q���擾����
			std::vector<GameObject*> pChildrenInChildren = (*itr)->GetChildren(true);
			for (int n = 0; n < (int)pChildrenInChildren.size(); n++)
			{
				pChildren.push_back(pChildrenInChildren[n]);
			}
		}
	}
	return pChildren;
}

//=============================================================
// [GameObject] ���O����q�̃Q�[���I�u�W�F�N�g���擾����
//=============================================================
GameObject* GameObject::FindNameChildren(const std::string& sName)
{
	// �q���擾����
	std::vector<GameObject*> pChildren = GetChildren();

	// �T��
	for (auto itr = pChildren.begin(); itr != pChildren.end(); itr++)
	{
		if ((*itr)->GetName() == sName)
		{ // ���O����v�����Ƃ�
			return *itr;
		}
	}

	// ���O����v���Ȃ������Ƃ�
	return nullptr;
}

//=============================================================
// [GameObject] �^�O����q�̃Q�[���I�u�W�F�N�g���擾����
//=============================================================
GameObject* GameObject::FindTagChildren(const std::string& sTag)
{
	// �q���擾����
	std::vector<GameObject*> pChildren = GetChildren();

	// �T��
	for (auto itr = pChildren.begin(); itr != pChildren.end(); itr++)
	{
		if ((*itr)->GetTag() == sTag)
		{ // �^�O����v�����Ƃ�
			return *itr;
		}
	}

	// �^�O����v���Ȃ������Ƃ�
	return nullptr;
}

//=============================================================
// [GameObject] �폜
//=============================================================
void GameObject::Destroy(const bool& includeChild)
{
	if (GameObject::IsExist(this))
	{
		m_bDeathFlag = true;
	}

	// �q���܂߂�ꍇ
	if (includeChild)
	{
		std::vector<GameObject*> pChildren = this->GetChildren();
		for (auto itr = pChildren.begin(); itr != pChildren.end(); itr++)
		{
			(*itr)->Destroy(true);
		}
	}
}

//=============================================================
// [GameObject] ���ׂč폜
//=============================================================
void GameObject::DestroyAll(bool bIncludeNot)
{
	for (auto itr = m_gameObjects.begin(); itr != m_gameObjects.end(); itr++)
	{
		if (bIncludeNot)
		{ // ���ׂẴI�u�W�F�N�g��j������
			(*itr)->Destroy();
		}
		else
		{ // NotDestroy�̃^�O���t���Ă���ꍇ�̓X���[����
			if ((*itr)->GetTag() != TAG_NODESTROY)
			{ // �^�O�������Ă��Ȃ��ꍇ
				(*itr)->Destroy();
			}
		}
	}
}

//=============================================================
// [GameObject] ���S�t���O�̂����I�u�W�F�N�g���폜
//=============================================================
void GameObject::DestroyDeathFlag()
{
	int idx = static_cast<int>(m_gameObjects.size());
	for (int i = idx - 1; i >= 0; i--)
	{
		if (m_gameObjects[i]->m_bDeathFlag)
		{ // ���S�t���O�����Ă���Ƃ�
			delete m_gameObjects[i];
		}
	}
}

//=============================================================
// [GameObject] �R���|�[�l���g�̍폜
//=============================================================
void GameObject::Destroy(Component* component)
{
	if (component == nullptr)
		return;

	for (auto itr = m_components.begin(); itr != m_components.end(); itr++)
	{
		if (*itr == component)
		{
			// �I������
			(*itr)->Uninit();
			m_components.erase(itr);
			
			if (component != nullptr)
			{
				delete component;
				component = nullptr;
			}
			return;
		}
	}
}

//=============================================================
// [GameObject] �R���X�g���N�^
//=============================================================
GameObject::GameObject(const std::string& name, const std::string& tag)
{
	m_active = true;
	m_visible = true;
	SetName(name);
	SetTag(tag);
	transform = new Transform();
	m_bDeathFlag = false;

	// �Q�[���I�u�W�F�N�g�ɓo�^����
	m_gameObjects.push_back(this);

	// �D��x��ݒ肷��
	SetPriority(DEFAULT_PRIORITY);
}

//=============================================================
// [GameObject] �f�X�g���N�^
//=============================================================
GameObject::~GameObject()
{
	// �Q�[���I�u�W�F�N�g�����C�x���g
	for (auto itrGameObj = m_gameObjects.begin(); itrGameObj != m_gameObjects.end(); itrGameObj++)
	{
		if (*itrGameObj == this) { continue; }

		// �R���|�[�l���g�̃C�x���g�������s��
		for (auto itrComp = (*itrGameObj)->m_components.begin(); itrComp != (*itrGameObj)->m_components.end(); itrComp++)
		{
			if (*itrComp != nullptr)
			{
				(*itrComp)->OnDestroyOtherObject(this);
			}
		}
	}

	// �܂܂��R���|�[�l���g���폜����
	for (auto itrComp = m_components.begin(); itrComp != m_components.end(); itrComp++)
	{
		if (*itrComp != nullptr)
		{
			// �R���|�[�l���g�����C�x���g
			for (auto itrGameObj = m_gameObjects.begin(); itrGameObj != m_gameObjects.end(); itrGameObj++)
			{
				if (*itrGameObj == this) { continue; }
				// �R���|�[�l���g�̃C�x���g�������s��
				for (auto itrObjComp = (*itrGameObj)->m_components.begin(); itrObjComp != (*itrGameObj)->m_components.end(); itrObjComp++)
				{
					if (*itrObjComp != nullptr)
					{
						(*itrObjComp)->OnDestroyOtherComponent(*itrComp);
					}
				}
			}

			(*itrComp)->Uninit();
			delete *itrComp;
			*itrComp = nullptr;
		}
	}

	// ���̃I�u�W�F�N�g��e�Ƃ��Đݒ肵�Ă���I�u�W�F�N�g�̉���
	for (auto itr = m_gameObjects.begin(); itr != m_gameObjects.end(); itr++)
	{
		if (*itr == this) { continue; }

		if ((*itr)->transform->GetParent() == transform)
		{
			(*itr)->transform->SetParent(nullptr);		// �e��Ԃ̉���
		}
	}

	// �g�����X�t�H�[���̔j��
	if (transform)
	{
		delete transform;
		transform = nullptr;
	}

	// �f�[�^�t�B�[���h�̍폜
	CDataField::Destroy(this);

	// �R���W�������폜����
	CCollision::RemoveCollision(this);

	// �Q�[���I�u�W�F�N�g�̓o�^����������
	for (auto itr = m_gameObjects.begin(); itr != m_gameObjects.end(); itr++)
	{
		if (*itr == this)
		{
			m_gameObjects.erase(itr);
			break;
		}
	}
}

//=============================================================
// [GameObject] �D��x�̐ݒ�
//=============================================================
void GameObject::SetPriority(int nPriority)
{
	m_nPriority = nPriority;

	// �Q�[���I�u�W�F�N�g��D��x���Ƀ\�[�g����
	std::sort(m_gameObjects.begin(), m_gameObjects.end(), [](GameObject* obj1, GameObject* obj2) {return obj1->GetPriority() < obj2->GetPriority(); });
	
	// �R���|�[�l���g���\�[�g����
	Component::Sort();
}

//=============================================================
// [GameObject] �Q�[���I�u�W�F�N�g�����݂��邩
//=============================================================
bool GameObject::IsExist(GameObject* pGameObject)
{
	for (auto itr = m_gameObjects.begin(); itr != m_gameObjects.end(); itr++)
	{
		if (*itr == pGameObject)
		{	// ���݂��Ă���Ƃ�
			return true;
		}
	}
	return false;
}

//=============================================================
// [GameObject] �v���n�u�̓ǂݍ���
//=============================================================
GameObject* GameObject::LoadPrefab(const std::string& sPath, Transform transform)
{
	// json�t�@�C����ǂݍ���
	ifstream ifs(sPath.c_str());

	if (ifs.fail())
	{ // �t�@�C���̓ǂݍ��݂Ɏ��s
		return nullptr;
	}
	
	// json�`���ɕϊ�
	std::string sInputData((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	auto jPrefab = json::parse(sInputData);

	// �e�v���n�u�I�u�W�F�N�g�̍쐬
	GameObject* pPrefabObject = new GameObject();
	pPrefabObject->transform->SetPos(transform.GetPos());
	pPrefabObject->transform->SetRot(transform.GetRot());
	pPrefabObject->transform->SetScale(transform.GetScale());

	if (jPrefab.contains("prefab"))
	{ // �v���n�u���܂܂�Ă���Ƃ��i�K�{�j
		pPrefabObject->SetName(jPrefab["prefab"]["name"]);
		pPrefabObject->SetTag(jPrefab["prefab"]["tag"]);
		pPrefabObject->transform->Translate(jPrefab["prefab"]["transform"]["position"][0], jPrefab["prefab"]["transform"]["position"][1], jPrefab["prefab"]["transform"]["position"][2]);
		pPrefabObject->transform->Rotate(jPrefab["prefab"]["transform"]["rotation"][0], jPrefab["prefab"]["transform"]["rotation"][1], jPrefab["prefab"]["transform"]["rotation"][2]);
		//pPrefabObject->transform->SetScale(jPrefab["prefab"]["transform"]["scale"][0], jPrefab["prefab"]["transform"]["scale"][1], jPrefab["prefab"]["transform"]["scale"][2]);

		// �R���W�����̂Ƃ�
		if (jPrefab["prefab"].contains("collision"))
		{ // �R���W������񂪊܂܂�Ă���Ƃ�
			CCollision::Create(pPrefabObject);

			// ���W�b�h�{�f�B��
			if (jPrefab["prefab"]["rigidbody"])
			{ // ���W�b�h�{�f�B���L���̎�
				pPrefabObject->AddComponent<CRigidBody>();
			}

			// �g���K�[��
			if (jPrefab["prefab"].contains("trigger"))
			{
				CCollision::GetCollision(pPrefabObject)->IsTrigger(jPrefab["prefab"]["trigger"]);
			}

			// �R���W�������
			for (unsigned int i = 0; i < jPrefab["prefab"]["collision"].size(); i++)
			{
				// �R���W�����̃^�C�v���擾����
				string sCollisionType = jPrefab["prefab"]["collision"][i]["type"];

				// �^�C�v���Ƃɏ�������
				CCollider* pCol = nullptr;
				if (sCollisionType == "box")
				{ // �{�b�N�X�̂Ƃ�
					pCol = pPrefabObject->AddComponent<CBoxCollider>();
					CBoxCollider* pBoxCol = (CBoxCollider*)pCol;

					// �T�C�Y
					pBoxCol->SetSize({
						jPrefab["prefab"]["collision"][i]["size"][0],
						jPrefab["prefab"]["collision"][i]["size"][1],
						jPrefab["prefab"]["collision"][i]["size"][2]
						});
					pBoxCol->SetSize(pBoxCol->GetSize() /2);
				}
				else if (sCollisionType == "sphere")
				{ // ���̂Ƃ�
					pCol = pPrefabObject->AddComponent<CSphereCollider>();
					CSphereCollider* pSphereCol = (CSphereCollider*)pCol;

					// ���a
					pSphereCol->SetRadius(jPrefab["prefab"]["collision"][i]["radius"]);
				}
				else if (sCollisionType == "capsule")
				{ // �J�v�Z���̂Ƃ�
					pCol = pPrefabObject->AddComponent<CCapsuleCollider>();
					CCapsuleCollider* pCapsuleCol = (CCapsuleCollider*)pCol;

					// ���a
					pCapsuleCol->SetRadius(jPrefab["prefab"]["collision"][i]["radius"]);

					// ����
					pCapsuleCol->SetHeight(jPrefab["prefab"]["collision"][i]["height"]);
				}
				else if (sCollisionType == "cylinder")
				{ // �~���̂Ƃ�
					pCol = pPrefabObject->AddComponent<CCylinderCollider>();
					CCylinderCollider* pCylinderCol = (CCylinderCollider*)pCol;

					// ���a
					pCylinderCol->SetRadius(jPrefab["prefab"]["collision"][i]["radius"]);

					// ����
					pCylinderCol->SetHeight(jPrefab["prefab"]["collision"][i]["height"]);
				}

				// ---------------------------------------------------
				// �S�ʐݒ�
				
				// �I�t�Z�b�g
				if (jPrefab["prefab"]["collision"][i].contains("offset"))
				{
					pCol->SetOffset({
						jPrefab["prefab"]["collision"][i]["offset"][0],
						jPrefab["prefab"]["collision"][i]["offset"][1],
						jPrefab["prefab"]["collision"][i]["offset"][2]
						});
				}

				// ��]
				if (jPrefab["prefab"]["collision"][i].contains("rotation"))
				{
					pCol->SetRot({
						jPrefab["prefab"]["collision"][i]["rotation"][0],
						jPrefab["prefab"]["collision"][i]["rotation"][1],
						jPrefab["prefab"]["collision"][i]["rotation"][2]
						});
				}
			}
		}
	}
	else
	{ // �܂܂�Ă��Ȃ��ꍇ�͎��s
		pPrefabObject->Destroy();
		return nullptr;
	}

	// �I�u�W�F�N�g���̍쐬�E�ǂݍ���
	vector<GameObject*> vecObjects;		// �I�u�W�F�N�g�ێ��p
	if (jPrefab.contains("object"))
	{ // �I�u�W�F�N�g���܂܂�Ă���Ƃ�
		for (unsigned int i = 0; i < jPrefab["object"].size(); i++)
		{
			GameObject* pObject = new GameObject();

			// ���̎擾
			pObject->SetName(jPrefab["object"][to_string(i)]["name"]);
			pObject->SetTag(jPrefab["object"][to_string(i)]["tag"]);
			pObject->transform->SetPos(jPrefab["object"][to_string(i)]["transform"]["position"][0],
				jPrefab["object"][to_string(i)]["transform"]["position"][1],
				jPrefab["object"][to_string(i)]["transform"]["position"][2]);
			pObject->transform->SetRot(jPrefab["object"][to_string(i)]["transform"]["rotation"][0],
				jPrefab["object"][to_string(i)]["transform"]["rotation"][1],
				jPrefab["object"][to_string(i)]["transform"]["rotation"][2]);
			pObject->transform->SetScale(jPrefab["object"][to_string(i)]["transform"]["scale"][0],
				jPrefab["object"][to_string(i)]["transform"]["scale"][1],
				jPrefab["object"][to_string(i)]["transform"]["scale"][2]);

			if (jPrefab["object"][to_string(i)].contains("model"))
			{ // ���f����񂪊܂܂�Ă���Ƃ��i�C�Ӂj
				// �e�`��
				bool bDrawShadow = true;
				if (jPrefab["object"][to_string(i)].contains("shadow"))
				{
					bDrawShadow = jPrefab["object"][to_string(i)]["shadow"];
				}

				if (jPrefab["object"][to_string(i)]["model"] != "none")
				{
					CMesh* pMesh = pObject->AddComponent<CMesh>();
					pMesh->LoadMeshX(jPrefab["object"][to_string(i)]["model"], bDrawShadow);
				}
			}

			// ����I�u�W�F�N�g�̂Ƃ�
			if (jPrefab["object"][to_string(i)].contains("light"))
			{ // ���C�g��񂪊܂܂�Ă���Ƃ�
				CLight* pLight = pObject->AddComponent<CLight>();
				pLight->SetIntensity(jPrefab["object"][to_string(i)]["light"]["intensity"]);
				pLight->SetColor(D3DXCOLOR(
					jPrefab["object"][to_string(i)]["light"]["color"][0],
					jPrefab["object"][to_string(i)]["light"]["color"][1],
					jPrefab["object"][to_string(i)]["light"]["color"][2],
					jPrefab["object"][to_string(i)]["light"]["color"][3]));
			}

			// �R���W�����̂Ƃ�
			if (jPrefab["object"][to_string(i)].contains("collision"))
			{ // �I�u�W�F�N�g�ɃR���W������񂪊܂܂�Ă��邩
				CCollision::Create(pObject);
				auto jCol = jPrefab["object"][to_string(i)]["collision"]; // �ȗ�

				// �g���K�[��
				if (jPrefab["object"][to_string(i)].contains("trigger"))
				{
					CCollision::GetCollision(pObject)->IsTrigger(jPrefab["object"][to_string(i)]["trigger"]);
				}

				// ���C���
				if (jPrefab["object"][to_string(i)].contains("friction"))
				{
					CCollision::GetCollision(pObject)->SetFriction(jPrefab["object"][to_string(i)]["friction"]);
				}

				// �R���W�������
				for (unsigned int nCntCol = 0; nCntCol < jCol.size(); nCntCol++)
				{
					// �R���W�����̃^�C�v���擾����
					string sCollisionType = jPrefab["object"][to_string(i)]["collision"][nCntCol]["type"];

					// �^�C�v���Ƃɏ�������
					CCollider* pCol = nullptr;
					if (sCollisionType == "box")
					{ // �{�b�N�X�̂Ƃ�
						pCol = pObject->AddComponent<CBoxCollider>();
						CBoxCollider* pBoxCol = (CBoxCollider*)pCol;

						// �T�C�Y
						pBoxCol->SetSize({
							jCol[nCntCol]["size"][0],
							jCol[nCntCol]["size"][1],
							jCol[nCntCol]["size"][2]
							});
						pBoxCol->SetSize(pBoxCol->GetSize() / 2);
					}
					else if (sCollisionType == "sphere")
					{ // ���̂Ƃ�
						pCol = pObject->AddComponent<CSphereCollider>();
						CSphereCollider* pSphereCol = (CSphereCollider*)pCol;

						// ���a
						pSphereCol->SetRadius(jCol[nCntCol]["radius"]);
					}
					else if (sCollisionType == "capsule")
					{ // �J�v�Z���̂Ƃ�
						pCol = pObject->AddComponent<CCapsuleCollider>();
						CCapsuleCollider* pCapsuleCol = (CCapsuleCollider*)pCol;

						// ���a
						pCapsuleCol->SetRadius(jCol[nCntCol]["radius"]);

						// ����
						pCapsuleCol->SetHeight(jCol[nCntCol]["height"]);
					}
					else if (sCollisionType == "cylinder")
					{ // �~���̂Ƃ�
						pCol = pObject->AddComponent<CCylinderCollider>();
						CCylinderCollider* pCylinderCol = (CCylinderCollider*)pCol;

						// ���a
						pCylinderCol->SetRadius(jCol[nCntCol]["radius"]);

						// ����
						pCylinderCol->SetHeight(jCol[nCntCol]["height"]);
					}

					// ---------------------------------------------------
					// �S�ʐݒ�

					// �I�t�Z�b�g
					if (jCol[nCntCol].contains("offset"))
					{
						pCol->SetOffset({
							jCol[nCntCol]["offset"][0],
							jCol[nCntCol]["offset"][1],
							jCol[nCntCol]["offset"][2]
							});
					}

					// ��]
					if (jCol[nCntCol].contains("rotation"))
					{
						pCol->SetRot({
							jCol[nCntCol]["rotation"][0],
							jCol[nCntCol]["rotation"][1],
							jCol[nCntCol]["rotation"][2]
							});
					}
				}
			}

			// �I�u�W�F�N�g����ێ�����
			vecObjects.push_back(pObject);
		}
	}

	// �e�q�֌W�̓ǂݍ���
	if (jPrefab.contains("parent"))
	{ // �e�q��񂪊܂܂�Ă���Ƃ�
		for (unsigned int i = 0; i < jPrefab["parent"].size(); i++)
		{
			// �e�̐ݒ�
			if (0 <= jPrefab["parent"][to_string(i)] &&
				jPrefab["parent"][to_string(i)] < vecObjects.size())
			{ // �w��̃I�u�W�F�N�g�Őݒ肳��Ă���Ƃ�
				vecObjects[i]->SetParent(vecObjects[jPrefab["parent"][to_string(i)]]);
			}
			else
			{ // �e�v���n�u�̂Ƃ�
				vecObjects[i]->SetParent(pPrefabObject);
			}
		}
	}

	// �R���W���������X�V����
	for (unsigned int i = 0; i < vecObjects.size(); i++)
	{
		if (CCollision::GetCollision(vecObjects[i]) != nullptr)
		{
			CCollision::GetCollision(vecObjects[i])->UpdateCollision();
		}
	}

	// ���ʂƖ��C�̐ݒ�
	if (jPrefab["prefab"].contains("collision"))
	{// �R���W������񂪊܂܂�Ă���Ƃ�
		// ����
		if (jPrefab["prefab"].contains("mass"))
		{
			CCollision::GetCollision(pPrefabObject)->SetMass(jPrefab["prefab"]["mass"]);
		}

		// ���C
		if (jPrefab["prefab"].contains("friction"))
		{
			CCollision::GetCollision(pPrefabObject)->SetFriction(jPrefab["prefab"]["friction"]);
		}
	}

	// ���[�V�������̓ǂݍ���
	if (jPrefab.contains("motion"))
	{ // ���[�V������񂪊܂܂�Ă���Ƃ�
		// �R���|�[�l���g��ǉ�
		CMotionManager* pMotionManager = pPrefabObject->AddComponent<CMotionManager>((int)vecObjects.size());

		// �p�[�c�ɃA�^�b�`����
		for (unsigned int i = 0; i < vecObjects.size(); i++)
		{
			pMotionManager->SetParts(i, vecObjects[i]);
			pMotionManager->SetOffset(i, *vecObjects[i]->transform);
		}

		for (auto motion = jPrefab["motion"].items().begin(); motion != jPrefab["motion"].items().end(); motion++)
		{
			// ���[�V�����R���e���c�̍쐬
			string sContentName = motion.key();					// ���[�V���������擾
			CMotionContents* pContent = pMotionManager->AddContents(sContentName);		// �R���e���c���쐬

			// �p�[�c���ƂɃL�[�̒ǉ�
			for (auto motionParts = jPrefab["motion"][sContentName].items().begin(); motionParts != jPrefab["motion"][sContentName].items().end(); motionParts++)
			{
				if (motionParts.key() == "loop")
				{ // �J��Ԃ��ݒ�
					pContent->SetLoop(jPrefab["motion"][sContentName]["loop"]);
				}
				else if (motionParts.key() == "max_frame")
				{ // �ő�t���[���ݒ�
					pContent->SetMaxFrame(jPrefab["motion"][sContentName]["max_frame"]);
				}
				else
				{ // �L�[�̒ǉ�
					int nPartsID = atoi(motionParts.key().c_str());		// �p�[�cID�̎擾

					for (auto motionKey = jPrefab["motion"][sContentName][to_string(nPartsID)]["keys"].items().begin(); motionKey != jPrefab["motion"][sContentName][to_string(nPartsID)]["keys"].items().end(); motionKey++)
					{
						int nKey = atoi(motionKey.key().c_str());			// �L�[�̎擾

						// �L�[�̒ǉ�
						pContent->AddKey(nPartsID, nKey,
							{ 
							jPrefab["motion"][sContentName][to_string(nPartsID)]["keys"][to_string(nKey)]["position"][0],
							jPrefab["motion"][sContentName][to_string(nPartsID)]["keys"][to_string(nKey)]["position"][1],
							jPrefab["motion"][sContentName][to_string(nPartsID)]["keys"][to_string(nKey)]["position"][2] 
							},
							{
							jPrefab["motion"][sContentName][to_string(nPartsID)]["keys"][to_string(nKey)]["rotation"][0],
							jPrefab["motion"][sContentName][to_string(nPartsID)]["keys"][to_string(nKey)]["rotation"][1],
							jPrefab["motion"][sContentName][to_string(nPartsID)]["keys"][to_string(nKey)]["rotation"][2]
							},
							{
							jPrefab["motion"][sContentName][to_string(nPartsID)]["keys"][to_string(nKey)]["scale"][0],
							jPrefab["motion"][sContentName][to_string(nPartsID)]["keys"][to_string(nKey)]["scale"][1],
							jPrefab["motion"][sContentName][to_string(nPartsID)]["keys"][to_string(nKey)]["scale"][2]
							}
						);
					}
				}
			}
		}

		// �������[�V����
		if (jPrefab.contains("default-motion"))
		{ // �ݒ肳��Ă���Ƃ�
			pMotionManager->Play(jPrefab["default-motion"]);
		}
	}

	// �f�[�^�t�B�[���h�̓ǂݍ���
	if (jPrefab.contains("data-field"))
	{ // �f�[�^�t�B�[���h��񂪊܂܂�Ă���Ƃ�
		for (int i = 0; i < (int)jPrefab["data-field"].size(); i++)
		{
			// �f�[�^�t�B�[���h�̎擾
			CDataField* pDataField = CDataField::GetDataField(pPrefabObject);

			// ���O�ƌ^
			string sNameDF = jPrefab["data-field"][i]["name"];
			string sTypeDF = jPrefab["data-field"][i]["type"];

			// �e�^�ɍ���������
			if (sTypeDF == "int")
			{
				CDF_Int* pIntDF = new CDF_Int();
				pIntDF->SetName(sNameDF);
				pIntDF->SetValue(jPrefab["data-field"][i]["value"]);
				pDataField->AddData(pIntDF);
			}
			if (sTypeDF == "float")
			{
				CDF_Float* pFloatDF = new CDF_Float();
				pFloatDF->SetName(sNameDF);
				pFloatDF->SetValue(jPrefab["data-field"][i]["value"]);
				pDataField->AddData(pFloatDF);
			}
			if (sTypeDF == "bool")
			{
				CDF_Bool* pBoolDF = new CDF_Bool();
				pBoolDF->SetName(sNameDF);
				pBoolDF->SetValue(jPrefab["data-field"][i]["value"]);
				pDataField->AddData(pBoolDF);
			}
			if (sTypeDF == "string")
			{
				CDF_String* pStringDF = new CDF_String();
				pStringDF->SetName(sNameDF);
				pStringDF->SetValue(jPrefab["data-field"][i]["value"]);
				pDataField->AddData(pStringDF);
			}
			if (sTypeDF == "vector3")
			{
				CDF_Vector3* pVector3DF = new CDF_Vector3();
				pVector3DF->SetName(sNameDF);
				pVector3DF->SetValue({ jPrefab["data-field"][i]["value"][0], jPrefab["data-field"][i]["value"][1], jPrefab["data-field"][i]["value"][2] });
				pDataField->AddData(pVector3DF);
			}
			if (sTypeDF == "vector2")
			{
				CDF_Vector2* pVector2DF = new CDF_Vector2();
				pVector2DF->SetName(sNameDF);
				pVector2DF->SetValue({ jPrefab["data-field"][i]["value"][0], jPrefab["data-field"][i]["value"][1]});
				pDataField->AddData(pVector2DF);
			}
		}
	}

	// �t�@�C�������
	ifs.close();

	return pPrefabObject;
}