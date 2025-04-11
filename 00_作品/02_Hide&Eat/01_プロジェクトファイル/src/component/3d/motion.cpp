//=============================================================
//
// ���[�V���� [motion.cpp]
// Author: Ito Kotaro
//
//=============================================================
#include "motion.h"
#include "manager.h"

//=============================================================
// [CMotionManager] �R���X�g���N�^
//=============================================================
CMotionManager::CMotionManager(int nPartsNum)
{
	// ���[�V�����ݒ�̏�����
	m_nBlendFrame = 8;

	// �p�[�c���̐ݒ�
	Resize(nPartsNum);
}

//=============================================================
// [CMotionManager] �f�X�g���N�^
//=============================================================
CMotionManager::~CMotionManager()
{
	// ���C���[��j������
	for (int i = 0; i < (int)m_layer.size(); i++)
	{
		if (m_layer[i] != nullptr)
		{
			delete m_layer[i];
			m_layer[i] = nullptr;
		}
	}
	m_layer.clear();

	// �Đ����̃��C���[����ɂ���
	m_playingLayer.clear();

	// �R���e���c��j������
	for (int i = 0; i < (int)m_contents.size(); i++)
	{
		if (m_contents[i] != nullptr)
		{
			delete m_contents[i];
			m_contents[i] = nullptr;
		}
	}
	m_contents.clear();
}

