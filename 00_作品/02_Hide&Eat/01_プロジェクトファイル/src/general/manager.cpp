//=============================================================
//
// �}�l�[�W���[ [manager.cpp]
// Author: Ito Kotaro
//
//=============================================================
#include "manager.h"
#include "gameobject.h"
#include "scene.h"
#include "input_system.h"
#include "data_field.h"
#include "component/2d/text.h"

//=============================================================
// [CManager] �R���X�g���N�^
//=============================================================
CManager::CManager()
{
	m_showCursor = true;
}

//=============================================================
// [CManager] �f�X�g���N�^
//=============================================================
CManager::~CManager()
{

}

//=============================================================
// [CManager] ������
//=============================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// �n���h���̑��
	m_hwnd = hWnd;

	// �����_���[�̐���
	CRenderer::GetInstance()->Init(hInstance, hWnd, bWindow);

	// �t�H���g�̓ǂݍ���
	CText::InitLoadFont();

	// �����̐���
	CPhysics::GetInstance()->Init();

	// �f�[�^�}�l�[�W���[�̐���
	CDataManager::GetInstance()->Init();

	// �I�[�f�B�I�}�l�[�W���[�̐���
	m_pAudioManager = new CAudioManager();
	m_pAudioManager->Init();

	// ���̓V�X�e���̐���
	CInputSystem::GetInstance()->Init(hInstance, hWnd);

	// �V�[���}�l�[�W���[�̐���
	CSceneManager::GetInstance()->Init();
	CSceneManager::GetInstance()->SetScene(CSceneManager::START_SCENE_NAME);

	return S_OK;
}

//=============================================================
// [CManager] �I��
//=============================================================
void CManager::Uninit()
{
	// �V�[���}�l�[�W���[�̏I��
	CSceneManager::GetInstance()->Uninit();

	// ���ׂẴI�u�W�F�N�g���������
	GameObject::DestroyAll(true);
	GameObject::DestroyDeathFlag();

	// ���̓V�X�e���̏I��
	CInputSystem::GetInstance()->Uninit();

	// �����_���[��j������
	CRenderer::GetInstance()->Uninit();

	// ������j������
	CPhysics::GetInstance()->Uninit();

	// �I�[�f�B�I�}�l�[�W���[��j������
	if (m_pAudioManager != nullptr)
	{
		m_pAudioManager->Uninit();
		delete m_pAudioManager;
		m_pAudioManager = nullptr;
	}

	// �f�[�^�Ǘ���j������
	CDataManager::GetInstance()->Uninit();
}

//=============================================================
// [CManager] �X�V
//=============================================================
void CManager::Update()
{
	// ���̓V�X�e���̍X�V
	CInputSystem::GetInstance()->Update();

	// �I�[�f�B�I�̍X�V
	m_pAudioManager->Update();

	// �����_���[�̍X�V
	CRenderer::GetInstance()->Update();

	if (!m_bPause)
	{
		// �����̍X�V
		CPhysics::GetInstance()->Update();
	}

	// �V�[���̍X�V
	CSceneManager::GetInstance()->Update();
}

//=============================================================
// [CManager] �`��
//=============================================================
void CManager::Draw()
{
	// �����_���[�̕`��
	CRenderer::GetInstance()->Draw();

	// �V�[���̕`��
	CSceneManager::GetInstance()->Draw();
}

//=============================================================
// [CManager] �J�[�\���̕\��
//=============================================================
void CManager::SetShowCursor(const bool& show)
{
	if (m_showCursor != show)
	{
		ShowCursor(show ? TRUE : FALSE);
		m_showCursor = show;
	}
}

//=============================================================
// [CManager] �J�[�\���ʒu���擾����
//=============================================================
CManager::CursorPos CManager::GetCursorClientPos()
{
	POINT points;
	GetCursorPos(&points);
	
	// �X�N���[����Ō�������̍��W���擾����
	POINT startPos;
	startPos.x = 0;
	startPos.y = 0;
	ClientToScreen(m_hwnd, &startPos);

	CursorPos cPos;
	cPos.x = static_cast<float>(points.x - startPos.x);
	cPos.y = static_cast<float>(points.y - startPos.y);


	D3DXVECTOR2 rect = GetWindowSize();
	cPos.x *= static_cast<float>(CRenderer::SCREEN_WIDTH / (float)rect.x);
	cPos.y *= static_cast<float>(CRenderer::SCREEN_HEIGHT / (float)rect.y);
	return cPos;
}

//=============================================================
// [CManager] �J�[�\���ʒu��ݒ肷��
//=============================================================
void CManager::SetCursorClientPos(float x, float y)
{
	CursorPos cPos;
	cPos.x = x;
	cPos.y = y;

	// �X�N���[����Ō�������̍��W���擾����
	POINT startPos;
	startPos.x = 0;
	startPos.y = 0;
	ClientToScreen(m_hwnd, &startPos);

	D3DXVECTOR2 rect = GetWindowSize();
	cPos.x *= static_cast<float>(rect.x / (float)CRenderer::SCREEN_WIDTH);
	cPos.y *= static_cast<float>(rect.y / (float)CRenderer::SCREEN_HEIGHT);

	cPos.x += startPos.x;
	cPos.y += startPos.y;

	SetCursorPos(static_cast<int>(cPos.x), static_cast<int>(cPos.y));
}

//=============================================================
// [CManager] �E�B���h�E�T�C�Y
//=============================================================
D3DXVECTOR2 CManager::GetWindowSize()
{
	RECT rect;
	GetWindowRect(CManager::GetInstance()->GetHWND(), &rect);
	return D3DXVECTOR2(static_cast<float>(rect.right - rect.left), static_cast<float>(rect.bottom - rect.top));
}