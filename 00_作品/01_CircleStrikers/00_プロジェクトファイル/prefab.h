//==========================================================================================================
//
//プレハブの処理[prefab.h]
// Author MurataShinnosuke
//
//==========================================================================================================
#ifndef _PREFAB_H_
#define _PREFAB_H_

#include "object.h"
#include "manager.h"

#include "camera.h"
#include "collider.h"
#include "dire_light.h"
#include "rigidbody.h"
#include "transform.h"

#include "menu.h"
#include "model.h"
#include "number.h"
#include "plane.h"
#include "square.h"

#include "body.h"
#include "block.h"
#include "camera_tps.h"
#include "fade.h"
#include "pause_menu.h"
#include "player.h"
#include "timer.h"
#include "title_menu.h"

//背景
class Background2DPrefab
{
public:
	//生成処理
	static Object* Create(LPDIRECT3DTEXTURE9 pTexture)
	{
		//背景を生成する
		Object* pPrefab = new Object("Background2D");

		//トランスフォームを追加する
		Transform2D* pTransform2D = new Transform2D(pPrefab);
		pTransform2D->SetSize({ SCREEN_WIDTH, SCREEN_HEIGHT });
		pPrefab->AddComponent(pTransform2D);

		//四角形レンダリングを追加する
		Square* pSquare = new Square(pPrefab);
		pSquare->SetTexture(pTexture);
		pPrefab->AddComponent(pSquare);

		//初期化する
		pPrefab->Init();

		//プレハブを返す
		return pPrefab;
	}
};

//背景
class Background3DPrefab
{
public:
	//生成処理
	static Object* Create(LPDIRECT3DTEXTURE9 pTexture)
	{
		//背景を生成する
		Object* pPrefab = new Object("Background3D");

		//トランスフォームを追加する
		Transform* pTransform = new Transform(pPrefab);
		pTransform->SetPos({ 0.0f, 0.0f, 10.0f });
		pTransform->SetScale({ 6.4f, 3.6f, 1.0f });
		pPrefab->AddComponent(pTransform);

		//四角形レンダリングを追加する
		PlaneY* pPlaneY = new PlaneY(pPrefab);
		pPlaneY->SetTexture(pTexture);
		pPrefab->AddComponent(pPlaneY);

		//初期化する
		pPrefab->Init();

		//プレハブを返す
		return pPrefab;
	}
};

//体
class BodyPrefab
{
public:
	//生成処理
	static Object* Create(Object* pPlayer, D3DXVECTOR3 pos)
	{
		//プレイヤーを生成する
		Object* pPrefab = new Object("Body");

		//トランスフォームを追加する
		Transform* pTransform = new Transform(pPrefab);
		pTransform->SetPos(pos);
		pTransform->SetScale({ 0.125f, 0.125f, 1.0f });
		pPrefab->AddComponent(pTransform);

		//四角形レンダリングを追加する
		PlaneY* pPlaneY = new PlaneY(pPrefab);
		pPlaneY->SetTexture(Manager::Get()->GetTexture()->Get("player_00.png"));
		pPrefab->AddComponent(pPlaneY);

		//ボックスコライダーを追加する
		BoxCollider* pBoxCollider = new BoxCollider(pPrefab);
		pBoxCollider->SetSize({ Plane::BASE_SIZE.x * pTransform->GetScale().x, Plane::BASE_SIZE.y * pTransform->GetScale().y, 5.0f });
		pBoxCollider->Trigger();
		pPrefab->AddComponent(pBoxCollider);

		//プレイヤーの挙動を追加する
		Body* pBody = new Body(pPrefab, pPlayer);
		pPrefab->AddComponent(pBody);

		//初期化する
		pPrefab->Init();

		//プレハブを返す
		return pPrefab;
	}
};

