//========================================================================================================
//
//�֗��֐�����[benlib.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _BENLIB_H_
#define _BENLIB_H_

#include "main.h"

//�v���g�^�C�v�錾
float DistanceToPos(D3DXVECTOR3 pos, D3DXVECTOR3 posTarget);   //�ΏۂƂ̋����̎Z�o����
float DirectionToPos(D3DXVECTOR3 pos, D3DXVECTOR3 posTarget);   //�Ώۂ̕����̎Z�o����
int CreateRand(int nMax, int nMin);   //�����̐�������

#endif // !_BENLIB_H_
