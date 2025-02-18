//======================================================================================================
//
//�f�B���N�V���i�����C�g�̏���[dire_light.cpp]
// Auhtor Murata Shinnosuke
//
//======================================================================================================
#include "dire_light.h"
#include "manager.h"
#include "object.h"
#include "transform.h"

//�ÓI�����o�ϐ�������������
int DireLight::m_nTotal = 0;

//==============================================================================
// ���C�g�̏���������
//==============================================================================
void DireLight::Init()
{
	//�f�o�C�X���擾����
	LPDIRECT3DDEVICE9 pDevice = Manager::Get()->GetRenderer()->GetDevice();   //�f�o�C�X�ւ̃|�C���^

	//����ݒ肷��
	this->m_light.Type = D3DLIGHT_DIRECTIONAL;   //���
	this->m_light.Diffuse = this->m_color;   //�g�U��

	//������ݒ肷��
	D3DXVECTOR3 vecDir = this->GetObj()->GetComponent<Transform>()->GetRot();   //�����̎擾
	D3DXVec3Normalize(&vecDir, &vecDir);	//�x�N�g�����K��
	this->m_light.Direction = vecDir;

	//�ݒ肷��
	pDevice->SetLight(this->m_nId, &this->m_light);

	//�L���ɂ���
	pDevice->LightEnable(this->m_nId, TRUE);
}