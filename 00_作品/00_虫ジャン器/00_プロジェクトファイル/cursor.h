//========================================================================================================
//
//�J�[�\���̏���[cursor.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _CORSOR_H_
#define _CORSOR_H_

#include "behavior.h"

//�J�[�\��
class Cursor : public Behavior
{
public:
	static const float INIT_RANGE;   //�����͈�
	static const float ADD_RANGE;   //�����l
	static const float MOVE_SPEED;   //�ړ����x
	static const float MAX_DISTANCE;   //�ő勗��

	//�R���X�g���N�^
	Cursor(Object* pObject) : Behavior(pObject)
	{
		//�����o�ϐ�������������
		this->m_pPlayer = nullptr;
		this->m_fRange = Cursor::INIT_RANGE;
	}

	//�f�X�g���N�^
	~Cursor() override
	{
	}

	void Init() override;   //����������
	void Update() override;   //�X�V����

	float GetRange() { return this->m_fRange; };   //�͈͂̎擾����

private:
	void Control();   //���쏈��

	Object* m_pPlayer;   //�v���C���[
	float m_fRange;   //�͈�
};

#endif // !_CORSOR_H_