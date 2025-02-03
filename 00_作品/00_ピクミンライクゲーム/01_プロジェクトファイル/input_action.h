//===========================================================================================================
//
//���̓A�N�V�����̏���[input_action.h]
// Author Murata Shinnosuke
//
//===========================================================================================================
#ifndef _INPUT_ACTION_H_
#define _INPUT_ACTION_H_

#include "main.h"

//���̓A�N�V����
class InputAction
{
public:
	//�R���X�g���N�^
	InputAction(std::string sName)
	{
		//�����o�ϐ�������������
		this->m_sName = sName;
	}

	//�f�X�g���N�^
	~InputAction()
	{
	}

	void Init();   //����������
	void Uninit();   //�I������

	static InputAction* Get(int nId) { return InputAction::m_vInputAction[nId]; };   //�擾

private:
	std::string m_sName;   //���O

	static std::vector<InputAction*> m_vInputAction;
};

#endif // !_INPUT_ACTION_H_
