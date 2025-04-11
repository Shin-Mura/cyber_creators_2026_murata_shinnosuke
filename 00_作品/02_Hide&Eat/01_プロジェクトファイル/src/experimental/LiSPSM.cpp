//=============================================================
//
// LiSPSM [LiSPSM.cpp]
// Author: Ito Kotaro
//
//=============================================================
#include "LiSPSM.h"
#include "renderer.h"

//=============================================================
// [CLiSPSM] ������
//=============================================================
void CLiSPSM::Init()
{
    // �f�o�C�X���擾����
    LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

    // �V���h�E�G�t�F�N�g�t�@�C����ǂݍ���
    DWORD dwShaderFlags = D3DXFX_NOT_CLONEABLE;
#if defined( _DEBUG )
    dwShaderFlags |= D3DXSHADER_DEBUG;
#endif
    HRESULT result = D3DXCreateEffectFromFile(pDevice,
        "data\\SHADER\\ShadowMap.fx",
        nullptr,
        nullptr,
        dwShaderFlags,
        nullptr,
        &m_pShadowMap,
        nullptr);

    // ���_�錾���쐬����
    D3DVERTEXELEMENT9 decl0[] = {
        {0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
        {0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0},
        D3DDECL_END()
    };
    if (FAILED(pDevice->CreateVertexDeclaration(decl0, &m_pVertDecl0)))
    {
        return;
    }
    D3DVERTEXELEMENT9 decl1[] = {
        {0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
        {0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
        D3DDECL_END()
    };
    if (FAILED(pDevice->CreateVertexDeclaration(decl1, &m_pVertDecl1)))
    {
        return;
    }

    if (FAILED(pDevice->CreateDepthStencilSurface(1024, 1024, D3DFMT_D24S8,
        D3DMULTISAMPLE_NONE, 0, TRUE, &m_pRenderZ, NULL))) {
        return;
    }

    // �e�N�X�`�����쐬����
    if (FAILED(pDevice->CreateTexture(1024, 1024, 1, D3DUSAGE_RENDERTARGET,
        D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pShadowTex, NULL))) {
        return;
    }
}

//=============================================================
// [CLiSPSM] �I��
//=============================================================
void CLiSPSM::Uninit()
{
    // �G�t�F�N�g�̔j��
    if (m_pShadowMap != nullptr)
    {
        m_pShadowMap->Release();
        m_pShadowMap = nullptr;
    }
}

//=============================================================
// [CLiSPSM] �`��
//=============================================================
void CLiSPSM::Draw(CCamera* pCamera)
{
    pTargetCamera = pCamera;

    CalcLightTrans();
    DrawShadowMap();
    DrawReceiver();
    DrawTexture();
}

//=============================================================
// [CLiSPSM] �V���h�E�}�b�v�̕`��
//=============================================================
void CLiSPSM::DrawShadowMap()
{
    // �f�o�C�X���擾����
    LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

    LPDIRECT3DSURFACE9 pTarget = nullptr;

    // �����_�����O�^�[�Q�b�g��ύX����
    m_pShadowTex->GetSurfaceLevel(0, &pTarget);
    pDevice->SetRenderTarget(0, pTarget);
    pDevice->SetRenderTarget(0, m_pBackBuffer);
    // �F�����AZ�o�b�t�@��1.0f�ɃN���A����
    //pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0);

    // �`�悷��
    m_pShadowMap->SetTechnique(m_aDrawEffHan[1]);
    pDevice->SetVertexDeclaration(m_pVertDecl0);

    u_int pass;
    D3DXMATRIX trans, matW;

    // �I�u�W�F�N�g�`�揈�����s��
    std::vector<GameObject*> pGameObjects = GameObject::GetAllGameObjects();
    for (unsigned int i = 0; i < pGameObjects.size(); i++)
    {
        if (pGameObjects[i]->GetActive())
        {
            for (unsigned int n = 0; n < pGameObjects[i]->GetComponents().size(); n++)
            {
                if (pGameObjects[i]->GetComponents()[n]->enabled)
                {
                    matW = pGameObjects[i]->transform->GetMatrix();
                    D3DXMatrixMultiply(&trans, &matW, &m_matLightTrans);
                    m_pShadowMap->SetMatrix("matLS", &trans);
                    m_pShadowMap->Begin(&pass, 0);
                    for (unsigned int i = 0; i < pass; i++) {
                        m_pShadowMap->BeginPass(i);

                        // �`�揈��
                        pGameObjects[i]->GetComponents()[n]->Draw();

                        m_pShadowMap->EndPass();
                    }
                    m_pShadowMap->End();
                }
            }
        }
    }



    // ���ɖ߂�
    pDevice->SetRenderTarget(0, m_pBackBuffer);
    pDevice->SetDepthStencilSurface(m_pZBuffer);

    // �^�[�Q�b�g��j������
    if (pTarget != nullptr)
    {
        pTarget->Release();
        pTarget = nullptr;
    }
}

//=============================================================
// [CLiSPSM] ���V�[�u�̕`��
//=============================================================
void CLiSPSM::DrawReceiver()
{
    // �f�o�C�X���擾����
    LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

    m_pShadowMap->SetTechnique(m_aDrawEffHan[2]);
    m_pShadowMap->SetTexture("texRender", m_pShadowTex);
    pDevice->SetVertexDeclaration(m_pVertDecl0);

    // �`��
    u_int pass;
    D3DXMATRIX wvp, matV, matP;

    // �I�u�W�F�N�g�`�揈�����s��
    std::vector<GameObject*> pGameObjects = GameObject::GetAllGameObjects();
    for (unsigned int i = 0; i < pGameObjects.size(); i++)
    {
        if (pGameObjects[i]->GetActive())
        {
            for (unsigned int n = 0; n < pGameObjects[i]->GetComponents().size(); n++)
            {
                if (pGameObjects[i]->GetComponents()[n]->enabled)
                {
                    matV = pTargetCamera->GetViewMatrix();
                    matP = pTargetCamera->GetProjectionMatrix();
                    D3DXMatrixMultiply(&wvp, &matV, &matP);
                    m_pShadowMap->SetMatrix("matWVP", &wvp);
                    m_pShadowMap->SetMatrix("matLS", &m_matLightTrans);

                    m_pShadowMap->Begin(&pass, 0);
                    for (unsigned int i = 0; i < pass; i++) {
                        m_pShadowMap->BeginPass(i);

                        // �`��
                        pGameObjects[i]->GetComponents()[n]->Draw();

                        m_pShadowMap->EndPass();
                    }
                    m_pShadowMap->End();
                }
            }
        }
    }
}

//=============================================================
// [CLiSPSM] �e�N�X�`���̕`��
//=============================================================
void CLiSPSM::DrawTexture()
{
    // �f�o�C�X���擾����
    LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();
    
    // �ʏ�`��
    u_int pass;
    m_pShadowMap->SetTechnique(m_aDrawEffHan[3]);

    std::vector<GameObject*> pGameObjects = GameObject::GetAllGameObjects();
    for (unsigned int i = 0; i < pGameObjects.size(); i++)
    {
        if (pGameObjects[i]->GetActive())
        {
            for (unsigned int n = 0; n < pGameObjects[i]->GetComponents().size(); n++)
            {
                if (pGameObjects[i]->GetComponents()[n]->enabled)
                {
                    m_pShadowMap->Begin(&pass, 0);

                    m_pShadowMap->SetTexture("texRender", m_pShadowTex);
                    pDevice->SetVertexDeclaration(m_pVertDecl1);

                    for (unsigned int i = 0; i < pass; i++)
                    {
                        m_pShadowMap->BeginPass(i);

                        // �`��
                        pDevice->SetTexture(1, m_pShadowTex);
                        pGameObjects[i]->GetComponents()[n]->Draw();

                        m_pShadowMap->EndPass();
                    }

                    m_pShadowMap->End();

                }
            }
        }
    }
}

//=============================================================
// [CLiSPSM] ���C�g�̌v�Z
//=============================================================
void CLiSPSM::CalcLightTrans()
{
    D3DXVECTOR3		vLight(0.0f, 0.0f, -1.0f);
    D3DXMATRIX		mat;
    D3DXMATRIX mtxView = pTargetCamera->GetViewMatrix();
    D3DXMATRIX mtxProj = pTargetCamera->GetProjectionMatrix();
    D3DXMatrixRotationYawPitchRoll(&mat, m_vLightAngle.y, m_vLightAngle.x, 0.0f);
    D3DXVec3TransformNormal(&vLight, &vLight, &mat);

    m_vLightDir = vLight;

    // �r���[�{�����[�������߂�
    CVec3List	cList;
    CalcPointsOfViewBolume(&cList, mtxView, D3DXToRadian(45.0f), 4.0f / 3.0f, 1.0f, 100.0f);

    // �ϊ��s������߂�
    CalcLispMatrix(&cList);
    D3DXMatrixMultiply(&m_matLightTrans, &mtxView, &mtxProj);
}

//=============================================================
// [CLiSPSM] ��x�N�g�������߂�
//=============================================================
void CLiSPSM::CalcUpVector(D3DXVECTOR3* pUp, const D3DXVECTOR3* pView, const D3DXVECTOR3* pLight)
{
    D3DXVECTOR3		left;

    D3DXVec3Cross(&left, pView, pLight);
    D3DXVec3Cross(pUp, pLight, &left);
    D3DXVec3Normalize(pUp, pUp);
}

//=============================================================
// [CLiSPSM] �s��� (-1, -1, -1) �` (1, 1, 1) �͈̔͂ɂ��킹��
//=============================================================
void CLiSPSM::ScaleMatrixToFit(D3DXMATRIX* pOut, const D3DXVECTOR3* pMax, const D3DXVECTOR3* pMin)
{
    pOut->_11 = 2.0f / (pMax->x - pMin->x);
    pOut->_21 = 0.0f;
    pOut->_31 = 0.0f;
    pOut->_41 = -(pMax->x + pMin->x) / (pMax->x - pMin->x);

    pOut->_12 = 0.0f;
    pOut->_22 = 2.0f / (pMax->y - pMin->y);
    pOut->_32 = 0.0f;
    pOut->_42 = -(pMax->y + pMin->y) / (pMax->y - pMin->y);

    pOut->_13 = 0.0f;
    pOut->_23 = 0.0f;
    pOut->_33 = 1.0f / (pMax->z - pMin->z);
    pOut->_43 = -pMin->z / (pMax->z - pMin->z);

    pOut->_14 = 0.0f;
    pOut->_24 = 0.0f;
    pOut->_34 = 0.0f;
    pOut->_44 = 1.0f;
}

//=============================================================
// [CLiSPSM] LiSPSM�̕ϊ��s������߂�
//=============================================================
void CLiSPSM::CalcLispMatrix(CVec3List* pList)
{
    D3DXVECTOR3		min, max;
    D3DXVECTOR3		up;
    D3DXMATRIX		matLisp;
    CVec3List		ListCopy = *pList;
    D3DXVECTOR3 vViewDir = pTargetCamera->GetPosR() - pTargetCamera->transform->GetWPos();
    D3DXVec3Normalize(&vViewDir, &vViewDir);
    float			cosGamma = D3DXVec3Dot(&vViewDir, &m_vLightAngle);
    float			sinGamma = sqrtf(1.0f - cosGamma * cosGamma);

    D3DXMATRIX mtxView = pTargetCamera->GetViewMatrix();
    D3DXMATRIX mtxProj = pTargetCamera->GetProjectionMatrix();
    D3DXVECTOR3 vEye = pTargetCamera->transform->GetWPos();

    // �A�b�v�x�N�g�������߂�
    CalcUpVector(&up, &vViewDir, &m_vLightDir);

    // �J�������_�A���C�g�x�N�g���A�A�b�v�x�N�g������r���[�s������߂�
    D3DXVECTOR3 vAt = vEye + m_vLightDir;
    D3DXMatrixLookAtLH(&mtxView, &vEye, &vAt, &up);

    // �|�C���g���X�g��ϊ�����
    ListCopy.Transform(&mtxView);

    // �ϊ������|�C���g���X�g������AABB���擾����
    ListCopy.GetAABB(&max, &min);

    // ���C�g�X�y�[�X�ɐ����ȃr���[�̃j�A�N���b�v�ʂƃt�@�[�N���b�v�ʂ����߂�
    // AABB �̓��C�g�̃r���[�s��ŕϊ�����Ă���̂� y ����L�r���[�̉��s���ɂȂ�
#if		0
    float			factor = 1.0f / sinGamma;
    float			z_n = factor * pStatus->fNearDist;
    float			d = max.y - min.y;
    float			z_f = z_n + d * sinGamma;
    float			n = (z_n + sqrtf(z_f * z_n)) * factor;
    float			f = n + d;
    D3DXVECTOR3		pos;

    // �V�������_�����߂�
    pos = pStatus->vEyePos - (up * (n - pStatus->fNearDist));

    // �V�������C�g�r���[�s������߂�
    D3DXMatrixLookAtLH(&(pStatus->matView), &pos, &(pos + pStatus->vLightDir), &up);

    // �j�A�N���b�v�ʂƃt�@�[�N���b�v�ʂ���Y�����ւ̓����ϊ��s������߂�
    D3DXMatrixIdentity(&matLisp);
    matLisp._22 = f / (f - n);
    matLisp._42 = -f * n / (f - n);
    matLisp._24 = 1.0f;
    matLisp._44 = 0.0f;

    // ���݂̃��C�g���_����̕ϊ��s������߂�
    D3DXMATRIX	matLVP;
    D3DXMatrixMultiply(&matLVP, &(pStatus->matView), &matLisp);

    // ���̍s��Ō��̃|�C���g���X�g��ϊ�����
    ListCopy = *pList;
    ListCopy.Transform(&matLVP);
#else
    float	d = max.y - min.y;
    float	n = (min.y > 0.0f) ? (min.y + d * 0.1f) : (d * 0.25f);
    float	f = n + d;
    float	p = min.y - n;

    // �j�A�N���b�v�ʂƃt�@�[�N���b�v�ʂ���Y�����ւ̓����ϊ��s������߂�
    D3DXMatrixIdentity(&matLisp);
    matLisp._22 = f / (f - n);
    matLisp._42 = -f * n / (f - n);
    matLisp._24 = 1.0f;
    matLisp._44 = 0.0f;

    // ���݂̃��C�g���_����̕ϊ��s������߂�
    D3DXMATRIX	matLVP;
    D3DXMatrixTranslation(&matLVP, 0.0f, -p, 0.0f);
    D3DXMatrixMultiply(&mtxView, &mtxView, &matLVP);
    D3DXMatrixMultiply(&matLVP, &matLVP, &matLisp);

    // ���̍s��Ń|�C���g���X�g��ϊ�����
    ListCopy.Transform(&matLVP);
#endif
    // AABB���擾����
    ListCopy.GetAABB(&max, &min);

    // ��L��AABB�� (-1, -1, 0) �` (1, 1, 1) �͈̔͂ɂȂ�悤�ȍs����쐬����
    // �ʒu�ƃT�C�Y�𐳊m�Ȃ��̂ɂ��邽��
    ScaleMatrixToFit(&mtxProj, &max, &min);

    // �ŏI�I�ȓ����ϊ��s������߂�
    D3DXMatrixMultiply(&mtxProj, &matLisp, &mtxProj);
}

//=============================================================
// [CLiSPSM] �������8�_�����߂�
//=============================================================
void CLiSPSM::CalcPointsOfViewBolume(CVec3List* pList, D3DXMATRIX& matView, float fAngle, float fAspect, float fNear, float fFar)
{
    pList->Clear();

    float	t = tanf(fAngle / 2.0f);
    float	fNLen = t * fNear;
    float	fFLen = t * fFar;
    D3DXVECTOR3		vPos;

    // �j�A�v���[���̓_�����߂�
    vPos.x = fNLen * fAspect;
    vPos.y = fNLen;
    vPos.z = fNear;
    pList->Add(vPos);
    vPos.x = -vPos.x;
    pList->Add(vPos);
    vPos.y = -vPos.y;
    pList->Add(vPos);
    vPos.x = -vPos.x;
    pList->Add(vPos);

    // �t�@�[�v���[���̓_�����߂�
    vPos.x = fFLen * fAspect;
    vPos.y = fFLen;
    vPos.z = fFar;
    pList->Add(vPos);
    vPos.x = -vPos.x;
    pList->Add(vPos);
    vPos.y = -vPos.y;
    pList->Add(vPos);
    vPos.x = -vPos.x;
    pList->Add(vPos);

    // �r���[�s��̋t�s��ŕϊ�����
    D3DXMATRIX	matInvView;
    D3DXMatrixInverse(&matInvView, NULL, &matView);
    pList->Transform(&matInvView);
}