//========================================================================================================
//
//�{�b�N�X�Փ˔͈͂̏���[box.cpp]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "collider.h"
#include "manager.h"
#include "rigidbody.h"
#include "behavior.h"

//========================================================================================================
//����������
//========================================================================================================
void BoxCollider::Init()
{
    for (int i = 0; i < BoxCollider::NUM_LINE; i++)
    {
        //���𐶐�����
        this->m_pLine[i] = Line::Create({ 1.0f, 0.0f, 0.0f, 1.0f });
        this->m_pLine[i]->Init();   //������
    }
}

//========================================================================================================
//�I������
//========================================================================================================
void BoxCollider::Uninit()
{
    for (int i = 0; i < BoxCollider::NUM_LINE; i++)
    {
        //����j������
        this->m_pLine[i]->Uninit();   //�I������
        delete this->m_pLine[i];
        this->m_pLine[i] = nullptr;
    }
}

//========================================================================================================
//�X�V����
//========================================================================================================
void BoxCollider::Update()
{
    //
    this->SetCollision(false);

    //�͈͂��X�V����
    this->UpdateRange();

    //���̈ʒu�̐ݒ菈�����s��
    this->UpdateLine();
}

//========================================================================================================
//�X�V����
//========================================================================================================
void BoxCollider::Draw()
{
    return;

    for (int i = 0; i < BoxCollider::NUM_LINE; i++)
    {
        //���̕`�揈�����s��
        this->m_pLine[i]->Draw();
    }
}

