//========================================================================================================
//
//�}�E�X���͏���[mouse.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _MOUSE_H_
#define _MOUSE_H_

#include "input.h"

//�}�E�X�N���X
class Mouse : public Input
{
public:
	Mouse();   //�R���X�g���N�^
	~Mouse();  //�f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;   //����������
	void Uninit() override;   //�I������
	void Update() override;   //�X�V����

	POINT GetPoint() { return this->m_point; };   //���W�̎擾����
	D3DXVECTOR2 GetMove() { return this->m_move; };   //�ړ��ʂ̎擾����

private:
	void ResetPoint();   //���W�̃��Z�b�g����

	POINT m_point;   //���W
	POINT m_pointOld;   //�O��̍��W
	D3DXVECTOR2 m_move;   //�ړ���
	bool m_isReset;   //�}�E�X�̃��Z�b�g�t���O
};

#endif // !_MOUSE_H_