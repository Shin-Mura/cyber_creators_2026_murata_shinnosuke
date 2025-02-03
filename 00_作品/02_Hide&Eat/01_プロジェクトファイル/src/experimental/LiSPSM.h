//=============================================================
//
// LiSPSM [LiSPSM.h]
// Author: Ito Kotaro
//
//=============================================================
#ifndef _LISPSM_H_
#define _LISPSM_H_

#include "component/3d/camera.h"

//------------------------------------------------------------------------------
//! �|�C���g���X�g�N���X
class	CVec3List {
private:
	std::vector<D3DXVECTOR3>		m_cPointList;

public:
	//! �R���X�g���N�^
	CVec3List() {}
	//! �f�X�g���N�^
	~CVec3List() { m_cPointList.clear(); }

	//! �|�C���g��ǉ�����
	void	Add(D3DXVECTOR3& vec)
	{
		m_cPointList.push_back(vec);
	}

	//! �|�C���g���N���A����
	void	Clear(void)
	{
		m_cPointList.clear();
	}

	//! �|�C���g��ϊ�����
	void	Transform(D3DXMATRIX* pMat)
	{
		int		num = m_cPointList.size();
		for (int i = 0; i < num; i++) {
			D3DXVECTOR3		vec = m_cPointList[i];
			D3DXVec3TransformCoord(&vec, &vec, pMat);
			m_cPointList[i] = vec;
		}
	}

	//! AABB���擾����
	void	GetAABB(D3DXVECTOR3* pMax, D3DXVECTOR3* pMin)
	{
		int		num = m_cPointList.size();
		if (num > 0) {
			*pMax = *pMin = m_cPointList[0];
			for (int i = 1; i < num; i++) {
				if (pMax->x < m_cPointList[i].x) { pMax->x = m_cPointList[i].x; }
				else if (pMin->x > m_cPointList[i].x) { pMin->x = m_cPointList[i].x; }
				if (pMax->y < m_cPointList[i].y) { pMax->y = m_cPointList[i].y; }
				else if (pMin->y > m_cPointList[i].y) { pMin->y = m_cPointList[i].y; }
				if (pMax->z < m_cPointList[i].z) { pMax->z = m_cPointList[i].z; }
				else if (pMin->z > m_cPointList[i].z) { pMin->z = m_cPointList[i].z; }
			}
		}
	}

	CVec3List& operator=(const CVec3List& b)
	{
		Clear();
		int		num = b.m_cPointList.size();
		for (int i = 0; i < num; i++) {
			m_cPointList.push_back(b.m_cPointList[i]);
		}
		return *this;
	}

	D3DXVECTOR3& operator[](int n)
	{
		return m_cPointList[n];
	}
};

// LiSPSM
class CLiSPSM
{
public:
    void Init();
    void Uninit();
	void Draw(CCamera* pCamera);
    void DrawShadowMap();
    void DrawReceiver();
    void DrawTexture();
    void CalcLightTrans();

    ID3DXEffect* GetShadowMap() { return m_pShadowMap; }
	LPDIRECT3DTEXTURE9 GetShadowTex() { return m_pShadowTex; }
    LPDIRECT3DSURFACE9& GetBackBuffer() { return m_pBackBuffer; }
    LPDIRECT3DSURFACE9& GetZBuffer() { return m_pZBuffer; }
private:
	void CalcLispMatrix(CVec3List* pList);
	void CalcPointsOfViewBolume(CVec3List* pList, D3DXMATRIX& matView, float fAngle, float fAspect, float fNear, float fFar);
	void CalcUpVector(D3DXVECTOR3* pUp, const D3DXVECTOR3* pView, const D3DXVECTOR3* pLight);
	void ScaleMatrixToFit(D3DXMATRIX* pOut, const D3DXVECTOR3* pMax, const D3DXVECTOR3* pMin);

	CCamera* pTargetCamera;
    ID3DXEffect* m_pShadowMap;                                   // �V���h�E�}�b�v
    LPDIRECT3DTEXTURE9 m_pShadowTex;                     // �V���h�E�e�N�X�`��
    LPDIRECT3DVERTEXDECLARATION9 m_pVertDecl0;	    // ���_�錾
    LPDIRECT3DVERTEXDECLARATION9 m_pVertDecl1;		// ���_�錾
    LPDIRECT3DSURFACE9 m_pBackBuffer;
    LPDIRECT3DSURFACE9 m_pZBuffer;
    LPDIRECT3DSURFACE9 m_pRenderZ;

    D3DXHANDLE m_aDrawEffHan[8];

	D3DXMATRIX				m_matLightTrans;					// ���C�g�ϊ��s��
	D3DXVECTOR3			m_vLightDir;							// ���C�g�̕���
	D3DXVECTOR3			m_vLightAngle;						// ���C�g�̊p�x
};

#endif // !_LISPSM_H_
