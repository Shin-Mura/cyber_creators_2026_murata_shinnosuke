//=============================================================
//
// ���̓V�X�e�� [input_system.h]
// Author: Ito Kotaro
//
//=============================================================
#ifndef _INPUT_SYSTEM_H_
#define _INPUT_SYSTEM_H_

// ���̓f�o�C�X�i���j
class CInputDevice
{
public:
	CInputDevice();																				// �R���X�g���N�^
	virtual ~CInputDevice();																	// �f�X�g���N�^
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd) = 0;		// ������
	virtual void Uninit() = 0;																	// �I��
	virtual void Update() = 0;																// �X�V
	virtual bool GetPress(const std::string& key) = 0;								// �v���X���͂̎擾
	virtual bool GetTrigger(const std::string& key) = 0;							// �g���K�[���͂̎擾
	static std::vector<CInputDevice*>& GetInputDevice();						// ���̓f�o�C�X�ꗗ�̎擾

protected:
	LPDIRECTINPUTDEVICE8 m_pDevice;
	static std::vector<CInputDevice*> m_apInputDevice;
};

// �L�[�{�[�h�f�o�C�X
class CKeyboardDevice : public CInputDevice
{
public:
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit();
	void Update();
	bool GetPress(const std::string& key);
	bool GetTrigger(const std::string& key);
	static const int MAX_KEYBOARD_KEY = 256;
private:
	BYTE m_aKeyState[MAX_KEYBOARD_KEY];
	BYTE m_aKeyStateTrigger[MAX_KEYBOARD_KEY];
};

// �Q�[���p�b�h�f�o�C�X
class CGamepadDevice : public CInputDevice
{
public:
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit();
	void Update();
	bool GetPress(const std::string& key);
	bool GetTrigger(const std::string& key);
	XINPUT_STATE& GetState() { return m_aJoyKeyState; }
private:
	XINPUT_STATE m_aJoyKeyState;
	XINPUT_STATE m_aJoyKeyStateTrigger;
};

// �}�E�X�f�o�C�X
class CMouseDevice : public CInputDevice
{
public:
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit();
	void Update();
	bool GetPress(const std::string& key);
	bool GetTrigger(const std::string& key);

	static const int MAX_MOUSE_BUTTON = 3;
private:
	bool m_aMouseState[MAX_MOUSE_BUTTON];
	bool m_aMouseStateTrigger[MAX_MOUSE_BUTTON];
};

// ���̓V�X�e��
class CInputSystem
{
public:
	// @brief �R���X�g���N�^
	CInputSystem();

	/*
	@brief ���̓V�X�e���̏���������
	@return ���s����
	*/
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);

	/*
	@brief ���̓V�X�e���̏I������
	*/
	void Uninit();

	/*
	@brief ���̓V�X�e���̍X�V����
	*/
	void Update();

	/*
	@brief �w��L�[�����͂���Ă��邩�̔���
	@param[in] sKeyName : �o�^�����L�[��
	@return bool : ���͏��
	*/
	bool onInput(const std::string& sKeyName);

	/*
	@brief �L�[�P�̂̃v���X����
	@param[in] key : �L�[��
	@return bool : ���͏��
	*/
	bool onPress(const std::string& key);

	/*
	@brief �L�[�P�̂̃g���K�[����
	@param[in] key : �L�[��
	@return bool : ���͏��
	*/
	bool onTrigger(const std::string& key);

	/*
	@brief �o�^����Ă�����̓f�o�C�X�̎擾
	@return ���̓f�o�C�X�̃|�C���^�i���s: nullptr�j
	*/
	template<class T> T* GetInputDevice() {
		std::vector<CInputDevice*>& pDeviceList = CInputDevice::GetInputDevice();
		for (int i = 0; i < pDeviceList.size(); i++)
		{
			if (typeid(T) == typeid(*pDeviceList[i]))
			{ // �^����v����Ƃ�
				T* pCasted = (T*)pDeviceList[i];
				return pCasted;
			}
		}
		return nullptr;	// ������Ȃ������Ƃ�
	}

	/*
	@brief ���͂̎擾
	@return LPDIRECTINPUT8
	*/
	LPDIRECTINPUT8 GetDirectInput();

	/*
	@brief �C���X�^���X�̎擾
	@return �C���X�^���X
	*/
	static CInputSystem* GetInstance()
	{
		static CInputSystem instance;
		return &instance;
	}

	// ���͕���
	enum INPUT_TYPE
	{
		PRESS,
		TRIGGER
	};

	// �L�[�f�[�^
	struct KeyData
	{
		std::string sKeyName;				// �L�[��
		std::vector<std::string> key;		// ���̓L�[�i���͔��ʁj
		INPUT_TYPE inputType;				// ���͕���
	};
private:
	/*
	@brief ���͏��t�@�C���ǂݍ���
	@param[in] sPath : ���͏��t�@�C���̃p�X
	@return bool : ���s����
	*/
	HRESULT LoadFile(const std::string& sPath = "data\\input.json");

	/*
	@brief ���������ɑΉ����邽�߂�&��؂�ɕ�����
	*/
	std::vector<std::string> KeySplit(std::string key);

	/*
	@brief �L�[�f�[�^�̍쐬
	@param[in] sKeyName : �L�[��
	@param[in] key : ���̓L�[
	@param[in] type : ���͕����iPRESS, TRIGGER�j
	*/
	void AddKeyData(const std::string& sKeyName, const std::vector<std::string>& key, INPUT_TYPE type);

	std::vector<KeyData> m_keyData;
	LPDIRECTINPUT8 m_pInput;
};

#endif // !_INPUT_SYSTEM_H_
