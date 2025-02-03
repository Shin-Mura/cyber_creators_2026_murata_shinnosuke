//========================================================================================================
//
//タイトルシーン処理[result.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "scene.h"

//タイトルシーンクラス
class Result : public Scene   //（親）シーンクラス
{
public:
	Result();   //コンストラクタ
	virtual ~Result();   //デストラクタ

	void Init() override;   //初期化処理
	void Uninit() override;   //終了処理
	void Update() override;   //更新処理
	void Draw() override;   //描画処理

private:
};

#endif // !_RESULT_H_
