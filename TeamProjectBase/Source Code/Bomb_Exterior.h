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
	U_ptr<CBomb_Exterior> CreateBombExterior(D3DMATRIX *pBombMtx);

private:
	Vec<CSceneX> m_pBatteryList;


};
#endif