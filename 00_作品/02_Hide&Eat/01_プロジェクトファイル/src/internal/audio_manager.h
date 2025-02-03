//=============================================================
//
// �I�[�f�B�I�Ǘ� [audio_manager.h]
// Author: Ito Kotaro
//
//=============================================================
#ifndef _AUDIO_MANAGER_H_
#define _AUDIO_MANAGER_H_

#include "component.h"

// �I�[�f�B�I�Ǘ��N���X
class CAudioManager
{
public:
	HRESULT Init();			// ������
	void Uninit();		// �I��
	void Update();	// �X�V
private:
	ALCdevice* m_device;
	ALCcontext* m_context;
};

#endif // !_AUDIO_H_
