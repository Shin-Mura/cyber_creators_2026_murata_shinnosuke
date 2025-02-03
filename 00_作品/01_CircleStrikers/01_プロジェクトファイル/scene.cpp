//========================================================================================================
//
//シーン処理[scene.cpp]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "scene.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "ranking.h"

//========================================================================================================
//生成処理
//========================================================================================================
Scene* Scene::Create(MODE mode)
{
	Scene* pScene = nullptr;   //インスタンス格納用

	switch (mode)
	{
	case Scene::MODE::IS_TITLE:
		//タイトルを生成する
		pScene = new Title;
		pScene->Init();

		//処理を抜け出す
		break;

	case Scene::MODE::IS_GAME:
		//ゲームを生成する
		pScene = new Game;
		pScene->Init();

		//処理を抜け出す
		break;

	case Scene::MODE::IS_RESULT:
		//リザルトを生成する
		pScene = new Result;
		pScene->Init();

		//処理を抜け出す
		break;

	case Scene::MODE::IS_RANKIGN:
		//ランキングを生成する
		pScene = new Ranking;
		pScene->Init();

		//処理を抜け出す
		break;
	}

	//シーンを返す
	return pScene;
}