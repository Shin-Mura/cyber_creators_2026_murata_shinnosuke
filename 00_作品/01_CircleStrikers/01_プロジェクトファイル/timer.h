//========================================================================================================
//
//�^�C�}�[�̏���[timer.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _TIMER_H_
#define _TIMER_H_

#include "behavior.h"

//�^�C�}�[�N���X
class Timer : public Behavior   //(�e)����
{
public:
	static const int START_TIMER;   //�J�n�^�C�}�[
	static const D3DXVECTOR2 SIZE;   //�T�C�Y

	//�R���X�g���N�^
	Timer(Object* pObject) : Behavior(pObject)
	{
		//�����o�ϐ�������������
		this->m_nTimer = START_TIMER;   //�^�C�}�[
		this->m_dwTime = timeGetTime() / 1000;   //����
	}

	//�f�X�g���N�^
	~Timer() override
	{

	}

	void Init() override;   //������
	void Update() override;   //�X�V����

private:
	DWORD m_dwTime;   //����
	int m_nTimer;   //�^�C�}�[
};

#endif // !_TIMER_H_