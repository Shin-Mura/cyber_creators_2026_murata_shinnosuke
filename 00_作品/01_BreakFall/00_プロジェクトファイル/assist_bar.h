//=======================================================================================================
//
//�A�V�X�g�_�̏���[assist_bar.h]
// Author MurataShinnosuke
//
//=======================================================================================================
#ifndef _ASSIST_BAR_H_
#define _ASSIST_BAR_H_

#include "behavior.h"

//�A�V�X�g�_�̋���
class AssistBar : public Behavior   //�i�e�j����
{
public:
	//�R���X�g���N�^
	AssistBar(Object* pObject) : Behavior(pObject)
	{
		this->m_nCntLife = 900;
	}

	//�f�X�g���N�^
	~AssistBar()
	{
	}

	void Init() override;   //����������
	void Update() override;   //�X�V����

private:
	int m_nCntLife;
};

#endif // !_ASSIST_BAR_H_
