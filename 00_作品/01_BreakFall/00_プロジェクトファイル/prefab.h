//==========================================================================================================
//
//�v���n�u�H�̏���[prefab.h]
// Author MurataShinnosuke
//
//==========================================================================================================
#ifndef _PREFAB_H_
#define _PREFAB_H_

#include "object.h"
#include "manager.h"

#include "camera.h"
#include "collider.h"
#include "dire_light.h"
#include "motioneer.h"
#include "rigidbody.h"
#include "stencil.h"
#include "transform.h"

#include "mask.h"
#include "menu.h"
#include "model.h"
#include "number.h"
#include "plane.h"
#include "square.h"

#include "assist_bar.h"
#include "ball.h"
#include "block.h"
#include "block_spawner.h"
#include "fade.h"
#include "pause_menu.h"
#include "score.h"
#include "stick.h"
#include "timer.h"
#include "title_menu.h"

#include "item.h"

////�v���n�u
//class Prefab
//{
//public:
//	//�R���X�g���N�^
//	Prefab()
//	{
//		this->m_vPrefab.clear();   //�R���e�i
//	}
//
//	//�f�X�g���N�^
//	~Prefab()
//	{
//	}
//
//	void AddPrefab(Object* pObejct) { this->m_vPrefab.push_back(pObejct); };   //�v���n�u�̒ǉ�
//
//
//private:
//	std::vector<Object*> m_vPrefab;   //�R���e�i
//};

//�A�V�X�g�_
class AssistBarPrefab
{
public:
	//��������
	static Object* Create()
	{
		//�w�i�𐶐�����
		Object* pPrefab = new Object("AssistBar");
		pPrefab->SetTag(Object::TAG::IS_STICK);

		//�g�����X�t�H�[����ǉ�����
		Transform* pTransform = new Transform(pPrefab);
		pTransform->SetScale({ 2.5f, 0.1f, 0.1f });
		pTransform->SetPos({ 0.0f, -350.0f, 0.0f });
		pPrefab->AddComponent(pTransform);

		//�l�p�`�����_�����O��ǉ�����
		PlaneY* pPlaneY = new PlaneY(pPrefab);
		//pPlaneY->SetTexture(Manager::Get()->GetTexture()->Get("ball_00.png"));
		pPrefab->AddComponent(pPlaneY);

		//�{�b�N�X�R���C�_�[��ǉ�����
		BoxCollider* pBoxCollider = new BoxCollider(pPrefab);
		pBoxCollider->SetSize({ 500.0f, 20.0f, 5.0f });
		pPrefab->AddComponent(pBoxCollider);

		//�_�̋�����ǉ�����
		AssistBar* pAssistBar = new AssistBar(pPrefab);
		pPrefab->AddComponent(pAssistBar);

		//����������
		pPrefab->Init();

		//�v���n�u��Ԃ�
		return pPrefab;
	}
};

//�w�i
class Background2DPrefab
{
public:
	//��������
	static Object* Create(LPDIRECT3DTEXTURE9 pTexture)
	{
		//�w�i�𐶐�����
		Object* pPrefab = new Object("Background2D");

		//�g�����X�t�H�[����ǉ�����
		Transform2D* pTransform2D = new Transform2D(pPrefab);
		pTransform2D->SetSize({ SCREEN_WIDTH, SCREEN_HEIGHT });
		pPrefab->AddComponent(pTransform2D);

		//�l�p�`�����_�����O��ǉ�����
		Square* pSquare = new Square(pPrefab);
		pSquare->SetTexture(pTexture);
		pPrefab->AddComponent(pSquare);

		//����������
		pPrefab->Init();

		//�v���n�u��Ԃ�
		return pPrefab;
	}
};

