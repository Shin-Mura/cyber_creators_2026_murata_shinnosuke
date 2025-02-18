//========================================================================================================
//
//マネージャー処理[manager.cpp]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "manager.h"
#include "object.h"
//#include "fade.h"
#include "animation.h"

#include <time.h>

//静的メンバ変数を初期化する
Manager* Manager::m_pInstance = nullptr;

//=======================================================================================================
//初期化処理
//=======================================================================================================
HRESULT Manager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//レンダラーを生成する
	this->m_pRenderer = new Renderer;
	this->m_pRenderer->Init(hWnd, TRUE);   //初期化

	//テクスチャを生成する
	this->m_pTexture = new Texture;
	this->m_pTexture->Init();   //初期化

	//Xファイルを生成する
	this->m_pXFile = new XFile;
	this->m_pXFile->Init();   //初期化

	//キーボードを生成する
	this->m_pKeyboard = new Keyboard;
	this->m_pKeyboard->Init(hInstance, hWnd);   //初期化

	//マウスを生成する
	this->m_pMouse = new Mouse;
	this->m_pMouse->Init(hInstance, hWnd);   //初期化

	//ジョイパッドを生成する
	this->m_pJoypad = new Joypad;
	this->m_pJoypad->Init(hInstance, hWnd);   //初期化

	//シーンを設定する
	SetSceneMode(Scene::IS_TITLE);

	return S_OK;
}

//=======================================================================================================
//終了処理
//=======================================================================================================
void Manager::Uninit()
{
	//シーンを破棄する
	this->m_pScene->Uninit();   //終了処理
	delete this->m_pScene;
	this->m_pScene = nullptr;

	//ジョイパッドを破棄する
	this->m_pJoypad->Uninit();
	delete this->m_pJoypad;
	this->m_pJoypad = nullptr;

	//マウスを破棄する
	this->m_pMouse->Uninit();
	delete this->m_pMouse;
	this->m_pMouse = nullptr;

	//キーボードを破棄する
	this->m_pKeyboard->Uninit();
	delete this->m_pKeyboard;
	this->m_pKeyboard = nullptr;

	//Xファイルを破棄する
	this->m_pXFile->Uninit();   //終了処理
	delete this->m_pXFile;
	this->m_pXFile = nullptr;

	//テクスチャを破棄する
	this->m_pTexture->Uninit();   //終了処理
	delete this->m_pTexture;
	this->m_pTexture = nullptr;

	//レンダラーを破棄する
	this->m_pRenderer->Uninit();
	delete this->m_pRenderer;
	this->m_pRenderer = nullptr;
}

//=======================================================================================================
//更新処理
//=======================================================================================================
void Manager::Update()
{
	//乱数の種を設定
	srand((unsigned int)clock());

	//キーボードの更新処理を行う
	this->m_pKeyboard->Update();

	//マウスの更新処理を行う
	this->m_pMouse->Update();

	//ジョイパッドの更新処理を行う
	this->m_pJoypad->Update();

	//レンダラーの更新処理を行う
	this->m_pRenderer->Update();
}

//=======================================================================================================
//描画処理
//=======================================================================================================
void Manager::Draw()
{
	//レンダラーの描画処理を行う
	m_pRenderer->Draw();
}

//=======================================================================================================
//シーンの設定処理
//=======================================================================================================
void Manager::SetSceneMode(Scene::MODE mode)
{
	if (this->m_pScene != nullptr)
	{//データがある場合
		//シーンを破棄する
		this->m_pScene->Uninit();   //終了処理
		delete this->m_pScene;
		this->m_pScene = nullptr;
	}

	//シーンを生成する
	this->m_pScene = Scene::Create(mode);
}