//==========================================================================================================
//
//�v���n�u�̏���[prefab.h]
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
#include "rigidbody.h"
#include "transform.h"

#include "menu.h"
#include "model.h"
#include "number.h"
#include "plane.h"
#include "square.h"

#include "body.h"
#include "block.h"
#include "camera_tps.h"
#include "fade.h"
#include "pause_menu.h"
#include "player.h"
#include "timer.h"
#include "title_menu.h"

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

//��
class BodyPrefab
{
public:
	//��������
	static Object* Create(Object* pPlayer, D3DXVECTOR3 pos)
	{
		//�v���C���[�𐶐�����
		Object* pPrefab = new Object("Body");

		//�g�����X�t�H�[����ǉ�����
		Transform* pTransform = new Transform(pPrefab);
		pTransform->SetPos(pos);
		pTransform->SetScale({ 0.125f, 0.125f, 1.0f });
		pPrefab->AddComponent(pTransform);

		//�l�p�`�����_�����O��ǉ�����
		PlaneY* pPlaneY = new PlaneY(pPrefab);
		pPlaneY->SetTexture(Manager::Get()->GetTexture()->Get("player_00.png"));
		pPrefab->AddComponent(pPlaneY);

		//�{�b�N�X�R���C�_�[��ǉ�����
		BoxCollider* pBoxCollider = new BoxCollider(pPrefab);
		pBoxCollider->SetSize({ Plane::BASE_SIZE.x * pTransform->GetScale().x, Plane::BASE_SIZE.y * pTransform->GetScale().y, 5.0f });
		pBoxCollider->Trigger();
		pPrefab->AddComponent(pBoxCollider);

		//�v���C���[�̋�����ǉ�����
		Body* pBody = new Body(pPrefab, pPlayer);
		pPrefab->AddComponent(pBody);

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
	static Object* Create()
	{
		//�u���b�N�𐶐�����
		Object* pPrefab = new Object("Block");

		//�g�����X�t�H�[����ǉ�����
		Transform* pTransform = new Transform(pPrefab);
		pPrefab->AddComponent(pTransform);

		//���f�������_�����O��ǉ�����
		Model* pModel = new Model(pPrefab);
		pModel->SetXFile(Manager::Get()->GetXFile()->Get("block_00.x"));
		pModel->SetTexture(Manager::Get()->GetTexture()->Get("block_00.png"));
		pPrefab->AddComponent(pModel);

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

		////TPS�J�����̋�����ǉ�����
		//CameraTPS* pCameraTPS = new CameraTPS(pPrefab);
		//pPrefab->AddComponent(pCameraTPS);

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

//�w�i
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

//�v���C���[
class PlayerPrefab
{
public:
	//��������
	static Object* Create(D3DXVECTOR3 pos, int nId)
	{
		//�v���C���[�𐶐�����
		Object* pPrefab = new Object("Player");
		pPrefab->SetTag(Object::TAG::IS_PLAYER);

		//�g�����X�t�H�[����ǉ�����
		Transform* pTransform = new Transform(pPrefab);
		pTransform->SetPos(pos);
		pTransform->SetScale({ 0.125f, 0.125f, 1.0f });
		pPrefab->AddComponent(pTransform);

		//�l�p�`�����_�����O��ǉ�����
		PlaneY* pPlaneY = new PlaneY(pPrefab);
		pPlaneY->SetTexture(Manager::Get()->GetTexture()->Get("player_00.png"));
		pPrefab->AddComponent(pPlaneY);

		//���W�b�g�{�f�B��ǉ�����
		Rigidbody* pRigidbody = new Rigidbody(pPrefab);
		pRigidbody->SetGravity(0.0f);   //�d�͖���
		pRigidbody->SetFriction(0.1f);   //����
		pRigidbody->SetFrictionAir(0.1f);
		pPrefab->AddComponent(pRigidbody);

		//�{�b�N�X�R���C�_�[��ǉ�����
		BoxCollider* pBoxCollider = new BoxCollider(pPrefab);
		pBoxCollider->SetSize({ Plane::BASE_SIZE.x * pTransform->GetScale().x, Plane::BASE_SIZE.y * pTransform->GetScale().y, 5.0f});
		pPrefab->AddComponent(pBoxCollider);

		//�v���C���[�̋�����ǉ�����
		Player* pPlayer = new Player(pPrefab, nId);
		pPrefab->AddComponent(pPlayer);

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

#endif // !_PREFAB_H_
