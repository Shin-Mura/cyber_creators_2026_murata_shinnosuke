//========================================================================================================
//
//�V�[������[scene.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

//�V�[���N���X
class Scene
{
public:
	typedef enum
	{
		IS_TITLE = 0,   //�^�C�g��
		IS_GAME,   //�Q�[��
		IS_RESULT,   //���U���g
		IS_RANKIGN,   //�����L���O
	}MODE;   //���[�h

	//�R���X�g���N�^
	Scene()
	{
		//�����o�ϐ�������������
		this->m_mode = Scene::MODE::IS_TITLE;   //���[�h
		this->m_isNextScene = false;   //�J�ڃt���O
	}

	//�f�X�g���N�^
	virtual ~Scene()
	{
	}

	virtual void Init() = 0;   //����������
	virtual void Uninit() = 0;   //�I������
	virtual void Update() = 0;   //�X�V����
	virtual void Draw() = 0;   //�`�揈��
	void NextScene() { this->m_isNextScene = true; };   //�I���t���O�𗧂Ă�

	static Scene* Create(MODE mode);   //��������

protected:
	bool GetEnd() { return this->m_isNextScene; };   //�I���t���O�̎擾

private:
	MODE m_mode;   //���[�h
	bool m_isNextScene;   //�I���t���O
};

#endif // !_SCENE_H_
