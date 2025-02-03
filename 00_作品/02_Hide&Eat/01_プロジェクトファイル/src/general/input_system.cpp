//=============================================================
//
// ���̓V�X�e�� [input_system.cpp]
// Author: Ito Kotaro
//
//=============================================================
#include "input_system.h"
#include "internal/KeyAssignmentTable.h"
#include "manager.h"
#include <fstream>
using namespace std;

// �ÓI�����o������
vector<CInputDevice*> CInputDevice::m_apInputDevice = {};
const int CKeyboardDevice::MAX_KEYBOARD_KEY;

//=============================================================
// [CInputSystem] �R���X�g���N�^
//=============================================================
CInputSystem::CInputSystem()
{
	m_pInput = nullptr;
}

//=============================================================
// [CInputSystem] ������
//=============================================================
HRESULT CInputSystem::Init(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInput�I�u�W�F�N�g�̐���
	if (m_pInput == nullptr)
	{
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, nullptr)))
		{
			return E_FAIL;
		}
	}

	// �t�@�C���ǂݍ���
	LoadFile();

	//------------------------------------------------------------------------------------------------------------------------------------------
	// ���̓f�o�C�X�̐���

	// �L�[�{�[�h
	CKeyboardDevice* pKeyboardDevice = new CKeyboardDevice();
	pKeyboardDevice->Init(hInstance, hWnd);

	// �Q�[���p�b�h
	CGamepadDevice* pGamepadDevice = new CGamepadDevice();
	pGamepadDevice->Init(hInstance, hWnd);

	// �}�E�X
	CMouseDevice* pMouseDevice = new CMouseDevice();
	pMouseDevice->Init(hInstance, hWnd);

	return S_OK;
}

//=============================================================
// [CInputSystem] �I��
//=============================================================
void CInputSystem::Uninit()
{
	// ���ׂĂ̓��̓f�o�C�X���I������
	vector<CInputDevice*>& pInputDevice = CInputDevice::GetInputDevice();
	int nNumDevice = static_cast<int>(pInputDevice.size());
	for (int i = 0; i < nNumDevice; i++)
	{
		if (pInputDevice[0] != nullptr)
		{
			pInputDevice[0]->Uninit();
			delete pInputDevice[0];
		}
	}

	// DirectInput�I�u�W�F�N�g�̔j��
	if (m_pInput != nullptr)
	{
		m_pInput->Release();
		m_pInput = nullptr;
	}
}

//=============================================================
// [CInputSystem] �X�V
//=============================================================
void CInputSystem::Update()
{
	// ���ׂĂ̓��̓f�o�C�X���X�V����
	vector<CInputDevice*>& pInputDevice = CInputDevice::GetInputDevice();
	for (unsigned int i = 0; i < pInputDevice.size(); i++)
	{
		if (pInputDevice[i] != nullptr)
		{
			pInputDevice[i]->Update();
		}
	}
}

//=============================================================
// [CInputSystem] ���͔���
//=============================================================
bool CInputSystem::onInput(const std::string& sKeyName)
{
	for (unsigned int i = 0; i < m_keyData.size(); i++)
	{
		if (m_keyData[i].sKeyName == sKeyName)
		{ // �L�[�������v����Ƃ�

			switch (m_keyData[i].inputType)
			{
			case INPUT_TYPE::PRESS:
				for (unsigned int nCntKey = 0; nCntKey < m_keyData[i].key.size(); nCntKey++)
				{
					if (onPress(m_keyData[i].key[nCntKey]))
					{
						return true;
					}
				}
				return false;
			case INPUT_TYPE::TRIGGER:
				for (unsigned int nCntKey = 0; nCntKey < m_keyData[i].key.size(); nCntKey++)
				{
					if (onTrigger(m_keyData[i].key[nCntKey]))
					{
						return true;
					}
				}
				return false;
			}

		}
	}
	return false;
}

//=============================================================
// [CInputSystem] �v���X���͔���
//=============================================================
bool CInputSystem::onPress(const std::string& key)
{
	if (key.length() <= 0)
	{ // ���������͂���Ă��Ȃ��Ƃ�
		return false;
	}

	// �L�[���Ƃɋ�؂�
	vector<string> sKeys = KeySplit(key);

	vector<CInputDevice*>& pInputDevice = CInputDevice::GetInputDevice();
	for (unsigned int nCntKey = 0; nCntKey < sKeys.size(); nCntKey++)
	{
		bool bInputKey = false;
		for (unsigned int i = 0; i < pInputDevice.size(); i++)
		{
			if (pInputDevice[i]->GetPress(sKeys[nCntKey]))
			{ // ���͂���Ă����Ƃ�
				bInputKey = true;
				break;
			}
		}
		
		// ���͂���Ă��Ȃ������Ƃ�
		if (!bInputKey)
		{
			return false;	// 1�ł����͂���Ă��Ȃ��ꍇ��false
		}
	}
	return true;
}