//============================================================================================================
//�Փˎ��̏���
//============================================================================================================
void BoxCollider::Collision(Collider* pColliderTarget, Physics::CONTACT contact)
{
    //�{�b�N�X�R���C�_�[�ɕϊ�����
    BoxCollider* pBoxColliderTarget = (BoxCollider*)pColliderTarget;

    //�Փˈʒu�ɂ���ď�����ς���
    switch (contact)
    {
    case Physics::CONTACT::IS_TOP:   //��
        //�g���K�[���m�F����
        if (pBoxColliderTarget->GetTrigger() == false)
        {//�g���K�[����Ȃ��ꍇ
            //���W�b�g�{�f�B���m�F����
            Rigidbody* pRigidbodyTarget = pBoxColliderTarget->GetObj()->GetComponent<Rigidbody>();
            if (pRigidbodyTarget == nullptr)
            {//���W�b�g�{�f�B���t���Ă��Ȃ��ꍇ
                //�V�����ʒu���v�Z����
                D3DXVECTOR3 centerNew = this->GetCenter();   //���݂̈ʒu
                centerNew.y = pBoxColliderTarget->GetRange().posMax.y + (this->GetSize().y / 2);

                ////�ړ��ʂ�ł�����
                //Rigidbody* pRigidbody = this->GetObj()->GetComponent<Rigidbody>();
                //pRigidbody->AddMove({ 0.0f, -pRigidbody->GetMove().y, 0.0f });   //�ړ���

                //�ʒu���C������
                this->SetCenter(centerNew);
            }
            else
            {//�t���Ă���ꍇ
                //���ʂ��m�F����
                if (pBoxColliderTarget->GetMass() < this->GetMass())
                {//�Ώۂ̕����y���ꍇ
                    //�V�����ʒu���v�Z����
                    D3DXVECTOR3 centerNew = pBoxColliderTarget->GetCenter();   //���݂̈ʒu
                    centerNew.y = this->m_range.posMin.y - (pBoxColliderTarget->GetSize().y / 2);

                    ////�ړ��ʂ�ł�����
                    //pRigidbodyTarget->AddMove({ 0.0f, -pRigidbodyTarget->GetMove().y,0.0f });   //�ړ���

                    //�ʒu���C������
                    pBoxColliderTarget->SetCenter(centerNew);
                }
                else
                {//�y���Ȃ��ꍇ
                    //�V�����ʒu���v�Z����
                    D3DXVECTOR3 centerNew = this->GetCenter();   //���݂̈ʒu
                    centerNew.y = pBoxColliderTarget->GetRange().posMax.y + (this->GetSize().y / 2);

                    ////�ړ��ʂ�ł�����
                    //Rigidbody* pRigidbody = this->GetObj()->GetComponent<Rigidbody>();
                    //pRigidbody->AddMove({ 0.0f, -pRigidbody->GetMove().y,0.0f });   //�ړ���

                    //�ʒu���C������
                    this->SetCenter(centerNew);
                }
            }
        }

        //�����𔲂��o��
        break;

    case Physics::CONTACT::IS_BOTTOM:   //��
        //�g���K�[���m�F����
        if (pBoxColliderTarget->GetTrigger() == false)
        {//�g���K�[����Ȃ��ꍇ
            //���W�b�g�{�f�B���m�F����
            Rigidbody* pRigidbodyTarget = pBoxColliderTarget->GetObj()->GetComponent<Rigidbody>();
            if (pRigidbodyTarget == nullptr)
            {//���W�b�g�{�f�B���t���Ă��Ȃ��ꍇ
                //�V�����ʒu���v�Z����
                D3DXVECTOR3 centerNew = this->GetCenter();   //���݂̈ʒu
                centerNew.y = pBoxColliderTarget->GetRange().posMin.y - (this->GetSize().y / 2);

                ////�ړ��ʂ�ł�����
                //Rigidbody* pRigidbody = this->GetObj()->GetComponent<Rigidbody>();
                //pRigidbody->AddMove({ 0.0f, -pRigidbody->GetMove().y, 0.0f });

                //�ʒu���C������
                this->SetCenter(centerNew);
            }
            else
            {//�t���Ă���ꍇ
                //���ʂ��m�F����
                if (pBoxColliderTarget->GetMass() < this->GetMass())
                {//�Ώۂ̕����y���ꍇ
                    //�V�����ʒu���v�Z����
                    D3DXVECTOR3 centerNew = pBoxColliderTarget->GetCenter();   //���݂̈ʒu
                    centerNew.y = this->m_range.posMax.y + (pBoxColliderTarget->GetSize().y / 2);

                    ////�ړ��ʂ�ł�����
                    //pRigidbodyTarget->AddMove({ 0.0f, -pRigidbodyTarget->GetMove().y, 0.0f });

                    //�ʒu���C������
                    pBoxColliderTarget->SetCenter(centerNew);
                }
                else
                {//�y���Ȃ��ꍇ
                    //�V�����ʒu���v�Z����
                    D3DXVECTOR3 centerNew = this->GetCenter();   //���݂̈ʒu
                    centerNew.y = pBoxColliderTarget->GetRange().posMin.y - (this->GetSize().y / 2);

                    ////�ړ��ʂ�ł�����
                    //Rigidbody* pRigidbody = this->GetObj()->GetComponent<Rigidbody>();
                    //pRigidbody->AddMove({ 0.0f, -pRigidbody->GetMove().y, 0.0f });

                    //�ʒu���C������
                    this->SetCenter(centerNew);
                }
            }
        }

        //�����𔲂��o��
        break;

    case::Physics::CONTACT::IS_RIGHT:   //�E
        //�g���K�[���m�F����
        if (pBoxColliderTarget->GetTrigger() == false)
        {//�g���K�[����Ȃ��ꍇ
            //���W�b�g�{�f�B���m�F����
            Rigidbody* pRigidbodyTarget = pBoxColliderTarget->GetObj()->GetComponent<Rigidbody>();
            if (pRigidbodyTarget == nullptr)
            {//���W�b�g�{�f�B���t���Ă��Ȃ��ꍇ
                //�V�����ʒu���v�Z����
                D3DXVECTOR3 centerNew = this->GetCenter();   //���݂̈ʒu
                centerNew.x = pBoxColliderTarget->GetRange().posMax.x + (this->GetSize().x / 2);

                ////�ړ��ʂ�ł�����
                //Rigidbody* pRigidbody = this->GetObj()->GetComponent<Rigidbody>();
                //pRigidbody->AddMove({ -pRigidbody->GetMove().x, 0.0f, 0.0f });

                //�ʒu���C������
                this->SetCenter(centerNew);
            }
            else
            {//�t���Ă���ꍇ
                //���ʂ��m�F����
                if (pBoxColliderTarget->GetMass() < this->GetMass())
                {//�Ώۂ̕����y���ꍇ
                    //�V�����ʒu���v�Z����
                    D3DXVECTOR3 centerNew = pBoxColliderTarget->GetCenter();   //���݂̈ʒu
                    centerNew.x = this->m_range.posMin.x - (pBoxColliderTarget->GetSize().x / 2);

                    ////�ړ��ʂ�ł�����
                    //pRigidbodyTarget->AddMove({ -pRigidbodyTarget->GetMove().x, 0.0f, 0.0f });

                    //�ʒu���C������
                    pBoxColliderTarget->SetCenter(centerNew);
                }
                else
                {//�y���Ȃ��ꍇ
                    //�V�����ʒu���v�Z����
                    D3DXVECTOR3 centerNew = this->GetCenter();   //���݂̈ʒu
                    centerNew.x = pBoxColliderTarget->GetRange().posMax.x + (this->GetSize().x / 2);

                    ////�ړ��ʂ�ł�����
                    //Rigidbody* pRigidbody = this->GetObj()->GetComponent<Rigidbody>();
                    //pRigidbody->AddMove({ -pRigidbody->GetMove().x, 0.0f, 0.0f });

                    //�ʒu���C������
                    this->SetCenter(centerNew);
                }
            }
        }

        //�����𔲂��o��
        break;

    case::Physics::CONTACT::IS_LEFT:   //��
        //�g���K�[���m�F����
        if (pBoxColliderTarget->GetTrigger() == false)
        {//�g���K�[����Ȃ��ꍇ
            //���W�b�g�{�f�B���m�F����
            Rigidbody* pRigidbodyTarget = pBoxColliderTarget->GetObj()->GetComponent<Rigidbody>();
            if (pRigidbodyTarget == nullptr)
            {//���W�b�g�{�f�B���t���Ă��Ȃ��ꍇ
                //�V�����ʒu���v�Z����
                D3DXVECTOR3 centerNew = this->GetCenter();   //���݂̈ʒu
                centerNew.x = pBoxColliderTarget->GetRange().posMin.x - (this->GetSize().x / 2);

                ////�ړ��ʂ�ł�����
                //Rigidbody* pRigidbody = this->GetObj()->GetComponent<Rigidbody>();
                //pRigidbody->AddMove({ -pRigidbody->GetMove().x, 0.0f, 0.0f });

                //�ʒu���C������
                this->SetCenter(centerNew);
            }
            else
            {//�t���Ă���ꍇ
                //���ʂ��m�F����
                if (pBoxColliderTarget->GetMass() < this->GetMass())
                {//�Ώۂ̕����y���ꍇ
                    //�V�����ʒu���v�Z����
                    D3DXVECTOR3 centerNew = pBoxColliderTarget->GetCenter();   //���݂̈ʒu
                    centerNew.x = this->m_range.posMax.x + (pBoxColliderTarget->GetSize().x / 2);

                    //�ړ��ʂ�ł�����
                    pRigidbodyTarget->AddMove({ -pRigidbodyTarget->GetMove().x, 0.0f, 0.0f });

                    //�ʒu���C������
                    pBoxColliderTarget->SetCenter(centerNew);
                }
                else
                {//�y���Ȃ��ꍇ
                    //�V�����ʒu���v�Z����
                    D3DXVECTOR3 centerNew = this->GetCenter();   //���݂̈ʒu
                    centerNew.x = pBoxColliderTarget->GetRange().posMin.x - (this->GetSize().x / 2);

                    ////�ړ��ʂ�ł�����
                    //Rigidbody* pRigidbody = this->GetObj()->GetComponent<Rigidbody>();
                    //pRigidbody->AddMove({ -pRigidbody->GetMove().x, 0.0f, 0.0f });

                    //�ʒu���C������
                    this->SetCenter(centerNew);
                }
            }
        }

        //�����𔲂��o��
        break;

    case::Physics::CONTACT::IS_BACK:   //��
        //�g���K�[���m�F����
        if (pBoxColliderTarget->GetTrigger() == false)
        {//�g���K�[����Ȃ��ꍇ
            //���W�b�g�{�f�B���m�F����
            Rigidbody* pRigidbodyTarget = pBoxColliderTarget->GetObj()->GetComponent<Rigidbody>();
            if (pRigidbodyTarget == nullptr)
            {//���W�b�g�{�f�B���t���Ă��Ȃ��ꍇ
                //�V�����ʒu���v�Z����
                D3DXVECTOR3 centerNew = this->GetCenter();   //���݂̈ʒu
                centerNew.z = pBoxColliderTarget->GetRange().posMax.z + (this->GetSize().z / 2);

                ////�ړ��ʂ�ł�����
                //Rigidbody* pRigidbody = this->GetObj()->GetComponent<Rigidbody>();
                //pRigidbody->AddMove({ 0.0f, 0.0f, -pRigidbody->GetMove().z });

                //�ʒu���C������
                this->SetCenter(centerNew);
            }
            else
            {//�t���Ă���ꍇ
                //���ʂ��m�F����
                if (pBoxColliderTarget->GetMass() < this->GetMass())
                {//�Ώۂ̕����y���ꍇ
                    //�V�����ʒu���v�Z����
                    D3DXVECTOR3 centerNew = pBoxColliderTarget->GetCenter();   //���݂̈ʒu
                    centerNew.z = this->m_range.posMin.z - (pBoxColliderTarget->GetSize().z / 2);

                    ////�ړ��ʂ�ł�����
                    //pRigidbodyTarget->AddMove({ 0.0f, 0.0f, -pRigidbodyTarget->GetMove().z });

                    //�ʒu���C������
                    pBoxColliderTarget->SetCenter(centerNew);
                }
                else
                {//�y���Ȃ��ꍇ
                    //�V�����ʒu���v�Z����
                    D3DXVECTOR3 centerNew = this->GetCenter();   //���݂̈ʒu
                    centerNew.z = pBoxColliderTarget->GetRange().posMax.z + (this->GetSize().z / 2);

                    ////�ړ��ʂ�ł�����
                    //Rigidbody* pRigidbody = this->GetObj()->GetComponent<Rigidbody>();
                    //pRigidbody->AddMove({ 0.0f, 0.0f, -pRigidbody->GetMove().z });

                    //�ʒu���C������
                    this->SetCenter(centerNew);
                }
            }
        }

        //�����𔲂��o��
        break;

    case::Physics::CONTACT::IS_FRONT:   //�O
        //�g���K�[���m�F����
        if (pBoxColliderTarget->GetTrigger() == false)
        {//�g���K�[����Ȃ��ꍇ
            //���W�b�g�{�f�B���m�F����
            Rigidbody* pRigidbodyTarget = pBoxColliderTarget->GetObj()->GetComponent<Rigidbody>();
            if (pRigidbodyTarget == nullptr)
            {//���W�b�g�{�f�B���t���Ă��Ȃ��ꍇ
                //�V�����ʒu���v�Z����
                D3DXVECTOR3 centerNew = this->GetCenter();   //���݂̈ʒu
                centerNew.z = pBoxColliderTarget->GetRange().posMin.z - (this->GetSize().z / 2);

                ////�ړ��ʂ�ł�����
                //Rigidbody* pRigidbody = this->GetObj()->GetComponent<Rigidbody>();
                //pRigidbody->AddMove({ 0.0f, 0.0f, -pRigidbody->GetMove().z });

                //�ʒu���C������
                this->SetCenter(centerNew);
            }
            else
            {//�t���Ă���ꍇ
                //���ʂ��m�F����
                if (pBoxColliderTarget->GetMass() < this->GetMass())
                {//�Ώۂ̕����y���ꍇ
                    //�V�����ʒu���v�Z����
                    D3DXVECTOR3 centerNew = pBoxColliderTarget->GetCenter();   //���݂̈ʒu
                    centerNew.z = this->m_range.posMax.z + (pBoxColliderTarget->GetSize().z / 2);

                    ////�ړ��ʂ�ł�����
                    //pRigidbodyTarget->AddMove({ 0.0f, 0.0f, -pRigidbodyTarget->GetMove().z });

                    //�ʒu���C������
                    pBoxColliderTarget->SetCenter(centerNew);
                }
                else
                {//�y���Ȃ��ꍇ
                    //�V�����ʒu���v�Z����
                    D3DXVECTOR3 centerNew = this->GetCenter();   //���݂̈ʒu
                    centerNew.z = pBoxColliderTarget->GetRange().posMin.z - (this->GetSize().z / 2);

                    ////�ړ��ʂ�ł�����
                    //Rigidbody* pRigidbody = this->GetObj()->GetComponent<Rigidbody>();
                    //pRigidbody->AddMove({ 0.0f, 0.0f, -pRigidbody->GetMove().z });

                    //�ʒu���C������
                    this->SetCenter(centerNew);
                }
            }
        }

        //�����𔲂��o��
        break;

    case Physics::CONTACT::IS_IN:   //��
        //�g���K�[���m�F����
        if (pBoxColliderTarget->GetTrigger() == false)
        {//�g���K�[����Ȃ��ꍇ
            //�������v�Z����
            D3DXVECTOR3 vecTarget = { pBoxColliderTarget->GetCenter().x - this->GetCenter().x, 0.0f, pBoxColliderTarget->GetCenter().z - this->GetCenter().z };   //�x�N�g��
            float fDirection = atan2f(vecTarget.x, vecTarget.z);

            //���W�b�g�{�f�B���m�F����
            Rigidbody* pRigidbodyTarget = pBoxColliderTarget->GetObj()->GetComponent<Rigidbody>();
            if (pRigidbodyTarget == nullptr)
            {//���W�b�g�{�f�B���t���Ă��Ȃ��ꍇ
                ////�ړ��ʂ�ł�����
                //Rigidbody* pRigidbody = this->GetObj()->GetComponent<Rigidbody>();
                //pRigidbody->AddMove({ -pRigidbody->GetMove() });

                ////�ړ��ʂ����Z����
                //pRigidbody->AddMove({ sinf(fDirection - D3DX_PI), 0.0f, cosf(fDirection - D3DX_PI) });
            }
            else
            {//�t���Ă���ꍇ
                //���ʂ��m�F����
                if (pBoxColliderTarget->GetMass() < this->GetMass())
                {//�Ώۂ̕����y���ꍇ
                    //////�ړ��ʂ�ł�����
                    //pRigidbodyTarget->AddMove({ -pRigidbodyTarget->GetMove() });

                    ////�ړ��ʂ����Z����
                    //pRigidbodyTarget->AddMove({ sinf(fDirection), 0.0f, cosf(fDirection) });
                }
                else if (pBoxColliderTarget->GetMass() > this->GetMass())
                {//�Ώۂ��d�����ꍇ
                    ////�ړ��ʂ�ł�����
                    //Rigidbody* pRigidbody = this->GetObj()->GetComponent<Rigidbody>();
                    //pRigidbody->AddMove({ -pRigidbody->GetMove() });

                    ////�ړ��ʂ����Z����
                    //pRigidbody->AddMove({ sinf(fDirection - D3DX_PI), 0.0f, cosf(fDirection - D3DX_PI) });
                }
                else
                {//�����ꍇ
                    ////�ړ��ʂ����Z����
                    //Rigidbody* pRigidbody = this->GetObj()->GetComponent<Rigidbody>();
                    //pRigidbody->AddMove({ sinf(fDirection - D3DX_PI), 0.0f, cosf(fDirection - D3DX_PI) });

                    ////�ړ��ʂ����Z����
                    //pRigidbodyTarget->AddMove({ sinf(fDirection), 0.0f, cosf(fDirection) });
                }
            }
        }

        //�����𔲂��o��
        break;
    }

    //���ɏՓˏ��������Ă��邩�m�F����
    if (this->GetCollision() == false)
    {
        //���������邩�m�F����
        Behavior* pBehavior = this->GetObj()->GetComponent<Behavior>();
        if (pBehavior != nullptr)
        {
            //�I�u�W�F�N�g�̏Փˎ��̏������s��
            pBehavior->Collision(pColliderTarget->GetObj(), contact);
            this->SetCollision(true);
        }
    }

    //���ɏՓ˂��Ă��邩�m�F����
    if (pColliderTarget->GetCollision() == false)
    {
        //���������邩�m�F����
        Behavior* pBehaviorTarget = pColliderTarget->GetObj()->GetComponent<Behavior>();
        if (pBehaviorTarget != nullptr)
        {
            //�I�u�W�F�N�g�̏Փˎ��̏������s��
            pBehaviorTarget->Collision(this->GetObj(), contact);
            pColliderTarget->SetCollision(true);
        }
    }
}

