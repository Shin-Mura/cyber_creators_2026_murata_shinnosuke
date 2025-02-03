//========================================================================================================
//
//���D��T��[bfs.h]
// Author MurataShinnosuke
//
//========================================================================================================
#ifndef _BFS_H_
#define _BFS_H_

#include "main.h"
#include "waypoint.h"

//���D��T��
class Bfs
{
public:
	//�m�[�h�̍\����
	struct Node
	{
		Waypoint* pWaypoint;   //�E�F�C�|�C���g
		int nStep;   //�X�e�b�v
		int nFrom;   //�`�d
	};

	//�R���X�g���N�^
	Bfs()
	{
	}

	//�f�X�g���N�^
	~Bfs()
	{
	}

	static std::vector<D3DXVECTOR3> CalcRoute(Waypoint* pStart, Waypoint* pGoal);   //���[�g�̉��Z

private:
};

#endif // !_BFS_H_
