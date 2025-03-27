//==========================================================================================================
//
//�����̏���[behavior.h]
// Author MurataShinnosuke
//
//==========================================================================================================
#ifndef _BEHAVIOR_H_
#define _BEHAVIOR_H_

#include "component.h"
#include "object.h"
#include "physics.h"

//����
class Behavior : public Component   //(�e)�R���|�[�l���g
{
public:
	//�R���X�g���N�^
	Behavior(Object* pObject) : Component(pObject)
	{
	}

	//�f�X�g���N�^
	virtual ~Behavior() override
	{
	}

	virtual void Init() override = 0;
	virtual void Update() override = 0;
	virtual void Collision(Object* pObject, Physics::CONTACT contact) {};   //�Փˏ���
	virtual void EndMotion() {};   //���[�V�����̏I������
};

#endif // !_BEHAVIOR_H_
