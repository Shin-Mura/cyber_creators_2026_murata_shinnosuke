//========================================================================================================
//
//�u���b�N�̏���[block.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "behavior.h"

//�u���b�N�N���X
class Block : public Behavior   //(�e)����
{
public:
	static const float MOVE;   //�ړ���
	static const D3DXVECTOR3 SIZE;   //�T�C�Y

	//�F�̗�
	enum COLOR
	{
		IS_RED = 0,   //��
		IS_BLUE,   //��
		IS_GREEN,   //��
		IS_YELLOW   //��
	};

	//�R���X�g���N�^
	Block(Object* pObject) : Behavior(pObject)
	{
		//�����o�ϐ�������������
		this->m_nHp = 1;
	}

	//�f�X�g���N�^
	~Block() override
	{
	}

	void Init() override;   //����������
	void Update() override;   //�X�V����
	void Hit();   //�q�b�g����

private:
	int m_nHp;   //�q�b�g�|�C���g
};

#endif // !_BLOCK_H_
