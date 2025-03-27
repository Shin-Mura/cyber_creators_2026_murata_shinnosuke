//========================================================================================================
//
//�����蔻��̏���[physics.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include "main.h"

//�O���錾
class Collider;
class BoxCollider;
class SphereCollider;
//�����蔻��N���X
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

	void Calc();   //���Z����

	static void Create();   //��������
	static void Destroy() { delete Physics::m_pInstance; Physics::m_pInstance = nullptr; };   //�j��
	static Physics* Get() { return Physics::m_pInstance; };   //�擾

private:
	//�R���X�g���N�^
	Physics()
	{
	}

	//�f�X�g���N�^
	~Physics()
	{
	}

	bool BoxToBox(BoxCollider* pBoxCollider, BoxCollider* pBoxColliderTarget);
	//void SphereToSphere(SphereCollider* pSphereCollider, SphereCollider* pSphereColliderTarget);

	static Physics* m_pInstance;   //�C���X�^���X
};

#endif // !_PHYSICS_H_
