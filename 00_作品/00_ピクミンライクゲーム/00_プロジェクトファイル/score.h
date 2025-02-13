//========================================================================================================
//
//�X�R�A[score.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "behavior.h"

//�X�R�A�N���X
class Score : public Behavior   //(�e)����
{
public:
	//�X�R�A
	Score(Object* pObject) : Behavior(pObject)
	{
		//�����o�ϐ�������������
		this->m_nScore = 0;   //�X�R�A
	}

	//�f�X�g���N�^
	~Score() override
	{
	}

	void Init() override;   //������
	void Update() override;   //�X�V����
	void Add(int nValue);   //���Z����

private:
	int m_nScore;   //�X�R�A
};

#endif // !_SCORE_H_