//=============================================================
// [CMotionManager] �X�V
//=============================================================
void CMotionManager::Update()
{
	if (CManager::GetInstance()->GetPause())
		return;

	// �Đ����̃��C���[���X�V����i�L�[��i�߂�j
	for (int i = 0; i < (int)m_playingLayer.size(); i++)
	{
		m_playingLayer[i]->Update();
	}

	// ���ꂼ��̃p�[�c�̃��[�V������������o��
	bool* bPlayedParts = new bool[m_nPartsNum];		// �Đ��ς݃p�[�c�i���C���[�ł̃p�[�c����h���j
	memset(bPlayedParts, false, sizeof(bool)*m_nPartsNum);

	for (int i = 0; i < (int)m_playingLayer.size(); i++)
	{
		// �ϐ��錾
		CMotionLayer* pLayer = m_playingLayer[(m_playingLayer.size() - 1) - i];		// �Ώۂ̃��C���[�i�Ōォ�珇�j
		std::vector<int> partsList = pLayer->GetPartsList();										// ���C���[�̃p�[�c���X�g���擾
		CMotionContents* contents = pLayer->GetPlayContents();									// �Đ����̃R���e���c���擾

		// �p�[�c���ƂɊ���o��
		for (int nCntParts = 0; nCntParts < (int)partsList.size(); nCntParts++)
		{
			// �Ώۃp�[�c���擾
			int nTargetIdx = partsList[nCntParts];
			if (!(0 <= nTargetIdx && nTargetIdx < m_nPartsNum))
				continue;	// �ΏۊO�̃p�[�c���X�L�b�v

			// �Ώۃp�[�c�����ɍĐ��ς݂ł͂Ȃ������m�F����
			if (bPlayedParts[nTargetIdx])
			{ // �Đ��ς݂̂Ƃ�
				continue;										// �p�[�c�X�L�b�v
			}
			else
			{ // ���Đ��̂Ƃ�
				bPlayedParts[nTargetIdx] = true;		// �Đ��ς݂ɕύX
			}

			// ���[�V�����f�[�^
			m_motionData[nTargetIdx].pContents = contents;
			m_motionData[nTargetIdx].nKeyFrame = pLayer->GetKeyFrame();
		}
	}

	// ���[�V�������ݒ肳��Ă��Ȃ��p�[�c�͏�����Ԃɂ���
	for (int i = 0; i < m_nPartsNum; i++)
	{
		if (!bPlayedParts[i])
		{ // ���[�V�������Đ�����Ă��Ȃ��Ƃ�
			m_motionData[i].pContents = nullptr;
			m_motionData[i].nKeyFrame = 0;
		}
	}

	// �u�����h����
	bool* bBlendParts = new bool[m_nPartsNum];		// �u�����h�p�[�c
	memset(bBlendParts, false, sizeof(bool) * m_nPartsNum);
	for (int i = 0; i < m_nPartsNum; i++)
	{
		if (m_blendData[i].nBlendCounter <= 0 &&
			m_motionData[i].pContents != m_blendData[i].pContents)
		{ // �O��ƈقȂ��Ă���Ƃ��i�u�����h����: ����̂݁j
			m_blendData[i].nBlendCounter = m_nBlendFrame;	// �u�����h�J�E���^�[���u�����h�t���[�����ɐݒ肷��
		}

		// �u�����h����Ƃ�
		if (m_blendData[i].nBlendCounter > 0)
		{
			// �J�E���^�[�����炷
			m_blendData[i].nBlendCounter--;

			// �u�����h��1�t���[���X�V����
			m_blendData[i].nKeyFrame++;

			// �ő�t���[���ɓ��B�����Ƃ�
			if (m_blendData[i].pContents != nullptr &&
				m_blendData[i].nKeyFrame > m_blendData[i].pContents->GetMaxFrame())
			{
				if (m_blendData[i].pContents->GetLoop())
				{ // ���[�v�̂Ƃ�
					m_blendData[i].nKeyFrame = 0;
				}
				else
				{ // ���[�v���Ȃ��Ƃ�
					m_blendData[i].nKeyFrame = m_blendData[i].pContents->GetMaxFrame();
				}
			}

			bBlendParts[i] = true;

			// �u�����h�̍Ō�܂œ��B�����Ƃ��A�u�����h�f�[�^���ŐV�f�[�^�ɍX�V����
			if (m_blendData[i].nBlendCounter <= 0)
			{
				m_blendData[i].pContents = m_motionData[i].pContents;
				m_blendData[i].nKeyFrame = m_motionData[i].nKeyFrame;
			}
		}
	}



	// ���[�V�����f�[�^�����Ƀg�����X�t�H�[�������i�[����
	for (int i = 0; i < m_nPartsNum; i++)
	{
		// �ϐ�
		Transform normalTransform, blendTransform;

		// �ʏ�l���i�[����
		if (m_motionData[i].pContents != nullptr)
		{ // ���[�V�������̃f�[�^���L��Ƃ�
			normalTransform = m_motionData[i].pContents->GetTransform(i, m_motionData[i].nKeyFrame);
		}

		// �u�����h�l���i�[����
		if (bBlendParts[i] &&
			m_blendData[i].pContents != nullptr)
		{ // �u�����h���̂Ƃ�
			blendTransform = m_blendData[i].pContents->GetTransform(i, m_blendData[i].nKeyFrame);
		}

		// �g�����X�t�H�[���l��������
		if (bBlendParts[i])
		{ // �u�����h���̂Ƃ�
			Transform resultTransform;	// �u�����h�ς݂̃g�����X�t�H�[��

			// �u�����h�̌v�Z
			resultTransform.SetPos(
				normalTransform.GetPos() * (float)((m_nBlendFrame - m_blendData[i].nBlendCounter) / (float)m_nBlendFrame) +
				blendTransform.GetPos() * (float)(m_blendData[i].nBlendCounter / (float)m_nBlendFrame)
			);

			resultTransform.SetRot(
				normalTransform.GetRot()* (float)((m_nBlendFrame - m_blendData[i].nBlendCounter) / (float)m_nBlendFrame) +
				blendTransform.GetRot() * (float)(m_blendData[i].nBlendCounter / (float)m_nBlendFrame)
			);

			resultTransform.SetScale(
				normalTransform.GetScale()* (float)((m_nBlendFrame - m_blendData[i].nBlendCounter) / (float)m_nBlendFrame) +
				blendTransform.GetScale() * (float)(m_blendData[i].nBlendCounter / (float)m_nBlendFrame)
			);


			// �I�t�Z�b�g�����Z����
			resultTransform.SetPos(resultTransform.GetPos() + m_offset[i].GetPos());		// �ʒu
			resultTransform.SetRot(resultTransform.GetRot() + m_offset[i].GetRot());		// ��]
			resultTransform.SetScale(																			// �X�P�[��
				resultTransform.GetScale().x * m_offset[i].GetScale().x,
				resultTransform.GetScale().y * m_offset[i].GetScale().y,
				resultTransform.GetScale().z * m_offset[i].GetScale().z
			);

			// �g�����X�t�H�[���ɑ������
			m_transform[i].SetPos(resultTransform.GetPos());
			m_transform[i].SetRot(resultTransform.GetRot());
			m_transform[i].SetScale(resultTransform.GetScale());
		}
		else
		{ // �u�����h���Ă��Ȃ��Ƃ�
			m_transform[i].SetPos(normalTransform.GetPos() + m_offset[i].GetPos());		// �ʒu
			m_transform[i].SetRot(normalTransform.GetRot() + m_offset[i].GetRot());		// ��]
			m_transform[i].SetScale(																			// �X�P�[��
				normalTransform.GetScale().x * m_offset[i].GetScale().x,
				normalTransform.GetScale().y * m_offset[i].GetScale().y,
				normalTransform.GetScale().z * m_offset[i].GetScale().z
			);
		}
	}

	// �ݒ肳��Ă���p�[�c�ɓK�p����
	for (int i = 0; i < m_nPartsNum; i++)
	{
		if (m_partsObject[i] != nullptr)
		{
			m_partsObject[i]->transform->SetPos(m_transform[i].GetPos());
			m_partsObject[i]->transform->SetRot(m_transform[i].GetRot());
			m_partsObject[i]->transform->SetScale(m_transform[i].GetScale());
		}
	}


	// �u�����h�̂��߂ɏ���ۑ����Ă���
	for (int i = 0; i < m_nPartsNum; i++)
	{
		if (!bBlendParts[i])
		{ // �u�����h���̃p�[�c�ȊO���X�V����
			m_blendData[i].pContents = m_motionData[i].pContents;
			m_blendData[i].nKeyFrame = m_motionData[i].nKeyFrame;
		}
	}

	// �쐬�����ϐ���j������
	delete[] bPlayedParts;
	bPlayedParts = nullptr;
	delete[] bBlendParts;
	bBlendParts = nullptr;
}

