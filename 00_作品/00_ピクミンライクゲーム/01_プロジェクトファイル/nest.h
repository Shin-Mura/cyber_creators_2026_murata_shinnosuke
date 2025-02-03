//========================================================================================================
//
//���̏���[nest.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _NEST_H_
#define _NEST_H_

#include "behavior.h"

//���N���X
class Nest : public Behavior   //(�e)����
{
public:
	static const int NUM_SPAWN;   //�X�|�[����
	static const float MOVE_SPAWN;   //�X�|�[���������̈ړ���

	//�R���X�g���N�^
	Nest(Object* pObject) : Behavior(pObject)
	{
	}

	//�f�X�g���N�^
	~Nest() override
	{
	}

	void Init() override;   //����������
	void Update() override;   //�X�V����
	void SpawnInsect();   //���̃X�|�[��
	void Collision(Object* pObject, Physics::CONTACT contact) override;   //�Փˎ�

private:
};

#endif // !_BAKET_H_
