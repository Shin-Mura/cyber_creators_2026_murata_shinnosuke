//========================================================================================================
//
//ゲームシーン処理[game.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "scene.h"
#include "physics.h"
#include "pause.h"

//ゲームシーンクラス
class Game : public Scene   //(親)シーンクラス
{
public:
	//コンストラクタ
	Game()
	{
		//メンバ変数を初期化する
		this->m_pPhysics = nullptr;
		this->m_pPause = nullptr;   //ポーズ
	}

	//デストラクタ
	virtual ~Game()
	{
	}

	void Init() override;   //初期化処理
	void Uninit() override;   //終了処理
	void Update() override;   //更新処理
	void Draw() override;   //描画処理

	Pause* GetPause() { return this->m_pPause; };   //ポーズの取得処理
	Physics* GetPhysics() { return this->m_pPhysics; };   //当たり判定の取得

private:
	Pause* m_pPause;   //ポーズ
	Physics* m_pPhysics;   //物理
};

#endif // !_GAME_H_
