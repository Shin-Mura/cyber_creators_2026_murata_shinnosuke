//========================================================================================================
//
//�V�[���̃��[�h[scene_mode.h]
// Author MurataShinnosuke
//
//========================================================================================================
#ifndef _SCENE_MODE_H_
#define _SCENE_MODE_H_

#include "main.h"
#include "object.h"
#include "pause.h"

//�O���錾
class Scene;   //�V�[��
//�V�[���̃��[�h
class SceneMode
{
public:
	//�R���X�g���N�^
	SceneMode(Scene* pScene)
	{
		//�����o�ϐ�������������
		this->m_pScene = pScene;
	}

	//�f�X�g���N�^
	virtual ~SceneMode()
	{
	}

	virtual void Init() = 0;   //����������
	virtual void Uninit() = 0;   //�I������
	virtual void Update() = 0;   //�X�V����
	virtual void Draw() = 0;   //�`�揈��

protected:
	Scene* GetScene() { return this->m_pScene; };   //�V�[���̎擾

private:
	Scene* m_pScene;   //�V�[��
};

//�^�C�g���V�[��
class SceneModeTitle : public SceneMode   //(�e)�V�[�����[�h
{
public:
	//�R���X�g���N�^
	SceneModeTitle(Scene* pScene) : SceneMode(pScene)
	{
		//�����o�ϐ�������������
		this->pTitleMenu = nullptr;
	}

	//�f�X�g���N�^
	~SceneModeTitle() override
	{
	}

	void Init() override;   //����������
	void Uninit() override;   //�I������
	void Update() override;   //�X�V����
	void Draw() override;   //�`�揈��

private:
	Object* pTitleMenu;   //�^�C�g�����j���[
};

//�Q�[���V�[��
class SceneModeGame : public SceneMode   //(�e)�V�[�����[�h
{
public:
	//�R���X�g���N�^
	SceneModeGame(Scene* pScene) : SceneMode(pScene)
	{
		//�����o�ϐ�������������
		this->m_pPause = nullptr;   //�|�[�Y
	}

	//�f�X�g���N�^
	~SceneModeGame() override
	{
	}

	void Init() override;   //����������
	void Uninit() override;   //�I������
	void Update() override;   //�X�V����
	void Draw() override;   //�`�揈��

	Pause* GetPause() { return this->m_pPause; };   //�|�[�Y�̎擾����

private:
	Pause* m_pPause;   //�|�[�Y
};

//���U���g�V�[��
class SceneModeResult : public SceneMode   //(�e)�V�[�����[�h
{
public:
	//�R���X�g���N�^
	SceneModeResult(Scene* pScene) : SceneMode(pScene)
	{
	}

	//�f�X�g���N�^
	~SceneModeResult() override
	{
	}

	void Init() override;   //����������
	void Uninit() override;   //�I������
	void Update() override;   //�X�V����
	void Draw() override;   //�`�揈��

private:
};

//�����L���O�V�[���N���X
class Ranking : public SceneMode   //(�e)�V�[�����[�h
{
public:
	//�R���X�g���N�^
	Ranking(Scene* pScene) : SceneMode(pScene)
	{
	}

	//�f�X�g���N�^
	~Ranking()
	{
	}

	void Init() override;   //����������
	void Uninit() override;   //�I������
	void Update() override;   //�X�V����
	void Draw() override;   //�`�揈��

private:
	void Control();   //���쏈��
};


#endif // !_SCENE_MODE_H_
