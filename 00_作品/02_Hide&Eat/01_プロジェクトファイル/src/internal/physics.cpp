//=============================================================
//
// 3D���� [physics.cpp]
// Author: Ito Kotaro
// 
// ����:
// �����G���W�����g�p��������
//
//=============================================================
#include "physics.h"
#include "manager.h"
#include "component/3d/collision.h"
#include "component/3d/line.h"
#include "benlib.h"

// �ÓI�����o�̏�����
std::vector<CCollision*> CCollision::m_collisions;
btDiscreteDynamicsWorld* CPhysics::m_dynamicsWorld = nullptr;
btAlignedObjectArray<btCollisionShape*> CPhysics::m_collisionShapes;
CPhysicsDebugDraw* CPhysics::m_debugDraw = nullptr;

// �ݒ�
constexpr bool COLLISION_WIREFRAME = true;

//=============================================================
// [CPhysicsDebugDraw] �R���X�g���N�^
//=============================================================
CPhysicsDebugDraw::CPhysicsDebugDraw()
{
	m_pLineObject = new GameObject();		// ���C���`��p�̃Q�[���I�u�W�F�N�g���쐬
	m_pLineObject->SetName("PhysicsDebugLines");
	m_pLineObject->SetTag(TAG_NODESTROY);
}

//=============================================================
// [CPhysicsDebugDraw] ���C���̕`��
//=============================================================
void CPhysicsDebugDraw::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
#if _DEBUG
	// ���C���̃R���|�[�l���g��ǉ�����
	for (unsigned int i = 0; i < m_pLines.size(); i++)
	{
		if (!m_pLines[i]->enabled)
		{
			m_pLines[i]->SetLine({ from.getX(), from.getY(), from.getZ() }, { to.getX(), to.getY(), to.getZ() }, { color.getX(), color.getY(), color.getZ(), 1.0f });
			m_pLines[i]->enabled = true;
			return;
		}
	}

	// ���C�������ׂĖ��܂��Ă���Ƃ��i�ǉ�����j
	CLine* pLine = m_pLineObject->AddComponent<CLine>();
	pLine->SetLine({ from.getX(), from.getY(), from.getZ() }, { to.getX(), to.getY(), to.getZ() }, { color.getX(), color.getY(), color.getZ(), 1.0f });
	pLine->enabled = true;
	m_pLines.push_back(pLine);
#endif
}

//=============================================================
// [CPhysicsDebugDraw] ���C���̃N���A
//=============================================================
void CPhysicsDebugDraw::clearLines()
{
#if _DEBUG
	for (unsigned int i = 0; i < m_pLines.size(); i++)
	{
		m_pLines[i]->enabled = false;
	}
#endif
}

//=============================================================
// [CPhysics] �R���X�g���N�^
//=============================================================
CPhysics::CPhysics() : m_isUpdatePhysics(true)
{

}

//=============================================================
// [CPhysics] �f�X�g���N�^
//=============================================================
CPhysics::~CPhysics()
{

}

//=============================================================
// [CPhysics] ������
//=============================================================
void CPhysics::Init()
{
	// �R���W�����̐ݒ�
	m_collisionConfiguration = new btDefaultCollisionConfiguration();
	m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);

	// �u���[�h�t�F�[�Y�@�̐ݒ�
	m_overlappingPairCache = new btDbvtBroadphase();

	// �S���̃\���o�ݒ�
	m_solver = new btSequentialImpulseConstraintSolver;

	// Bullet���[���h���쐬
	m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_overlappingPairCache, m_solver, m_collisionConfiguration);

	// �S�[�X�g
	m_ghostPairCollback = new btGhostPairCallback();
	m_dynamicsWorld->getPairCache()->setInternalGhostPairCallback(m_ghostPairCollback);

	// �f�o�b�O
	m_debugDraw = new CPhysicsDebugDraw();
	m_debugDraw->setDebugMode(COLLISION_WIREFRAME ? btIDebugDraw::DBG_DrawWireframe : btIDebugDraw::DBG_NoDebug);
	m_dynamicsWorld->setDebugDrawer(m_debugDraw);

	// �A�N�V�����C���^�[�t�F�C�X
	m_actionInterface = new CActionInterface();
	m_dynamicsWorld->addAction(m_actionInterface);

	// �d�͂�ݒ�
	m_dynamicsWorld->setGravity(btVector3(0, -90, 0));
}

