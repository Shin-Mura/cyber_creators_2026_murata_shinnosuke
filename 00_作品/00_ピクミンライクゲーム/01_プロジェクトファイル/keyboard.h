//********************************************************************************************************
//
//�L�[�{�[�h���͏���[input_keyboard.h]
// Author Murata Shinnosuke
//
//********************************************************************************************************
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include "input.h"

class Keyboard : public Input
{
public:
	static const int MAX = 256;   //�L�[�̐�

	Keyboard();   //�R���X�g���N�^
	~Keyboard();  //�f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;   //����������
	void Uninit() override;   //�I������
	void Update() override;   //�X�V����
	bool GetPress(int nKey);   //�v���X���̎擾����
	bool GetTrigger(int nKey);   //�g���K�[���̎擾����

private:
	BYTE m_aState[MAX];   //���
	BYTE m_aStateTrigger[MAX];   //�g���K�[���
};

#endif // !_KEYBOARD_H_
