//========================================================================================================
//
//エフェクトの処理[effect.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "effect.h"
#include "manager.h"
#include "texture.h"

//========================================================================================================
//コンストラクタ
//========================================================================================================
Effect::Effect()
{
	//メンバ変数を初期化する
	this->m_pVtxBuffer = nullptr;   //頂点バッファ
	this->m_pTexture = nullptr;   //テクスチャ
	D3DXMatrixIdentity(&this->m_mtxWorld);   //ワールドマトリックス
	this->m_pos = { 0.0f, 0.0f, 0.0f };   //位置
	this->m_color = { 1.0f, 1.0f, 1.0f, 1.0f };   //色
	this->m_fRadius = 0.0f;   //半径
}

//========================================================================================================
//デストラクタ
//========================================================================================================
Effect::~Effect()
{
}

//========================================================================================================
//初期化処理
//========================================================================================================
void Effect::Init()
{
	//デバイスを取得する
	LPDIRECT3DDEVICE9 pDevice = Manager::Get()->GetRenderer()->GetDevice();

	//頂点バッファを生成する
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,   //確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&this->m_pVtxBuffer,
		nullptr);

	//更新処理を行う
	this->Update();
}

//========================================================================================================
//終了処理
//========================================================================================================
void Effect::Uninit()
{
	//頂点バッファを破棄する
	if (m_pVtxBuffer != nullptr)
	{
		m_pVtxBuffer->Release();
		m_pVtxBuffer = nullptr;
	}
}

//========================================================================================================
//更新処理
//========================================================================================================
void Effect::Update()
{
	//頂点座標をロックして、頂点情報へのポインタを取得する
	VERTEX_3D* pVtx;   //頂点座標
	this->m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標を設定する
	pVtx[0].pos = { -this->m_fRadius, +this->m_fRadius, 0.0f };
	pVtx[1].pos = { +this->m_fRadius, +this->m_fRadius, 0.0f };
	pVtx[2].pos = { -this->m_fRadius, -this->m_fRadius, 0.0f };
	pVtx[3].pos = { +this->m_fRadius, -this->m_fRadius, 0.0f };

	//法線ベクトルを設定する
	pVtx[0].nor = { 0.0f, 0.0f, -1.0f };
	pVtx[1].nor = { 0.0f, 0.0f, -1.0f };
	pVtx[2].nor = { 0.0f, 0.0f, -1.0f };
	pVtx[3].nor = { 0.0f, 0.0f, -1.0f };

	//頂点カラーを設定する
	pVtx[0].col = this->m_color;
	pVtx[1].col = this->m_color;
	pVtx[2].col = this->m_color;
	pVtx[3].col = this->m_color;

	//テクスチャ座標を設定する
	pVtx[0].tex = { 0.0f, 0.0f };
	pVtx[1].tex = { 1.0f, 0.0f };
	pVtx[2].tex = { 0.0f, 1.0f };
	pVtx[3].tex = { 1.0f, 1.0f };

	//頂点バッファをアンロックする
	this->m_pVtxBuffer->Unlock();
}

//========================================================================================================
//描画処理
//========================================================================================================
void Effect::Draw()
{
	D3DXMATRIX mtxTrans;   //計算用マトリックス
	D3DXMATRIX mtxView;   //ビューマトリックス取得用

	//デバイスを取得する
	Renderer* pRenderer = Manager::Get()->GetRenderer();   //レンダラー
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();   //デバイスへのポインタ

	//ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//アルファテストを有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//Zバッファの書き込みを無効にする
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//ワールドマトリックスを初期化する
	D3DXMatrixIdentity(&m_mtxWorld);

	//ビューマトリックスを取得する
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//ポリゴンをカメラに対して正面にする
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);   //逆行列を求める

	//移動情報の打ち消し
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	//位置を反映する
	D3DXMatrixTranslation(&mtxTrans, this->m_pos.x, this->m_pos.y, this->m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスを設定する
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをテータストリームに設定する
	pDevice->SetStreamSource(0, m_pVtxBuffer, 0, sizeof(VERTEX_3D));

	//頂点フォーマットを設定する
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャを設定する
	pDevice->SetTexture(0, m_pTexture);   //設定

	//描画する
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//Zバッファの書き込みを有効にする
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//アルファテストを無効に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//ライトを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}