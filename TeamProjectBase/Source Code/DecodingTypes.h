//*************************************************************************************************************
//
// ��Ǐ��̍\����[���� [DecodingTypes.h]
// Author:IKUTO SEKINE
//
//*************************************************************************************************************
#ifndef _DECODINGTYPES_H_
#define _DECODINGTYPES_H_

//-------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------------------
#include "Mylibrary.h"

//-------------------------------------------------------------------------------------------------------------
// �\���̒�`
//-------------------------------------------------------------------------------------------------------------
typedef struct _SETINGINFO
{
	_SETINGINFO() :								// �R���X�g���N�^
		pos(MYLIB_VEC3_UNSET),
		size(MYLIB_VEC2_UNSET),
		col(MYLIB_D3DXCOR_SET),
		fAngle(MYLIB_FLOAT_UNSET),
		OriginType(ORIGINVERTEXTYPE_CENTER),
		bDisp(false),
		nParentID(-1) {}
	_SETINGINFO(								// �R���X�g���N�^
		D3DXVECTOR3& pos, D3DXVECTOR2& size, D3DXCOLOR& col, float fAngle, ORIGINVERTEXTYPE OriginType, bool bDisp,int nParentID) :
		pos(pos), size(size), col(col), fAngle(fAngle), OriginType(OriginType), bDisp(bDisp), nParentID(nParentID) {}

	_SETINGINFO(float fPosX, float fPosY, float fPosZ, float fSizeX, float fSizeY, float fColR, float fColG, float fColB, float fColA, float fAngle, int nOriginTytpe, bool bDisp, int nParentID) :
		pos(fPosX, fPosY, fPosZ), size(fSizeX, fSizeY), col(fColR, fColG, fColB, fColA), fAngle(fAngle), OriginType((ORIGINVERTEXTYPE)nOriginTytpe), bDisp(bDisp), nParentID(nParentID) {}


	FLOAT3           pos;			// �ʒu
	FLOAT2           size;			// �傫��
	D3DXCOLOR        col;			// �F
	float            fAngle;		// �p�x
	ORIGINVERTEXTYPE OriginType;	// ���_�^�C�v
	bool             bDisp;			// �`��t���O
	int              nParentID;		// �e��ID
}SETINGINFO;

#endif