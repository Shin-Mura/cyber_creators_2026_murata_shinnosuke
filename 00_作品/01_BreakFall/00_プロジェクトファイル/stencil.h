//========================================================================================================
//
//�X�e���V���̏���[stencil.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _STENCIL_H_
#define _STENCIL_H_

#include "component.h"

//�l�p�`�N���X
class Stencil : public Component   //(�e)�����_�����O
{
public:
	//��r���@�̗�
	enum COMPARE
	{
		IS_ALWAYS = D3DCMP_ALWAYS,   //���
		IS_EQUAL = D3DCMP_EQUAL,   //���������
		IS_GREATEREQUAL = D3DCMP_GREATEREQUAL,   //�ȏ�ł����
	};

	//���i���̔��f���e�̗�
	enum PASS
	{
		IS_REPLACE = D3DSTENCILOP_REPLACE,   //�u������
		IS_KEEP = D3DSTENCILOP_KEEP,   //�L�[�v
		IS_INCR = D3DSTENCILOP_INCR,   //����
		IS_DECR = D3DSTENCILOP_DECR,   //����
	};

	//�R���X�g���N�^
	Stencil(Object* pObject, int nRef, Stencil::COMPARE compare, Stencil::PASS pass = Stencil::PASS::IS_KEEP) : Component(pObject)
	{
		//�����o�ϐ�������������
		this->m_nRef = nRef;   //��r�l
		this->m_compare = compare;   //��r���@
		this->m_pass = pass;   //���f���e
	}

	//�f�X�g���N�^
	~Stencil() override
	{
	}

	void Draw() override;   //�`�揈��

private:
	int m_nRef;   //�Q�ƒl
	Stencil::COMPARE m_compare;   //��r���@
	Stencil::PASS m_pass;   //���f���e
};

#endif // !_STENCIL_H_
