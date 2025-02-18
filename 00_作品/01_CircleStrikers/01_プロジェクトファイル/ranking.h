//========================================================================================================
//
//ランキングシーン処理[ranking.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "scene.h"

//ランキングシーンクラス
class Ranking : public Scene   //（親）シーンクラス
{
public:
	Ranking();   //コンストラクタ
	~Ranking();   //デストラクタ

	void Init() override;   //初期化処理
	void Uninit() override;   //終了処理
	void Update() override;   //更新処理
	void Draw() override;   //描画処理

private:
	void Control();   //操作処理
};

#endif // !_RANKING_H_
