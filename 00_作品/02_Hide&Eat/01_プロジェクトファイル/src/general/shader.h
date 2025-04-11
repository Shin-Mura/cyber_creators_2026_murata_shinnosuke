//=============================================================
//
// �V�F�[�_�[ [shader.h]
// Author: Ito Kotaro
//
//=============================================================
#ifndef _SHADER_H_
#define _SHADER_H_

// �V�F�[�_�[�i���j
class Shader
{
public:
	// �R���X�g���N�^
	Shader() { }
	// �f�X�g���N�^
	virtual ~Shader() {}

	// ������
	virtual bool Init() = 0;
	// �I��
	virtual void Uninit() = 0;

	// �`��J�n
	virtual HRESULT Begin();
	// �`��I��
	virtual HRESULT End();
	// �p�X�J�n
	virtual HRESULT BeginPass(const UINT& pass);
	// �p�X�I��
	virtual HRESULT EndPass();

	// �p�X���̎擾
	UINT GetNumPass() { return m_numPass; }

	// �R���|�[�l���g����󂯎�����f�[�^
	struct ParamData
	{
		Component* component;
		D3DXCOLOR color;
		LPDIRECT3DTEXTURE9 texture;
		D3DXMATRIX mtx;
	};

	// �`����̐ݒ�
	virtual void SetParam(const ParamData& data){}

protected:
	ID3DXEffect* m_effect;				// �G�t�F�N�g
	UINT m_numPass;						// �p�X��
};

// �W���V�F�[�_�[
class DefaultShader : public Shader
{
public:
	DefaultShader() {m_numPass = 1;}

	// ������
	bool Init() override{}
	// �I��
	void Uninit() override {}
	
	// �W���͌Œ�p�C�v���C�����g�p���邽�ߐݒ肵�Ȃ�
	HRESULT Begin() override {}
	HRESULT End() override {}
	HRESULT BeginPass(const UINT& pass) override {}
	HRESULT EndPass() override {}
};


#endif // !_SHADER_H_
