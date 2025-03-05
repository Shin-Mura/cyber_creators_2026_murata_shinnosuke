//********************************************************************************************************
//
//���C������[main.cpp]
// Author Murata Shinnosuke
//
//********************************************************************************************************
#include "main.h"
#include "manager.h"

// �������[���[�N���o
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define FIND_MEM_LEAKS
#endif // _DEBUG

#ifdef FIND_MEM_LEAKS
#define _NEW new (NORMALBLOCK, FILE, __LINE)
#else
#define _NEW new
#endif // FIND_MEM_LEAKS

//�v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//�O���[�o���ϐ���錾
int g_nCountFPS = 0;   //fps�J�E���^

//=======================================================================================================
//���C���֐�
//=======================================================================================================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
#ifdef _DEBUG
	// �������[���[�N���m
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(386);
#endif

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL, IDI_APPLICATION),
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL, IDI_APPLICATION),
	};

	HWND hWnd; //�E�C���h�E�n���h��
	MSG msg; //���b�Z�[�W���i�[����ϐ�

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	DWORD dwCurrentTime;
	DWORD dwExecLastTime;
	DWORD dwFrameCount;   //�t���[���J�E���g
	DWORD dwFPSLastTime;   //�Ō��FPS���v�����Ď���

	//�E�C���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	//�E�C���h�E�𐶐�
	hWnd = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(rect.right - rect.left),
		(rect.bottom - rect.top),
		NULL,
		NULL,
		hInstance,
		NULL);

	//�}�l�[�W���[�𐶐�����
	Manager::Create();
	Manager* pManager = Manager::Get();
	pManager->Init(hInstance, hWnd, TRUE);

	//����\�̐ݒ�
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();

	//�E�C���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);   //�E�C���h�E�\����Ԑݒ�
	UpdateWindow(hWnd);   //�N���C�A���g�̈���X�V

	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windows�̏���
			if (msg.message == WM_QUIT)
			{ //WM_QUIT���b�Z�[�W���󂯎�����ꍇ
				//���[�v�𔲂���
				break;
			}
			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{ //DirectX�̏���
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5�b�o��
				//FPS���v��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}
			//�X�V����
			pManager->Update();

			//�`�揈��
			pManager->Draw();
		}
	};

	//�I������
	pManager->Uninit();
	delete pManager;
	pManager = nullptr;

	//�E�C���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=======================================================================================================
//�E�C���h�E�v���V�[�W��
//=======================================================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//�ϐ���錾
	int nID;   //�Ԃ�l�i�[

	switch (uMsg)
	{
	case WM_DESTROY:
		//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_CLOSE:   //����{�^��
		//���b�Z�[�WBOX��\������
		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO | MB_ICONQUESTION);

		if (nID == IDYES)
		{//yes�̏ꍇ
			////���b�Z�[�WBOX�\������
			//MessageBox(hWnd, "���������[�I", "��������", MB_OK | MB_ICONINFORMATION);

			//�E�B���h�E��j������
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;   //0��Ԃ�
		}
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:   //escape�L�[
			//���b�Z�[�WBOX��\������
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO | MB_ICONQUESTION);

			if (nID == IDYES)
			{ //yes�̏ꍇ
				//���b�Z�[�WBOX�\������
				//MessageBox(hWnd, "���������[�I", "��������", MB_OK | MB_ICONINFORMATION);

				//�E�B���h�E��j������
				DestroyWindow(hWnd);
			}
			break;

		case VK_SPACE:   //space�L�[
			//���b�Z�[�WBOX�\������
			//MessageBox(hWnd, "��������I��������I", "��������", MB_OK | MB_ICONINFORMATION);
			break;

		case 0x41:   //a�L�[
			//���b�Z�[�WBOX�\������
			//MessageBox(hWnd, "���Ă����̂��ƍD�������`", "��������", MB_OK | MB_ICONINFORMATION);
			break;

		case 0x34:   //4�L�[
			//���b�Z�[�WBOX�\������
			//MessageBox(hWnd, "44.5...", "��������", MB_OK | MB_ICONINFORMATION);
			break;
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}