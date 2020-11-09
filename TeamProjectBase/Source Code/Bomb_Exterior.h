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
public:
	CBomb_Exterior();
	virtual ~CBomb_Exterior();
	static U_ptr<CBomb_Exterior> CreateBombExterior(D3DXMATRIX *pBombMtx);

	Vec<S_ptr<CSceneX>> GetBatteryPtrList() { return m_pBatteryList; };

private:
	Vec<S_ptr<CSceneX>> m_pBatteryList;


};
#endif