//========================================================================================================
//
//シーン処理[scene.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

//シーンクラス
class Scene
{
public:
	typedef enum
	{
		IS_TITLE = 0,   //タイトル
		IS_GAME,   //ゲーム
		IS_RESULT,   //リザルト
		IS_RANKIGN,   //ランキング
	}MODE;   //モード

	//コンストラクタ
	Scene()
	{
		//メンバ変数を初期化する
		this->m_mode = Scene::MODE::IS_TITLE;   //モード
		this->m_isNextScene = false;   //遷移フラグ
	}

	//デストラクタ
	virtual ~Scene()
	{
	}

	virtual void Init() = 0;   //初期化処理
	virtual void Uninit() = 0;   //終了処理
	virtual void Update() = 0;   //更新処理
	virtual void Draw() = 0;   //描画処理
	void NextScene() { this->m_isNextScene = true; };   //終了フラグを立てる

	static Scene* Create(MODE mode);   //生成処理

protected:
	bool GetEnd() { return this->m_isNextScene; };   //終了フラグの取得

private:
	MODE m_mode;   //モード
	bool m_isNextScene;   //終了フラグ
};

#endif // !_SCENE_H_
