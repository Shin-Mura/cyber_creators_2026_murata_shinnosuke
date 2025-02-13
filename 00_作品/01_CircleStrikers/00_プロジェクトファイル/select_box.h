//========================================================================================================
//
//�I�����̏���[select_box.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _SELECT_BOX_H_
#define _SELECT_BOX_H_

#include "main.h"

//�I�����N���X
class SelectBox
{
public:
	static float INIT_FADE;   //�t�F�[�h�̏����l

	SelectBox();   //�R���X�g���N�^
	~SelectBox();   //�f�X�g���N�^

	void Init();   //����������
	void Uninit();   //�I������
	void Update();   //�X�V����
	void Draw(LPDIRECT3DTEXTURE9 pTexture);   //�`�揈��
	void Select() { this->m_isSelect = true; };   //�I���t���O�̗��Ă鏈��

	//���Z�b�g����
	void Reset()
	{
		//���Z�b�g����
		this->m_color.a = 0.5f;
		this->m_fFade = SelectBox::INIT_FADE;
	}

	void SetPattern(int nPattern) { this->m_nPattern = nPattern; };
	void SetOder(int nOder) { this->m_nOder = nOder; };   //���Ԃ̐ݒ菈��
	void SetPos(D3DXVECTOR2 pos) { this->m_pos = pos; };   //�ʒu�̐ݒ菈��
	void SetSize(D3DXVECTOR2 size) { this->m_size = size; };   //�T�C�Y�̐ݒ菈��

	static SelectBox* Create(D3DXVECTOR2 pos, D3DXVECTOR2 size);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer;   //���_�o�b�t�@
	int m_nPattern;   //������
	int m_nOder;   //����
	D3DXVECTOR2 m_pos;   //�ʒu
	D3DXVECTOR2 m_size;   //�T�C�Y
	D3DXCOLOR m_color;   //�F
	bool m_isSelect;   //�I���t���O
	float m_fFade;   //�t�F�[�h�̒l
};

#endif // !_SELECT_BOX_H_