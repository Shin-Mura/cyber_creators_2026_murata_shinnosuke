//========================================================================================================
//
//���̐�[insect_num.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _NUM_INSECT_H_
#define _NUM_INSECT_H_

#include "behavior.h"

//���̐��N���X
class NumInsect : public Behavior   //(�e)����
{
public:
	//���̐�
	NumInsect(Object* pObject) : Behavior(pObject)
	{
		//�����o�ϐ�������������
		this->m_nNumInsect = 0;   //���̐�
	}

	//�f�X�g���N�^
	~NumInsect() override
	{
	}

	void Init() override;   //������
	void Update() override;   //�X�V����
	void SetNumInsect(int nNum);   //���̐��̐ݒ�

private:
	int m_nNumInsect;   //���̐�
};

#endif // !_NUM_INSECT_H_