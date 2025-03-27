//========================================================================================================
//
//�G�t�F�N�g����[effect.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "component.h"

//�G�t�F�N�g
class Effect : public Component   //(�e)�R���|�[�l���g
{
public:
	//�R���X�g���N�^
	Effect(Object* pObject) : Component(pObject)
	{
		//�����o�ϐ�������������
		this->m_fRadius = 0.0f;   //���a
	}

	//�f�X�g���N�^
	~Effect() override
	{
	}

	void Init() override;   //����������
	void Update() override;   //�X�V����

private:
	float m_fRadius;   //���a
};

#endif // !_EFFECT_H_
