//=============================================================
//
// �����_�[�o�b�t�@�[ [render_buffer.cpp]
// Author: Ito Kotaro
//
//=============================================================
#include "render_buffer.h"
#include "renderer.h"
#include "manager.h"

//=============================================================
// [RenderBuffer] �I��
//=============================================================
void RenderBuffer::Uninit()
{
	// �e�N�X�`���̔j��
	if (m_texture != nullptr)
	{
		m_texture->Release();
		m_texture = nullptr;
	}

	// �e�N�X�`���T�[�t�F�C�X�̔j��
	if (m_surface != nullptr)
	{
		m_surface->Release();
		m_surface = nullptr;
	}

	// �[�x�o�b�t�@�̔j��
	if (m_depthSurface != nullptr)
	{
		m_depthSurface->Release();
		m_depthSurface = nullptr;
	}
}

//=============================================================
// [RenderBuffer] �^�[�Q�b�g�̕ύX
//=============================================================
void RenderBuffer::ChangeTarget()
{
	// �f�o�C�X�̎擾
	auto device = CRenderer::GetInstance()->GetDevice();

	// �O��̐ݒ�Ƃ��ĕۑ����Ă���
	device->GetRenderTarget(0, &m_beforeBufferSurface);
	device->GetDepthStencilSurface(&m_beforeDepthSurface);

	// �����_�[�^�[�Q�b�g��ݒ肷��
	if (m_texture != nullptr)
	{
		device->SetDepthStencilSurface(m_depthSurface);

		if (FAILED(m_texture->GetSurfaceLevel(0, &m_surface)))
		{
			return;
		}
	}
	device->SetRenderTarget(0, m_surface);
}

//=============================================================
// [RenderBuffer] �o�b�t�@�����Ƃɖ߂�
//=============================================================
void RenderBuffer::ResetBuffer()
{
	// �f�o�C�X�̎擾
	auto device = CRenderer::GetInstance()->GetDevice();

	// ���̃����_�[�^�[�Q�b�g��ݒ肷��
	device->SetRenderTarget(0, m_beforeBufferSurface);

	// ���̐ݒ�ɖ߂�
	device->SetDepthStencilSurface(m_beforeDepthSurface);
}

//=============================================================
// [RenderBuffer] �����_�[
//=============================================================
void RenderBuffer::Render()
{
	// �f�o�C�X�̎擾
	auto device = CRenderer::GetInstance()->GetDevice();

	// ��ʃN���A�i�o�b�t�@�N���A��Z�o�b�t�@�N���A�j
	device->Clear(0, nullptr, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 1.0f, 0);

	// �Q�[���I�u�W�F�N�g�̕`�揈��
	GameObject::DrawAll();

	// �Q�[���I�u�W�F�N�g��UI�`�揈��
	GameObject::DrawUIAll();
}

//=============================================================
// [RenderBuffer] �e�N�X�`���̐���
//=============================================================
bool RenderBuffer::CreateTexture(const int& width, const int& height, const D3DFORMAT& format)
{
	// �f�o�C�X�̎擾
	auto device = CRenderer::GetInstance()->GetDevice();

	// �����e�N�X�`����j��
	if (m_texture != nullptr)
	{
		m_texture->Release();
		m_texture = nullptr;
	}

	// �e�N�X�`���̍쐬
	if (FAILED(D3DXCreateTexture(
		device,
		width,
		height,
		0,
		D3DUSAGE_RENDERTARGET,
		format,
		D3DPOOL_DEFAULT,
		&m_texture)))
	{
		return false;
	}

	// �[�x�o�b�t�@�̍쐬
	if (FAILED(device->CreateDepthStencilSurface(
		width,
		height,
		D3DFMT_D24S8,
		D3DMULTISAMPLE_NONE,
		0,
		TRUE,
		&m_depthSurface,
		NULL)))
	{
		return false;
	}

	return true;
}

//=============================================================
// [RenderBuffer] �e�N�X�`���̔j��
//=============================================================
void RenderBuffer::DestroyTexture()
{
	RenderBuffer::Uninit();
}

//=============================================================
// [RenderBuffer] �V�[���`��J�n
//=============================================================
bool RenderBuffer::BeginScene()
{
	auto device = CRenderer::GetInstance()->GetDevice();
	if (SUCCEEDED(device->BeginScene()))
	{
		return true;
	}
	return false;
}

//=============================================================
// [RenderBuffer] �V�[���`��I��
//=============================================================
bool RenderBuffer::EndScene()
{
	auto device = CRenderer::GetInstance()->GetDevice();
	if (SUCCEEDED(device->EndScene()))
	{
		return true;
	}
	return false;
}

//=============================================================
// [CameraRenderBuffer] �����_�[
//=============================================================
void CameraRenderBuffer::Render()
{
	auto device = CRenderer::GetInstance()->GetDevice();

	if (BeginScene())
	{
		// ��ʃN���A�i�o�b�t�@�N���A��Z�o�b�t�@�N���A�j
		device->Clear(0, nullptr, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 1.0f, 0);

		if (m_camera != nullptr)
		{
			m_camera->SetCamera();
			m_camera->GetSkybox()->Draw();

			if (CShadow::USE_SHADOW)
				CRenderer::GetInstance()->GetShadow()->Draw(m_camera);
		}
		
		GameObject::DrawAll();
		GameObject::DrawUIAll();

		EndScene();
	}
}