//=============================================================
// [CMotionManager] �����C�x���g
//=============================================================
void CMotionManager::OnDestroyOtherObject(GameObject* other)
{
	for (int nCntParts = 0; nCntParts < (int)m_partsObject.size(); nCntParts++)
	{ // �p�[�c��J��Ԃ�
		if (m_partsObject[nCntParts] == other)
		{ // �Q�[���I�u�W�F�N�g����v�����ꍇ
			m_partsObject[nCntParts] = nullptr;	// ����
		}
	}
}

//=============================================================
// [CMotionManager] �T�C�Y�ύX
//=============================================================
void CMotionManager::Resize(int nPartsNum)
{
	// �p�[�c���̐ݒ�
	m_nPartsNum = nPartsNum;
	m_transform.resize(m_nPartsNum);
	m_partsObject.resize(m_nPartsNum);
	m_offset.resize(m_nPartsNum);
	m_motionData.resize(m_nPartsNum);
	m_blendData.resize(m_nPartsNum);

	for (int i = 0; i < (int)m_contents.size(); i++)
	{
		m_contents[i]->GetKey().resize(nPartsNum);
	}

	for (int i = 0; i < m_nPartsNum; i++)
	{
		m_partsObject[i] = nullptr;
	}

	// �x�[�X���C���[�̒ǉ�
	CMotionLayer* pLayer = AddLayer("Base");
	for (int i = 0; i < m_nPartsNum; i++)
		pLayer->AddParts(i);
}

//=============================================================
// [CMotionManager] ���C���[�̒ǉ�
//=============================================================
CMotionLayer* CMotionManager::AddLayer(std::string LayerName)
{
	// �������O�̃��C���[�����݂��Ȃ������m�F����
	CMotionLayer* pFindLayer = FindLayer(LayerName);
	if (pFindLayer) return pFindLayer;	// ���ɑ��݂��Ă���

	// ���[�V�������C���[�̍쐬
	CMotionLayer* layer = new CMotionLayer(&m_nBlendFrame);

	// ���C���[�̐ݒ���s��
	layer->SetName(LayerName);

	// ���C���[��o�^����
	m_layer.push_back(layer);

	return layer;
}

