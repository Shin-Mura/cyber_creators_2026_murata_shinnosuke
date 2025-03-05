//========================================================================================================
//
//���f������[model.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "rendering.h"
#include "Xfile.h"
#include "parts.h"
#include "motion.h"

//���f��
class Model : public Rendering   //(�e)�R���|�[�l���g
{
public:
	//�R���X�g���N�^
	Model(Object* pObject) : Rendering(pObject)
	{
		//�����o�ϐ�������������
		this->m_vParts.clear();
	}

	//�f�X�g���N�^
	virtual ~Model() override
	{
	}

	virtual void Init() override;   //����������
	virtual void Uninit() override;   //�I������
	virtual void Update() override;   //�X�V����
	virtual void Draw() override;   //�`�揈��
	void LoadParts(const char* pPass);   //�p�[�c�̓ǂݍ��ݏ���

	void SetXFile(XFile::Mesh mesh);   //X�t�@�C���̐ݒ菈��
	void SetTexture(LPDIRECT3DTEXTURE9 pTexture);

	Parts* GetParts(int nId) { return this->m_vParts[nId]; };   //�p�[�c�̎擾����	
	int GetNumParts() { return this->m_vParts.size(); };   //�p�[�c�̐��̎擾����

private:
	std::vector<Parts*> m_vParts;   //�p�[�c
};

//���[�V�����L�胂�f��
class MotionModel : public Model
{
public:
	//�R���X�g���N�^
	MotionModel(Object* pObject) : Model(pObject)
	{
		//�����o�ϐ�������������
		this->m_nNowMotion = 0;
		this->m_vMotion.clear();
	}

	//�f�X�g���N�^
	~MotionModel() override
	{
	}

	virtual void Init() override;   //����������
	virtual void Uninit() override;   //�I������
	virtual void Update() override;   //�X�V����
	virtual void Draw() override { this->Model::Draw(); };   //�`�揈��

protected:
	void LoadMotion(const char* pPass);   //���[�V�����̓ǂݍ��ݏ���

	//���[�V�����̍Đ�����
	void StartMotion(int nId)
	{
		//���[�V�����̔ԍ����m�F����
		if (nId != this->m_nNowMotion)
		{//���݃��[�V�����ƈႤ�ꍇ
			//���݂̃��[�V�����ɓK�p����
			this->m_nNowMotion = nId;

			//���[�V���������Z�b�g����
			this->m_vMotion[this->m_nNowMotion]->Reset();
		}
	}

private:
	int m_nNowMotion;   //�Đ������[�V����
	std::vector<Motion*> m_vMotion;   //���[�V����
};

#endif // !_MODEL_H_
