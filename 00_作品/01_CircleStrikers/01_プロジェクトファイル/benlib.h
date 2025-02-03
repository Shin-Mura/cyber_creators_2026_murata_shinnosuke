//========================================================================================================
//
//便利関数処理[benlib.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _BENLIB_H_
#define _BENLIB_H_

#include "main.h"

//プロトタイプ宣言
float DistanceToPos(D3DXVECTOR3 pos, D3DXVECTOR3 posTarget);   //対象との距離の算出処理
float DirectionToPos(D3DXVECTOR3 pos, D3DXVECTOR3 posTarget);   //対象の方向の算出処理
int CreateRand(int nMax, int nMin);   //乱数の生成処理

#endif // !_BENLIB_H_
