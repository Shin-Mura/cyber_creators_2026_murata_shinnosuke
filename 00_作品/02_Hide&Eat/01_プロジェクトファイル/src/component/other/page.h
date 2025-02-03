//=============================================================
//
// �y�[�W [page.h]
// Author: Ito Kotaro
// 
//=============================================================
#ifndef _PAGE_H_
#define _PAGE_H_

#include "component.h"

// �y�[�W�R���|�[�l���g
class Pages : public Component
{
public:
	Pages() : m_pageIdx(0){}

	// �y�[�W��ǉ�����
	void SetNumPage(UINT pages);

	// �I�u�W�F�N�g��o�^����
	void AddObject(UINT page, GameObject* obj);

	// �I�u�W�F�N�g�̓o�^����������
	void RemoveObject(UINT page, GameObject* obj);

	// �y�[�W��ݒ肷��
	void SetPage(UINT page);

	// ���݂̃y�[�W�����擾����
	UINT GetPage() { return m_pageIdx; }

	// �y�[�W�ɓo�^����Ă��邷�ׂẴI�u�W�F�N�g���\���ɂ���
	void AllHideObjects();
private:
	UINT m_pageIdx;
	std::vector<std::vector<GameObject*>> m_pages;
};

#endif // !_PAGE_H_
