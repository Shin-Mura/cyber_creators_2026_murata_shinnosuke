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
		IS_NULL = 0,
		IS_UP = XINPUT_GAMEPAD_DPAD_UP,
		IS_DOWN = XINPUT_GAMEPAD_DPAD_DOWN,
		IS_LEFT = XINPUT_GAMEPAD_DPAD_LEFT,
		IS_RIGHT = XINPUT_GAMEPAD_DPAD_RIGHT,
		IS_START = XINPUT_GAMEPAD_START,
		IS_BACK = XINPUT_GAMEPAD_BACK,
		IS_LT = XINPUT_GAMEPAD_LEFT_THUMB,
		IS_RT = XINPUT_GAMEPAD_RIGHT_THUMB,
		IS_LS = XINPUT_GAMEPAD_LEFT_SHOULDER,
		IS_RS = XINPUT_GAMEPAD_RIGHT_SHOULDER,
		IS_A = XINPUT_GAMEPAD_A,
		IS_B = XINPUT_GAMEPAD_B,
		IS_X = XINPUT_GAMEPAD_X,
		IS_Y = XINPUT_GAMEPAD_Y
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