//ブロック
class BlockPrefab
{
public:
	//生成処理
	static Object* Create()
	{
		//ブロックを生成する
		Object* pPrefab = new Object("Block");

		//トランスフォームを追加する
		Transform* pTransform = new Transform(pPrefab);
		pPrefab->AddComponent(pTransform);

		//モデルレンダリングを追加する
		Model* pModel = new Model(pPrefab);
		pModel->SetXFile(Manager::Get()->GetXFile()->Get("block_00.x"));
		pModel->SetTexture(Manager::Get()->GetTexture()->Get("block_00.png"));
		pPrefab->AddComponent(pModel);

		//ブロックの挙動を追加する
		Block* pBlock = new Block(pPrefab);
		pPrefab->AddComponent(pBlock);

		//初期化する
		pPrefab->Init();

		//プレハブを返す
		return pPrefab;
	}
};

//カメラ
class CameraPrefab
{
public:
	//生成処理
	static Object* Create()
	{
		//カメラを生成する
		Object* pPrefab = new Object("Camera");

		//トランスフォームを追加する
		Transform* pTransform = new Transform(pPrefab);
		pPrefab->AddComponent(pTransform);

		//カメラを追加する
		Camera* pCamera = new Camera(pPrefab);
		pPrefab->AddComponent(pCamera);

		////TPSカメラの挙動を追加する
		//CameraTPS* pCameraTPS = new CameraTPS(pPrefab);
		//pPrefab->AddComponent(pCameraTPS);

		//初期化する
		pPrefab->Init();

		//プレハブを返す
		return pPrefab;
	}
};

//ライト
class DireLightPrefab
{
public:
	//生成処理
	static Object* Create(D3DXVECTOR3 rot, D3DXCOLOR color)
	{
		//ライトを生成する
		Object* pPrefab = new Object("DirectionalLight");

		//トランスフォームを追加する
		Transform* pTransform = new Transform(pPrefab);
		pTransform->SetRot(rot);
		pPrefab->AddComponent(pTransform);

		//ライトを追加する
		DireLight* pDireLight = new DireLight(pPrefab);
		pDireLight->SetColor(color);   //色
		pPrefab->AddComponent(pDireLight);

		//初期化する
		pPrefab->Init();

		//プレハブを返す
		return pPrefab;
	}
};

//背景
class FadePrefab
{
public:
	//生成処理
	static Object* Create()
	{
		//背景を生成する
		Object* pPrefab = new Object("Fade");

		//トランスフォームを追加する
		Transform2D* pTransform2D = new Transform2D(pPrefab);
		pTransform2D->SetSize({ SCREEN_WIDTH, SCREEN_HEIGHT });
		pPrefab->AddComponent(pTransform2D);

		//四角形レンダリングを追加する
		Square* pSquare = new Square(pPrefab);
		pSquare->SetColor({ 0.0f, 0.0f, 0.0f, 1.0f });   //色
		pPrefab->AddComponent(pSquare);

		//フェードの挙動を追加する
		Fade* pFade = new Fade(pPrefab);
		pPrefab->AddComponent(pFade);

		//初期化する
		pPrefab->Init();

		//プレハブを返す
		return pPrefab;
	}
};

//ポーズメニュー
class PauseMenuPrefab
{
public:
	//生成処理
	static Object* Create()
	{
		//ポーズメニューを生成する
		Object* pPrefab = new Object("PauseMenu");
		pPrefab->SetActive(false);   //非アクティブ

		//トランスフォームを追加する
		Transform2D* pTransform2D = new Transform2D(pPrefab);
		pTransform2D->SetPos({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 });   //位置
		pTransform2D->SetSize(PauseMenu::SIZE_MENU);   //サイズ
		pPrefab->AddComponent(pTransform2D);

		//メニューレンダリングを追加する
		Menu* pMenu = new Menu(pPrefab);
		pMenu->SetTexture(Manager::Get()->GetTexture()->Get("pause_menu_00.png"));
		pMenu->SetSelectBox(PauseMenu::MENU::IS_MAX);
		pMenu->SetGap(1.0f);
		pPrefab->AddComponent(pMenu);

		//ポーズメニューの挙動を追加する
		PauseMenu* pPauseMenu = new PauseMenu(pPrefab);
		pPrefab->AddComponent(pPauseMenu);

		//初期化する
		pPrefab->Init();

		//プレハブを返す
		return pPrefab;
	}
};

