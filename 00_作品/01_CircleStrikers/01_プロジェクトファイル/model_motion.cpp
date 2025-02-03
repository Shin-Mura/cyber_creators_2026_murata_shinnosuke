//========================================================================================================
//
//モーション有モデルの処理[model_motion.cpp]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "model.h"

//========================================================================================================
//初期化処理
//========================================================================================================
void MotionModel::Init()
{
	//
	this->Model::Init();

	//モーションの数分繰り返す
	for (unsigned int i = 0; i < this->m_vMotion.size(); i++)
	{
		//モーションの初期化処理を行う
		this->m_vMotion[i]->Init();
	}
}

//========================================================================================================
//終了処理
//========================================================================================================
void MotionModel::Uninit()
{
	//
	this->Model::Uninit();

	//モーションの数分繰り返す
	for (unsigned int i = 0; i < this->m_vMotion.size(); i++)
	{
		//モーションの終了処理を行う
		this->m_vMotion[i]->Uninit();
		delete this->m_vMotion[i];
	}

	//モーションを削除する
	this->m_vMotion.clear();
}

//========================================================================================================
//更新処理
//========================================================================================================
void MotionModel::Update()
{
	//現在モーションの更新処理を行う
	int nNowMotion = this->m_nNowMotion;
	this->m_vMotion[nNowMotion]->Update();

	//パーツの数分繰り返す
	for (int i = 0; i < this->GetNumParts(); i++)
	{
		//モーションのキーの情報をパーツに設定する
		this->GetParts(i)->SetRot(this->m_vMotion[nNowMotion]->GetRot(i));
	}

	//
	this->Model::Update();
}

//=========================================================================================================
//パーツの読み込み処理
//=========================================================================================================
void MotionModel::LoadMotion(const char* pPass)
{
	//パーツを読み込む
	this->LoadParts("data\\MOTION\\motion_player.txt");

	//ファイルを開く
	FILE* pFile = fopen(pPass, "r");
	if (pFile != nullptr)
	{//開かれている場合
		char sText[128];   //読み込んだ行

		//-------------------------------------------------------------------------------------------------
		//モーションを読み込む
		//-------------------------------------------------------------------------------------------------
		while (1)
		{
			//読み込んだ行を確認する
			if (fgets(sText, 128, pFile) == nullptr)
			{//最後の行まで読み込んだ場合
				//ループを抜け出す
				break;
			}
			else if (strstr(sText, "MOTIONSET") != nullptr)
			{//モーションの設定の場合
				//モーションを生成する
				Motion* pMotion = new Motion;

				while (1)
				{
					//読み込んだ行を確認する
					if (fgets(sText, 128, pFile) == nullptr)
					{//最後の行まで読み込んだ場合
						//ループを抜け出す
						break;
					}
					else if (strstr(sText, "END_MOTIONSET") != nullptr)
					{//モーションの情報の終わりの場合
						//ループを抜け出す
						break;
					}
					else if (strstr(sText, "LOOP") != nullptr)
					{//ループフラグの場合
						//ループフラグを読み込む
						int nLoop;
						sscanf(sText, "\tLOOP = %d", &nLoop);
						if (nLoop = 1)
						{//1の場合
							//ループフラグを立てる
							pMotion->Loop();
						}
					}
					else if (strstr(sText, "KEYSET") != nullptr)
					{//キーの設定の場合
						Motion::Key keyLoad;   //読み込んだキーの保存用
						int nCntKey = 0;   //キーのカウンター

						while (1)
						{
							//読み込んだ行を確認する
							if (fgets(sText, 128, pFile) == nullptr)
							{//最後の行まで読み込んだ場合
								//ループを抜け出す
								break;
							}
							else if (strstr(sText, "END_KEYSET") != nullptr)
							{//キーの設定の終わりの場合
								//保存したキーを設定する
								pMotion->SetKey(keyLoad);

								//ループを抜け出す
								break;
							}
							else if (strstr(sText, "FRAME") != nullptr)
							{//フレームの場合
								//フレームを読み込む
								sscanf(sText, "\t\tFRAME = %d", &keyLoad.nFrame);
							}
							else if (strstr(sText, "KEY\t") != nullptr)
							{//キーの場合
								//次の行を読み込む
								fgets(sText, 128, pFile);
								sscanf(sText, "\t\t\tPOS = %f %f %f", &keyLoad.pos[nCntKey].x, &keyLoad.pos[nCntKey].y, &keyLoad.pos[nCntKey].z);   //位置を保存

								//次の行を読み込む
								fgets(sText, 128, pFile);
								sscanf(sText, "\t\t\tROT = %f %f %f", &keyLoad.rot[nCntKey].x, &keyLoad.rot[nCntKey].y, &keyLoad.rot[nCntKey].z);   //位置を保存

								//キーのカウンターを進める
								nCntKey++;
							}
						}
					}
				}

				//モーションを保存する
				this->m_vMotion.push_back(pMotion);
			}
		}

		//ファイルを閉じる
		fclose(pFile);
	}

	//パーツの数分繰り返す
	for (unsigned int i = 0; i < this->m_vMotion.size(); i++)
	{
		//モーションの初期化処理を行う
		this->m_vMotion[i]->Init();
	}
}