//=============================================================
// [CPhysics] �I��
//=============================================================
void CPhysics::Uninit()
{
	// �`����폜����
	for (int i = 0; i < m_collisionShapes.size(); i++)
	{
		btCollisionShape* shape = m_collisionShapes[i];
		m_collisionShapes[i] = nullptr;
		delete shape;
	}

	// �S�����폜����
	for (int i = 0; i < m_dynamicsWorld->getNumConstraints(); i++)
	{
		btTypedConstraint* pConstraint = m_dynamicsWorld->getConstraint(i);
		m_dynamicsWorld->removeConstraint(pConstraint);
		delete pConstraint;
	}

	// �A�N�V�����C���^�[�t�F�C�X�̔j��
	if (m_actionInterface != nullptr)
	{
		m_dynamicsWorld->removeAction(m_actionInterface);		// ���[���h����폜����
		delete m_actionInterface;
		m_actionInterface = nullptr;
	}

	// �������[���h�̔j��
	if (m_dynamicsWorld != nullptr)
	{
		delete m_dynamicsWorld;
		m_dynamicsWorld = nullptr;
	}

	// �\���o�̔j��
	if (m_solver != nullptr)
	{
		delete m_solver;
		m_solver = nullptr;
	}

	// �I�[�o�[���b�s���O�y�A�L���b�V���̔j��
	if (m_overlappingPairCache != nullptr)
	{
		delete m_overlappingPairCache;
		m_overlappingPairCache = nullptr;
	}

	// �f�B�X�p�b�`���[�̔j��
	if (m_dispatcher != nullptr)
	{
		delete m_dispatcher;
		m_dispatcher = nullptr;
	}

	// �R���W�����ݒ�̔j��
	if (m_collisionConfiguration != nullptr)
	{
		delete m_collisionConfiguration;
		m_collisionConfiguration = nullptr;
	}

	// �S�[�X�g�R�[���o�b�N�̔j��
	if (m_ghostPairCollback != nullptr)
	{
		delete m_ghostPairCollback;
		m_ghostPairCollback = nullptr;
	}

	// �f�o�b�O�`��̔j��
	if (m_debugDraw != nullptr)
	{
		delete m_debugDraw;
		m_debugDraw = nullptr;
	}

	m_collisionShapes.clear();
}

