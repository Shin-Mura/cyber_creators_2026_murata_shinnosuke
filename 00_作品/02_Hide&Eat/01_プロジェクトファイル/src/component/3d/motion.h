//=============================================================
//
// ���[�V���� [motion.h]
// Author: Ito Kotaro
//
//=============================================================
#ifndef _MOTION_H_
#define _MOTION_H_

#include "transform.h"
#include "component.h"

// ���[�V�������e�N���X�̒�`
class CMotionContents
{
public:
	CMotionContents(int nPartsNum);			// �R���X�g���N�^

	// �L�[�\����
	typedef struct
	{
		int nKeyFrame;				// �L�[�̈ʒu
		Transform transform;		// �g�����X�t�H�[��
	}Key;

	// �L�[�̒ǉ�
	void AddKey(int nPartsIdx, int nKey,
		D3DXVECTOR3 pos = { 0.0f, 0.0f, 0.0f }, 
		D3DXVECTOR3 rot = { 0.0f, 0.0f, 0.0f }, 
		D3DXVECTOR3 scale = { 1.0f, 1.0f, 1.0f });
	void RemoveKey(int nPartsIdx, int nKey);				// �L�[�̍폜
	void SortKey(int nPartsIdx);								// �\�[�g����

	// �擾
	std::string GetName() { return m_name; }								// ���O���擾
	int GetMaxFrame() { return m_nMaxFrame; }							// �ő�t���[�����̎擾
	bool GetLoop() { return m_bLoop; }										// ���[�v�̎擾
	Transform GetTransform(int nPartsIdx, int nKey);						// �L�[�ʒu�̃g�����X�t�H�[���l���擾
	std::vector<std::vector<Key>>& GetKey() { return m_partsKey; }

	// �ݒ�
	void SetName(std::string ContentsName) {	// ���O�ύX
		m_name = ContentsName;
	}
	void SetMaxFrame(int nMaxFrame) {									// �ő�t���[�����̐ݒ�
		if (nMaxFrame >= 0)
		{
			m_nMaxFrame = nMaxFrame;
		}
	}
	void SetLoop(bool bLoop) { m_bLoop = bLoop; }					// ���[�v�̐ݒ�

private:
	std::string m_name;															// ���[�V������
	int m_nMaxFrame;																// �ő�t���[��
	bool m_bLoop;																	// ���[�v
	std::vector<std::vector<Key>>	m_partsKey;						// �p�[�c���Ƃ̃L�[
};


// ���[�V�������C���[�N���X�̒�`
class CMotionLayer
{
public:
	CMotionLayer(int* pBlendFrame);										// �R���X�g���N�^
	void Update();																	// �X�V

	void AddParts(int nPartsIdx);												// �p�[�c��ǉ�����
	void RemoveParts(int nPartsIdx);											// �p�[�c���폜����
	void SetMotion(CMotionContents* pContents);

	// �擾
	char* GetName() { return &m_name[0]; }							// ���O���擾
	std::vector<int> GetPartsList() { return m_partsIdx; }			// �p�[�c���X�g���擾
	int GetKeyFrame() { return m_nKeyFrame; }						// �L�[�t���[�����擾
	void SetKeyFrame(int nKeyFrame) { m_nKeyFrame = nKeyFrame; }
	CMotionContents* GetPlayContents() {									// �Đ����̃R���e���c���擾
		return m_pPlayContents; 
	}
	bool GetEnded() { return m_bEnded; }								// �I�����Ă��邩
	
	// �ݒ�
	void SetName(std::string LayerName) {								// ���O�ύX
		m_name = LayerName;
	}

private:
	std::string m_name;															// ���C���[��
	std::vector<int> m_partsIdx;												// �܂܂��p�[�c�C���f�b�N�X
	CMotionContents* m_pPlayContents;									// �Đ����̃��[�V����
	int m_nKeyFrame;																// �L�[�t���[��
	int m_nBlendCounter;															// �u�����h�J�E���^�[
	int* m_pBlendFrame;															// �u�����h�t���[���̎擾�p�|�C���^

	bool m_bEnded;																	// ���[�V�������I�����Ă��邩

	// �u�����h�̂��߂̑O��̃��[�V����
	CMotionContents* m_pBeforeContents;								// �O��̃R���e���c
	int m_nBeforeKeyFrame;													// �O��̃L�[�t���[��
};

// ���[�V�����N���X�̒�`
class CMotionManager : public Component
{
public:
	CMotionManager(int nPartsNum);				// �R���X�g���N�^
	~CMotionManager();									// �f�X�g���N�^

	void Update() override;								// �X�V
	void OnDestroyOtherObject(GameObject* other) override;								// �����C�x���g

	CMotionLayer* AddLayer(std::string	 LayerName);											// ���C���[�̒ǉ�
	void RemoveLayer(std::string	LayerName);														// ���C���[�̍폜
	CMotionLayer* FindLayer(std::string LayerName);											// ���C���[�̌���

	CMotionContents* AddContents(std::string ContentsName);								// �R���e���c�̒ǉ�
	void RemoveContents(std::string ContentsName);											// �R���e���c�̍폜
	CMotionContents* FindContents(std::string ContentsName);								// �R���e���c�̌���

	void Play(std::string ContentsName, std::string LayerName = "Base");				// �Đ�
	void Stop(std::string LayerName = "Base");														// ��~
	void Stop(CMotionLayer* pLayer);																	// ��~
	void StopAll();																								// ���ׂĒ�~

	void Resize(int nPartsNum);
	void SetParts(int nPartsIdx, GameObject* pParts);											// �p�[�c�̐ݒ�
	void SetOffset(const int& nPartsIdx, Transform offset);										// �I�t�Z�b�g�̐ݒ�
	std::vector<GameObject*>& GetParts() { return m_partsObject; }					// �p�[�c���X�g�̎擾
	std::vector<CMotionContents*>& GetContents() { return m_contents; }			// �R���e���c�̎擾
	Transform GetTransform(int nPartsIdx);															// �g�����X�t�H�[���l���擾

private:
	std::vector<CMotionLayer*> m_layer;								// ���C���[
	std::vector<CMotionLayer*> m_playingLayer;					// �Đ����̃��C���[�i�㔼�ɂ�������D�悳���j
	std::vector<CMotionContents*> m_contents;					// ���[�V�������e
	std::vector<GameObject*> m_partsObject;						// �p�[�c�̃g�����X�t�H�[���̃|�C���^
	std::vector<Transform> m_offset;									// �I�t�Z�b�g���
	std::vector<Transform> m_transform;							// �g�����X�t�H�[�����i���ʁj
	int m_nBlendFrame;														// �u�����h�t���[����
	int m_nPartsNum;															// �p�[�c��

	// ���[�V�����̏󋵃f�[�^
	struct MotionStateData
	{
		CMotionContents* pContents;
		int nKeyFrame;
		int nBlendCounter;
	};
	std::vector<MotionStateData> m_motionData;
	std::vector<MotionStateData> m_blendData;
};


#endif // !_MOTION_H_
