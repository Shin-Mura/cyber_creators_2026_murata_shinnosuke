//=============================================================
//
// �^�C�g�� [title.h]
// Author: Ito Kotaro
//
//=============================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "scene.h"

// �^�C�g���V�[��
class CTitleScene : public CScene
{
public:
	void Init() override;						// ������
	void Uninit() override;						// �I��
	void Update() override;					// �X�V
	void Draw() override;						// �`��

	// �I����
	enum SELECT
	{
		START = 0,	// �X�^�[�g
		EXIT,				// �I��
		MAX
	};
private:
	void UpdateSelect();						// �I���̍X�V

	GameObject* m_tutorialImg;
	GameObject* m_pSelectObj[MAX];		// �I���I�u�W�F�N�g
	SELECT m_select;								// �I��
	bool m_tutorial;
};

#endif // !_TITLE_H_