//=============================================================
// [CMotionManager] ���C���[�̍폜
//=============================================================
void CMotionManager::RemoveLayer(std::string LayerName)
{
	// ���C���[�𖼑O�������Ď擾
	CMotionLayer* pLayer = FindLayer(LayerName);
	if (!pLayer) return;	// ���s

	// �Ώۂ��x�[�X���C���[�ł͂Ȃ����m�F����
	if (LayerName == "Base")
		return;	// �x�[�X���C���[�̏ꍇ�͏I��

	// ��v���郌�C���[��o�^����
	for (int i = 0; i < (int)m_layer.size(); i++)
	{
		if (m_layer[i] == pLayer)
		{
			m_layer.erase(m_layer.begin() + i);
			break;
		}
	}

	// ���C���[��j������
	delete pLayer;
}

//=============================================================
// [CMotionManager] ���C���[�̌���
//=============================================================
CMotionLayer* CMotionManager::FindLayer(std::string LayerName)
{
	// �o�^����Ă��郌�C���[���疼�O����v������̂�Ԃ�
	for (int i = 0; i < (int)m_layer.size(); i++)
	{
		CMotionLayer* target = m_layer[i];

		if (LayerName == target->GetName())
		{	// ���O����v�����Ƃ�
			return target;		// �Ώۃ��C���[��Ԃ�
		}
	}

	// ������Ȃ������Ƃ�
	return nullptr;
}

//=============================================================
// [CMotionManager] �R���e���c�̒ǉ�
//=============================================================
CMotionContents* CMotionManager::AddContents(std::string ContentsName)
{
	// ���O���d�����Ă��Ȃ���
	for (int i = 0; i < (int)m_contents.size(); i++)
	{
		if (m_contents[i]->GetName() == ContentsName)
		{ // ���O���d�����Ă����ꍇ
			return nullptr;	// �X���[
		}
	}

	// ���[�V�����R���e���c�̍쐬
	CMotionContents* contents = new CMotionContents(m_nPartsNum);

	// ���C���[�̐ݒ���s��
	contents->SetName(ContentsName);

	// ���C���[��o�^����
	m_contents.push_back(contents);

	return contents;
}

//=============================================================
// [CMotionManager] �R���e���c�̍폜
//=============================================================
void CMotionManager::RemoveContents(std::string ContentsName)
{
	// �R���e���c�𖼑O�������Ď擾
	CMotionContents* pContents = FindContents(ContentsName);
	if (!pContents) return;	// ���s

	// ��v����R���e���c��o�^����
	for (int i = 0; i < (int)m_contents.size(); i++)
	{
		if (m_contents[i] == pContents)
		{
			m_contents.erase(m_contents.begin() + i);
			break;
		}
	}

	// �R���e���c��j������
	delete pContents;
}

//=============================================================
// [CMotionManager] �R���e���c�̌���
//=============================================================
CMotionContents* CMotionManager::FindContents(std::string ContentsName)
{
	// �o�^����Ă���R���e���c���疼�O����v������̂�Ԃ�
	for (int i = 0; i < (int)m_contents.size(); i++)
	{
		CMotionContents* target = m_contents[i];

		if (ContentsName == target->GetName())
		{	// ���O����v�����Ƃ�
			return target;		// �ΏۃR���e���c��Ԃ�
		}
	}

	// ������Ȃ������Ƃ�
	return nullptr;
}

//=============================================================
// [CMotionManager] �Đ�
//=============================================================
void CMotionManager::Play(std::string ContentsName, std::string LayerName)
{
	// �w�肳�ꂽ���C���[���擾����
	CMotionLayer* pLayer = FindLayer(LayerName);
	if (!pLayer) return; // ���s

	// �w�肳�ꂽ���[�V�������擾����
	CMotionContents* pContent = FindContents(ContentsName);
	if (!pContent) return; // ���s

	// ���C���[�̍Đ����[�V�����ɐݒ肷��
	pLayer->SetMotion(pContent);

	// �v���C���̂Ƃ��͒�~����
	Stop(pLayer);

	// �v���C���̃��C���[�ɒǉ�����
	m_playingLayer.push_back(pLayer);
}

