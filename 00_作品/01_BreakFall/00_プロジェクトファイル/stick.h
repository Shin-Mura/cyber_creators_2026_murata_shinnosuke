//=======================================================================================================
//
//�_�̏���[stick.h]
// Author MurataShinnosuke
//
//=======================================================================================================
#ifndef _STICK_H_
#define _STICK_H_

#include "behavior.h"

//�_�̋���
class Stick : public Behavior   //�i�e�j����
{
public:
	static const float MOVE;   //�ړ���

	//�R���X�g���N�^
	Stick(Object* pObject) : Behavior(pObject)
	{
	}

	//�f�X�g���N�^
	~Stick()
	{
	}

	void Init() override;   //����������
	void Update() override;   //�X�V����

private:

};

#endif // !_STICK_H_
