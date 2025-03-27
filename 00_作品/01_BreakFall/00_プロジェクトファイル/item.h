//========================================================================================================
//
// �A�C�e���̏���[item.h]
// Author ItoKotaro
//
//========================================================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "behavior.h"

//�A�C�e���i���j
class Item : public Behavior		//�i�e�j����
{
public:
	Item(Object* pObject) : Behavior(pObject) {}
	void Init() override;
	void Update() override;
	void Collision(Object* pObject, Physics::CONTACT contact) override;

	static const float SIZE;
	static const float FALL_SPEED;
private:
	virtual void onHit() = 0;
};

//�ʑ��₷
class AddBallItem : public Item
{
public:
	AddBallItem(Object* pObject) : Item(pObject){}
	void Init() { Item::Init(); }
	void Update() { Item::Update(); }
private:
	void onHit() override;
};

//�u���b�N����
class ClearBlockItem : public Item
{
public:
	ClearBlockItem(Object* pObject) : Item(pObject) {}
	void Init() { Item::Init(); }
	void Update() { Item::Update(); }
private:
	void onHit() override;
};

//�⏕�o�[
class AssistBarItem : public Item
{
public:
	AssistBarItem(Object* pObject) : Item(pObject) {}
	void Init() { Item::Init(); }
	void Update() { Item::Update(); }
private:
	void onHit() override;
};

//�n�[�g����
class AddHeartItem : public Item
{
public:
	AddHeartItem(Object* pObject) : Item(pObject) {}
	void Init() { Item::Init(); }
	void Update() { Item::Update(); }
private:
	void onHit() override;
};

#endif // !_ITEM_H_
