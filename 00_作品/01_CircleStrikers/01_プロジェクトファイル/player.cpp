//========================================================================================================
//
//プレイヤー処理[player.cpp]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "player.h"
#include "benlib.h"
#include "manager.h"
#include "joypad.h"
#include "component.h"
#include "rigidbody.h"
#include "collider.h"
#include "rendering.h"
#include "game_manager.h"
#include "prefab.h"

//静的メンバ変数を初期化する
const float Player::MOVE_SPEED = 2.0f;

//========================================================================================================
//初期化処理
//========================================================================================================
void Player::Init()
{
}

//========================================================================================================
//更新処理
//========================================================================================================
void Player::Update()
{
	//ヒットフラグを確認する
	if (this->m_isHit)
	{
		//処理を終了する
		return;
	}

	//コントロール処理を行う
	this->Control();

	//行動制限処理を行う
	this->LimitMove();

	//体を生成する
	BodyPrefab::Create(this->GetObj(), this->GetObj()->GetComponent<Transform>()->GetPos());
}

//========================================================================================================
//ヒット処理
//========================================================================================================
void Player::Hit()
{
	//ヒットフラグを立てる
	this->m_isHit = true;
	this->GetObj()->GetComponent<Rendering>()->SetColor({ 1.0f, 0.0f, 0.0f, 1.0f });   //赤くする
}

//========================================================================================================
//コントロール処理
//========================================================================================================
void Player::Control()
{
	Joypad* pJoypad = Manager::Get()->GetJoypad();

	//----------------------------------------------------------------------------------------------------
	//移動処理
	//----------------------------------------------------------------------------------------------------
	{
		short sThumbLX = pJoypad->GetState(this->m_nId)->Gamepad.sThumbLX;   //左右入力
		short sThumbLY = pJoypad->GetState(this->m_nId)->Gamepad.sThumbLY;   //上下入力

		//倒してる方向を計算する
		float fDireThumbL = atan2f(sThumbLX, sThumbLY);
		if (sThumbLX != 0 || sThumbLY != 0)
		{//左スティックが入力されている場合
			//移動量を増やす
			this->GetObj()->GetComponent<Rigidbody>()->AddMove({ sinf(fDireThumbL) * Player::MOVE_SPEED, cosf(fDireThumbL) * Player::MOVE_SPEED, 0.0f });
		}
	}

	//----------------------------------------------------------------------------------------------------
	//加速処理
	//----------------------------------------------------------------------------------------------------
	{
		//Aボタンを確認する
		if (pJoypad->GetTrigger(Joypad::JOYKEY::JOYKEY_A, this->m_nId))
		{
			//加速する
			this->GetObj()->GetComponent<Rigidbody>()->AddMove(this->GetObj()->GetComponent<Rigidbody>()->GetMove());
		}
	}
}

//========================================================================================================
//行動制限処理
//========================================================================================================
void Player::LimitMove()
{
	//コンポーネントを取得する
	Transform* pTransform = this->GetObj()->GetComponent<Transform>();   //トランスフォーム
	Rigidbody* pRigidbody = this->GetObj()->GetComponent<Rigidbody>();   //リジットボディ
	BoxCollider* pBoxCollider = this->GetObj()->GetComponent<BoxCollider>();   //ボックスコライダー

	//当たり判定の範囲を取得する
	BoxCollider::Range range = pBoxCollider->GetRange();

	//右の確認をする
	if (range.posMax.x > SCREEN_WIDTH / 2)
	{
		//位置を修正する
		D3DXVECTOR3 posNew = pTransform->GetPos();
		posNew.x = SCREEN_WIDTH / 2 - (pBoxCollider->GetSize().x / 2);
		this->GetObj()->GetComponent<Transform>()->SetPos(posNew);

		//反射する
		pRigidbody->AddMove({ -pRigidbody->GetMove().x * 2, 0.0f, 0.0f });
	}

	//左の確認をする
	if (range.posMin.x < -SCREEN_WIDTH / 2)
	{
		//位置を修正する
		D3DXVECTOR3 posNew = pTransform->GetPos();
		posNew.x = -SCREEN_WIDTH / 2 + (pBoxCollider->GetSize().x / 2);
		pTransform->SetPos(posNew);

		//反射する
		pRigidbody->AddMove({ -pRigidbody->GetMove().x * 2, 0.0f, 0.0f });
	}

	//上の確認をする
	if (range.posMax.y > SCREEN_HEIGHT / 2)
	{
		//位置を修正する
		D3DXVECTOR3 posNew = pTransform->GetPos();
		posNew.y = SCREEN_HEIGHT / 2 - (pBoxCollider->GetSize().y / 2);
		pTransform->SetPos(posNew);

		//反射する
		pRigidbody->AddMove({ 0.0f, -pRigidbody->GetMove().y * 2, 0.0f });
	}

	//下の確認をする
	if (range.posMin.y < -SCREEN_HEIGHT / 2)
	{
		//位置を修正する
		D3DXVECTOR3 posNew = pTransform->GetPos();
		posNew.y = -SCREEN_HEIGHT / 2 + (pBoxCollider->GetSize().y / 2);
		pTransform->SetPos(posNew);

		//反射する
		pRigidbody->AddMove({ 0.0f, -pRigidbody->GetMove().y * 2, 0.0f });
	}
}