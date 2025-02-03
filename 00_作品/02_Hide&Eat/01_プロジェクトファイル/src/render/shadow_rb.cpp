//=============================================================
//
// �e�����_�[ [shadow_rb.cpp]
// Author: Ito Kotaro
//
//=============================================================
#include "shadow_rb.h"
#include "component/2d/polygon.h"
#include "component/3d/mesh.h"
#include "component/3d/meshfield.h"

const int ShadowRenderBuffer::SHADOWMAP_SIZE = 4096;

//=============================================================
// [ShadowMapShader] ������
//=============================================================
bool ShadowMapShader::Init()
{
	// �f�o�C�X�̎擾
	auto device = CRenderer::GetInstance()->GetDevice();

	// ���\�[�X�ɂ���Z�l�v���b�g�V�F�[�_�v���O������ǂݍ���
	D3DXCreateEffectFromFile(device,
		"data\\SHADER\\ShadowMap.fx",
		nullptr,
		nullptr,
		0,
		nullptr,
		&m_effect,
		nullptr);

	m_hLightDiffuse = m_effect->GetParameterByName(NULL, "g_vLightDiffuse");
	m_hCosTheta = m_effect->GetParameterByName(NULL, "g_fCosTheta");
	m_hProj = m_effect->GetParameterByName(NULL, "g_mProj");
	m_hLightPos = m_effect->GetParameterByName(NULL, "g_vLightPos");
	m_hLightDir = m_effect->GetParameterByName(NULL, "g_vLightDir");
	m_hWorldView = m_effect->GetParameterByName(NULL, "g_mWorldView");
	m_hMaterial = m_effect->GetParameterByName(NULL, "g_vMaterial");
	m_hTexture = m_effect->GetParameterByName(NULL, "g_txScene");
	m_hShadowTex = m_effect->GetParameterByName(NULL, "g_txShadow");
	m_hViewToLightProj = m_effect->GetParameterByName(NULL, "g_mViewToLightProj");
	m_hLightAmbient = m_effect->GetParameterByName(NULL, "g_vLightAmbient");
	m_hRenderShadowTechnique = m_effect->GetTechniqueByName("RenderShadow");
	m_hRenderSceneTechnique = m_effect->GetTechniqueByName("RenderScene");
	m_hRenderLightTechnique = m_effect->GetTechniqueByName("RenderLight");

	// �e�N�X�`���̍쐬�i��1pixel�j
	device->CreateTexture(1, 1, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_defTex, NULL);
	D3DLOCKED_RECT lr;
	m_defTex->LockRect(0, &lr, NULL, 0);
	*(LPDWORD)lr.pBits = D3DCOLOR_RGBA(255, 255, 255, 255);
	m_defTex->UnlockRect(0);

	return true;
}

//=============================================================
// [ShadowMapShader] �I��
//=============================================================
void ShadowMapShader::Uninit()
{
	// �e�N�X�`���̔j��
	if (m_defTex != nullptr)
	{
		m_defTex->Release();
		m_defTex = nullptr;
	}
}

//=============================================================
// [ShadowMapShader] �p�����[�^�[�̐ݒ�
//=============================================================
void ShadowMapShader::SetParam(const ParamData& data)
{
	// �}�e���A���ݒ�
	D3DXVECTOR4 vDif = { data.color.r, data.color.g, data.color.b, data.color.a };
	m_effect->SetVector(m_hMaterial, &vDif);

	// �e�N�X�`���ݒ�
	if (data.texture != nullptr)
		m_effect->SetTexture(m_hTexture, data.texture);
	else
		m_effect->SetTexture(m_hTexture, m_defTex);


	D3DXMATRIXA16 mWorldView = data.mtx != nullptr ? data.mtx : data.component->transform->GetMatrix();
	D3DXMATRIX viewMtx = m_viewMtx;
	D3DXMatrixMultiply(&mWorldView, &mWorldView, &viewMtx);
	SetWorldView(&mWorldView);

	// �l�̕ύX��K�p
	HRESULT hr = m_effect->CommitChanges();
}

