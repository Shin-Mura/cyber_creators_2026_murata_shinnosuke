//========================================================================================================
//
//�u���b�N����[block.cpp]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "block.h"
#include "manager.h"
#include "rendering.h"
#include "transform.h"
#include "heart.h"
#include "benlib.h"
#include "prefab.h"
#include "sound.h"

//�ÓI�����o�ϐ�������������
const float Block::MOVE = 0.1f;
const D3DXVECTOR3 Block::SIZE = { 100.0f, 50.0f, 0.0f };   //�T�C�Y

//========================================================================================================
//����������
//========================================================================================================
void Block::Init()
{
	//�����ŐF�����肷��
	int nRand = Benlib::CreateRand(4, 0);
	Rendering* pRendering = this->GetComponent<Rendering>();   //�����_�����O�̎擾
	if (nRand == Block::COLOR::IS_RED)
	{//�Ԃ̏ꍇ
		//�ԐF�ɂ���
		pRendering->SetColor({ 1.0f, 0.25f, 0.25f, 1.0f });
	}
	else if (nRand == Block::COLOR::IS_BLUE)
	{//�̏ꍇ
		//�ɂ���
		pRendering->SetColor({ 0.25f, 0.25f, 1.0f, 1.0f });
	}
	else if (nRand == Block::COLOR::IS_GREEN)
	{//�΂̏ꍇ
		//�΂ɂ���
		pRendering->SetColor({ 0.25f, 1.0f, 0.25f, 1.0f });
	}
	else if (nRand == Block::COLOR::IS_YELLOW)
	{//���̏ꍇ
		//���ɂ���
		pRendering->SetColor({ 1.0f, 1.0f, 0.25f, 1.0f });
	}

	//�����ő̗͂�ݒ肷��
	if (Benlib::CreateRand(2, 0) == 0)
	{
		//�q�b�g�|�C���g��1�ɐݒ肷��
		this->m_nHp = 1;
		pRendering->SetTexture(Manager::Get()->GetTexture()->Get("block_02.png"));   //�e�N�X�`��
	}
	else if (Benlib::CreateRand(2, 0) == 0)
	{
		//�q�b�g�|�C���g��1�ɐݒ肷��
		this->m_nHp = 2;
		pRendering->SetTexture(Manager::Get()->GetTexture()->Get("block_01.png"));   //�e�N�X�`��
	}
	else if (Benlib::CreateRand(2, 0) == 0)
	{
		//�q�b�g�|�C���g��2�ɐݒ肷��
		this->m_nHp = 3;
		pRendering->SetTexture(Manager::Get()->GetTexture()->Get("block_00.png"));   //�e�N�X�`��
	}
}

//========================================================================================================
//�X�V����
//========================================================================================================
void Block::Update()
{
	//�u���b�N���ړ�������
	this->GetComponent<Transform>()->AddPos({ 0.0f, -Block::MOVE, 0.0f });

	//�u���b�N�̈ʒu���m�F����
	if (this->GetComponent<Transform>()->GetPos().y <= -SCREEN_HEIGHT / 2)
	{//��ʊO�ɍs�����ꍇ
		//�n�[�g���擾����
		Object* pHeart = Object::Find("HeartUI");

		//�̗͂�0�ɂ���
		pHeart->GetComponent<HeartManager>()->AllDamageHeart();
	}
}

//=======================================================================================================
//�q�b�g����
//=======================================================================================================
void Block::Hit()
{
	//�q�b�g�|�C���g�����炷
	this->m_nHp--;
	Rendering* pRendering = this->GetComponent<Rendering>();   //�����_�����O�̎擾
	if (this->m_nHp <= 0)
	{//�q�b�g�|�C���g���O�ɂȂ�����
		//�����ŃA�C�e�����h���b�v����
		if (Benlib::CreateRand(10, 0) == 0)
		{
			//�����ŃA�C�e�������߂�
			int nRand = Benlib::CreateRand(9, 0);
			if (nRand >= 8)
			{
				//�H�A�C�e�����h���b�v����
				ClearBlockItemPrefab::Create(this->GetComponent<Transform>()->GetPos());
			}
			else if (nRand >= 6)
			{
				//�⏕�A�C�e�����h���b�v����
				AssistBarItemPrefab::Create(this->GetComponent<Transform>()->GetPos());
			}
			else if (nRand >= 3)
			{
				//�n�[�g�ǉ��A�C�e�����h���b�v����
				AddHeartItemPrefab::Create(this->GetComponent<Transform>()->GetPos());
			}
			else if (nRand >= 0)
			{
				//�{�[���ǉ��A�C�e�����h���b�v����
				AddBallItemPrefab::Create(this->GetComponent<Transform>()->GetPos());
			}
		}

		//���M��j������
		this->GetObj()->Death();
	}
	else if (this->m_nHp == 1)
	{
		//��ꂻ���̃e�N�X�`����ݒ�
		pRendering->SetTexture(Manager::Get()->GetTexture()->Get("block_02.png"));   //�e�N�X�`��
	}
	else if (this->m_nHp == 2)
	{
		//�Ђѓ���̃e�N�X�`����ݒ�
		pRendering->SetTexture(Manager::Get()->GetTexture()->Get("block_01.png"));   //�e�N�X�`��
	}

	//����炷
	PlaySound(SOUND_LABEL_BLOCK_BREAK);
}