//------------------------------------------------------------------------------
//
//���W���[���p�[�c�̃L�[�p�b�h  [module_parts_No2_ShapeKey.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "module_parts_No3_Wire.h"
#include "module_No3_LampAndWire.h"
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
CModule_Parts_No3_Wire::CModule_Parts_No3_Wire()
{
	m_Wire = CModule_No3_LampAndWire::WIRE::NONE;
	m_WireColor = MagentaColor;
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CModule_Parts_No3_Wire::~CModule_Parts_No3_Wire()
{

}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CModule_Parts_No3_Wire::Init()
{
	//���f�����ݒ�
	BindModelInfo(CModelInfo::GetModelInfo(CModelInfo::MODEL_MODULEPARTS_NO3_WIRE));

	CSceneX::Init();

	return S_OK;
}

//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CModule_Parts_No3_Wire::Update()
{
	CSceneX::Update();
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CModule_Parts_No3_Wire::Draw()
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
void CModule_Parts_No3_Wire::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}
//------------------------------------------------------------------------------
//���C���[�J���[�ݒ�
//------------------------------------------------------------------------------
void CModule_Parts_No3_Wire::SetWireCol(CModule_No3_LampAndWire::WIRE wirecol)
{
	m_Wire = wirecol;

	switch (m_Wire)
	{

	case CModule_No3_LampAndWire::RED:
		m_WireColor = RedColor;
		break;
	case CModule_No3_LampAndWire::BLUE:
		m_WireColor = BlueColor;
		break;
	case CModule_No3_LampAndWire::GREEN:
		m_WireColor = GreenColor;
		break;
	case CModule_No3_LampAndWire::YELLOW:
		m_WireColor = YellowColor;
		break;
	case CModule_No3_LampAndWire::WHITE:
		m_WireColor = WhiteColor;
		break;
	case CModule_No3_LampAndWire::BLACK:
		m_WireColor = BlackColor;
		break;


	}


}
