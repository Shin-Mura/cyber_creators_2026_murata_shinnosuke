//=============================================================
//
// �o�[ [bar.h]
// Author: Ito Kotaro
//
//=============================================================
#ifndef _BAR_H_
#define _BAR_H_

#include "component.h"
#include "component/2d/polygon.h"

// �o�[
class CBar : public Component
{
public:
	void Init() override;
	void Update() override;

	CPolygon* GetPolyBG() { return m_pBgObj->GetComponent<CPolygon>(); }
	CPolygon* GetPolyBar() { return m_pBarObj->GetComponent<CPolygon>(); }
	void SetProgress(const float& fProgress) { m_fBarProgress = fProgress; }
	void SetLength(const float& length) { m_fBarLength = length; }
	void SetBold(const float& bold) { m_fBarBold = bold; }

	static const float DEFAULT_BAR_LENGTH;	// �f�t�H���g�̃o�[�̒���
	static const float DEFAULT_BAR_BOLD;		// �f�t�H���g�̃o�[�̑���
private:
	float m_fBarLength;
	float m_fBarBold;
	float m_fBarProgress;

	GameObject* m_pBgObj;
	GameObject* m_pBarObj;
};

// �v���O���X�o�[
class CProgressBar : public Component
{
public:
	CProgressBar(const int& nNumBar);
	void Init() override;
	void Uninit() override;
	void Update() override;
	void SetProgress(const float& fProgress) { m_fBarProgress = fProgress; }
	void SetLength(const float& fLength) { m_fBarLength = fLength; }
	void SetBold(const float& fBold) { m_fBarBold = fBold; }
	void SetBarSpace(const float& fSpace) { m_fBarSpace = fSpace; }
	void SetSpace(const float& fSpace) { m_fSpace = fSpace; }
	void SetBGColor(const D3DXCOLOR& color);
	void SetFillColor(const D3DXCOLOR& color) { m_fillColor = color; }
	void SetNonFillColor(const D3DXCOLOR& color) { m_nonFillCollor = color; }
	void SetAlpha(const float& fAlpha);
	float GetProgress() { return m_fBarProgress; }

	static const float DEFAULT_BAR_SPACE;			// �f�t�H���g�̃o�[�̋��
	static const D3DXCOLOR DEFAULT_FILL_COLOR;			// �f�t�H���g�̖��܂��Ă���F
	static const D3DXCOLOR DEFAULT_NONFILL_COLOR;	// �f�t�H���g�̖��܂��Ă��Ȃ��Ƃ��̐F
private:
	float m_fBarLength;
	float m_fBarBold;
	float m_fBarProgress;
	float m_fBarSpace;
	float m_fSpace;
	float m_fAlpha;
	int m_nNumBar;
	D3DXCOLOR m_fillColor, m_nonFillCollor;

	GameObject* m_pBgObj;
	std::vector<GameObject*> m_pBars;
};

// ���x�ȃo�[
class CAdvancedBar : public Component
{
public:
	CAdvancedBar():m_pVtxBar(nullptr),m_align(ALIGN::LEFT),m_fBold(30.0f),m_fLength(500.0f),m_fProgress(1.0f),m_texture(nullptr)
	{
		for (int i = 0; i < 4; i++)
		{
			m_color[i] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		m_bgColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	void Init() override;
	void Uninit() override;
	void DrawUI() override;

	// �F�ύX
	void SetColor(int index, D3DXCOLOR color);
	// �F�ύX
	void SetColor(D3DXCOLOR color);
	// �w�i�F�ύX
	void SetBGColor(D3DXCOLOR color);
	// �i���x�ύX
	void SetProgress(const float& percent);
	// �i���x�̎擾
	float GetProgress() { return m_fProgress; }
	// �����̕ύX
	void SetLength(const float& length);
	// �����̎擾
	float GetLength() { return m_fLength; }
	// �����̕ύX
	void SetBold(const float& bold);
	// �����̎擾
	float GetBold() { return m_fBold; }
	// �e�N�X�`���̐ݒ�
	void SetTexture(std::string sPath);

	// ����
	enum ALIGN
	{
		LEFT,
		CENTER
	};

	// ����̕ύX
	void SetAlign(const ALIGN& align);
	// ����̎擾
	ALIGN GetAlign() { return m_align; }

	// ���_�X�V
	void UpdateVertex();
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBar;	// �o�[���_���
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBG;	// �w�i���_���
	LPDIRECT3DTEXTURE9 m_texture;				// �e�N�X�`��

	ALIGN m_align;											// ����
	float m_fBold;											// ����
	float m_fLength;										// ����
	float m_fProgress;										// �i���x
	D3DXCOLOR m_color[4];							// �F
	D3DXCOLOR m_bgColor;							// �w�i�F
};


#endif // !_HP_BAR_H_
