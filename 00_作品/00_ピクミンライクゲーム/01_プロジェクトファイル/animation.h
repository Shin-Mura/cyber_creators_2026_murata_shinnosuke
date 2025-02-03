//========================================================================================================
//
//�A�j���[�V�����̏���[animation.h]
// Author MurataShinnosuke
//
//========================================================================================================
#include "main.h"

//�A�j���[�V�����N���X
class Animation
{
public:
	static const int MAX_NUM = 8;   //�ő吔

	Animation();   //�R���X�g���N�^
	~Animation();   //�f�X�g���N�^

	void Init();   //����������
	void Uninit();   //�I������
	void Update();   //�X�V����
	void Reset();
	int GetId() { return this->m_nId; };   //�ԍ��̎擾����
	int GetFrame() { return this->m_nFrame; };   //�t���[���̎擾����
	int GetPattern() { return this->m_nPattern; };   //�p�^�[���̎擾����
	LPDIRECT3DTEXTURE9 GetTexture() { return this->m_pTexture; };

	static Animation* Create(int nPattern, int nTime, LPDIRECT3DTEXTURE9 pTexture);   //��������
	static void UpdateAll();   //�S�X�V����
	static Animation* Get(int nId) { return Animation::m_apAnimation[nId]; };   //�擾����

private:
	int m_nId;   //�ԍ�
	int m_nFrame;   //�t���[��
	int m_nPattern;   //�p�^�[��
	int m_nTime;   //����
	int m_nCnt;   //�J�E���^�[
	LPDIRECT3DTEXTURE9 m_pTexture;   //�e�N�X�`��

	static Animation* m_apAnimation[Animation::MAX_NUM];   //�A�j���[�V�����̏��
};