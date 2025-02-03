//========================================================================================================
//
//�����_�����O�̏���[rendering.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _RENDERING_H_
#define _RENDERING_H_

#include "component.h"

//�����_�����O
class Rendering : public Component
{
public:
	//�R���X�g���N�^
	Rendering(Object* pObject) : Component(pObject)
	{
		//�����o�ϐ�������������
		this->m_pTexture = nullptr;   //�e�N�X�`��
		this->m_color = { 1.0f, 1.0f, 1.0f, 1.0f };   //�F
	}

	//�f�X�g���N�^
	virtual ~Rendering() override
	{
	}

	virtual void Init() override = 0;   //����������
	virtual void Uninit() override = 0;   //�I������
	virtual void Update() override = 0;   //�X�V����
	virtual void Draw() override = 0;   //�`�揈��

	void SetColor(D3DXCOLOR color) { this->m_color = color; };   //�F�̐ݒ�
	void SetTexture(LPDIRECT3DTEXTURE9 pTexture) { this->m_pTexture = pTexture; };   //�e�N�X�`���̐ݒ�

	D3DXCOLOR GetColor() { return this->m_color; };   //�F�̎擾
	LPDIRECT3DTEXTURE9 GetTexture() { return this->m_pTexture; };   //�e�N�X�`���̎擾

private:
	LPDIRECT3DTEXTURE9 m_pTexture;   //�e�N�X�`��
	D3DXCOLOR m_color;   //�F
};

#endif // !_RENDERING_H_