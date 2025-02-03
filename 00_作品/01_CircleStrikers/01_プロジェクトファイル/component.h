//========================================================================================================
//
//�R���|�[�l���g�̏���[component.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "main.h"

//�R���|�[�l���g
class Object;
class Component
{
public:
	//�R���X�g���N�^
	Component(Object* pObject)
	{
		//�����o�ϐ�������������
		this->m_pObject = pObject;   //�I�u�W�F�N�g
	}

	//�f�X�g���N�^
	virtual ~Component()
	{
	}
	
	virtual void Init() {};   //����������
	virtual void Uninit() {};   //�I������
	virtual void Update() {};   //�X�V����
	virtual void Draw() {};   //�`�揈��

	Object* GetObj() { return this->m_pObject; };   //�I�u�W�F�N�g�̎擾

private:
	Object* m_pObject;
};

#endif // !_COMPONENT_H_
