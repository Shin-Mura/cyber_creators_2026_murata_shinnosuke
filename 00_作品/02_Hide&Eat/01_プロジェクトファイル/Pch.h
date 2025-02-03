//=============================================================
//
// �v���R���p�C���ς݃w�b�_�[ [Pch.h]
// Author: Ito Kotaro
//
//=============================================================
#ifndef _PCH_H_
#define _PCH_H_

// ��`
#define DIRECTINPUT_VERSION	(0x0800)	// �r���h���̌x���Ώ��p�}�N��

// �C���N���[�h
#include <Windows.h>
#include "d3dx9.h"										// �`�揈���ɕK�v
#include "d3d9.h"
#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <algorithm>
#include <Shlwapi.h>
#include "dinput.h"
#include "Xinput.h"
#include "input_system.h"
#include "gameobject.h"
#include "benlib.h"
class CInputSystem;
#define INPUT_INSTANCE	(CInputSystem::GetInstance())

// Eigen	���C�u����
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <Eigen/Dense>

// OpenAL Soft ���C�u����
#include "AL/al.h"
#include "AL/alc.h"
#include "AL/alext.h"
#pragma comment(lib, "OpenAL32.lib")
#pragma comment(lib, "ex-common.lib")

// Json ���C�u����
#include "libs/json/json.hpp"
using json = nlohmann::json;

// ���C�u�����̃����N
#pragma comment(lib, "d3d9.lib")		// �`�揈���ɕK�v
#pragma comment(lib, "d3dx9.lib")		// �g�����C�u����
#pragma comment(lib, "dxguid.lib")	// DirectX�R���|�[�l���g
#pragma comment(lib, "winmm.lib")	// �V�X�e�������擾�ɕK�v
#pragma comment(lib, "dinput8.lib")	// ���͏����ɕK�v
#pragma comment(lib, "xinput.lib")		// �W���C�p�b�h�����ɕK�v
#pragma comment(lib, "Shlwapi.lib")	// �t�@�C���̑��݊m�F

#endif // !_PCH_H_