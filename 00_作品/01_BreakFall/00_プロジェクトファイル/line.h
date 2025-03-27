//==========================================================================================================
//
//���̏���[line.h]
// Author Murata Shinnosuke
//
//==========================================================================================================
#ifndef _LINE_H_
#define _LINE_H_

#include "main.h"

//��
class Line
{
public:
	//�R���X�g���N�^
	Line()
	{
		//�����o�ϐ�������������
		D3DXMatrixIdentity(&m_mtxWorld);
		this->m_pVtxBuffer = nullptr;
		this->m_posStart = { 0.0f, 0.0f, 0.0f };
		this->m_posEnd = { 0.0f, 0.0f, 0.0f };
		this->m_color = { 1.0f, 1.0f, 1.0f, 1.0f };
	}

	//�f�X�g���N�^
	~Line()
	{
	}

	void Init();   //����������
	void Uninit();   //�I������
	void Update();   //�X�V����
	void Draw();   //�`�揈��

	//�ݒ菈��
	void SetPos(D3DXVECTOR3 posStart, D3DXVECTOR3 posEnd) { this->m_posStart = posStart, this->m_posEnd = posEnd; };   //�n�_�ƏI�_

	//��������
	static Line* Create(D3DXCOLOR color)
	{
		//���𐶐�����
		Line* pLine = new Line;

		//����ݒ肷��
		pLine->m_color = color;   //�F

		//����Ԃ�
		return pLine;
	}

private:
	D3DXMATRIX m_mtxWorld;   //���[���h�}�g���b�N�X
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer;   //���_�o�b�t�@
	D3DXVECTOR3 m_posStart;   //�n�_
	D3DXVECTOR3 m_posEnd;   //�I�_
	D3DXCOLOR m_color;   //�F
};

#endif // !_LINE_H_