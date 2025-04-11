//=============================================================
//
// �f�[�^�t�B�[���h [data_field.cpp]
// Author: Ito Kotaro
//
//=============================================================
#include "data_field.h"

// �ÓI�����o�ϐ��̏�����
std::vector<CDataField*> CDataField::m_pDataFields;

//=============================================================
// [CDataField] �f�X�g���N�^Int�f�[�^�̎擾
//=============================================================
CDataField::~CDataField()
{
	if (m_pDatas.size() > 0)
	{ // �f�[�^�����݂���Ƃ�
		// �f�[�^���폜����
		for (int i = 0; i < (int)m_pDatas.size(); i++)
		{
			delete m_pDatas[i];
			m_pDatas[i] = nullptr;
		}
	}

	// ��ɂ���
	m_pDatas.clear();

	// �f�[�^�t�B�[���h���X�g����폜����
	for (int i = 0; i < (int)m_pDataFields.size(); i++)
	{
		if (m_pDataFields[i] == this)
		{ // ��v����Ƃ�
			m_pDataFields.erase(m_pDataFields.begin() + i);
			return;
		}
	}
}

//=============================================================
// [CDataField] Int�f�[�^�̎擾
//=============================================================
int CDataField::GetInt(const std::string& name)
{
	for (int i = 0; i < (int)m_pDatas.size(); i++)
	{
		if (m_pDatas[i]->GetName() == name &&
			m_pDatas[i]->GetType() == CDF::TYPE::INT)
		{
			CDF_Int* data = (CDF_Int*)m_pDatas[i];
			return  data->GetValue();
		}
	}

	return 0;
}

//=============================================================
// [CDataField] Float�f�[�^�̎擾
//=============================================================
float CDataField::GetFloat(const std::string& name)
{
	for (int i = 0; i < (int)m_pDatas.size(); i++)
	{
		if (m_pDatas[i]->GetName() == name &&
			m_pDatas[i]->GetType() == CDF::TYPE::FLOAT)
		{
			CDF_Float* data = (CDF_Float*)m_pDatas[i];
			return  data->GetValue();
		}
	}
	return 0.0f;
}

//=============================================================
// [CDataField] Bool�f�[�^�̎擾
//=============================================================
bool CDataField::GetBool(const std::string& name)
{
	for (int i = 0; i < (int)m_pDatas.size(); i++)
	{
		if (m_pDatas[i]->GetName() == name &&
			m_pDatas[i]->GetType() == CDF::TYPE::BOOL)
		{
			CDF_Bool* data = (CDF_Bool*)m_pDatas[i];
			return  data->GetValue();
		}
	}
	return false;
}

//=============================================================
// [CDataField] String�f�[�^�̎擾
//=============================================================
std::string CDataField::GetString(const std::string& name)
{
	for (int i = 0; i < (int)m_pDatas.size(); i++)
	{
		if (m_pDatas[i]->GetName() == name &&
			m_pDatas[i]->GetType() == CDF::TYPE::STRING)
		{
			CDF_String* data = (CDF_String*)m_pDatas[i];
			return  data->GetValue();
		}
	}
	return "";
}

//=============================================================
// [CDataField] Vector3�f�[�^�̎擾
//=============================================================
D3DXVECTOR3 CDataField::GetVector3(const std::string& name)
{
	for (int i = 0; i < (int)m_pDatas.size(); i++)
	{
		if (m_pDatas[i]->GetName() == name &&
			m_pDatas[i]->GetType() == CDF::TYPE::VECTOR3)
		{
			CDF_Vector3* data = (CDF_Vector3*)m_pDatas[i];
			return  data->GetValue();
		}
	}
	return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================
// [CDataField] Vector2�f�[�^�̎擾
//=============================================================
D3DXVECTOR2 CDataField::GetVector2(const std::string& name)
{
	for (int i = 0; i < (int)m_pDatas.size(); i++)
	{
		if (m_pDatas[i]->GetName() == name &&
			m_pDatas[i]->GetType() == CDF::TYPE::VECTOR2)
		{
			CDF_Vector2* data = (CDF_Vector2*)m_pDatas[i];
			return  data->GetValue();
		}
	}
	return D3DXVECTOR2(0.0f, 0.0f);
}

//=============================================================
// [CDataField] �f�[�^�̒ǉ�
//=============================================================
void CDataField::AddData(CDF* pData)
{
	// ���O���d�����Ă��Ȃ���
	for (int i = 0; i < (int)m_pDatas.size(); i++)
	{
		if (pData->GetName() == m_pDatas[i]->GetName())
		{ // �d�����Ă���ꍇ
			return;
		}
	}

	// �f�[�^��ǉ�����
	m_pDatas.push_back(pData);
}

//=============================================================
// [CDataField] �f�[�^�̎擾
//=============================================================
CDF* CDataField::GetData(const std::string& name)
{
	for (int i = 0; i < (int)m_pDatas.size(); i++)
	{
		if (name == m_pDatas[i]->GetName())
		{ // ���������ꍇ
			return m_pDatas[i];
		}
	}
	return nullptr;
}

//=============================================================
// [CDataField] �f�[�^�t�B�[���h�����݂��邩
//=============================================================
bool CDataField::IsExist(GameObject* gameObject)
{
	for (int i = 0; i < (int)m_pDataFields.size(); i++)
	{
		if (m_pDataFields[i]->m_pAttachObject == gameObject)
		{ // ���݂���Ƃ�
			return true;
		}
	}
	return false;
}

//=============================================================
// [CDataField] �f�[�^�t�B�[���h�̎擾
//=============================================================
CDataField* CDataField::GetDataField(GameObject* gameObject)
{
	// �T��
	for (int i = 0; i < (int)m_pDataFields.size(); i++)
	{
		if (m_pDataFields[i]->m_pAttachObject == gameObject)
		{
			return m_pDataFields[i];
		}
	}

	// ���݂��Ȃ��ꍇ�A�쐬����
	CDataField* pDataField = new CDataField();
	pDataField->m_pAttachObject = gameObject;
	m_pDataFields.push_back(pDataField);

	return pDataField;
}

//=============================================================
// [CDataField] �f�[�^��j������
//=============================================================
void CDataField::Destroy(GameObject* gameObject)
{
	if (IsExist(gameObject))
	{ // ���݂���Ƃ�
		delete GetDataField(gameObject);
	}
}
