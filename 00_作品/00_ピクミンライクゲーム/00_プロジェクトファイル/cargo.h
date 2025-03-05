//========================================================================================================
//
//�ݕ��̏���[cargo.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _CARGO_H_
#define _CARGO_H_

#include "behavior.h"
#include "waypoint.h"

//�t���[�c�N���X
class Cargo : public Behavior   //(�e)����
{
public:
	static const int FRAME_COLLECT;   //����܂ł̃t���[��
	static const float DIRE_WAYPOINT;   //�E�F�C�|�C���g�܂ł̋���
	static const float MOVE;   //�ړ���
	static const float SUB_SCALE;   //�g�嗦�̌�����

	//�R���X�g���N�^
	Cargo(Object* pObject, int nWeight) : Behavior(pObject)
	{
		//�����o�ϐ�������������
		this->m_nWeight = nWeight;   //�d��
		this->m_nLiftPower = 0;   //�����グ���
		this->m_isLift = false;   //�����グ���Ă�t���O
		this->m_pWaypointGoal = nullptr;
		this->m_isCollect = false;   //����t���O
		this->m_nFrameCollect = 0;   //����t���[��
		this->m_vRoute.clear();   //���[�g
		this->m_nStep = 0;   //�X�e�b�v
	}

	//�f�X�g���N�^
	~Cargo() override
	{
	}

	void Init() override;   //����������
	void Update() override;   //�X�V����
	void Collect();   //���
	void AddILiftPower(int nAddPower) { this->m_nLiftPower += nAddPower; };   //�����グ��͂̉��Z

	void SetWaypointGoal(Waypoint* Waypoint) { this->m_pWaypointGoal = Waypoint; };   //�����̈ʒu�̐ݒ�

	int GetWeight() { return this->m_nWeight; };   //�d���̎擾
	bool GetLift() { return this->m_isLift; };   //�����グ���Ă�t���O�̎擾
	bool GetCollect() { return this->m_isCollect; };   //����t���O

private:
	int m_nWeight;   //�d��
	int m_nLiftPower;   //�����グ���
	bool m_isLift;   //�����グ���Ă�t���O
	Waypoint* m_pWaypointGoal;   //�E�F�C�|�C���g
	bool m_isCollect;   //����t���O
	int m_nFrameCollect;   //����t���[��
	std::vector<D3DXVECTOR3> m_vRoute;   //���[�g
	int m_nStep;   //�X�e�b�v
};

#endif // !_CARGO_H_
