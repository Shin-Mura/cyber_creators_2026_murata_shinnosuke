//=============================================================
//
// �e�����_�[ [shadow_rb.h]
// Author: Ito Kotaro
//
//=============================================================
#ifndef _SHADOW_RENDERBUFFER_H_
#define _SHADOW_RENDERBUFFER_H_

#include "render_buffer.h"
#include "shader.h"

// �e�V�F�[�_�[
class ShadowMapShader : public Shader
{
public:
	bool Init() override;
	void Uninit() override;

	// �p�X�J�n
	void SetParam(const ParamData& data) override;

	// �J������ݒ肷��
	void SetViewMtx(D3DXMATRIX mtx) { m_viewMtx = mtx; }

	// �ݒ�
	void SetLightDiffuse(D3DXVECTOR4* diffuse) { m_effect->SetVector(m_hLightDiffuse, diffuse); }
	void SetCosTheta(float cosTheta) { m_effect->SetFloat(m_hCosTheta, cosTheta); }
	void SetProj(const D3DXMATRIX* pmProj) { m_effect->SetMatrix(m_hProj, pmProj); }
	void SetLightPos(D3DXVECTOR4* lightPos) { m_effect->SetVector(m_hLightPos, lightPos); }
	void SetLightDir(D3DXVECTOR4* lightDir) { m_effect->SetVector(m_hLightDir, lightDir); }
	void SetLightAmbient(D3DXVECTOR4* ambient) { m_effect->SetVector(m_hLightAmbient, ambient); }
	void SetWorldView(D3DXMATRIX* worldView) { m_effect->SetMatrix(m_hWorldView, worldView); }
	void SetShadowTex(LPDIRECT3DTEXTURE9 shadowTex) { m_effect->SetTexture(m_hShadowTex, shadowTex); }
	void SetViewToLightProj(D3DXMATRIX* viewToLightProj) { m_effect->SetMatrix(m_hViewToLightProj, viewToLightProj); }
	void SetRenderShadowTechnique() { m_effect->SetTechnique(m_hRenderShadowTechnique); }
	void SetRenderSceneTechnique() { m_effect->SetTechnique(m_hRenderSceneTechnique); }
	void SetRenderLightTechnique() { m_effect->SetTechnique(m_hRenderLightTechnique); }
private:
	LPDIRECT3DTEXTURE9 m_defTex;

	D3DXMATRIX m_viewMtx;
	D3DXHANDLE m_hLightDiffuse;
	D3DXHANDLE m_hCosTheta;
	D3DXHANDLE m_hProj;
	D3DXHANDLE m_hLightPos;
	D3DXHANDLE m_hLightDir;
	D3DXHANDLE m_hWorldView;
	D3DXHANDLE m_hMaterial;
	D3DXHANDLE m_hTexture;
	D3DXHANDLE m_hShadowTex;
	D3DXHANDLE m_hViewToLightProj;
	D3DXHANDLE m_hLightAmbient;
	D3DXHANDLE m_hRenderShadowTechnique;
	D3DXHANDLE m_hRenderSceneTechnique;
	D3DXHANDLE m_hRenderLightTechnique;
};


// �����_�[
class ShadowRenderBuffer : public CameraRenderBuffer
{
public:
	void Init() override;
	void Uninit() override;
	void Render() override;

	void SetAmbient(D3DXVECTOR4 ambient) { m_shader->SetLightAmbient(&ambient); }
	void SetLightCamera(CCamera* camera) { m_lightCamera = camera; }
	void SetShadowPoint(const D3DXVECTOR3& pos) { m_shadowPoint = pos; }
	void SetShadowRange(const float& range) { m_shadowRange = range; }

	static const int SHADOWMAP_SIZE;
private:
	void RenderScene(bool renderShadow, const D3DXMATRIX* pmView, const D3DXMATRIX* pmProj);

	ShadowMapShader* m_shader = nullptr;	// �V�F�[�_�[

	D3DLIGHT9 m_light;								// �X�|�b�g���C�g
	LPDIRECT3DTEXTURE9 m_shadowMap;	// �V���h�E�}�b�v
	LPDIRECT3DSURFACE9 m_dsShadow;		// �[�x�o�b�t�@
	float m_lightFov;									// �X�|�b�g���C�g��FOV
	D3DXMATRIX m_shadowProj;					// �v���W�F�N�V�����}�g���b�N�X
	CCamera* m_lightCamera;						// ���C�g�J����
	D3DXVECTOR3 m_shadowPoint;				// �V���h�E�̒��S�n
	float m_shadowRange;							// �V���h�E�͈̔�
};

#endif