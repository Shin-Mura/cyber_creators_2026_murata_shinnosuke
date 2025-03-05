//========================================================================================================
//
//コンポーネントの処理[component.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "main.h"

//コンポーネント
class Object;
class Component
{
public:
	//コンストラクタ
	Component(Object* pObject)
	{
		//メンバ変数を初期化する
		this->m_pObject = pObject;   //オブジェクト
	}

	//デストラクタ
	virtual ~Component()
	{
	}
	
	virtual void Init() {};   //初期化処理
	virtual void Uninit() {};   //終了処理
	virtual void Update() {};   //更新処理
	virtual void Draw() {};   //描画処理

	Object* GetObj() { return this->m_pObject; };   //オブジェクトの取得

private:
	Object* m_pObject;
};

#endif // !_COMPONENT_H_
