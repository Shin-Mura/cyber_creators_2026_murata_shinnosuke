//========================================================================================================
//
//���ʂ̏���[plane.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _PLANE_H_
#define _PLANE_H_

#include "rendering.h"
#include "manager.h"

//���ʃN���X
class Plane : public Rendering   //(�e)�����_�����O
{
public:
	static const D3DXVECTOR2 BASE_SIZE;   //��{�T�C�Y

	//�R���X�g���N�^
	Plane(Object* pObject) : Rendering(pObject)
	{
		//�����o�ϐ�������������
		this->m_pVtxBuffer = nullptr;   //�o�b�t�@
	}

	//�f�X�g���N�^
	virtual ~Plane() override
	{
	}

	void Init() override;   //����������
	void Uninit() override;   //�I������
	virtual void Draw() override;   //�`�揈��
	virtual void Update() override = 0;   //�X�V����

protected:
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuffer() { return this->m_pVtxBuffer; };   //���_�o�b�t�@�̎擾

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer;   //���_�o�b�t�@
};

//XZ�����̕���
class PlaneXZ : public Plane
{
public:
	//�R���X�g���N�^
	PlaneXZ(Object* pObject) : Plane(pObject)
	{
	}

	//�f�X�g���N�^
	~PlaneXZ() override
	{
	}

	//�X�V����
	void Update() override;
};

//Y�����̕���
class PlaneY : public Plane
{
public:
	//�R���X�g���N�^
	PlaneY(Object* pObject) : Plane(pObject)
	{
	}

	//�f�X�g���N�^
	virtual ~PlaneY() override
	{
	}

	//�X�V����
	void Update() override;
};

//�r���{�[�h
class Billboard : public PlaneY
{
public:
	//�R���X�g���N�^
	Billboard(Object* pObject) : PlaneY(pObject)
	{
		//�����o�ϐ�������������
		this->m_isYAxis = false;   //Y��
		this->m_isMultiply = false;   //���Z����
	}

	//�f�X�g���N�^
	~Billboard() override
	{
	}

	void Draw() override;

protected:
	void YAxis() { this->m_isYAxis = true; };   //Y���r���{�[�h
	void Multiply() { this->m_isMultiply = true; };   //���Z����

private:
	bool m_isYAxis;   //Y��
	bool m_isMultiply;   //���Z����
};

#endif // !_PLANE_H_
