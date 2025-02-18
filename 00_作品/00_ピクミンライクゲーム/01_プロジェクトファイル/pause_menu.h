//========================================================================================================
//
//�|�[�Y���j���[�̏���[pause_menu.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _PAUSE_MENU_H_
#define _PAUSE_MENU_H_

#include "behavior.h"

//�|�[�Y���j���[�N���X
class PauseMenu : public Behavior   //(�e)����
{
public:
	const static D3DXVECTOR2 SIZE_MENU;

	typedef enum
	{
		IS_CONTINUE = 0,   //�R���e�j���[
		IS_REPLAY,   //���v���C
		IS_QUIT,   //�I��
		IS_MAX
	}MENU;   //���j���[

	//�R���X�g���N�^
	PauseMenu(Object* pObject) : Behavior(pObject)
	{
	}

	//�f�X�g���N�^
	~PauseMenu()
	{
	}

	void Init();   //������
	void Update();   //�X�V����

private:
};

#endif // !_PAUSE_MENU_H_