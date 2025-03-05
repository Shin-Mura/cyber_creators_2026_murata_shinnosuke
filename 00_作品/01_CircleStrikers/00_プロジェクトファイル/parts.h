//========================================================================================================
//
//�p�[�c�̏���[parts.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _PARTS_H_
#define _PARTS_H_

#include "main.h"
#include "Xfile.h"

//�p�[�c
class Parts
{
public:
	Parts(int nPriority = 3);   //�R���X�g���N�^
	~Parts();   //�f�X�g���N�^

	void Init();   //����������
	void Uninit();   //�I������
	void Update();   //�X�V����
	void Draw(D3DXMATRIX mtxWorldParent);   //�`�揈��

	void SetXFile(XFile::Mesh mesh) { this->m_mesh = mesh; };   //�p�[�c�̌��т�����
	void SetTexture(LPDIRECT3DTEXTURE9 pTexture) { this->m_pTexture = pTexture; };   //�e�N�X�`���̌��т�����
	void SetId(int nId) { this->m_nId = nId; };
	void SetIdParent(int nId) { this->m_nIdParent = nId; };   //�e�̐ݒ菈��
	void SetPos(D3DXVECTOR3 pos) { this->m_pos = pos; };
	void SetRot(D3DXVECTOR3 rot) { this->m_rot = rot; };

	int GetId() { return this->m_nId; };   //�ԍ��̎擾
	int GetIdParent() { return this->m_nIdParent; };   //�e�̔ԍ��̎擾
	D3DXVECTOR3 GetPos() { return this->m_pos; };
	D3DXVECTOR3 GetRot() { return this->m_rot; };
	D3DXMATRIX GetMtxWorld() { return this->m_mtxWorld; };   //���[���h�}�g���b�N�X�̎擾����

private:
	int m_nId;   //�ԍ�
	XFile::Mesh m_mesh;   //���b�V��
	LPDIRECT3DTEXTURE9 m_pTexture;   //�e�N�X�`��
	D3DXMATRIX m_mtxWorld;   //���[���h�}�g���b�N�X
	int m_nIdParent;   //�e�̔ԍ�
	D3DXVECTOR3 m_pos;   //�ʒu
	D3DXVECTOR3 m_rot;   //����
};

#endif // !_PARTS_H_
