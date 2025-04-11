//=============================================================
//
// �����L���O [ranking_system.cpp]
// Author: Ito Kotaro
// 
//=============================================================
#include "ranking_system.h"

const std::string RankingSystem::RANKING_PATH = "data\\ranking_data.bin";
const int RankingSystem::MAX_DATA = 5;
//=============================================================
// [RankingSystem] �f�[�^��ǉ�
//=============================================================
void RankingSystem::RegisterData(int score)
{
	int data[MAX_DATA];
	for (int i = 0; i < MAX_DATA; i++)
	{
		data[i] = -1;
	}

	// �t�@�C�����J��
	FILE* file;
	file = fopen(RANKING_PATH.c_str(), "rb");

	if (file != nullptr)
	{
		// �f�[�^�ǂݍ���
		fread(&data, sizeof(data), 1, file);

		// �t�@�C�������
		fclose(file);
	}

	// �Ō���ɃX�R�A��ǉ�����
	if (data[MAX_DATA-1] <= score)
	{ // �����L���O�ɓ���Ƃ�
		data[MAX_DATA-1] = score;
	}
	
	// ����ւ���
	for (int i = MAX_DATA-1; i > 0; i--)
	{
		if (data[i] < data[i - 1] && data[i - 1] == -1)
		{
			int change = data[i];
			data[i] = data[i - 1];
			data[i - 1] = change;
		}
	}

	// �t�@�C�����J��
	file = fopen(RANKING_PATH.c_str(), "wb");
	
	if (file != nullptr)
	{
		// �t�@�C���ɏ�������
		fwrite(data, sizeof(data), 1, file);

		// �t�@�C�������
		fclose(file);
	}
}

//=============================================================
// [RankingSystem] �X�R�A���烉���L���O�ʒu���擾����
//=============================================================
int RankingSystem::GetRanking(int score)
{
	int data[10];

	// �t�@�C�����J��
	FILE* file;
	file = fopen(RANKING_PATH.c_str(), "rb");

	if (file != nullptr)
	{
		// �f�[�^�ǂݍ���
		fread(&data, sizeof(data), 1, file);

		// �t�@�C�������
		fclose(file);
	}
	else
	{
		// �f�[�^���Ȃ�
		return 0;
	}

	// �X�R�A����ʒu����肷��
	for (int i = 0; i < MAX_DATA; i++)
	{
		if (data[i] == score)
		{
			return i + 1;
		}
	}

	return 0;
}

//=============================================================
// [RankingSystem] �X�R�A���烉���L���O�ʒu���擾����
//=============================================================
int RankingSystem::GetScore(int rank)
{
	int data[10];

	// �t�@�C�����J��
	FILE* file;
	file = fopen(RANKING_PATH.c_str(), "rb");

	if (file != nullptr)
	{
		// �f�[�^�ǂݍ���
		fread(&data, sizeof(data), 1, file);

		// �t�@�C�������
		fclose(file);
	}
	else
	{
		// �f�[�^���Ȃ�
		return -1;
	}

	// ���ʂ���X�R�A���擾����
	if (0 <= rank && rank < MAX_DATA)
	{
		return data[rank];
	}
	return -1;
}