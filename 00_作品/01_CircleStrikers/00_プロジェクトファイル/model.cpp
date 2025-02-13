//========================================================================================================
//
//モデル処理[model.cpp]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "model.h"
#include "manager.h"
#include "object.h"
#include "transform.h"

//========================================================================================================
//初期化処理
//========================================================================================================
void Model::Init()
{
	//パーツの数分繰り返す
	for (unsigned int i = 0; i < this->m_vParts.size(); i++)
	{
		//パーツの初期化処理を行う
		this->m_vParts[i]->Init();
	}
}

//========================================================================================================
//終了処理
//========================================================================================================
void Model::Uninit()
{
	//パーツの数分繰り返す
	for (unsigned int i = 0; i < this->m_vParts.size(); i++)
	{
		//パーツの終了処理を行う
		this->m_vParts[i]->Uninit();
		delete this->m_vParts[i];
	}

	//パーツを削除する
	this->m_vParts.clear();
}

//========================================================================================================
//更新処理
//========================================================================================================
void Model::Update()
{
	//パーツの数分繰り返す
	for (unsigned int i = 0; i < this->m_vParts.size(); i++)
	{
		//パーツの更新処理を行う
		this->m_vParts[i]->Update();
	}
}

//========================================================================================================
//描画処理
//========================================================================================================
void Model::Draw()
{
	//パーツの数分繰り返す
	for (unsigned int i = 0; i < this->m_vParts.size(); i++)
	{
		D3DXMATRIX mtxWorld;   //ワールドマトリックス

		//親の番号を取得する
		int nIdParent = this->m_vParts[i]->GetIdParent();
		if (nIdParent == -1)
		{//親がいない場合
			//ワールドマトリックスを取得する
			mtxWorld = this->GetObj()->GetComponent<Transform>()->GetMtxWorld();
		}
		else
		{//親がいる場合
			//親の情報を取得する
			mtxWorld = this->m_vParts[nIdParent]->GetMtxWorld();
		}

		//パーツの描画処理を行う
		this->m_vParts[i]->Draw(mtxWorld);
	}
}

//========================================================================================================
//Xファイルの設定処理
//========================================================================================================
void Model::SetXFile(XFile::Mesh mesh)
{
	//パーツを生成する
	Parts* pParts = new Parts;
	pParts->SetXFile(mesh);

	//パーツを保存する
	this->m_vParts.push_back(pParts);
}

//========================================================================================================
//パーツの読み込み処理
//========================================================================================================
void Model::LoadParts(const char* pPass)
{
	//ファイルを開く
	FILE* pFile = fopen(pPass, "r");
	if (pFile != nullptr)
	{//開かれている場合
		char sText[128];   //読み込んだ行

		//------------------------------------------------------------------------------------------------
		//パーツのモデルの読み込み
		//------------------------------------------------------------------------------------------------
		while (1)
		{
			//読み込んだ行を確認する
			if (fgets(sText, 128, pFile) == nullptr)
			{//最後の行まで読み込んだ場合
				//ループを抜け出す
				break;
			}
			else if (strstr(sText, "MODEL_FILENAME") != nullptr)
			{//モデルのパスの場合
				//パスを読み込む
				char sPass[128];   //パスの保存用
				sscanf(sText, "MODEL_FILENAME = %s", &sPass);   //パス

				//パーツを生成する
				Parts* pParts = new Parts;
				pParts->SetXFile(Manager::Get()->GetXFile()->Get(sPass));

				//パーツを保存する
				this->m_vParts.push_back(pParts);
			}
		}

		//読み取り行を最初に戻す
		fseek(pFile, 0, SEEK_SET);

		//------------------------------------------------------------------------------------------------
		//パーツの情報の読み込み
		//------------------------------------------------------------------------------------------------
		int nCnt = 0;
		while (1)
		{
			//読み込んだ行を確認する
			if (fgets(sText, 128, pFile) == nullptr)
			{//最後の行まで読み込んだ場合
				//ループを抜け出す
				break;
			}
			else if (strstr(sText, "PARTSSET") != nullptr)
			{//パーツの情報の場合
				while (1)
				{
					//読み込んだ行を確認する
					if (fgets(sText, 128, pFile) == nullptr)
					{//最後の行まで読み込んだ場合
						//ループを抜け出す
						break;
					}
					if (strstr(sText, "END_PARTSSET") != nullptr)
					{//パーツの情報の終わりの場合
						//番号を設定する
						this->m_vParts[nCnt]->SetId(nCnt);

						//カウンターを進める
						nCnt++;

						//ループを抜け出す
						break;
					}
					else if (strstr(sText, "PARENT") != nullptr)
					{//親の番号の場合
						//親の番号を読み込む
						int nIdParent = -1;
						sscanf(sText, "\t\tPARENT = %d", &nIdParent);
						this->m_vParts[nCnt]->SetIdParent(nIdParent);
					}
					else if (strstr(sText, "POS") != nullptr)
					{//位置の場合
						//位置を読み込む
						D3DXVECTOR3 pos = { 0.0f, 0.0f, 0.0f };
						sscanf(sText, "\t\tPOS = %f %f %f", &pos.x, &pos.y, &pos.z);   //位置
						this->m_vParts[nCnt]->SetPos(pos);
					}
					else if (strstr(sText, "ROT") != nullptr)
					{//向きの場合
						//向きを読み込む
						D3DXVECTOR3 rot = { 0.0f, 0.0f, 0.0f };
						sscanf(sText, "\t\tROT = %f %f %f", &rot.x, &rot.y, &rot.z);   //位置
						this->m_vParts[nCnt]->SetRot(rot);
					}
				}
			}

			//カウンターを確認する
			if ((unsigned int)nCnt >= this->m_vParts.size())
			{
				//ループを抜け出す
				break;
			}
		}

		//ファイルを閉じる
		fclose(pFile);
	}

	//パーツの数分繰り返す
	for (unsigned int i = 0; i < this->m_vParts.size(); i++)
	{
		//パーツの初期化処理を行う
		this->m_vParts[i]->Init();
	}
}

//========================================================================================================
//テクスチャの設定処理
//========================================================================================================
void Model::SetTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	//パーツの数分繰り返す
	for (unsigned int i = 0; i < this->m_vParts.size(); i++)
	{
		//テクスチャを設定する
		this->m_vParts[i]->SetTexture(pTexture);
	}
}