//===========================================================================================================
//
//���̓A�N�V�����̏���[input_action.h]
// Author Murata Shinnosuke
//
//===========================================================================================================
#ifndef _INPUT_ACTION_H_
#define _INPUT_ACTION_H_

//���̓A�N�V����
class InputAction
{
public:
	static const int MAX_DATA = 8;   //���̍ő吔

	InputAction();   //�R���X�g���N�^
	~InputAction();   //�f�X�g���N�^

	void Init();   //����������
	void Uninit();   //�I������
	void Release();   //�������

	static InputAction* Get(int nId) { return InputAction::m_apInputAction[nId]; };   //�擾����

private:
	int m_nId;   //�ԍ�

	static InputAction* m_apInputAction[InputAction::MAX_DATA];   //���
};

#endif // !_INPUT_ACTION_H_