//�w�i
class Background3DPrefab
{
public:
	//��������
	static Object* Create(LPDIRECT3DTEXTURE9 pTexture)
	{
		//�w�i�𐶐�����
		Object* pPrefab = new Object("Background3D");

		//�g�����X�t�H�[����ǉ�����
		Transform* pTransform = new Transform(pPrefab);
		pTransform->SetPos({ 0.0f, 0.0f, 10.0f });
		pTransform->SetScale({ 6.4f, 3.6f, 1.0f });
		pPrefab->AddComponent(pTransform);

		//�l�p�`�����_�����O��ǉ�����
		PlaneY* pPlaneY = new PlaneY(pPrefab);
		pPlaneY->SetTexture(pTexture);
		pPrefab->AddComponent(pPlaneY);

		//����������
		pPrefab->Init();

		//�v���n�u��Ԃ�
		return pPrefab;
	}
};

//�{�[��
class BallPrefab
{
public:
	//��������
	static Object* Create()
	{
		//�����𐶐�����
		Object* pPrefab = new Object("Ball");
		pPrefab->SetTag(Object::TAG::IS_BALL);

		//�g�����X�t�H�[����ǉ�����
		Transform* pTransform = new Transform(pPrefab);
		pTransform->SetScale({ 0.1f, 0.1f, 0.1f });
		pPrefab->AddComponent(pTransform);

		//�l�p�`�����_�����O��ǉ�����
		PlaneY* pPlaneY = new PlaneY(pPrefab);
		pPlaneY->SetTexture(Manager::Get()->GetTexture()->Get("block_00.png"));
		pPrefab->AddComponent(pPlaneY);

		//���W�b�g�{�f�B��ǉ�����
		Rigidbody* pRigidbody = new Rigidbody(pPrefab);
		pRigidbody->SetGravity(0.0f);
		pRigidbody->SetFriction(0.0f);
		pRigidbody->SetFrictionAir(0.0f);
		pPrefab->AddComponent(pRigidbody);

		//�{�b�N�X�R���C�_�[��ǉ�����
		BoxCollider* pBoxCollider = new BoxCollider(pPrefab);
		pBoxCollider->SetSize({ 20.0f, 20.0f, 20.0f });
		pPrefab->AddComponent(pBoxCollider);

		//�{�[���̋�����ǉ�����
		Ball* pBall = new Ball(pPrefab);
		pPrefab->AddComponent(pBall);

		//����������
		pPrefab->Init();

		//�v���n�u��Ԃ�
		return pPrefab;
	}
};

//�u���b�N
class BlockPrefab
{
public:
	//��������
	static Object* Create(D3DXVECTOR3 pos)
	{
		//�w�i�𐶐�����
		Object* pPrefab = new Object("Block");
		pPrefab->SetTag(Object::TAG::IS_BLOCK);

		//�g�����X�t�H�[����ǉ�����
		Transform* pTransform = new Transform(pPrefab);
		pTransform->SetPos(pos);   //�ʒu�̐ݒ�
		pTransform->SetScale({ 0.5f, 0.25f, 1.0f });
		pPrefab->AddComponent(pTransform);

		//�l�p�`�����_�����O��ǉ�����
		PlaneY* pPlaneY = new PlaneY(pPrefab);
		pPlaneY->SetTexture(Manager::Get()->GetTexture()->Get("block_00.png"));
		pPrefab->AddComponent(pPlaneY);

		//�{�b�N�X�R���C�_�[��ǉ�����
		BoxCollider* pBoxCollider = new BoxCollider(pPrefab);
		pBoxCollider->SetSize(Block::SIZE);
		pPrefab->AddComponent(pBoxCollider);

		//�{�[���̋�����ǉ�����
		Block* pBlock = new Block(pPrefab);
		pPrefab->AddComponent(pBlock);

		//����������
		pPrefab->Init();

		//�v���n�u��Ԃ�
		return pPrefab;
	}
};

//�u���b�N�X�|�i�[
class BlockSpawnerPrefab
{
public:
	//��������
	static Object* Create()
	{
		//�w�i�𐶐�����
		Object* pPrefab = new Object("BlockSpawner");
		pPrefab->SetTag(Object::TAG::IS_BLOCK);

		//�u���b�N�X�|�i�[�̋�����ǉ�����
		BlockSpawner* pBlockSpawner = new BlockSpawner(pPrefab);
		pPrefab->AddComponent(pBlockSpawner);

		//����������
		pPrefab->Init();

		//�v���n�u��Ԃ�
		return pPrefab;
	}
};

