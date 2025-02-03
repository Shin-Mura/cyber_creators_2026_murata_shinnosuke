//========================================================================================================
//
//�̂̏���[body.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _TRAJECTORY_H_
#define _TRAJECTORY_H_

#include "behavior.h"

//�O�ՃN���X
class Body : public Behavior   //(�e)����
{
public:
	//�R���X�g���N�^
	Body(Object* pObject, Object* pPlayer) : Behavior(pObject)
	{
		//�����o�ϐ�������������
		this->m_pPlayer = pPlayer;
		this->m_nLife = 30;
	}

	//�f�X�g���N�^
	~Body() override
	{
	}

	void Init() override;   //����������
	void Update() override;   //�X�V����
	void Collision(Object* pObject, Physics::CONTACT contact) override;

private:
	Object* m_pPlayer;   //�v���C���[
	int m_nLife;   //����
};

#endif // !_TRAJECTORY_H_
