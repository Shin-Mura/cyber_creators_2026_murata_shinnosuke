//========================================================================================================
//
//�r���{�[�h�̏���[billboard.cpp]
// Author MurataShinnosuke
//
//========================================================================================================
#include "plane.h"

//========================================================================================================
//�`�揈��
//========================================================================================================
void Billboard::Draw()
{
	D3DXMATRIX mtxTrans;   //�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView, mtxViewInverse;   //�r���[�}�g���b�N�X�擾�p

	//�f�o�C�X���擾����
	LPDIRECT3DDEVICE9 pDevice = Manager::GetRenderer()->GetDevice();   //�f�o�C�X�ւ̃|�C���^

	//���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�A���t�@�e�X�g��L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//Z�o�b�t�@�̏������݂𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	if (this->m_isMultiply == true)
	{//���Z��������ꍇ
		//���u�����f�B���O�����Z�����ɐݒ�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	//�J�����̋t�s������߂�
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);
	D3DXMatrixInverse(&mtxViewInverse, NULL, &mtxView);

	//Y���r���{�[�h���m�F����
	if (m_isYAxis)
	{
		//Y����]���̑ł�����
		mtxViewInverse._21 = 0.0f;
		mtxViewInverse._22 = 1.0f;
		mtxViewInverse._23 = 0.0f;
	}

	//�ړ����̑ł�����
	mtxViewInverse._41 = 0.0f;
	mtxViewInverse._42 = 0.0f;
	mtxViewInverse._43 = 0.0f;

	//���[���h�}�g���b�N�X���擾����
	D3DXMATRIX mtxWorld = this->GetMtxWorld();

	//�t�s��𔽉f����
	D3DXMatrixMultiply(&mtxViewInverse, &mtxViewInverse, &mtxWorld);

	//���[���h�}�g���b�N�X��ݒ肷��
	pDevice->SetTransform(D3DTS_WORLD, &mtxViewInverse);

	//���_�o�b�t�@���e�[�^�X�g���[���ɐݒ肷��
	pDevice->SetStreamSource(0, this->GetVtxBuffer(), 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g��ݒ肷��
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`����ݒ肷��
	pDevice->SetTexture(0, this->GetTexture());   //�ݒ�

	//�`�悷��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//Z�o�b�t�@�̏������݂�L���ɂ���
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//�A���t�@�e�X�g�𖳌��ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//���C�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}