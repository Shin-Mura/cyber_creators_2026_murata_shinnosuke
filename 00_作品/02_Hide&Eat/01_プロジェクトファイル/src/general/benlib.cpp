//==================================================================
//
// �֗��֐����C�u���� [benlib.cpp]
// by Kotaro Ito
//
//==================================================================
#include "benlib.h"
#include <random>

float Benlib::PosDistance(const D3DXVECTOR3& pos1, const D3DXVECTOR3& pos2)
{
	float xz = fabsf(pos1.x - pos2.x) * fabsf(pos1.x - pos2.x) + fabsf(pos1.z - pos2.z) * fabsf(pos1.z - pos2.z);
	xz = sqrtf(xz);
	float y = xz * xz + fabsf(pos1.y - pos2.y) * fabsf(pos1.y - pos2.y);
	float result = sqrtf(y);
	return result;
}

float Benlib::PosPlaneDistance(const D3DXVECTOR3& pos1, const D3DXVECTOR3& pos2)
{
	float xz = fabsf(pos1.x - pos2.x) * fabsf(pos1.x - pos2.x) + fabsf(pos1.z - pos2.z) * fabsf(pos1.z - pos2.z);
	xz = sqrtf(xz);
	return xz;
}

D3DXVECTOR3 Benlib::VectorDistance(const D3DXVECTOR3& start, D3DXVECTOR3 vec, const float& fLength)
{
	D3DXVECTOR3 resultPos;
	D3DXVec3Normalize(&vec, &vec);
	resultPos.x = start.x + (fLength * vec.x) / (float)sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	resultPos.y = start.y + (fLength * vec.y) / (float)sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	resultPos.z = start.z + (fLength * vec.z) / (float)sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	return resultPos;
}

float Benlib::PosAngle(const D3DXVECTOR3& pos1, const D3DXVECTOR3& pos2)
{
	return atan2f(pos2.x - pos1.x, pos2.z - pos1.z);
}

D3DXVECTOR3 Benlib::PosRotation(const D3DXVECTOR3& pos1, const D3DXVECTOR3& pos2)
{
	float fTargetAngle = atan2f(pos2.x - pos1.x, pos2.z - pos1.z);
	float fTargetHeightAngle = atan2f(sqrtf(fabsf(pos2.x - pos1.x) * fabsf(pos2.x - pos1.x) +
		fabsf(pos2.z - pos1.z) * fabsf(pos2.z - pos1.z)), (pos2.y - pos1.y));
	return D3DXVECTOR3(sinf(fTargetAngle), cosf(fTargetHeightAngle), cosf(fTargetAngle));
}

D3DXVECTOR3 Benlib::CalcNormalVector(const D3DXVECTOR3& pos1, const D3DXVECTOR3& pos2, const D3DXVECTOR3& pos3)
{
	D3DXVECTOR3 v1, v2, v3;
	v1 = pos2 - pos1;
	v2 = pos3 - pos1;
	D3DXVec3Cross(&v3, &v1, &v2);
	D3DXVec3Normalize(&v3, &v3);
	return v3;
}

D3DXQUATERNION Benlib::LookAt(const D3DXVECTOR3& pos1, const D3DXVECTOR3& pos2)
{
	D3DXVECTOR3 target = pos2 - pos1;
	D3DXVec3Normalize(&target, &target);
	D3DXVECTOR3 norm = { 0, 0, 1 };
	float dot = D3DXVec3Dot(&norm, &target);
	float theta = acosf(dot);
	D3DXVECTOR3 cross;
	D3DXVec3Cross(&cross, &norm, &target);
	D3DXQUATERNION q;
	D3DXVec3Normalize(&cross, &cross);
	theta = theta / (float)2;
	q.x = cross.x * sinf(theta);
	q.y = cross.y * sinf(theta);
	q.z = cross.z * sinf(theta);
	q.w = cosf(theta);
	return q;
}

int Benlib::RandomInt(const int& min, const int& max)
{
	return rand() % (abs(max - min) + 1) + min;
}

float Benlib::RandomFloat(const float& min, const float& max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dist(min, max);
	return dist(gen);
}

float Benlib::DegreeToRadian(const int& nDegree)
{
	return nDegree * D3DX_PI / (float)180.0f;
}

int Benlib::RadianToDegree(const float& fRadian)
{
	return static_cast<int>(fRadian * 180.0f / D3DX_PI);
}

D3DXVECTOR3 Benlib::QuaternionToEuler(D3DXQUATERNION q)
{
	auto sx = -(2 * q.y * q.z - 2 * q.x * q.w);
	auto unlocked = std::abs(sx) < 0.99999f;
	return D3DXVECTOR3(
		std::asin(sx),
		unlocked ? std::atan2(2 * q.x * q.z + 2 * q.y * q.w, 2 * q.w * q.w + 2 * q.z * q.z - 1)
		: std::atan2(-(2 * q.x * q.z - 2 * q.y * q.w), 2 * q.w * q.w + 2 * q.x * q.x - 1),
		unlocked ? std::atan2(2 * q.x * q.y + 2 * q.z * q.w, 2 * q.w * q.w + 2 * q.y * q.y - 1) : 0
	);
}

void Benlib::BackFileChar(FILE* pFile, const int& nBackCount)
{
	fpos_t filePos;
	fgetpos(pFile, &filePos);
	filePos -= nBackCount;
	fsetpos(pFile, &filePos);
}

void Benlib::RemovePathSplit(char* FilePath, const int& nSplit)
{
	int nLength = static_cast<int>(strlen(&FilePath[0]));
	int nPathSplit = 0;												 // �p�X�̋�؂�J�E���g
	int nLimitPathDel = nSplit;										 // �p�X�폜�̃��~�b�g

	for (int nCntLength = 0; nCntLength < nLength; nCntLength++)
	{ // ��������J��Ԃ�
		if (FilePath[nLength - nCntLength - 1] == '\\')
		{ // ��؂蕶���̎�
			nPathSplit++;
		}

		FilePath[nLength - nCntLength - 1] = '\0';	//����������

		// ��������ɒB�����Ƃ�
		if (nPathSplit >= nLimitPathDel)
		{
			break;
		}
	}
}

void Benlib::RemovePathSplit(std::string& FilePath, const int& nSplit)
{
	int nLength = (int)FilePath.length();
	int nPathSplit = 0;												 // �p�X�̋�؂�J�E���g
	int nLimitPathDel = nSplit;										 // �p�X�폜�̃��~�b�g

	for (int nCntLength = 0; nCntLength < nLength; nCntLength++)
	{ // ��������J��Ԃ�
		if (FilePath[nLength - nCntLength - 1] == '\\')
		{ // ��؂蕶���̎�
			nPathSplit++;
		}

		FilePath.erase(nLength - nCntLength - 1);	//����������

		// ��������ɒB�����Ƃ�
		if (nPathSplit >= nLimitPathDel)
		{
			break;
		}
	}
}

void Benlib::ReplacePathSplit(char* FilePath, const char& cSplit)
{
	for (int nCntLength = 0; nCntLength < (int)strlen(&FilePath[0]); nCntLength++)
	{ // ��������J��Ԃ�

		if (FilePath[nCntLength] == '\\')
		{
			FilePath[nCntLength] = cSplit;
		}
	}
}