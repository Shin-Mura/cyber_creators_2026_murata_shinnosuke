//========================================================================================================
//
//�E�F�C�|�C���g�̏���[waypoint.h]
// Author MurataShinnosuke
//
//========================================================================================================
#ifndef _WAYPOINT_H_
#define _WAYPOINT_H_

#include "main.h"

//�E�F�C�|�C���g
class Waypoint
{
public:
	//�R���X�g���N�^
	Waypoint(D3DXVECTOR3 pos)
	{
		//�����o�ϐ�������������
		this->m_pos = pos;   //�ʒu
		this->m_vConnect.clear();   //�q�����Ă�|�C���g

		//�R���e�i�ɕۑ�����
		Waypoint::m_vWaypoint.push_back(this);
	}

	//�f�X�g���N�^
	~Waypoint()
	{
	}

	void AddConnect(Waypoint* pWaypoint) { this->m_vConnect.push_back(pWaypoint); };   //�q�����Ă�|�C���g�̒ǉ�

	D3DXVECTOR3 GetPos() { return this->m_pos; };   //�ʒu�̎擾
	std::vector<Waypoint*> GetConnect() { return this->m_vConnect; };   //�q�����Ă�|�C���g�̎擾

	//���Ԃ̎擾
	int GetOder() 
	{
		//�R���e�i�̐����J��Ԃ�
		for (unsigned int i = 0; i < Waypoint::m_vWaypoint.size(); i++)
		{
			//�E�F�C�|�C���g���m�F����
			if (Waypoint::m_vWaypoint[i] == this)
			{
				//���Ԃ�Ԃ�
				return i;
			}
		}

		//-1��Ԃ�
		return -1;
	}

	//�ꊇ���
	static void ReleaseAll() 
	{
		//�E�F�C�|�C���g�̐����J��Ԃ�
		for (unsigned int i = 0; i < Waypoint::m_vWaypoint.size(); i++)
		{
			//�E�F�C�|�C���g��j������
			delete Waypoint::m_vWaypoint[i];
		}

		//�R���e�i�̃N���A����
		Waypoint::m_vWaypoint.clear();
	}

	static std::vector<Waypoint*> Get() { return Waypoint::m_vWaypoint; };   //�R���e�i�̎擾

private:
	D3DXVECTOR3 m_pos;   //�ʒu
	std::vector<Waypoint*> m_vConnect;   //�q�����Ă�|�C���g

	static std::vector<Waypoint*> m_vWaypoint;   //�R���e�i
};

#endif // !_WAYPOINT_H_
