//=============================================================
//
// �I�[�f�B�I�Ǘ� [audio_manager.cpp]
// Author: Ito Kotaro
//
//=============================================================
#include "audio_manager.h"
#include "manager.h"
#include <iostream>
#include <fstream>

class WaveFile {
public:
	~WaveFile() {
		m_fp.close();
	}
	bool Open(const char* path);
	int Read(void* out, size_t size);
	bool IsEnd()const { return (0 == m_LoadedSize) || (m_DataSize == m_LoadedSize); }
	ALuint CreateBuffer(ALuint buffer);

private:
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
bool WaveFile::Open(const char* path) {
	m_fp.open(path, std::ios::binary);

	// "RIFF" �̓ǂݍ���
	unsigned int riff;
	m_fp.read((char*)&riff, 4);

	// �f�[�^�T�C�Y���擾
	m_fp.read((char*)&m_DataSize, 4);

	// WAVE�̓ǂݍ���
	unsigned int wave;
	m_fp.read((char*)&wave, 4);

	// PCM ���ƃf�[�^�̐擪�̎擾
	for (int i = 0; i < 2; ++i) {
		unsigned int res, size;
		m_fp.read((char*)&res, 4);
		m_fp.read((char*)&size, 4);
		if (0x20746d66u == res) 
		{
			// PCM ���̎擾
			unsigned short res16;
			m_fp.read((char*)&res16, 2);
			if (1 != res16) {// ��Ή��t�H�[�}�b�g
				return false;
			}

			// ���m����(1), �X�e���I(2)
			m_fp.read((char*)&m_ChannelQuantity, 2);
			if (2 < m_ChannelQuantity) {
				return false;
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
	return true;
}

int WaveFile::Read(void* out, size_t size) {
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

ALuint WaveFile::CreateBuffer(ALuint buffer) {
	// �V�K�Ƀo�b�t�@���쐬
	if (!buffer)
	{
		alGenBuffers(1, &buffer);
	}
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
	alBufferData(buffer, format, &wavData[0], read, m_SamplingRate);
	return buffer;
}


//=============================================================
// [CAudioManager] ������
//=============================================================
HRESULT CAudioManager::Init()
{
	// �f�o�C�X�̍쐬
	m_device = alcOpenDevice(nullptr);
	if (m_device)
	{
		// �R���e�L�X�g�̍쐬
		m_context = alcCreateContext(m_device, nullptr);
		alcMakeContextCurrent(m_context);
	}

	alGetError();

	return S_OK;
}

//=============================================================
// [CAudioManager] �I��
//=============================================================
void CAudioManager::Uninit()
{
	// �R���e�L�X�g��j������
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(m_context);

	// �f�o�C�X��j������
	alcCloseDevice(m_device);
}

//=============================================================
// [CAudioManager] �X�V
//=============================================================
void CAudioManager::Update()
{

}