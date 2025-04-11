//=============================================================
//
// �v���[���g�W�F�l���[�^ [present_generator.cpp]
// Author: Ito Kotaro
//
//=============================================================
#include "present_generator.h"
#include "manager.h"

#include "component/3d/mesh.h"
#include "component/3d/collision.h"
#include "scripts/present.h"

//=============================================================
// [PresentGenerator] ������
//=============================================================
void PresentGenerator::Init()
{
	m_nextGenerator = 5.0f;

	for (int i = 0; i < 50; i++)
	{
		// �v���[���g�𐶐�����
		Generate();
	}
}

//=============================================================
// [PresentGenerator] �I��
//=============================================================
void PresentGenerator::Uninit()
{
}

//=============================================================
// [PresentGenerator] �X�V
//=============================================================
void PresentGenerator::Update()
{
	// ���̐���
	//m_nextGenerator -= CManager::GetInstance()->GetDeltaTime();
	//if (m_nextGenerator <= 0.0f)
	//{
	//	// �v���[���g�𐶐�����
	//	Generate();
	//	m_nextGenerator = 5.0f;
	//}
}

//=============================================================
// [PresentGenerator] ����
//=============================================================
void PresentGenerator::Generate()
{
	GameObject* pPresent = new GameObject();
	pPresent->transform->SetScale(0.1f);
	pPresent->transform->SetPos(Benlib::RandomFloat(-250.0f, 250.0f), 0.0f, Benlib::RandomFloat(-250.0f, 250.0f));
	pPresent->AddComponent<CMesh>()->LoadMeshX("data\\MODEL\\present_box_00.x");
	pPresent->AddComponent<CBoxCollider>(D3DXVECTOR3(5.0f, 5.0f, 5.0f), D3DXVECTOR3(0.0f, 5.0f, 0.0f));
	CCollision::GetCollision(pPresent)->IsTrigger(true);
	pPresent->AddComponent<Present>();

}