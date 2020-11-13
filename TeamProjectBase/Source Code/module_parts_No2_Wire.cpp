//------------------------------------------------------------------------------
//
//���W���[���p�[�c�̃L�[�p�b�h  [module_parts_No1_ShapeKey.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "module_parts_No2_Wire.h"
#include "module_No2_LampAndWire.h"
#include "renderer.h"
#include "manager.h"
#include "modelinfo.h"
#include "particle.h"
#include "timer.h"
#include "scene3D.h"
#include "keyboard.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CModule_Parts_No2_Wire::CModule_Parts_No2_Wire()
{
	m_Wire = CModule_No2_LampAndWire::WIRE::NONE;
	m_WireColor = MagentaColor;
	m_bCut = false;
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CModule_Parts_No2_Wire::~CModule_Parts_No2_Wire()
{

}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CModule_Parts_No2_Wire::Init()
{
	//���f�����ݒ�
	BindModelInfo(CModelInfo::GetModelInfo(CModelInfo::MODEL_MODULEPARTS_NO3_WIRE));

	CSceneX::Init();

	return S_OK;
}

//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CModule_Parts_No2_Wire::Update()
{
	CSceneX::Update();
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CModule_Parts_No2_Wire::Draw()
{
	//�n�[�h�G�b�W�`��
	//�I������Ă��郂�f���̂�
	CSceneX::DrawHardEdgeStencil();

	//���[���h�}�g���b�N�X�̌v�Z
	CSceneX::CalcMtx_IncludeParentMtx();

	//���b�V���`��@�}�e���A���F��ݒ�
	CSceneX::DrawMesh_SetMaterial(m_WireColor, false, { 2 });

	//CSceneX::Draw();
}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CModule_Parts_No2_Wire::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}
//------------------------------------------------------------------------------
//���C���[�J���[�ݒ�
//------------------------------------------------------------------------------
void CModule_Parts_No2_Wire::SetWire(CModule_No2_LampAndWire::WIRE wire)
{
	m_Wire = wire;

	switch (m_Wire)
	{

	case CModule_No2_LampAndWire::RED:
		m_WireColor = RedColor;
		break;
	case CModule_No2_LampAndWire::BLUE:
		m_WireColor = BlueColor;
		break;
	case CModule_No2_LampAndWire::GREEN:
		m_WireColor = GreenColor;
		break;
	case CModule_No2_LampAndWire::YELLOW:
		m_WireColor = YellowColor;
		break;
	case CModule_No2_LampAndWire::WHITE:
		m_WireColor = WhiteColor;
		break;
	case CModule_No2_LampAndWire::BLACK:
		m_WireColor = BlackColor;
		break;


	}


}
