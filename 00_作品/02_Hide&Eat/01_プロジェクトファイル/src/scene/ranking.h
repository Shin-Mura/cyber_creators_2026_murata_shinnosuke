//=============================================================
//
// �Q�[���V�[�� [ranking.h]
// Author: Ito Kotaro
// 
//=============================================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "scene.h"

// �����L���O�V�[��
class CRankingScene : public CScene
{
public:
	void Init() override;			// ������
	void Uninit() override;			// �I��
	void Update() override;		// �X�V
	void Draw() override;			// �`��
	void SetRank(const int& rank) { m_rank = rank; }
private:
	int m_rank;
};

#endif // !_RANKING_H_
