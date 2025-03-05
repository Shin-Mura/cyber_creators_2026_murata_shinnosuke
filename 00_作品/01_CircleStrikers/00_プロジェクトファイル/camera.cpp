//========================================================================================================
//
//カメラ処理[camera.cpp]
// Auhtor Murata Shinnosuke
//
//========================================================================================================
#include "camera.h"
#include "manager.h"
#include "renderer.h"

//======================================================================================================
//更新
//======================================================================================================
void Camera::Update()
{
	//向きを確認する
	if (this->m_rot.x > D3DX_PI - 0.01f)
	{//上限を超えた場合
		//補正する
		this->m_rot.x = D3DX_PI - 0.01f;
	}
	else if (this->m_rot.x < 0.01f)
	{//上限を超えた場合
		//補正する
		this->m_rot.x = 0.01f;
	}

	if (Manager::Get()->GetKeyboard()->GetTrigger(DIK_F5))
	{
		//投影方法を確認する
		if (this->m_mtx == Camera::MATRIX::IS_PERSPECTIVE)
		{//透視投影の場合
			this->m_mtx = IS_ORTHO;
		}
		else if (this->m_mtx == Camera::MATRIX::IS_ORTHO)
		{//平行投影の場合
			this->m_mtx = IS_PERSPECTIVE;
		}
	}

	if (Manager::Get()->GetKeyboard()->GetPress(DIK_D))
	{
		this->m_posView.x += 1.0f;
	}
	if (Manager::Get()->GetKeyboard()->GetPress(DIK_A))
	{
		this->m_posView.x -= 1.0f;
	}
}

//======================================================================================================
//設定処理
//======================================================================================================
void Camera::Set()
{
	//デバイスを取得する
	Renderer* pRenderer = Manager::Get()->GetRenderer();   //レンダラー
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();   //デバイスへのポインタ

	//プロジェクションマトリックスを初期化する
	D3DXMatrixIdentity(&this->m_mtxProjection);

	//投影方法を確認する
	if (this->m_mtx == Camera::MATRIX::IS_PERSPECTIVE)
	{//透視投影の場合
		//透視投影を行う
		D3DXMatrixPerspectiveFovLH(&this->m_mtxProjection,
			D3DXToRadian(45.0f),   //視野角
			(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
			10.0f,   //Z値の最小値
			4000.0f);   //Z値の最大値
	}
	else if (this->m_mtx == Camera::MATRIX::IS_ORTHO)
	{//平行投影の場合
		//平行投影を行う
		D3DXMatrixOrthoLH(&this->m_mtxProjection,
			(float)SCREEN_WIDTH,
			(float)SCREEN_HEIGHT,
			10.0f,
			1000.0f);
	}

	//プロジェクションマトリックスを設定する
	pDevice->SetTransform(D3DTS_PROJECTION, &this->m_mtxProjection);

	//ビューマトリックスを初期化する
	D3DXMatrixIdentity(&this->m_mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&this->m_mtxView, &this->m_posView, &this->m_posRegard, &this->m_vecUp);

	//ビューマトリックスを設定する
	pDevice->SetTransform(D3DTS_VIEW, &this->m_mtxView);
}