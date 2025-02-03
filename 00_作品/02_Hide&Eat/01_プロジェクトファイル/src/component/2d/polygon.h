//=============================================================
//
// �|���S���R���|�[�l���g [polygon.h]
// Author: Ito Kotaro
//
//=============================================================
#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "component.h"

// �|���S���N���X
class CPolygon : public Component
{
public:
	CPolygon();
	CPolygon(std::string sTexPath);
	virtual ~CPolygon() override;
	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void DrawUI() override;
	void SetColor(const D3DXCOLOR& color);
	void SetColor(const int& idx, const D3DXCOLOR& color);
	D3DXCOLOR GetColor() { return m_color; }
	void SetAnchorPoint(const D3DXVECTOR2& anchorPoint) { m_anchorPoint = anchorPoint; }
	void SetTexture(std::string sPath);
	void BindTexture(LPDIRECT3DTEXTURE9 tex) { m_pTexture = tex; }
	void SetReverse(bool bReverse) { m_bReverse = bReverse; }
	bool GetReverse() { return m_bReverse; }
	void SetAnim(int nSplit, int nTime);
private:
	void UpdateAnim();
	void UpdateVertex();
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_���
	LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`��
	D3DXVECTOR2 m_anchorPoint;					// �A���J�[�|�C���g
	D3DXCOLOR m_color;

	// �A�j���[�V����
	int m_nSplit;					// ������
	int m_nTime;					// ����
	DWORD m_nextTime;		// ���̎���
	int m_nAnimIdx;			// �C���f�b�N�X
	bool m_bReverse;			// ���]
};

#endif // !_IMAGE_H_
