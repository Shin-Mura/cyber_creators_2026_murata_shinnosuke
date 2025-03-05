//========================================================================================================
//
//�|�[�Y�̏���[pause.h]
// Auhtor Murata Shinnosuke
//
//========================================================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "object.h"
#include "menu.h"

//�|�[�Y�N���X
class Pause
{
public:
	//�R���X�g���N�^
	Pause()
	{
		//�����o�ϐ�������������
		this->m_isPause = false;
		this->m_pPauseMenu = nullptr;
	}

	//�f�X�g���N�^
	~Pause()
	{
	}

	void Init();   //����������
	void Uninit();   //�I������
	void Update();   //�X�V����
	void Draw();   //�`�揈��
	void SwitchPause();   //�|�[�Y�̐؂�ւ�����
	bool GetPause() { return this->m_isPause; };   //�|�[�Y�t���O�̎擾����
	Menu* GetMenu() { return this->m_pPauseMenu->GetComponent<Menu>(); };   //�I�𒆂̑I�����̎擾����

private:
	bool m_isPause;   //�|�[�Y�t���O
	Object* m_pPauseMenu;   //���j���[
};

#endif // !_PAUSE_H_