//========================================================================================================
//
//�֗��֐�����[benlib.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "benlib.h"

//========================================================================================================
//�ΏۂƂ̋����̎Z�o����
//========================================================================================================
D3DXVECTOR3 Benlib::Distance(D3DXVECTOR3 pos, D3DXVECTOR3 posTarget)
{
	//�������v�Z����
	float fDistanceYZ = (posTarget.y - pos.y) * (posTarget.y - pos.y) + (posTarget.z - pos.z) * (posTarget.z - pos.z);
	fDistanceYZ = (float)sqrt(fDistanceYZ);   //������

	//�������v�Z����
	float fDistanceXY = (posTarget.x - pos.x) * (posTarget.x - pos.x) + (posTarget.y - pos.y) * (posTarget.y - pos.y);
	fDistanceXY = (float)sqrt(fDistanceXY);   //������

	//�������v�Z����
	float fDistanceXZ = (posTarget.x - pos.x) * (posTarget.x - pos.x) + (posTarget.z - pos.z) * (posTarget.z - pos.z);
	fDistanceXZ = (float)sqrt(fDistanceXZ);   //������

	//������Ԃ�
	return {fDistanceYZ, fDistanceXZ, fDistanceXY };
}

//========================================================================================================
//�Ώۂ̕����̎Z�o����
//========================================================================================================
D3DXVECTOR3 Benlib::Direction(D3DXVECTOR3 pos, D3DXVECTOR3 posTarget)
{
	//�x�N�g�����v�Z����
	D3DXVECTOR3 vec = posTarget - pos;

	//�������v�Z����
	float fDirectionYZ = atan2f(vec.y, vec.z);
	float fDirectionXY = atan2f(vec.x, vec.y);
	float fDirectionXZ = atan2f(vec.x, vec.z);

	//������Ԃ�
	return{fDirectionYZ, fDirectionXZ, fDirectionXY };
}

//========================================================================================================
//�����̐�������
//========================================================================================================
int Benlib::CreateRand(int nMax, int nMin)
{
	//�Œ�l���Βl�ɂ���
	int nMinAbs = abs(nMin);

	//�����𐶐�����
	int nRand = rand() % (nMax + nMinAbs);
	nRand -= nMinAbs;

	//�����𐶐�����
	return nRand;
}