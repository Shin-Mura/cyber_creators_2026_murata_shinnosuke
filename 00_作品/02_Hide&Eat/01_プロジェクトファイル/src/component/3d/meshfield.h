//=============================================================
//
// ���b�V���t�B�[���h [meshfield.h]
// Author: Ito Kotaro
// 
//=============================================================
#ifndef _MESH_FIELD_H_
#define _MESH_FIELD_H_

#include "component.h"

// ���b�V���t�B�[���h
class CMeshField : public Component
{
public:
	void Init() override;
	void Uninit() override;
	void Draw() override;

	void BindTexture(LPDIRECT3DTEXTURE9 texture) { m_pTexture = texture; }
	void SetTexture(const std::string& sPath);
	void SetLoopTexture(const int& num);

	// ���b�V���t�B�[���h��p�ӂ���
	void Create(const int& x, const int& y, const float& spaceSize);

	// �w��̈ʒu�̍�����ύX����
	void SetHeight(const int& x, const int& y, const float& height);

	// �w��̈ʒu�̐F��ύX����
	void SetColor(const int& x, const int& y, const D3DXCOLOR& color);

	// �@����K�؂Ȍ����ɕύX����
	void ResetNormals();

	// �f�[�^���擾���܂�
	std::vector<D3DXVECTOR3>& GetVertices() { return m_vertices; }
	std::vector<int>& GetIndices() { return m_indices; }
	int GetNumFaces() { return (m_sizeX * 2) * m_sizeY; }

	// �@����\������
	void ShowNormals(GameObject* pLineObj);

private:
	int m_sizeX;				// X�̖ʐ�
	int m_sizeY;				// Y�̖ʐ�
	int m_loopTex;			// �e�N�X�`���̃��[�v��
	float m_sizeSpace;		// �Ԋu

	std::vector<D3DXVECTOR3> m_vertices;	// ���_�f�[�^
	std::vector<int> m_indices;						// �C���f�b�N�X�f�[�^

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	// �C���f�b�N�X�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`��
};

#endif // !_MESH_FIELD_H_
