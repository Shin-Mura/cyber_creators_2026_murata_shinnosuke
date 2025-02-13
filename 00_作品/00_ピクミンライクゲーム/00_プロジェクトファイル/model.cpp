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
void Model::LoadParts(std::string sFileName)
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
		if (sLine.find("MODEL_FILENAME = data/MODEL/") != std::string::npos)
		{//���f���̃p�X�̏ꍇ
			//���f���̃t�@�C������ۑ�����
			char aNameModel[128];
			sscanf(sLine.c_str(), "MODEL_FILENAME = data/MODEL/%s", &aNameModel);
			std::string sNameModel = aNameModel;

			//�p�[�c�𐶐�����
			Parts* pParts = new Parts;
			pParts->SetXFile(Manager::Get()->GetXFile()->Get(sNameModel));

			//�p�[�c��ۑ�����
			this->m_vParts.push_back(pParts);
		}
		else if (sLine.find("CHARACTERSET") != std::string::npos)
		{//�L�����N�^�[�ݒ�̏ꍇ
			//�t�@�C����ǂݍ���
			int nCntParts = 0;   //�ǂݍ��񂾃p�[�c�̐�
			while (std::getline(file, sLine))
			{
				if (sLine.find("END_CHARACTERSET") != std::string::npos)
				{//�L�����N�^�[�ݒ�̏I���̏ꍇ
					//���[�v�𔲂��o��
					break;
				}
				if (sLine.find("PARTSSET") != std::string::npos)
				{//�p�[�c�̐ݒ�̏ꍇ
					//�p�[�c�ݒ�̏I���܂œǂݍ���
					while (std::getline(file, sLine))
					{
						//�ǂݍ��񂾍s���m�F����
						if (sLine.find("END_PARTSSET") != std::string::npos)
						{//�p�[�c�ݒ�̏I���̏ꍇ
							//���[�v�𔲂��o��
							break;
						}
						else if (sLine.find("PARENT = ") != std::string::npos)
						{//�e�̔ԍ��̏ꍇ
							//�e�̔ԍ���ݒ肷��
							std::string sIdParent = sLine.substr(sLine.find("PARENT = "));
							int nIdParent = -1;
							sscanf(sIdParent.c_str(), "PARENT = %d", &nIdParent);
							this->m_vParts[nCntParts]->SetIdParent(nIdParent);
						}
						else if (sLine.find("POS = ") != std::string::npos)
						{//�ʒu�̏ꍇ
							//�ʒu��ݒ肷��
							std::string sPos = sLine.substr(sLine.find("POS = "));
							D3DXVECTOR3 pos = { 0.0f, 0.0f, 0.0f };
							sscanf(sPos.c_str(), "POS = %f %f %f", &pos.x, &pos.y, &pos.z);
							this->m_vParts[nCntParts]->SetPos(pos);
						}
						else if (sLine.find("ROT = ") != std::string::npos)
						{//�����̏ꍇ
							//������ݒ肷��
							std::string sRos = sLine.substr(sLine.find("ROT = "));
							D3DXVECTOR3 rot = { 0.0f, 0.0f, 0.0f };
							sscanf(sRos.c_str(), "ROT = %f %f %f", &rot.x, &rot.y, &rot.z);
							this->m_vParts[nCntParts]->SetRot(rot);
						}
					}

					//�ԍ���ݒ肷��
					this->m_vParts[nCntParts]->SetId(nCntParts);
					nCntParts++;   //�J�E���^�[��i�߂�
				}
			}
		}
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