//========================================================================================================
//
//2D�I�u�W�F�N�g�̏���[object2D.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _OBJECT2D_
#define _OBJECT2D_

#include "object.h"

//UI�I�u�W�F�N�g�N���X
class Object2D : public Object   //�i�e�j�I�u�W�F�N�g�N���X
{
public:
	Object2D(int nPriority = 4);   //�R���X�g���N�^
	virtual ~Object2D();   //�f�X�g���N�^

	virtual void Init();   //����������
	virtual void Uninit();   //�I������
	virtual void Update();   //�X�V����
	virtual void Draw();   //�`�揈��

	D3DXVECTOR2 GetPos() { return this->m_pos; };   //�ʒu�̎擾����
	D3DXVECTOR2 GetSize() { return this->m_size; };   //�T�C�Y�̎擾����
	D3DXCOLOR GetColor() { return this->m_color; };   //�F�̎擾����

protected:
	void SetPos(D3DXVECTOR2 pos) { this->m_pos = pos; };   //�ʒu�̐ݒ菈��
	void SetSize(D3DXVECTOR2 size) { this->m_size = size; };   //�T�C�Y�̐ݒ菈��
	void SetColor(D3DXCOLOR col) { this->m_color = col; };   //�F�̐ݒ菈��

private:
	D3DXVECTOR2 m_pos;   //�ʒu
	D3DXVECTOR2 m_size;   //�T�C�Y
	D3DXCOLOR m_color;   //�F
};

#endif // !_OBJECT2D_
