//========================================================================================================
//
//�X�e���V���̏���[stencil.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "stencil.h"
#include "manager.h"
#include "rendering.h"
#include "object.h"

//========================================================================================================
//�`��
//========================================================================================================
void Stencil::Draw()
{
	//�f�o�C�X���擾����
	LPDIRECT3DDEVICE9 pDevice = Manager::Get()->GetRenderer()->GetDevice();

	//�X�e���V���o�b�t�@��L���ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_STENCILREF, this->m_nRef);   //��r����Q�ƒl�ݒ�

	//�X�e���V���o�b�t�@�̒l�ɑ΂��Ẵ}�X�N�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);

	//�X�e���V���e�X�g�̔�r���@�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILFUNC, this->m_compare);

	//�X�e���V���e�X�g�̌��ʂɑ΂��Ă̔��f�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILPASS, this->m_pass);
	pDevice->SetRenderState(D3DRS_STENCILFAIL, this->m_pass);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, Stencil::PASS::IS_KEEP);

	//�e�N���X�̏������s��
	this->GetObj()->GetComponent<Rendering>()->Draw();

	//�X�e���V���o�b�t�@�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}