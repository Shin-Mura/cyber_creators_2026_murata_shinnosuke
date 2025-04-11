//=============================================================
//
// �Q�[���V�[�� [game.h]
// Author: Ito Kotaro
// 
//=============================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "scene.h"
#include "scripts/present_generator.h"

// �Q�[���V�[��
class CGameScene : public CScene
{
public:
	void Init() override;									// ������
	void Uninit() override;									// �I��
	void Update() override;								// �X�V
	void Draw() override;									// �`��
	void onGameOver();
	bool IsGameOver() { return m_isGameOver; }
	void onClear();
	bool IsClear() { return m_isClear; }
private:
	GameObject* m_pCamera;							// �J����
	GameObject* m_pPlayer;							// �v���C���[
	PresentGenerator* m_presentGenerator;		// �v���[���g�W�F�l���[�^
	bool m_isGameOver;									// �Q�[���I�[�o�[
	bool m_isClear;
	float m_gameTime;
};

#endif // !_GAME_H_
