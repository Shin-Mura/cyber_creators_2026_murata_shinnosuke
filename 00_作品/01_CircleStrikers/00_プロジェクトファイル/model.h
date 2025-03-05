//========================================================================================================
//
//モデル処理[model.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "rendering.h"
#include "Xfile.h"
#include "parts.h"
#include "motion.h"

//モデル
class Model : public Rendering   //(親)コンポーネント
{
public:
	//コンストラクタ
	Model(Object* pObject) : Rendering(pObject)
	{
		//メンバ変数を初期化する
		this->m_vParts.clear();
	}

	//デストラクタ
	virtual ~Model() override
	{
	}

	virtual void Init() override;   //初期化処理
	virtual void Uninit() override;   //終了処理
	virtual void Update() override;   //更新処理
	virtual void Draw() override;   //描画処理
	void LoadParts(const char* pPass);   //パーツの読み込み処理

	void SetXFile(XFile::Mesh mesh);   //Xファイルの設定処理
	void SetTexture(LPDIRECT3DTEXTURE9 pTexture);

	Parts* GetParts(int nId) { return this->m_vParts[nId]; };   //パーツの取得処理	
	int GetNumParts() { return this->m_vParts.size(); };   //パーツの数の取得処理

private:
	std::vector<Parts*> m_vParts;   //パーツ
};

//モーション有りモデル
class MotionModel : public Model
{
public:
	//コンストラクタ
	MotionModel(Object* pObject) : Model(pObject)
	{
		//メンバ変数を初期化する
		this->m_nNowMotion = 0;
		this->m_vMotion.clear();
	}

	//デストラクタ
	~MotionModel() override
	{
	}

	virtual void Init() override;   //初期化処理
	virtual void Uninit() override;   //終了処理
	virtual void Update() override;   //更新処理
	virtual void Draw() override { this->Model::Draw(); };   //描画処理

protected:
	void LoadMotion(const char* pPass);   //モーションの読み込み処理

	//モーションの再生処理
	void StartMotion(int nId)
	{
		//モーションの番号を確認する
		if (nId != this->m_nNowMotion)
		{//現在モーションと違う場合
			//現在のモーションに適用する
			this->m_nNowMotion = nId;

			//モーションをリセットする
			this->m_vMotion[this->m_nNowMotion]->Reset();
		}
	}

private:
	int m_nNowMotion;   //再生中モーション
	std::vector<Motion*> m_vMotion;   //モーション
};

#endif // !_MODEL_H_
