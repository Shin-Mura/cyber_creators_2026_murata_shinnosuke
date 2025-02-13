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

#include "basket.h"
#include "block.h"
#include "camera_bird.h"
#include "camera_tps.h"
#include "cursor.h"
#include "fade.h"
#include "cargo.h"
#include "insect.h"
#include "nest.h"
#include "num_insect.h"
#include "obstacle.h"
#include "pause_menu.h"
#include "player.h"
#include "score.h"
#include "timer.h"
#include "title_menu.h"

#include "waypoint.h"

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

//����
class BasketPrefab
{
public:
	//��������
	static Object* Create(D3DXVECTOR3 pos)
	{
		//�����𐶐�����
		Object* pPrefab = new Object("Basket");

		//�g�����X�t�H�[����ǉ�����
		Transform* pTransform = new Transform(pPrefab);
		pTransform->SetPos(pos);
		pTransform->SetScale({ 5.0f, 5.0f, 5.0f });   //�g�嗦
		pPrefab->AddComponent(pTransform);

		//���f�������_�����O��ǉ�����
		Model* pModel = new Model(pPrefab);
		pModel->SetXFile(Manager::Get()->GetXFile()->Get("basket_00.x"));
		pPrefab->AddComponent(pModel);

		//�X�e���V����ǉ�����
		Stencil* pStencil = new Stencil(pPrefab, 1, Stencil::COMPARE::IS_GREATEREQUAL, Stencil::PASS::IS_INCR);
		pPrefab->AddComponent(pStencil);

		//�{�b�N�X�R���C�_�[��ǉ�����
		BoxCollider* pBoxCollider = new BoxCollider(pPrefab);
		pBoxCollider->SetSize({ 100.0f, 50.0f, 100.0f });
		pBoxCollider->SetOffset({ 0.0f, 25.0f, 0.0f });
		pPrefab->AddComponent(pBoxCollider);

		//�����̋�����ǉ�����
		Basket* pBasket = new Basket(pPrefab);
		pPrefab->AddComponent(pBasket);

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
		//�u���b�N�𐶐�����
		Object* pPrefab = new Object("Block");

		//�g�����X�t�H�[����ǉ�����
		Transform* pTransform = new Transform(pPrefab);
		pTransform->SetPos(pos);
		pPrefab->AddComponent(pTransform);

		//���f�������_�����O��ǉ�����
		Model* pModel = new Model(pPrefab);
		pModel->SetXFile(Manager::Get()->GetXFile()->Get("block_00.x"));
		pModel->SetTexture(Manager::Get()->GetTexture()->Get("block_00.png"));
		pPrefab->AddComponent(pModel);

		//�X�e���V����ǉ�����
		Stencil* pStencil = new Stencil(pPrefab, 1, Stencil::COMPARE::IS_GREATEREQUAL, Stencil::PASS::IS_INCR);
		pPrefab->AddComponent(pStencil);

		//�{�b�N�X�R���C�_�[��ǉ�����
		BoxCollider* pBoxCollider = new BoxCollider(pPrefab);
		pBoxCollider->SetSize({ 60.0f, 60.0f, 60.0f });
		pBoxCollider->SetOffset({ 0.0f, 30.0f, 0.0f });
		pPrefab->AddComponent(pBoxCollider);

		//�u���b�N�̋�����ǉ�����
		Block* pBlock = new Block(pPrefab);
		pPrefab->AddComponent(pBlock);

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
		pPrefab->AddComponent(pTransform);

		//�J������ǉ�����
		Camera* pCamera = new Camera(pPrefab);
		pPrefab->AddComponent(pCamera);

		//�o�[�h���_�J�����̋�����ǉ�����
		CameraBird* pCameraBird = new CameraBird(pPrefab);
		pPrefab->AddComponent(pCameraBird);

		//����������
		pPrefab->Init();

		//�v���n�u��Ԃ�
		return pPrefab;
	}
};

