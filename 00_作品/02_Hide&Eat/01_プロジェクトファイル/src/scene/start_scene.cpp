//=============================================================
//
// スタートシーン [start_scene.cpp]
// Author: Ito Kotaro
// 
// アプリケーション開始後、最初に読み込まれるシーンです
// シーンの登録を行うことをお勧めします
//
//=============================================================
#include "start_scene.h"
#include "manager.h"

// シーンのインクルード
#include "title.h"
#include "game.h"
#include "result.h"
#include "ranking.h"

//=============================================================
// [CStartScene] 初期化
//=============================================================
void CStartScene::Init()
{
	// シーンマネージャーの取得
	CSceneManager* pSceneManager = CSceneManager::GetInstance();

	// シーンの登録
	pSceneManager->RegistScene<CTitleScene>("title");
	pSceneManager->RegistScene<CGameScene>("game");
	pSceneManager->RegistScene<CResultScene>("result");
	pSceneManager->RegistScene<CRankingScene>("ranking");

	// シーンの再生
	pSceneManager->SetScene("title");
}

//=============================================================
// [CStartScene] 終了
//=============================================================
void CStartScene::Uninit()
{
}

//=============================================================
// [CStartScene] 更新
//=============================================================
void CStartScene::Update()
{
}

//=============================================================
// [CStartScene] 描画
//=============================================================
void CStartScene::Draw()
{
}