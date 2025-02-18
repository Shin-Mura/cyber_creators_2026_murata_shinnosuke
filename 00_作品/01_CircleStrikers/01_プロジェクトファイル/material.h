//==========================================================================================================
//
//�}�e���A���̏���[material.h]
// Author Murata Shinnosuke
//
//==========================================================================================================
#ifndef _MATERIAL_H_
#define _MATERIAL_H_

//�C���N���[�h
#include "component.h"

//�}�e���A��
class Material : public Component   //(�e)�R���|�[�l���g
{
public:
	//�R���X�g���N�^
	Material()
	{
		//�����o�ϐ�������������
		this->m_color = { 1.0f, 1.0f, 1.0f, 1.0f };   //�F
		this->m_pTexture = nullptr;   //�e�N�X�`��
	}

	//�f�X�g���N�^
	~Material()
	{
	}

	void SetColor(D3DXCOLOR color) { this->m_color = color; };   //�F�̐ݒ菈��
	void SetTexture(LPDIRECT3DTEXTURE9 pTexture) { this->m_pTexture = pTexture; };   //�e�N�X�`���̐ݒ菈��

	D3DXCOLOR GetColor() { return this->m_color; };   //�F�̎擾����
	LPDIRECT3DTEXTURE9 GetTexture() { return this->m_pTexture; };   //�e�N�X�`���̎擾����

	//��������
	static Material* Create(Object* pObject)
	{
		//�}�e���A���𐶐�����
		Material* pMaterial = new Material;

		//����ݒ肷��
		pMaterial->SetObject(pObject);

		//�}�e���A����Ԃ�
		return pMaterial;
	}

private:
	D3DXCOLOR m_color;   //�F
	LPDIRECT3DTEXTURE9 m_pTexture;   //�e�N�X�`��
};

#endif // !_MATERIAL_H_