//=============================================================
// [CMotionManager] ��~
//=============================================================
void CMotionManager::Stop(std::string LayerName)
{
	// �w�肳�ꂽ���C���[���擾����
	CMotionLayer* pLayer = FindLayer(LayerName);
	if (!pLayer) return; // ���s

	// �v���C���̃��C���[�ɓ����Ă���Ƃ��̏���
	for (int i = 0; i < (int)m_playingLayer.size(); i++)
	{
		if (m_playingLayer[i] == pLayer)
		{ // �����Ă����Ƃ�
			m_playingLayer.erase(m_playingLayer.begin() + i);	// ���X�g����폜����
			return;
		}
	}
}
void CMotionManager::Stop(CMotionLayer* pLayer)
{
	// NULL�`�F�b�N
	if (!pLayer) return; // ���s

	// �v���C���̃��C���[�ɓ����Ă���Ƃ��̏���
	for (int i = 0; i < (int)m_playingLayer.size(); i++)
	{
		if (m_playingLayer[i] == pLayer)
		{ // �����Ă����Ƃ�
			m_playingLayer.erase(m_playingLayer.begin() + i);	// ���X�g����폜����
			return;
		}
	}
}

//=============================================================
// [CMotionManager] ���ׂĒ�~
//=============================================================
void CMotionManager::StopAll()
{
	// �Đ����̃��C���[����ɂ���
	m_playingLayer.clear();
}

//=============================================================
// [CMotionManager] �p�[�c�̐ݒ�
//=============================================================
void CMotionManager::SetParts(int nPartsIdx, GameObject* pParts)
{
	if (!(0 <= nPartsIdx && nPartsIdx < m_nPartsNum))
		return;	// �p�[�c�̍ő�l�𒴂��Ă���

	// �p�[�c�̐ݒ���s��
	m_partsObject[nPartsIdx] = pParts;
}

//=============================================================
// [CMotionManager] �I�t�Z�b�g�̐ݒ�
//=============================================================
void CMotionManager::SetOffset(const int& nPartsIdx, Transform offset)
{
	if (!(0 <= nPartsIdx && nPartsIdx < m_nPartsNum))
		return;	// �p�[�c�̍ő�l�𒴂��Ă���

	// �I�t�Z�b�g�̐ݒ���s��
	m_offset[nPartsIdx].SetPos(offset.GetPos());
	m_offset[nPartsIdx].SetRot(offset.GetRot());
	m_offset[nPartsIdx].SetScale(offset.GetScale());
}

//=============================================================
// [CMotionManager] �g�����X�t�H�[���l���擾
//=============================================================
Transform CMotionManager::GetTransform(int nPartsIdx)
{
	// �p�[�c�̃C���f�b�N�X���ő�l�𒴂��Ă��邩
	if (!(0 <= nPartsIdx && nPartsIdx < m_nPartsNum))
		return Transform();	// �����Ă���Ƃ�

	// �g�����X�t�H�[���l��Ԃ�
	return m_transform[nPartsIdx];
}



//=============================================================
// [CMotionLayer] �R���X�g���N�^
//=============================================================
CMotionLayer::CMotionLayer(int* pBlendFrame)
{
	// �ϐ�������������
	strcpy(&m_name[0], "");
	m_pPlayContents = nullptr;
	m_nKeyFrame = 0;
	m_nBlendCounter = 0;
	m_pBeforeContents = nullptr;
	m_nBeforeKeyFrame = 0;
	m_pBlendFrame = pBlendFrame;
	m_bEnded = true;
}

//=============================================================
// [CMotionLayer] �X�V�i�L�[��i�߂�j
//=============================================================
void CMotionLayer::Update()
{
	if (m_pPlayContents == nullptr)
		return;	// �Đ����̃��[�V�������Ȃ��Ƃ��͏I��

	// �L�[��i�߂�
	m_nKeyFrame++;
	
	// �L�[���ő�t���[���ɒB�����Ƃ�
	if (m_pPlayContents->GetMaxFrame() <= m_nKeyFrame)
	{
		if (m_pPlayContents->GetLoop())
		{ // ���[�v����Ƃ�
			m_nKeyFrame = 0;												// �L�[��0�ɖ߂�
		}
		else
		{ // ���[�v���Ȃ��Ƃ�
			m_nKeyFrame = m_pPlayContents->GetMaxFrame();	// �ő�t���[���ɃL�[��ύX
			m_bEnded = true;
		}
	}
}

//=============================================================
// [CMotionLayer] �p�[�c�̒ǉ�
//=============================================================
void CMotionLayer::AddParts(int nPartsIdx)
{
	// �p�[�c�����ɓo�^����Ă��Ȃ������m�F����
	for (int i = 0; i < (int)m_partsIdx.size(); i++)
	{
		if (m_partsIdx[i] == nPartsIdx)
		{ // ���������ꍇ
			return;
		}
	}

	// �p�[�c��o�^����
	m_partsIdx.push_back(nPartsIdx);
}

