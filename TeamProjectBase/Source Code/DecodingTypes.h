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
typedef struct _SETINGBASE
{
	_SETINGBASE() :
		pos(MYLIB_VEC3_UNSET),
		size(MYLIB_VEC2_UNSET),
		col(MYLIB_D3DXCOR_SET){}
	_SETINGBASE(D3DXVECTOR3& pos, D3DXVECTOR2& size, D3DXCOLOR& col) :
		pos(pos), size(size), col(col) {}
	_SETINGBASE(float fPosX, float fPosY, float fPosZ, float fSizeX, float fSizeY, float fColR, float fColG, float fColB, float fColA) :
		pos(fPosX, fPosY, fPosZ), size(fSizeX, fSizeY), col(fColR, fColG, fColB, fColA) {}

	FLOAT3           pos;			// �ʒu
	FLOAT2           size;			// �傫��
	D3DXCOLOR        col;			// �F
}SETINGBASE;

typedef struct _SETINGINFO : public SETINGBASE
{
	_SETINGINFO() :								// �R���X�g���N�^
		SETINGBASE(),
		fAngle(MYLIB_FLOAT_UNSET),
		OriginType(ORIGINVERTEXTYPE_CENTER),
		bDisp(false),
		nParentID(-1) {}
	_SETINGINFO(								// �R���X�g���N�^
		D3DXVECTOR3& pos, D3DXVECTOR2& size, D3DXCOLOR& col, float fAngle, ORIGINVERTEXTYPE OriginType, bool bDisp, int nParentID) :
		SETINGBASE(pos, size, col), fAngle(fAngle), OriginType(OriginType), bDisp(bDisp), nParentID(nParentID) {}
	_SETINGINFO(								// �R���X�g���N�^
		float fPosX, float fPosY, float fPosZ, float fSizeX, float fSizeY, float fColR, float fColG, float fColB, float fColA, float fAngle, int nOriginTytpe, bool bDisp, int nParentID) :
		SETINGBASE(fPosX, fPosY, fPosZ, fSizeX, fSizeY, fColR, fColG, fColB, fColA), fAngle(fAngle), OriginType((ORIGINVERTEXTYPE)nOriginTytpe), bDisp(bDisp), nParentID(nParentID) {}

	inline _SETINGINFO operator = (SETINGBASE &Base)
	{
		this->col = Base.col;
		this->pos = Base.pos;
		this->size = Base.size;

		return *this;
	}

	float            fAngle;		// �p�x
	ORIGINVERTEXTYPE OriginType;	// ���_�^�C�v
	bool             bDisp;			// �`��t���O
	int              nParentID;		// �e��ID
}SETINGINFO;

typedef struct _WINDOW_SETING : public SETINGBASE
{
	_WINDOW_SETING() :
		SETINGBASE(), AspectRatio(), SizeScal() {}
	_WINDOW_SETING(D3DXVECTOR3& pos, D3DXVECTOR2& size, D3DXCOLOR& col, D3DXVECTOR2& AspectRatio, D3DXVECTOR2& SizeScal) :
		SETINGBASE(pos, size, col), AspectRatio(AspectRatio), SizeScal(SizeScal) {}
	_WINDOW_SETING(float fPosX, float fPosY, float fPosZ, float fSizeX, float fSizeY, float fColR, float fColG, float fColB, float fColA, float fAspectRatioX, float fAspectRatioY, float fSizeScalX, float fSizeScalY) :
		SETINGBASE(fPosX, fPosY, fPosZ, fSizeX, fSizeY, fColR, fColG, fColB, fColA), AspectRatio(fAspectRatioX, fAspectRatioY), SizeScal(fSizeScalX, fSizeScalY) {}

	inline _WINDOW_SETING operator = (SETINGBASE &Base)
	{
		this->col = Base.col;
		this->pos = Base.pos;
		this->size = Base.size;

		return *this;
	}

	FLOAT2 AspectRatio;		// �A�X�y�N�g��
	FLOAT2 SizeScal;		// �E�B���h�E�̊g�k��

}WINDOW_SETING;

typedef struct _POLYVERTEXSUVINFO
{
	_POLYVERTEXSUVINFO() : pos(0.0f, 0.0f), size(0.0f, 0.0f) {}
	_POLYVERTEXSUVINFO(UVINFO& pos, UVINFO& size) : pos(pos), size(size) {}
	union {
		struct {
			UVINFO pos;
			UVINFO size;
		};
		UVINFO uv[2];
		float   m[4];
	};

}POLYVERTEXSUVINFO;

#endif