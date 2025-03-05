//========================================================================================================
//
//�����_���[����[renderer.cpp]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "camera.h"

//========================================================================================================
//�R���X�g���N�^
//========================================================================================================
Renderer::Renderer()
{
	//�����o�ϐ�������������
	this->m_pD3D = nullptr;   //Direct3D
	this->m_pD3DDevice = nullptr;   //Direct3D�f�o�C�X
	this->m_pFont = nullptr;   //�t�H���g
	this->m_isFullScreen = true;
	this->m_hWnd = nullptr;
}

//========================================================================================================
//�f�X�g���N�^
//========================================================================================================
Renderer::~Renderer()
{
}

//=======================================================================================================
//����������
//=======================================================================================================
HRESULT Renderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;   //�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;   //�v���[���e�[�V�����p�����[�^�[

	//DirectX3D�I�u�W�F�N�g�̐���
	this->m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (this->m_pD3D == NULL)
	{
		return E_FAIL;
	}

	//���݂̃f�B�X�v���C���[�h���擾����
	if (FAILED(this->m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));   //�p�����[�^�̃[���N���A

	d3dpp.BackBufferWidth = SCREEN_WIDTH;   //�Q�[����ʃT�C�Y ��
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;   //�Q�[����ʃT�C�Y ����
	d3dpp.BackBufferFormat = d3ddm.Format;   //�o�b�N�o�t�@�̌`��
	d3dpp.BackBufferCount = 1;   //�o�b�N�o�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;   //
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_�������n�[�h�E�F�A�ōs��)
	if (FAILED(this->m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &this->m_pD3DDevice)))
	{
		//Direct3D�f�o�C�X�̐���(�`�揈���̓n�[�h�E�F�A ���_������CPU�ōs��)
		if (FAILED(this->m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &this->m_pD3DDevice)))
		{
			//Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_������CPU�ōs��)
			if (FAILED(this->m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &this->m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//�����_�[�X�e�[�g�̐ݒ�
	this->m_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
	this->m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	this->m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	this->m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	this->m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//�T���v���[�X�e�[�g�̐ݒ�
	this->m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	this->m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	this->m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	this->m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	this->m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	this->m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	this->m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	//�E�B���h�E�n���h����ۑ�����
	this->m_hWnd = hWnd;

	//�f�o�b�O�\���p�t�H���g�̐���
	D3DXCreateFont(this->m_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &this->m_pFont);


	return S_OK;
}

//=======================================================================================================
//�I������
//=======================================================================================================
void Renderer::Uninit()
{
	//Direct3D�f�o�C�X�̔j��
	if (m_pD3DDevice != nullptr)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = nullptr;
	}

	//Direct3D�I�u�W�F�N�g�̔j��
	if (m_pD3D != nullptr)
	{
		m_pD3D->Release();
		m_pD3D = nullptr;
	}

	//�f�o�b�O�\���p�t�H���g�̔j��
	if (m_pFont != nullptr)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}
}

//=======================================================================================================
//�X�V����
//=======================================================================================================
void Renderer::Update()
{
	//�t���X�N���[���̐؂�ւ�����
	Keyboard* pKeyboard = Manager::Get()->GetKeyboard();
	if (pKeyboard->GetTrigger(DIK_F11))
	{//F11�L�[�������ꂽ�ꍇ
		//�t���X�N���[����؂�ւ���
		SetFullScreen(!this->m_isFullScreen);
	}
}

//=======================================================================================================
//�`�揈��
//=======================================================================================================
void Renderer::Draw()
{
	//��ʃN���A(�o�b�N�o�b�t�@ Z�o�b�t�@ �X�e���V���o�b�t�@�̃N���A)
	m_pD3DDevice->Clear(0, NULL, 
		(D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0),
		1.0f,
		0);

	//�`��J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{ //�`��J�n�����������ꍇ
		//�J�������t���Ă���I�u�W�F�N�g���擾����
		std::vector<Camera*> vCamera = Component::Get<Camera>();

		//�J�������t���Ă���I�u�W�F�N�g���J��Ԃ�
		for (unsigned int i = 0; i < vCamera.size(); i++)
		{
			//�J������ݒ肷��
			vCamera[i]->Set();
		}

		//�V�[���̕`�揈�����s��
		Manager::Get()->GetScene()->Draw();

		//�`��I��
		m_pD3DDevice->EndScene();
	}

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=======================================================================================================
//�t���X�N���[��
//=======================================================================================================
void Renderer::SetFullScreen(bool bFullScreen)
{
	//�t���X�N���[���t���O��؂�ւ���
	this->m_isFullScreen = bFullScreen;

	//���݂̃E�B���h�E�X�^�C�����擾����
	DWORD dwStyle = GetWindowLong(m_hWnd, GWL_STYLE);
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	//�t���X�N���[���t���O���m�F����
	if (m_isFullScreen == true)
	{
		//�E�B���h�E���[�h�ɐ؂�ւ���
		SetWindowLong(m_hWnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(m_hWnd, HWND_TOP, rect.left, rect.top,
			rect.right - rect.left, rect.bottom - rect.top,
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(m_hWnd, SW_NORMAL);
	}
	else
	{
		//�t���X�N���[�����[�h�ɐ؂�ւ���
		GetWindowRect(m_hWnd, &rect);
		SetWindowLong(m_hWnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
		SetWindowPos(m_hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(m_hWnd, SW_MAXIMIZE);
	}
}