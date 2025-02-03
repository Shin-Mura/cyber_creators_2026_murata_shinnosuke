//========================================================================================================
//
//タイトルシーン処理[title.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "scene.h"
#include "camera.h"
#include "scene.h"

//前方宣言
class Menu;
//タイトルシーン
class Title : public Scene   //（親）シーンクラス
{
public:
	Title();   //コンストラクタ
	virtual ~Title();   //デストラクタ

	void Init() override;   //初期化処理
	void Uninit() override;   //終了処理
	void Update() override;   //更新処理
	void Draw() override;   //描画処理

private:
	Menu* m_pMenu;   //メニュー
};

#endif // !_TITLE_H_
