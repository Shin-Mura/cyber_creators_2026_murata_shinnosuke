//========================================================================================================
//
//エフェクト処理[effect.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "object.h"

//エフェクトクラス
class Effect : public Object   //(親)オブジェクト
{
public:
	Effect();   //コンストラクタ
	~Effect() override;   //デストラクタ

	virtual void Init() override;   //初期化処理
	virtual void Uninit() override;   //終了処理
	virtual void Update() override;   //更新処理
	virtual void Draw() override;   //描画処理

protected:
	void SetTexture(LPDIRECT3DTEXTURE9 pTexture) { this->m_pTexture = pTexture; };

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer;   //頂点バッファ
	LPDIRECT3DTEXTURE9 m_pTexture;   //テクスチャ
	D3DXMATRIX m_mtxWorld;   //ワールドマトリックス
	D3DXVECTOR3 m_pos;   //位置
	D3DXCOLOR m_color;   //色
	float m_fRadius;   //半径
};

#endif // !_EFFECT_H_
