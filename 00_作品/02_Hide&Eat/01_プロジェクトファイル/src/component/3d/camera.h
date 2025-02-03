//=============================================================
//
// �J�����R���|�[�l���g [camera.h]
// Author: Ito Kotaro
//
//=============================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <component.h>
#include "renderer.h"
#include "skybox.h"

// �J�����R���|�[�l���g�̒�`
class CCamera : public Component
{
public:
	void Init() override;
	void Uninit() override;

	void Update();

	// �擾
	D3DXMATRIX GetProjectionMatrix() { return m_mtxProjection; }
	D3DXMATRIX GetViewMatrix() { return m_mtxView; }
	CSkybox* GetSkybox() { return m_pSkybox; }

	// �ݒ�ϐ�
	float m_fClippingPlanesNear;			// �N���b�v�����i�߂��j
	float m_fClippingPlanesFar;				// �N���b�v�����i�����j

	// �J�����̐ݒ�
	void SetCamera(const bool& isSet = true);																						// �J�����̐ݒ�
	void SetPosR(const D3DXVECTOR3& posR) { m_posR = posR; }					// �����_�̐ݒ�
	D3DXVECTOR3 GetPosR() { return m_posR; }												// �����_�̎擾
	void SetParallel(const bool& isParallel) { m_bParallel = isParallel; }					// ���s���e�̐ݒ�
	bool GetParallel() { return m_bParallel; }														// ���s���e��Ԃ̎擾
	void SetVisible(const bool& isVisible) { m_bVisible = isVisible; }						// �\���̐ݒ�
	bool GetVisible() { return m_bVisible; }														// �\���̎擾
	void SetAmbient(const float& fAmbient) { m_fAmbient = fAmbient; }			// ���邳�̐ݒ�
	float GetAmbient() { return m_fAmbient; }													// ���邳�̎擾
	void SetCustomPosR(const bool& enabled) { m_bCustomPosR = enabled; }	// �J�X�^�������_�̐ݒ�
	bool GetCustomPosR() { return m_bCustomPosR; }										// �J�X�^�������_�̎擾

	// �r���[�|�[�g�ݒ�
	void SetViewportPosition(float x, float y) {
		m_viewport.X = (DWORD)x;
		m_viewport.Y = (DWORD)y;
	}
	void SetViewportSize(float width, float height) {
		m_viewport.Width = (DWORD)width;
		m_viewport.Height = (DWORD)height;
	}

	// �w�i�F�̐ݒ�
	void SetColor(D3DXCOLOR col) { m_backColor = col; }
	D3DXCOLOR GetColor() { return m_backColor; }

private:
	D3DXCOLOR m_backColor;				// �w�i�F
	D3DXVECTOR3 m_vecU;					// ������x�N�g��
	D3DXVECTOR3 m_posR;					// �����_
	bool m_bCustomPosR;					// �J�X�^�������_
	float m_fLength;							// ���_�ƒ����_�̒���
	D3DXMATRIX m_mtxProjection;		// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;				// �r���[�}�g���b�N�X
	D3DVIEWPORT9 m_viewport;			// �r���[�|�[�g
	bool m_bParallel;							// ���s���e�ɂ��邩
	bool m_bVisible;								// �\�����邩

	CSkybox* m_pSkybox;					// �X�J�C�{�b�N�X
	float m_fAmbient;							// ���邳
};

#endif