//�ʒǉ��A�C�e��
class AddBallItemPrefab
{
public:
	//��������
	static Object* Create(D3DXVECTOR3 pos)
	{
		//��������
		Object* pPrefab = new Object("AddBallItem");
		pPrefab->SetTag(Object::TAG::IS_ITEM);

		//�g�����X�t�H�[����ǉ�����
		Transform* pTransform = new Transform(pPrefab);
		pTransform->SetPos(pos);   //�ʒu�̐ݒ�
		pTransform->SetScale({ 0.25f, 0.25f, 1.0f });
		pPrefab->AddComponent(pTransform);

		//�l�p�`�����_�����O��ǉ�����
		PlaneY* pPlaneY = new PlaneY(pPrefab);
		pPlaneY->SetTexture(Manager::Get()->GetTexture()->Get("addball_item.png"));
		pPrefab->AddComponent(pPlaneY);

		//���W�b�g�{�f�B��ǉ�����
		Rigidbody* pRigidbody = new Rigidbody(pPrefab);
		pRigidbody->SetGravity(0.0f);
		pRigidbody->SetFriction(0.0f);
		pRigidbody->SetFrictionAir(0.0f);
		pPrefab->AddComponent(pRigidbody);

		//�{�b�N�X�R���C�_�[��ǉ�����
		BoxCollider* pBoxCollider = new BoxCollider(pPrefab);
		pBoxCollider->SetSize({ Item::SIZE, Item::SIZE, 5.0f });
		pBoxCollider->SetMass(4);
		pPrefab->AddComponent(pBoxCollider);

		//�A�C�e���̋�����ǉ�����
		AddBallItem* pItem = new AddBallItem(pPrefab);
		pPrefab->AddComponent(pItem);

		//����������
		pPrefab->Init();

		//�v���n�u��Ԃ�
		return pPrefab;
	}
};

//�ʒǉ��A�C�e��
class ClearBlockItemPrefab
{
public:
	//��������
	static Object* Create(D3DXVECTOR3 pos)
	{
		//��������
		Object* pPrefab = new Object("AddBallItem");
		pPrefab->SetTag(Object::TAG::IS_ITEM);

		//�g�����X�t�H�[����ǉ�����
		Transform* pTransform = new Transform(pPrefab);
		pTransform->SetPos(pos);   //�ʒu�̐ݒ�
		pTransform->SetScale({ 0.25f, 0.25f, 1.0f });
		pPrefab->AddComponent(pTransform);

		//�l�p�`�����_�����O��ǉ�����
		PlaneY* pPlaneY = new PlaneY(pPrefab);
		pPlaneY->SetTexture(Manager::Get()->GetTexture()->Get("clear_item.png"));
		pPrefab->AddComponent(pPlaneY);

		//���W�b�g�{�f�B��ǉ�����
		Rigidbody* pRigidbody = new Rigidbody(pPrefab);
		pRigidbody->SetGravity(0.0f);
		pRigidbody->SetFriction(0.0f);
		pRigidbody->SetFrictionAir(0.0f);
		pPrefab->AddComponent(pRigidbody);

		//�{�b�N�X�R���C�_�[��ǉ�����
		BoxCollider* pBoxCollider = new BoxCollider(pPrefab);
		pBoxCollider->SetSize({ Item::SIZE, Item::SIZE, 5.0f });
		pBoxCollider->SetMass(4);
		pPrefab->AddComponent(pBoxCollider);

		//�A�C�e���̋�����ǉ�����
		ClearBlockItem* pItem = new ClearBlockItem(pPrefab);
		pPrefab->AddComponent(pItem);

		//����������
		pPrefab->Init();

		//�v���n�u��Ԃ�
		return pPrefab;
	}
};

