//========================================================================================================
//
//�t�F�[�h����[fade.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "behavior.h"

//�t�F�[�h�N���X
class Fade : public Behavior   //(�e)����
{
public:
	//�R���X�g���N�^
	Fade(Object* pObject) : Behavior(pObject)
	{
	}

	//�f�X�g���N�^
	~Fade() override
	{
	}

	void Init() override;   //����������
	void Update() override;   //�X�V����

private:
};
#endif // !_FADE_H_
