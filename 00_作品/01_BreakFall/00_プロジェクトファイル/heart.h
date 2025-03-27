//==========================================================================================================
//
// �n�[�g�̏���[heart.h]
// Author ItouKotaro
//
//==========================================================================================================
#ifndef _HEART_H_
#define _HEART_H_

#include "behavior.h"

//�n�[�gUI�i�P�́j
class HeartUI : public Behavior	//�i�e�j����
{
public:
	HeartUI(Object* pObject) : Behavior(pObject), m_active(true){}
	void Init() override;
	void Update() override{}
	void SetActive(const bool& active);
private:
	bool m_active;	// �n�[�g���L����
};

//�n�[�g�}�l�[�W���[
class HeartManager : public Behavior	//�i�e�j����
{
public:
	HeartManager(Object* pObject) : Behavior(pObject), m_value(MAX_HEART), m_isAlive(true){}
	void Init() override;
	void Update() override;

	//�n�[�g�񕜁i+1�j
	void RecoveryHeart();
	//�n�[�g�_���[�W�i-1�j
	void DamageHeart();
	//�̗͑S���̃_���[�W��^����
	void AllDamageHeart();

	//�����Ă��邩
	bool IsAlive() { return m_isAlive; }

private:
	static const int MAX_HEART = 3;
	static const float HEART_SIZE;
	static const float HEART_SPACE;

	int m_value;									//�n�[�g�i�̗́j
	bool m_isAlive;								//�����Ă��邩
	Object* m_heartUI[MAX_HEART];	//�n�[�gUI
};

#endif // !_HEART_H_
