//========================================================================================================
//
//�u���b�N�X�|�i�[�̏���[block_spawner.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _BLOCK_SPAWNER_H_
#define _BLOCK_SPAWNER_H_

#include "behavior.h"

//�u���b�N�X�|�i�[
class BlockSpawner : public Behavior   //(�e)����
{
public:
	static const int INTERVAL = 500;   //�C���^�[�o��
	static const int NUM_SPAWN = 10;   //1��̃X�|�[����

	//�R���X�g���N�^
	BlockSpawner(Object* pObject) : Behavior(pObject)
	{
		//�����o�ϐ�������������
		this->m_nCntSpawn = 0;
	}

	//�f�X�g���N�^
	~BlockSpawner() override
	{
	}

	void Init() override;   //����������
	void Update() override;   //�X�V����
	void Spawn(float fYAxis);   //�X�|�[������

private:
	int m_nCntSpawn;   //�X�|�[���J�E���^�[
};

#endif // !_BLOCK_SPAWNER_H_
