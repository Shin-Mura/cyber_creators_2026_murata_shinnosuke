//=============================================================
//
// �e�L�X�g�R���|�[�l���g [text.h]
// Author: Ito Kotaro
//
//=============================================================
#ifndef _TEXT_COMPONENT_H_
#define _TEXT_COMPONENT_H_

#include "component.h"

// �e�L�X�g�R���|�[�l���g
class CText : public Component
{
public:
	// ����
	enum ALIGN
	{
		LEFT,
		CENTER,
		RIGHT
	};

	// �������
	struct TextInfo
	{
		IDirect3DTexture9* pTex;	// �����̃e�N�X�`��
		D3DXVECTOR3 pos;			// �����ʒu
		int line;								// �s��
	};

	// �t�H���g�̃f�[�^
	struct FontData
	{
		std::string sFontPath;
		std::string sFontName;
	};

	void Init() override;
	void Uninit() override;
	virtual void DrawUI() override;

	void SetText(const std::string& text);
	void SetFontSize(const int& size);
	void SetOutlineSize(const int& size);
	void SetOutlineColor(const D3DXCOLOR& color);
	void SetFontColor(const D3DXCOLOR& color);
	void SetFont(const std::string& fontName);
	void SetAlign(const ALIGN& align);
	void SetAlpha(const float& fAlpha);
	float GetAlpha() { return m_alpha; }

	int GetFontSize() { return m_fontSize; }

	static const FontData LoadFonts[];
	static void InitLoadFont();
protected:
	// �`��
	LPD3DXSPRITE m_pSprite;							// �X�v���C�g
	std::vector<TextInfo> m_textInfos;				// �����Ǘ�
	float m_fMaxHeight;									// �����̒��ł��ő�T�C�Y
	float m_alpha;											// �s�����x
private:
	void UpdateText();

	// 1�����̃e�N�X�`���𐶐�����
	IDirect3DTexture9* CreateFontTexture(
		const char* faceName = "MS �S�V�b�N",
		unsigned char charSet = SHIFTJIS_CHARSET,
		const char* str = "T",
		unsigned fontHeight = 450,
		unsigned weight = 0,
		int penSize = 5,
		D3DXCOLOR edgeColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		D3DXCOLOR fillColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f),
		int quality = 3,
		RECT* info = 0);

	// ���
	std::string m_text;					// ����
	unsigned char m_charSet;		// �����Z�b�g
	int m_fontSize;					// �t�H���g�T�C�Y
	float m_weight;						// �t�H���g�̑���
	int m_outlineSize;				// �A�E�g���C���T�C�Y
	D3DXCOLOR m_fillColor;			// �h��Ԃ��F
	D3DXCOLOR m_outlineColor;		// �A�E�g���C���F
	int m_quality;						// �A���`�G�C���A�X�i1�ȏ�j
	RECT* m_info;
	ALIGN m_align;						// ����

	// �t�H���g���
	std::string m_fontName;		// �t�H���g��
};

// �^�C�s���O�e�L�X�g
class CTypingText : public CText
{
public:
	CTypingText();
	void Update() override;
	void DrawUI() override;
	void SetTypingSpeed(const int& nSpeed) { m_nTypingSpeed = nSpeed; }
private:
	int m_nTypingCounter;	// �^�C�s���O�J�E���^�[
	int m_nTypingSpeed;		// �^�C�s���O�X�s�[�h
	int m_nTypingNum;		// �^�C�s���O�ς�
};

// �e�L�X�g�^�O�i���j
class CTextTag
{
public:
	enum TYPE
	{
		SIZE,
		COLOR,
		FONT_COLOR,
		EDGE_COLOR,
	};
	CTextTag(const TYPE& type) { m_type = type; }
	void SetIdx(const int& idx) { m_idx = idx; }
	int GetIdx() { return m_idx; }
	TYPE GetType() { return m_type; }
private:
	int m_idx;
	TYPE m_type;
};

// �T�C�Y�^�O
class CSizeTag : public CTextTag
{
public:
	CSizeTag() : CTextTag(SIZE) {}
	void SetSize(const int& size) { m_size = size; }
	int GetSize() { return m_size; }
private:
	int m_size;
};

// �J���[�^�O
class CColorTag : public CTextTag
{
public:
	CColorTag() : CTextTag(COLOR) {}
	void SetColor(const D3DXCOLOR& color) { 
		m_fillColor = color; 
		m_edgeColor = color;
	}
	void SetFillColor(const D3DXCOLOR& color) { m_fillColor = color; }
	void SetEdgeColor(const D3DXCOLOR& color) { m_edgeColor = color; }
	D3DXCOLOR GetFillColor() { return m_fillColor; }
	D3DXCOLOR GetEdgeColor() { return m_edgeColor; }
private:
	D3DXCOLOR m_fillColor;
	D3DXCOLOR m_edgeColor;
};

// �t�H���g�J���[�^�O
class CFontColorTag : public CTextTag
{
public:
	CFontColorTag() : CTextTag(FONT_COLOR) {}
	void SetColor(const D3DXCOLOR& color) { m_color = color; }
	D3DXCOLOR GetColor() { return m_color; }
private:
	D3DXCOLOR m_color;
};

// �G�b�W�J���[�^�O
class CEdgeColorTag : public CTextTag
{
public:
	CEdgeColorTag() : CTextTag(EDGE_COLOR) {}
	void SetColor(const D3DXCOLOR& color) { m_color = color; }
	D3DXCOLOR GetColor() { return m_color; }
private:
	D3DXCOLOR m_color;
};

#endif // !_TEXT_COMPONENT_H_
