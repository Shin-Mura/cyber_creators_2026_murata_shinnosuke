//========================================================================================================
//
//���j���[�̏���[menu.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _MENU_H_
#define _MENU_H_

#include "rendering.h"
#include "select_box.h"

//���j���[�N���X
class Menu : public Rendering   //(�e)�����_�����O
{
public:
	//�R���X�g���N�^
	Menu(Object* pObject) : Rendering(pObject)
	{
		//�����o�ϐ�������������
		this->m_vSelectBox.clear();
		this->m_nSelect = 0;
		this->m_fGap = 0.0f;   //�I�����̌���
		this->m_isDecide = false;
	}

	//�f�X�g���N�^
	~Menu() override
	{
	}

	void Init();   //����������
	void Uninit();   //�I������
	void Update();   //�X�V����
	void Draw();   //�`�揈��

	void SetSelectBox(int nNum);   //�I�����̐ݒ菈��
	void SetGap(float fGap) { this->m_fGap = fGap; };   //�I�����̌��Ԃ̐ݒ菈��

	bool GetDecide() { return this->m_isDecide; };   //����t���O�̎擾����
	int GetSelect() { return this->m_nSelect; };   //�I�𒆂̑I����

private:
	void Control();   //���쏈��

	std::vector<SelectBox*> m_vSelectBox;   //�I����
	int m_nSelect;   //�I�𒆂̑I����
	float m_fGap;   //�I�����̌���
	bool m_isDecide;   //����t���O
};

#endif // !_MENU_H_