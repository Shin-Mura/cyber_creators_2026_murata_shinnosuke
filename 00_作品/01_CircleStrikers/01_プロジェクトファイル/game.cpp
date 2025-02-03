//========================================================================================================
//
//ゲームシーン処理[game.cpp]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "game.h"
#include "manager.h"
#include "keyboard.h"
#include "prefab.h"
#include "game_manager.h"

//========================================================================================================
//初期化処理
//========================================================================================================
void Game::Init()
{
	//衝突判定を生成する
	this->m_pPhysics = new Physics;

	//ポーズを生成する
	this->m_pPause = new Pause;
	this->m_pPause->Init();   //初期化

	//カメラを生成する
	CameraPrefab::Create();

	//ディレクショナルライトを生成する
	DireLightPrefab::Create({ 0.22f, -0.87f, 0.44f }, {1.0f, 1.0f, 1.0f, 1.0f});
	DireLightPrefab::Create({ -0.18f, 0.88f, -0.44f }, { 0.65f, 0.65f, 0.65f, 1.0f });
	DireLightPrefab::Create({ 0.89f, 0.11f, 0.44f }, { 0.15f, 0.15f, 0.15f, 0.15f });

	//背景を追加する
	Background3DPrefab::Create(Manager::Get()->GetTexture()->Get("field_00.png"));

	//プレイヤーを生成する
	PlayerPrefab::Create({ 300.0f, 0.0f, 0.0f }, 0);
	PlayerPrefab::Create({ -300.0f, 0.0f, 0.0f }, 1);

	//タイマーを生成する
	TimerPrefab::Create();

	//フェードを生成する
	FadePrefab::Create();
}

//========================================================================================================
//終了処理
//========================================================================================================
void Game::Uninit()
{
	//オブジェクトを一括破棄する
	Object::ReleaseAll();

	//ポーズを破棄する
	this->m_pPause->Uninit();
	delete this->m_pPause;
	this->m_pPause = nullptr;

	//衝突判定を破棄する
	delete this->m_pPhysics;
	this->m_pPhysics = nullptr;
}

//========================================================================================================
//更新処理
//========================================================================================================
void Game::Update()
{
	Keyboard* pKeyboard = Manager::Get()->GetKeyboard();   //キーボード入力
	Joypad* pJoypad = Manager::Get()->GetJoypad();   //ジョイパッド

	//Pキーを確認する
	if (pKeyboard->GetTrigger(DIK_P) || pJoypad->GetTrigger(Joypad::JOYKEY_START, 0))
	{//Pキーが押されている場合
		//ポーズフラグを切り替える
		this->m_pPause->SwitchPause();
	}

	//ポーズフラグを確認する
	if (this->m_pPause->GetPause() == true)
	{//ポーズフラグが立っている場合
		//ポーズの更新処理を行う
		this->m_pPause->Update();

		//ポーズメニューを取得する
		Menu* pPauseMenu = this->m_pPause->GetMenu();

		//終了フラグを確認する
		if (pPauseMenu->GetDecide() == true)
		{//終了フラグが立っている場合
			//ポーズメニューの選択中のメニューによって処理を変える
			switch (pPauseMenu->GetSelect())
			{
			case  PauseMenu::MENU::IS_CONTINUE:
				//ポーズを切り替える
				this->m_pPause->SwitchPause();

				//処理を抜け出す
				break;

			case PauseMenu::MENU::IS_REPLAY:  //リプレイの場合
				//ゲーム画面に遷移する
				Manager::Get()->SetSceneMode(Scene::MODE::IS_GAME);

				//処理を抜け出す
				break;

			case PauseMenu::MENU::IS_QUIT:   //終了の場合
				//タイトル画面に遷移する
				Manager::Get()->SetSceneMode(Scene::MODE::IS_TITLE);

				//処理を抜け出す
				break;
			}

			//処理終了
			return;
		}
	}
	else
	{//立っていない場合
		Object::UpdateAll();

		//次のシーンフラグを確認する
		if (this->GetEnd())
		{
			//リザルト画面に遷移する
			Manager::Get()->SetSceneMode(Scene::MODE::IS_RESULT);
		}
	}
}

//========================================================================================================
//描画処理
//========================================================================================================
void Game::Draw()
{
	//オブジェクトの一括描画を行う
	Object::DrawAll();
}