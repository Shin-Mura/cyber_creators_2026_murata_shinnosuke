//========================================================================================================
//
//X�t�@�C������[Xfile.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _XFILE_H_
#define _XFILE_H_

#include "main.h"

//X�t�@�C��
class XFile
{
public:
	typedef struct
	{
		LPD3DXMESH pMesh;   //���b�V��
		LPD3DXBUFFER  pBuffMat;   //�}�e���A��
		DWORD dwMat;   //�}�e���A���̐�
	}Mesh;   //���b�V��

	typedef struct
	{
		std::string sPass;   //�p�X
		Mesh mesh;   //���b�V��
	}List;   //���X�g

	XFile();   //�R���X�g���N�^
	~XFile();   //�f�X�g���N�^

	void Init();   //����������
	void Uninit();   //�I������
	Mesh Get(std::string sFileName);

private:
	std::vector<XFile::List> m_vList;
};

#endif // !_XFILE_H_
