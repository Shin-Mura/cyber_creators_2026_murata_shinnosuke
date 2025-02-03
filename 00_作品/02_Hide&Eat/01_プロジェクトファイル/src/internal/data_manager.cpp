//=============================================================
//
// �f�[�^�Ǘ� [data_manager.h]
// Author: Ito Kotaro
//
//=============================================================
#include "data_manager.h"
#include "manager.h"
using namespace std;

//=============================================================
// [CDataManager] �R���X�g���N�^
//=============================================================
CDataManager::CDataManager()
{
	
}

//=============================================================
// [CDataManager] �f�X�g���N�^
//=============================================================
CDataManager::~CDataManager()
{

}

//=============================================================
// [CDataManager] ������
//=============================================================
void CDataManager::Init()
{

}

//=============================================================
// [CDataManager] �I��
//=============================================================
void CDataManager::Uninit()
{
	// ���ׂẴf�[�^��j������
	for (unsigned int i = 0; i < m_apData.size(); i++)
	{
		if (m_apData[i] != nullptr)
		{
			// �i�[�f�[�^��j������
			m_apData[i]->Clear();

			// �f�[�^��j������
			delete m_apData[i];
			m_apData[i] = nullptr;
		}
	}

	// �f�[�^���X�g����ɂ���
	m_apData.clear();
}

//=============================================================
// [CDataManager] �e�N�X�`���̎Q�Ɓi���݂��Ȃ��ꍇ�͍쐬�j
//=============================================================
CDataTexture* CDataManager::RefTexture(const std::string& sPath)
{
	// �f�[�^�����݂��邩����������
	for (unsigned int i = 0; i < m_apData.size(); i++)
	{
		if (m_apData[i]->GetPath() == sPath &&
			m_apData[i]->GetFormat() == CDataBase::FORMAT::TEXTURE)
		{ // ���������Ƃ�
			CDataTexture* pTextureData = (CDataTexture*)m_apData[i];	// �e�N�X�`���N���X�Ƀ_�E���L���X�g
			return pTextureData;
		}
	}

	// �f�[�^�����݂��Ȃ��ꍇ ---------------------------------------------------------------------------------------------

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	// �f�[�^�N���X�𐶐�
	CDataTexture* pNewData = new CDataTexture();
	pNewData->SetPath(sPath);

	// ���[�h
	if (FAILED(pNewData->Load(pNewData->GetPath())))
	{ // ���s
		delete pNewData;
		pNewData = nullptr;
		return nullptr;
	}

	m_apData.push_back(pNewData);		// �f�[�^��o�^����

	return pNewData;
}

//=============================================================
// [CDataManager] ���b�V���̎Q�Ɓi���݂��Ȃ��ꍇ�͍쐬�j
//=============================================================
CDataMesh* CDataManager::RefMesh(const std::string& sPath)
{
	// �f�[�^�����݂��邩����������
	for (unsigned int i = 0; i < m_apData.size(); i++)
	{
		if (m_apData[i]->GetPath() == sPath &&
			m_apData[i]->GetFormat() == CDataBase::FORMAT::MESH)
		{ // ���������Ƃ�
			CDataMesh* pMeshData = (CDataMesh*)m_apData[i];		// ���b�V���N���X�Ƀ_�E���L���X�g
			return pMeshData;
		}
	}

	// �f�[�^�����݂��Ȃ��ꍇ ---------------------------------------------------------------------------------------------

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	// �f�[�^�N���X�𐶐�
	CDataMesh* pNewData = new CDataMesh();
	pNewData->SetPath(sPath);

	// ���[�h
	if (FAILED(pNewData->Load(pNewData->GetPath())))
	{ // ���s
		delete pNewData;
		pNewData = nullptr;
		return nullptr;
	}

	m_apData.push_back(pNewData);		// �f�[�^��o�^����

	return pNewData;
}

