//========================================================================================================
//
//���̏���[digit.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _DIGIT_H_
#define _DIGIT_H_

#include "main.h"

//���N���X
class Digit
{
public:
	//�R���X�g���N�^
	Digit()
	{
		//�����o�ϐ�������������
		this->m_pVtxBuffer = nullptr;
		this->m_nValue = 0;
		this->m_pos = { 0.0f, 0.0f };
		this->m_size = { 0.0f, 0.0f };
	}

	//�f�X�g���N�^
	~Digit()
	{
	}

	void Init();   //����������
	void Uninit();	  //�I������
	void Update();	  //�X�V����
	void Draw(LPDIRECT3DTEXTURE9 pTexutre);	//�`�揈��

	void SetValue(int nValue) { this->m_nValue = nValue; };   //���l�̐ݒ菈��
	void SetPos(D3DXVECTOR2 pos) { this->m_pos = pos; };   //�ʒu�̐ݒ菈��
	void SetSize(D3DXVECTOR2 size) { this->m_size = size; };   //�T�C�Y�̐ݒ菈��

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer;   //���_�o�b�t�@
	int m_nValue;   //���l
	D3DXVECTOR2 m_pos;   //�ʒu
	D3DXVECTOR2 m_size;   //�T�C�Y
};

#endif // !_DIGIT_H_