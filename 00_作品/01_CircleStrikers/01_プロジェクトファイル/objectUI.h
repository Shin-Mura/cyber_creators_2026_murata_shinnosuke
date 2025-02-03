//========================================================================================================
//
//2Dオブジェクトの処理[object2D.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _OBJECT2D_
#define _OBJECT2D_

#include "object.h"

//UIオブジェクトクラス
class Object2D : public Object   //（親）オブジェクトクラス
{
public:
	Object2D(int nPriority = 4);   //コンストラクタ
	virtual ~Object2D();   //デストラクタ

	virtual void Init();   //初期化処理
	virtual void Uninit();   //終了処理
	virtual void Update();   //更新処理
	virtual void Draw();   //描画処理

	D3DXVECTOR2 GetPos() { return this->m_pos; };   //位置の取得処理
	D3DXVECTOR2 GetSize() { return this->m_size; };   //サイズの取得処理
	D3DXCOLOR GetColor() { return this->m_color; };   //色の取得処理

protected:
	void SetPos(D3DXVECTOR2 pos) { this->m_pos = pos; };   //位置の設定処理
	void SetSize(D3DXVECTOR2 size) { this->m_size = size; };   //サイズの設定処理
	void SetColor(D3DXCOLOR col) { this->m_color = col; };   //色の設定処理

private:
	D3DXVECTOR2 m_pos;   //位置
	D3DXVECTOR2 m_size;   //サイズ
	D3DXCOLOR m_color;   //色
};

#endif // !_OBJECT2D_
