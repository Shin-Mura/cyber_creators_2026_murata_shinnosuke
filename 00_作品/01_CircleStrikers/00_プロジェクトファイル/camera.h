//********************************************************************************************************
//
//カメラの処理[camera.h]
// Auhtor Murata Shinnosuke
//
//********************************************************************************************************
#ifndef _CAMERA_H_
#define _CAMERA_H_ 

#include "component.h"
#include "object.h"

//カメラクラス
class Camera : public Component
{
public:
	//投影方法の列挙
	enum MATRIX
	{
		IS_PERSPECTIVE = 0,   //透視投影
		IS_ORTHO,   //平行投影
		IS_MAX
	};

	//コンストラクタ
	Camera(Object* pObject) : Component(pObject)
	{
		this->m_posView = { 0.0f, 0.0f, -500.0f };   //視点
		this->m_posRegard = { 0.0f, 0.0f, 0.0f };   //注視点
		this->m_vecUp = { 0.0f, 1.0f, 0.0f };   //上方向ベクトル
		this->m_rot = { D3DX_PI / 2, 0.0f, 0.0f };   //向き
		this->m_mtxProjection;   //プロジェクションマトリックス
		this->m_mtxView;   //ビューマトリックス
		this->m_mtx = MATRIX::IS_ORTHO;;
	}

	//デストラクタ
	~Camera()
	{
	}

	void Update() override;   //更新
	void Set();   //設定処理
	void AddRot(D3DXVECTOR3 rotAdd) { this->m_rot += rotAdd; };   //向きの加算

	void SetPosView(D3DXVECTOR3 pos) { this->m_posView = pos; };   //視点の位置の設定
	void SetPosRegard(D3DXVECTOR3 pos) { this->m_posRegard = pos; };   //注視点の位置の設定

	D3DXVECTOR3 GetPosView() { return this->m_posView; };   //視点の位置の取得
	D3DXVECTOR3 GetPosRegard() { return this->m_posRegard; };   //注視点の取得処理
	D3DXVECTOR3 GetRot() { return this->m_rot; };   //向きの取得処理

private:
	D3DXVECTOR3 m_posView;   //視点の位置
	D3DXVECTOR3 m_posRegard;   //注視点の位置
	D3DXVECTOR3 m_vecUp;   //上方向ベクトル
	D3DXVECTOR3 m_rot;   //向き
	D3DXMATRIX m_mtxProjection;   //プロジェクションマトリックス
	D3DXMATRIX m_mtxView;   //ビューマトリックス
	MATRIX m_mtx;   //投影方法
};

#endif // !_CAMERA_H_