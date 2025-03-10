//========================================================================================================
//
//ポーズの処理[pause.cpp]
// Auhtor Murata Shinnosuke
//
//========================================================================================================
#include "pause.h"
#include "prefab.h"
#include "pause_menu.h"

//========================================================================================================
//コンストラクタ
//========================================================================================================
Pause::Pause()
{
	//メンバ変数を初期化する
	this->m_isPause = false;
	this->m_pMenu = nullptr;
}

//========================================================================================================
//デストラクタ
//========================================================================================================
Pause::~Pause()
{
}

//========================================================================================================
//初期化処理
//========================================================================================================
void Pause::Init()
{
	//ポーズメニューを生成する
	this->m_pMenu = PauseMenuPrefab::Create()->GetComponent<Menu>();
}

//========================================================================================================
//終了処理
//========================================================================================================
void Pause::Uninit()
{
}

//========================================================================================================
//更新処理
//========================================================================================================
void Pause::Update()
{
	//ポーズメニューの更新処理を行う
	this->m_pMenu->Update();
}

//========================================================================================================
//描画処理
//========================================================================================================
void Pause::Draw()
{
}

//========================================================================================================
//ポーズの切り替え処理
//========================================================================================================
void Pause::SwitchPause()
{
	//ポーズを切り替える
	this->m_isPause = this->m_isPause ? false : true;
	if (this->m_isPause == true)
	{//ポーズ中に切り替わった場合
		//ポーズメニューを初期化する
		this->m_pMenu->Init();
		this->m_pMenu->GetObj()->SetActive(true);   //アクティブ化
	}
	else
	{
		//非アクティブ化する
		this->m_pMenu->GetObj()->SetActive(false);
	}
}