//=============================================================
// [ShadowRenderBuffer] ������
//=============================================================
void ShadowRenderBuffer::Init()
{
	// �f�o�C�X�̎擾
	auto device = CRenderer::GetInstance()->GetDevice();

	m_shadowPoint = { 0.0f, 0.0f, 0.0f };
	m_shadowRange = 1500.0f;

	// �V�F�[�_�[�̏�����
	m_shader = new ShadowMapShader();
	m_shader->Init();

	// �X�|�b�g���C�g�̏�����
	m_lightFov = D3DXToRadian(45.0f);

	m_light.Diffuse.r = 1.0f;
	m_light.Diffuse.g = 1.0f;
	m_light.Diffuse.b = 1.0f;
	m_light.Diffuse.a = 1.0f;
	m_light.Position = D3DXVECTOR3(-8.0f, -8.0f, 0.0f);
	m_light.Direction = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&m_light.Direction, (D3DXVECTOR3*)&m_light.Direction);
	m_light.Range = 20.0f;
	m_light.Theta = m_lightFov / 2.0f;
	m_light.Phi = m_lightFov / 2.0f;

	// �V�F�[�_�[�̒l��ݒ肷��
	m_shader->SetLightDiffuse((D3DXVECTOR4*)&m_light.Diffuse);
	m_shader->SetCosTheta(cosf(m_light.Theta));

	// �V���h�E�}�b�v�e�N�X�`�����쐬����
	if (FAILED( device->CreateTexture(
		SHADOWMAP_SIZE, SHADOWMAP_SIZE,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_R32F,
		D3DPOOL_DEFAULT,
		&m_shadowMap,
		NULL
	)))
	{ // ���s
		MessageBoxA(NULL, "�V���h�E�}�b�v�e�N�X�`���̍쐬�Ɏ��s�I", "�G���[", MB_OK);
	}

	// �[�x�o�b�t�@�̍쐬
	if (FAILED(device->CreateDepthStencilSurface(
		SHADOWMAP_SIZE, SHADOWMAP_SIZE,
		D3DFMT_D24S8,
		D3DMULTISAMPLE_NONE,
		0,
		TRUE,
		&m_dsShadow,
		NULL
	)))
	{ // ���s
		MessageBoxA(NULL, "�[�x�o�b�t�@�̍쐬�Ɏ��s�I", "�G���[", MB_OK);
	}

	//m_shadowMapTex = new GameObject();
	//m_shadowMapTex->AddComponent<CPolygon>()->BindTexture(m_shadowMap);
	//m_shadowMapTex->transform->SetSize(150, 150);
}

//=============================================================
// [ShadowRenderBuffer] �I��
//=============================================================
void ShadowRenderBuffer::Uninit()
{
	// �V�F�[�_�[�̉��
	if (m_shader != nullptr)
	{
		m_shader->Uninit();
		delete m_shader;
		m_shader = nullptr;
	}

	// �V���h�E�}�b�v�e�N�X�`���̔j��
	if (m_shadowMap != nullptr)
	{
		m_shadowMap->Release();
		m_shadowMap = nullptr;
	}

	// �[�x�o�b�t�@�̔j��
	if (m_dsShadow != nullptr)
	{
		m_dsShadow->Release();
		m_dsShadow = nullptr;
	}
}

//=============================================================
// [ShadowRenderBuffer] �`��
//=============================================================
void ShadowRenderBuffer::Render()
{
	// �f�o�C�X�̎擾
	auto device = CRenderer::GetInstance()->GetDevice();

	if (m_camera == nullptr || m_lightCamera == nullptr)
	{
		CameraRenderBuffer::Render();
		return;
	}

	// �J�����̍X�V
	m_camera->SetCamera(false);

	// ���C�g�J�����̍X�V
	m_lightCamera->SetCamera(false);

	// ���C�g�̃r���[�}�g���b�N�X�̎擾
	D3DXMATRIX mLightView;
	mLightView = m_lightCamera->GetViewMatrix();

	// �e�̃v���W�F�N�V�����}�g���b�N�X
	D3DXMatrixPerspectiveFovLH(&m_shadowProj, m_lightFov, 1, m_lightCamera->m_fClippingPlanesNear, m_lightCamera->m_fClippingPlanesFar);

	//----------------------------------------------------------------------------------
	// �V���h�E�}�b�v��`�悷��
	//----------------------------------------------------------------------------------
	LPDIRECT3DSURFACE9 pOldRT = NULL;
	device->GetRenderTarget(0, &pOldRT);
	LPDIRECT3DSURFACE9 pShadowSurf;
	if (SUCCEEDED(m_shadowMap->GetSurfaceLevel(0, &pShadowSurf)))
	{
		device->SetRenderTarget(0, pShadowSurf);
		if (pShadowSurf != nullptr)
		{
			pShadowSurf->Release();
			pShadowSurf = nullptr;
		}
	}
	LPDIRECT3DSURFACE9 pOldDS = NULL;
	if (SUCCEEDED(device->GetDepthStencilSurface(&pOldDS)))
		device->SetDepthStencilSurface(m_dsShadow);

	RenderScene(true, &mLightView, &m_shadowProj);

	if (pOldDS)
	{
		device->SetDepthStencilSurface(pOldDS);
		pOldDS->Release();
	}
	device->SetRenderTarget(0, pOldRT);
	if (pOldRT != nullptr)
	{
		pOldRT->Release();
		pOldRT = nullptr;
	}

	//----------------------------------------------------------------------------------
	// �V�[���̕`��
	//----------------------------------------------------------------------------------
	D3DXMATRIX cameraViewMtx = m_camera->GetViewMatrix();
	const D3DXMATRIX* pmView = &cameraViewMtx;

	// �K�v�p�����[�^�[�̏�����
	m_shader->SetShadowTex(m_shadowMap);

	// �r���[��Ԃ�������e��Ԃɕϊ�����
	D3DXMATRIXA16 mViewToLightProj;
	mViewToLightProj = *pmView;
	D3DXMatrixInverse(&mViewToLightProj, NULL, &mViewToLightProj);
	D3DXMatrixMultiply(&mViewToLightProj, &mViewToLightProj, &mLightView);
	D3DXMatrixMultiply(&mViewToLightProj, &mViewToLightProj, &m_shadowProj);
	m_shader->SetViewToLightProj(&mViewToLightProj);

	D3DXMATRIX cameraProjMtx = m_camera->GetProjectionMatrix();
	RenderScene(false, pmView, &cameraProjMtx);
	m_shader->SetShadowTex(NULL);
}

