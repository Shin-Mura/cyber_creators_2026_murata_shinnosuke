//=======================================================================================================
//
//�X�e�[�W�̏���[stage.h]
// Author MurataShinnosuke
//
//=======================================================================================================
#ifndef _STAGE_H_
#define _STAGE_H_

//�X�e�[�W
class Stage
{
public:
	//��ނ̗�
	enum TYPE
	{
		IS_DEMO = 0,
		IS_MAIN,
	};

	//�R���X�g���N�^
	Stage()
	{
	}

	//�f�X�g���N�^
	~Stage()
	{
	}

	void Load(Stage::TYPE type);   //�ǂݍ���

private:
	void LoadMain();
};

#endif // !_STAGE_H_
