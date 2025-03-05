//========================================================================================================
//
//�|�[�Y�̏���[pause.h]
// Auhtor Murata Shinnosuke
//
//========================================================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

//�O���錾
class Menu;
//�|�[�Y�N���X
class Pause
{
public:
	Pause();   //�R���X�g���N�^
	~Pause();   //�f�X�g���N�^

	void Init();   //����������
	void Uninit();   //�I������
	void Update();   //�X�V����
	void Draw();   //�`�揈��
	void SwitchPause();   //�|�[�Y�̐؂�ւ�����

	bool GetPause() { return this->m_isPause; };   //�|�[�Y�t���O�̎擾����
	Menu* GetMenu() { return this->m_pMenu; };   //�I�𒆂̑I�����̎擾����

private:
	bool m_isPause;   //�|�[�Y�t���O
	Menu* m_pMenu;   //���j���[
};

#endif // !_PAUSE_H_