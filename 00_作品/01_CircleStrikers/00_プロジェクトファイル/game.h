//========================================================================================================
//
//�Q�[���V�[������[game.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "scene.h"
#include "physics.h"
#include "pause.h"

//�Q�[���V�[���N���X
class Game : public Scene   //(�e)�V�[���N���X
{
public:
	//�R���X�g���N�^
	Game()
	{
		//�����o�ϐ�������������
		this->m_pPhysics = nullptr;
		this->m_pPause = nullptr;   //�|�[�Y
	}

	//�f�X�g���N�^
	virtual ~Game()
	{
	}

	void Init() override;   //����������
	void Uninit() override;   //�I������
	void Update() override;   //�X�V����
	void Draw() override;   //�`�揈��

	Pause* GetPause() { return this->m_pPause; };   //�|�[�Y�̎擾����
	Physics* GetPhysics() { return this->m_pPhysics; };   //�����蔻��̎擾

private:
	Pause* m_pPause;   //�|�[�Y
	Physics* m_pPhysics;   //����
};

#endif // !_GAME_H_