//========================================================================================================
//�͈͂̍X�V����
//========================================================================================================
void BoxCollider::UpdateRange()
{
    D3DXVECTOR3 pos = this->GetCenter();
    D3DXVECTOR3 posOld = this->GetCenterOld();

    //�Փ˔͈͂��v�Z����
    this->m_range.posMax =
    {
        pos.x + (this->m_size.x / 2),
        pos.y + (this->m_size.y / 2),
        pos.z + (this->m_size.z / 2),
    };   //�ő�͈�

    this->m_range.posMaxOld =
    {
        posOld.x + (this->m_size.x / 2),
        posOld.y + (this->m_size.y / 2),
        posOld.z + (this->m_size.z / 2),
    };   //�O��̍ő�͈�

    this->m_range.posMin =
    {
        pos.x - (this->m_size.x / 2),
        pos.y - (this->m_size.y / 2),
        pos.z - (this->m_size.z / 2),
    };   //�ŏ��͈�

    this->m_range.posMinOld =
    {
        posOld.x - (this->m_size.x / 2),
        posOld.y - (this->m_size.y / 2),
        posOld.z - (this->m_size.z / 2),
    };   //�O��̍ŏ��͈�
}

//========================================================================================================
//���̈ʒu�̐ݒ菈��
//========================================================================================================
void BoxCollider::UpdateLine()
{
    //���̈ʒu��ݒ肷��
    //��4�ӂ̐ݒ�
    this->m_pLine[0]->SetPos(
        {
            this->m_range.posMin.x,
            this->m_range.posMin.y,
            this->m_range.posMin.z
        },
        {
            this->m_range.posMax.x,
            this->m_range.posMin.y,
            this->m_range.posMin.z
        });

    this->m_pLine[1]->SetPos(
        {
            this->m_range.posMax.x,
            this->m_range.posMin.y,
            this->m_range.posMin.z
        },
        {
            this->m_range.posMax.x,
            this->m_range.posMin.y,
            this->m_range.posMax.z
        });

    this->m_pLine[2]->SetPos(
        {
            this->m_range.posMax.x,
            this->m_range.posMin.y,
            this->m_range.posMax.z
        },
        {
            this->m_range.posMin.x,
            this->m_range.posMin.y,
            this->m_range.posMax.z
        });

    this->m_pLine[3]->SetPos(
        {
            this->m_range.posMin.x,
            this->m_range.posMin.y,
            this->m_range.posMax.z
        },
        {
            this->m_range.posMin.x,
            this->m_range.posMin.y,
            this->m_range.posMin.z
        });

    //��4�ӂ̐ݒ�
    this->m_pLine[4]->SetPos(
        {
            this->m_range.posMin.x,
            this->m_range.posMin.y,
            this->m_range.posMin.z
        },
        {
            this->m_range.posMin.x,
            this->m_range.posMax.y,
            this->m_range.posMin.z
        });

    this->m_pLine[5]->SetPos(
        {
            this->m_range.posMax.x,
            this->m_range.posMin.y,
            this->m_range.posMin.z
        },
        {
            this->m_range.posMax.x,
            this->m_range.posMax.y,
            this->m_range.posMin.z
        });

    this->m_pLine[6]->SetPos(
        {
            this->m_range.posMax.x,
            this->m_range.posMin.y,
            this->m_range.posMax.z
        },
        {
            this->m_range.posMax.x,
            this->m_range.posMax.y,
            this->m_range.posMax.z
        });

    this->m_pLine[7]->SetPos(
        {
            this->m_range.posMin.x,
            this->m_range.posMin.y,
            this->m_range.posMax.z
        },
        {
            this->m_range.posMin.x,
            this->m_range.posMax.y,
            this->m_range.posMax.z
        });

    //��4�ӂ̐ݒ�
    this->m_pLine[8]->SetPos(
        {
            this->m_range.posMin.x,
            this->m_range.posMax.y,
            this->m_range.posMin.z
        },
        {
            this->m_range.posMax.x,
            this->m_range.posMax.y,
            this->m_range.posMin.z
        });

    this->m_pLine[9]->SetPos(
        {
            this->m_range.posMax.x,
            this->m_range.posMax.y,
            this->m_range.posMin.z
        },
        {
            this->m_range.posMax.x,
            this->m_range.posMax.y,
            this->m_range.posMax.z
        });

    this->m_pLine[10]->SetPos(
        {
            this->m_range.posMax.x,
            this->m_range.posMax.y,
            this->m_range.posMax.z
        },
        {
            this->m_range.posMin.x,
            this->m_range.posMax.y,
            this->m_range.posMax.z
        });

    this->m_pLine[11]->SetPos(
        {
            this->m_range.posMin.x,
            this->m_range.posMax.y,
            this->m_range.posMax.z
        },
        {
            this->m_range.posMin.x,
            this->m_range.posMax.y,
            this->m_range.posMin.z
        });

    for (int i = 0; i < BoxCollider::NUM_LINE; i++)
    {
        //���̍X�V�������s��
        this->m_pLine[i]->Update();
    }
}