//=============================================================
// [CMotionLayer] �p�[�c�̍폜
//=============================================================
void CMotionLayer::RemoveParts(int nPartsIdx)
{
	// �Ώۂ̃p�[�c�̓o�^����������
	for (int i = 0; i < (int)m_partsIdx.size(); i++)
	{
		if (m_partsIdx[i] == nPartsIdx)
		{ // �폜�Ώۃp�[�c�����������Ƃ�
			m_partsIdx.erase(m_partsIdx.begin() + i);	// �o�^����������
			return;
		}
	}
}

//=============================================================
// [CMotionLayer] ���[�V�����̐ݒ�
//=============================================================
void CMotionLayer::SetMotion(CMotionContents* pContents)
{
	if (m_pPlayContents != pContents || m_bEnded)
	{ // �Ⴄ���[�V�������ݒ肳��Ă����Ƃ�

		// �O��̃��[�V�����Ƃ��ăf�[�^��ۑ����Ă���
		m_pBeforeContents = m_pPlayContents;
		m_nBeforeKeyFrame = m_nKeyFrame;

		// �u�����h�J�E���^�[�̐ݒ�
		m_nBlendCounter = *m_pBlendFrame * 2;

		// �Đ����[�V������ύX����
		m_pPlayContents = pContents;
		m_bEnded = false;

		// �L�[�t���[����0�ɐݒ肷��
		m_nKeyFrame = 0;
	}
}


//=============================================================
// [CMotionContents] �R���X�g���N�^
//=============================================================
CMotionContents::CMotionContents(int nPartsNum)
{
	// �L�[�i�[�x�N�^�[���m�ۂ���
	m_partsKey.resize(nPartsNum);

	// �ϐ��̏�����
	strcpy(&m_name[0], "");
	m_nMaxFrame = 20;
	m_bLoop = false;
}

//=============================================================
// [CMotionContents] �L�[�̒ǉ�
//=============================================================
void CMotionContents::AddKey(int nPartsIdx, int nKey, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale)
{
	// �L�[���쐬����
	Key key;

	// �L�[�̐ݒ�
	key.nKeyFrame = nKey;
	key.transform.SetPos(pos);
	key.transform.SetRot(rot);
	key.transform.SetScale(scale);

	// �p�[�c�̃C���f�b�N�X�����e�l�𒴂��Ă���ꍇ
	if ((int)m_partsKey.size() <= nPartsIdx)
		return; // ���s

	// �L�[�����ɐݒ肳��Ă��邩���m�F����
	for (int i = 0; i < (int)m_partsKey[nPartsIdx].size(); i++)
	{
		if (m_partsKey[nPartsIdx][i].nKeyFrame == nKey)
		{ // �L�[�t���[�������v���Ă���ꍇ
			m_partsKey[nPartsIdx][i] = key;	// �㏑������
			return;
		}
	}

	// �L�[��o�^����
	m_partsKey[nPartsIdx].push_back(key);

	// �����ɕ��בւ���
	SortKey(nPartsIdx);
}

//=============================================================
// [CMotionContents] �L�[�̍폜
//=============================================================
void CMotionContents::RemoveKey(int nPartsIdx, int nKey)
{
	// �w��̃L�[�����݂��邩���m�F����
	for (int i = 0; i < (int)m_partsKey[nPartsIdx].size(); i++)
	{
		if (m_partsKey[nPartsIdx][i].nKeyFrame == nKey)
		{ // �L�[�t���[�������v���Ă���ꍇ
			m_partsKey[nPartsIdx].erase(m_partsKey[nPartsIdx].begin() + i);	// �폜
			return;
		}
	}
}

//=============================================================
// [CMotionContents] �L�[�̕��בւ�
//=============================================================
void CMotionContents::SortKey(int nPartsIdx)
{
	// �����ɕ��בւ���
	sort(m_partsKey[nPartsIdx].begin(), m_partsKey[nPartsIdx].end(),
		[](const Key& a, const Key& b) {return a.nKeyFrame < b.nKeyFrame; });
}

