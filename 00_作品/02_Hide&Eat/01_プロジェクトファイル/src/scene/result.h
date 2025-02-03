//=============================================================
//
// ���U���g�V�[�� [result.h]
// Author: Ito Kotaro
// 
//=============================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "scene.h"

// ���U���g�V�[��
class CResultScene : public CScene
{
public:
	void Init() override;			// ������
	void Uninit() override;			// �I��
	void Update() override;		// �X�V
	void Draw() override;			// �`��
	void SetScore(const int& score) { m_score = score; }
private:
	GameObject* m_timeNumText;
	int m_score;
};

#endif // !_RESULT_H_