//�ʒǉ��A�C�e��
class AssistBarItemPrefab
{
public:
	//��������
	static Object* Create(D3DXVECTOR3 pos)
	{
		//��������
		Object* pPrefab = new Object("AddBallItem");
		pPrefab->SetTag(Object::TAG::IS_ITEM);

		//�g�����X�t�H�[����ǉ�����
		Transform* pTransform = new Transform(pPrefab);
		pTransform->SetPos(pos);   //�ʒu�̐ݒ�
		pTransform->SetScale({ 0.25f, 0.25f, 1.0f });
		pPrefab->AddComponent(pTransform);

		//�l�p�`�����_�����O��ǉ�����
		PlaneY* pPlaneY = new PlaneY(pPrefab);
		pPlaneY->SetTexture(Manager::Get()->GetTexture()->Get("supportbar_item.png"));
		pPrefab->AddComponent(pPlaneY);

		//���W�b�g�{�f�B��ǉ�����
		Rigidbody* pRigidbody = new Rigidbody(pPrefab);
		pRigidbody->SetGravity(0.0f);
		pRigidbody->SetFriction(0.0f);
		pRigidbody->SetFrictionAir(0.0f);
		pPrefab->AddComponent(pRigidbody);

		//�{�b�N�X�R���C�_�[��ǉ�����
		BoxCollider* pBoxCollider = new BoxCollider(pPrefab);
		pBoxCollider->SetSize({ Item::SIZE, Item::SIZE, 5.0f });
		pBoxCollider->SetMass(4);
		pPrefab->AddComponent(pBoxCollider);

		//�A�C�e���̋�����ǉ�����
		AssistBarItem* pItem = new AssistBarItem(pPrefab);
		pPrefab->AddComponent(pItem);

		//����������
		pPrefab->Init();

		//�v���n�u��Ԃ�
		return pPrefab;
	}
};

//�ʒǉ��A�C�e��
class AddHeartItemPrefab
{
public:
	//��������
	static Object* Create(D3DXVECTOR3 pos)
	{
		//��������
		Object* pPrefab = new Object("AddBallItem");
		pPrefab->SetTag(Object::TAG::IS_ITEM);

		//�g�����X�t�H�[����ǉ�����
		Transform* pTransform = new Transform(pPrefab);
		pTransform->SetPos(pos);   //�ʒu�̐ݒ�
		pTransform->SetScale({ 0.25f, 0.25f, 1.0f });
		pPrefab->AddComponent(pTransform);

		//�l�p�`�����_�����O��ǉ�����
		PlaneY* pPlaneY = new PlaneY(pPrefab);
		pPlaneY->SetTexture(Manager::Get()->GetTexture()->Get("heal_item.png"));
		pPrefab->AddComponent(pPlaneY);

		//���W�b�g�{�f�B��ǉ�����
		Rigidbody* pRigidbody = new Rigidbody(pPrefab);
		pRigidbody->SetGravity(0.0f);
		pRigidbody->SetFriction(0.0f);
		pRigidbody->SetFrictionAir(0.0f);
		pPrefab->AddComponent(pRigidbody);

		//�{�b�N�X�R���C�_�[��ǉ�����
		BoxCollider* pBoxCollider = new BoxCollider(pPrefab);
		pBoxCollider->SetSize({ Item::SIZE, Item::SIZE, 5.0f });
		pBoxCollider->SetMass(4);
		pPrefab->AddComponent(pBoxCollider);

		//�A�C�e���̋�����ǉ�����
		AddHeartItem* pItem = new AddHeartItem(pPrefab);
		pPrefab->AddComponent(pItem);

		//����������
		pPrefab->Init();

		//�v���n�u��Ԃ�
		return pPrefab;
	}
};

//�J����
class CameraPrefab
{
public:
	//��������
	static Object* Create()
	{
		//�J�����𐶐�����
		Object* pPrefab = new Object("Camera");

		//�g�����X�t�H�[����ǉ�����
		Transform* pTransform = new Transform(pPrefab);
		pTransform->SetPos({ 0.0f, 0.0f, -500.0f });
		pPrefab->AddComponent(pTransform);

		//�J������ǉ�����
		Camera* pCamera = new Camera(pPrefab);
		pPrefab->AddComponent(pCamera);

		//����������
		pPrefab->Init();

		//�v���n�u��Ԃ�
		return pPrefab;
	}
};

