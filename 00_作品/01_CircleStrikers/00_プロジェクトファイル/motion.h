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
	static const int MAX_KEY = 32;   //�L�[�̍ő吔

	struct Key   //�L�[�̍\����
	{
		int nFrame;   //�t���[��
		D3DXVECTOR3 pos[32];   //�ʒu
		D3DXVECTOR3 rot[32];   //����
	};

	Motion();   //�R���X�g���N�^
	~Motion();   //�f�X�g���N�^

	void Init();   //����������
	void Uninit();   //�I������
	void Update();   //�X�V����
	void Reset();   //���Z�b�g����

	void SetKey(Motion::Key key);   //�L�[�̐ݒ菈��

	void Loop() { this->m_isLoop = true; };   //���[�v�t���O�̊m������

	D3DXVECTOR3 GetPos(int nId) { return this->m_pos[nId]; };   //�ʒu�̎擾����
	D3DXVECTOR3 GetRot(int nId) { return this->m_rot[nId]; };   //�ʒu�̎擾����

private:
	bool m_isLoop;   //���[�v�t���O
	int m_nFrame;   //���݃t���[��
	int m_nFrameBlend;   //�u�����h�t���[��
	int m_nKey;   //���݃L�[
	Motion::Key m_key[Motion::MAX_KEY];   //�L�[
	int m_nNumKey;   //�L�[�̐�

	D3DXVECTOR3 m_pos[32];
	D3DXVECTOR3 m_rot[32];
};

#endif // !_MOTION_H_