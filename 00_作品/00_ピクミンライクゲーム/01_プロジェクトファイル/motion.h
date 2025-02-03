//========================================================================================================
//
//���[�V�����̏���[motion.h]
// Author MurataShinnosuke
//
//========================================================================================================
#ifndef _MOTION_H_
#define _MOTION_H_

#include "main.h"

//���[�V����
class Motion
{
public:
	static const int FRAME_BLEND;

	//���[�V�����̏�Ԃ̗�
	enum STATE
	{
		IS_START = 0,   //�Đ���
		IS_STOP,   //��~��
		IS_END,   //�I��
	};

	//�L�[�̍\����
	struct Key
	{
		int nFrame;   //�t���[��
		std::vector<D3DXVECTOR3> vPos;
		std::vector<D3DXVECTOR3> vRot;
	};

	//�R���X�g���N�^
	Motion()
	{
		//�����o�ϐ�������������
		this->sName = "null";   //���O
		this->m_isLoop = false;   //���[�v�t���O
		this->m_nFrame = 0;   //���݃t���[��
		this->m_nFrameBlend = 0;   //�u�����h�t���[��
		this->m_nKey = 0;   //���݃L�[
		this->m_vKey.clear();   //�L�[�̃R���e�i
		this->m_vRot.clear();   //����
		this->m_isEnd = false;   //�I���t���O
	}

	//�f�X�g���N�^
	~Motion()
	{

	}

	void Init();   //����������
	void Uninit();   //�I������
	void Update();   //�X�V����
	void AddKey(Motion::Key key) { this->m_vKey.push_back(key); };
	void Loop() { this->m_isLoop = true; };   //���[�v�t���O

	//���Z�b�g����
	void Reset()
	{
		//�Đ��ɕK�v�ȏ������Z�b�g����
		this->m_nFrame = 0;
		this->m_nFrameBlend = 0;
		this->m_nKey = 0;
		this->m_isEnd = false;
	}

	//�p�[�c�̐��̐ݒ�
	void SetNumParts(int nNum)
	{
		//�p�[�c�̐����J��Ԃ�
		for (int i = 0; i < nNum; i++)
		{
			//�p�[�c�̕��������R���e�i�ɒǉ�����
			D3DXVECTOR3 rot = { 0.0f, 0.0f, 0.0f };
			this->m_vRot.push_back(rot);
		}
	}

	D3DXVECTOR3 GetRot(int nId) { return this->m_vRot[nId]; };   //�����̎擾
	bool GetEnd() { return this->m_isEnd; };   //�I���t���O�̎擾

private:
	std::string sName;   //���O
	bool m_isLoop;   //���[�v�t���O
	int m_nFrame;   //���݃t���[��
	int m_nFrameBlend;   //�u�����h�t���[��s
	int m_nKey;   //���݃L�[
	std::vector<Motion::Key> m_vKey;   //�L�[
	std::vector<D3DXVECTOR3> m_vRot;   //����
	bool m_isEnd;   //�I���t���O
};

#endif // !_MOTION_H_