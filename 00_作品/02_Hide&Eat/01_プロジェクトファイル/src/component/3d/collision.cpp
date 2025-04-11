//=============================================================
//
// �R���W�����R���|�[�l���g [collision.cpp]
// Author: Ito Kotaro
//
//=============================================================
#include "collision.h"
#include "internal/physics.h"
#include "manager.h"


//=============================================================
// [CRigidBody] ������
//=============================================================
void CRigidBody::Init()
{
	// �R���W����
	CCollision::Create(gameObject);												// �쐬
	CCollision* pCollision = CCollision::GetCollision(gameObject);	// �擾

	// �R���W�����̍X�V
	if (pCollision != nullptr)
	{
		pCollision->UpdateCollision();
	}
}

//=============================================================
// [CRigidBody] �X�V
//=============================================================
void CRigidBody::Update()
{
}

//=============================================================
// [CRigidBody] ���W�b�h�{�f�B�̎擾
//=============================================================
btRigidBody* CRigidBody::GetRigidBody()
{
	return CCollision::GetCollision(gameObject)->GetRigidBody();
}

//=============================================================
// [CRigidBody] �R���W�����̎擾
//=============================================================
CCollision* CRigidBody::GetCollision()
{
	return CCollision::GetCollision(gameObject);
}

//=============================================================
// [CRigidBody] ��ɃA�N�e�B�u
//=============================================================
void CRigidBody::EnableAlwayActive()
{
	GetRigidBody()->setActivationState(DISABLE_DEACTIVATION);
}

//=============================================================
// [CGhostObject] ������
//=============================================================
void CGhostObject::Init()
{
	// �R���W����
	CCollision::Create(gameObject);												// �쐬
	CCollision* pCollision = CCollision::GetCollision(gameObject);	// �擾

	// �R���W�����̍X�V
	if (pCollision != nullptr)
	{
		pCollision->UpdateCollision();
	}
}

//=============================================================
// [CGhostObject] �S�[�X�g�I�u�W�F�N�g�̎擾
//=============================================================
btGhostObject* CGhostObject::GetGhostObject()
{
	return CCollision::GetCollision(gameObject)->GetGhostObject();
}

//=============================================================
// [CGhostObject] �R���W�����̎擾
//=============================================================
CCollision* CGhostObject::GetCollision()
{
	return CCollision::GetCollision(gameObject);
}


//=============================================================
// [CPoint2PointConstraint] �R���X�g���N�^
//=============================================================
CPoint2PointConstraint::CPoint2PointConstraint() : 
	m_p2p(nullptr)
{
}

//=============================================================
// [CPoint2PointConstraint] �I��
//=============================================================
void CPoint2PointConstraint::Uninit()
{
	if (m_p2p != nullptr)
	{
		// �������[���h����폜����
		CPhysics::GetInstance()->GetDynamicsWorld().removeConstraint(m_p2p);

		// �j������
		delete m_p2p;
		m_p2p = nullptr;
	}
}

//=============================================================
// [CPoint2PointConstraint] �S���ݒ�
//=============================================================
void CPoint2PointConstraint::SetConstraint(btRigidBody* rb1, btRigidBody* rb2, const D3DXVECTOR3& pivotInA, const D3DXVECTOR3& pivotInB)
{
	// �j������
	CPoint2PointConstraint::Uninit();

	// �쐬����
	m_p2p = new btPoint2PointConstraint(
		*rb1, 
		*rb2, 
		btVector3(pivotInA.x, pivotInA.y, pivotInA.z), 
		btVector3(pivotInB.x, pivotInB.y, pivotInB.z)
	);

	// �ݒ肷��
	CPhysics::GetInstance()->GetDynamicsWorld().addConstraint(m_p2p);
}


//=============================================================
// [CHingeConstraint] �R���X�g���N�^
//=============================================================
CHingeConstraint::CHingeConstraint() :
	m_hinge(nullptr)
{
}

