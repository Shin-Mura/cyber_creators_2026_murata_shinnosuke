//========================================================================================================
//
//�ݕ��̏���[cargo.cpp]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "cargo.h"
#include "benlib.h"
#include "insect.h"
#include "insect_state.h"
#include "transform.h"
#include "rigidbody.h"
#include "bfs.h"

//�ÓI�����o�ϐ�������������
const int Cargo::FRAME_COLLECT = 60;   //����܂ł̃t���[��
const float Cargo::DIRE_WAYPOINT = 10.0f;   //�E�F�C�|�C���g�ɓ��B�����Ɣ��f���鋗��
const float Cargo::MOVE = 0.5f;   //�ړ���
const float Cargo::SUB_SCALE = 0.05f;   //�g�嗦�̌�����

//========================================================================================================
//����������
//========================================================================================================
void Cargo::Init()
{

}

//========================================================================================================
//�X�V����
//========================================================================================================
void Cargo::Update()
{
	//����t���O���m�F����
	if (this->m_isCollect)
	{
		//�g�嗦������������
		Transform* pTransform = this->GetObj()->GetComponent<Transform>();
		D3DXVECTOR3 scale = pTransform->GetScale();
		scale -= {Cargo::SUB_SCALE, Cargo::SUB_SCALE, Cargo::SUB_SCALE};
		if (scale.x <= 0.0f)
		{//0�ɂȂ����ꍇ
			//���S�t���O�𗧂Ă�
			this->GetObj()->Death();
			return;
		}

		//�g�嗦��ݒ肷��
		pTransform->SetScale(scale);
		return;
	}

	//�����グ��͂Əd�����m�F����
	if (this->m_nLiftPower >= this->m_nWeight)
	{
		//�����グ���Ă�t���O�𗧂Ă�
		this->m_isLift = true;

		//���[�g���m�F����
		if (this->m_vRoute.empty())
		{//���[�g���ݒ肳��Ă��Ȃ��ꍇ
			//1�ԋ߂��E�F�C�|�C���g���Z�o����
			std::vector<Waypoint*> vWaypoint = Waypoint::Get();
			float fDistMin = -1.0f;   //�ŒZ����
			Waypoint* pWaypointMin = nullptr;   //�ŒZ�E�F�C�|�C���g
			for (unsigned int i = 0; i < vWaypoint.size(); i++)
			{
				//�������m�F����
				float fDist = Benlib::Distance(this->GetComponent<Transform>()->GetPos(), vWaypoint[i]->GetPos()).y;
				if (fDistMin > fDist || fDistMin == -1.0f)
				{//�ۑ�����Ă��ŒZ�������Z���ꍇ
					//�ŒZ�������㏑������
					fDistMin = fDist;
					pWaypointMin = vWaypoint[i];
				}
			}

			//�����܂ł̃��[�g���v�Z����
			this->m_vRoute = Bfs::CalcRoute(pWaypointMin, this->m_pWaypointGoal);
			this->m_nStep = 0;
		}

		//�X�e�b�v���m�F����
		if ((unsigned int)this->m_nStep < this->m_vRoute.size())
		{//���[�g�̃R���e�i��菬�����ꍇ
			//�����グ���Ă�͂��m�F����
			float fMove = Cargo::MOVE;
			if (this->m_nLiftPower >= (this->m_nWeight * 2))
			{//�����グ���Ă�͂����ʂ�2�{�̏ꍇ
				//�ړ��ʂ�{����������
				fMove *= 1.5;
			}

			//�E�F�C�|�C���g�Ɍ������Ĉړ�����
			float fDire = Benlib::Direction(this->GetComponent<Transform>()->GetPos(), this->m_vRoute[this->m_nStep]).y;
			this->GetComponent<Rigidbody>()->AddMove({ sinf(fDire) * fMove, 0.0f, cosf(fDire) * fMove });
			if (Benlib::Distance(this->GetComponent<Transform>()->GetPos(), this->m_vRoute[this->m_nStep]).y <= Cargo::DIRE_WAYPOINT)
			{//�E�F�C�|�C���g�ɓ��B�����ꍇ
				//���̃X�e�b�v����
				this->m_nStep++;
			}
		}
	}
	else
	{
		//�����グ���Ă�t���O�����낷
		this->m_isLift = false;
	}
}

//========================================================================================================
//���
//========================================================================================================
void Cargo::Collect()
{
	//����t���O�𗧂Ă�
	this->m_isCollect = true;
}