//プレイヤー
class PlayerPrefab
{
public:
	//生成処理
	static Object* Create(D3DXVECTOR3 pos, int nId)
	{
		//プレイヤーを生成する
		Object* pPrefab = new Object("Player");
		pPrefab->SetTag(Object::TAG::IS_PLAYER);

		//トランスフォームを追加する
		Transform* pTransform = new Transform(pPrefab);
		pTransform->SetPos(pos);
		pTransform->SetScale({ 0.125f, 0.125f, 1.0f });
		pPrefab->AddComponent(pTransform);

		//四角形レンダリングを追加する
		PlaneY* pPlaneY = new PlaneY(pPrefab);
		pPlaneY->SetTexture(Manager::Get()->GetTexture()->Get("player_00.png"));
		pPrefab->AddComponent(pPlaneY);

		//リジットボディを追加する
		Rigidbody* pRigidbody = new Rigidbody(pPrefab);
		pRigidbody->SetGravity(0.0f);   //重力無し
		pRigidbody->SetFriction(0.1f);   //慣性
		pRigidbody->SetFrictionAir(0.1f);
		pPrefab->AddComponent(pRigidbody);

		//ボックスコライダーを追加する
		BoxCollider* pBoxCollider = new BoxCollider(pPrefab);
		pBoxCollider->SetSize({ Plane::BASE_SIZE.x * pTransform->GetScale().x, Plane::BASE_SIZE.y * pTransform->GetScale().y, 5.0f});
		pPrefab->AddComponent(pBoxCollider);

		//プレイヤーの挙動を追加する
		Player* pPlayer = new Player(pPrefab, nId);
		pPrefab->AddComponent(pPlayer);

		//初期化する
		pPrefab->Init();

		//プレハブを返す
		return pPrefab;
	}
};

//タイマー
class TimerPrefab
{
public:
	//生成処理
	static Object* Create()
	{
		//タイマーを生成する
		Object* pPrefab = new Object("Timer");

		//トランスフォームを追加する
		Transform2D* pTransform2D = new Transform2D(pPrefab);
		pTransform2D->SetPos({ 50.0f, 80.0f });   //位置
		pTransform2D->SetSize({200.0f, 100.0f});   //サイズ
		pPrefab->AddComponent(pTransform2D);

		//数字レンダリングを追加する
		Number* pNumber = new Number(pPrefab);
		pNumber->SetTexture(Manager::Get()->GetTexture()->Get("number_00.png"));
		pNumber->SetDigit(3);
		pNumber->SetNumber(Timer::START_TIMER);
		pPrefab->AddComponent(pNumber);

		//タイマーの挙動を追加する
		Timer* pTimer = new Timer(pPrefab);
		pPrefab->AddComponent(pTimer);

		//初期化する
		pPrefab->Init();

		//プレハブを返す
		return pPrefab;
	}
};

//タイトルメニュー
class TitleMenuPrefab
{
public:
	//生成処理
	static Object* Create()
	{
		//タイトルメニューを生成する
		Object* pPrefab = new Object("TitleMenu");

		//トランスフォームを追加する
		Transform2D* pTransform2D = new Transform2D(pPrefab);
		pTransform2D->SetPos({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 });   //位置
		pTransform2D->SetSize(TitleMenu::SIZE_MENU);   //サイズ
		pPrefab->AddComponent(pTransform2D);

		//メニューレンダリングを追加する
		Menu* pMenu = new Menu(pPrefab);
		pMenu->SetTexture(Manager::Get()->GetTexture()->Get("title_menu_00.png"));
		pMenu->SetSelectBox(TitleMenu::MENU::IS_MAX);
		pMenu->SetGap(1.0f);
		pPrefab->AddComponent(pMenu);

		//タイトルメニューの挙動を追加する
		TitleMenu* pTitleMenu = new TitleMenu(pPrefab);
		pPrefab->AddComponent(pTitleMenu);

		//初期化する
		pPrefab->Init();

		//プレハブを返す
		return pPrefab;
	}
};

#endif // !_PREFAB_H_
