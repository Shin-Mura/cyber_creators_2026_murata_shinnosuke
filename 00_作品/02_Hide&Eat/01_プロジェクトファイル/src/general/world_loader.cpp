//=============================================================
//
// ���[���h���[�_�[ [world_loader.cpp]
// Author: Ito Kotaro
//
//=============================================================
#include "world_loader.h"
#include <fstream>
#include "component/3d/mesh.h"
#include "component/3d/light.h"
#include "component/3d/collision.h"

//=============================================================
// [WorldLoader] ���[�h
//=============================================================
void WorldLoader::Load(const std::string& path)
{
	// json�t�@�C����ǂݍ���
	std::ifstream ifs(path.c_str());

	// json�`���ɕϊ�
	std::string sInputData((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	auto jWorld = json::parse(sInputData);

	// X�I�u�W�F�N�g��ǂݍ���
	for (auto jXObj = jWorld["x-objects"].items().begin(); jXObj != jWorld["x-objects"].items().end(); jXObj++)
	{
		for (unsigned int i = 0; i < jXObj.value().size(); i++)
		{
			// �I�u�W�F�N�g���쐬����
			GameObject* pXObject = new GameObject;

			// ���b�V����ǂݍ���
			CMesh* pMesh = pXObject->AddComponent<CMesh>();
			if (FAILED(pMesh->LoadMeshX(jXObj.key())))
			{ // ���s�����Ƃ�
				pMesh->enabled = false;
				pXObject->Destroy();
				break;
			}

			// ���O�ƃ^�O
			pXObject->SetName(jXObj.value()[i]["name"]);
			pXObject->SetTag(jXObj.value()[i]["tag"]);

			// �g�����X�t�H�[�����
			pXObject->transform->SetPos({
				jXObj.value()[i]["transform"]["position"][0],  jXObj.value()[i]["transform"]["position"][1],  jXObj.value()[i]["transform"]["position"][2]
				});
			pXObject->transform->SetRot({
				jXObj.value()[i]["transform"]["rotation"][0],  jXObj.value()[i]["transform"]["rotation"][1],  jXObj.value()[i]["transform"]["rotation"][2]
				});
			pXObject->transform->SetScale({
				jXObj.value()[i]["transform"]["scale"][0],  jXObj.value()[i]["transform"]["scale"][1],  jXObj.value()[i]["transform"]["scale"][2]
				});

			// �J�X�^���I�u�W�F�N�g
			CustomObject(pXObject);

			// �I�u�W�F�N�g�Ǘ��ɒǉ�����
			m_pWorldObjects.push_back(pXObject);
		}
	}

	// �v���n�u�I�u�W�F�N�g��ǂݍ���
	for (auto jPrefabObj = jWorld["prefab-objects"].items().begin(); jPrefabObj != jWorld["prefab-objects"].items().end(); jPrefabObj++)
	{
		for (unsigned int i = 0; i < jPrefabObj.value().size(); i++)
		{
			// �g�����X�t�H�[�����
			Transform prefTrans = Transform();
			prefTrans.SetPos({
				jPrefabObj.value()[i]["transform"]["position"][0],  jPrefabObj.value()[i]["transform"]["position"][1],  jPrefabObj.value()[i]["transform"]["position"][2]
				});
			prefTrans.SetRot({
				jPrefabObj.value()[i]["transform"]["rotation"][0],  jPrefabObj.value()[i]["transform"]["rotation"][1],  jPrefabObj.value()[i]["transform"]["rotation"][2]
				});
			prefTrans.SetScale({
				jPrefabObj.value()[i]["transform"]["scale"][0],  jPrefabObj.value()[i]["transform"]["scale"][1],  jPrefabObj.value()[i]["transform"]["scale"][2]
				});

			// �I�u�W�F�N�g���쐬����
			GameObject* pPrefabObject = GameObject::LoadPrefab(jPrefabObj.key(), prefTrans);

			if (pPrefabObject == nullptr)
			{ // ���s�����Ƃ�
				break;
			}

			// ���O�ƃ^�O
			pPrefabObject->SetName(jPrefabObj.value()[i]["name"]);
			pPrefabObject->SetTag(jPrefabObj.value()[i]["tag"]);

			// �f�[�^�t�B�[���h���̏㏑��
			for (int n = 0; n < (int)jPrefabObj.value()[i]["data-field"].size(); n++)
			{
				std::string sNameDF = jPrefabObj.value()[i]["data-field"][n]["name"];
				std::string sTypeDF = jPrefabObj.value()[i]["data-field"][n]["type"];

				// ���̎擾
				CDataField* pDataField = CDataField::GetDataField(pPrefabObject);
				CDF* pDF = pDataField->GetData(sNameDF);

				if (pDF != nullptr)
				{ // �f�[�^�����݂���Ƃ�
					CDF::TYPE dfType = pDF->GetType();
					if (dfType == CDF::INT)
					{
						CDF_Int* pIntDF = (CDF_Int*)pDF;
						pIntDF->SetValue(jPrefabObj.value()[i]["data-field"][n]["value"]);
					}
					else if (dfType == CDF::FLOAT)
					{
						CDF_Float* pFloatDF = (CDF_Float*)pDF;
						pFloatDF->SetValue(jPrefabObj.value()[i]["data-field"][n]["value"]);
					}
					else if (dfType == CDF::BOOL)
					{
						CDF_Bool* pBoolDF = (CDF_Bool*)pDF;
						pBoolDF->SetValue(jPrefabObj.value()[i]["data-field"][n]["value"]);
					}
					else if (dfType == CDF::STRING)
					{
						CDF_String* pStringDF = (CDF_String*)pDF;
						pStringDF->SetValue(jPrefabObj.value()[i]["data-field"][n]["value"]);
					}
					else if (dfType == CDF::VECTOR3)
					{
						CDF_Vector3* pVector3DF = (CDF_Vector3*)pDF;
						pVector3DF->SetValue({ jPrefabObj.value()[i]["data-field"][n]["value"][0], jPrefabObj.value()[i]["data-field"][n]["value"][1], jPrefabObj.value()[i]["data-field"][n]["value"][2] });
					}
					else if (dfType == CDF::VECTOR2)
					{
						CDF_Vector2* pVector2DF = (CDF_Vector2*)pDF;
						pVector2DF->SetValue({ jPrefabObj.value()[i]["data-field"][n]["value"][0], jPrefabObj.value()[i]["data-field"][n]["value"][1] });
					}
				}
			}

			// �J�X�^���I�u�W�F�N�g
			CustomObject(pPrefabObject);

			// �I�u�W�F�N�g�Ǘ��ɒǉ�����
			m_pWorldObjects.push_back(pPrefabObject);
		}
	}

	// ���C�g�I�u�W�F�N�g��ǂݍ���
	for (auto jLightObj = jWorld["light-objects"].items().begin(); jLightObj != jWorld["light-objects"].items().end(); jLightObj++)
	{
		// �I�u�W�F�N�g���쐬����
		GameObject* pLightObject = new GameObject;

		// ���C�g��ݒ肷��
		CLight* pLight = pLightObject->AddComponent<CLight>();

		// ���O�ƃ^�O
		pLightObject->SetName(jLightObj.value()["name"]);
		pLightObject->SetTag(jLightObj.value()["tag"]);

		// ���C�g�̐ݒ�
		pLight->SetIntensity(jLightObj.value()["intensity"]);		// ����
		pLight->SetColor(D3DXCOLOR(										// �F
			jLightObj.value()["color"][0], jLightObj.value()["color"][1], jLightObj.value()["color"][2], jLightObj.value()["color"][3]
		));

		// �g�����X�t�H�[�����
		pLightObject->transform->SetPos({
			jLightObj.value()["transform"]["position"][0],  jLightObj.value()["transform"]["position"][1],  jLightObj.value()["transform"]["position"][2]
			});
		pLightObject->transform->SetRot({
			jLightObj.value()["transform"]["rotation"][0],  jLightObj.value()["transform"]["rotation"][1],  jLightObj.value()["transform"]["rotation"][2]
			});
		pLightObject->transform->SetScale({
			jLightObj.value()["transform"]["scale"][0],  jLightObj.value()["transform"]["scale"][1],  jLightObj.value()["transform"]["scale"][2]
			});

		// �J�X�^���I�u�W�F�N�g
		CustomObject(pLightObject);

		// �I�u�W�F�N�g�Ǘ��ɒǉ�����
		m_pWorldObjects.push_back(pLightObject);
	}

	// �t�@�C�������
	ifs.close();
}