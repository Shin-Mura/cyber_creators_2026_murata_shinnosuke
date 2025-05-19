//========================================================================================================
//
//�e�N�X�`������[texture.h]
// Author Murata Shinnosuke
//
//========================================================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "main.h"

//�e�N�X�`���N���X
class Texture
{
public:
	typedef struct
	{
		std::string sPass;   //�p�X
		LPDIRECT3DTEXTURE9 pTexture;   //�e�N�X�`��
	}List;   //���X�g

	Texture();   //�R���X�g���N�^
	~Texture();   //�f�X�g���N�^

	void Init();   //����������
	void Uninit();   //�I������
	LPDIRECT3DTEXTURE9 Get(std::string sFileName);   //�擾����

private:
	std::vector<Texture::List> m_vList;   //���X�g
};

#endif // !_TEXTURE_H_
