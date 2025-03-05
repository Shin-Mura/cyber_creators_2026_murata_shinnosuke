//********************************************************************************************************
//
//���C������[main.h]
// Author Murata Shinnosuke
//
//********************************************************************************************************
#ifndef _MAIN_H_
#define _MAIN_H_

#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <iostream>
#define DIRECTINPUT_VERSION (0x0800)
#include "d3dx9.h"
#include "dinput.h"
#include "xaudio2.h"
#include "Xinput.h"

//���C�u�����̃����N
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "xinput.lib")  

//�}�N����`
#define SCREEN_WIDTH (1280) //�E�C���h�E�̕�
#define SCREEN_HEIGHT (720) //�E�C���h�E�̍���
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define SECONDS_FLAME (60)   //�P�b�Ԃ̃t���[��
#define CLASS_NAME "WindowClass"    //�E�B���h�E�N���X�̖��O
#define WINDOW_NAME "�s�N�~�����C�N�̃Q�[��" //�E�C���h�E�̖��O
#define MAX_STRING (128)

//�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;   //���_���W
	float rhw;   //���W�ϊ��p�W��
	D3DCOLOR col;   //���_�J���[
	D3DXVECTOR2 tex;   //�e�N�X�`�����W
}VERTEX_2D;   //���_���[2D]

//���_���[3D]�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos; //���_���W
	D3DXVECTOR3 nor;   //�@���x�N�g��
	D3DCOLOR col;	 //���_�J���[
	D3DXVECTOR2 tex; //�e�N�X�`�����W
} VERTEX_3D;

#endif // !_MAIN_H_
