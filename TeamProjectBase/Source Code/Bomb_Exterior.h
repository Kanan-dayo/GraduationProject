//------------------------------------------------------------------------------
//
//�{���̊O������  [bomb_exterior.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _BOMB_EXTERIOR_H_
#define _BOMB_EXTERIOR_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CScene3D;
class CSceneX;

class CBomb_Exterior
{
	//�O���̃^�C�v
	enum EXTERIOR_TYPE
	{
		NONE = 0,		//�����Ȃ�
		BATTERY,		//�o�b�e���[
		MAX,			//
	};


public:
	CBomb_Exterior();
	virtual ~CBomb_Exterior();
	static U_ptr<CBomb_Exterior> CreateBombExterior(D3DXMATRIX *pBombMtx);

	Vec<S_ptr<CSceneX>> GetBatteryPtrList() { return m_pBatteryList; };
	int GetBatteryNum() { return m_nBatteryNum; };

private:
	Vec<S_ptr<CSceneX>> m_pBatteryList;		//�o�b�e���[�̃��X�g
	Vec<EXTERIOR_TYPE> m_ExteriorList;		//�O���ɉ������邩�̃��X�g
	int m_nBatteryNum;						//�o�b�e���[��

	void SetExterior();						//�O���ɉ��������邩���߂�
	void Create(D3DXMATRIX *pBombMtx);		//�����֐�

	void CalcExteriorPosition(int const nCnt, D3DXVECTOR3 &pos, D3DXVECTOR3 &rot);

};
#endif