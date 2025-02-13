//========================================================================================================
//
//�^�C�g���V�[������[title.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "scene.h"
#include "camera.h"
#include "scene.h"

//�O���錾
class Menu;
//�^�C�g���V�[��
class Title : public Scene   //�i�e�j�V�[���N���X
{
public:
	Title();   //�R���X�g���N�^
	virtual ~Title();   //�f�X�g���N�^

	void Init() override;   //����������
	void Uninit() override;   //�I������
	void Update() override;   //�X�V����
	void Draw() override;   //�`�揈��

private:
	Menu* m_pMenu;   //���j���[
};

#endif // !_TITLE_H_
