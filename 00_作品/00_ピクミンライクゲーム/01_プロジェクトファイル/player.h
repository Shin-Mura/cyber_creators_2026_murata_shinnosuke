//========================================================================================================
//
//�v���C���[����[player.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "behavior.h"

//�v���C���[
class Player : public Behavior
{
public:
	static const int MAX_INSECT;   //���̍ő吔
	static const float MOVE_SPEED;   //�ړ����x

	//���[�V�����̗�
	enum MOTION
	{
		IS_NEUTRAL = 0,
		IS_MOVE,
		IS_ATTACK,
	};

	//�R���X�g���N�^
	Player(Object* pObject) : Behavior(pObject)
	{
		//�����o�ϐ�������������
		this->m_motionPlay = Player::MOTION::IS_NEUTRAL;   //�Đ����̃��[�V����
		this->m_pCursor = nullptr;   //�J�[�\��
		this->m_vInsect.clear();   //���̃R���e�i
	}

	//�f�X�g���N�^
	~Player() override
	{
	}

	void Init() override;   //����������
	void Update() override;   //�X�V����
	void EndMotion() override;   //���[�V�����I�����̏���

private:
	void Control();   //�R���g���[������
	void SearchInsect();   //����T��
	void ThrowInsect();   //���𓊂���
	void ChangeMotion(Player::MOTION motion);

	//���������Ă��邩�m�F
	bool HasInsect(Object* pInsect)
	{
		//���̐����J��Ԃ�
		for (unsigned int i = 0; i < this->m_vInsect.size(); i++)
		{
			//�����m�F����
			if (this->m_vInsect[i] == pInsect)
			{
				//�����Ă����Ԃ�
				return true;
			}
		}

		//�����Ă��Ȃ���Ԃ�
		return false;
	}

	Player::MOTION m_motionPlay;   //�Đ����̃��[�V����
	Object* m_pCursor;  //�J�[�\��
	std::vector<Object*> m_vInsect;   //���̃R���e�i
	Object* m_pNumInsect;   //���̐���UI
};

#endif // !_PLAYER_H_