//=============================================================
// [CPhysics] �X�V
//=============================================================
void CPhysics::Update()
{
	// �������[���h��i�߂�
	if (m_isUpdatePhysics)
	{
		m_dynamicsWorld->stepSimulation(static_cast<btScalar>(1. / 60.), 1);
		m_dynamicsWorld->debugDrawWorld();
	}

	// �R���W�������X�g���擾����
	std::vector<CCollision*> pCollisions = CCollision::GetCollisions();

	for (unsigned int i = 0; i < pCollisions.size(); i++)
	{
		// ���W�b�h�{�f�B���擾����
		btRigidBody* pRigidBody = pCollisions[i]->GetRigidBody();
		btGhostObject* pGhostObject = pCollisions[i]->GetGhostObject();
		btTransform resultTrans;		// ���ʃg�����X�t�H�[��

		// �O��̉�]�ɕύX���������Ă��Ȃ���
		if (pCollisions[i]->GetBeforeRot() != pCollisions[i]->GetAttachObject()->transform->GetWQuaternion())
		{
			// �ύX��̉�]�̎擾
			D3DXQUATERNION wRot = pCollisions[i]->GetAttachObject()->transform->GetWQuaternion();

			// �V���ɐݒ肷���]���쐬����
			btQuaternion quaternion(wRot.x, wRot.y, wRot.z, wRot.w);

			// ��]��K�p����
			if (pRigidBody != nullptr)
			{ // ���W�b�h�{�f�B�[�̏ꍇ
				resultTrans = pRigidBody->getWorldTransform();
				resultTrans.setRotation(quaternion);
				pRigidBody->setWorldTransform(resultTrans);

			}
			else
			{ // ���W�b�h�{�f�B�[�ȊO�̏ꍇ
				resultTrans = pGhostObject->getWorldTransform();
				resultTrans.setRotation(quaternion);
				pGhostObject->setWorldTransform(resultTrans);
			}
		}

		// �O��̈ʒu�ɕύX���������Ă��Ȃ���
		if (pCollisions[i]->GetBeforePos() != pCollisions[i]->GetAttachObject()->transform->GetWPos())
		{
			// �ύX��̈ʒu�̎擾
			D3DXVECTOR3 wPos = pCollisions[i]->GetAttachObject()->transform->GetWPos();

			// �ʒu��K�p����
			if (pRigidBody != nullptr)
			{ // ���W�b�h�{�f�B�[�̏ꍇ
				if (pCollisions[i]->GetIsKinematic())
				{ // �L�l�}�e�B�b�N�I�u�W�F�N�g�̂Ƃ�
					btTransform newTrans;
					pRigidBody->getMotionState()->getWorldTransform(newTrans);
					newTrans.getOrigin() = btVector3(wPos.x, wPos.y, wPos.z);
					pRigidBody->getMotionState()->setWorldTransform(newTrans);
				}
				else
				{ // �L�l�}�e�B�b�N�I�u�W�F�N�g�ȊO�̂Ƃ�
					D3DXVECTOR3 moveTrans = wPos - pCollisions[i]->GetBeforePos();
					pRigidBody->translate(btVector3(moveTrans.x, moveTrans.y, moveTrans.z));
				}
			}
			else
			{ // ���W�b�h�{�f�B�[�ȊO�̏ꍇ
				resultTrans = pGhostObject->getWorldTransform();
				resultTrans.setOrigin(btVector3(wPos.x, wPos.y, wPos.z));
				pGhostObject->setWorldTransform(resultTrans);
			}
		}

		// ���W�b�h�{�f�B�[�̏���
		if (pRigidBody != nullptr)
		{
			// ���W�b�h�{�f�B�̃g�����X�t�H�[�������擾����
			pRigidBody->getMotionState()->getWorldTransform(resultTrans);

			// �A�^�b�`����Ă���Q�[���I�u�W�F�N�g�̃g�����X�t�H�[�����擾
			Transform* pTransform = pCollisions[i]->GetAttachObject()->transform;

			// �ʒu�̔��f
			pTransform->SetPos({ resultTrans.getOrigin().getX(), resultTrans.getOrigin().getY(), resultTrans.getOrigin().getZ() });

			// �����̔��f
			pTransform->SetQuaternion(D3DXQUATERNION(resultTrans.getRotation().getX(), resultTrans.getRotation().getY(), resultTrans.getRotation().getZ(), resultTrans.getRotation().getW()));
		}
	}

	// �O��̃g�����X�t�H�[���l�Ƃ��ĕۑ�����
	for (unsigned int i = 0; i < pCollisions.size(); i++)
	{
		pCollisions[i]->SaveTransform();
	}
}





//=============================================================
// [CCollision] �R���X�g���N�^
//=============================================================
CCollision::CCollision(GameObject* gameObject) : m_pAttachObject(gameObject)
{
	m_pGhostObject = nullptr;
	m_pRigidBody = nullptr;
	m_fMass = 1.0f;
	m_fFriction = 1.0f;
	m_bTrigger = false;
	m_bKinematic = false;
	m_nGroup = 0;
	m_nMask = 0;
	m_bUseFilter = false;
	m_beforePos = gameObject->transform->GetWPos();
	m_beforeRot = gameObject->transform->GetWQuaternion();
}

//=============================================================
// [CCollision] �f�X�g���N�^
//=============================================================
CCollision::~CCollision()
{

}

//=============================================================
// [CCollision] ������
//=============================================================
void CCollision::Init()
{
	UpdateCollision();
}

//=============================================================
// [CCollision] �I��
//=============================================================
void CCollision::Uninit()
{
	// �`��̔j��
	if (m_compShape != nullptr)
	{
		for (int i = 0; i < m_compShape->getNumChildShapes(); i++)
		{
			m_compShape->removeChildShape(m_compShape->getChildShape(0));
		}

		delete m_compShape;
		m_compShape = nullptr;
	}

	// �S�[�X�g�I�u�W�F�N�g�̔j��
	if (m_pGhostObject != nullptr)
	{
		CPhysics::GetInstance()->GetDynamicsWorld().removeCollisionObject(m_pGhostObject);
		delete m_pGhostObject;
		m_pGhostObject = nullptr;
	}

	// ���W�b�h�{�f�B�̔j��
	if (m_pRigidBody != nullptr)
	{
		// ���[�V�����X�e�[�g�̔j��
		if (m_pRigidBody->getMotionState() != nullptr)
		{
			delete m_pRigidBody->getMotionState();
		}

		CPhysics::GetInstance()->GetDynamicsWorld().removeRigidBody(m_pRigidBody);
		delete m_pRigidBody;
		m_pRigidBody = nullptr;
	}
}

