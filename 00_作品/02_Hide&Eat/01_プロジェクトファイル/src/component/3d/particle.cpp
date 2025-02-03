//=============================================================
//
// �p�[�e�B�N�� [particle.cpp]
// Author: Ito Kotaro
// 
//=============================================================
#include "particle.h"
#include "renderer.h"
#include "internal/data_manager.h"
#include "manager.h"

//=============================================================
// [Particle] ������
//=============================================================
void Particle::Init()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_vtxBuff, NULL);
	VERTEX_3D* pVtx; //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�@���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_vtxBuff->Unlock();
}

//=============================================================
// [Particle] �I��
//=============================================================
void Particle::Uninit()
{
	// ���_�o�b�t�@�̔j��
	if (m_vtxBuff != nullptr)
	{
		m_vtxBuff->Release();
		m_vtxBuff = nullptr;
	}
}

//=============================================================
// [Particle] �X�V
//=============================================================
void Particle::Update()
{
}

//=============================================================
// [Particle] �`��
//=============================================================
void Particle::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();		// �f�o�C�X���擾
	D3DXMATRIX mtx;
	D3DXMATRIX mtxView;

	Component::BeginPass();

	// ���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���[���h�}�g���b�N�X�̐ݒ�
	if (!IsEnabledShader()) pDevice->SetTransform(D3DTS_WORLD, &mtx);

	// �}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtx);

	// �r���[�}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	// �|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&mtx, NULL, &mtxView);	// �t�s������߂�
	mtx._41 = 0.0f;
	mtx._42 = 0.0f;
	mtx._43 = 0.0f;

	// �I�u�W�F�N�g�̃}�g���b�N�X���|����
	D3DXMATRIX mtxTrans = transform->GetTranslationMatrix();
	D3DXMatrixMultiply(&mtx, &mtx, &mtxTrans);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_vtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	if (!IsEnabledShader()) pDevice->SetTexture(0, m_texture);

	Shader::ParamData paramData;
	paramData.color = m_color;
	paramData.texture = m_texture;
	paramData.mtx = mtx;
	Component::SetParam(paramData);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, //�v���~�e�B�u�̎��
		0, //�`�悷��ŏ��̒��_�C���f�b�N�X
		2);				//�`�悷��v���~�e�B�u��

	Component::EndPass();

	// ���C�g��L���ɖ߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================================
