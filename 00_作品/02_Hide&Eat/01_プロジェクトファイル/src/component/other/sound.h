//=============================================================
//
// �T�E���h [sound.h]
// Author: Ito Kotaro
//
//=============================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "component.h"
#include <fstream>

// �T�E���h�R���|�[�l���g
class CSound : public Component
{
public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	bool LoadWav(const std::string& sPath);

	// ���
	enum STATE
	{
		INITIAL,	// �Đ��O
		PLAYING,	// �Đ���
		PAUSED,	// �ꎞ��~��
		STOPPED,	// �Đ��I����
	};

	// �t�F�[�h���
	enum FADESTATE
	{
		NONE,		// �Ȃ�
		FADEIN,		// �t�F�[�h�C��
		FADEOUT	// �t�F�[�h�A�E�g
	};

	void Play();
	void Stop();
	void Pause();
	void Rewind();
	void SetLoop(const bool& bEnable);
	void SetVolume(const float& fVolume);
	void SetPitch(const float& fPitch);
	void FadeOut(const float& fFadeValue = 0.01f);
	void FadeIn(const float& fFadeValue = 0.01f, const float& fMaxVolume = 1.0f);
	STATE GetState();
	void IsStoppedDestroy(const bool& bEnable = true);
	void IsIgnoreDistance(const bool& bEnable = true);
private:
	ALuint m_source;					// �\�[�XID
	bool m_bStoppedDestroy;		// ��~�����Ƃ��ɃI�u�W�F�N�g��j�����邩
	bool m_bIgnoreDistance;		// �����𖳎�����

	float m_fFadeValue;				// �t�F�[�h�l
	float m_fFadeMaxVolume;		// �t�F�[�h�̍ő剹�ʁi�t�F�[�h�C���Ɏg�p�j
	FADESTATE m_fadeState;		// �t�F�[�h���
};

// ���X�i�[
class CSoundListener : public Component
{
public:
	void Init() override;
	void Uninit() override;
	void Update() override;

	void IsUpdateAngle(const bool& bEnable) { m_bUpdateAngle = bEnable; }
	void SetAngle(const float& fAngle);
private:
	D3DXVECTOR3 m_oldPos;
	bool m_bUpdateAngle;
};

#endif // !_SOUND_H_
