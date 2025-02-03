//========================================================================================================
//
//モーションの処理[motion.h]
// Author MurataShinnosuke
//
//========================================================================================================
#ifndef _MOTION_H_
#define _MOTION_H_

#include "main.h"

//モーション
class Motion
{
public:
	static const int MAX_KEY = 32;   //キーの最大数

	struct Key   //キーの構造体
	{
		int nFrame;   //フレーム
		D3DXVECTOR3 pos[32];   //位置
		D3DXVECTOR3 rot[32];   //向き
	};

	Motion();   //コンストラクタ
	~Motion();   //デストラクタ

	void Init();   //初期化処理
	void Uninit();   //終了処理
	void Update();   //更新処理
	void Reset();   //リセット処理

	void SetKey(Motion::Key key);   //キーの設定処理

	void Loop() { this->m_isLoop = true; };   //ループフラグの確立処理

	D3DXVECTOR3 GetPos(int nId) { return this->m_pos[nId]; };   //位置の取得処理
	D3DXVECTOR3 GetRot(int nId) { return this->m_rot[nId]; };   //位置の取得処理

private:
	bool m_isLoop;   //ループフラグ
	int m_nFrame;   //現在フレーム
	int m_nFrameBlend;   //ブレンドフレーム
	int m_nKey;   //現在キー
	Motion::Key m_key[Motion::MAX_KEY];   //キー
	int m_nNumKey;   //キーの数

	D3DXVECTOR3 m_pos[32];
	D3DXVECTOR3 m_rot[32];
};

#endif // !_MOTION_H_