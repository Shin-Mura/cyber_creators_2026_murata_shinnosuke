//=============================================================
//
// �����_���[ [renderer.h]
// Author: Ito Kotaro
//
//=============================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "internal/shadow.h"
#include "render_buffer.h"

// �}�N����`
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)	// ���_�t�H�[�}�b�g[3D]

// �����_���[�N���X�̒�`
class CRenderer
{
public:
	CRenderer();
	~CRenderer();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit();
	void Update();
	void Draw();

	static CRenderer* GetInstance() {
		static CRenderer renderer;
		return &renderer;
	}

	// �����_�[�o�b�t�@�̓o�^
	template<class T> T* RegisterRenderBuffer(const std::string& name)
	{
		RenderBuffer* findRenderBuffer = GetRenderBuffer(name);
		if (findRenderBuffer == nullptr)
		{
			T* renderBuffer = new T();
			renderBuffer->SetName(name);
			m_renderBuffers.push_back(renderBuffer);
			renderBuffer->Init();
			return renderBuffer;
		}
		return static_cast<T*>(findRenderBuffer);
	}
	// �����_�[�o�b�t�@�̎擾
	RenderBuffer* GetRenderBuffer(const std::string& name);
	// �����_�[�o�b�t�@�̍폜
	void RemoveRenderBuffer(const std::string& name);

	// �e�̕`��
	CShadow* GetShadow() { return m_pShadow; }

	// �t���X�N���[��
	bool GetFullScreen() { return m_bFullScreen; }
	void SetFullScreen(const bool& bFullScreen);

	LPDIRECT3DDEVICE9 GetDevice() { return m_pD3DDevice; }
	HWND GetHWND() { return m_hwnd; }

	static const int SCREEN_WIDTH;					// �E�B���h�E�T�C�Y�i���j
	static const int SCREEN_HEIGHT;				// �E�B���h�E�T�C�Y�i�����j
	static const bool USE_FOG;							// �t�H�O���g�p���邩
private:
	LPDIRECT3D9 m_pD3D;								// Direct3D�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECT3DDEVICE9 m_pD3DDevice;			// Direct3D�f�o�C�X�ւ̃|�C���^
	HWND m_hwnd;										// �n���h��
	CShadow* m_pShadow;								// �e
	bool m_bFullScreen;									// �t���X�N���[��

	// �����_�[�o�b�t�@
	std::vector<RenderBuffer*> m_renderBuffers;

	// �t�H�O
	float m_fFogStartPos;									// �t�H�O�̃X�^�[�g�ʒu
	float m_fFogEndPos;									// �t�H�O�̏I���ʒu
};


// ���_���[2D]�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	float rhw;					// ���W�ϊ��p�W���i1.0f�ŌŒ�j
	D3DCOLOR col;			// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
} VERTEX_2D;

// ���_���[3D]�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	D3DXVECTOR3 nor;	// �@���x�N�g��
	D3DCOLOR col;			// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
} VERTEX_3D;

#endif // !_RENDERER_H_
