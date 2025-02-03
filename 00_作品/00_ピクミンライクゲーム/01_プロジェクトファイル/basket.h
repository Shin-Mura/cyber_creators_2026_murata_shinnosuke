//========================================================================================================
//
//�����̏���[basket.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _BASKET_H_
#define _BASKET_H_

#include "behavior.h"

//�����N���X
class Basket : public Behavior   //(�e)����
{
public:
	//�R���X�g���N�^
	Basket(Object* pObject) : Behavior(pObject)
	{
		//�����o�ϐ�������������
		this->m_pScore = nullptr;
	}

	//�f�X�g���N�^
	~Basket() override
	{
	}

	void Init() override;   //����������
	void Update() override;   //�X�V����
	void Collision(Object* pObject, Physics::CONTACT contact) override;   //�Փˎ�

private:
	Object* m_pScore;
};

#endif // !_BAKET_H_
