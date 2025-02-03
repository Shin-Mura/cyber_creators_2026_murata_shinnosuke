//========================================================================================================
//
//�Q�[���}�l�[�W���[�̏���[game_manager.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include "behavior.h"

//�O���錾
class Player;   //�v���C���[
//�Q�[���}�l�[�W���[
class GameManager : public Behavior   //(�e)����
{
public:
	//�R���X�g���N�^
	GameManager(Object* pObject) : Behavior(pObject)
	{
		//�����o�ϐ�������������
		this->m_isStart = false;   //�X�^�[�g�t���O
		this->m_vPlayer.clear();   //�v���C���[�̃R���e�i
	}

	//�f�X�g���N�^
	~GameManager() override
	{
	}

	void Init() override;   //������
	void Update() override;   //�X�V
	void SetPlayer(Player* pPlayer) { this->m_vPlayer.push_back(pPlayer); };

private:
	std::vector<Player*> m_vPlayer;   //�v���C���[
	bool m_isStart;   //�X�^�[�g�t���O
};

#endif // !_GAME_MANAGER_H_
