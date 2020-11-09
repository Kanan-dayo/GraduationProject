//------------------------------------------------------------------------------
//
//���W���[���̃{�^������  [module_Button.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "Bomb_Exterior.h"
#include "modelinfo.h"
#include "scene3D.h"
#include "sceneX.h"

//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define EXTERIOR_OFFSET (D3DXVECTOR3(200.0f,100.0f,0.0f))
//#define EXTERIOR_OFFSET (D3DXVECTOR3(200.0f,100.0f,0.0f))
//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CBomb_Exterior::CBomb_Exterior()
{
	m_pBatteryList.clear();
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CBomb_Exterior::~CBomb_Exterior()
{
	m_pBatteryList.clear();
}

//------------------------------------------------------------------------------
//���e�̊O������
//------------------------------------------------------------------------------
U_ptr<CBomb_Exterior> CBomb_Exterior::CreateBombExterior(D3DXMATRIX * pBombMtx)
{
	//�������m��
	U_ptr<CBomb_Exterior> pPtr = std::make_unique<CBomb_Exterior>();

	//nullcheck
	if (pPtr)
	{
		//�o�b�e���[����
		pPtr->m_pBatteryList.emplace_back(CSceneX::CreateShared(D3DXVECTOR3(EXTERIOR_OFFSET.x, EXTERIOR_OFFSET.y, EXTERIOR_OFFSET.z), ZeroVector3,
																pBombMtx, CScene::OBJTYPE_BOMB_EXTERIOR, CModelInfo::MODEL_MODULE_NONE));

		//return
		return std::move(pPtr);
	}

	//return
	return nullptr;
}
