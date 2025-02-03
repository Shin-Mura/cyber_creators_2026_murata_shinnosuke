//=============================================================
//
// ���b�V���R���|�[�l���g [mesh.h]
// Author: Ito Kotaro
//
//=============================================================
#ifndef _MESH_H_
#define _MESH_H_

#include <component.h>
#include "main.h"

// ���b�V��
class CMesh : public Component
{
public:
	CMesh();
	CMesh(std::string sPath, bool bShadow = true);
	void Init();
	void Uninit();
	void Draw();
	HRESULT LoadMeshX(std::string sPath, bool bShadow = true);
	HRESULT SetMesh(LPD3DXMESH pMesh);
	ID3DXMesh* GetShadowMesh() { return m_pShadowMesh; }
	LPD3DXMESH GetMesh() { return m_pMesh; }
	LPD3DXBUFFER GetBuffMat() { return m_pBuffMat; }
	DWORD GetNumMat() { return m_dwNumMat; }
	void SetTexture(int nIdx, LPDIRECT3DTEXTURE9 pTexture);
	std::vector<LPDIRECT3DTEXTURE9>* GetTextures() { return &m_apTexture; }
	void SetAlpha(const float& fAlpha);
	float* GetAlpha() { return m_fAlpha; }
private:
	float* m_fAlpha;																// �s�����x
	LPD3DXMESH m_pMesh;													// ���b�V���ւ̃|�C���^
	ID3DXMesh* m_pShadowMesh;											// �e���b�V��
	LPD3DXBUFFER m_pBuffMat;												// �}�e���A���ւ̃|�C���^
	DWORD m_dwNumMat;														// �}�e���A���̐�
	std::vector<LPDIRECT3DTEXTURE9> m_apTexture;				// �e�N�X�`��
};

#endif // !_MESH_H_
