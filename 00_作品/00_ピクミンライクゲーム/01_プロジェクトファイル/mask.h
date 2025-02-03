//========================================================================================================
//
//�}�X�N�̏���[mask.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _MASK_H_
#define _MASK_H_

#include "rendering.h"

//�}�X�N
class Mask : public Rendering   //(�e)�����_�����O
{
public:
	//�R���X�g���N�^
	Mask(Object* pObject) : Rendering(pObject)
	{
		//�����o�ϐ�������������
		this->m_pVtxBuffer = nullptr;
	}

	//�f�X�g���N�^
	~Mask() override
	{
	}

	void Init() override;   //����������
	void Uninit() override;   //�I������
	void Update() override;   //�X�V����
	void Draw() override;   //�`�揈��

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer;   //���_�o�b�t�@
};

#endif // !_MASK_H_
