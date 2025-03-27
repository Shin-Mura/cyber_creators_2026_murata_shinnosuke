//=======================================================================================================
//
//�_�̏���[stick.cpp]
// Author MurataShinnosuke
//
//=======================================================================================================
#include "stick.h"
#include "manager.h"
#include "transform.h"
#include "rigidbody.h"
#include "collider.h"
#include "ball.h"
#include "sound.h"

//�ÓI�����o�ϐ�������������
const float Stick::MOVE = 10.0f;   //�ړ���

//=======================================================================================================
//����������
//=======================================================================================================
void Stick::Init()
{

}

//=======================================================================================================
//�X�V����
//=======================================================================================================
void Stick::Update()
{
	//�L�[�{�[�h���擾����
	Keyboard* pKeyborad = Manager::Get()->GetKeyboard();

	//A�L�[���m�F����
	if (pKeyborad->GetPress(DIK_A))
	{
		//���Ɉړ�����
		Transform* pTransform = this->GetComponent<Transform>();
		pTransform->AddPos({ -Stick::MOVE, 0.0f, 0.0f });
		if (pTransform->GetPos().x <= -SCREEN_WIDTH / 2)
		{
			//�ʒu���C������
			pTransform->SetPos({ -SCREEN_WIDTH / 2 , pTransform->GetPos().y, 0.0f });
		}
	}

	//D�L�[���m�F����
	if (pKeyborad->GetPress(DIK_D))
	{
		//���Ɉړ�����
		Transform* pTransform = this->GetComponent<Transform>();
		pTransform->AddPos({ Stick::MOVE, 0.0f, 0.0f });
		if (pTransform->GetPos().x >= SCREEN_WIDTH / 2)
		{
			//�ʒu���C������
			pTransform->SetPos({ SCREEN_WIDTH / 2 , pTransform->GetPos().y, 0.0f });
		}
	}
}