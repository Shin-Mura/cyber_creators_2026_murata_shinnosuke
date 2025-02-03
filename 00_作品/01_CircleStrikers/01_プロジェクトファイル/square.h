//========================================================================================================
//
//�l�p�`�̏���[object2D.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _SQUARE_H_
#define _SQUARE_H_

#include "rendering.h"

//�l�p�`�N���X
class Square : public Rendering   //(�e)�����_�����O
{
public:
	//�R���X�g���N�^
	Square(Object* pObject) : Rendering(pObject)
	{
		//�����o�ϐ�������������
		this->m_pVtxBuffer = nullptr;
	}

	//�f�X�g���N�^
	~Square() override
	{
	}

	void Init() override;   //����������
	void Uninit() override;   //�I������
	void Update() override;   //�X�V����
	void Draw() override;   //�`�揈��

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer;   //���_�o�b�t�@
};

#endif // !_SQUARE_H_