//=============================================================
// [CHingeConstraint] �I��
//=============================================================
void CHingeConstraint::Uninit()
{
	if (m_hinge != nullptr)
	{
		// �������[���h����폜����
		CPhysics::GetInstance()->GetDynamicsWorld().removeConstraint(m_hinge);

		// �j������
		delete m_hinge;
		m_hinge = nullptr;
	}
}

//=============================================================
// [CHingeConstraint] �S���ݒ�
//=============================================================
void CHingeConstraint::SetConstraint(btRigidBody* rb, const D3DXVECTOR3& pivotInA, const D3DXVECTOR3& axisInA)
{
	// �j������
	CHingeConstraint::Uninit();

	// �쐬����
	m_hinge = new btHingeConstraint(
		*rb,
		btVector3(pivotInA.x, pivotInA.y, pivotInA.z),
		btVector3(axisInA.x, axisInA.y, axisInA.z)
	);

	// �ݒ肷��
	CPhysics::GetInstance()->GetDynamicsWorld().addConstraint(m_hinge);
}

//=============================================================
// [CHingeConstraint] �S���ݒ�
//=============================================================
void CHingeConstraint::SetConstraint(btRigidBody* rb1, btRigidBody* rb2, const D3DXVECTOR3& pivotInA, const D3DXVECTOR3& pivotInB, const D3DXVECTOR3& axisInA, const D3DXVECTOR3& axisInB)
{
	// �j������
	CHingeConstraint::Uninit();

	// �쐬����
	m_hinge = new btHingeConstraint(
		*rb1, *rb2,
		btVector3(pivotInA.x, pivotInA.y, pivotInA.z), btVector3(pivotInB.x, pivotInB.y, pivotInB.z),
		btVector3(axisInA.x, axisInA.y, axisInA.z), btVector3(axisInB.x, axisInB.y, axisInB.z)
	);

	// �ݒ肷��
	CPhysics::GetInstance()->GetDynamicsWorld().addConstraint(m_hinge);
}


//=============================================================
// [CHinge2Constraint] �R���X�g���N�^
//=============================================================
CHinge2Constraint::CHinge2Constraint() :
	m_hinge2(nullptr)
{
}

//=============================================================
// [CHinge2Constraint] �I��
//=============================================================
void CHinge2Constraint::Uninit()
{
	if (m_hinge2 != nullptr)
	{
		// �������[���h����폜����
		CPhysics::GetInstance()->GetDynamicsWorld().removeConstraint(m_hinge2);

		// �j������
		delete m_hinge2;
		m_hinge2 = nullptr;
	}
}

//=============================================================
// [CHinge2Constraint] �S���ݒ�
//=============================================================
void CHinge2Constraint::SetConstraint(btRigidBody* rb1, btRigidBody* rb2, D3DXVECTOR3 anchor, D3DXVECTOR3 parentAxis, D3DXVECTOR3 childAxis)
{
	// �j������
	CHinge2Constraint::Uninit();

	// �쐬����
	btVector3 btAnchor = btVector3(anchor.x, anchor.y, anchor.z);
	btVector3 btParentAxis = btVector3(parentAxis.x, parentAxis.y, parentAxis.z);
	btVector3 btChildAxis = btVector3(childAxis.x, childAxis.y, childAxis.z);
	m_hinge2 = new btHinge2Constraint(
		*rb1, *rb2,
		btAnchor,
		btParentAxis,
		btChildAxis
	);

	// �ݒ肷��
	CPhysics::GetInstance()->GetDynamicsWorld().addConstraint(m_hinge2, true);
}

//=============================================================
// [CBoxCollider] �R���X�g���N�^
//=============================================================
CBoxCollider::CBoxCollider(D3DXVECTOR3 size, D3DXVECTOR3 offset, D3DXVECTOR3 rot)
{
	SetSize(size);
	SetOffset(offset);
	SetRot(rot);
}

