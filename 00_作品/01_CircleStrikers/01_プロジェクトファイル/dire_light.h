//======================================================================================================
//
//�f�B���N�V���i�����C�g�̏���[dire_light.h]
// Auhtor Murata Shinnosuke
//
//======================================================================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_ 

#include "component.h"

class DireLight : public Component   //(�e)�R���|�[�l���g
{
public:
	//�R���X�g���N�^
	DireLight(Object* pObject) : Component(pObject)
	{
		//�����o�ϐ�������������
		this->m_nId = DireLight::m_nTotal;
		ZeroMemory(&this->m_light, sizeof(D3DLIGHT9));

		//������ǉ�����
		DireLight::m_nTotal++;
	}

	//�f�X�g���N�^
	~DireLight()
	{
	}

	void Init() override;   //����������

	void SetColor(D3DXCOLOR color) { this->m_color = color; };   //�F�̐ݒ�

private:
	int m_nId;   //�ԍ�
	D3DLIGHT9 m_light;   //���C�g
	D3DXCOLOR m_color;   //�F

	static int m_nTotal;   //��
};

#endif // !_LIGHT_H_