//========================================================================================================
//
//���[�V�����L���f���̏���[model_motion.cpp]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "model.h"

//========================================================================================================
//����������
//========================================================================================================
void MotionModel::Init()
{
	//
	this->Model::Init();

	//���[�V�����̐����J��Ԃ�
	for (unsigned int i = 0; i < this->m_vMotion.size(); i++)
	{
		//���[�V�����̏������������s��
		this->m_vMotion[i]->Init();
	}
}

//========================================================================================================
//�I������
//========================================================================================================
void MotionModel::Uninit()
{
	//
	this->Model::Uninit();

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
void MotionModel::Update()
{
	//���݃��[�V�����̍X�V�������s��
	int nNowMotion = this->m_nNowMotion;
	this->m_vMotion[nNowMotion]->Update();

	//�p�[�c�̐����J��Ԃ�
	for (int i = 0; i < this->GetNumParts(); i++)
	{
		//���[�V�����̃L�[�̏����p�[�c�ɐݒ肷��
		this->GetParts(i)->SetRot(this->m_vMotion[nNowMotion]->GetRot(i));
	}

	//
	this->Model::Update();
}

//=========================================================================================================
//�p�[�c�̓ǂݍ��ݏ���
//=========================================================================================================
void MotionModel::LoadMotion(const char* pPass)
{
	//�p�[�c��ǂݍ���
	this->LoadParts("data\\MOTION\\motion_player.txt");

	//�t�@�C�����J��
	FILE* pFile = fopen(pPass, "r");
	if (pFile != nullptr)
	{//�J����Ă���ꍇ
		char sText[128];   //�ǂݍ��񂾍s

		//-------------------------------------------------------------------------------------------------
		//���[�V������ǂݍ���
		//-------------------------------------------------------------------------------------------------
		while (1)
		{
			//�ǂݍ��񂾍s���m�F����
			if (fgets(sText, 128, pFile) == nullptr)
			{//�Ō�̍s�܂œǂݍ��񂾏ꍇ
				//���[�v�𔲂��o��
				break;
			}
			else if (strstr(sText, "MOTIONSET") != nullptr)
			{//���[�V�����̐ݒ�̏ꍇ
				//���[�V�����𐶐�����
				Motion* pMotion = new Motion;

				while (1)
				{
					//�ǂݍ��񂾍s���m�F����
					if (fgets(sText, 128, pFile) == nullptr)
					{//�Ō�̍s�܂œǂݍ��񂾏ꍇ
						//���[�v�𔲂��o��
						break;
					}
					else if (strstr(sText, "END_MOTIONSET") != nullptr)
					{//���[�V�����̏��̏I���̏ꍇ
						//���[�v�𔲂��o��
						break;
					}
					else if (strstr(sText, "LOOP") != nullptr)
					{//���[�v�t���O�̏ꍇ
						//���[�v�t���O��ǂݍ���
						int nLoop;
						sscanf(sText, "\tLOOP = %d", &nLoop);
						if (nLoop = 1)
						{//1�̏ꍇ
							//���[�v�t���O�𗧂Ă�
							pMotion->Loop();
						}
					}
					else if (strstr(sText, "KEYSET") != nullptr)
					{//�L�[�̐ݒ�̏ꍇ
						Motion::Key keyLoad;   //�ǂݍ��񂾃L�[�̕ۑ��p
						int nCntKey = 0;   //�L�[�̃J�E���^�[

						while (1)
						{
							//�ǂݍ��񂾍s���m�F����
							if (fgets(sText, 128, pFile) == nullptr)
							{//�Ō�̍s�܂œǂݍ��񂾏ꍇ
								//���[�v�𔲂��o��
								break;
							}
							else if (strstr(sText, "END_KEYSET") != nullptr)
							{//�L�[�̐ݒ�̏I���̏ꍇ
								//�ۑ������L�[��ݒ肷��
								pMotion->SetKey(keyLoad);

								//���[�v�𔲂��o��
								break;
							}
							else if (strstr(sText, "FRAME") != nullptr)
							{//�t���[���̏ꍇ
								//�t���[����ǂݍ���
								sscanf(sText, "\t\tFRAME = %d", &keyLoad.nFrame);
							}
							else if (strstr(sText, "KEY\t") != nullptr)
							{//�L�[�̏ꍇ
								//���̍s��ǂݍ���
								fgets(sText, 128, pFile);
								sscanf(sText, "\t\t\tPOS = %f %f %f", &keyLoad.pos[nCntKey].x, &keyLoad.pos[nCntKey].y, &keyLoad.pos[nCntKey].z);   //�ʒu��ۑ�

								//���̍s��ǂݍ���
								fgets(sText, 128, pFile);
								sscanf(sText, "\t\t\tROT = %f %f %f", &keyLoad.rot[nCntKey].x, &keyLoad.rot[nCntKey].y, &keyLoad.rot[nCntKey].z);   //�ʒu��ۑ�

								//�L�[�̃J�E���^�[��i�߂�
								nCntKey++;
							}
						}
					}
				}

				//���[�V������ۑ�����
				this->m_vMotion.push_back(pMotion);
			}
		}

		//�t�@�C�������
		fclose(pFile);
	}

	//�p�[�c�̐����J��Ԃ�
	for (unsigned int i = 0; i < this->m_vMotion.size(); i++)
	{
		//���[�V�����̏������������s��
		this->m_vMotion[i]->Init();
	}
}