//=============================================================
// [CBoxCollider] ������
//=============================================================
void CBoxCollider::Init()
{
	// �R���W�����̍쐬�i���łɂ���ꍇ�̓X���[�j
	CCollision::Create(gameObject);

	// �R���W�����̎擾
	CCollision* pCollision = CCollision::GetCollision(gameObject);

	// �R���W�����̍X�V
	pCollision->UpdateCollision();
}

//=============================================================
// [CBoxCollider] �V�F�C�v�ɒǉ�����
//=============================================================
void CBoxCollider::AddShapes(btCompoundShape* pShapes)
{
	// ���[�J���p��
	btTransform localTrans = btTransform::getIdentity();
	localTrans.setOrigin(btVector3(GetOffset().x, GetOffset().y, GetOffset().z));

	// ��]
	btQuaternion quaternion;
	quaternion.setEuler(GetRot().y, GetRot().x, GetRot().z);
	localTrans.setRotation(quaternion);

	// �V�F�C�v��ǉ�����
	btBoxShape* box_shape = new btBoxShape(btVector3(m_size.x, m_size.y, m_size.z));
	pShapes->addChildShape(localTrans, box_shape);

	// ���X�g�ɒǉ�����
	CPhysics::GetInstance()->GetCollisionShape().push_back(box_shape);
}


//=============================================================
// [CSphereCollider] �R���X�g���N�^
//=============================================================
CSphereCollider::CSphereCollider(float fRadius, D3DXVECTOR3 offset, D3DXVECTOR3 rot)
{
	SetRadius(fRadius);
	SetOffset(offset);
	SetRot(rot);
}

//=============================================================
// [CSphereCollider] ������
//=============================================================
void CSphereCollider::Init()
{
	// �R���W�����̍쐬�i���łɂ���ꍇ�̓X���[�j
	CCollision::Create(gameObject);

	// �R���W�����̎擾
	CCollision* pCollision = CCollision::GetCollision(gameObject);

	// �R���W�����̍X�V
	pCollision->UpdateCollision();
}

//=============================================================
// [CSphereCollider] �V�F�C�v�ɒǉ�����
//=============================================================
void CSphereCollider::AddShapes(btCompoundShape* pShapes)
{
	// ���[�J���p��
	btTransform localTrans = btTransform::getIdentity();
	localTrans.setOrigin(btVector3(GetOffset().x, GetOffset().y, GetOffset().z));

	// ��]
	btQuaternion quaternion;
	quaternion.setEuler(GetRot().y, GetRot().x, GetRot().z);
	localTrans.setRotation(quaternion);

	// �V�F�C�v��ǉ�����
	btSphereShape* sphere_shape = new btSphereShape(m_fRadius);
	pShapes->addChildShape(localTrans, sphere_shape);

	// ���X�g�ɒǉ�����
	CPhysics::GetInstance()->GetCollisionShape().push_back(sphere_shape);
}


//=============================================================
// [CCapsuleCollider] �R���X�g���N�^
//=============================================================
CCapsuleCollider::CCapsuleCollider(float fRadius, float fHeight, D3DXVECTOR3 offset, D3DXVECTOR3 rot)
{
	SetRadius(fRadius);
	SetHeight(fHeight);
	SetOffset(offset);
	SetRot(rot);
}

//=============================================================
// [CCapsuleCollider] ������
//=============================================================
void CCapsuleCollider::Init()
{
	// �R���W�����̍쐬�i���łɂ���ꍇ�̓X���[�j
	CCollision::Create(gameObject);

	// �R���W�����̎擾
	CCollision* pCollision = CCollision::GetCollision(gameObject);

	// �R���W�����̍X�V
	pCollision->UpdateCollision();
}