//�J�[�\��
class CursorPrefab
{
public:
	//��������
	static Object* Create(D3DXVECTOR3 pos)
	{
		//�w�i�𐶐�����
		Object* pPrefab = new Object("Cursor");

		//�g�����X�t�H�[����ǉ�����
		Transform* pTransform = new Transform(pPrefab);
		pTransform->SetPos(pos);
		pTransform->SetScale({ 0.25f, 0.25f, 0.25f });
		pPrefab->AddComponent(pTransform);

		//�l�p�`�����_�����O��ǉ�����
		PlaneXZ* pPlaneXZ = new PlaneXZ(pPrefab);
		pPlaneXZ->SetTexture(Manager::Get()->GetTexture()->Get("cursor_00.png"));
		pPrefab->AddComponent(pPlaneXZ);

		//�J�[�\���̋�����ǉ�����
		Cursor* pCursor = new Cursor(pPrefab);
		pPrefab->AddComponent(pCursor);

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

//��
class FieldPrefab
{
public:
	//��������
	static Object* Create()
	{
		//�w�i�𐶐�����
		Object* pPrefab = new Object("Field");

		//�g�����X�t�H�[����ǉ�����
		Transform* pTransform = new Transform(pPrefab);
		pTransform->SetPos({ 0.0f, 0.0f, 0.0f });
		pTransform->SetScale({ 4.0f, 1.0f, 4.0f });
		pPrefab->AddComponent(pTransform);

		//�l�p�`�����_�����O��ǉ�����
		PlaneXZ* pPlaneXZ = new PlaneXZ(pPrefab);
		pPlaneXZ->SetTexture(Manager::Get()->GetTexture()->Get("field_00.png"));
		pPrefab->AddComponent(pPlaneXZ);

		//�{�b�N�X�R���C�_�[��ǉ�����
		BoxCollider* pBoxCollider = new BoxCollider(pPrefab);
		pBoxCollider->SetSize({ Plane::BASE_SIZE.x * pTransform->GetScale().x, 1.0f, Plane::BASE_SIZE.y * pTransform->GetScale().z });
		pBoxCollider->SetOffset({ 0.0f, -0.5f, 0.0f });
		pBoxCollider->SetMass(99);   //����
		pPrefab->AddComponent(pBoxCollider);

		//����������
		pPrefab->Init();

		//�v���n�u��Ԃ�
		return pPrefab;
	}
};

//�t���[�c
class FruitPrefab
{
public:
	//��������
	static Object* Create(D3DXVECTOR3 pos, int nWeight)
	{
		//�t���[�c�𐶐�����
		Object* pPrefab = new Object("Fruit");
		pPrefab->SetTag(Object::TAG::IS_FRUIT);

		//�g�����X�t�H�[����ǉ�����
		Transform* pTransform = new Transform(pPrefab);
		pTransform->SetPos(pos);
		pTransform->SetScale({ 3.0f, 3.0f, 3.0f });
		pPrefab->AddComponent(pTransform);

		//���f�������_�����O��ǉ�����
		Model* pModel = new Model(pPrefab);
		pModel->SetXFile(Manager::Get()->GetXFile()->Get("fruit_00.x"));
		pPrefab->AddComponent(pModel);

		//�X�e���V����ǉ�����
		Stencil* pStencil = new Stencil(pPrefab, 1, Stencil::COMPARE::IS_GREATEREQUAL, Stencil::PASS::IS_INCR);
		pPrefab->AddComponent(pStencil);

		//�ݕ��̋�����ǉ�����
		Cargo* pCargo = new Cargo(pPrefab, nWeight);
		pPrefab->AddComponent(pCargo);

		//���W�b�g�{�f�B��ǉ�����
		Rigidbody* pRigidbody = new Rigidbody(pPrefab);
		pPrefab->AddComponent(pRigidbody);

		//�{�b�N�X�R���C�_�[��ǉ�����
		BoxCollider* pBoxCollider = new BoxCollider(pPrefab);
		pBoxCollider->SetSize({ 50.0f, 50.0f, 50.0f });
		pBoxCollider->SetOffset({ 0.0f, 25.0f, 0.0f });
		pBoxCollider->SetMass(4);   //����
		pPrefab->AddComponent(pBoxCollider);

		//����������
		pPrefab->Init();

		//�v���n�u��Ԃ�
		return pPrefab;
	}
};

//��
class InsectPrefab
{
public:
	//��������
	static Object* Create(D3DXVECTOR3 pos)
	{
		//���𐶐�����
		Object* pPrefab = new Object("Insect");

		//�g�����X�t�H�[����ǉ�����
		Transform* pTransform = new Transform(pPrefab);
		pTransform->SetPos(pos);
		pTransform->SetScale({ 1.0f, 1.0f, 1.0f });
		pPrefab->AddComponent(pTransform);

		//���f�������_�����O��ǉ�����
		Model* pModel = new Model(pPrefab);
		pModel->SetXFile(Manager::Get()->GetXFile()->Get("insect_00.x"));
		pPrefab->AddComponent(pModel);

		//���̋�����ǉ�����
		Insect* pInsect = new Insect(pPrefab);
		pPrefab->AddComponent(pInsect);

		//���W�b�g�{�f�B��ǉ�����
		Rigidbody* pRigidbody = new Rigidbody(pPrefab);
		pRigidbody->SetGravity(0.75f);
		pRigidbody->SetFrictionAir(0.1f);   //�󒆗p�̖��C
		pPrefab->AddComponent(pRigidbody);

		//�{�b�N�X�R���C�_�[��ǉ�����
		BoxCollider* pBoxCollider = new BoxCollider(pPrefab);
		pBoxCollider->SetSize({ 10.0f, 20.0f, 10.0f });
		pBoxCollider->SetOffset({ 0.0f, 10.0f, 0.0f });
		pBoxCollider->SetMass(2);
		pPrefab->AddComponent(pBoxCollider);

		//����������
		pPrefab->Init();

		//�v���n�u��Ԃ�
		return pPrefab;
	}
};

//�[���[
class JellyPrefab
{
public:
	//��������
	static Object* Create(D3DXVECTOR3 pos, int nWeight)
	{
		//�[���[�𐶐�����
		Object* pPrefab = new Object("Jelly");
		pPrefab->SetTag(Object::TAG::IS_JELLY);

		//�g�����X�t�H�[����ǉ�����
		Transform* pTransform = new Transform(pPrefab);
		pTransform->SetPos(pos);
		pTransform->SetScale({ 2.0f, 2.0f, 2.0f });
		pPrefab->AddComponent(pTransform);

		//���f�������_�����O��ǉ�����
		Model* pModel = new Model(pPrefab);
		pModel->SetXFile(Manager::Get()->GetXFile()->Get("jelly_00.x"));
		pPrefab->AddComponent(pModel);

		//�X�e���V����ǉ�����
		Stencil* pStencil = new Stencil(pPrefab, 1, Stencil::COMPARE::IS_GREATEREQUAL, Stencil::PASS::IS_INCR);
		pPrefab->AddComponent(pStencil);

		//�ݕ��̋�����ǉ�����
		Cargo* pCargo = new Cargo(pPrefab, nWeight);
		pPrefab->AddComponent(pCargo);

		//���W�b�g�{�f�B��ǉ�����
		Rigidbody* pRigidbody = new Rigidbody(pPrefab);
		pPrefab->AddComponent(pRigidbody);

		//�{�b�N�X�R���C�_�[��ǉ�����
		BoxCollider* pBoxCollider = new BoxCollider(pPrefab);
		pBoxCollider->SetSize({ 35.0f, 32.0f, 35.0f });
		pBoxCollider->SetOffset({ 0.0f, 16.0f, 0.0f });
		pBoxCollider->SetMass(4);   //����
		pPrefab->AddComponent(pBoxCollider);

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

//�v���C���[
class PlayerPrefab
{
public:
	//��������
	static Object* Create(D3DXVECTOR3 pos)
	{
		//�u���b�N�𐶐�����
		Object* pPrefab = new Object("Player");

		//�g�����X�t�H�[����ǉ�����
		Transform* pTransform = new Transform(pPrefab);
		pTransform->SetPos(pos);
		pTransform->SetScale({ 0.25f, 0.25f, 0.25f });
		pPrefab->AddComponent(pTransform);

		//���f�������_�����O��ǉ�����
		Model* pModel = new Model(pPrefab);
		pModel->LoadParts("motion_kabuto.txt");
		pPrefab->AddComponent(pModel);

		//�X�e���V����ǉ�����
		Stencil* pStencil = new Stencil(pPrefab, 1, Stencil::COMPARE::IS_ALWAYS, Stencil::PASS::IS_REPLACE);
		pPrefab->AddComponent(pStencil);

		//���[�V���i�[��ǉ�����
		Motioneer* pMotioneer = new Motioneer(pPrefab);
		pMotioneer->LoadMotion("motion_kabuto.txt");
		pPrefab->AddComponent(pMotioneer);

		//�v���C���[�̋�����ǉ�����
		Player* pPlayer = new Player(pPrefab);
		pPrefab->AddComponent(pPlayer);

		//���W�b�g�{�f�B��ǉ�����
		Rigidbody* pRigidbody = new Rigidbody(pPrefab);
		pPrefab->AddComponent(pRigidbody);

		//�{�b�N�X�R���C�_�[��ǉ�����
		BoxCollider* pBoxCollider = new BoxCollider(pPrefab);
		pBoxCollider->SetSize({ 50.0f, 50.0f, 50.0f });
		pBoxCollider->SetOffset({ 0.0f, 25.0f, 0.0f });
		pPrefab->AddComponent(pBoxCollider);

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
	static Object* Create()
	{
		//�X�R�A�𐶐�����
		Object* pPrefab = new Object("Score");

		//�g�����X�t�H�[����ǉ�����
		Transform2D* pTransform2D = new Transform2D(pPrefab);
		pTransform2D->SetPos({ 50.0f, 70.0f });   //�ʒu
		pTransform2D->SetSize({ 500.0f, 100.0f });   //�T�C�Y
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
		pTransform2D->SetSize({200.0f, 100.0f});   //�T�C�Y
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
		pTransform2D->SetPos({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 });   //�ʒu
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

//�L�m�R
class MushroomPrefab
{
public:
	//��������
	static Object* Create(D3DXVECTOR3 pos)
	{
		//�L�m�R�𐶐�����
		Object* pPrefab = new Object("Mushroom");
		pPrefab->SetTag(Object::TAG::IS_OBSTACLE);   //��Q��

		//�g�����X�t�H�[����ǉ�����
		Transform* pTransform = new Transform(pPrefab);
		pTransform->SetPos(pos);
		pPrefab->AddComponent(pTransform);

		//���f�������_�����O��ǉ�����
		Model* pModel = new Model(pPrefab);
		pModel->SetXFile(Manager::Get()->GetXFile()->Get("mushroom_00.x"));
		pPrefab->AddComponent(pModel);

		//�X�e���V����ǉ�����
		Stencil* pStencil = new Stencil(pPrefab, 1, Stencil::COMPARE::IS_GREATEREQUAL, Stencil::PASS::IS_INCR);
		pPrefab->AddComponent(pStencil);

		//�{�b�N�X�R���C�_�[��ǉ�����
		BoxCollider* pBoxCollider = new BoxCollider(pPrefab);
		pBoxCollider->SetSize({ 60.0f, 60.0f, 60.0f });
		pBoxCollider->SetOffset({ 0.0f, 30.0f, 0.0f });
		pPrefab->AddComponent(pBoxCollider);

		//��Q���̋�����ǉ�����
		Obstacle* pObstacle = new Obstacle(pPrefab);
		pPrefab->AddComponent(pObstacle);

		//����������
		pPrefab->Init();

		//�v���n�u��Ԃ�
		return pPrefab;
	}
};

//��
class NestPrefab
{
public:
	//��������
	static Object* Create(D3DXVECTOR3 pos)
	{
		//���𐶐�����
		Object* pPrefab = new Object("Nest");

		//�g�����X�t�H�[����ǉ�����
		Transform* pTransform = new Transform(pPrefab);
		pTransform->SetPos(pos);
		pTransform->SetScale({ 2.5f, 2.5f, 2.5f });   //�g�嗦
		pPrefab->AddComponent(pTransform);

		//���f�������_�����O��ǉ�����
		Model* pModel = new Model(pPrefab);
		pModel->SetXFile(Manager::Get()->GetXFile()->Get("nest_00.x"));
		pPrefab->AddComponent(pModel);

		//�X�e���V����ǉ�����
		Stencil* pStencil = new Stencil(pPrefab, 1, Stencil::COMPARE::IS_GREATEREQUAL, Stencil::PASS::IS_INCR);
		pPrefab->AddComponent(pStencil);

		//�{�b�N�X�R���C�_�[��ǉ�����
		BoxCollider* pBoxCollider = new BoxCollider(pPrefab);
		pBoxCollider->SetSize({ 50.0f, 50.0f, 50.0f });
		pBoxCollider->SetOffset({ 0.0f, 25.0f, 0.0f });
		pPrefab->AddComponent(pBoxCollider);

		//�����̋�����ǉ�����
		Nest* pNest = new Nest(pPrefab);
		pPrefab->AddComponent(pNest);

		//����������
		pPrefab->Init();

		//�v���n�u��Ԃ�
		return pPrefab;
	}
};

//���̐�
class NumInsectPrefab
{
public:
	//��������
	static Object* Create()
	{
		//�X�R�A�𐶐�����
		Object* pPrefab = new Object("NumInsect");

		//�g�����X�t�H�[����ǉ�����
		Transform2D* pTransform2D = new Transform2D(pPrefab);
		pTransform2D->SetPos({ 1100.0f, 650.0f });   //�ʒu
		pTransform2D->SetSize({ 200.0f, 100.0f });   //�T�C�Y
		pPrefab->AddComponent(pTransform2D);

		//���������_�����O��ǉ�����
		Number* pNumber = new Number(pPrefab);
		pNumber->SetTexture(Manager::Get()->GetTexture()->Get("number_00.png"));
		pNumber->SetDigit(3);
		pNumber->SetNumber(Timer::START_TIMER);
		pPrefab->AddComponent(pNumber);

		//�X�R�A�̋�����ǉ�����
		NumInsect* pNumInsect = new NumInsect(pPrefab);
		pPrefab->AddComponent(pNumInsect);

		//����������
		pPrefab->Init();

		//�v���n�u��Ԃ�
		return pPrefab;
	}
};

//�E�F�C�|�C���g
class WeypointPrefab
{
public:
	//��������
	static Object* Create(D3DXVECTOR3 pos, int nId, std::string sFileName)
	{
		//�L�m�R�𐶐�����
		Object* pPrefab = new Object("Waypoint" + std::to_string(nId));
		pPrefab->SetTag(Object::TAG::IS_OBSTACLE);   //��Q��

		//�g�����X�t�H�[����ǉ�����
		Transform* pTransform = new Transform(pPrefab);
		pTransform->SetPos(pos);
		pTransform->SetScale({ 0.25f, 0.25f, 0.25f });
		pPrefab->AddComponent(pTransform);

		//���f�������_�����O��ǉ�����
		Billboard* pBillboard = new Billboard(pPrefab);
		pBillboard->SetTexture(Manager::Get()->GetTexture()->Get(sFileName));
		pPrefab->AddComponent(pBillboard);

		//����������
		pPrefab->Init();

		//�v���n�u��Ԃ�
		return pPrefab;
	}
};

#endif // !_PREFAB_H_
