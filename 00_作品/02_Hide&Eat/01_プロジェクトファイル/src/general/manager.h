//=============================================================
//
// �}�l�[�W���[ [manager.h]
// Author: Ito Kotaro
//
//=============================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "renderer.h"
#include "scene.h"
#include "internal/physics.h"
#include "internal/data_manager.h"
#include "internal/audio_manager.h"
#include "gameobject.h"

// �}�l�[�W���[�N���X�̒�`
class CManager
{
public:
	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);	// ������
	void Uninit();																						// �I��
	void Update();																					// �X�V
	void Draw();																						// �`��

	static CManager* GetInstance() {
		static CManager manager;
		return &manager;
	}

	void SetFPS(const int& nFPS) { m_nFPS = nFPS; }														// FPS�̐ݒ�i���[�U�[�̎g�p�֎~�j
	const int GetFPS() { return m_nFPS; }																			// FPS�̎擾
	void SetDeltaTime(const float& fDeltaTime) { m_fDeltaTime = fDeltaTime; }					// �f���^�^�C���̐ݒ�i���[�U�[�̎g�p�֎~�j
	const float GetDeltaTime() { return m_fDeltaTime; }													// �f���^�^�C���̎擾
	void SetPause(const bool& bPause) { m_bPause = bPause; }											// �|�[�Y�̐ݒ�
	const bool GetPause() { return m_bPause; }																// �|�[�Y�̎擾
	void SetMouseWheel(const int& nMouseWheel) { m_nMouseWheel = nMouseWheel; }	// �}�E�X�z�C�[���̐ݒ�i���[�U�[�̎g�p�֎~�j
	const int GetMouseWheel() { return m_nMouseWheel; }												// �}�E�X�z�C�[���̎擾
	void SetShowCursor(const bool& show);

	struct CursorPos
	{
		float x;
		float y;
	};

	CursorPos GetCursorClientPos();																						// �J�[�\���ʒu�̎擾
	void SetCursorClientPos(float x, float y);																	// �J�[�\���ʒu�̐ݒ�
	D3DXVECTOR2 GetWindowSize();																				// �E�B���h�E�T�C�Y�̎擾

	HWND GetHWND() { return m_hwnd; }												// �n���h���̎擾
private:
	int m_nFPS;												// FPS�l
	float m_fDeltaTime;									// �f���^�^�C��
	int m_nMouseWheel;									// �}�E�X�z�C�[���l
	POINT m_cursorPos;								// �}�E�X�ʒu
	bool m_bPause;											// �|�[�Y
	bool m_showCursor;									// �J�[�\���̕\��
	HWND m_hwnd;										// �n���h��
	CAudioManager* m_pAudioManager;			// �I�[�f�B�I�}�l�[�W���[
};

#endif // !_MANAGER_H_
