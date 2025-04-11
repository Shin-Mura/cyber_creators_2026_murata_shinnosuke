//=============================================================
//
// �g�����X�t�H�[�� [transform.cpp]
// Author: Ito Kotaro
//
//=============================================================
#include "transform.h"
#include "internal/physics.h"

//=============================================================
// [Transform] �ʒu�̐ݒ�
//=============================================================
void Transform::SetPos(float x, float y, float z)
{
	m_position = { x, y, z };
}

//=============================================================
// [Transform] ��]�̐ݒ�
//=============================================================
void Transform::SetRot(float x, float y, float z)
{
	D3DXQUATERNION q;
	D3DXQuaternionRotationYawPitchRoll(&q, y, x, z);
	m_rotation = q;
}

//=============================================================
// [Transform] �e��ݒ肷��
//=============================================================
void Transform::SetParent(Transform* pParent)
{
	// nullptr���ݒ肳�ꂽ�Ƃ�
	if (pParent == nullptr)
	{
		m_pParent = nullptr;
		return;
	}

	// �����Ɏ����̃|�C���^�������ꂽ�Ƃ�
	if (pParent == this)
		return;

	// �w�肵���g�����X�t�H�[���̐e�������ȊO�̎��̂݁A�ݒ肷��
	if (pParent->GetParent() != this)
		m_pParent = pParent;
}

//=============================================================
// [Transform] ��]�̎擾
//=============================================================
D3DXVECTOR3 Transform::GetRot()
{
	auto sx = -(2 * m_rotation.y * m_rotation.z - 2 * m_rotation.x * m_rotation.w);
	auto unlocked = std::abs(sx) < 0.99999f;
	return D3DXVECTOR3(
		std::asin(sx),
		unlocked ? std::atan2(2 * m_rotation.x * m_rotation.z + 2 * m_rotation.y * m_rotation.w, 2 * m_rotation.w * m_rotation.w + 2 * m_rotation.z * m_rotation.z - 1)
		: std::atan2(-(2 * m_rotation.x * m_rotation.z - 2 * m_rotation.y * m_rotation.w), 2 * m_rotation.w * m_rotation.w + 2 * m_rotation.x * m_rotation.x - 1),
		unlocked ? std::atan2(2 * m_rotation.x * m_rotation.y + 2 * m_rotation.z * m_rotation.w, 2 * m_rotation.w * m_rotation.w + 2 * m_rotation.y * m_rotation.y - 1) : 0
	);
}

//=============================================================
// [Transform] ���[���h���W�ł̈ʒu���擾
//=============================================================
D3DXVECTOR3 Transform::GetWPos()
{
	D3DXMATRIX mtx = GetMatrix();
	D3DXVECTOR3 pos = { mtx._41, mtx._42, mtx._43 };
	return pos;
}

//=============================================================
// [Transform] ���[���h���W�ł̃N�H�[�^�j�I�����擾
//=============================================================
D3DXQUATERNION Transform::GetWQuaternion()
{
	D3DXQUATERNION worldQuaternion;
	D3DXQuaternionIdentity(&worldQuaternion);

	Transform* worldTransform = this;
	do
	{
		D3DXQUATERNION q = worldTransform->GetQuaternion();
		D3DXQuaternionMultiply(&worldQuaternion, &worldQuaternion, &q);

		// ���̐e�ɐi��
		worldTransform = worldTransform->GetParent();

	} while (worldTransform != nullptr);

	// ���K��
	D3DXQuaternionNormalize(&worldQuaternion, &worldQuaternion);

	return worldQuaternion;
}

//=============================================================
// [Transform] ���[���h���W�ł̃I�C���[�p���擾
//=============================================================
D3DXVECTOR3 Transform::GetWRot()
{
	// �e�̃��[���h���W�����[�J�����W�ɑ���
	//D3DXVECTOR3 worldRot = { 0.0f, 0.0f, 0.0f };
	//Transform* worldTransform = this;
	//do
	//{
	//	// ���W�𑫂�
	//	worldRot += worldTransform->GetRot();

	//	// ���̐e�ɐi��
	//	worldTransform = worldTransform->GetParent();

	//} while (worldTransform != nullptr);


	// ���K��
	//worldRot = NormalizeRotation(worldRot);

	D3DXQUATERNION q = this->GetWQuaternion();

	auto sx = -(2 * q.y * q.z - 2 * q.x * q.w);
	auto unlocked = std::abs(sx) < 0.99999f;
	return D3DXVECTOR3(
		std::asin(sx),
		unlocked ? std::atan2(2 * q.x * q.z + 2 * q.y * q.w, 2 * q.w * q.w + 2 * q.z * q.z - 1)
		: std::atan2(-(2 * q.x * q.z - 2 * q.y * q.w), 2 * q.w * q.w + 2 * q.x * q.x - 1),
		unlocked ? std::atan2(2 * q.x * q.y + 2 * q.z * q.w, 2 * q.w * q.w + 2 * q.y * q.y - 1) : 0
	);
}

