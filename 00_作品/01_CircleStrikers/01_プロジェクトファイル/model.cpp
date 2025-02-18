//========================================================================================================
//
//���f������[model.cpp]
// Author Murata Shinnosuke
//
//========================================================================================================
#include "model.h"
#include "manager.h"
#include "object.h"
#include "transform.h"

//========================================================================================================
//����������
//========================================================================================================
void Model::Init()
{
	//�p�[�c�̐����J��Ԃ�
	for (unsigned int i = 0; i < this->m_vParts.size(); i++)
	{
		//�p�[�c�̏������������s��
		this->m_vParts[i]->Init();
	}
}

//========================================================================================================
//�I������
//========================================================================================================
void Model::Uninit()
{
	//�p�[�c�̐����J��Ԃ�
	for (unsigned int i = 0; i < this->m_vParts.size(); i++)
	{
		//�p�[�c�̏I���������s��
		this->m_vParts[i]->Uninit();
		delete this->m_vParts[i];
	}

	//�p�[�c���폜����
	this->m_vParts.clear();
}

//========================================================================================================
//�X�V����
//========================================================================================================
void Model::Update()
{
	//�p�[�c�̐����J��Ԃ�
	for (unsigned int i = 0; i < this->m_vParts.size(); i++)
	{
		//�p�[�c�̍X�V�������s��
		this->m_vParts[i]->Update();
	}
}

//========================================================================================================
//�`�揈��
//========================================================================================================
void Model::Draw()
{
	//�p�[�c�̐����J��Ԃ�
	for (unsigned int i = 0; i < this->m_vParts.size(); i++)
	{
		D3DXMATRIX mtxWorld;   //���[���h�}�g���b�N�X

		//�e�̔ԍ����擾����
		int nIdParent = this->m_vParts[i]->GetIdParent();
		if (nIdParent == -1)
		{//�e�����Ȃ��ꍇ
			//���[���h�}�g���b�N�X���擾����
			mtxWorld = this->GetObj()->GetComponent<Transform>()->GetMtxWorld();
		}
		else
		{//�e������ꍇ
			//�e�̏����擾����
			mtxWorld = this->m_vParts[nIdParent]->GetMtxWorld();
		}

		//�p�[�c�̕`�揈�����s��
		this->m_vParts[i]->Draw(mtxWorld);
	}
}

//========================================================================================================
//X�t�@�C���̐ݒ菈��
//========================================================================================================
void Model::SetXFile(XFile::Mesh mesh)
{
	//�p�[�c�𐶐�����
	Parts* pParts = new Parts;
	pParts->SetXFile(mesh);

	//�p�[�c��ۑ�����
	this->m_vParts.push_back(pParts);
}

//========================================================================================================
//�p�[�c�̓ǂݍ��ݏ���
//========================================================================================================
void Model::LoadParts(const char* pPass)
{
	//�t�@�C�����J��
	FILE* pFile = fopen(pPass, "r");
	if (pFile != nullptr)
	{//�J����Ă���ꍇ
		char sText[128];   //�ǂݍ��񂾍s

		//------------------------------------------------------------------------------------------------
		//�p�[�c�̃��f���̓ǂݍ���
		//------------------------------------------------------------------------------------------------
		while (1)
		{
			//�ǂݍ��񂾍s���m�F����
			if (fgets(sText, 128, pFile) == nullptr)
			{//�Ō�̍s�܂œǂݍ��񂾏ꍇ
				//���[�v�𔲂��o��
				break;
			}
			else if (strstr(sText, "MODEL_FILENAME") != nullptr)
			{//���f���̃p�X�̏ꍇ
				//�p�X��ǂݍ���
				char sPass[128];   //�p�X�̕ۑ��p
				sscanf(sText, "MODEL_FILENAME = %s", &sPass);   //�p�X

				//�p�[�c�𐶐�����
				Parts* pParts = new Parts;
				pParts->SetXFile(Manager::Get()->GetXFile()->Get(sPass));

				//�p�[�c��ۑ�����
				this->m_vParts.push_back(pParts);
			}
		}

		//�ǂݎ��s���ŏ��ɖ߂�
		fseek(pFile, 0, SEEK_SET);

		//------------------------------------------------------------------------------------------------
		//�p�[�c�̏��̓ǂݍ���
		//------------------------------------------------------------------------------------------------
		int nCnt = 0;
		while (1)
		{
			//�ǂݍ��񂾍s���m�F����
			if (fgets(sText, 128, pFile) == nullptr)
			{//�Ō�̍s�܂œǂݍ��񂾏ꍇ
				//���[�v�𔲂��o��
				break;
			}
			else if (strstr(sText, "PARTSSET") != nullptr)
			{//�p�[�c�̏��̏ꍇ
				while (1)
				{
					//�ǂݍ��񂾍s���m�F����
					if (fgets(sText, 128, pFile) == nullptr)
					{//�Ō�̍s�܂œǂݍ��񂾏ꍇ
						//���[�v�𔲂��o��
						break;
					}
					if (strstr(sText, "END_PARTSSET") != nullptr)
					{//�p�[�c�̏��̏I���̏ꍇ
						//�ԍ���ݒ肷��
						this->m_vParts[nCnt]->SetId(nCnt);

						//�J�E���^�[��i�߂�
						nCnt++;

						//���[�v�𔲂��o��
						break;
					}
					else if (strstr(sText, "PARENT") != nullptr)
					{//�e�̔ԍ��̏ꍇ
						//�e�̔ԍ���ǂݍ���
						int nIdParent = -1;
						sscanf(sText, "\t\tPARENT = %d", &nIdParent);
						this->m_vParts[nCnt]->SetIdParent(nIdParent);
					}
					else if (strstr(sText, "POS") != nullptr)
					{//�ʒu�̏ꍇ
						//�ʒu��ǂݍ���
						D3DXVECTOR3 pos = { 0.0f, 0.0f, 0.0f };
						sscanf(sText, "\t\tPOS = %f %f %f", &pos.x, &pos.y, &pos.z);   //�ʒu
						this->m_vParts[nCnt]->SetPos(pos);
					}
					else if (strstr(sText, "ROT") != nullptr)
					{//�����̏ꍇ
						//������ǂݍ���
						D3DXVECTOR3 rot = { 0.0f, 0.0f, 0.0f };
						sscanf(sText, "\t\tROT = %f %f %f", &rot.x, &rot.y, &rot.z);   //�ʒu
						this->m_vParts[nCnt]->SetRot(rot);
					}
				}
			}

			//�J�E���^�[���m�F����
			if ((unsigned int)nCnt >= this->m_vParts.size())
			{
				//���[�v�𔲂��o��
				break;
			}
		}

		//�t�@�C�������
		fclose(pFile);
	}

	//�p�[�c�̐����J��Ԃ�
	for (unsigned int i = 0; i < this->m_vParts.size(); i++)
	{
		//�p�[�c�̏������������s��
		this->m_vParts[i]->Init();
	}
}

//========================================================================================================
//�e�N�X�`���̐ݒ菈��
//========================================================================================================
void Model::SetTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	//�p�[�c�̐����J��Ԃ�
	for (unsigned int i = 0; i < this->m_vParts.size(); i++)
	{
		//�e�N�X�`����ݒ肷��
		this->m_vParts[i]->SetTexture(pTexture);
	}
}