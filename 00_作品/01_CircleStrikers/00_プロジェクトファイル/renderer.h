//========================================================================================================
//
//�����_���[����[renderer.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"

//�����_���[�N���X
class Renderer
{
public:
	Renderer();   //�R���X�g���N�^
	~Renderer();   //�f�X�g���N�^

	HRESULT Init(HWND hWnd, BOOL bWindow);   //����������
	void Uninit();   //�I������
	void Update();   //�X�V����
	void Draw();   //�`�揈��
	LPDIRECT3DDEVICE9 GetDevice() { return m_pD3DDevice; };   //�f�o�C�X�̎擾����
	HWND GetHWND() { return m_hWnd; };   //�E�B���h�E�n���h���̎擾����
	void SetFullScreen(bool bFullScreen);	// �t���X�N���[��
	void SetStencilRenderState();

private:
	LPDIRECT3D9 m_pD3D;   //Direct3D
	LPDIRECT3DDEVICE9 m_pD3DDevice;   //Direct3D�f�o�C�X
	HWND m_hWnd;
	LPD3DXFONT m_pFont;   //�t�H���g
	bool m_isFullScreen;   //�t���X�N���[���t���O
};

#endif // !_RENDERER_H_
