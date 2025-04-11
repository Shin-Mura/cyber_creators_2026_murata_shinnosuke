//=============================================================
//
// �f�[�^�t�B�[���h [data_field.h]
// Author: Ito Kotaro
//
//=============================================================
#ifndef _DATA_FIELD_H_
#define _DATA_FIELD_H_

#include "gameobject.h"


// �f�[�^�t�B�[���h�̃f�[�^
class CDF
{
public:
	enum TYPE
	{
		INT,
		FLOAT,
		BOOL,
		STRING,
		VECTOR3,
		VECTOR2,
	};

	CDF(const TYPE& type) { m_type = type; }								// �R���X�g���N�^�i�^�ݒ�j
	TYPE GetType() { return m_type; }											// ��ނ̎擾
	void SetName(const std::string name) { m_name = name; }	// ���O�̐ݒ�
	std::string GetName() { return m_name; }								// ���O�̎擾
private:
	std::string m_name;	// ���O
	TYPE m_type;			// ���
};

// Int�^�f�[�^
class CDF_Int : public CDF
{
public:
	CDF_Int() : CDF(TYPE::INT) {}
	void SetValue(const int& data) { m_nData = data; }
	int GetValue() { return m_nData; }
private:
	int m_nData;
};

// Float�^�f�[�^
class CDF_Float : public CDF
{
public:
	CDF_Float() : CDF(TYPE::FLOAT) {}
	void SetValue(const float& data) { m_fData = data; }
	float GetValue() { return m_fData; }
private:
	float m_fData;
};

// Bool�^�f�[�^
class CDF_Bool : public CDF
{
public:
	CDF_Bool() : CDF(TYPE::BOOL) {}
	void SetValue(const bool& data) { m_bData = data; }
	bool GetValue() { return m_bData; }
private:
	bool m_bData;
};

// String�^�f�[�^
class CDF_String : public CDF
{
public:
	CDF_String() : CDF(TYPE::STRING) {}
	void SetValue(const std::string& data) { m_sData = data; }
	std::string GetValue() { return m_sData; }
private:
	std::string m_sData;
};

// Vector3�^�f�[�^
class CDF_Vector3 : public CDF
{
public:
	CDF_Vector3() : CDF(TYPE::VECTOR3) {}
	void SetValue(const D3DXVECTOR3& data) { m_vec3Data = data; }
	D3DXVECTOR3 GetValue() { return m_vec3Data; }
private:
	D3DXVECTOR3 m_vec3Data;
};

// Vector2�^�f�[�^
class CDF_Vector2 : public CDF
{
public:
	CDF_Vector2() : CDF(TYPE::VECTOR2) {}
	void SetValue(const D3DXVECTOR2& data) { m_vec2Data = data; }
	D3DXVECTOR2 GetValue() { return m_vec2Data; }
private:
	D3DXVECTOR2 m_vec2Data;
};

// �f�[�^�t�B�[���h
class CDataField
{
public:
	~CDataField();

	// �e�^�̃f�[�^�擾
	int GetInt(const std::string& name);
	float GetFloat(const std::string& name);
	bool GetBool(const std::string& name);
	std::string GetString(const std::string& name);
	D3DXVECTOR3 GetVector3(const std::string& name);
	D3DXVECTOR2 GetVector2(const std::string& name);

	// ����
	void AddData(CDF* pData);
	CDF* GetData(const std::string& name);

	static void Destroy(GameObject* gameObject);
	static bool IsExist(GameObject* gameObject);
	static CDataField* GetDataField(GameObject* gameObject);
private:
	CDataField(){}
	GameObject* m_pAttachObject;
	std::vector<CDF*> m_pDatas;
	static std::vector<CDataField*> m_pDataFields;
};

#endif // !_DATA_FIELD_H_
