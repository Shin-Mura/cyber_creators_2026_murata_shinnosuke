//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�ꗗ
//*****************************************************************************
typedef enum
{
	//SOUND_LABEL_TEST = 0,				//�e�X�gBGM
	SOUND_LABEL_SELECT_MOVE = 0,		//�I���ړ�
	SOUND_LABEL_SELECT_DECIDE,		//�I������
	SOUND_LABEL_DAMAGE,					//�_���[�W
	SOUND_LABEL_BLOCK_BREAK,			//�u���b�N�j��
	SOUND_LABEL_STICK_HIT,				//�X�e�B�b�N�q�b�g��
	SOUND_LABEL_RESULT,						//���U���gBGM
	SOUND_LABEL_TITLE,						//�^�C�g��BGM
	SOUND_LABEL_GAME,						//�Q�[��BGM
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
