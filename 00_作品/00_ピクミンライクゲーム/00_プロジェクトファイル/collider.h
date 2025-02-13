//========================================================================================================
//
//�Փ˔͈͂̏���[collider.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _COLLIDER_H_
#define _COLLIDER_H_

#include "component.h"
#include "physics.h"
#include "line.h"
#include "object.h"
#include "transform.h"

//�Փ˔͈̓N���X
class Collider : public Component
{
public:
	static const int CALC_PHYSICS = 5;   //�����蔻��̉��Z��

	typedef enum
	{
		IS_BOX = 0,   //�{�b�N�X
		IS_SPHERE,   //����
	}TYPE;   //���

	//�R���X�g���N�^
	Collider(Object* pObject) : Component(pObject)
	{
		//�����o�ϐ�������������
		this->m_type = Collider::TYPE::IS_BOX;
		this->m_isTrigger = false;
		this->m_offset = { 0.0f, 0.0f, 0.0f };
		this->m_nMass = 3;   //����
	}

	//�f�X�g���N�^
	virtual ~Collider()
	{
	}

	virtual void Init() override = 0;   //����������
	virtual void Uninit() override = 0;   //�I������
	virtual void Update() override = 0;   //�X�V����
	virtual void Draw() override = 0;   //�`�揈��
	virtual void Collision(Collider* pColliderTarget, Physics::CONTACT contact) = 0;   //�Փˎ��̏���
	void Trigger() { this->m_isTrigger = true; };

	void SetCenter(D3DXVECTOR3 center) { this->GetObj()->GetComponent<Transform>()->SetPos(center - this->m_offset); };   //�����̐ݒ菈��
	void SetMass(int nMass) { this->m_nMass = nMass; };   //���ʂ̐ݒ菈��
	void SetOffset(D3DXVECTOR3 offset) { this->m_offset = offset; };

	Collider::TYPE GetType() { return this->m_type; };   //��ނ̎擾����
	bool GetTrigger() { return this->m_isTrigger; };   //�g���K�[�t���O�̎擾����
	int GetMass() { return this->m_nMass; };
	D3DXVECTOR3 GetCenter() { return this->GetObj()->GetComponent<Transform>()->GetPos() + this->m_offset; };   //�����̎擾����
	D3DXVECTOR3 GetCenterOld() { return this->GetObj()->GetComponent<Transform>()->GetPosOld() + this->m_offset; };

protected:
	void SetType(Collider::TYPE type) { this->m_type = type; };

private:
	Collider::TYPE m_type;
	bool m_isTrigger;   //�g���K�[�t���O
	D3DXVECTOR3 m_offset;   //���Βl
	int m_nMass;   //����
};

//�{�b�N�X�Փ˔͈�
class BoxCollider : public Collider   //(�e)�Փ˔͈̓N���X
{
public:
	static const int NUM_LINE = 12;   //�ӂ̐�

	typedef struct
	{
		D3DXVECTOR3 posMax;   //�ő�͈�
		D3DXVECTOR3 posMaxOld;   //�O��̍ő�͈�
		D3DXVECTOR3 posMin;   //�ŏ��͈�
		D3DXVECTOR3 posMinOld;   //�O��̍ŏ��͈�
	}Range;   //�͈�

	//�R���X�g���N�^
	BoxCollider(Object* pObject) : Collider(pObject)
	{
		//�����o�ϐ�������������
		this->m_size = {0.0f, 0.0f, 0.0f};   //�T�C�Y
		this->m_range.posMax = { 0.0f, 0.0f, 0.0f };   //�ő�͈�
		this->m_range.posMaxOld = m_range.posMax;   //�O��̍ő�͈�
		this->m_range.posMin = { 0.0f, 0.0f, 0.0f };   //�ŏ��͈�
		this->m_range.posMinOld = m_range.posMin;   //�O��̍ŏ��͈�
		this->SetType(Collider::TYPE::IS_BOX);

		for (int i = 0; i < BoxCollider::NUM_LINE; i++)
		{
			//��������������
			this->m_pLine[i] = nullptr;
		}
	}

	//�f�X�g���N�^
	~BoxCollider() override
	{
	}

	void Init() override;   //����������
	void Uninit() override;   //�I������
	void Update() override;   //�X�V����
	void Draw() override;   //�`�揈��
	void Collision(Collider* pColliderTarget, Physics::CONTACT contact) override;   //�Փˎ��̏���

	void SetSize(D3DXVECTOR3 size) { this->m_size = size; };   //�T�C�Y

	D3DXVECTOR3 GetSize() { return m_size; };   //�T�C�Y�̎擾����
	Range GetRange() { return m_range; };   //�͈͂̎擾����

private:
	void UpdateRange();
	void UpdateLine();   //���̈ʒu�̐ݒ菈��

	D3DXVECTOR3 m_size;   //�T�C�Y
	Range m_range;   //�͈�
	Line* m_pLine[BoxCollider::NUM_LINE];   //��
};

//���̏Փ˔͈�
class SphereCollider : public Collider   //(�e)�Փ˔͈�
{
public:
	//�R���X�g���N�^
	SphereCollider(Object* pObject, float fRadius) : Collider(pObject)
	{
		//�����o�ϐ�������������
		this->SetType(Collider::TYPE::IS_SPHERE);   //���
		this->m_fRadius = fRadius;   //���a
	}

	//�f�X�g���N�^
	~SphereCollider() override
	{
	}

	void Init() override;   //����������
	void Uninit() override;   //�I������
	void Update() override;   //�X�V����
	void Draw() override;   //�`�揈��
	void Collision(Collider* pColliderTarget, Physics::CONTACT contact) override;   //�Փˎ��̏���


	float GetRadius() { return this->m_fRadius; };   //���a�̎擾

private:
	float m_fRadius;   //���a
};

#endif // !_COLLIDER_H_
