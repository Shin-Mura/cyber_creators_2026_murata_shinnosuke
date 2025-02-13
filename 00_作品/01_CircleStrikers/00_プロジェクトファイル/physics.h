//========================================================================================================
//
//�����蔻��̏���[physics.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include "main.h"

//�����蔻��N���X
class Collider;
class BoxCollider;
class Physics
{
public:
	typedef enum
	{
		IS_TOP = 0,
		IS_BOTTOM,
		IS_RIGHT,
		IS_LEFT,
		IS_FRONT,
		IS_BACK,
		IS_IN,
	}CONTACT;   //�Փˈʒu

	//�R���X�g���N�^
	Physics()
	{
	}

	//�f�X�g���N�^
	~Physics()
	{
	}

	void Calc(Collider* pCollider);   //���Z����

private:
	void BoxToBox(BoxCollider* pBoxCollider, BoxCollider* pBoxColliderTarget);
};

#endif // !_PHYSICS_H_
