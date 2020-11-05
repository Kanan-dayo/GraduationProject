//------------------------------------------------------------------------------
//
//Scene�̃x�[�X�N���X [SceneBase.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//�C���N���[�h
//-----------------------------------------------------------------------------
#include "SceneBase.h"
//-----------------------------------------------------------------------------
//�R���X�g���N�^
//-----------------------------------------------------------------------------
CSceneBase::CSceneBase()
{
	//������
	m_pos = ZeroVector3;
	m_size = ZeroVector3;
	m_rot = ZeroVector3;
	m_col = WhiteColor;
	m_scale = OneVector3;
	m_bLighting = true;
	D3DXMatrixIdentity(&m_mtxWorld);
	m_pParentMtx = nullptr;
	m_bDisp = true;
	m_pVtxBuff = nullptr;
	m_pTexture = nullptr;
}

//-----------------------------------------------------------------------------
//�f�X�g���N�^
//-----------------------------------------------------------------------------
CSceneBase::~CSceneBase()
{
	//nullcheck
	if (m_pVtxBuff)
	{
		//���_�o�b�t�@�J��
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//-----------------------------------------------------------------------------
//�}�g���b�N�X�̌v�Z�@�e�̃}�g���b�N�X�̍������܂�
//-----------------------------------------------------------------------------
void CSceneBase::CalcMtx_IncludeParentMtx()
{
	//�}�g���b�N�X�v�Z
	CHossoLibrary::CalcMatrix(GetMtxWorldPtr(), GetPos(), GetRot(), GetScale());

	//nullcheck
	if (GetParentMtxPtr())
	{
		//�e�̃}�g���b�N�X���|�����킹��
		*GetMtxWorldPtr() *= *GetParentMtxPtr();
	}

}
