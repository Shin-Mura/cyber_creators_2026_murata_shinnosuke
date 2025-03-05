//========================================================================================================
//
//ゲームマネージャーの処理[game_manager.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include "behavior.h"

//前方宣言
class Player;   //プレイヤー
//ゲームマネージャー
class GameManager : public Behavior   //(親)挙動
{
public:
	//コンストラクタ
	GameManager(Object* pObject) : Behavior(pObject)
	{
		//メンバ変数を初期化する
		this->m_isStart = false;   //スタートフラグ
		this->m_vPlayer.clear();   //プレイヤーのコンテナ
	}

	//デストラクタ
	~GameManager() override
	{
	}

	void Init() override;   //初期化
	void Update() override;   //更新
	void SetPlayer(Player* pPlayer) { this->m_vPlayer.push_back(pPlayer); };

private:
	std::vector<Player*> m_vPlayer;   //プレイヤー
	bool m_isStart;   //スタートフラグ
};

#endif // !_GAME_MANAGER_H_