//=============================================================
// [CCollision] �i�O��̒l�Ƃ��āj�g�����X�t�H�[���l�̕ۑ�
//=============================================================
void CCollision::SaveTransform()
{
	m_beforePos = m_pAttachObject->transform->GetWPos();
	m_beforeRot = m_pAttachObject->transform->GetWQuaternion();
}

//=============================================================
// [CCollision] �g���K�[��Ԃ̐ݒ�
//=============================================================
void CCollision::IsTrigger(const bool& isTrigger)
{
	m_bTrigger = isTrigger;		// �ݒ�ύX

	// �R���W�����̍X�V
	UpdateCollision();
}

//=============================================================
// [CCollision] �L�l�}�e�B�b�N�̐ݒ�
//=============================================================
void CCollision::IsKinematic(const bool& isKinematic)
{
	m_bKinematic = isKinematic;		// �ݒ�ύX

	// �R���W�����̍X�V
	UpdateCollision();
}

//=============================================================
// [CCollision] ���ʂ̐ݒ�
//=============================================================
void CCollision::SetMass(const float& fMass)
{
	m_fMass = fMass;		// �ݒ�ύX

	// �R���W�����̍X�V
	UpdateCollision();
}

//=============================================================
// [CCollision] ���C�̐ݒ�
//=============================================================
void CCollision::SetFriction(const float& fFriction)
{
	m_fFriction = fFriction;		// �ݒ�ύX

	// �R���W�����̍X�V
	UpdateCollision();
}

//=============================================================
// [CCollision] ���s���x�̎擾
//=============================================================
float CCollision::GetWalkSpeed()
{
	if (m_pRigidBody != nullptr)
	{ // ���W�b�h�{�f�B�̂Ƃ�
		return fabsf(m_pRigidBody->getLinearVelocity().getX()) + fabsf(m_pRigidBody->getLinearVelocity().getZ());
	}
	return 0.0f;
}

