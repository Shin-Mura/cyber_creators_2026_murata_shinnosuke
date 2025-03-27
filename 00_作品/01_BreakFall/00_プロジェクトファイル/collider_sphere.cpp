//========================================================================================================
//
//���̏Փ˔͈͂̏���[collider_sphere.cpp]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "collider.h"
#include "benlib.h"
#include "manager.h"
#include "transform.h"
#include "rigidbody.h"
#include "behavior.h"

//========================================================================================================
//����������
//========================================================================================================
void SphereCollider::Init()
{
}

//========================================================================================================
//�I������
//========================================================================================================
void SphereCollider::Uninit()
{
}

//========================================================================================================
//�X�V����
//========================================================================================================
void SphereCollider::Update()
{
    ////�g���K�[�t���O���m�F����
    //if (this->GetTrigger() == false)
    //{
    //    //�R���|�[�l���g���m�F����
    //    if (this->GetObj()->GetComponent<Rigidbody>() != nullptr)
    //    {//���W�b�g�{�f�B���t���Ă���ꍇ
    //        //�����蔻��̉��Z�񐔕��J��Ԃ�
    //        for (int i = 0; i < Collider::CALC_PHYSICS; i++)
    //        {
    //            //�����蔻��̉��Z���s��
    //            Physics::Get()->Calc(this);
    //        }
    //    }
    //}
}

//========================================================================================================
//�X�V����
//========================================================================================================
void SphereCollider::Draw()
{

}

//============================================================================================================
//�Փˎ��̏���
//============================================================================================================
void SphereCollider::Collision(Collider* pColliderTarget, Physics::CONTACT contact)
{
    //���̃R���C�_�[�ɕϊ�����
    SphereCollider* pSphereColliderTarget = (SphereCollider*)pColliderTarget;

    //���g�ƑΏۂ̋������v�Z����
    D3DXVECTOR3 dis = Benlib::Distance(
        this->GetObj()->GetComponent<Transform>()->GetPos(), 
        pSphereColliderTarget->GetObj()->GetComponent<Transform>()->GetPos());

    //���荞��ł��邩�m�F����
    float fRadiusSum = this->m_fRadius + pSphereColliderTarget->GetRadius();
    if (fRadiusSum < dis.x && fRadiusSum < dis.y)
    {
        //�������v�Z����
        D3DXVECTOR3 dire = Benlib::Direction(
            this->GetObj()->GetComponent<Transform>()->GetPos(),
            pSphereColliderTarget->GetObj()->GetComponent<Transform>()->GetPos());

        //�ʒu���C������
        D3DXVECTOR3 posNew =
        {
            pSphereColliderTarget->GetObj()->GetComponent<Transform>()->GetPos().x - fRadiusSum * sinf(dire.x) * sinf(dire.y),
            pSphereColliderTarget->GetObj()->GetComponent<Transform>()->GetPos().y - fRadiusSum * cosf(dire.x),
            pSphereColliderTarget->GetObj()->GetComponent<Transform>()->GetPos().z - fRadiusSum * sinf(dire.x) * cosf(dire.y),
        };
    }

    //�I�u�W�F�N�g�̏Փˎ��̏������s��
    this->GetObj()->GetComponent<Behavior>()->Collision(pColliderTarget->GetObj(), contact);
    pColliderTarget->GetObj()->GetComponent<Behavior>()->Collision(this->GetObj(), contact);
}