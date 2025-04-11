//=============================================================
//
// �e [shadow.cpp]
// Author: Ito Kotaro
//
//=============================================================
#include "shadow.h"
#include "manager.h"
#include "component/3d/light.h"
#include "component/3d/mesh.h"
#include "component/3d/camera.h"
#include "benlib.h"
using namespace std;

// �ϐ��̒�`
const bool CShadow::USE_SHADOW = false;
const std::string CShadow::SHADOW_VOLUME_PATH = "./data/SHADER/ShadowVolume.fx";		// �V���h�E�{�����[���̃p�X
const float CShadow::FAR_CLIP = 500.0f;
const float CShadow::ADJACENCY_EPSILON = 0.0001f;
const float CShadow::EXTRUDE_EPSILON = 0.01f;
const CShadow::RENDER_TYPE CShadow::RENDER_MODE = CShadow::RENDERTYPE_SCENE;

// �V���h�E�̒��_�錾
struct SHADOWVERT
{
    D3DXVECTOR3 Position;   // �ʒu
    D3DXVECTOR3 Normal;    // �@��
    const static D3DVERTEXELEMENT9 Decl[3];
};
const D3DVERTEXELEMENT9 SHADOWVERT::Decl[3] =
{
    { 0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
    { 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
    D3DDECL_END()
};

// ���b�V���̒��_�錾
struct MESHVERT
{
    D3DXVECTOR3 Position;
    D3DXVECTOR3 Normal;
    D3DXVECTOR2 Tex;
    const static D3DVERTEXELEMENT9 Decl[4];
};
const D3DVERTEXELEMENT9 MESHVERT::Decl[4] =
{
    { 0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
    { 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
    { 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
    D3DDECL_END()
};

//=============================================================
// [CShadow] �R���X�g���N�^
//=============================================================
CShadow::CShadow()
{
    m_pShadowVolume = nullptr;
    m_pMeshDecl = nullptr;
    m_pShadowDecl = nullptr;
    m_hShowShadow = nullptr;
    m_hRenderScene = nullptr;
    m_hRenderShadow = nullptr;
    m_pDefaultTex = nullptr;
    m_pLightMesh = nullptr;
}

//=============================================================
// [CShadow] �f�X�g���N�^
//=============================================================
CShadow::~CShadow()
{

}

//=============================================================
// [CShadow] ������
//=============================================================
void CShadow::Init()
{
    // �f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

    // �G�t�F�N�g�̏����ݒ�
    m_pShadowVolume->SetFloat("g_fFarClip", FAR_CLIP);

    // ���C�g�p�̃��b�V�����쐬����
    D3DXCreateSphere(pDevice, 1.0f, 32, 16, &m_pLightMesh, nullptr);
}

//=============================================================
// [CShadow] �I��
//=============================================================
void CShadow::Uninit()
{
    // �G�t�F�N�g�̔j��
    if (m_pShadowVolume != nullptr)
    {
        m_pShadowVolume->Release();
        m_pShadowVolume = nullptr;
    }

    // ���b�V���錾�̔j��
    if (m_pMeshDecl != nullptr)
    {
        m_pMeshDecl->Release();
        m_pMeshDecl = nullptr;
    }

    // �V���h�E�錾�̔j��
    if (m_pShadowDecl != nullptr)
    {
        m_pShadowDecl->Release();
        m_pShadowDecl = nullptr;
    }

    // �f�t�H���g�e�N�X�`���̔j��
    if (m_pDefaultTex != nullptr)
    {
        m_pDefaultTex->Release();
        m_pDefaultTex = nullptr;
    }
}

//=============================================================
// [CShadow] �e�̕`��
//=============================================================
void CShadow::Draw(CCamera* pCamera)
{
    D3DXMATRIX mtxProj = pCamera->GetProjectionMatrix();
    m_pShadowVolume->SetMatrix("g_mProj", &mtxProj);     // �v���W�F�N�V�����}�g���b�N�X��ݒ�

    {
        m_pShadowVolume->SetTechnique("RenderSceneAmbient");
        D3DXVECTOR4 vAmb(pCamera->GetAmbient(), pCamera->GetAmbient(), pCamera->GetAmbient(), 1.0f);
        m_pShadowVolume->SetVector("g_vAmbient", &vAmb);
        // ���f���̕`��
        RenderMesh(pCamera, false);
    }

    // �t�H�O���L���̂Ƃ��A�ꎞ�I�ɃI�t�ɂ���
    if (CRenderer::USE_FOG)
    {
        CRenderer::GetInstance()->GetDevice()->SetRenderState(D3DRS_FOGENABLE, FALSE);
    }

    // �e�̕`��
    DrawShadow(pCamera);

    // �t�H�O���L���̂Ƃ��A�I���ɖ߂�
    if (CRenderer::USE_FOG)
    {
        CRenderer::GetInstance()->GetDevice()->SetRenderState(D3DRS_FOGENABLE, TRUE);
    }
}

//=============================================================
// [CShadow] �e�̕`��
//=============================================================
void CShadow::DrawShadow(CCamera* pCamera)
{
    // �f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

    // ���C�g���X�g�̎擾
    vector<CLight*> pLightList = Component::GetComponents<CLight>(false, true);

    for (int nCntLight = 0; nCntLight < (int)pLightList.size(); nCntLight++)
    {
        // ���C�g�̎擾
        CLight* pLight = pLightList[nCntLight];

        // �X�e���V���o�b�t�@���N���A����
        pDevice->Clear(0, nullptr, D3DCLEAR_STENCIL, D3DCOLOR_ARGB(0, 170, 170, 170), 1.0f, 0);

        // �r���[�}�g���b�N�X�ƃv���W�F�N�V�����}�g���b�N�X���擾����
        D3DXMATRIX mtxView;
        mtxView = pCamera->GetViewMatrix();
        //mtxProj = pCamera->GetProjectionMatrix();

        // �Ɩ��̐ݒ��K�p����
        D3DXVECTOR3 lightPos = pLight->transform->GetWPos();
        D3DXVECTOR4 vLight(lightPos.x, lightPos.y, lightPos.z, 1.0f);
        D3DXVECTOR4 vLightColor = { pLight->GetColor().r, pLight->GetColor().g, pLight->GetColor().b, pLight->GetColor().a };
        vLightColor *= pLight->GetIntensity();

        D3DXVec4Transform(&vLight, &vLight, &mtxView);
        m_pShadowVolume->SetVector("g_vLightView", &vLight);
        m_pShadowVolume->SetVector("g_vLightColor", &vLightColor);

        // �V���h�E�{�����[����`�悷��
        switch (RENDER_MODE)
        {
        case RENDERTYPE_SHADOWVOLUME:
            m_pShadowVolume->SetTechnique(m_hShowShadow);
            break;
        default:
            m_pShadowVolume->SetTechnique(m_hRenderShadow);
        }

        // �V���h�E�{�����[���̐F��K�p����i�`��^�C�v��SHADOWVOLUME�̂݋@�\����j
        D3DXVECTOR4 volumeColor = { 
            pLight->GetVolumeColor().r,
            pLight->GetVolumeColor().g,
            pLight->GetVolumeColor().b,
            pLight->GetVolumeColor().a 
        };
        m_pShadowVolume->SetVector("g_vShadowColor", &volumeColor);

        // ���f�����X�g���擾����
        std::vector<CMesh*> pMeshList = Component::GetComponents<CMesh>(false, true);

        for (unsigned int nCntModel = 0; nCntModel < pMeshList.size(); nCntModel++)
        {
            // ���f�����擾����
            CMesh* pMesh = pMeshList[nCntModel];

            // ���f���ɃV���h�E���b�V��������ꍇ�̂ݕ`��
            if (pMesh->GetShadowMesh() != nullptr)
            {
                // �e���W���M��Ȃ��悤�ɂ��邽�߂̏k���X�P�[��
                D3DXMATRIX mtxShadowScale;
                D3DXMatrixIdentity(&mtxShadowScale);
                D3DXMatrixScaling(&mtxShadowScale, 0.96f, 0.96f, 0.96f);

                // ���f���̃��[���h�}�g���b�N�X��K�p����
                D3DXMATRIXA16 mWorldView = mtxShadowScale * pMesh->transform->GetMatrix() * pCamera->GetViewMatrix();
                D3DXMATRIXA16 mWorldViewProjection = mWorldView * pCamera->GetProjectionMatrix();
                m_pShadowVolume->SetMatrix("g_mWorldViewProjection", &mWorldViewProjection);
                m_pShadowVolume->SetMatrix("g_mWorldView", &mWorldView);
                pDevice->SetVertexDeclaration(m_pShadowDecl);

                // �e��`�悷��
                UINT cPasses;
                m_pShadowVolume->Begin(&cPasses, 0);
                for (UINT i = 0; i < cPasses; ++i)
                {
                    m_pShadowVolume->BeginPass(i);
                    m_pShadowVolume->CommitChanges();
                    pMesh->GetShadowMesh()->DrawSubset(0);
                    m_pShadowVolume->EndPass();
                }
                m_pShadowVolume->End();
            }
        }

        // �X�e���V���ƃ��C�e�B���O��L���ɂ��ăV�[���������_�����O
        m_pShadowVolume->SetTechnique(m_hRenderScene);
        RenderMesh(pCamera, false);
    }
}

//=============================================================
// [CShadow] ���b�V���̃����_�[
//=============================================================
void CShadow::RenderMesh(CCamera* pCamera, bool bRenderLight)
{
    // �f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

    // �}�g���b�N�X�ϐ�
    D3DXMATRIXA16 mWorldView;
    D3DXMATRIXA16 mViewProj;
    D3DXMATRIXA16 mWorldViewProjection;

    // �ϐ�
    D3DXMATERIAL* pMat;					// �}�e���A���f�[�^�ւ̃|�C���^

    // �r���[�}�g���b�N�X�ƃv���W�F�N�V�����}�g���b�N�X���擾����
    D3DXMATRIX mtxView, mtxProj;
    mtxView = pCamera->GetViewMatrix();
    mtxProj = pCamera->GetProjectionMatrix();
    D3DXMatrixMultiply(&mViewProj, &mtxView, &mtxProj);

    // ���C�g��`�悷�邩
    if (bRenderLight)
    { // �`�悷��Ƃ�

        D3DXHANDLE hCurrTech;
        hCurrTech = m_pShadowVolume->GetCurrentTechnique();  // Save the current technique
        m_pShadowVolume->SetTechnique("RenderSceneAmbient");
        m_pShadowVolume->SetTexture("g_txScene", m_pDefaultTex);
        D3DXVECTOR4 vLightMat(1.0f, 1.0f, 1.0f, 1.0f);
        m_pShadowVolume->SetVector("g_vMatColor", &vLightMat);
        UINT cPasses;
        m_pShadowVolume->Begin(&cPasses, 0);
        for (UINT p = 0; p < cPasses; ++p)
        {
            m_pShadowVolume->BeginPass(p);

            // ���C�g���X�g�̎擾
            vector<CLight*> pLightList = Component::GetComponents<CLight>(false, true);

            for (unsigned int i = 0; i < pLightList.size(); i++)
            {
                // ���C�g�̎擾
                CLight* pLight = pLightList[i];
                D3DXVECTOR4 lightCol = { 
                    pLight->GetColor().r,
                    pLight->GetColor().g,
                    pLight->GetColor().b,
                    pLight->GetColor().a 
                };
                lightCol *= pLight->GetIntensity();

                mWorldView = pLight->transform->GetMatrix() * pCamera->GetViewMatrix();
                mWorldViewProjection = mWorldView * pCamera->GetProjectionMatrix();
                m_pShadowVolume->SetMatrix("g_mWorldView", &mWorldView);
                m_pShadowVolume->SetMatrix("g_mWorldViewProjection", &mWorldViewProjection);
                m_pShadowVolume->SetVector("g_vAmbient", &lightCol);

                // The effect interface queues up the changes and performs them 
                // with the CommitChanges call. You do not need to call CommitChanges if 
                // you are not setting any parameters between the BeginPass and EndPass.
                m_pShadowVolume->CommitChanges();

                m_pLightMesh->DrawSubset(0);
            }
            m_pShadowVolume->EndPass();
        }
        m_pShadowVolume->End();
        m_pShadowVolume->SetTechnique(hCurrTech); // Restore the old technique
        D3DXVECTOR4 vAmb(pCamera->GetAmbient(), pCamera->GetAmbient(), pCamera->GetAmbient(), 1.0f);
        m_pShadowVolume->SetVector("g_vAmbient", &vAmb);
    }

    // ���b�V�����X�g���擾����
    vector<CMesh*> pMeshList = Component::GetComponents<CMesh>(false, true);

    for (unsigned int nCntModel = 0; nCntModel < pMeshList.size(); nCntModel++)
    {
        // ���f�����擾����
        CMesh* pMesh = pMeshList[nCntModel];
        D3DXMATRIX modelMtx = pMesh->transform->GetMatrix();

        pDevice->SetVertexDeclaration(m_pMeshDecl);
        mWorldView = modelMtx * pCamera->GetViewMatrix();
        mWorldViewProjection = modelMtx * mViewProj;
        m_pShadowVolume->SetMatrix("g_mWorldViewProjection", &mWorldViewProjection);
        m_pShadowVolume->SetMatrix("g_mWorldView", &mWorldView);

        UINT cPasses;
        m_pShadowVolume->Begin(&cPasses, 0);
        for (UINT p = 0; p < cPasses; ++p)
        {
            m_pShadowVolume->BeginPass(p);

            pMat = (D3DXMATERIAL*)pMesh->GetBuffMat()->GetBufferPointer();
            for (int nCntMat = 0; nCntMat < (int)pMesh->GetNumMat(); nCntMat++)
            {
                // �s�����x
                float fAlpha, fBeforeAlpha;
                fBeforeAlpha = pMat[nCntMat].MatD3D.Diffuse.a;
                if (pMesh->GetAlpha() != nullptr)
                {
                    fAlpha = *pMesh->GetAlpha();
                }
                else
                {
                    fAlpha = pMat[nCntMat].MatD3D.Diffuse.a;
                }

                pMat[nCntMat].MatD3D.Diffuse.a = fAlpha;
                m_pShadowVolume->SetVector("g_vMatColor", (D3DXVECTOR4*)&pMat[nCntMat].MatD3D.Diffuse);

                if (pMesh->GetTextures()->at(nCntMat) != nullptr)
                { // �e�N�X�`��������Ƃ�
                    m_pShadowVolume->SetTexture("g_txScene", pMesh->GetTextures()->at(nCntMat));
                }
                else
                { // �e�N�X�`�����Ȃ��Ƃ�
                    m_pShadowVolume->SetTexture("g_txScene", m_pDefaultTex);
                }
                m_pShadowVolume->CommitChanges();
                pMesh->GetMesh()->DrawSubset(nCntMat);

                // �}�e���A���ݒ��߂�
                pMat[nCntMat].MatD3D.Diffuse.a = fBeforeAlpha;
            }

            m_pShadowVolume->EndPass();
        }
        m_pShadowVolume->End();
    }
}

//=============================================================
// [CShadow] �\�̓`�F�b�N
//=============================================================
bool CShadow::CheckShadow(LPDIRECT3D9 pObject, LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS d3dpp)
{
    if (USE_SHADOW)
    {
        // �e�̔\�̓`�F�b�N
        if (!IsDeviceAcceptableShadow(pObject, pDevice, d3dpp))
        {
            return false;
        }

        // �e�̒��_������
        InitVertexDeclarationShadow(pDevice);
    }
    return true;
}

//=============================================================
// �f�o�C�X�̔\�̓`�F�b�N
//=============================================================
bool CShadow::IsDeviceAcceptableShadow(LPDIRECT3D9 pObject, LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS d3dpp)
{
    // �L���b�v���擾����
    D3DCAPS9 pCaps;
    pDevice->GetDeviceCaps(&pCaps);

    // �A���t�@�u�����f�B���O���T�|�[�g���Ȃ��o�b�N�o�b�t�@�`�����X�L�b�v
    if (FAILED(pObject->CheckDeviceFormat(pCaps.AdapterOrdinal,
        pCaps.DeviceType,
        D3DFMT_X8R8G8B8,
        D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING,
        D3DRTYPE_TEXTURE,
        d3dpp.BackBufferFormat)))
    {
        return false;
    }

    // �s�N�Z���V�F�[�_ 2.0�ɑΉ����Ă��邩
    if (pCaps.PixelShaderVersion < D3DPS_VERSION(2, 0))
    {
        return false;
    }

    // �X�e���V���o�b�t�@�ɑΉ����Ă��邩
    if (!IsDepthFormatOk(D3DFMT_D24S8,
        D3DFMT_X8R8G8B8,
        d3dpp.BackBufferFormat,
        pObject))
    {
        return false;
    }

    return true;
}

//=============================================================
// ���_�錾�̏�����
//=============================================================
void CShadow::InitVertexDeclarationShadow(LPDIRECT3DDEVICE9 pDevice)
{
    // �V���h�E�G�t�F�N�g�t�@�C����ǂݍ���
    DWORD dwShaderFlags = D3DXFX_NOT_CLONEABLE;
#if defined( _DEBUG )
    dwShaderFlags |= D3DXSHADER_DEBUG;
#endif
    D3DXCreateEffectFromFile(pDevice,
        SHADOW_VOLUME_PATH.c_str(),
        nullptr,
        nullptr,
        dwShaderFlags,
        nullptr,
        &m_pShadowVolume,
        nullptr);

    // ���_�錾�̏�����
    pDevice->CreateVertexDeclaration(MESHVERT::Decl, &m_pMeshDecl);
    pDevice->CreateVertexDeclaration(SHADOWVERT::Decl, &m_pShadowDecl);

    // �f�o�C�X�̗e�ʂɊ�Â��āA�g�p���郌���_�����O�Z�p�����߂�
    D3DCAPS9 pCaps;
    pDevice->GetDeviceCaps(&pCaps); // �L���b�v�̎擾

    m_hRenderScene = m_pShadowVolume->GetTechniqueByName("RenderScene");

    // ���ʃX�e���V�����T�|�[�g����Ă��邩
    if (pCaps.StencilCaps & D3DSTENCILCAPS_TWOSIDED)
    { // �T�|�[�g���Ă���
        m_hRenderShadow = m_pShadowVolume->GetTechniqueByName("RenderShadowVolume2Sided");
        m_hShowShadow = m_pShadowVolume->GetTechniqueByName("ShowShadowVolume2Sided");
    }
    else
    { // �T�|�[�g���Ă��Ȃ�
        m_hRenderShadow = m_pShadowVolume->GetTechniqueByName("RenderShadowVolume");
        m_hShowShadow = m_pShadowVolume->GetTechniqueByName("ShowShadowVolume");
    }

    // 1x1�̔����e�N�X�`�����쐬����i�f�t�H���g�e�N�X�`���j
    pDevice->CreateTexture(1, 1, 1, 0, D3DFMT_A8R8G8B8,
        D3DPOOL_MANAGED, &m_pDefaultTex, nullptr);
    D3DLOCKED_RECT lr;
    m_pDefaultTex->LockRect(0, &lr, nullptr, 0);
    *(LPDWORD)lr.pBits = D3DCOLOR_RGBA(255, 255, 255, 255);
    m_pDefaultTex->UnlockRect(0);
}

//=============================================================
// �f�v�X�t�H�[�}�b�g���Ή����Ă��邩�𒲂ׂ�
//=============================================================
BOOL CShadow::IsDepthFormatOk(D3DFORMAT DepthFormat,
    D3DFORMAT AdapterFormat,
    D3DFORMAT BackBufferFormat,
    LPDIRECT3D9 pObject)
{
    // �f�v�X�t�H�[�}�b�g�����݂��邱�Ƃ��m�F����
    HRESULT hr = pObject->CheckDeviceFormat(D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        AdapterFormat,
        D3DUSAGE_DEPTHSTENCIL,
        D3DRTYPE_SURFACE,
        DepthFormat);
    if (FAILED(hr)) return FALSE;

    // �o�b�N�o�b�t�@�̃t�H�[�}�b�g���L���ł��邱�Ƃ��m�F����
    hr = pObject->CheckDeviceFormat(D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        AdapterFormat,
        D3DUSAGE_RENDERTARGET,
        D3DRTYPE_SURFACE,
        BackBufferFormat);
    if (FAILED(hr)) return FALSE;

    // �f�v�X�t�H�[�}�b�g���݊��������邱�Ƃ��m�F����
    hr = pObject->CheckDepthStencilMatch(D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        AdapterFormat,
        BackBufferFormat,
        DepthFormat);

    return SUCCEEDED(hr);
}

//=============================================================
// [CShadow] �e���b�V���̐���
//=============================================================
HRESULT CShadow::GenerateShadowMesh(IDirect3DDevice9* pDevice, ID3DXMesh* pMesh, ID3DXMesh** ppOutMesh)
{
    HRESULT hr = S_OK;
    ID3DXMesh* pInputMesh;

    if (!ppOutMesh)
        return E_INVALIDARG;
    *ppOutMesh = nullptr;

    // ���̓��b�V����32bit�C���f�b�N�X���g���ďo�̓��b�V���Ɠ����t�H�[�}�b�g�ɕϊ�����
    hr = pMesh->CloneMesh(D3DXMESH_32BIT, SHADOWVERT::Decl, pDevice, &pInputMesh);
    if (FAILED(hr))
        return hr;

    // �אڏ��̐���
    DWORD* pdwAdj = new DWORD[3 * pInputMesh->GetNumFaces()];
    DWORD* pdwPtRep = new DWORD[pInputMesh->GetNumVertices()];
    if (!pdwAdj || !pdwPtRep)
    {
        delete[] pdwAdj; delete[] pdwPtRep;
        pInputMesh->Release();
        return E_OUTOFMEMORY;
    }

    hr = pInputMesh->GenerateAdjacency(ADJACENCY_EPSILON, pdwAdj);
    if (FAILED(hr))
    {
        delete[] pdwAdj; delete[] pdwPtRep;
        pInputMesh->Release();
        return hr;
    }

    pInputMesh->ConvertAdjacencyToPointReps(pdwAdj, pdwPtRep);
    delete[] pdwAdj;

    SHADOWVERT* pVBData = nullptr;
    DWORD* pdwIBData = nullptr;

    pInputMesh->LockVertexBuffer(0, (LPVOID*)&pVBData);
    pInputMesh->LockIndexBuffer(0, (LPVOID*)&pdwIBData);

    if (pVBData && pdwIBData)
    {
        // �G�b�W�̍ő吔 = �ʂ̐� * 3
        DWORD dwNumEdges = pInputMesh->GetNumFaces() * 3;
        CEdgeMapping* pMapping = new CEdgeMapping[dwNumEdges];
        if (pMapping)
        {
            int nNumMaps = 0;  // pMapping�̃G���g���[��

            // ���b�V�����쐬
            ID3DXMesh* pNewMesh;
            hr = D3DXCreateMesh(pInputMesh->GetNumFaces() + dwNumEdges * 2,
                pInputMesh->GetNumFaces() * 3,
                D3DXMESH_32BIT,
                SHADOWVERT::Decl,
                pDevice,
                &pNewMesh);
            if (SUCCEEDED(hr))
            {
                SHADOWVERT* pNewVBData = nullptr;
                DWORD* pdwNewIBData = nullptr;

                pNewMesh->LockVertexBuffer(0, (LPVOID*)&pNewVBData);
                pNewMesh->LockIndexBuffer(0, (LPVOID*)&pdwNewIBData);

                // ���̒��_�C���f�b�N�X�l���i�[�����IB���̔z��C���f�b�N�X
                int nNextIndex = 0;

                if (pNewVBData && pdwNewIBData)
                {
                    ZeroMemory(pNewVBData, pNewMesh->GetNumVertices() * pNewMesh->GetNumBytesPerVertex());
                    ZeroMemory(pdwNewIBData, sizeof(DWORD) * pNewMesh->GetNumFaces() * 3);

                    // ���̒��_���������ޏꏊ
                    SHADOWVERT* pNextOutVertex = pNewVBData;

                    // �V�������b�V���ɐV�������_�Ɩʂ��o�͂��A���̕ӂ��}�b�s���O�E�e�[�u���ɏ�������
                    for (UINT f = 0; f < pInputMesh->GetNumFaces(); ++f)
                    {
                        // 3���_���ׂĂ̒��_�f�[�^���R�s�[����
                        CopyMemory(pNextOutVertex, pVBData + pdwIBData[f * 3], sizeof(SHADOWVERT));
                        CopyMemory(pNextOutVertex + 1, pVBData + pdwIBData[f * 3 + 1], sizeof(SHADOWVERT));
                        CopyMemory(pNextOutVertex + 2, pVBData + pdwIBData[f * 3 + 2], sizeof(SHADOWVERT));

                        // �ʂ������o��
                        pdwNewIBData[nNextIndex++] = f * 3;
                        pdwNewIBData[nNextIndex++] = f * 3 + 1;
                        pdwNewIBData[nNextIndex++] = f * 3 + 2;

                        // �ʂ̖@�����v�Z���A����𒸓_�̖@���ɑ������
                        D3DXVECTOR3 v1, v2;
                        D3DXVECTOR3 vNormal;
                        v1 = *(D3DXVECTOR3*)(pNextOutVertex + 1) - *(D3DXVECTOR3*)pNextOutVertex;
                        v2 = *(D3DXVECTOR3*)(pNextOutVertex + 2) - *(D3DXVECTOR3*)(pNextOutVertex + 1);
                        D3DXVec3Cross(&vNormal, &v1, &v2);
                        D3DXVec3Normalize(&vNormal, &vNormal);

                        pNextOutVertex->Normal = vNormal;
                        (pNextOutVertex + 1)->Normal = vNormal;
                        (pNextOutVertex + 2)->Normal = vNormal;

                        pNextOutVertex += 3;

                        // �ʂ̃G�b�W���}�b�s���O�e�[�u���ɒǉ�����

                        // �G�b�W1
                        int nIndex;
                        int nVertIndex[3] =
                        {
                            static_cast<int>(pdwPtRep[pdwIBData[f * 3]]),
                            static_cast<int>(pdwPtRep[pdwIBData[f * 3 + 1]]),
                            static_cast<int>(pdwPtRep[pdwIBData[f * 3 + 2]])
                        };
                        nIndex = FindEdgeInMappingTable(nVertIndex[0], nVertIndex[1], pMapping, dwNumEdges);

                        // �G���[�̏ꍇ�͒��f
                        if (-1 == nIndex)
                        {
                            hr = E_INVALIDARG;
                            goto cleanup;
                        }

                        if (pMapping[nIndex].m_anOldEdge[0] == -1 && pMapping[nIndex].m_anOldEdge[1] == -1)
                        {
                            // �G�b�W�̃G���g���[���Ȃ��̂ŏ�����
                            pMapping[nIndex].m_anOldEdge[0] = nVertIndex[0];
                            pMapping[nIndex].m_anOldEdge[1] = nVertIndex[1];
                            pMapping[nIndex].m_aanNewEdge[0][0] = f * 3;
                            pMapping[nIndex].m_aanNewEdge[0][1] = f * 3 + 1;

                            nNumMaps++;
                        }
                        else
                        {
                            // �G�b�W�̃G���g���[���������̂Ŏl�p�`���쐬���ďo�͂���
                            assert(nNumMaps > 0);

                            pMapping[nIndex].m_aanNewEdge[1][0] = f * 3;
                            pMapping[nIndex].m_aanNewEdge[1][1] = f * 3 + 1;

                            // 1�ڂ̎O�p�`
                            pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[0][1];
                            pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[0][0];
                            pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[1][0];

                            // 2�ڂ̎O�p�`
                            pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[1][1];
                            pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[1][0];
                            pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[0][0];

                            // �Ō�̃}�b�v�G���g���[���R�s�[���āA�}�b�v�J�E���g���f�N�������g����
                            pMapping[nIndex] = pMapping[nNumMaps - 1];
                            FillMemory(&pMapping[nNumMaps - 1], sizeof(pMapping[nNumMaps - 1]), 0xFF);
                            nNumMaps--;
                        }

                        // �G�b�W2
                        nIndex = FindEdgeInMappingTable(nVertIndex[1], nVertIndex[2], pMapping, dwNumEdges);

                        // �G���[�̏ꍇ�͒��f
                        if (-1 == nIndex)
                        {
                            hr = E_INVALIDARG;
                            goto cleanup;
                        }

                        if (pMapping[nIndex].m_anOldEdge[0] == -1 && pMapping[nIndex].m_anOldEdge[1] == -1)
                        {
                            pMapping[nIndex].m_anOldEdge[0] = nVertIndex[1];
                            pMapping[nIndex].m_anOldEdge[1] = nVertIndex[2];
                            pMapping[nIndex].m_aanNewEdge[0][0] = f * 3 + 1;
                            pMapping[nIndex].m_aanNewEdge[0][1] = f * 3 + 2;

                            nNumMaps++;
                        }
                        else
                        {
                            // �G�b�W�̃G���g���[���������̂Ŏl�p�`���쐬���ďo�͂���
                            assert(nNumMaps > 0);

                            pMapping[nIndex].m_aanNewEdge[1][0] = f * 3 + 1;
                            pMapping[nIndex].m_aanNewEdge[1][1] = f * 3 + 2;

                            // 1�ڂ̎O�p�`
                            pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[0][1];
                            pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[0][0];
                            pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[1][0];

                            // 2�ڂ̎O�p�`
                            pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[1][1];
                            pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[1][0];
                            pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[0][0];

                            // �Ō�̃}�b�v�G���g���[���R�s�[���āA�}�b�v�J�E���g���f�N�������g����
                            pMapping[nIndex] = pMapping[nNumMaps - 1];
                            FillMemory(&pMapping[nNumMaps - 1], sizeof(pMapping[nNumMaps - 1]), 0xFF);
                            nNumMaps--;
                        }

                        // �G�b�W3
                        nIndex = FindEdgeInMappingTable(nVertIndex[2], nVertIndex[0], pMapping, dwNumEdges);

                        // �G���[�̏ꍇ�͒��f
                        if (-1 == nIndex)
                        {
                            hr = E_INVALIDARG;
                            goto cleanup;
                        }

                        if (pMapping[nIndex].m_anOldEdge[0] == -1 && pMapping[nIndex].m_anOldEdge[1] == -1)
                        {
                            pMapping[nIndex].m_anOldEdge[0] = nVertIndex[2];
                            pMapping[nIndex].m_anOldEdge[1] = nVertIndex[0];
                            pMapping[nIndex].m_aanNewEdge[0][0] = f * 3 + 2;
                            pMapping[nIndex].m_aanNewEdge[0][1] = f * 3;

                            nNumMaps++;
                        }
                        else
                        {
                            // �G�b�W�̃G���g���[���������̂Ŏl�p�`���쐬���ďo�͂���
                            assert(nNumMaps > 0);

                            pMapping[nIndex].m_aanNewEdge[1][0] = f * 3 + 2;
                            pMapping[nIndex].m_aanNewEdge[1][1] = f * 3;

                            // 1�ڂ̎O�p�`
                            pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[0][1];
                            pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[0][0];
                            pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[1][0];

                            // 2�ڂ̎O�p�`
                            pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[1][1];
                            pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[1][0];
                            pdwNewIBData[nNextIndex++] = pMapping[nIndex].m_aanNewEdge[0][0];

                            // �Ō�̃}�b�v�G���g���[���R�s�[���āA�}�b�v�J�E���g���f�N�������g����
                            pMapping[nIndex] = pMapping[nNumMaps - 1];
                            FillMemory(&pMapping[nNumMaps - 1], sizeof(pMapping[nNumMaps - 1]), 0xFF);
                            nNumMaps--;
                        }
                    }


                    // �\���ȑ傫���̒��_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�������b�V�����쐬

                    SHADOWVERT* pPatchVBData = nullptr;
                    DWORD* pdwPatchIBData = nullptr;

                    ID3DXMesh* pPatchMesh = nullptr;
                    // IB�ɏ\���ȃX�y�[�X���m�ۂ��A�e�p�b�`���O�ʂɍő�3�̎l�p�`���g�p����
                    hr = D3DXCreateMesh(nNextIndex / 3 + nNumMaps * 7,
                        (pInputMesh->GetNumFaces() + nNumMaps) * 3,
                        D3DXMESH_32BIT,
                        SHADOWVERT::Decl,
                        pDevice,
                        &pPatchMesh);

                    if (FAILED(hr))
                        goto cleanup;

                    hr = pPatchMesh->LockVertexBuffer(0, (LPVOID*)&pPatchVBData);
                    if (SUCCEEDED(hr))
                        hr = pPatchMesh->LockIndexBuffer(0, (LPVOID*)&pdwPatchIBData);

                    if (pPatchVBData && pdwPatchIBData)
                    {
                        ZeroMemory(pPatchVBData, sizeof(SHADOWVERT) * (pInputMesh->GetNumFaces() + nNumMaps) *
                            3);
                        ZeroMemory(pdwPatchIBData, sizeof(DWORD) * (nNextIndex + 3 * nNumMaps * 7));

                        // ����̃��b�V�����瑼�̃��b�V���Ƀf�[�^���R�s�[����
                        CopyMemory(pPatchVBData, pNewVBData, sizeof(SHADOWVERT) * pInputMesh->GetNumFaces() * 3);
                        CopyMemory(pdwPatchIBData, pdwNewIBData, sizeof(DWORD) * nNextIndex);
                    }
                    else
                    {
                        // �d��ȃG���[�ɂ�胍�b�N�ł��Ȃ��ꍇ
                        pPatchMesh->Release();
                        goto cleanup;
                    }

                    // �X�V���ꂽ���̂ɒu��������
                    pNewMesh->UnlockVertexBuffer();
                    pNewMesh->UnlockIndexBuffer();
                    pNewVBData = pPatchVBData;
                    pdwNewIBData = pdwPatchIBData;
                    pNewMesh->Release();
                    pNewMesh = pPatchMesh;

                    // �e���L�G�b�W�ɑ΂��Ďl�p�`�𐶐�����
                    // �񋤗L�G�b�W���ƂɁA�V�����ʂŊJ�������p�b�`����

                    // ���̒��_�̃C���f�b�N�X
                    int nNextVertex = pInputMesh->GetNumFaces() * 3;

                    for (int i = 0; i < nNumMaps; ++i)
                    {
                        if (pMapping[i].m_anOldEdge[0] != -1 &&
                            pMapping[i].m_anOldEdge[1] != -1)
                        {
                            // 2�Ԗڂ̐V�����G�b�W�̃C���f�b�N�X��-1�ł���΁A���̃G�b�W�͔񋤗L�G�b�W�ł���
                            if (pMapping[i].m_aanNewEdge[1][0] == -1 ||
                                pMapping[i].m_aanNewEdge[1][1] == -1)
                            {
                                // ���݂̕ӂƒ��_�����L����ʂ̔񋤗L�ӂ�������
                                for (int i2 = i + 1; i2 < nNumMaps; ++i2)
                                {
                                    if (pMapping[i2].m_anOldEdge[0] != -1 &&
                                        pMapping[i2].m_anOldEdge[1] != -1 &&
                                        (pMapping[i2].m_aanNewEdge[1][0] == -1 ||
                                            pMapping[i2].m_aanNewEdge[1][1] == -1))
                                    {
                                        int nVertShared = 0;
                                        if (pMapping[i2].m_anOldEdge[0] == pMapping[i].m_anOldEdge[1])
                                            ++nVertShared;
                                        if (pMapping[i2].m_anOldEdge[1] == pMapping[i].m_anOldEdge[0])
                                            ++nVertShared;

                                        if (2 == nVertShared)
                                        {
                                            // �k�ގl�ӌ`���쐬�ł���悤�ɂ���
                                            pMapping[i2].m_aanNewEdge[1][0] = pMapping[i].m_aanNewEdge[0][0];
                                            pMapping[i2].m_aanNewEdge[1][1] = pMapping[i].m_aanNewEdge[0][1];
                                            break;
                                        }
                                        else if (1 == nVertShared)
                                        {
                                            // �ǂ���̃G�b�W����������̃G�b�W���O�ɂ��邩
                                            int nBefore, nAfter;
                                            if (pMapping[i2].m_anOldEdge[0] == pMapping[i].m_anOldEdge[1])
                                            {
                                                nBefore = i;
                                                nAfter = i2;
                                            }
                                            else
                                            {
                                                nBefore = i2;
                                                nAfter = i;
                                            }

                                            // 2�̕ӂ���2�̑މ������l�p�`�ƈꏏ�ɖʂ����

                                            pNewVBData[nNextVertex] = pNewVBData[pMapping[nAfter].m_aanNewEdge[0][1]];
                                            pNewVBData[nNextVertex +
                                                1] = pNewVBData[pMapping[nBefore].m_aanNewEdge[0][1]];
                                            pNewVBData[nNextVertex +
                                                2] = pNewVBData[pMapping[nBefore].m_aanNewEdge[0][0]];

                                            // �@�����Čv�Z����
                                            D3DXVECTOR3 v1 = pNewVBData[nNextVertex + 1].Position -
                                                pNewVBData[nNextVertex].Position;
                                            D3DXVECTOR3 v2 = pNewVBData[nNextVertex + 2].Position -
                                                pNewVBData[nNextVertex + 1].Position;
                                            D3DXVec3Normalize(&v1, &v1);
                                            D3DXVec3Normalize(&v2, &v2);
                                            D3DXVec3Cross(&pNewVBData[nNextVertex].Normal, &v1, &v2);
                                            pNewVBData[nNextVertex + 1].Normal = pNewVBData[nNextVertex +
                                                2].Normal = pNewVBData[nNextVertex].Normal;

                                            pdwNewIBData[nNextIndex] = nNextVertex;
                                            pdwNewIBData[nNextIndex + 1] = nNextVertex + 1;
                                            pdwNewIBData[nNextIndex + 2] = nNextVertex + 2;

                                            // 1�ڂ̎l�p�`

                                            pdwNewIBData[nNextIndex + 3] = pMapping[nBefore].m_aanNewEdge[0][1];
                                            pdwNewIBData[nNextIndex + 4] = pMapping[nBefore].m_aanNewEdge[0][0];
                                            pdwNewIBData[nNextIndex + 5] = nNextVertex + 1;

                                            pdwNewIBData[nNextIndex + 6] = nNextVertex + 2;
                                            pdwNewIBData[nNextIndex + 7] = nNextVertex + 1;
                                            pdwNewIBData[nNextIndex + 8] = pMapping[nBefore].m_aanNewEdge[0][0];

                                            // 2�ڂ̎l�p�`

                                            pdwNewIBData[nNextIndex + 9] = pMapping[nAfter].m_aanNewEdge[0][1];
                                            pdwNewIBData[nNextIndex + 10] = pMapping[nAfter].m_aanNewEdge[0][0];
                                            pdwNewIBData[nNextIndex + 11] = nNextVertex;

                                            pdwNewIBData[nNextIndex + 12] = nNextVertex + 1;
                                            pdwNewIBData[nNextIndex + 13] = nNextVertex;
                                            pdwNewIBData[nNextIndex + 14] = pMapping[nAfter].m_aanNewEdge[0][0];

                                            // �V�����ǉ����ꂽ�ʂ�3�Ԗڂ̃G�b�W�𔽉f����悤�ɁAi2���C������

                                            if (pMapping[i2].m_anOldEdge[0] == pMapping[i].m_anOldEdge[1])
                                            {
                                                pMapping[i2].m_anOldEdge[0] = pMapping[i].m_anOldEdge[0];
                                            }
                                            else
                                            {
                                                pMapping[i2].m_anOldEdge[1] = pMapping[i].m_anOldEdge[1];
                                            }
                                            pMapping[i2].m_aanNewEdge[0][0] = nNextVertex + 2;
                                            pMapping[i2].m_aanNewEdge[0][1] = nNextVertex;

                                            // ���̒��_�ƃC���f�b�N�X�̈ʒu���X�V����

                                            nNextVertex += 3;
                                            nNextIndex += 15;

                                            break;
                                        }
                                    }
                                }
                            }
                            else
                            {
                                // �k�ނ����l�p�`�����

                                // 1�ڂ̎O�p�`
                                pdwNewIBData[nNextIndex++] = pMapping[i].m_aanNewEdge[0][1];
                                pdwNewIBData[nNextIndex++] = pMapping[i].m_aanNewEdge[0][0];
                                pdwNewIBData[nNextIndex++] = pMapping[i].m_aanNewEdge[1][0];

                                // 2�ڂ̎O�p�`
                                pdwNewIBData[nNextIndex++] = pMapping[i].m_aanNewEdge[1][1];
                                pdwNewIBData[nNextIndex++] = pMapping[i].m_aanNewEdge[1][0];
                                pdwNewIBData[nNextIndex++] = pMapping[i].m_aanNewEdge[0][0];
                            }
                        }
                    }
                }

            cleanup:;
                if (pNewVBData)
                {
                    pNewMesh->UnlockVertexBuffer();
                    pNewVBData = nullptr;
                }
                if (pdwNewIBData)
                {
                    pNewMesh->UnlockIndexBuffer();
                    pdwNewIBData = nullptr;
                }

                if (SUCCEEDED(hr))
                {
                    // �o�͂���郁�b�V���̃C���f�b�N�X�o�b�t�@�͎��ۂɕK�v�ȃT�C�Y���傫����������Ȃ��̂�
                    // �K�v��IB�T�C�Y�𐳊m�Ɏ��ʂ̃��b�V�����쐬���ďo�͂���
                    // 32�r�b�g���K�v�Ȃ����16�r�b�g�̃C���f�b�N�X���g�p����
                    bool bNeed32Bit = (pInputMesh->GetNumFaces() + nNumMaps) * 3 > 65535;
                    ID3DXMesh* pFinalMesh;
                    hr = D3DXCreateMesh(nNextIndex / 3,
                        (pInputMesh->GetNumFaces() + nNumMaps) * 3,
                        D3DXMESH_WRITEONLY | (bNeed32Bit ? D3DXMESH_32BIT : 0),
                        SHADOWVERT::Decl,
                        pDevice,
                        &pFinalMesh);
                    if (SUCCEEDED(hr))
                    {
                        pNewMesh->LockVertexBuffer(0, (LPVOID*)&pNewVBData);
                        pNewMesh->LockIndexBuffer(0, (LPVOID*)&pdwNewIBData);

                        SHADOWVERT* pFinalVBData = nullptr;
                        WORD* pwFinalIBData = nullptr;

                        pFinalMesh->LockVertexBuffer(0, (LPVOID*)&pFinalVBData);
                        pFinalMesh->LockIndexBuffer(0, (LPVOID*)&pwFinalIBData);

                        if (pNewVBData && pdwNewIBData && pFinalVBData && pwFinalIBData)
                        {
                            CopyMemory(pFinalVBData, pNewVBData, sizeof(SHADOWVERT) *
                                (pInputMesh->GetNumFaces() + nNumMaps) * 3);

                            if (bNeed32Bit)
                                CopyMemory(pwFinalIBData, pdwNewIBData, sizeof(DWORD) * nNextIndex);
                            else
                            {
                                for (int i = 0; i < nNextIndex; ++i)
                                    pwFinalIBData[i] = (WORD)pdwNewIBData[i];
                            }
                        }

                        if (pNewVBData)
                            pNewMesh->UnlockVertexBuffer();
                        if (pdwNewIBData)
                            pNewMesh->UnlockIndexBuffer();
                        if (pFinalVBData)
                            pFinalMesh->UnlockVertexBuffer();
                        if (pwFinalIBData)
                            pFinalMesh->UnlockIndexBuffer();

                        // �j������
                        pNewMesh->Release();
                        pNewMesh = pFinalMesh;
                    }

                    *ppOutMesh = pNewMesh;
                }
                else
                    pNewMesh->Release();
            }
            delete[] pMapping;
        }
        else
            hr = E_OUTOFMEMORY;
    }
    else
        hr = E_FAIL;

    if (pVBData)
        pInputMesh->UnlockVertexBuffer();

    if (pdwIBData)
        pInputMesh->UnlockIndexBuffer();

    delete[] pdwPtRep;
    pInputMesh->Release();

    return hr;
}

//=============================================================
// [CShadow] �}�b�s���O�e�[�u������G�b�W��T������
//=============================================================
int CShadow::FindEdgeInMappingTable(int nV1, int nV2, CEdgeMapping* pMapping, int nCount)
{
    for (int i = 0; i < nCount; ++i)
    {
        // �}�b�s���O�G���g���̌Â��G�b�W�̒��_�C���f�b�N�X�������Ƃ� -1 �̏ꍇ�A��v����G���g���������炸�ɗL���ȃG���g�������ׂČ����������ƂɂȂ�
        // ���̃C���f�b�N�X��V�����쐬�����G���g���Ƃ��ĕԂ�
        if ((pMapping[i].m_anOldEdge[0] == -1 && pMapping[i].m_anOldEdge[1] == -1) ||

            // ��v������̂�����΃C���f�b�N�X��Ԃ�
            (pMapping[i].m_anOldEdge[1] == nV1 && pMapping[i].m_anOldEdge[0] == nV2))
        {
            return i;
        }
    }

    return -1;
}
