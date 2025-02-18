//========================================================================================================
//
//プレイヤー処理[player.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "behavior.h"

//プレイヤークラス
class Player : public Behavior   //(親)挙動
{
public:
	const static float MOVE_SPEED;   //移動速度

	//コンストラクタ
	Player(Object* pObject, int nId) : Behavior(pObject)
	{
		//メンバ変数を初期化する
		this->m_nId = nId;
		this->m_isHit = false;
	}

	//デストラクタ
	~Player() override
	{
	}

	void Init() override;   //初期化処理
	void Update() override;   //更新処理
	void Hit();   //ヒット処理

private:
	void Control();   //コントロール処理
	void LimitMove();   //行動制限

	int m_nId;   //番号
	bool m_isHit;   //ヒットフラグ
};

#endif // !_PLAYER_H_
