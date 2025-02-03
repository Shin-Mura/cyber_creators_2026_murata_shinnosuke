//=============================================================
//
// �r���{�[�h�R���|�[�l���g [billboard.h]
// Author: Ito Kotaro
//
//=============================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "component.h"

class CBillboard : public Component
{
public:
	void Init() override;
	void Uninit() override;
	void Set(float fWidth, float fHeight);
	void Draw() override;
	void BindTexture(LPDIRECT3DTEXTURE9 texture) { m_pTexture = texture; }
	void SetTexture(const std::string& sPath);
	void SetColor(D3DXCOLOR col);
	D3DXCOLOR GetColor() { return m_color; }
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture;				// �e�N�X�`��
	D3DXCOLOR m_color;									// �F
};

#endif // !_FIELD_H_
