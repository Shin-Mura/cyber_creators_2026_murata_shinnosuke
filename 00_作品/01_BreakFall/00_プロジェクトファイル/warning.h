//=======================================================================================================
//
//�x���̏���[warning.h]
// Author MurataShinnosuke
//
//=======================================================================================================
#ifndef _WARNING_H_
#define _WARNING_H_

#include "behavior.h"

//�x���̋���
class Warning : public Behavior   //�i�e�j����
{
public:
	static const float MOVE;   //�ړ���

	//�R���X�g���N�^
	Warning(Object* pObject) : Behavior(pObject)
	{
	}

	//�f�X�g���N�^
	~Warning()
	{
	}

	void Init() override;   //����������
	void Update() override;   //�X�V����

private:

};

#endif // !_WARNING_H_
