//=============================================================
//
// �p�[�e�B�N�� [particle.h]
// Author: Ito Kotaro
// 
//=============================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "component.h"
#include "component/3d/billboard.h"

// �p�[�e�B�N���i�P�́j
class Particle : public Component
{
public:
	Particle() : m_vtxBuff(nullptr), m_texture(nullptr), m_color({1.0f, 1.0f, 1.0f, 1.0f}) {}

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	// �T�C�Y�̐ݒ�
	void SetSize(const float& x, const float& y);

	// �J���[�̐ݒ�
	void SetColor(const D3DXCOLOR& color) { m_color = color; }

	// �e�N�X�`���̐ݒ�
	void SetTexture(const std::string& path);
	void BindTexture(LPDIRECT3DTEXTURE9 texture) { m_texture = texture; }
private:
	LPDIRECT3DVERTEXBUFFER9 m_vtxBuff;		// ���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_texture;					// �e�N�X�`��
	D3DXCOLOR m_color;
};

// �p�[�e�B�N�����W���[��
namespace ParticleModule
{
	// ���o
	class Emission
	{
	public:
		Emission() : m_rateOverTime(1.0f), m_elapsedTime(0.0f) {}
		void SetRateOverTime(const float& perSec) { m_rateOverTime = 1.0f / perSec; }
		float GetRateOverTime() { return m_rateOverTime; }
		void SetElapsedTime(float elapsedTime) { m_elapsedTime += elapsedTime; }
		virtual int GetResult();
	protected:
		float m_rateOverTime;	// �b������̕��o��
		float m_elapsedTime;		// �o�ߎ���
	};

	// �`��
	class Shape
	{
	public:
		struct ResultData
		{
			D3DXVECTOR3 position;
			D3DXVECTOR3 direction;
		};
		virtual ResultData GetResult() = 0;
	};

	// ��
	class Power
	{
	public:
		Power() : m_min(1.0f), m_max(1.0f){}
		void Set(const float& power) 
		{ 
			m_min = power;
			m_max = power;
		}
		void Set(const float& min, const float& max)
		{
			m_min = min;
			m_max = max;
		}
		virtual float GetResult() { return Benlib::RandomFloat(m_min, m_max); }
	private:
		float m_min, m_max;
	};

	// ��������
	class Lifetime
	{
	public:
		Lifetime() : m_min(60), m_max(60) {}
		void Set(const int& time)
		{
			m_min = time;
			m_max = time;
		}
		void Set(const int& min, const int& max)
		{
			m_min = min;
			m_max = max;
		}
		virtual int GetResult() { return Benlib::RandomInt(m_min, m_max); }
	private:
		int m_min, m_max;
	};

	// �e�N�X�`��
	class Texture
	{
	public:
		void AddTexture(const std::string& path, const int& chance = 1);
		LPDIRECT3DTEXTURE9 GetResult();
	private:
		struct TextureData
		{
			LPDIRECT3DTEXTURE9 texture;
			int chance;
		};
		std::vector<TextureData> m_textures;
	};
}


// �p�[�e�B�N���V�X�e��
class ParticleSystem : public Component
{
public:
	ParticleSystem() :
		m_gravity(0.0f),
		m_size(5.0f),
		m_emission(nullptr),
		m_shape(nullptr),
		m_power(nullptr),
		m_lifetime(nullptr),
		m_texture(nullptr){}
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	// @brief �d�͂̐ݒ�
	void SetGravity(const float& gravity) { m_gravity = -gravity; }

	// @brief �G�~�b�V�����̐ݒ�
	void SetEmission(ParticleModule::Emission* emission);

	// @brief �V�F�C�v�̐ݒ�
	void SetShape(ParticleModule::Shape* shape);

	// @brief �e�N�X�`���̎擾
	ParticleModule::Texture* GetTexture() { return m_texture; }

	// @brief �p�[�e�B�N���̑���
	int GetNumParticles() { return static_cast<int>(m_particleData.size()); }

	static const int DESTROY_TIME = 60;
private:
	void UpdateGenerator();
	void UpdateParticles();
	void UpdateDestroy();

	// ���W���[��
	ParticleModule::Emission* m_emission;		// ���o
	ParticleModule::Shape* m_shape;				// �`��
	ParticleModule::Power* m_power;				// ��
	ParticleModule::Lifetime* m_lifetime;			// ��������
	ParticleModule::Texture* m_texture;			// �e�N�X�`��

	// �W���ݒ�
	float m_gravity;											// �d��
	float m_size;												// �T�C�Y

	// �p�[�e�B�N���f�[�^
	struct ParticleData
	{
		SingleComponent<Particle>* particle;		// �p�[�e�B�N��
		D3DXVECTOR3 move;							// ����

		int lifeCounter;										// ����
		int destroyCounter;								// �j���J�E���^�[
		bool use;												// �g�p���Ă��邩
	};
	std::vector<ParticleData> m_particleData;
};

// �p�[�e�B�N���̃V�F�C�v
namespace ParticleShape
{
	// �|�C���g�i��_�j
	class PointShape : public ParticleModule::Shape
	{
	public:
		ResultData GetResult() override
		{
			ResultData data;
			data.position = { 0.0f, 0.0f, 0.0f };
			data.direction = { 0.0f, 0.0f, 0.0f };
			return data;
		}
	};

	// ��
	class SphereShape : public ParticleModule::Shape
	{
	public:
		SphereShape() : m_radius(1.0f) {}
		ResultData GetResult() override;
		void SetRadius(const float& radius) { m_radius = radius; }
	private:
		float m_radius;	// ���a
	};
}



#endif // !_PARTICLE_H_
