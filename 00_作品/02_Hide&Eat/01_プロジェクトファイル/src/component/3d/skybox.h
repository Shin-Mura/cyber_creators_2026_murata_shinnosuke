//=============================================================
//
// �X�J�C�{�b�N�X [skybox.h]
// Author: Ito Kotaro
// 
//=============================================================
#ifndef _SKY_BOX_H_
#define _SKY_BOX_H_

// �X�J�C�{�b�N�X
class CSkybox
{
public:
	// �ʒu
	enum POS
	{
		UP,			// ��
		DOWN,		// ��
		FRONT,		// ����
		BACK,		// �w��
		LEFT,		// ��
		RIGHT		// �E
	};

	// �e�N�X�`���^�C�v
	enum TEXTURETYPE
	{
		SINGLE,		// 1��
		SPLIT		// �����i6���j
	};

	CSkybox(Transform* transform) { m_pCameraTransform = transform; }
	void Init();
	void Uninit();
	void Draw();
	void SetTextureType(TEXTURETYPE textureType);
	void SetTexture(const int& idx, const std::string& path);
	void LoadSkybox(const std::string& sPath);

	static const float SKYBOX_SIZE;
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff[6];		// ���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture[6];				// �e�N�X�`��
	D3DXCOLOR m_color;										// �F
	TEXTURETYPE m_textureType;							// �e�N�X�`���^�C�v
	Transform* m_pCameraTransform;						// �J�����̃g�����X�t�H�[���l
};

#endif // !_SKY_BOX_H_
