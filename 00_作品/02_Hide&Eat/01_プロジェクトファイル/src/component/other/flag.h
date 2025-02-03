//=============================================================
//
// �t���O [flag.h]
// Author: Ito Kotaro
// 
//=============================================================
#ifndef _FLAG_H_
#define _FLAG_H_

// �t���O
// - �ʒu���Ǘ����܂�
class Flag
{
public:
	// ���ׂẴt���O���擾����
	static std::vector<Flag>& GetAllFlags() { return m_allFlags; }
private:
	// ���O
	std::string m_name;

	// �ʒu
	D3DXVECTOR3 m_pos;

	// ���ׂẴt���O
	static std::vector<Flag> m_allFlags;
};

#endif // !_FLAG_H_
