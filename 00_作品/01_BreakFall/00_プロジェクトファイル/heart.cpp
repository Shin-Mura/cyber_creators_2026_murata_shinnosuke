//==========================================================================================================
//
// �n�[�g�̏���[heart.cpp]
// Author ItouKotaro
//
//==========================================================================================================
#include "heart.h"
#include "manager.h"
#include "square.h"
#include "transform.h"
#include "sound.h"

// �萔
constexpr const char* HEART_TEX = "heart_00.png";
constexpr const char* HEART_EMPTY_TEX = "heart_01.png";
const float HeartManager::HEART_SIZE = 70.0f;
const float HeartManager::HEART_SPACE = HEART_SIZE + 10.0f;

//=======================================================================================================
//����������
//=======================================================================================================
void HeartUI::Init()
{
	//�e�N�X�`����ύX����
	this->GetComponent<Square>()->SetTexture(Manager::Get()->GetTexture()->Get(m_active ? HEART_TEX : HEART_EMPTY_TEX));
}

//=======================================================================================================
//�X�V����
//=======================================================================================================
void HeartUI::SetActive(const bool& active)
{
	if (active != m_active)
	{ //�ύX���ꂽ�Ƃ�
		//�e�N�X�`����ύX����
		this->GetComponent<Square>()->SetTexture(Manager::Get()->GetTexture()->Get(active ? HEART_TEX : HEART_EMPTY_TEX));
	
		//��Ԃ��X�V����
		m_active = active;
	}
}

//=======================================================================================================
//����������
//=======================================================================================================
void HeartManager::Init()
{
	//�n�[�gUI�𐶐�����
	for (int i = 0; i < MAX_HEART; i++)
	{
		//�n�[�g�e�X�g
		Object* pHeart = new Object("HeartUI");

		//�g�����X�t�H�[����ǉ�����
		Transform2D* pTransform2D = new Transform2D(pHeart);
		pTransform2D->SetPos(this->GetComponent<Transform2D>()->GetPos() + D3DXVECTOR2(HEART_SPACE * i, 0.0f));
		pTransform2D->SetSize({ HEART_SIZE, HEART_SIZE });
		pHeart->AddComponent(pTransform2D);

		//�l�p�`�����_�����O��ǉ�����
		Square* pSquare = new Square(pHeart);
		pHeart->AddComponent(pSquare);

		//�n�[�gUI��ǉ�����
		HeartUI* pHeartUI = new HeartUI(pHeart);
		pHeart->AddComponent(pHeartUI);

		//����������
		pHeart->Init();

		//�z��ɑ������
		m_heartUI[i] = pHeart;
	}
}

//=======================================================================================================
//�X�V����
//=======================================================================================================
void HeartManager::Update()
{
	//�̗͂𔽉f����
	for (int i = 0; i < MAX_HEART; i++)
	{
		m_heartUI[i]->GetComponent<HeartUI>()->SetActive(i < m_value);
	}
}

//=======================================================================================================
//�n�[�g��
//=======================================================================================================
void HeartManager::RecoveryHeart()
{
	if (m_value < MAX_HEART)
	{//�񕜂̗]�n������Ƃ�
		m_value++;
	}
}

//=======================================================================================================
//�n�[�g�_���[�W
//=======================================================================================================
void HeartManager::DamageHeart()
{
	if (m_value > 0)
	{//�_���[�W�̗]�n������Ƃ�
		m_value--;

		// �_���[�W����炷
		PlaySound(SOUND_LABEL_DAMAGE);

		// �̗͂������Ȃ����Ƃ�
		if (m_value <= 0)
		{
			m_isAlive = false;
		}
	}
}

//=======================================================================================================
//�n�[�g�_���[�W
//=======================================================================================================
void HeartManager::AllDamageHeart()
{
	while (m_value > 0)
	{
		DamageHeart();
	}
}
