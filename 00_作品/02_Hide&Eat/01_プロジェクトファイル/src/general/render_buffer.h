//=============================================================
//
// �����_�[�o�b�t�@�[ [render_buffer.h]
// Author: Ito Kotaro
//
//=============================================================
#ifndef _RENDER_BUFFER_H_
#define _RENDER_BUFFER_H_

// �����_�[�o�b�t�@�[
class RenderBuffer
{
public:
	RenderBuffer() : m_name(""), m_surface(nullptr), m_texture(nullptr), enabled(true){}
	virtual ~RenderBuffer() {}

	//@brief �`��
	virtual void Render();
	//@brief ������
	virtual void Init(){}
	//@brief �I��
	virtual void Uninit();

	//@brief �^�[�Q�b�g�̕ύX
	void ChangeTarget();
	//@brief ���Ƃ̃o�b�t�@�ɖ߂�
	void ResetBuffer();

	//@brief �e�N�X�`���̐���
	bool CreateTexture(const int& width, const int& height, const D3DFORMAT& format = D3DFMT_R8G8B8);
	//@brief �e�N�X�`���̔j��
	void DestroyTexture();

	//@brief ���O�̐ݒ�
	void SetName(const std::string& name) { m_name = name; }
	//@brief ���O�̎擾
	std::string GetName() { return m_name; }
	//@brief �e�N�X�`���̎擾
	LPDIRECT3DTEXTURE9 GetTexture() { return m_texture; }

	bool enabled;	// �L����

protected:
	//@brief �V�[���̊J�n
	bool BeginScene();
	//@brief �V�[���̏I��
	bool EndScene();
private:
	std::string m_name;	// ���O

	LPDIRECT3DSURFACE9 m_surface;				// �T�[�t�F�C�X
	LPDIRECT3DSURFACE9 m_depthSurface;	// �[�x�o�b�t�@
	LPDIRECT3DTEXTURE9 m_texture;				// �e�N�X�`��

	LPDIRECT3DSURFACE9 m_beforeBufferSurface;
	LPDIRECT3DSURFACE9 m_beforeDepthSurface;
};


#include "component/3d/camera.h"
// �J���������_�[�o�b�t�@
class CameraRenderBuffer : public RenderBuffer
{
public:
	CameraRenderBuffer() : m_camera(nullptr) {}
	void SetCamera(CCamera* camera) { m_camera = camera; }
	void Render() override;
protected:
	CCamera* m_camera;
};

#endif // !_RENDER_BUFFER_H_
