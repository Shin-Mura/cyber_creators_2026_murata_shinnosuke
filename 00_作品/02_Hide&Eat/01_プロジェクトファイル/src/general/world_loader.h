//=============================================================
//
// ���[���h���[�_�[ [world_loader.h]
// Author: Ito Kotaro
//
//=============================================================
#ifndef _WORLD_LOADER_H_
#define _WORLD_LOADER_H_

#include "gameobject.h"

// ���[���h��ǂݍ��ނ��߂̃N���X�ł�
// ���[���h���ƂŃI�u�W�F�N�g���Ǘ��ł��܂�
class WorldLoader
{
public:
	// ���[���h�t�@�C��(.wdit) �̓ǂݍ���
	void Load(const std::string& path);

	// �I�u�W�F�N�g�ɑ΂��Ď��s����v���O����
	virtual void CustomObject(GameObject* gameObject) {}
private:
	std::vector<GameObject*> m_pWorldObjects;		// ���[���h���Ɋ܂܂��I�u�W�F�N�g
};

#endif // !_WORLD_LOADER_H_