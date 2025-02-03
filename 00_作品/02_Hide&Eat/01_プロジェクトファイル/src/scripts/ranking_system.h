//=============================================================
//
// �����L���O [ranking_system.h]
// Author: Ito Kotaro
// 
//=============================================================
#ifndef _RANKING_SYSTEM_H_
#define _RANKING_SYSTEM_H_

// �����L���O�V�X�e��
class RankingSystem
{
public:
	// �f�[�^�o�^
	void RegisterData(int score);

	// ���ʂ��擾����
	int GetRanking(int score);

	// ���ʂ���X�R�A���擾����
	int GetScore(int rank);

	static const std::string RANKING_PATH;	// �����L���O�̃p�X
	static const int MAX_DATA;						// �ő�f�[�^
private:
	
};

#endif // !_RANKING_SYSTEM_H_
