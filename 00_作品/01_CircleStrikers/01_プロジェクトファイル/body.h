//========================================================================================================
//
//体の処理[body.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _TRAJECTORY_H_
#define _TRAJECTORY_H_

#include "behavior.h"

//軌跡クラス
class Body : public Behavior   //(親)挙動
{
public:
	//コンストラクタ
	Body(Object* pObject, Object* pPlayer) : Behavior(pObject)
	{
		//メンバ変数を初期化する
		this->m_pPlayer = pPlayer;
		this->m_nLife = 30;
	}

	//デストラクタ
	~Body() override
	{
	}

	void Init() override;   //初期化処理
	void Update() override;   //更新処理
	void Collision(Object* pObject, Physics::CONTACT contact) override;

private:
	Object* m_pPlayer;   //プレイヤー
	int m_nLife;   //寿命
};

#endif // !_TRAJECTORY_H_
