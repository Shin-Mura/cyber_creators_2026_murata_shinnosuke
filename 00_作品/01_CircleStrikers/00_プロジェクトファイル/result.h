//========================================================================================================
//
//�^�C�g���V�[������[result.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "scene.h"

//�^�C�g���V�[���N���X
class Result : public Scene   //�i�e�j�V�[���N���X
{
public:
	Result();   //�R���X�g���N�^
	virtual ~Result();   //�f�X�g���N�^

	void Init() override;   //����������
	void Uninit() override;   //�I������
	void Update() override;   //�X�V����
	void Draw() override;   //�`�揈��

private:
};

#endif // !_RESULT_H_