//=============================================================
// [Transform] ���[���h���W�ł̃X�P�[�����擾
//=============================================================
D3DXVECTOR3 Transform::GetWScale()
{
	// �e�̃��[���h���W�����[�J�����W�Ɋ|����
	D3DXVECTOR3 worldScale = { 1.0f, 1.0f, 1.0f };
	Transform* worldTransform = this;
	do
	{
		// ���W���|����
		worldScale.x *= worldTransform->GetScale().x;
		worldScale.y *= worldTransform->GetScale().y;
		worldScale.z *= worldTransform->GetScale().z;

		// ���̐e�ɐi��
		worldTransform = worldTransform->GetParent();

	} while (worldTransform != nullptr);

	return worldScale;
}

//=============================================================
// [Transform] �}�g���b�N�X���擾����
//=============================================================
D3DXMATRIX& Transform::GetMatrix()
{
	// �ϐ�
	D3DXMATRIX mtxScale, mtxRot, mtxTrans;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtx);

	// �X�P�[���𔽉f
	D3DXVECTOR3 scale = GetScale();
	D3DXMatrixScaling(&mtxScale, scale.x, scale.y, scale.z);
	D3DXMatrixMultiply(&m_mtx, &m_mtx, &mtxScale);

	// �����𔽉f
	D3DXVECTOR3 rotation = GetRot();
	D3DXMatrixRotationQuaternion(&mtxRot, &m_rotation);
	D3DXMatrixMultiply(&m_mtx, &m_mtx, &mtxRot);
	//31 32 33�őO���������擾�ł���

	// �ʒu�𔽉f
	D3DXVECTOR3 position = GetPos();
	D3DXMatrixTranslation(&mtxTrans, position.x, position.y, position.z);
	D3DXMatrixMultiply(&m_mtx, &m_mtx, &mtxTrans);

	if (GetParent() != nullptr)
	{
		D3DXMATRIX mtxParent;
		mtxParent = GetParent()->GetMatrix();
		D3DXMatrixMultiply(&m_mtx, &m_mtx, &mtxParent);
	}

	return m_mtx;
}

//=============================================================
// [Transform] ���Z�q ==
//=============================================================
bool Transform::operator ==(Transform& transform)
{
	if (GetWPos() == transform.GetWPos() &&
		GetWQuaternion() == transform.GetWQuaternion() &&
		GetWScale() == transform.GetWScale() &&
		m_pParent == transform.m_pParent)
	{
		return true;
	}
	return false;
}

//=============================================================
// [Transform] �w��ʒu�̕���������
//=============================================================
void Transform::LookAt(D3DXVECTOR3 target)
{
	m_rotation = Benlib::LookAt(GetWPos(), target);

	//// ���݂̈ʒu���擾����
	//D3DXVECTOR3 pos = GetWPos();

	//// �����ׂ��������Z�o����
	//D3DXVECTOR3 rot;
	//float fTargetAngle = -atan2f(target.x - pos.x, target.z - pos.z);
	//float fTargetHeightAngle = atan2f(sqrtf(fabsf(target.x - pos.x) * fabsf(target.x - pos.x) +
	//fabsf(target.z - pos.z) * fabsf(target.z - pos.z)), (target.y - pos.y));

	//// ��������
	//rot = D3DXVECTOR3(-fTargetHeightAngle + D3DX_PI * 0.5f, fTargetAngle, 0.0f);
	//SetRot(rot);



	//D3DXVECTOR3 direction = target - this->GetWPos();

	//D3DXVECTOR3 upVector(0.0f, 1.0f, 0.0f);
	//D3DXVECTOR3 axis;
	//D3DXVec3Cross(&axis, &upVector, &direction);
	//D3DXVec3Normalize(&axis, &axis);

	//float angle = acos(D3DXVec3Dot(&upVector, &axis));

	//D3DXQuaternionRotationAxis(&m_rotation, &axis, angle);
}

//=============================================================
// [Transform] ��]�̐��K��
//=============================================================
D3DXVECTOR3 Transform::NormalizeRotation(const D3DXVECTOR3& rot)
{
	D3DXVECTOR3 normalized = rot;
	if (normalized.x > D3DX_PI)
	{
		normalized.x -= D3DX_PI * 2;
	}
	if (normalized.y > D3DX_PI)
	{
		normalized.y -= D3DX_PI * 2;
	}
	if (normalized.z > D3DX_PI)
	{
		normalized.z -= D3DX_PI * 2;
	}

	if (normalized.x < -D3DX_PI)
	{
		normalized.x += D3DX_PI * 2;
	}
	if (normalized.y < -D3DX_PI)
	{
		normalized.y += D3DX_PI * 2;
	}
	if (normalized.z < -D3DX_PI)
	{
		normalized.z += D3DX_PI * 2;
	}
	return normalized;
}