//���C�g
class DireLightPrefab
{
public:
	//��������
	static Object* Create(D3DXVECTOR3 rot, D3DXCOLOR color)
	{
		//���C�g�𐶐�����
		Object* pPrefab = new Object("DirectionalLight");

		//�g�����X�t�H�[����ǉ�����
		Transform* pTransform = new Transform(pPrefab);
		pTransform->SetRot(rot);
		pPrefab->AddComponent(pTransform);

		//���C�g��ǉ�����
		DireLight* pDireLight = new DireLight(pPrefab);
		pDireLight->SetColor(color);   //�F
		pPrefab->AddComponent(pDireLight);

		//����������
		pPrefab->Init();

		//�v���n�u��Ԃ�
		return pPrefab;
	}
};

//�t�F�[�h
class FadePrefab
{
public:
	//��������
	static Object* Create()
	{
		//�w�i�𐶐�����
		Object* pPrefab = new Object("Fade");

		//�g�����X�t�H�[����ǉ�����
		Transform2D* pTransform2D = new Transform2D(pPrefab);
		pTransform2D->SetSize({ SCREEN_WIDTH, SCREEN_HEIGHT });
		pPrefab->AddComponent(pTransform2D);

		//�l�p�`�����_�����O��ǉ�����
		Square* pSquare = new Square(pPrefab);
		pSquare->SetColor({ 0.0f, 0.0f, 0.0f, 1.0f });   //�F
		pPrefab->AddComponent(pSquare);

		//�t�F�[�h�̋�����ǉ�����
		Fade* pFade = new Fade(pPrefab);
		pPrefab->AddComponent(pFade);

		//����������
		pPrefab->Init();

		//�v���n�u��Ԃ�
		return pPrefab;
	}
};

//�|�[�Y���j���[
class PauseMenuPrefab
{
public:
	//��������
	static Object* Create()
	{
		//�|�[�Y���j���[�𐶐�����
		Object* pPrefab = new Object("PauseMenu");
		pPrefab->SetActive(false);   //��A�N�e�B�u

		//�g�����X�t�H�[����ǉ�����
		Transform2D* pTransform2D = new Transform2D(pPrefab);
		pTransform2D->SetPos({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 });   //�ʒu
		pTransform2D->SetSize(PauseMenu::SIZE_MENU);   //�T�C�Y
		pPrefab->AddComponent(pTransform2D);

		//���j���[�����_�����O��ǉ�����
		Menu* pMenu = new Menu(pPrefab);
		pMenu->SetTexture(Manager::Get()->GetTexture()->Get("pause_menu_00.png"));
		pMenu->SetSelectBox(PauseMenu::MENU::IS_MAX);
		pMenu->SetGap(1.0f);
		pPrefab->AddComponent(pMenu);

		//�|�[�Y���j���[�̋�����ǉ�����
		PauseMenu* pPauseMenu = new PauseMenu(pPrefab);
		pPrefab->AddComponent(pPauseMenu);

		//����������
		pPrefab->Init();

		//�v���n�u��Ԃ�
		return pPrefab;
	}
};

//�X�R�A
class ScorePrefab
{
public:
	//��������
	static Object* Create(D3DXVECTOR2 pos = {0.0f, 0.0f}, D3DXVECTOR2 size = {500.0f, 100.0f})
	{
		//�X�R�A�𐶐�����
		Object* pPrefab = new Object("Score");

		//�g�����X�t�H�[����ǉ�����
		Transform2D* pTransform2D = new Transform2D(pPrefab);
		pTransform2D->SetPos(pos);							//�ʒu
		pTransform2D->SetSize(size);							 //�T�C�Y
		pPrefab->AddComponent(pTransform2D);

		//���������_�����O��ǉ�����
		Number* pNumber = new Number(pPrefab);
		pNumber->SetTexture(Manager::Get()->GetTexture()->Get("number_00.png"));
		pNumber->SetDigit(8);
		pNumber->SetNumber(Timer::START_TIMER);
		pPrefab->AddComponent(pNumber);

		//�X�R�A�̋�����ǉ�����
		Score* pScore = new Score(pPrefab);
		pPrefab->AddComponent(pScore);

		//����������
		pPrefab->Init();

		//�v���n�u��Ԃ�
		return pPrefab;
	}
};

