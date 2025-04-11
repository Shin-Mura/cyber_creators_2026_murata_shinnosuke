//=============================================================
//
// 3D���� [physics.h]
// Author: Ito Kotaro
//
//=============================================================
#ifndef _PHYSICS_3D_H_
#define _PHYSICS_3D_H_

#include "general/main.h"
#include "gameobject.h"
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"

class CLine;

// �����f�o�b�O�̕`��
class CPhysicsDebugDraw : public btIDebugDraw
{
public:
	CPhysicsDebugDraw();
	void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);
	void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) {}
	void draw3dText(const btVector3& location, const char* textString) {}
	void reportErrorWarning(const char* warningString) {}
	void clearLines();
	void setDebugMode(int debugMode) { m_debugMode = debugMode; }
	int getDebugMode() const { return m_debugMode; }
private:
	int m_debugMode;
	GameObject* m_pLineObject;
	std::vector<CLine*> m_pLines;
};

// �A�N�V�����C���^�[�t�F�C�X
class CActionInterface : public btActionInterface
{
public:
	void updateAction(btCollisionWorld* collisionWorld, btScalar deltaTimeStep) override;
	void debugDraw(btIDebugDraw* debugDrawer) {}
};

// �����N���X�̒�`
class CPhysics
{
public:
	CPhysics();
	~CPhysics();
	void Init();				// ������
	void Uninit();			// �I��
	void Update();		// �X�V
	void SetUpdatePhysics(const bool& enabled) { m_isUpdatePhysics = enabled; }

	static CPhysics* GetInstance() {
		static CPhysics physics;
		return &physics;
	}

	static btDiscreteDynamicsWorld& GetDynamicsWorld() { return *m_dynamicsWorld; }							// �������[���h�̎擾
	static btAlignedObjectArray<btCollisionShape*>& GetCollisionShape() { return m_collisionShapes; }		// �`�󃊃X�g�̎擾
	static CPhysicsDebugDraw* GetPhysicsDebugDraw() { return m_debugDraw; }
private:
	static btDiscreteDynamicsWorld* m_dynamicsWorld;								// �������[���h
	static btAlignedObjectArray<btCollisionShape*> m_collisionShapes;		// �`�󃊃X�g
	static CPhysicsDebugDraw* m_debugDraw;
	bool m_isUpdatePhysics;

	// �ݒ�
	btDefaultCollisionConfiguration* m_collisionConfiguration;
	btCollisionDispatcher* m_dispatcher;
	btBroadphaseInterface* m_overlappingPairCache;
	btSequentialImpulseConstraintSolver* m_solver;
	btGhostPairCallback* m_ghostPairCollback;
	CActionInterface* m_actionInterface;
};


// �R���W�����N���X�i�R���W�������K�v�ȃQ�[���I�u�W�F�N�g���A�^�b�`��ɐݒ肷��j
class CCollision
{
public:
	CCollision(GameObject* gameObject);				// �R���X�g���N�^
	virtual ~CCollision();										// �f�X�g���N�^
	void Init();														// ����������
	void Uninit();													// �I������
	void UpdateCollision();									// �R���W�������X�V����
	void SaveTransform();									// �g�����X�t�H�[���l��ۑ�����

	const D3DXVECTOR3& GetBeforePos() { return m_beforePos; }					// �O��̈ʒu�̎擾
	const D3DXQUATERNION& GetBeforeRot() { return m_beforeRot; }			// �O��̉�]�̎擾

	GameObject* GetAttachObject() { return m_pAttachObject; }					// �A�^�b�`����Ă���Q�[���I�u�W�F�N�g�̎擾
	btGhostObject* GetGhostObject() { return m_pGhostObject; }					// �S�[�X�g�I�u�W�F�N�g�̎擾
	btRigidBody* GetRigidBody() { return m_pRigidBody; }							// ���W�b�h�{�f�B�̎擾
	void IsTrigger(const bool& isTrigger);														// �g���K�[��Ԃ̐ݒ�
	bool GetIsTrigger() { return m_bTrigger; }												// �g���K�[��Ԃ̎擾
	void IsKinematic(const bool& isKinematic);												// �L�l�}�e�B�N�̐ݒ�
	bool GetIsKinematic() { return m_bKinematic; }										// �L�l�}�e�B�N�̎擾
	void SetMass(const float& fMass);															// ���ʂ̐ݒ�
	float GetMass() { return m_fMass; }														// ���ʂ̎擾
	void SetFriction(const float& fFriction);														// ���C�̐ݒ�
	float GetFriction() { return m_fFriction; }													// ���C�̎擾
	std::vector<GameObject*>& GetOverlappingGameObjects() {					// �d�Ȃ��Ă���I�u�W�F�N�g�ꗗ�̎擾
		return m_overlappingObjects; 
	}
	btCompoundShape* GetCompoundShape() { return m_compShape; }

	float GetWalkSpeed();																				// ���s���x�̎擾�iX��Z�̈ړ����x�j
	void SetFilter(const int& nGroup, const int& nMask = -1);							// �t�B���^�[�̐ݒ�
	void UseFilter(const bool& bUse);															// �t�B���^�[��L���ɂ��邩

	static void Create(GameObject* gameObject);											// ����
	static bool isCollisionExist(GameObject* gameObject);								// �Q�[���I�u�W�F�N�g�ɃR���W���������邩
	static GameObject* GetGameObjectFromCollisionObj(const btCollisionObject* collision);		// �R���W�����I�u�W�F�N�g����Q�[���I�u�W�F�N�g���擾����
	static CCollision* GetCollision(GameObject* gameObject);							// �R���W�����̎擾
	static void RemoveCollision(GameObject* gameObject);							// �R���W�����̍폜
	static std::vector<CCollision*>& GetCollisions() { return m_collisions; }		// ���ׂẴR���W�������擾
private:
	void UpdateShapes();												// �`��̍X�V

	GameObject* const m_pAttachObject;						// �A�^�b�`����Q�[���I�u�W�F�N�g
	btGhostObject* m_pGhostObject;							// �S�[�X�g�I�u�W�F�N�g�i�����蔻��j
	btRigidBody* m_pRigidBody;									// ���W�b�h�{�f�B
	btCompoundShape* m_compShape;						// �`��
	float m_fMass;														// ����
	float m_fFriction;													// ���C
	bool m_bTrigger;													// �g���K�[
	bool m_bKinematic;												// �L�l�}�e�B�b�N
	int m_nGroup;														// �O���[�v
	int m_nMask;															// �}�X�N
	bool m_bUseFilter;													// �t�B���^�[���g�p���邩
	std::vector<GameObject*> m_overlappingObjects;	// �d�Ȃ��Ă���I�u�W�F�N�g
	static std::vector<CCollision*> m_collisions;			// �R���W�����̕ۑ�
	

	// �O��̒l
	D3DXVECTOR3 m_beforePos;			// �ʒu
	D3DXQUATERNION m_beforeRot;	// ��]
};

#endif // !_PHYSICS_3D_H_
