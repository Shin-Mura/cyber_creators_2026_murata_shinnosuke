//========================================================================================================
//
//���[�V���i�[�̏���[motioneer.cpp]
// Author MurataShinnosuke
//
//========================================================================================================
#include "motioneer.h"
#include "object.h"
#include "model.h"
#include "behavior.h"

//========================================================================================================
//����������
//========================================================================================================
void Motioneer::Init()
{
}

//========================================================================================================
//�I������
//========================================================================================================
void Motioneer::Uninit()
{
	//���[�V�����̐����J��Ԃ�
	for (unsigned int i = 0; i < this->m_vMotion.size(); i++)
	{
		//���[�V�����̏I���������s��
		this->m_vMotion[i]->Uninit();
		delete this->m_vMotion[i];
	}

	//���[�V�������폜����
	this->m_vMotion.clear();
}

//========================================================================================================
//�X�V����
//========================================================================================================
void Motioneer::Update()
{
	//���f�����m�F����
	if (this->m_pModel == nullptr)
	{
		//���f�����擾����
		this->m_pModel = this->GetObj()->GetComponent<Model>();

		//���[�V�����̐����J��Ԃ�
		for (unsigned int i = 0; i < this->m_vMotion.size(); i++)
		{
			//���[�V�����Ƀp�[�c����ݒ肷��
			this->m_vMotion[i]->SetNumParts(this->m_pModel->GetNumParts());
		}
	}

	//���݃��[�V�����̍X�V�������s��
	this->m_vMotion[this->m_nMotionPlay]->Update();
	if (this->m_vMotion[this->m_nMotionPlay]->GetEnd())
	{//���[�V�������I�������ꍇ
		//���[�V�����̏I�����̏������s��
		this->GetObj()->GetComponent<Behavior>()->EndMotion();
	}

	//�p�[�c�̐����J��Ԃ�
	for (int i = 0; i < this->m_pModel->GetNumParts(); i++)
	{
		//���[�V�����̃L�[�̏����p�[�c�ɐݒ肷��
		this->m_pModel->GetParts(i)->SetRot(this->m_vMotion[this->m_nMotionPlay]->GetRot(i));
	}
}

//=========================================================================================================
//���[�V�����̓ǂݍ��ݏ���
//=========================================================================================================
void Motioneer::LoadMotion(std::string sFileName)
{
	//�p�X�Ƀt�@�C�����𑫂�
	std::string sPass = "data\\MOTION\\";
	sPass += sFileName;

	//�ǂݍ��ރt�@�C�����w�肷��
	std::ifstream file(sPass);

	//�t�@�C����ǂݍ���
	std::string sLine;
	while (std::getline(file, sLine))
	{
		//�ǂݍ��񂾍s���m�F����
		if (sLine.find("MOTIONSET") != std::string::npos)
		{//���[�V�����̐ݒ�̏ꍇ
			//���[�V�����𐶐�����
			Motion* pMotion = new Motion;

			//�t�@�C����ǂݍ���
			while (std::getline(file, sLine))
			{
				//�ǂݍ��񂾍s���m�F����
				if (sLine.find("END_MOTIONSET") != std::string::npos)
				{//���[�V�����̐ݒ�̏I���̏ꍇ
					//���[�v�𔲂��o��
					break;
				}
				else if (sLine.find("LOOP = ") != std::string::npos)
				{//���[�v�̏ꍇ
					//���[�v�̒l���m�F����
					std::string sLoop = sLine.substr(sLine.find("LOOP = "));
					int nLoop;
					sscanf(sLoop.c_str(), "LOOP = %d", &nLoop);
					if (nLoop == 1)
					{
						//���[�v�ɐݒ肷��
						pMotion->Loop();
					}
				}
				else if (sLine.find("KEYSET") != std::string::npos) 
				{//�L�[�̐ݒ�
					Motion::Key key;   //�ǂݍ��񂾃L�[���̕ۑ��p
					int nCntKey = 0;   //�ǂݍ��񂾃L�[�̐�

					//�t�@�C����ǂݍ���
					while (std::getline(file, sLine))
					{
						//�ǂݍ��񂾍s���m�F����
						if (sLine.find("END_KEYSET") != std::string::npos)
						{
							//���[�v�𔲂��o��
							break;
						}
						else if (sLine.find("FRAME = ") != std::string::npos)
						{//�t���[���̏ꍇ
							//�t���[����ǂݍ���
							std::string sFrame = sLine.substr(sLine.find("FRAME = "));
							int nFrame;
							sscanf(sFrame.c_str(), "FRAME = %d", &nFrame);
							key.nFrame = nFrame;
						}
						else if (sLine.find("KEY") != std::string::npos)
						{//�L�[�̏ꍇ
							//���̍s��ǂݍ���
							std::getline(file, sLine);
							std::string sPos = sLine.substr(sLine.find("POS = "));
							D3DXVECTOR3 pos;
							sscanf(sPos.c_str(), "POS = %f %f %f", &pos.x, &pos.y, &pos.z);   //�ʒu��ۑ�
							key.vPos.push_back(pos);

							//���̍s��ǂݍ���
							std::getline(file, sLine);
							std::string sRot = sLine.substr(sLine.find("ROT = "));
							D3DXVECTOR3 rot;
							sscanf(sRot.c_str(), "ROT = %f %f %f", &rot.x, &rot.y, &rot.z);   //�ʒu��ۑ�
							key.vRot.push_back(rot);

							//���̍s��ǂݍ���
							std::getline(file, sLine);
						}
					}

					//�L�[��ݒ肷��
					pMotion->AddKey(key);
				}
			}

			//���[�V������ۑ�����
			this->m_vMotion.push_back(pMotion);
		}
	}

	//�p�[�c�̐����J��Ԃ�
	for (unsigned int i = 0; i < this->m_vMotion.size(); i++)
	{
		//���[�V�����̏������������s��
		this->m_vMotion[i]->Init();
	}
}