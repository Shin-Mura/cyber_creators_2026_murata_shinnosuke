//=============================================================
//
// �f�[�^�Ǘ� [data_manager.h]
// Author: Ito Kotaro
// 
// �e�N�X�`���⃁�b�V���Ȃǂ̃f�[�^�Q�ƌ��Ƃ��ĊǗ����܂�
//
//=============================================================
#ifndef _DATA_MANAGER_H_
#define _DATA_MANAGER_H_

#include <fstream>

// �f�[�^���N���X
class CDataBase
{
public:
	typedef enum
	{
		TEXTURE = 0,		// �e�N�X�`��
		MESH,					// ���b�V��
		AUDIO,					// �I�[�f�B�I
	}FORMAT;

	CDataBase(const FORMAT& format);
	virtual void Clear() = 0;							// �i�[�f�[�^�폜

	FORMAT GetFormat();
	void SetPath(const std::string& sPath);	// �p�X�̐ݒ�
	std::string GetPath();								// �p�X�̎擾
private:
	std::string m_sPath;		// �p�X
	FORMAT m_format;		// �t�H�[�}�b�g
};

// �e�N�X�`���f�[�^�N���X
class CDataTexture : public CDataBase
{
public:
	CDataTexture();
	void Clear() override;
	HRESULT Load(const std::string& sPath);
	LPDIRECT3DTEXTURE9 GetTexture() { return m_texture; }			// �e�N�X�`���̎擾
	
private:
	LPDIRECT3DTEXTURE9 m_texture;												// �e�N�X�`���f�[�^
};

// ���b�V���f�[�^�N���X
class CDataMesh : public CDataBase
{
public:
	CDataMesh();
	void Clear() override;
	HRESULT Load(const std::string& sPath);
	LPD3DXMESH GetMesh() { return m_pMesh; }								// ���b�V���̎擾
	LPD3DXMESH GetShadowMesh() { return m_pShadowMesh; }		// �e�p���b�V���̎擾
	LPD3DXBUFFER GetBuffMat() { return m_pBuffMat; }					// �}�e���A���̎擾
	DWORD GetNumMat() { return m_dwNumMat; }							// �}�e���A�����̎擾
private:
	LPD3DXMESH m_pMesh;															// ���b�V���f�[�^
	LPD3DXMESH m_pShadowMesh;													// �e�p���b�V���f�[�^
	LPD3DXBUFFER m_pBuffMat;														// �}�e���A���f�[�^
	DWORD m_dwNumMat;																// �}�e���A����
};

// �I�[�f�B�I�f�[�^�N���X
class CDataAudio : public CDataBase
{
public:
	CDataAudio();
	void Clear() override;
	HRESULT Load(const std::string& sPath);
	ALuint GetBuffer() { return m_buffer; }
private:
	int Read(void* out, size_t size);
	ALuint m_buffer;	// �o�b�t�@ID

	// �T�E���h�f�[�^
	unsigned short m_ChannelQuantity;
	unsigned short m_BlockSize;
	unsigned short m_BitPerSample;
	unsigned int m_Bps;
	unsigned int m_SamplingRate;
	unsigned int m_Length;
	std::ifstream m_fp;
	std::ifstream::pos_type m_DataHead;
	size_t m_DataSize;
	size_t m_LoadedSize;
};


// �f�[�^�Ǘ��N���X
class CDataManager
{
public:
	CDataManager();
	~CDataManager();
	void Init();
	void Uninit();

	static CDataManager* GetInstance()
	{
		static CDataManager dataManager;
		return &dataManager;
	}

	CDataTexture* RefTexture(const std::string& sPath);
	CDataMesh* RefMesh(const std::string& sPath);
	CDataAudio* RefAudio(const std::string& sPath);
private:
	std::vector<CDataBase*> m_apData;		// �S�f�[�^�i�[
};

#endif // !_DATA_MANAGER_H_