//=============================================================
// [CInputSystem] �g���K�[���͔���
//=============================================================
bool CInputSystem::onTrigger(const std::string& key)
{
	if (key.length() <= 0)
	{ // ���������͂���Ă��Ȃ��Ƃ�
		return false;
	}

	// �L�[���Ƃɋ�؂�
	vector<string> sKeys = KeySplit(key);

	vector<CInputDevice*>& pInputDevice = CInputDevice::GetInputDevice();
	for (unsigned int nCntKey = 0; nCntKey < sKeys.size(); nCntKey++)
	{
		bool bInputKey = false;
		for (unsigned int i = 0; i < pInputDevice.size(); i++)
		{
			if (pInputDevice[i]->GetTrigger(sKeys[nCntKey]))
			{ // ���͂���Ă����Ƃ�
				bInputKey = true;
				break;
			}
		}

		// ���͂���Ă��Ȃ������Ƃ�
		if (!bInputKey)
		{
			return false;	// 1�ł����͂���Ă��Ȃ��ꍇ��false
		}
	}
	return true;
}

//=============================================================
// [CInputSystem] ���͂̎擾
//=============================================================
LPDIRECTINPUT8 CInputSystem::GetDirectInput()
{
	return m_pInput;
}

//=============================================================
// [CInputSystem] ���͏��t�@�C���ǂݍ���
//=============================================================
HRESULT CInputSystem::LoadFile(const std::string& sPath)
{
	// json�t�@�C����ǂݍ���
	ifstream ifs(sPath.c_str());
	
	if (ifs.fail())
	{ // �t�@�C���̓ǂݍ��݂Ɏ��s
		MessageBox(CManager::GetInstance()->GetHWND() , "���͏��t�@�C���̓ǂݍ��݂Ɏ��s���܂���", "�G���[", MB_OK); //�I�����b�Z�[�W
		return E_FAIL;
	}

	// json�`���ɕϊ�
	std::string sInputData((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	auto jInput = json::parse(sInputData);

	for (auto keyMap = jInput.items().begin(); keyMap != jInput.items().end(); keyMap++)
	{
		std::string sKeyName = keyMap.key();
		std::string sInputType = jInput[sKeyName]["input"];

		// ���͕���
		INPUT_TYPE inputType = INPUT_TYPE::PRESS;
		if (sInputType == "press")
			inputType = INPUT_TYPE::PRESS;
		else if (sInputType == "trigger")
			inputType = INPUT_TYPE::TRIGGER;

		// �L�[���擾
		vector<string> keys;
		for (auto key = jInput[sKeyName]["key"].begin(); key != jInput[sKeyName]["key"].end(); key++)
		{
			keys.push_back(key.value());
		}

		// �L�[�f�[�^��ǉ�����
		AddKeyData(sKeyName, keys, inputType);
	}

	return S_OK;
}

//=============================================================
// [CInputSystem] &���Ƃɋ�؂�
//=============================================================
std::vector<std::string> CInputSystem::KeySplit(std::string key)
{
	// �ϐ�
	vector<string> result;
	unsigned int first = 0;
	int last = static_cast<int>(key.find_first_of("&"));
	if (last <= -1) result.push_back(key);

	// &���Ƃɋ�؂�
	while (first < key.size()) 
	{
		string subStr(key, first, last - first);	// &�܂ł͈̔͂̕�����

		result.push_back(subStr);

		// ����&�܂ł͈̔͂��擾
		first = last + 1;
		last = static_cast<int>(key.find_first_of("&", first));

		if (last == string::npos)
		{
			last = static_cast<int>(key.size());
		}
	}

	return result;
}

//=============================================================
// [CInputSystem] �L�[�f�[�^��ǉ�
//=============================================================
void CInputSystem::AddKeyData(const std::string& sKeyName, const std::vector<std::string>& key, INPUT_TYPE type)
{
	// ���ɓ������O�̃L�[�f�[�^�����݂��Ȃ������m�F����
	for (unsigned int i = 0; i < m_keyData.size(); i++)
	{
		if (m_keyData[i].sKeyName == sKeyName)
		{ // ���݂���Ƃ�
			return;	// �L�����Z������
		}
	}

	// �L�[�f�[�^���쐬����
	KeyData data;
	data.sKeyName = sKeyName;
	data.key = key;
	data.inputType = type;

	// �L�[�f�[�^��o�^����
	m_keyData.push_back(data);
}

//=============================================================
// [CKeyboardDevice] �R���X�g���N�^
//=============================================================
CInputDevice::CInputDevice()
{
	// �f�o�C�X�ꗗ�ɓo�^����
	m_apInputDevice.push_back(this);
}

//=============================================================
// [CKeyboardDevice] �f�X�g���N�^
//=============================================================
CInputDevice::~CInputDevice()
{
	// �f�o�C�X�ꗗ����폜����
	for (unsigned int i = 0; i < m_apInputDevice.size(); i++)
	{
		if (m_apInputDevice[i] == this)
		{
			m_apInputDevice.erase(m_apInputDevice.begin() + i);
			return;
		}
	}
}

//=============================================================
// [CKeyboardDevice] ���̓f�o�C�X���X�g�̎擾
//=============================================================
std::vector<CInputDevice*>& CInputDevice::GetInputDevice()
{
	return m_apInputDevice;
}


//=============================================================
// [CKeyboardDevice] ������
//=============================================================
HRESULT CKeyboardDevice::Init(HINSTANCE hInstance, HWND hWnd)
{
	// ���͂̎擾
	LPDIRECTINPUT8 pInput = CInputSystem::GetInstance()->GetDirectInput();

	// ���̓f�o�C�X: �L�[�{�[�h�̐���
	if (FAILED(pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, nullptr)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��
	m_pDevice->Acquire();

	return S_OK;
}

//=============================================================
// [CKeyboardDevice] �I��
//=============================================================
void CKeyboardDevice::Uninit()
{
	// ���̓f�o�C�X�̔j��
	if (m_pDevice != nullptr)
	{
		m_pDevice->Unacquire(); // �f�o�C�X�ւ̃A�N�Z�X����j��
		m_pDevice->Release();
		m_pDevice = nullptr;
	}
}

//=============================================================
// [CKeyboardDevice] �X�V
//=============================================================
void CKeyboardDevice::Update()
{
	BYTE aKeyState[MAX_KEYBOARD_KEY]; // �L�[�{�[�h�̓��͏��

	// ���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < MAX_KEYBOARD_KEY; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];		// �g���K�[����ۑ�
			m_aKeyState[nCntKey] = aKeyState[nCntKey];																						// �v���X����ۑ�
		}
	}
	else
	{
		m_pDevice->Acquire(); // �L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}
}

//=============================================================
// [CKeyboardDevice] �v���X����
//=============================================================
bool CKeyboardDevice::GetPress(const std::string& key)
{
	// �L�[�{�[�h�p�L�[�e�[�u���Ɋ܂܂�Ă��邩
	BYTE keycode;
	for (int i = 0; i < sizeof(keyboardTable) / sizeof(keyboardTable[0]); i++)
	{
		if (keyboardTable[i].key == key)
		{ // ���O�����v����Ƃ�
			keycode = keyboardTable[i].code;
			return (m_aKeyState[keycode] & 0x80) != 0;
		}
	}
	return false;
}

//=============================================================
// [CKeyboardDevice] �g���K�[����
//=============================================================
bool CKeyboardDevice::GetTrigger(const std::string& key)
{
	// �L�[�{�[�h�p�L�[�e�[�u���Ɋ܂܂�Ă��邩
	BYTE keycode;
	for (int i = 0; i < sizeof(keyboardTable) / sizeof(keyboardTable[0]); i++)
	{
		if (keyboardTable[i].key == key)
		{ // ���O�����v����Ƃ�
			keycode = keyboardTable[i].code;
			return (m_aKeyStateTrigger[keycode] & 0x80) != 0;
		}
	}
	return false;
}

//=============================================================
// [CGamepadDevice] ������
//=============================================================
HRESULT CGamepadDevice::Init(HINSTANCE hInstance, HWND hWnd)
{
	// �������̃N���A
	memset(&m_aJoyKeyState, 0, sizeof(XINPUT_STATE));

	//XInput�̃X�e�[�g��ݒ�i�L���ɂ���j
	XInputEnable(true);

	return S_OK;
}

//=============================================================
// [CGamepadDevice] �I��
//=============================================================
void CGamepadDevice::Uninit()
{
	//XInput�̃X�e�[�g��ݒ�i�����ɂ���j
	XInputEnable(false);
}

//=============================================================
// [CGamepadDevice] �X�V
//=============================================================
void CGamepadDevice::Update()
{
	XINPUT_STATE joykeyState;	// �W���C�p�b�h�̓��͏��

	// �W���C�p�b�h�̏����擾
	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
	{
		m_aJoyKeyStateTrigger.Gamepad.wButtons = (m_aJoyKeyState.Gamepad.wButtons ^ joykeyState.Gamepad.wButtons) & joykeyState.Gamepad.wButtons;
		m_aJoyKeyState = joykeyState;
	}
}

//=============================================================
// [CGamepadDevice] �v���X����
//=============================================================
bool CGamepadDevice::GetPress(const std::string& key)
{
	// �Q�[���p�b�h�p�L�[�e�[�u���Ɋ܂܂�Ă��邩
	WORD keycode;
	for (int i = 0; i < sizeof(gamepadTable) / sizeof(gamepadTable[0]); i++)
	{
		if (gamepadTable[i].key == key)
		{ // ���O�����v����Ƃ�
			keycode = gamepadTable[i].code;
			return (m_aJoyKeyState.Gamepad.wButtons & keycode) ? true : false;
		}
	}
	return false;
}

//=============================================================
// [CGamepadDevice] �g���K�[����
//=============================================================
bool CGamepadDevice::GetTrigger(const std::string& key)
{
	// �Q�[���p�b�h�p�L�[�e�[�u���Ɋ܂܂�Ă��邩
	WORD keycode;
	for (int i = 0; i < sizeof(gamepadTable) / sizeof(gamepadTable[0]); i++)
	{
		if (gamepadTable[i].key == key)
		{ // ���O�����v����Ƃ�
			keycode = gamepadTable[i].code;
			return (m_aJoyKeyStateTrigger.Gamepad.wButtons & keycode) ? true : false;
		}
	}
	return false;
}


//=============================================================
// [CMouseDevice] ������
//=============================================================
HRESULT CMouseDevice::Init(HINSTANCE hInstance, HWND hWnd)
{
	return S_OK;
}

//=============================================================
// [CMouseDevice] �I��
//=============================================================
void CMouseDevice::Uninit()
{
}

//=============================================================
// [CMouseDevice] �X�V
//=============================================================
void CMouseDevice::Update()
{
	bool aMouseState[MAX_MOUSE_BUTTON]; // �}�E�X�̓��͏��

	// ���N���b�N
	aMouseState[0] = GetKeyState(VK_LBUTTON) & 0x80;
	m_aMouseStateTrigger[0] = (m_aMouseState[0] ^ aMouseState[0]) & aMouseState[0];
	m_aMouseState[0] = aMouseState[0];

	// �E�N���b�N
	aMouseState[1] = GetKeyState(VK_RBUTTON) & 0x80;
	m_aMouseStateTrigger[1] = (m_aMouseState[1] ^ aMouseState[1]) & aMouseState[1];
	m_aMouseState[1] = aMouseState[1];

	// �����N���b�N
	aMouseState[2] = GetKeyState(VK_MBUTTON) & 0x80;
	m_aMouseStateTrigger[2] = (m_aMouseState[2] ^ aMouseState[2]) & aMouseState[2];
	m_aMouseState[2] = aMouseState[2];
}

//=============================================================
// [CMouseDevice] �v���X����
//=============================================================
bool CMouseDevice::GetPress(const std::string& key)
{
	// �}�E�X�p�L�[�e�[�u���Ɋ܂܂�Ă��邩
	for (int i = 0; i < sizeof(mouseTable) / sizeof(mouseTable[0]); i++)
	{
		if (mouseTable[i].key == key)
		{ // ���O�����v����Ƃ�
			return m_aMouseState[mouseTable[i].code];
		}
	}
	return false;
}

//=============================================================
// [CMouseDevice] �g���K�[����
//=============================================================
bool CMouseDevice::GetTrigger(const std::string& key)
{
	// �}�E�X�p�L�[�e�[�u���Ɋ܂܂�Ă��邩
	for (int i = 0; i < sizeof(mouseTable) / sizeof(mouseTable[0]); i++)
	{
		if (mouseTable[i].key == key)
		{ // ���O�����v����Ƃ�
			return m_aMouseStateTrigger[mouseTable[i].code];
		}
	}
	return false;
}