//=============================================================
// [CDataManager] �I�[�f�B�I�̎Q�Ɓi���݂��Ȃ��ꍇ�͍쐬�j
//=============================================================
CDataAudio* CDataManager::RefAudio(const std::string& sPath)
{
	// �f�[�^�����݂��邩����������
	for (unsigned int i = 0; i < m_apData.size(); i++)
	{
		if (m_apData[i]->GetPath() == sPath &&
			m_apData[i]->GetFormat() == CDataBase::FORMAT::AUDIO)
		{ // ���������Ƃ�
			CDataAudio* pAudioData = (CDataAudio*)m_apData[i];		// �I�[�f�B�I�N���X�Ƀ_�E���L���X�g
			return pAudioData;
		}
	}

	// �f�[�^�����݂��Ȃ��ꍇ ---------------------------------------------------------------------------------------------

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	// �f�[�^�N���X�𐶐�
	CDataAudio* pNewData = new CDataAudio();
	pNewData->SetPath(sPath);

	// ���[�h
	if (FAILED(pNewData->Load(pNewData->GetPath())))
	{ // ���s
		delete pNewData;
		pNewData = nullptr;
		return nullptr;
	}

	m_apData.push_back(pNewData);		// �f�[�^��o�^����

	return pNewData;
}


//=============================================================
// [CDataBase] �R���X�g���N�^
//=============================================================
CDataBase::CDataBase(const FORMAT& format) : m_format(format)
{
}

//=============================================================
// [CDataBase] �t�H�[�}�b�g�̎擾
//=============================================================
CDataBase::FORMAT CDataBase::GetFormat()
{
	return m_format;	// �t�H�[�}�b�g��Ԃ�
}

//=============================================================
// [CDataBase] �p�X�̐ݒ�
//=============================================================
void CDataBase::SetPath(const std::string& sPath)
{
	m_sPath = sPath;
}

//=============================================================
// [CDataBase] �p�X�̎擾
//=============================================================
string CDataBase::GetPath()
{
	return m_sPath;
}





//=============================================================
// [CDataTexture] �R���X�g���N�^
//=============================================================
CDataTexture::CDataTexture() : CDataBase(TEXTURE)
{
	// �ϐ��̏�����
	m_texture = nullptr;
}

//=============================================================
// [CDataTexture] �N���A
//=============================================================
void CDataTexture::Clear()
{
	// �e�N�X�`���̔j��
	if (m_texture != nullptr)
	{
		m_texture->Release();
		m_texture = nullptr;
	}
}

//=============================================================
// [CDataTexture] ���[�h
//=============================================================
HRESULT CDataTexture::Load(const std::string& sPath)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	// �e�N�X�`���̍쐬
	if (FAILED(D3DXCreateTextureFromFile(pDevice, sPath.c_str(), &m_texture)))
	{ // ���s
		return E_FAIL;
	}

	// ����
	return S_OK;
}




//=============================================================
// [CDataMesh] �R���X�g���N�^
//=============================================================
CDataMesh::CDataMesh() : CDataBase(MESH)
{
	// �ϐ��̏�����
	m_pMesh = nullptr;
	m_pShadowMesh = nullptr;
	m_pBuffMat = nullptr;
	m_dwNumMat = 0;
}

//=============================================================
// [CDataMesh] �N���A
//=============================================================
void CDataMesh::Clear()
{
	// ���b�V���̔j��
	if (m_pMesh != nullptr)
	{
		m_pMesh->Release();
		m_pMesh = nullptr;
	}

	// �e�p���b�V���̔j��
	if (m_pShadowMesh != nullptr)
	{
		m_pShadowMesh->Release();
		m_pShadowMesh = nullptr;
	}

	// �}�e���A���̔j��
	if (m_pBuffMat != nullptr)
	{
		m_pBuffMat->Release();
		m_pBuffMat = nullptr;
	}
}

//=============================================================
// [CDataMesh] ���[�h
//=============================================================
HRESULT CDataMesh::Load(const std::string& sPath)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	// ���b�V���̐���
	if (FAILED(D3DXLoadMeshFromX(
		sPath.c_str(),
		D3DXMESH_SYSTEMMEM,
		pDevice,
		nullptr,
		&m_pBuffMat,
		nullptr,
		&m_dwNumMat,
		&m_pMesh
	)))
	{ // ���s
		return E_FAIL;
	}

	// �e�p���b�V���̐���
	if (CShadow::USE_SHADOW)
	{
		if (FAILED(CShadow::GenerateShadowMesh(pDevice, m_pMesh, &m_pShadowMesh)))
		{ // ���s
			return E_FAIL;
		}
	}

	// ����
	return S_OK;
}



