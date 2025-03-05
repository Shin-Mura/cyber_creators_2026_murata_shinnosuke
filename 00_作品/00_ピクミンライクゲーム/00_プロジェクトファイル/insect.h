//========================================================================================================
//
//���̏���[insect.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _INSECT_H_
#define _INSECT_H_

#include "behavior.h"
#include "insect_state.h"

//��
class Insect : public Behavior
{
public:
	static const float MOVE_SPEED;   //�ړ���
	static const float MOVE_THROW;   //������ꂽ���̈ړ���

	//�R���X�g���N�^
	Insect(Object* pObject) : Behavior(pObject)
	{
		//�����o�ϐ�������������
		this->m_pState = new InsectNeutralState(pObject);
	}

	//�f�X�g���N�^
	~Insect() override
	{
		//��Ԃ�j������
		delete this->m_pState;
		this->m_pState = nullptr;
	}

	void Init() override;   //����������
	void Update() override;   //�X�V����
	void ChangeState(InsectState* state);   //��Ԃ̕ύX
	void Collision(Object* pObject, Physics::CONTACT contact) override { this->m_pState->Collision(pObject); };   //�Փˎ�
	void Call(Object* pPlayer) { this->m_pState->Call(pPlayer); };   //�Ă΂��
	void Throw(D3DXVECTOR3 posThrow, float fDireThrow, float fDistCursor) { this->m_pState->Throw(posThrow, fDireThrow, fDistCursor); };   //��������

private:
	InsectState* m_pState;   //���
};

#endif // !_INSECT_H_
