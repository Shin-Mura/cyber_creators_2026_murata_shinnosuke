//========================================================================================================
//
//���D��T��[bfs.cpp]
// Author MurataShinnosuke
//
//========================================================================================================
#include "bfs.h"

//========================================================================================================
//���[�g�̉��Z
//========================================================================================================
std::vector<D3DXVECTOR3> Bfs::CalcRoute(Waypoint* pStart, Waypoint* pGoal)
{
    //�E�F�C�|�C���g���擾����
    std::vector<Waypoint*> vWaypoint = Waypoint::Get();
    std::vector<Bfs::Node> vNode(vWaypoint.size(), { nullptr, -1, -1 });   //�m�[�h
    for (unsigned int i = 0; i < vWaypoint.size(); i++)
    {
        //�m�[�h�ɃE�F�C�|�C���g��ۑ�����
        vNode[i].pWaypoint = vWaypoint[i];
    }

    //�X�^�[�g�E�F�C�|�C���g�𔭌������m�[�h�̃R���e�i�ɕۑ�����
    std::vector<Bfs::Node> vNodeFind = { {pStart, 0, -1} };

    //���������m�[�h����ɂȂ�܂ŌJ��Ԃ�
    while (!vNodeFind.empty())
    {
        //�S�[���E�F�C�|�C���g���m�F����
        if (vNodeFind.front().pWaypoint == pGoal)
        {//�S�[���E�F�C�|�C���g�̏ꍇ
            //���[�v�𔲂��o��
            break;
        }

        //���������m�[�h�̃R���e�i�̐擪����菜��
        Bfs::Node nodeFront = vNodeFind.front();
        vNodeFind.erase(vNodeFind.begin());

        //�q�����Ă�E�F�C�|�C���g���擾����
        std::vector<Waypoint*> vWaypointConnect = nodeFront.pWaypoint->GetConnect();
        for (unsigned int i = 0; i < vWaypointConnect.size(); i++)
        {
            //���ɔ������Ă��邩�m�F����
            int nOder = vWaypointConnect[i]->GetOder();
            if (vNode[nOder].nStep != -1)
            {//�������Ă���ꍇ
                //���̃��[�v�Ɉڍs����
                continue;
            }

            //�m�[�h�ɂ𔭌�������Ԃɂ���
            vNode[nOder].nStep = nodeFront.nStep + 1;
            vNode[nOder].nFrom = nodeFront.pWaypoint->GetOder();

            //�q�����Ă�m�[�h�𔭌������m�[�h�̃R���e�i�ɕۑ�����
            vNodeFind.push_back({ vWaypointConnect[i], nodeFront.nStep + 1, nodeFront.pWaypoint->GetOder() });
        }
    }

    //�Ԃ��p�̈ʒu�̃R���e�i�ɃS�[���̈ʒu��ۑ�����
    std::vector<D3DXVECTOR3> vPosRoute;
    vPosRoute.push_back(vNodeFind.front().pWaypoint->GetPos());
    int nId = vNodeFind.front().nFrom;   //���̔ԍ���ۑ�����

    //�J��Ԃ�
    while (1)
    {
        //�Ԃ��p�̃R���e�i�Ɍo�R�E�F�C�|�C���g�̈ʒu��ۑ�����
        vPosRoute.insert(vPosRoute.begin(), vNode[nId].pWaypoint->GetPos());
        if (vNode[nId].pWaypoint == pStart)
        {//�X�^�[�g�n�_�̏ꍇ
            //���[�v�𔲂��o��
            break;
        }

        //���̔ԍ���ۑ�����
        nId = vNode[nId].nFrom;
    }

	//���[�g��Ԃ�
	return vPosRoute;
}