//=============================================================
// [CCollision] �R���W�����̍X�V
//=============================================================
void CCollision::UpdateCollision()
{
	// �������[���h���擾����
	btDiscreteDynamicsWorld& pDynamicsWorld = CPhysics::GetInstance()->GetDynamicsWorld();

	// ���W�b�h�{�f�B�ƃS�[�X�g�I�u�W�F�N�g��j������
	if (m_pRigidBody != nullptr)
	{
		// ���[�V�����X�e�[�g�̔j��
		if (m_pRigidBody->getMotionState() != nullptr)
		{
			delete m_pRigidBody->getMotionState();
		}

		pDynamicsWorld.removeRigidBody(m_pRigidBody);
		delete m_pRigidBody;
		m_pRigidBody = nullptr;
	}
	if (m_pGhostObject != nullptr)
	{
		pDynamicsWorld.removeCollisionObject(m_pGhostObject);
		delete m_pGhostObject;
		m_pGhostObject = nullptr;
	}

	// �`����X�V����
	UpdateShapes();


	// ���W�b�h�{�f�B�R���|�[�l���g���擾����
	CRigidBody* pCmpRigidBody = m_pAttachObject->GetComponent<CRigidBody>();

	if (pCmpRigidBody != nullptr)
	{ // ���W�b�h�{�f�B�R���|�[�l���g�����݂���Ƃ�
		// ���̂̌`��
		btCollisionShape* shapes = m_compShape;
		btScalar mass = m_fMass;

		// �ړ�����I�u�W�F�N�g��
		bool bIsDynamic = (mass != 0.0f);

		// �ʒu��ݒ�
		D3DXVECTOR3 worldPos = m_pAttachObject->transform->GetWPos();
		btTransform startTransform;
		startTransform.setIdentity();
		startTransform.setOrigin(btVector3(worldPos.x, worldPos.y, worldPos.z));

		// ��]��ݒ�
		D3DXVECTOR3 worldRot = m_pAttachObject->transform->GetWRot();
		btQuaternion quaternion;
		quaternion.setEuler(worldRot.y, worldRot.x, worldRot.z);
		startTransform.setRotation(quaternion);

		// �������[�����g
		btVector3 inertia(0, 0, 0);
		if (bIsDynamic)
		{
			shapes->calculateLocalInertia(mass, inertia);
		}
		
		// ���̑���
		btMotionState* pMotionState = new btDefaultMotionState(startTransform);

		// ���̍쐬
		btRigidBody::btRigidBodyConstructionInfo rb_info(mass, pMotionState, shapes, inertia);
		m_pRigidBody = new btRigidBody(rb_info);

		// ���C�ݒ�
		m_pRigidBody->setFriction(m_fFriction);

		// �L�l�}�e�B�b�N��
		if (m_bKinematic)
		{
			m_pRigidBody->setCollisionFlags(m_pRigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
		}

		// �������[���h�ɒǉ�
		if (!m_bUseFilter)
		{ // �t�B���^�[���g�p���Ȃ�
			pDynamicsWorld.addRigidBody(m_pRigidBody);
		}
		else
		{ // �t�B���^�[���g�p����
			pDynamicsWorld.addRigidBody(m_pRigidBody, m_nGroup, m_nMask);
		}
	}
	else
	{	// �S�[�X�g�I�u�W�F�N�g�̂Ƃ�
		// �S�[�X�g�I�u�W�F�N�g���쐬����
		m_pGhostObject = new btGhostObject;

		// �`���ݒ肷��
		m_pGhostObject->setCollisionShape(m_compShape);

		// ���C�ݒ�
		m_pGhostObject->setFriction(m_fFriction);

		// ���̃I�u�W�F�N�g�Ɋ����邩
		if (m_bTrigger)
		{
			m_pGhostObject->setCollisionFlags(m_pGhostObject->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
		}

		// �ʒu��ݒ�
		D3DXVECTOR3 worldPos = m_pAttachObject->transform->GetWPos();
		btTransform startTransform;
		startTransform.setIdentity();
		startTransform.setOrigin(btVector3(worldPos.x, worldPos.y, worldPos.z));

		// ��]��ݒ�
		D3DXVECTOR3 worldRot = m_pAttachObject->transform->GetWRot();
		btQuaternion quaternion;
		quaternion.setEuler(worldRot.y, worldRot.x, worldRot.z);
		startTransform.setRotation(quaternion);

		m_pGhostObject->setWorldTransform(startTransform);

		// �������[���h�ɒǉ�
		if (!m_bUseFilter)
		{ // �t�B���^�[���g�p���Ȃ�
			pDynamicsWorld.addCollisionObject(m_pGhostObject);
		}
		else
		{ // �t�B���^�[���g�p����
			pDynamicsWorld.addCollisionObject(m_pGhostObject, m_nGroup, m_nMask);
		}
	}
}

//=============================================================
// [CCollision] �`��̍X�V
//=============================================================
void CCollision::UpdateShapes()
{
	// ���݂̌`���j������
	if (m_compShape != nullptr)
	{
		for (int i = m_compShape->getNumChildShapes() - 1; i >= 0; i--)
		{
			m_compShape->removeChildShape(m_compShape->getChildShape(i));
		}
		delete m_compShape;
		m_compShape = nullptr;
	}

	// �V�F�C�v���쐬����
	m_compShape = new btCompoundShape;

	// �`���ǉ�
	std::vector<CCollider*> pColliders = m_pAttachObject->GetComponents<CCollider>(true);
	for (unsigned int i = 0; i < pColliders.size(); i++)
	{
		pColliders[i]->AddShapes(m_compShape);
	}

	// �X�P�[����ݒ肷��
	//D3DXVECTOR3 scale = m_pAttachObject->transform->GetScale();
	//m_compShape->setLocalScaling(btVector3(scale.x, scale.y, scale.z));
}

//=============================================================
// [CCollision] ����
//=============================================================
void CCollision::Create(GameObject* gameObject)
{
	// ���łɃR���W�������Ȃ����𒲂ׂ�
	if (isCollisionExist(gameObject))
	{ // ���݂���Ƃ�
		return;
	}

	// �R���W�����𐶐�����
	CCollision* pCollision = new CCollision(gameObject);
	pCollision->Init();

	// ���X�g�ɒǉ�����
	m_collisions.push_back(pCollision);

	// �O���[�vID��ݒ肷��
	pCollision->m_nGroup = static_cast<int>(m_collisions.size());
}

//=============================================================
// [CCollision] �t�B���^�[��ݒ肷��
//=============================================================
void CCollision::SetFilter(const int& nGroup, const int& nMask)
{
	m_nGroup = nGroup;
	m_nMask = nMask;
}

//=============================================================
// [CCollision] �t�B���^�[���g�p���邩
//=============================================================
void CCollision::UseFilter(const bool& bUse)
{
	m_bUseFilter = bUse;
}

//=============================================================
// [CCollision] �Q�[���I�u�W�F�N�g�̃R���W���������݂��邩�𒲂ׂ�
//=============================================================
bool CCollision::isCollisionExist(GameObject* gameObject)
{
	for (unsigned int i = 0; i < m_collisions.size(); i++)
	{
		if (m_collisions[i]->m_pAttachObject == gameObject)
		{
			return true;	// ��������
		}
	}
	return false;
}

//=============================================================
// [CCollision] �R���W�����I�u�W�F�N�g����Q�[���I�u�W�F�N�g���擾����
//=============================================================
GameObject* CCollision::GetGameObjectFromCollisionObj(const btCollisionObject* collision)
{
	// ���ׂẴR���W�����I�u�W�F�N�g�̎擾
	std::vector<CCollision*>& pCollisions = CCollision::GetCollisions();

	for (unsigned int i = 0; i < pCollisions.size(); i++)
	{
		if (pCollisions[i] != nullptr)
		{ // nullptr�`�F�b�N
			if (pCollisions[i]->GetGhostObject() == collision ||
				pCollisions[i]->GetRigidBody() == collision)
			{ // ���������Ƃ�
				return pCollisions[i]->GetAttachObject();		// �A�^�b�`����Ă���Q�[���I�u�W�F�N�g��Ԃ�
			}
		}
	}

	return nullptr;	// ������Ȃ�����
}

//=============================================================
// [CCollision] �R���W�������擾����
//=============================================================
CCollision* CCollision::GetCollision(GameObject* gameObject)
{
	for (unsigned int i = 0; i < m_collisions.size(); i++)
	{
		if (m_collisions[i]->m_pAttachObject == gameObject)
		{
			return m_collisions[i];		// �R���W������Ԃ�
		}
	}
	return nullptr;
}

//=============================================================
// [CCollision] �R���W�������폜����
//=============================================================
void CCollision::RemoveCollision(GameObject* gameObject)
{
	for (unsigned int i = 0; i < m_collisions.size(); i++)
	{
		if (m_collisions[i]->m_pAttachObject == gameObject)
		{
			// �j������
			m_collisions[i]->Uninit();
			delete m_collisions[i];
			m_collisions[i] = nullptr;

			// ���X�g����폜
			m_collisions.erase(m_collisions.begin() + i);
			return;
		}
	}
}

//=============================================================
// [CActionInterface] �A�N�V�����̍X�V
//=============================================================
void CActionInterface::updateAction(btCollisionWorld* collisionWorld, btScalar deltaTimeStep)
{
	// ���ׂẴR���W�����I�u�W�F�N�g�̎擾
	std::vector<CCollision*>& pCollisions = CCollision::GetCollisions();

	for (unsigned int nCntObj = 0; nCntObj < pCollisions.size(); nCntObj++)
	{
		if (pCollisions[nCntObj]->GetGhostObject() != nullptr && pCollisions[nCntObj]->GetIsTrigger())
		{ // �S�[�X�g�I�u�W�F�N�g���g���K�[�̂Ƃ�
			btGhostObject* pObj = pCollisions[nCntObj]->GetGhostObject();		// �ΏۃI�u�W�F�N�g�̃|�C���^
			std::vector<Component*>& pComponents = pCollisions[nCntObj]->GetAttachObject()->GetComponents();		// �ΏۃI�u�W�F�N�g�ɃA�^�b�`����Ă���R���|�[�l���g�̎擾
			std::vector<GameObject*>& pOverlappingVector = pCollisions[nCntObj]->GetOverlappingGameObjects();		// �O��܂łɓ����Ă����I�u�W�F�N�g�ꗗ���擾����

			// �d�Ȃ��Ă���I�u�W�F�N�g�̐����擾����
			int nNumOverlapping = pObj->getNumOverlappingObjects();

			// Exit�C�x���g�p����
			try {
				for (unsigned int i = 0; i < pOverlappingVector.size(); i++)
				{
					bool bCurrentExist = false;	// �����݂��邩
					for (int n = 0; n < nNumOverlapping; n++)
					{
						GameObject* pCurrentGameObj = CCollision::GetGameObjectFromCollisionObj(pObj->getOverlappingObject(n));		// ���݂̃Q�[���I�u�W�F�N�g
						if (pOverlappingVector[i] == pCurrentGameObj)
						{	// ��������݂���Ƃ�
							bCurrentExist = true;
							break;
						}

						// �I�u�W�F�N�g���̍X�V
						nNumOverlapping = pObj->getNumOverlappingObjects();
					}

					if (!bCurrentExist)
					{ // �O��͂����āA����͑��݂��Ȃ��Ƃ�
						for (unsigned int nCntComp = 0; nCntComp < pComponents.size(); nCntComp++)
						{
							pComponents[nCntComp]->OnTriggerExit(pOverlappingVector[i]);	// �d�Ȃ��Ă���Ƃ��̃C�x���g

							// �C�x���g���Ŕj�����ꂽ�Ƃ�
							if (pComponents.size() <= 0)
							{
								return;	// �������I������
							}
						}
					}
				}
			}
			catch (char a) 
			{
				std::cout << a << "Exit Event Error" << std::endl;
			}

			try {
				// �d�Ȃ��Ă���I�u�W�F�N�g���A�J��Ԃ�
				for (int i = 0; i < nNumOverlapping; i++)
				{
					btCollisionObject* pCurrentOverlappingObj = pObj->getOverlappingObject(i);													// ���݁A�d�Ȃ��Ă���I�u�W�F�N�g
					GameObject* pCurrentOverlappingGameObj = CCollision::GetGameObjectFromCollisionObj(pCurrentOverlappingObj);	// ���݁A�d�Ȃ��Ă���I�u�W�F�N�g�̃Q�[���I�u�W�F�N�g�̎擾

					if (pCurrentOverlappingGameObj != nullptr)
					{
						// ���o�C�x���g
						bool bBeforeExist = false;	// �O������݂��Ă�����
						for (unsigned int nCntOverlapping = 0; nCntOverlapping < pOverlappingVector.size(); nCntOverlapping++)
						{
							if (pOverlappingVector[nCntOverlapping] == pCurrentOverlappingGameObj)
							{ // �O������݂��Ă���Ƃ�
								bBeforeExist = true;
								break;
							}
						}

						if (!bBeforeExist)
						{ // �O�񑶍݂��Ă��Ȃ��Ƃ�
							// OnEnter
							for (unsigned int nCntComp = 0; nCntComp < pComponents.size(); nCntComp++)
							{
								pComponents[nCntComp]->OnTriggerEnter(pCurrentOverlappingGameObj);	// �o���Ƃ��̃C�x���g
							}
						}


						for (unsigned int nCntComp = 0; nCntComp < pComponents.size(); nCntComp++)
						{
							pComponents[nCntComp]->OnTriggerStay(pCurrentOverlappingGameObj);	// �d�Ȃ��Ă���Ƃ��̃C�x���g
						}
					}

					// �I�u�W�F�N�g���̍X�V
					nNumOverlapping = pObj->getNumOverlappingObjects();
				}
			}
			catch (char a) 
			{
				std::cout << a << "Stay and Enter Events Error" << std::endl;
			}

			try {
				// �R���W�����ɓ����Ă���I�u�W�F�N�g���X�V����
				nNumOverlapping = pObj->getNumOverlappingObjects();
				if (!pOverlappingVector.empty())
				{
					pOverlappingVector.clear();
				}
				for (int i = 0; i < nNumOverlapping; i++)
				{
					btCollisionObject* pOverlappingObj = pObj->getOverlappingObject(i);													// �d�Ȃ��Ă���I�u�W�F�N�g
					GameObject* pOverlappingGameObj = CCollision::GetGameObjectFromCollisionObj(pOverlappingObj);	// �d�Ȃ��Ă���I�u�W�F�N�g�̃Q�[���I�u�W�F�N�g�̎擾

					if (pOverlappingGameObj != nullptr)
					{ // nullptr�`�F�b�N
						pOverlappingVector.push_back(pOverlappingGameObj);	// �Q�[���I�u�W�F�N�g��ǉ�
					}

					// �I�u�W�F�N�g���̍X�V
					nNumOverlapping = pObj->getNumOverlappingObjects();
				}
			}
			catch (char a) 
			{
				std::cout << a << "Update Overlapping Objects Error" << std::endl;
			}
		}
	}
}