//=============================================================
// [CCapsuleCollider] �V�F�C�v�ɒǉ�����
//=============================================================
void CCapsuleCollider::AddShapes(btCompoundShape* pShapes)
{
	// ���[�J���p��
	btTransform localTrans = btTransform::getIdentity();
	localTrans.setOrigin(btVector3(GetOffset().x, GetOffset().y, GetOffset().z));

	// ��]
	btQuaternion quaternion;
	quaternion.setEuler(GetRot().y, GetRot().x, GetRot().z);
	localTrans.setRotation(quaternion);

	// �V�F�C�v��ǉ�����
	btCapsuleShape* capsule_shape = new btCapsuleShape(m_fRadius, m_fHeight);
	pShapes->addChildShape(localTrans, capsule_shape);

	// ���X�g�ɒǉ�����
	CPhysics::GetInstance()->GetCollisionShape().push_back(capsule_shape);
}


//=============================================================
// [CCylinderCollider] �R���X�g���N�^
//=============================================================
CCylinderCollider::CCylinderCollider(float fRadius, float fHeight, D3DXVECTOR3 offset, D3DXVECTOR3 rot)
{
	SetRadius(fRadius);
	SetHeight(fHeight);
	SetOffset(offset);
	SetRot(rot);
}

//=============================================================
// [CCylinderCollider] ������
//=============================================================
void CCylinderCollider::Init()
{
	// �R���W�����̍쐬�i���łɂ���ꍇ�̓X���[�j
	CCollision::Create(gameObject);

	// �R���W�����̎擾
	CCollision* pCollision = CCollision::GetCollision(gameObject);

	// �R���W�����̍X�V
	pCollision->UpdateCollision();
}

//=============================================================
// [CCylinderCollider] �V�F�C�v�ɒǉ�����
//=============================================================
void CCylinderCollider::AddShapes(btCompoundShape* pShapes)
{
	// ���[�J���p��
	btTransform localTrans = btTransform::getIdentity();
	localTrans.setOrigin(btVector3(GetOffset().x, GetOffset().y, GetOffset().z));

	// ��]
	btQuaternion quaternion;
	quaternion.setEuler(GetRot().y, GetRot().x, GetRot().z);
	localTrans.setRotation(quaternion);

	// �V�F�C�v��ǉ�����
	btCylinderShape* cylinder_shape = new btCylinderShape(btVector3(m_fRadius, m_fHeight, m_fRadius));
	pShapes->addChildShape(localTrans, cylinder_shape);

	// ���X�g�ɒǉ�����
	CPhysics::GetInstance()->GetCollisionShape().push_back(cylinder_shape);
}


//=============================================================
// [CConeCollider] �R���X�g���N�^
//=============================================================
CConeCollider::CConeCollider(float fRadius, float fHeight, D3DXVECTOR3 offset, D3DXVECTOR3 rot)
{
	SetRadius(fRadius);
	SetHeight(fHeight);
	SetOffset(offset);
	SetRot(rot);
}

//=============================================================
// [CConeCollider] ������
//=============================================================
void CConeCollider::Init()
{
	// �R���W�����̍쐬�i���łɂ���ꍇ�̓X���[�j
	CCollision::Create(gameObject);

	// �R���W�����̎擾
	CCollision* pCollision = CCollision::GetCollision(gameObject);

	// �R���W�����̍X�V
	pCollision->UpdateCollision();
}

//=============================================================
// [CConeCollider] �V�F�C�v�ɒǉ�����
//=============================================================
void CConeCollider::AddShapes(btCompoundShape* pShapes)
{
	// ���[�J���p��
	btTransform localTrans = btTransform::getIdentity();
	localTrans.setOrigin(btVector3(GetOffset().x, GetOffset().y, GetOffset().z));

	// ��]
	btQuaternion quaternion;
	quaternion.setEuler(GetRot().y, GetRot().x, GetRot().z);
	localTrans.setRotation(quaternion);

	// �V�F�C�v��ǉ�����
	btConeShape* cone_shape = new btConeShape(m_fRadius, m_fHeight);
	pShapes->addChildShape(localTrans, cone_shape);

	// ���X�g�ɒǉ�����
	CPhysics::GetInstance()->GetCollisionShape().push_back(cone_shape);
}