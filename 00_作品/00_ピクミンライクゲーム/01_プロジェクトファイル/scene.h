//========================================================================================================
//
//�V�[������[scene.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"
#include "scene_mode.h"

//�V�[���N���X
class Scene
{
public:
	//���[�h�̗�
	enum MODE
	{
		IS_TITLE = 0,   //�^�C�g��
		IS_GAME,   //�Q�[��
		IS_RESULT,   //���U���g
		IS_RANKIGN,   //�����L���O
	};

	//�R���X�g���N�^
	Scene()
	{
		//�����o�ϐ�������������
		this->m_isNext = false;   //�J�ڃt���O
		this->m_modeNext = Scene::MODE::IS_TITLE;   //���̃��[�h
		this->m_pMode = nullptr;   //���[�h
	}

	//�f�X�g���N�^
	~Scene()
	{
		//���[�h��j������
		delete this->m_pMode;
	}

	void Init() { this->m_pMode->Init(); };   //����������
	void Uninit() { this->m_pMode->Uninit(); };   //�I������
	void Update() { this->m_pMode->Update(); };   //�X�V����
	void Draw() { this->m_pMode->Draw(); };   //�`�揈��
	void ChangeMode(SceneMode* pMode);   //���[�h�̕ύX
	void Reset() { this->m_isNext = false; };   //���Z�b�g
	void Next(Scene::MODE modeNext) { this->m_isNext = true; this->m_modeNext = modeNext; };   //�J�ڃt���O�𗧂Ă�
	bool GetNext() { return this->m_isNext; };   //�J�ڃt���O�̎擾
	Scene::MODE GetNextMode() { return this->m_modeNext; };   //���̃��[�h�̎擾

private:
	bool m_isNext;   //�J�ڃt���O
	Scene::MODE m_modeNext;   //���̃��[�h
	SceneMode* m_pMode;   //���[�h
};

#endif // !_SCENE_H_
