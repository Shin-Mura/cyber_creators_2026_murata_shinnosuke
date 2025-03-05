//========================================================================================================
//
//���[�V�����̏���[motion.cpp]
// Author MurataShinnosuke
//
//========================================================================================================
#include "motion.h"

//�ÓI�����o�ϐ�������������
const int Motion::FRAME_BLEND = 3;   //�u�����h�t���[��

//========================================================================================================
//����������
//========================================================================================================
void Motion::Init()
{
}

//========================================================================================================
//�I������
//========================================================================================================
void Motion::Uninit()
{
}

//========================================================================================================
//�X�V����
//========================================================================================================
void Motion::Update()
{
	//�L�[�̐���ۑ�����
	int nKeyNum = this->m_vKey.size();

	//���݃L�[���m�F����
	if (this->m_nKey < nKeyNum)
	{//���݃L�[���L�[�̐��𒴂��Ă��Ȃ��ꍇ
		//�I���t���O�����낷
		this->m_isEnd = false;

		//�t���[����i�߂�
		this->m_nFrame++;   //���݃t���[��
		this->m_nFrameBlend++;   //�u�����h�t���[��

		//�����̐����J��Ԃ�
		for (unsigned int i = 0; i < this->m_vRot.size(); i++)
		{
			//���̃L�[�̕ۑ�����
			int nKeyNext = this->m_nKey + 1;
			if (nKeyNext >= nKeyNum)
			{//���̃L�[���L�[�̐��𒴂����ꍇ
				if (this->m_isLoop)
				{
					//���̃L�[��1�ԍŏ��ɂ���
					nKeyNext = 0;
				}
				else
				{
					//���̃L�[�����݃L�[�̐ݒ肷��
					nKeyNext = this->m_nKey;
				}
			}

			//���̌����Ƃ̍��������
			D3DXVECTOR3 rotDiff = this->m_vKey[nKeyNext].vRot[i] - this->m_vKey[this->m_nKey].vRot[i];

			//�������v�Z����
			D3DXVECTOR3 rot =
			{
				this->m_vKey[this->m_nKey].vRot[i].x + ((rotDiff.x / this->m_vKey[this->m_nKey].nFrame) * this->m_nFrame),
				this->m_vKey[this->m_nKey].vRot[i].y + ((rotDiff.y / this->m_vKey[this->m_nKey].nFrame) * this->m_nFrame),
				this->m_vKey[this->m_nKey].vRot[i].z + ((rotDiff.z / this->m_vKey[this->m_nKey].nFrame) * this->m_nFrame)
			};

			//���݃t���[�����m�F����
			if (this->m_nFrameBlend <= Motion::FRAME_BLEND)
			{
				//���݂̈ʒu�ƍ��������
				rotDiff = rot - this->m_vRot[i];

				//�������v�Z����
				D3DXVECTOR3 rot =
				{
					this->m_vRot[i].x + ((rotDiff.x / Motion::FRAME_BLEND) * this->m_nFrameBlend),
					this->m_vRot[i].y + ((rotDiff.y / Motion::FRAME_BLEND) * this->m_nFrameBlend),
					this->m_vRot[i].z + ((rotDiff.z / Motion::FRAME_BLEND) * this->m_nFrameBlend)
				};
			}

			//�����𔽉f������
			this->m_vRot[i] = rot;
		}

		//���݃t���[�����m�F����
		if (this->m_nFrame >= this->m_vKey[this->m_nKey].nFrame)
		{//���݃t���[�������݃L�[�̃t���[���𒴂����ꍇ
			//���݃t���[�������Z�b�g����
			this->m_nFrame = 0;

			//���̃L�[�Ɉڍs����
			this->m_nKey++;
			if (this->m_nKey >= nKeyNum)
			{//���݃L�[���L�[�̐��𒴂����ꍇ
				//���[�v�t���O���m�F����
				if (this->m_isLoop == true)
				{//���[�v�t���O�������Ă���ꍇ
					//���݃L�[�����Z�b�g����
					this->m_nKey = 0;
				}
				else
				{
					//�I���t���O�𗧂Ă�
					this->m_isEnd = true;
				}
			}
		}
	}
}