//=============================================================
// [CDataAudio] �R���X�g���N�^
//=============================================================
CDataAudio::CDataAudio() : CDataBase(AUDIO)
{
	// �o�b�t�@�𐶐�
	alGenBuffers(1, &m_buffer);
}

//=============================================================
// [CDataAudio] �N���A
//=============================================================
void CDataAudio::Clear()
{
	// �o�b�t�@�̔j��
	//alDeleteBuffers(1, &m_buffer);
}

//=============================================================
// [CDataAudio] WAVE�t�@�C����ǂݍ���
//=============================================================
HRESULT CDataAudio::Load(const std::string& sPath)
{
	m_fp.open(sPath.c_str(), std::ios::binary);

	// "RIFF" �̓ǂݍ���
	unsigned int riff;
	m_fp.read((char*)&riff, 4);

	// �f�[�^�T�C�Y���擾
	m_fp.read((char*)&m_DataSize, 4);

	// WAVE�̓ǂݍ���
	unsigned int wave;
	m_fp.read((char*)&wave, 4);

	// PCM ���ƃf�[�^�̐擪�̎擾
	for (int i = 0; i < 2; ++i)
	{
		unsigned int res, size;
		m_fp.read((char*)&res, 4);
		m_fp.read((char*)&size, 4);
		if (0x20746d66u == res)
		{
			// PCM ���̎擾
			unsigned short res16;
			m_fp.read((char*)&res16, 2);
			if (1 != res16)
			{// ��Ή��t�H�[�}�b�g
				return E_FAIL;
			}

			// ���m����(1), �X�e���I(2)
			m_fp.read((char*)&m_ChannelQuantity, 2);
			if (2 < m_ChannelQuantity)
			{
				return E_FAIL;
			}

			// �T���v�����O���[�g
			m_fp.read((char*)&m_SamplingRate, 4);

			// 1�b������̃o�C�g��(byte/sec)
			m_fp.read((char*)&m_Bps, 4);

			// �u���b�N�T�C�Y(byte/sample)
			m_fp.read((char*)&m_BlockSize, 2);

			// �T���v��������̃r�b�g��(bit/sample)
			m_fp.read((char*)&m_BitPerSample, 2);
		}
		else if (0x61746164u == res)
		{
			// �f�[�^�̊J�n�ʒu��ۑ�
			m_DataHead = m_fp.tellg();
			m_DataSize = size;

			// �f�[�^��ǂݔ�΂�
			m_fp.seekg(size, std::ios::cur);
		}
	}

	// �f�[�^�̊J�n�ʒu�܂ŃV�[�N
	m_fp.seekg(m_DataHead);
	m_LoadedSize = 0;
	m_DataSize -= m_DataSize % 100;
	m_Length = static_cast<unsigned int>(m_DataSize) / m_Bps;

	std::vector<char> wavData(m_DataSize);
	int read = Read(&wavData[0], m_DataSize);
	ALenum format;
	if (1 == m_ChannelQuantity)
	{ // ���m����
		format = (8 == m_BitPerSample) ? AL_FORMAT_MONO8 : AL_FORMAT_MONO16;
	}
	else
	{ // �X�e���I
		format = (8 == m_BitPerSample) ? AL_FORMAT_STEREO8 : AL_FORMAT_STEREO16;
	}

	// OpenAL �̃o�b�t�@�Ƀf�[�^�̏�������
	alBufferData(m_buffer, format, &wavData[0], read, m_SamplingRate);

	wavData.clear();
	m_fp.close();

	return true;
}

//=============================================================
// [CDataAudio] �ǂݍ���
//=============================================================
int CDataAudio::Read(void* out, size_t size)
{
	if (!out)
	{
		return 0;
	}

	// �f�[�^�T�C�Y�̒���
	if (m_LoadedSize + size > m_DataSize) {
		size = m_DataSize - m_LoadedSize;
	}

	// �f�[�^��ǂݏo����������
	m_fp.read((char*)out, size);
	m_LoadedSize += size;
	if (m_LoadedSize == m_DataSize) {
		m_LoadedSize = 0;
		m_fp.seekg(m_DataHead);
	}
	return static_cast<int>(size);
}