// [Particle] �T�C�Y�ύX
//=============================================================
void Particle::SetSize(const float& x, const float& y)
{
	VERTEX_3D* pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-x / 2, y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(x / 2, y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-x / 2, -y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(x / 2, -y / 2, 0.0f);

	// ���_�o�b�t�@�̃A�����b�N
	m_vtxBuff->Unlock();
}

//=============================================================
// [Particle] �e�N�X�`���̐ݒ�
//=============================================================
void Particle::SetTexture(const std::string& path)
{
	BindTexture(CDataManager::GetInstance()->RefTexture(path)->GetTexture());
}


//=============================================================
// [ParticleSystem] ������
//=============================================================
void ParticleSystem::Init()
{
	// �G�~�b�V�����𐶐�����
	m_emission = new ParticleModule::Emission();

	// �V�F�C�v�𐶐�����
	m_shape = new ParticleShape::SphereShape();

	// �͂𐶐�����
	m_power = new ParticleModule::Power();

	// �������Ԃ𐶐�����
	m_lifetime = new ParticleModule::Lifetime();

	// �e�N�X�`���𐶐�����
	m_texture = new ParticleModule::Texture();
}

//=============================================================
// [ParticleSystem] �I��
//=============================================================
void ParticleSystem::Uninit()
{
	// �G�~�b�V�����̔j��
	if (m_emission != nullptr)
	{
		delete m_emission;
		m_emission = nullptr;
	}

	// �V�F�C�v�̔j��
	if (m_shape != nullptr)
	{
		delete m_shape;
		m_shape = nullptr;
	}

	// �͂̔j��
	if (m_power != nullptr)
	{
		delete m_power;
		m_power = nullptr;
	}

	// �������Ԃ̔j��
	if (m_lifetime != nullptr)
	{
		delete m_lifetime;
		m_lifetime = nullptr;
	}

	// �e�N�X�`���̔j��
	if (m_texture != nullptr)
	{
		delete m_texture;
		m_texture = nullptr;
	}

	// �p�[�e�B�N���̏I��/���
	for (auto itr = m_particleData.begin(); itr != m_particleData.end(); itr++)
	{
		if ((*itr).particle != nullptr)
		{
			(*itr).particle->Uninit();
			delete (*itr).particle;
		}
	}
	m_particleData.clear();
}

//=============================================================
// [ParticleSystem] �X�V
//=============================================================
void ParticleSystem::Update()
{
	// ��������
	UpdateGenerator();

	// �p�[�e�B�N���̍X�V
	UpdateParticles();

	// �j���̍X�V
	UpdateDestroy();
}

//=============================================================
// [ParticleSystem] ��������
//=============================================================
void ParticleSystem::UpdateGenerator()
{
	// �K�{�ݒ肪����Ă��邩���`�F�b�N����
	if (m_emission == nullptr || m_shape == nullptr || m_lifetime == nullptr)
		return;

	// �G�~�b�V�����ɂ����o�ʂ̌���
	m_emission->SetElapsedTime(CManager::GetInstance()->GetDeltaTime());
	int numPerticles = m_emission->GetResult();

	// �p�[�e�B�N���̐���
	for (int i = 0; i < numPerticles; i++)
	{
		// �V�F�C�v���猋�ʂ��擾����i�ʒu�ƕ����j
		ParticleModule::Shape::ResultData shapeResult = m_shape->GetResult();

		// �͂��擾����
		float power = m_power->GetResult();

		// �������Ԃ��擾����
		int lifetime = m_lifetime->GetResult();

		// �p�[�e�B�N���f�[�^��ݒ肷��
		ParticleData data;
		data.move = shapeResult.direction * power;
		data.lifeCounter = lifetime;
		data.destroyCounter = DESTROY_TIME;
		data.use = true;

		// �p�[�e�B�N�����ė��p����
		bool findParticle = false;
		for (auto itr = m_particleData.begin(); itr != m_particleData.end(); itr++)
		{
			ParticleData particle = *itr;
			if (!particle.use)
			{ // �g���Ă��Ȃ��p�[�e�B�N���̂Ƃ�
				data.particle = particle.particle;
				m_particleData.erase(itr);
				findParticle = true;
				break;
			}
		}

		// �g���Ă��Ȃ��p�[�e�B�N����������Ȃ������Ƃ��i�쐬�j
		if (!findParticle)
		{
			data.particle = new SingleComponent<Particle>();
			data.particle->Init();
			data.particle->SetSize(m_size, m_size);
			data.particle->BindTexture(m_texture->GetResult());
		}

		// �����ʒu��ݒ肷��
		data.particle->transform->SetParent(gameObject->transform);
		data.particle->transform->SetPos(shapeResult.position);

		// �ǉ�����
		m_particleData.push_back(data);
	}
}

//=============================================================
// [ParticleSystem] �p�[�e�B�N���̍X�V
//=============================================================
void ParticleSystem::UpdateParticles()
{
	for (auto itr = m_particleData.begin(); itr != m_particleData.end(); itr++)
	{
		ParticleData* data = &(*itr);
		if (data->use)
		{
			// �ړ��ʂ����Z����
			data->particle->transform->Translate(data->move);

			// �d�͂����Z����
			data->move.y += m_gravity;

			// ��������
			data->lifeCounter--;
			if (data->lifeCounter <= 0)
			{ // �������Ȃ��Ȃ����Ƃ�
				data->use = false;
				continue;
			}
		}
	}
}

//=============================================================
// [ParticleSystem] �j���̍X�V
//=============================================================
void ParticleSystem::UpdateDestroy()
{
	// �g���Ȃ��Ȃ����p�[�e�B�N���̔j���J�E���^��i�߂�
	for (auto itr = m_particleData.begin(); itr != m_particleData.end(); itr++)
	{
		ParticleData* data = &(*itr);

		if (!data->use)
		{ // �g���Ă��Ȃ��Ƃ�
			data->destroyCounter--;
			
			// �j���̃^�C�~���O
			if (data->destroyCounter <= 0)
			{
				data->particle->Uninit();
				delete data->particle;
				SAFE_ERASE(m_particleData, itr);
			}
		}
	}
}

//=============================================================
// [ParticleSystem] �`��
//=============================================================
void ParticleSystem::Draw()
{
	for (auto itr = m_particleData.begin(); itr != m_particleData.end(); itr++)
	{
		if ((*itr).use)
		{
			(*itr).particle->SetShader(this->GetShaderInfo());
			(*itr).particle->Draw();
		}
	}
}

//=============================================================
// [ParticleSystem] �G�~�b�V�����̐ݒ�
//=============================================================
void ParticleSystem::SetEmission(ParticleModule::Emission* emission)
{
	if (m_emission != nullptr)
	{
		delete m_emission;
		m_emission = nullptr;
	}

	m_emission = emission;
}

//=============================================================
// [ParticleSystem] �V�F�C�v�̐ݒ�
//=============================================================
void ParticleSystem::SetShape(ParticleModule::Shape* shape)
{
	if (m_shape != nullptr)
	{
		delete m_shape;
		m_shape = nullptr;
	}

	m_shape = shape;
}


//=============================================================
// [Emission] ���o��
//=============================================================
int ParticleModule::Emission::GetResult()
{
	if (m_elapsedTime >= m_rateOverTime)
	{
		int nNum = static_cast<int>((m_elapsedTime - fmod(m_elapsedTime, m_rateOverTime)) / m_rateOverTime);
		m_elapsedTime -= m_rateOverTime * nNum;
		return nNum;
	}
	return 0;
}

//=============================================================
// [Texture] �e�N�X�`���ǉ�
//=============================================================
void ParticleModule::Texture::AddTexture(const std::string& path, const int& chance)
{
	TextureData data;
	data.texture = CDataManager::GetInstance()->RefTexture(path)->GetTexture();
	data.chance = chance;
	m_textures.push_back(data);
}

//=============================================================
// [Texture] �e�N�X�`��
//=============================================================
LPDIRECT3DTEXTURE9 ParticleModule::Texture::GetResult()
{
	int allChance = 0;
	for (auto itr = m_textures.begin(); itr != m_textures.end(); itr++)
		allChance += (*itr).chance;

	if (allChance <= 0)
		return nullptr;

	// �����_��
	int randNum = rand() % allChance;
	int beforeNum = 0;
	for (auto itr = m_textures.begin(); itr != m_textures.end(); itr++)
	{
		if (beforeNum <= randNum && randNum < beforeNum + (*itr).chance)
			return (*itr).texture;
		else
			beforeNum += (*itr).chance;
	}
	return nullptr;
}

//=============================================================
// [SphereShape] �e�N�X�`���̐ݒ�
//=============================================================
ParticleModule::Shape::ResultData ParticleShape::SphereShape::GetResult()
{
	float x = Benlib::RandomFloat(0.0f, D3DX_PI);
	float y = Benlib::RandomFloat(0.0f, D3DX_PI * 2.0f);
	ResultData data;
	data.position = D3DXVECTOR3(sinf(y) * m_radius, cosf(x) * m_radius, cosf(y) * m_radius);
	D3DXVec3Normalize(&data.direction, &data.position);
	return data;
}