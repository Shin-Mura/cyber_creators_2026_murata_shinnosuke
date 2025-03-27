//==========================================================================================================
//
// �����L���O�̏���[ranking.h]
// Author ItouKotaro
//
//==========================================================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include <iostream>

// �����L���O�V�X�e��
class RankingSystem
{
public:
	// �C���X�^���X�̎擾
	static RankingSystem* GetInstance()
	{
		static RankingSystem instance;
		return &instance;
	}

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

#endif // !_RANKING_H_
