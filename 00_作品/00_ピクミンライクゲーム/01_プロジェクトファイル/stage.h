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
	void LoadDemo();
};

#endif // !_STAGE_H_
