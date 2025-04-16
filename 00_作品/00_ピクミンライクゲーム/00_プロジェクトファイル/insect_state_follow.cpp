//========================================================================================================
//
//���̒Ǐ]��Ԃ̏���[insect_state_follow.cpp]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "insect_state.h"
#include "insect.h"
#include "benlib.h"
#include "transform.h"
#include "rigidbody.h"
#include "cursor.h"

//�ÓI�����o�ϐ�������������
const float InsectFollowState::DIS_PLAYER = 75.0f;   //�v���C���[�Ƃ̋���

//========================================================================================================
//�n���h��
//========================================================================================================
void InsectFollowState::Handle()
{
	//�v���C���[�Ƃ̋������m�F����
	D3DXVECTOR3 pos = this->GetIncect()->GetComponent<Transform>()->GetPos();   //���g�̈ʒu
	D3DXVECTOR3 posPlayer = this->pPlayer->GetComponent<Transform>()->GetPos();   //�v���C���[�̈ʒu
	float fDisPlayer = Benlib::Distance(pos, posPlayer).y;   //����
	if (fDisPlayer >= InsectFollowState::DIS_PLAYER)
	{
		//�v���C���[�ɒǏ]����
		float fDirePlayer = Benlib::Direction(pos, posPlayer).y;   //����
		this->GetIncect()->GetComponent<Transform>()->AddPos({ sinf(fDirePlayer) * Insect::MOVE_SPEED, 0.0f, cosf(fDirePlayer) * Insect::MOVE_SPEED });
	}
}

//========================================================================================================
//��������
//========================================================================================================
void InsectFollowState::Throw(D3DXVECTOR3 posThrow, float fDireThrow, float fDistCursor)
{
	//�����Ɉړ��ʂ����Z����
	float fRateDist = fDistCursor / Cursor::MAX_DISTANCE;
	D3DXVECTOR3 move = { sinf(fDireThrow) * (Insect::MOVE_THROW * fRateDist), (Insect::MOVE_THROW * fRateDist) * 0.5f, cosf(fDireThrow) * (Insect::MOVE_THROW * fRateDist) };
	this->GetIncect()->GetComponent<Rigidbody>()->SetMove(move);
	this->GetIncect()->GetComponent<Rigidbody>()->SetAir(true);
	this->GetIncect()->GetComponent<Transform>()->SetPos({ posThrow.x, posThrow.y, posThrow.z });   //�ʒu��ݒ�
	this->GetIncect()->GetComponent<Insect>()->ChangeState(new InsectThrowState(this->GetIncect()));   //��Ԃ𓊂����Ă�ɕύX
}