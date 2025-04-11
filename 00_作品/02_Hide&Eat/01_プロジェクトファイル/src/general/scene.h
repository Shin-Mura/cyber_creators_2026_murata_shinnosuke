//=============================================================
//
// �V�[���Ǘ� [scene.h]
// Author: Ito Kotaro
// 
// ����: �V�[���̊Ǘ����s���܂�
//
//=============================================================
#ifndef _SCENE_H_
#define _SCENE_H_

// �V�[���̊��N���X
class CScene
{
public:
	virtual ~CScene() {}			// �f�X�g���N�^
	virtual void Init() {}			// ������
	virtual void Uninit() {}		// �I��
	virtual void Update() {}		// �X�V
	virtual void Draw() {}			// �`��
	virtual void LastUninit() {}	// �ŏI�I��
};

// �V�[���}�l�[�W���[
class CSceneManager
{
public:
	CSceneManager();		// �R���X�g���N�^

	/*
	@brief �V�[�����
	@param pScene : �V�[���̃|�C���^
	@param sName : �V�[����
	*/
	typedef struct
	{
		CScene* pScene;		// �V�[���̃|�C���^
		std::string sName;		// �V�[����
	}SceneData;

	void Init();				// ������
	void Uninit();			// �I��
	void Update();		// �X�V
	void Draw();			// �`��

	/*
	@brief �V�[���̐؂�ւ��i�ݒ�j
	@param [in] sName : �V�[����
	@param [in] bIsDestroy : �j�����邩
	@return �V�[�����
	*/
	HRESULT SetScene(std::string sName, bool bIsDestroy = true);

	/*
	@brief ���݂̃V�[���̍ēǂݍ���
	*/
	void ReloadScene();

	/*
	@brief �O�V�[���̏I���A���V�[���̏������i���S������邽�߁A���s���Ȃ��ł��������j
	*/
	void ChangingScene();

	/*
	@brief �V�[���̓o�^ ��: RegistScene<CAScene>("a");
	@param [template] : �V�[���N���X
	@param [in] sName : �V�[����
	*/
	template<class T> void RegistScene(std::string sName)
	{
		// �����|�C���^�����݂��Ȃ������`�F�b�N
		for (unsigned int i = 0; i < m_apScene.size(); i++)
		{
			if (m_apScene[i]->sName == sName)
			{ // �������O�����������Ƃ�
				return;	// ���s
			}
		}

		// �V�[���f�[�^���쐬����
		SceneData* pData = new SceneData();
		pData->pScene = new T();		// �|�C���^
		pData->sName = sName;		// ���O

		// �o�^����
		m_apScene.push_back(pData);
	}

	/*
	@brief �V�[���̎擾
	@param [in] sName : �V�[����
	@return �V�[�����
	*/
	SceneData* GetScene(std::string sName);

	/*
	@brief ���݂̃V�[���̎擾
	@return �V�[�����
	*/
	SceneData* GetCurrentScene() { return m_pCurrentScene; }

	/*
	@brief �C���X�^���X�̎擾
	@return �C���X�^���X
	*/
	static CSceneManager* GetInstance()
	{
		static CSceneManager instance;
		return &instance;
	}

	static const std::string START_SCENE_NAME;		// �X�^�[�g�V�[���̖��O
private:
	SceneData* m_pCurrentScene;					// ���݂̃V�[��
	SceneData* m_pNextScene;						// ���̃V�[���i�\��j
	bool m_bNoDestroy;									// �I�u�W�F�N�g��j�����邩
	bool m_bReload;										// �����[�h�g���K�[
	std::vector<SceneData*> m_apScene;		// �V�[���Ǘ�
};

#endif // !_SCENE_H_
