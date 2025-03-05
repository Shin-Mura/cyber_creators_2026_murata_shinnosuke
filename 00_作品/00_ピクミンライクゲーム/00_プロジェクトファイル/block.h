//========================================================================================================
//
//�u���b�N�̏���[block.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "behavior.h"

//�u���b�N�N���X
class Block : public Behavior   //(�e)����
{
public:
	static const D3DXVECTOR3 MODEL_SIZE;   //���f���̃T�C�Y

	//�R���X�g���N�^
	Block(Object* pObject) : Behavior(pObject)
	{
	}

	//�f�X�g���N�^
	~Block() override
	{
	}

	void Init() override;   //����������
	void Update() override;   //�X�V����

private:
};

#endif // !_BLOCK_H_
