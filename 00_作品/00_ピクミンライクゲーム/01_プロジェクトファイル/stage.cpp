//=======================================================================================================
//
//�X�e�[�W�̏���[stage.cpp]
// Author MurataShinnosuke
//
//=======================================================================================================
#include "stage.h"
#include "prefab.h"
#include "waypoint.h"

//=======================================================================================================
//�ǂݍ���
//=======================================================================================================
void Stage::Load(Stage::TYPE type)
{
	//��ނɂ���ď�����ς���
	switch (type)
	{
	case Stage::TYPE::IS_DEMO:
		//�f���X�e�[�W��ǂݍ���
		this->LoadDemo();

		break;
	}
}

//=======================================================================================================
//�ǂݍ���
//=======================================================================================================
void Stage::LoadDemo()
{
	//���𐶐�����
	FieldPrefab::Create();

	//�u���b�N�𐶐�����
	BlockPrefab::Create({ 100.0f, 0.0f, 0.0f });
	BlockPrefab::Create({ -100.0f, 0.0f, 0.0f });

	//�L�m�R�𐶐�����
	MushroomPrefab::Create({ 35.0f, 0.0f, 0.0f });
	MushroomPrefab::Create({ -35.0f, 0.0f, 0.0f });

	//�v���C���[�𐶐�����
	PlayerPrefab::Create({ 0.0f, 0.0f, -250.0f });
	CursorPrefab::Create({ 0.0f, 0.01f, -250.0f });
	NumInsectPrefab::Create();

	//���𐶐�����
	InsectPrefab::Create({ -60.0f, 0.0f, -300.0f });
	InsectPrefab::Create({ -30.0f, 0.0f, -300.0f });
	InsectPrefab::Create({ 0.0f, 0.0f, -300.0f });
	InsectPrefab::Create({ 30.0f, 0.0f, -300.0f });
	InsectPrefab::Create({ 60.0f, 0.0f, -300.0f });

	//�t���[�c�𐶐�����
	FruitPrefab::Create({ 100.0f, 0.0f, -200.0f }, 1);
	FruitPrefab::Create({ -100.0f, 0.0f, -200.0f }, 1);

	//�[���[
	JellyPrefab::Create({ 100.0f, 0.0f, -100.0f }, 1);

	//�����𐶐�����
	BasketPrefab::Create({ -100.0f, 0.02f, 250.0f });

	//���𐶐�����
	NestPrefab::Create({ 100.0f, 0.0f, 250.0f });

	//�X�R�A�𐶐�����
	ScorePrefab::Create();

	//�E�F�C�|�C���g�̐ݒ�
	{
		//�E�F�C�|�C���g�𐶐�����
		Waypoint* pWaypoint0 = new Waypoint({ { -100.0f, 0.0f, 250.0f } });
		WeypointPrefab::Create({ -100.0f, 100.0f, 250.0f }, 0, "waypoint_00.png");

		//Waypoint* pWaypoint1 = new Waypoint({ { 0.0f, 0.0f, 0.0f } });
		//WeypointPrefab::Create({ 0.0f, 100.0f, 0.0f }, 1, "waypoint_01.png");

		Waypoint* pWaypoint2 = new Waypoint({ { -200.0f, 0.0f, 0.0f } });
		WeypointPrefab::Create({ -200.0f, 100.0f, 0.0f }, 2, "waypoint_02.png");

		Waypoint* pWaypoint3 = new Waypoint({ { -200.0f, 0.0f, -250.0f } });
		WeypointPrefab::Create({ -200.0f, 100.0f, -250.0f }, 3, "waypoint_03.png");

		Waypoint* pWaypoint4 = new Waypoint({ { 0.0f, 0.0f, -250.0f } });
		WeypointPrefab::Create({ 0.0f, 100.0f, -250.0f }, 4, "waypoint_04.png");

		Waypoint* pWaypoint5 = new Waypoint({ { 200.0f, 0.0f, -250.0f } });
		WeypointPrefab::Create({ 200.0f, 100.0f, -250.0f }, 5, "waypoint_05.png");

		Waypoint* pWaypoint6 = new Waypoint({ { 200.0f, 0.0f, 0.0f } });
		WeypointPrefab::Create({ 200.0f, 100.0f, 0.0f }, 6, "waypoint_06.png");

		Waypoint* pWaypoint7 = new Waypoint({ { 100.0f, 0.0f, 250.0f } });
		WeypointPrefab::Create({ 100.0f, 100.0f, 250.0f }, 7, "waypoint_07.png");

		//�E�F�C�|�C���g���q����
		//pWaypoint0->AddConnect(pWaypoint1);
		//pWaypoint1->AddConnect(pWaypoint0);

		pWaypoint0->AddConnect(pWaypoint2);
		pWaypoint2->AddConnect(pWaypoint0);

		pWaypoint0->AddConnect(pWaypoint7);
		pWaypoint7->AddConnect(pWaypoint0);

		pWaypoint2->AddConnect(pWaypoint3);
		pWaypoint3->AddConnect(pWaypoint2);

		pWaypoint3->AddConnect(pWaypoint4);
		pWaypoint4->AddConnect(pWaypoint3);

		pWaypoint4->AddConnect(pWaypoint5);
		pWaypoint5->AddConnect(pWaypoint4);

		pWaypoint5->AddConnect(pWaypoint6);
		pWaypoint6->AddConnect(pWaypoint5);

		pWaypoint6->AddConnect(pWaypoint7);
		pWaypoint7->AddConnect(pWaypoint6);
	}
}