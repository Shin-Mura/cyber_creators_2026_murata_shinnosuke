//=============================================================
//
// �e [shadow.h]
// Author: Ito Kotaro
//
//=============================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "general/main.h"

class CCamera;

class CShadow
{
public:
    CShadow();
    ~CShadow();

    void Init();
    void Uninit();
    void Draw(CCamera* pCamera);
    static HRESULT GenerateShadowMesh(IDirect3DDevice9* pDevice, ID3DXMesh* pMesh, ID3DXMesh** ppOutMesh);
	bool CheckShadow(LPDIRECT3D9 pObject, LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS d3dpp);

    // �G�b�W�̃}�b�s���O
    struct CEdgeMapping
    {
        int m_anOldEdge[2];         // ���̕ӂ̒��_�C���f�b�N�X
        int m_aanNewEdge[2][2]; // �V�����G�b�W�̒��_�C���f�b�N�X
    public:
        CEdgeMapping()
        {
            FillMemory(m_anOldEdge, sizeof(m_anOldEdge), -1);
            FillMemory(m_aanNewEdge, sizeof(m_aanNewEdge), -1);
        }
    };

    // �V���h�E�̕`��^�C�v
    enum RENDER_TYPE
    {
        RENDERTYPE_SCENE,                   // �V�[���i�ʏ�j
        RENDERTYPE_SHADOWVOLUME    // �V���h�E�{�����[��
    };

	// ��`
    static const float FAR_CLIP;
	static const bool USE_SHADOW;								// �e��L���ɂ��邩�i�L���ɂ����ꍇ�ł��e�𐶐����Ȃ��I�v�V������I���ł��܂��j
	static const std::string SHADOW_VOLUME_PATH;		// �V���h�E�{�����[���̃p�X
	static const float ADJACENCY_EPSILON;
	static const float EXTRUDE_EPSILON;
    static const RENDER_TYPE RENDER_MODE;
private:
    void DrawShadow(CCamera* pCamera);
    void RenderMesh(CCamera* pCamera, bool bRenderLight);

	bool IsDeviceAcceptableShadow(LPDIRECT3D9 pObject, LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS d3dpp);	// �\�̓`�F�b�N
	void InitVertexDeclarationShadow(LPDIRECT3DDEVICE9 pDevice);																						// ���_�錾�̏�����
	BOOL IsDepthFormatOk(D3DFORMAT DepthFormat, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, LPDIRECT3D9 pObject);
    static int FindEdgeInMappingTable(int nV1, int nV2, CEdgeMapping* pMapping, int nCount);

	ID3DXEffect* m_pShadowVolume;
    IDirect3DVertexDeclaration9* m_pMeshDecl;
    IDirect3DVertexDeclaration9* m_pShadowDecl;
    D3DXHANDLE                       m_hRenderShadow;           // �e�������_�����O���邽�߂̃e�N�j�b�N�n���h��
    D3DXHANDLE                       m_hShowShadow;             // �V���h�E�{�����[����\������e�N�j�b�N�n���h��
    D3DXHANDLE                       m_hRenderScene;              // �V�[���������_�����O���邽�߂̃e�N�j�b�N�n���h��
    IDirect3DTexture9*               m_pDefaultTex;
    LPD3DXMESH                        m_pLightMesh;
};

#endif // !_SHADOW_H_
