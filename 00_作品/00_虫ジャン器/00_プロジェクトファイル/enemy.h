//=====================================================================================================================
//
//�G�̏���[enemy.h]
// Author MurataShinosuke
//
//=====================================================================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "behavior.h"

//�G
class Enemy : public Behavior   //(�e)����
{
public:
	//�R���X�g���N�^
	Enemy(Object* pObject) : Behavior(pObject)
	{
	}

	//�f�X�g���N�^
	~Enemy()
	{
	}

	void Init();   //������
	void Update();   //�X�V

private:

};

#endif // !_ENEMY_H_
