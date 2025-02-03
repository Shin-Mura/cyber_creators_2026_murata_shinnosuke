//========================================================================================================
//
//�G�t�F�N�g����[effect.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "object.h"

//�G�t�F�N�g�N���X
class Effect : public Object   //(�e)�I�u�W�F�N�g
{
public:
	Effect();   //�R���X�g���N�^
	~Effect() override;   //�f�X�g���N�^

	virtual void Init() override;   //����������
	virtual void Uninit() override;   //�I������
	virtual void Update() override;   //�X�V����
	virtual void Draw() override;   //�`�揈��

protected:
	void SetTexture(LPDIRECT3DTEXTURE9 pTexture) { this->m_pTexture = pTexture; };

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer;   //���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture;   //�e�N�X�`��
	D3DXMATRIX m_mtxWorld;   //���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;   //�ʒu
	D3DXCOLOR m_color;   //�F
	float m_fRadius;   //���a
};

#endif // !_EFFECT_H_
