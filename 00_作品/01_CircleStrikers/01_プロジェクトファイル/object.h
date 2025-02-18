//========================================================================================================
//
//オブジェクト処理[object.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"
#include "component.h"

//オブジェクトクラス
class Object
{
public:
	static const int PRIORITY = 6;   //優先度

	//タグの列挙
	enum TAG
	{
		IS_DEFAULT = 0,
		IS_PLAYER,
	};

	//コンストラクタ
	Object(std::string sName = "Object")
	{
		//メンバ変数を初期化する
		this->m_sName = sName;   //名前
		this->m_tag = TAG::IS_DEFAULT;   //タグ
		this->m_nPriority = 3;   //優先度
		this->m_isDeath = false;   //死亡フラグ
		this->m_isActive = true;   //アクティブフラグ
		this->m_vComponent.clear();

		//オブジェクト管理の最後尾に保存する
		Object::m_vObject.push_back(this);
	}

	//デストラクタ
	virtual ~Object()
	{
	}

	virtual void Init();   //初期化処理
	virtual void Uninit();   //終了処理
	virtual void Update();   //更新処理
	virtual void Draw();   //描画処理
	void Death() { this->m_isDeath = true; };   //死亡フラグを立てる処理

	//コンポーネントの追加処理
	void AddComponent(Component* pComponent)
	{
		//コンポーネントに追加する
		this->m_vComponent.push_back(pComponent);
	}

	void SetTag(TAG tag) { this->m_tag = tag; };   //タグの設定処理
	void SetActive(bool isActive) { this->m_isActive = isActive; };   //アクティブフラグの設定

	TAG GetTag() { return this->m_tag; };   //タグの取得処理
	int GetPriority() { return this->m_nPriority; };   //優先度の取得処理

	//コンポーネントの取得処理
	template<class T> T* GetComponent()
	{
		//コンポーネントの数分繰り返す
		for (unsigned int i = 0; i < this->m_vComponent.size(); i++)
		{
			//指定のコンポーネントか確認する
			if (T* pComponent = dynamic_cast<T*>(this->m_vComponent[i]))
			{//指定のコンポーネントの場合
				//コンポーネントを返す
				return (T*)this->m_vComponent[i];
			}
		}

		//nullを返す
		return nullptr;
	}

	//オブジェクト検索
	static Object* Find(std::string sName)
	{
		Object* pObject = nullptr;   //返すオブジェクト格納用

		//オブジェクトの数分繰り返す
		for (unsigned int i = 0; i < Object::m_vObject.size(); i++)
		{
			//名前を確認する
			if (Object::m_vObject[i]->m_sName == sName)
			{
				//返すオブジェクト格納用に保存する
				pObject = Object::m_vObject[i];

				//ループを抜け出す
				break;
			}
		}

		//オブジェクトを返す
		return pObject;
	}

	//一括解放処理
	static void ReleaseAll()
	{
		//オブジェクトの数分繰り返す
		for (unsigned int i = 0; i < Object::m_vObject.size(); i++)
		{
			//終了処理を行う
			Object::m_vObject[i]->Uninit();
			delete Object::m_vObject[i];
		}

		//オブジェクトを削除する
		Object::m_vObject.clear();
	}

	//一括更新処理
	static void UpdateAll()
	{
		//オブジェクトの数分繰り返す
		for (unsigned int i = 0; i < Object::m_vObject.size(); i++)
		{
			//アクティブフラグを確認する
			if (Object::m_vObject[i]->m_isActive)
			{
				//更新処理を行う
				Object::m_vObject[i]->Update();
				if (Object::m_vObject[i]->m_isDeath == true)
				{//死亡フラグが立っている場合
					//削除する
					Object::m_vObject[i]->Release();
				}
			}
		}
	}

	//一括描画処理
	static void DrawAll()
	{
		//優先度の分繰り返す
		for (int i = 0; i < Object::PRIORITY; i++)
		{
			//オブジェクトの数分繰り返す
			for (unsigned int j = 0; j < Object::m_vObject.size(); j++)
			{
				//優先度を確認する
				if (Object::m_vObject[j]->GetPriority() == i)
				{//現在の周回と一致した場合
					//アクティブフラグを確認する
					if (Object::m_vObject[j]->m_isActive)
					{
						//描画処理を行う
						Object::m_vObject[j]->Draw();
					}
				}
			}
		}
	}

	static Object* Get(int nId) { return m_vObject[nId]; };   //取得処理

	//指定コンポーネントが付いているオブジェクトの取得
	template<class T> static std::vector<Object*> Get()
	{
		std::vector<Object*> vObject;   //返す用コンテナ

		//オブジェクトの数分繰り返す
		for (unsigned int i = 0; i < Object::m_vObject.size(); i++)
		{
			Object* pObject = Object::m_vObject[i];

			//コンポーネントの数分繰り返す
			for (unsigned int j = 0; j < pObject->m_vComponent.size(); j++)
			{
				//キャスト出来るか確認する
				if (T* pComponent = dynamic_cast<T*>(pObject->m_vComponent[j]))
				{
					//コンテナに保存する
					vObject.push_back(Object::m_vObject[i]);
				}
			}
		}

		//コンテナを返す
		return vObject;
	}

private:
	//解放処理
	void Release()
	{
		//破棄する
		this->Uninit();
		Object::m_vObject.erase(Object::m_vObject.begin() + this->GetOder());
		delete this;
	}

	//順番の取得処理
	int GetOder()
	{
		int nOder = -1;   //順番

		//オブジェクトの数分繰り返す
		for (unsigned int i = 0; i < Object::m_vObject.size(); i++)
		{
			//保存されたオブジェクトを確認する
			if (Object::m_vObject[i] == this)
			{//自身の場合
				nOder = i;

				//ループを抜け出す
				break;
			}
		}

		//順番を返す
		return nOder;
	}

	std::string m_sName;   //名前
	TAG m_tag;   //タグ
	int m_nPriority;   //優先度
	bool m_isDeath;   //死亡フラグ
	bool m_isActive;   //アクティブフラグ
	std::vector<Component*> m_vComponent;

	static std::vector<Object*> m_vObject;   //オブジェクト管理
};

#endif // !_OBJECT_H_
