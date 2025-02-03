//========================================================================================================
//
//�}�l�[�W���[����[manager.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
#include "benlib.h"
#include "renderer.h"
#include "texture.h"
#include "Xfile.h"
#include "keyboard.h"
#include "mouse.h"
#include "joypad.h"
#include "scene.h"
#include "camera.h"
#include "physics.h"

//�}�l�[�W���[�N���X
class Manager
{
public:
	//�f�X�g���N�^
	~Manager()
	{

	}

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);   //������
	void Uninit();   //�I������
	void Update();   //�X�V����
	void Draw();   //�`�揈��

	void SetSceneMode(Scene::MODE mode);   //�V�[���̐ݒ菈��

	Renderer* GetRenderer() { return m_pRenderer; };   //�����_���[�̎擾����
	Texture* GetTexture() { return m_pTexture; };   //�e�N�X�`���̎擾����
	XFile* GetXFile() { return m_pXFile; };   //X�t�@�C���̎擾����
	Keyboard* GetKeyboard() { return m_pKeyboard; };   //�L�[�{�[�h�̎擾����
	Mouse* GetMouse() { return m_pMouse; };   //�}�E�X�̎擾����
	Joypad* GetJoypad() { return m_pJoypad; };   //�W���C�p�b�h�̎擾����
	Scene* GetScene() { return m_pScene; };   //�V�[���̎擾����

	static void Create()
	{
		//�C���X�^���X���m�F����
		if (Manager::m_pInstance != nullptr)
		{
			//�����I��
			return;
		}

		//�C���X�^���X�𐶐�����
		Manager::m_pInstance = new Manager;
	}

	static Manager* Get() { return Manager::m_pInstance; };   //�}�l�[�W���̎擾

private:
	//�R���X�g���N�^
	Manager()
	{
		//�����o�ϐ�������������
		this->m_pRenderer = nullptr;
		this->m_pTexture = nullptr;
		this->m_pXFile = nullptr;
		this->m_pKeyboard = nullptr;
		this->m_pMouse = nullptr;
		this->m_pJoypad = nullptr;
		this->m_pScene = nullptr;
	}

	Renderer* m_pRenderer;   //�����_���[
	Texture* m_pTexture;   //�e�N�X�`��
	XFile* m_pXFile;   //X�t�@�C��
	Keyboard* m_pKeyboard;   //�L�[�{�[�h
	Mouse* m_pMouse;   //�}�E�X
	Joypad* m_pJoypad;   //�W���C�p�b�h
	Scene* m_pScene;   //�V�[��

	static Manager* m_pInstance;   //�C���X�^���X
};

#endif // !_MANAGER_H_
