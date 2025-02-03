//===========================================================================================================
//
//入力アクションの処理[input_action.h]
// Author Murata Shinnosuke
//
//===========================================================================================================
#ifndef _INPUT_ACTION_H_
#define _INPUT_ACTION_H_

//入力アクション
class InputAction
{
public:
	static const int MAX_DATA = 8;   //情報の最大数

	InputAction();   //コンストラクタ
	~InputAction();   //デストラクタ

	void Init();   //初期化処理
	void Uninit();   //終了処理
	void Release();   //解放処理

	static InputAction* Get(int nId) { return InputAction::m_apInputAction[nId]; };   //取得処理

private:
	int m_nId;   //番号

	static InputAction* m_apInputAction[InputAction::MAX_DATA];   //情報
};

#endif // !_INPUT_ACTION_H_