//=============================================================
// [ShadowRenderBuffer] �V�[���`��
//=============================================================
void ShadowRenderBuffer::RenderScene(bool renderShadow, const D3DXMATRIX* pmView, const D3DXMATRIX* pmProj)
{
	// �f�o�C�X�̎擾
	auto device = CRenderer::GetInstance()->GetDevice();

	// �v���W�F�N�V�����}�g���b�N�X��ݒ肷��
	m_shader->SetProj(pmProj);
	m_shader->SetViewMtx(*pmView);

	// ���C�g�̃p�����[�^�[���X�V����
	D3DXVECTOR3 v = *(D3DXVECTOR3*)&m_lightCamera->transform->GetMatrix()._41;
	D3DXVECTOR4 v4;
	D3DXVec3Transform(&v4, &v, pmView);
	m_shader->SetLightPos(&v4);
	*(D3DXVECTOR3*)&v4 = *(D3DXVECTOR3*)&m_lightCamera->transform->GetMatrix()._31;
	v4.w = 0.0f;
	D3DXVec4Transform(&v4, &v4, pmView);
	D3DXVec3Normalize((D3DXVECTOR3*)&v4, (D3DXVECTOR3*)&v4);
	m_shader->SetLightDir(&v4);

	// �����_�[�o�b�t�@���N���A����
	device->Clear(0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x000000ff, 1.0f, 0L);

	if (renderShadow)
		m_shader->SetRenderShadowTechnique();

	// �`��J�n
	if (BeginScene())
	{
		if (!renderShadow)
		{
			m_shader->SetRenderSceneTechnique();

			m_camera->SetCamera();
			m_camera->GetSkybox()->Draw();
		}

		// �I�u�W�F�N�g��`�悷��
		auto allGameObjects = GameObject::GetAllGameObjects();
		for (auto itr = allGameObjects.begin(); itr != allGameObjects.end(); itr++)
		{
			if ((*itr)->GetActive() && (*itr)->GetVisible())
			{ // �A�N�e�B�u�̂Ƃ�
				auto components = (*itr)->GetComponents();

				// �R���|�[�l���g�̕`�揈�����s��
				for (auto itrComp = components.begin(); itrComp != components.end(); itrComp++)
				{
					if ((*itrComp)->enabled)
					{
						if (renderShadow && !Component::IsClassType<CMeshField>(*itrComp) &&
							Benlib::PosPlaneDistance((*itrComp)->transform->GetWPos(), m_shadowPoint) > m_shadowRange)
							break;

						// �I�u�W�F�N�g�̃}�g���b�N�X��ݒ肷��
						D3DXMATRIXA16 mWorldView = (*itrComp)->transform->GetMatrix();
						D3DXMatrixMultiply(&mWorldView, &mWorldView, pmView);
						m_shader->SetWorldView(&mWorldView);

						// �V�F�[�_�[�J�n
						m_shader->Begin();

						// �p�X�`��
						for (UINT i = 0; i < m_shader->GetNumPass(); i++)
						{
							(*itrComp)->SetShader(m_shader, i);
							(*itrComp)->Draw();
						}

						// �V�F�[�_�[�I��
						m_shader->End();
					}
				}
			}
		}

		// UI�̕`��
		if (!renderShadow)
			GameObject::DrawUIAll();

		// �V�[���̏I��
		EndScene();
	}

}