//=============================================================
// [CMotionContents] �L�[�ʒu�̃g�����X�t�H�[�����擾����
//=============================================================
Transform CMotionContents::GetTransform(int nPartsIdx, int nKey)
{
	// �p�[�c���ő吔�𒴂��Ă��Ȃ����m�F
	if (!(0 <= nPartsIdx && nPartsIdx < (int)m_partsKey.size()))
	{
		return Transform(); // �����Ă����Ƃ�
	}
		
	// �p�[�c�̃L�[���X�g���擾����
	std::vector<Key>* pKeyList = &m_partsKey[nPartsIdx];
	if (pKeyList->size() <= 0)
	{
		return Transform(); // �L�[�����݂��Ȃ��Ƃ�
	}

	// ���݂Ǝ��̃L�[���擾
	Key* pKey = nullptr;
	Key* pCurrentKey = nullptr;
	Key* pNextKey = nullptr;
	int nIntervalKeyFrame = 0;

	// �g�����X�t�H�[�������߂�
	Transform currentTrans, nextTrans;

	for (int i = 0; i < (int)pKeyList->size(); i++)
	{
		pKey = &pKeyList->at(i);
	
		if (pKey->nKeyFrame <= nKey)
		{ // �L�[�t���[�����w��̃L�[��菬�����Ƃ�
			pCurrentKey = &pKeyList->at(i); // ���݂̃L�[�ɐݒ�
			pNextKey = nullptr;					// ���̃L�[�����Z�b�g

			if (i+1 < (int)pKeyList->size())
			{ // ���̃L�[�����݂���Ƃ�
				pNextKey = &pKeyList->at(i + 1);
				nIntervalKeyFrame = pNextKey->nKeyFrame - pCurrentKey->nKeyFrame;
			}
			else
			{
				if (m_bLoop)
				{ // ���[�v����Ƃ�
					if (pKeyList->at(0).nKeyFrame == 0)
					{ // ���̃L�[��0�Ԗڂɂ���Ƃ�
						pNextKey = &pKeyList->at(0);	// �ŏ��̃L�[�����̃L�[�ɐݒ肷��
					}
					nIntervalKeyFrame = m_nMaxFrame - pCurrentKey->nKeyFrame;
				}
				else
				{
					return pKey->transform;	 // ���݂̃L�[�̃g�����X�t�H�[���l��Ԃ�
				}
			}
		}
		else
		{	// ���̃L�[�����݂��Ȃ��Ƃ�
			break;
		}
	}



	// �����̃L�[�͑��݂��Ȃ������̃L�[�͑��݂���Ƃ�
	if (pCurrentKey == nullptr)
	{
		pNextKey = &pKeyList->at(0);
		nIntervalKeyFrame = pNextKey->nKeyFrame;
	}
	else
	{
		currentTrans = pCurrentKey->transform;
	}

	// ���̃L�[�����݂���Ƃ�
	if (pNextKey != nullptr)
	{
		nextTrans = pNextKey->transform;
	}

	// 1�t���[���̕ω��ʂ��v�Z����
	D3DXVECTOR3 perPos;	// 1�t���[�����̈ړ���
	perPos = nextTrans.GetPos() - currentTrans.GetPos();
	perPos /= (float)nIntervalKeyFrame;

	D3DXVECTOR3 perRot;	// 1�t���[�����̉�]��
	perRot = nextTrans.GetRot() - currentTrans.GetRot();
	perRot /= (float)nIntervalKeyFrame;

	D3DXVECTOR3 perScale;	// 1�t���[�����̃X�P�[����
	perScale = nextTrans.GetScale() - currentTrans.GetScale();
	perScale /= (float)nIntervalKeyFrame;


	// ���݂̃L�[���牽�t���[���o�߂�����
	int nProgressFrame = nKey;
	if (pCurrentKey != nullptr)
	{
		nProgressFrame -= pCurrentKey->nKeyFrame;
	}

	// �L�[�ʒu�Ɋ�Â��g�����X�t�H�[���l���v�Z����
	Transform trans = Transform();
	trans.SetPos(currentTrans.GetPos() + perPos * (float)nProgressFrame);
	trans.SetRot(currentTrans.GetRot() + perRot * (float)nProgressFrame);
	trans.SetScale(currentTrans.GetScale() + perScale * (float)nProgressFrame);

	return trans;	// ���ʂ�Ԃ�
}
