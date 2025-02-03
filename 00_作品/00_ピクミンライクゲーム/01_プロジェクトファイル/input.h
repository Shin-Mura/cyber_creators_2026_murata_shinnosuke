//========================================================================================================
//
//���͏���[input.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

class Input
{
public:
	Input();   //�R���X�g���N�^
	~Input();   //�f�X�g���N�^

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);   //����������
	virtual void Uninit();   //�I������
	virtual void Update() = 0;   //�X�V����

protected:
	LPDIRECTINPUTDEVICE8 m_pDevice;   //�f�o�C�X
	static LPDIRECTINPUT8 m_pInput;   //����
};

#endif // !_INPUT_H_