//�_
class StickPrefab
{
public:
	//��������
	static Object* Create()
	{
		//�w�i�𐶐�����
		Object* pPrefab = new Object("Stick");
		pPrefab->SetTag(Object::TAG::IS_STICK);

		//�g�����X�t�H�[����ǉ�����
		Transform* pTransform = new Transform(pPrefab);
		pTransform->SetScale({ 1.5f, 0.1f, 0.1f });
		pTransform->SetPos({ 0.0f, -300.0f, 0.0f });
		pPrefab->AddComponent(pTransform);

		//�l�p�`�����_�����O��ǉ�����
		PlaneY* pPlaneY = new PlaneY(pPrefab);
		//pPlaneY->SetTexture(Manager::Get()->GetTexture()->Get("ball_00.png"));
		pPrefab->AddComponent(pPlaneY);

		//�{�b�N�X�R���C�_�[��ǉ�����
		BoxCollider* pBoxCollider = new BoxCollider(pPrefab);
		pBoxCollider->SetSize({ 300.0f, 20.0f, 5.0f });
		pPrefab->AddComponent(pBoxCollider);

		//�_�̋�����ǉ�����
		Stick* pStick = new Stick(pPrefab);
		pPrefab->AddComponent(pStick);

		//����������
		pPrefab->Init();

		//�v���n�u��Ԃ�
		return pPrefab;
	}
};

//�^�C�}�[
class TimerPrefab
{
public:
	//��������
	static Object* Create()
	{
		//�^�C�}�[�𐶐�����
		Object* pPrefab = new Object("Timer");

		//�g�����X�t�H�[����ǉ�����
		Transform2D* pTransform2D = new Transform2D(pPrefab);
		pTransform2D->SetPos({ 50.0f, 80.0f });   //�ʒu
		pTransform2D->SetSize({ 200.0f, 100.0f });   //�T�C�Y
		pPrefab->AddComponent(pTransform2D);

		//���������_�����O��ǉ�����
		Number* pNumber = new Number(pPrefab);
		pNumber->SetTexture(Manager::Get()->GetTexture()->Get("number_00.png"));
		pNumber->SetDigit(3);
		pNumber->SetNumber(Timer::START_TIMER);
		pPrefab->AddComponent(pNumber);

		//�^�C�}�[�̋�����ǉ�����
		Timer* pTimer = new Timer(pPrefab);
		pPrefab->AddComponent(pTimer);

		//����������
		pPrefab->Init();

		//�v���n�u��Ԃ�
		return pPrefab;
	}
};

//�^�C�g�����j���[
class TitleMenuPrefab
{
public:
	//��������
	static Object* Create()
	{
		//�^�C�g�����j���[�𐶐�����
		Object* pPrefab = new Object("TitleMenu");

		//�g�����X�t�H�[����ǉ�����
		Transform2D* pTransform2D = new Transform2D(pPrefab);
		pTransform2D->SetPos({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2  + 100.0f});   //�ʒu
		pTransform2D->SetSize(TitleMenu::SIZE_MENU);   //�T�C�Y
		pPrefab->AddComponent(pTransform2D);

		//���j���[�����_�����O��ǉ�����
		Menu* pMenu = new Menu(pPrefab);
		pMenu->SetTexture(Manager::Get()->GetTexture()->Get("title_menu_00.png"));
		pMenu->SetSelectBox(TitleMenu::MENU::IS_MAX);
		pMenu->SetGap(1.0f);
		pPrefab->AddComponent(pMenu);

		//�^�C�g�����j���[�̋�����ǉ�����
		TitleMenu* pTitleMenu = new TitleMenu(pPrefab);
		pPrefab->AddComponent(pTitleMenu);

		//����������
		pPrefab->Init();

		//�v���n�u��Ԃ�
		return pPrefab;
	}
};

#endif // !_PREFAB_H_
