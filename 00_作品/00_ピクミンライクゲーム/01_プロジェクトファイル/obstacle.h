//========================================================================================================
//
//��Q���̏���[obstacle.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#include "behavior.h"

//��Q��
class Obstacle : public Behavior   //(�e)����
{
public:
	static const D3DXVECTOR3 SUB_SCALE;   //�g�嗦�̌�����

	//�R���X�g���N�^
	Obstacle(Object* pObject) : Behavior(pObject)
	{
		//�����o�ϐ�������������
		this->m_nHp = 5;   //�q�b�g�|�C���g
		this->m_isBreak = false;   //�j��t���O
	}

	//�f�X�g���N�^
	~Obstacle() override
	{
	}

	void Init() override;   //����������
	void Update() override;   //�X�V����
	void Hit(int nDamage);   //�q�b�g

	bool GetBreak() { return this->m_isBreak; };   //�j��t���O�̎擾

private:
	int m_nHp;   //�q�b�g�|�C���g
	bool m_isBreak;   //�j��t���O
};

#endif // !_OBSTACLE_H_
