//========================================================================================================
//
//�֗��֐�����[benlib.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _BENLIB_H_
#define _BENLIB_H_

#include "main.h"

//�֗��֐�
class Benlib
{
public:
	static D3DXVECTOR3 Distance(D3DXVECTOR3 pos, D3DXVECTOR3 posTarget);   //�ΏۂƂ̋����̎Z�o����
	static D3DXVECTOR3 Direction(D3DXVECTOR3 pos, D3DXVECTOR3 posTarget);   //�Ώۂ̕����̎Z�o����
	static int CreateRand(int nMax, int nMin);   //�����̐�������
};

#endif // !_BENLIB_H_
