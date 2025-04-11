//=============================================================
//
// �y�[�W [page.cpp]
// Author: Ito Kotaro
// 
//=============================================================
#include "page.h"

//=============================================================
// [Pages] �y�[�W�̒ǉ�
//=============================================================
void Pages::SetNumPage(UINT pages)
{
	m_pages.resize(pages);
}

//=============================================================
// [Pages] �I�u�W�F�N�g��ǉ�����
//=============================================================
void Pages::AddObject(UINT page, GameObject* obj)
{
	if (0 <= page && page < m_pages.size())
	{ // �y�[�W�͈͓��̂Ƃ�

		// ���ɃI�u�W�F�N�g���o�^�ς݂łȂ������m�F����
		for (auto itr = m_pages[page].begin(); itr != m_pages[page].end(); itr++)
		{
			if (*itr == obj)
			{ // ��v����Ƃ�
				return;
			}
		}

		// �y�[�W�ɃI�u�W�F�N�g��ǉ�����
		m_pages[page].push_back(obj);
	}
}

//=============================================================
// [Pages] �I�u�W�F�N�g���폜����
//=============================================================
void Pages::RemoveObject(UINT page, GameObject* obj)
{
	if (0 <= page && page < m_pages.size())
	{ // �y�[�W�͈͓��̂Ƃ�
		// ���ɃI�u�W�F�N�g���o�^�ς݂łȂ������m�F����
		for (auto itr = m_pages[page].begin(); itr != m_pages[page].end(); itr++)
		{
			if (*itr == obj)
			{ // ��v����Ƃ�
				m_pages[page].erase(itr);
				return;
			}
		}
	}
}

//=============================================================
// [Pages] �y�[�W��ݒ肷��
//=============================================================
void Pages::SetPage(UINT page)
{
	if (0 <= page && page < m_pages.size())
	{ // �y�[�W�͈͓��̂Ƃ�
		// ���݂̃y�[�W�̃I�u�W�F�N�g���\���ɂ���
		for (auto itr = m_pages[m_pageIdx].begin(); itr != m_pages[m_pageIdx].end(); itr++)
		{
			(*itr)->SetActive(false);
		}

		// �V�����y�[�W�̃I�u�W�F�N�g��\������
		for (auto itr = m_pages[page].begin(); itr != m_pages[page].end(); itr++)
		{
			(*itr)->SetActive(true);
		}
		m_pageIdx = page;
	}
}

//=============================================================
// [Pages] �y�[�W�ɓo�^����Ă���I�u�W�F�N�g���ׂĂ��\���ɂ���
//=============================================================
void Pages::AllHideObjects()
{
	for (auto pageItr = m_pages.begin(); pageItr != m_pages.end(); pageItr++)
	{
		for (auto objItr = (*pageItr).begin(); objItr != (*pageItr).end(); objItr++)
		{
			(*objItr)->SetActive(false);
		}
	}
}