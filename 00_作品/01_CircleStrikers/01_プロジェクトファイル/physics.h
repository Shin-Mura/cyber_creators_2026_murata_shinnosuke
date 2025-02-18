//========================================================================================================
//
//当たり判定の処理[physics.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include "main.h"

//当たり判定クラス
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
	}CONTACT;   //衝突位置

	//コンストラクタ
	Physics()
	{
	}

	//デストラクタ
	~Physics()
	{
	}

	void Calc(Collider* pCollider);   //演算処理

private:
	void BoxToBox(BoxCollider* pBoxCollider, BoxCollider* pBoxColliderTarget);
};

#endif // !_PHYSICS_H_
