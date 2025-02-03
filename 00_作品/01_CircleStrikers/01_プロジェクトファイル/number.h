//========================================================================================================
//
//�����̏���[number.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "rendering.h"
#include "digit.h"

//�����N���X
class Number : public Rendering   //(�e)�I�u�W�F�N�g
{
public:
	//�R���X�g���N�^
	Number(Object* pObject) : Rendering(pObject)
	{
		//�����o�ϐ�������������
		this->m_nNumber = 0;   //����
		this->m_vDigid.clear();
	}

	//�f�X�g���N�^
	~Number() override
	{
	}

	void Init() override;   //����������
	void Uninit() override;	  //�I������
	void Update() override;	  //�X�V����
	void Draw() override;	//�`�揈��

	void SetNumber(int nNumber);   //�����̐ݒ菈��
	void SetDigit(int nDigirt);   //�����̐ݒ菈��

private:
	int m_nNumber;   //����
	std::vector<Digit*> m_vDigid;   //��
};

#endif // !_NUMBER_H_
