//========================================================================================================
//
//���[�V���i�[�̏���[motioneer.h]
// Author MurataShinnosuke
//
//========================================================================================================
#ifndef _MOTIONEER_H_
#define _MOTIONEER_H_

#include "component.h"
#include "motion.h"

//�O���錾
class Model;   //���f��
//���[�V���i�[
class Motioneer : public Component
{
public:
	//�R���X�g���N�^
	Motioneer(Object* pObject) : Component(pObject)
	{
		//�����o�ϐ�������������
		this->m_vMotion.clear();    //���[�V�����̃R���e�i
		this->m_nMotionPlay = 0;   //�Đ����̃��[�V�����̔ԍ�
		this->m_pModel = nullptr;   //���f��
	}

	//�f�X�g���N�^
	~Motioneer()
	{

	}

	void Init();   //����������
	void Uninit();   //�I������
	void Update();   //�X�V����
	void LoadMotion(std::string sFileName);   //���[�V�����̓ǂݍ��ݏ���

	//���[�V�����̍Đ�����
	void StartMotion(int nId)
	{
		//���[�V�����̔ԍ����m�F����
		if (nId != this->m_nMotionPlay)
		{//���݃��[�V�����ƈႤ�ꍇ
			//���݂̃��[�V�����ɓK�p����
			this->m_nMotionPlay = nId;

			//���[�V���������Z�b�g����
			this->m_vMotion[this->m_nMotionPlay]->Reset();
		}
	}

private:
	std::vector<Motion*> m_vMotion;   //���[�V�����̃R���e�i
	int m_nMotionPlay;   //�Đ����̃��[�V����
	Model* m_pModel;   //���f��
};

#endif // !_MOTIONEER_H_