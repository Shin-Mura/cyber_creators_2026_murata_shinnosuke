//========================================================================================================
//
//�^�C�g�����j���[�̏���[title_menu.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _TITLE_MENU_
#define _TITLE_MENU_

#include "behavior.h"

//�^�C�g�����j���[�N���X
class TitleMenu : public Behavior   //(�e)����
{
public:
	const static D3DXVECTOR2 SIZE_MENU;   //���j���[�̃T�C�Y

	typedef enum
	{
		IS_START = 0,
		IS_RANKING,
	    IS_MAX
	}MENU;   //���j���[

	//�R���X�g���N�^
	TitleMenu(Object* pObject) : Behavior(pObject)
	{
	}

	//�f�X�g���N�^
	~TitleMenu()
	{
	}

	void Init() override;   //������
	void Update() override;   //�X�V����

private:
};

#endif // !_TITLE_MENU_