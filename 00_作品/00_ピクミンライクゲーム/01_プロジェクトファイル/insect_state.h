//========================================================================================================
//
//���̏�ԏ���[insect_state.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _INSECT_STATE_H_
#define _INSECT_STATE_H_

#include "object.h"

//���̏��
class InsectState
{
public:
	//�R���X�g���N�^
	InsectState(Object* pInsect)
	{
		//�����o�ϐ�������������
		this->m_pInsect = pInsect;
	}

	//�f�X�g���N�^
	virtual ~InsectState()
	{
	}
	
	virtual void Handle() = 0;   //�n���h��
	virtual void Collision(Object* pObject) {};   //�Փˎ�
	virtual void Call(Object* pPlayer) {};   //�Ă΂��
	virtual void Throw(D3DXVECTOR3 posThrow, float fDireThrow, float fDistCursor) {};   //��������

protected:
	Object* GetIncect() { return this->m_pInsect; };   //���̎擾

private:
	Object* m_pInsect;   //��
};

//���̃j���[�g�������
class InsectNeutralState : public InsectState
{
public:
	static const float DIS_SEARCH;   //�T�[�`����

	//�R���X�g���N�^
	InsectNeutralState(Object* pInsect) : InsectState(pInsect)
	{
	}

	//�f�X�g���N�^
	~InsectNeutralState() override
	{
	}

	void Handle() override;   //�n���h��
	void Call(Object* pPlayer) override;   //�Ă�

private:
	void SeatchObject();   //�I�u�W�F�N�g��T��
	void SearchFruit();   //�t���[�c��T��
	void SearchObstacle();   //��Q����T��
};

//���̒Ǐ]���
class InsectFollowState : public InsectState
{
public:
	static const float DIS_PLAYER;   //�v���C���[�Ƃ̋���

	//�R���X�g���N�^
	InsectFollowState(Object* pInsect, Object* pPlayer) : InsectState(pInsect)
	{
		//�����o�ϐ�������������
		this->pPlayer = pPlayer;
	}

	//�f�X�g���N�^
	~InsectFollowState() override
	{
	}

	void Handle() override;   //�n���h��
	void Throw(D3DXVECTOR3 posThrow, float fDireThrow, float fDistCursor) override;   //��������

private:
	Object* pPlayer;   //�v���C���[
};

//���̓������Ă���
class InsectThrowState : public InsectState
{
public:
	//�R���X�g���N�^
	InsectThrowState(Object* pInsect) : InsectState(pInsect)
	{
	}

	//�f�X�g���N�^
	~InsectThrowState() override
	{
	}

	void Handle() override;   //�n���h��
	void Collision(Object* pObject) override;   //�Փˎ�

private:
};

//���̉^�����
class InsectCarryState : public InsectState
{
public:
	//�R���X�g���N�^
	InsectCarryState(Object* pInsect, Object* pCarry) : InsectState(pInsect)
	{
		//�����o�ϐ�������������
		this->m_pCarry = pCarry;   //�^���I�u�W�F�N�g
	}

	//�f�X�g���N�^
	~InsectCarryState() override
	{
	}

	void Handle() override;   //�n���h��
	void Call(Object* pPlayer) override;   //�Ă�

private:
	Object* m_pCarry;   //�^���I�u�W�F�N�g
};

//���̈ړ����
class InsectMoveState : public InsectState
{
public:
	//�R���X�g���N�^
	InsectMoveState(Object* pInsect, D3DXVECTOR3 posTarget) : InsectState(pInsect)
	{
		//�����o�ϐ�������������
		this->m_posTarget = posTarget;   //�ړ���
	}

	//�f�X�g���N�^
	~InsectMoveState() override
	{
	}

	void Handle() override;   //�n���h��
	void Call(Object* pPlayer) override;   //�Ă�
	void Collision(Object* pObject) override;

private:
	D3DXVECTOR3 m_posTarget;   //�ړ���
};

//���̍U�����
class InsectAttackState : public InsectState
{
public:
	static const int CNT_ATTACK;   //�U���J�E���^�[

	//�R���X�g���N�^
	InsectAttackState(Object* pInsect, Object* pObjAttack) : InsectState(pInsect)
	{
		//�����o�ϐ�������������
		this->m_pObjAttack = pObjAttack;   //�U�����̃I�u�W�F�N�g
		this->m_nCntAttack = CNT_ATTACK;   //�U���J�E���^�[
	}

	//�f�X�g���N�^
	~InsectAttackState() override
	{
	}

	void Handle() override;   //�n���h��
	void Call(Object* pPlayer) override;   //�Ă�

private:
	Object* m_pObjAttack;   //�U�����̃I�u�W�F�N�g
	int m_nCntAttack;   //�U���J�E���^�[
};

#endif // !_INSECT_STATE_H_