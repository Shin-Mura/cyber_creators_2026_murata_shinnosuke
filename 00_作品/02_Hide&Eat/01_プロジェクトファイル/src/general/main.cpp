//=============================================================
//
// ���C������ [main.cpp]
// Author: Ito Kotaro
//
//=============================================================
#include "main.h"
#include "manager.h"
#include <windowsx.h>

// �������[���[�N���o
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define FIND_MEM_LEAKS
#endif // _DEBUG

#ifdef FIND_MEM_LEAKS
#define _NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define _NEW new
#endif // FIND_MEM_LEAKS

//=============================================================
// ���C���֐�
//=============================================================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
#ifdef _DEBUG
	// �������[���[�N���m
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(�ԍ�);
#endif

	DWORD dwCurrentTime;	// ���ݎ���
	DWORD dwExecLastTime;	// �Ō�ɏ�����������
	DWORD dwFrameCount;		// �t���[���J�E���g
	DWORD dwFPSLastTime;	// �Ō��FPS���v����������

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),						// �������T�C�Y
		CS_CLASSDC,									// �E�B���h�E�̃X�^�C��
		WindowProc,										// �E�B���h�E�̃v���V�[�W��
		0,
		0,
		hInstance,											// �C���X�^���X�n���h��
		LoadIcon(nullptr, IDI_APPLICATION),	// �^�X�N�o�[�̃A�C�R��
		LoadCursor(nullptr,IDC_ARROW),			// �}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),		// �N���C�A���g�̈�̔w�i�F
		nullptr,												// ���j���[�o�[
		CLASS_NAME,									// �E�B���h�E�N���X�̖��O
		LoadIcon(nullptr, IDI_APPLICATION)		// �t�@�C���̃A�C�R��
	};

	HWND hWnd;	// �E�B���h�E�n���h���i���ʎq�j
	MSG msg;			// ���b�Z�[�W���i�[����ϐ�

	// �E�B���h�E�̍��W���i�[
	RECT rect = { 0, 0, CRenderer::SCREEN_WIDTH, CRenderer::SCREEN_HEIGHT };

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �N���C�A���g�̈���w��T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	// �E�B���h�E�𐶐�
	hWnd = CreateWindowEx(
		0,														// �g���E�B���h�E�X�^�C��
		CLASS_NAME,									// �E�B���h�E�N���X�̖��O
		WINDOW_NAME,								// �E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,				// �E�B���h�E�X�^�C��
		CW_USEDEFAULT,								// �E�B���h�E�̍����X���W
		CW_USEDEFAULT,								// �E�B���h�E�̍����Y���W
		(rect.right - rect.left),							// �E�B���h�E�̕�
		(rect.bottom - rect.top),						// �E�B���h�E�̍���
		nullptr,												// �e�E�B���h�E�̃n���h��
		nullptr,												// ���j���[�n���h���܂��͎q�E�B���h�EID
		hInstance,											// �C���X�^���X�o���h��
		nullptr												// �E�B���h�E�쐬�f�[�^
	);

	// �E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);		// �E�B���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd);						// �N���C�A���g�̈���X�V

	// �}�l�[�W���[�̐����E������
	CManager::GetInstance()->Init(hInstance, hWnd, TRUE);

	// ����\��ݒ�
	timeBeginPeriod(1);
	dwCurrentTime = 0;							// ����������
	dwExecLastTime = timeGetTime();		// ���ݎ������擾

	// FPS�v���̏�����
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	// ���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) != 0)
		{ // Windows�̏���
			if (msg.message == WM_QUIT)
			{ // WM_QUIT���b�Z�[�W
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{ // DirectX�̏���
			dwCurrentTime = timeGetTime();		// ���ݎ������擾

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{ // 0.5�b�o�ߖ�
				// FPS���v��
				CManager::GetInstance()->SetFPS((dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime));
				dwFPSLastTime = dwCurrentTime;							// �v�������������L�^
				dwFrameCount = 0;												// �t���[���J�E���g���N���A
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / FIXED_FPS))
			{ // 60����1�b�o��

				// �f���^�^�C����ݒ肷��
				CManager::GetInstance()->SetDeltaTime((dwCurrentTime - dwExecLastTime) * 0.001f);

				//�����J�n����
				dwExecLastTime = dwCurrentTime;

				// �X�V����
				CManager::GetInstance()->Update();

				// �`�揈��
				CManager::GetInstance()->Draw();

				// �V�[���̕ύX����
				CSceneManager::GetInstance()->ChangingScene();

				// ���S�t���O�̂����I�u�W�F�N�g��j������
				GameObject::DestroyDeathFlag();

				// �}�E�X�z�C�[���l��������
				CManager::GetInstance()->SetMouseWheel(0);
				
				dwFrameCount++; // �t���[���J�E���g�����Z
			}
		}
	}

	// ����\��߂�
	timeEndPeriod(1);

	// �}�l�[�W���[�̏I���E���
	CManager::GetInstance()->Uninit();

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=============================================================
// �E�B���h�E�v���V�[�W��
//=============================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;
	auto hdc = GetDC(hWnd);

	switch (uMsg)
	{
	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_ESCAPE:
			nID = MessageBox(hWnd, "�I�����܂����H", "�m�F", MB_YESNO); //�I�����b�Z�[�W
			if (nID == IDYES)
			{ // �u�͂��v��I�������Ƃ�
				DestroyWindow(hWnd); //�E�B���h�E��j��
			}
			break;
		}
		break;

	case WM_CLOSE:

		nID = MessageBox(hWnd, "�I�����܂����H", "�m�F", MB_YESNO); //�I�����b�Z�[�W

		if (nID == IDYES)
		{ //�u�͂��v��I�������Ƃ�
			DestroyWindow(hWnd); //�E�B���h�E��j��
		}
		else
		{ //�u�������v��I�������Ƃ�
			return 0; //�C�x���g���L�����Z��
		}

		break;

	case WM_MOUSEWHEEL:
		// �}�E�X�z�C�[���̈ړ��ʂ��擾
		CManager::GetInstance()->SetMouseWheel(GET_WHEEL_DELTA_WPARAM(wParam));
		return 0;
		break;

	case WM_DESTROY:
		//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam); //����̏�����Ԃ�
}