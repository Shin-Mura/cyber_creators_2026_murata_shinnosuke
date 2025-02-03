//========================================================================================================
//
//�W���C�p�b�h���͏���[input_joypad.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _JOYPAD_H_
#define _JOYPAD_H_

#include "input.h"

//�W���C�p�b�h�N���X
class Joypad : public Input
{
public:
	static const int MAX_NUM = 4;   //�W���C�p�b�h�̍ő吔

	typedef enum
	{
		JOYKEY_NULL = 0,
		JOYKEY_UP = XINPUT_GAMEPAD_DPAD_UP,
		JOYKEY_DOWN = XINPUT_GAMEPAD_DPAD_DOWN,
		JOYKEY_LEFT = XINPUT_GAMEPAD_DPAD_LEFT,
		JOYKEY_RIGHT = XINPUT_GAMEPAD_DPAD_RIGHT,
		JOYKEY_START = XINPUT_GAMEPAD_START,
		JOYKEY_BACK = XINPUT_GAMEPAD_BACK,
		JOYKEY_LT = XINPUT_GAMEPAD_LEFT_THUMB,
		JOYKEY_RT = XINPUT_GAMEPAD_RIGHT_THUMB,
		JOYKEY_LS = XINPUT_GAMEPAD_LEFT_SHOULDER,
		JOYKEY_RS = XINPUT_GAMEPAD_RIGHT_SHOULDER,
		JOYKEY_A = XINPUT_GAMEPAD_A,
		JOYKEY_B = XINPUT_GAMEPAD_B,
		JOYKEY_X = XINPUT_GAMEPAD_X,
		JOYKEY_Y = XINPUT_GAMEPAD_Y
	}JOYKEY;   //�W���C�p�b�h

	Joypad();   //�R���X�g���N�^
	~Joypad();  //�f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;   //����������
	void Uninit() override;   //�I������
	void Update() override;   //�X�V����
	bool GetPress(JOYKEY key, int nId);   //�v���X���̎擾����
	bool GetTrigger(JOYKEY key, int nId);   //�g���K�[���̎擾����
	XINPUT_STATE* GetState(int nId);   //�W���C�p�b�h��Ԃ̎擾����

private:
	XINPUT_STATE m_aState[MAX_NUM];   //���
	XINPUT_STATE m_aStateTrigger[MAX_NUM];   //�g���K�[���
	bool m_isButtonPressed[MAX_NUM];   //�����ꂽ���ǂ���
};

#endif // !_JOYPAD_H_
