//========================================================================================================
//
//ポーズの処理[pause.h]
// Auhtor Murata Shinnosuke
//
//========================================================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

//前方宣言
class Menu;
//ポーズクラス
class Pause
{
public:
	Pause();   //コンストラクタ
	~Pause();   //デストラクタ

	void Init();   //初期化処理
	void Uninit();   //終了処理
	void Update();   //更新処理
	void Draw();   //描画処理
	void SwitchPause();   //ポーズの切り替え処理

	bool GetPause() { return this->m_isPause; };   //ポーズフラグの取得処理
	Menu* GetMenu() { return this->m_pMenu; };   //選択中の選択肢の取得処理

private:
	bool m_isPause;   //ポーズフラグ
	Menu* m_pMenu;   //メニュー
};

#endif // !_PAUSE_H_