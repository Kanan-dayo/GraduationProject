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
#define KEYPAD_SYMBOL_OFFSET				(D3DXVECTOR3(0.0f,0.0f,-6.5f))
#define KEYPAD_SYMBOLPOLYGON_SIZE			(D3DXVECTOR3(12.0f,12.0f,0.0f))
#define KEYPAD_LIGHT_REDLIGHTING_TIME		(90)

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CModule_Parts_No3_Wire::CModule_Parts_No3_Wire()
{
	m_pShape.reset();
	m_Shape = CModule_No2_ShapeKeyPad::SHAPE::NONE;
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CModule_Parts_No3_Wire::~CModule_Parts_No3_Wire()
{
	m_pShape.reset();
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CModule_Parts_No3_Wire::Init()
{
	//���f�����ݒ�
	BindModelInfo(CModelInfo::GetModelInfo(CModelInfo::MODEL_MODULEPARTS_NO2_KEYPAD));

	//�����̐���
	m_pShape = CSceneBase::ScenePolygonCreateShared<CScene3D>(KEYPAD_SYMBOL_OFFSET, KEYPAD_SYMBOLPOLYGON_SIZE, WhiteColor,
		CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_MODULEPARTS_MODULE01), CScene::OBJTYPE_MODULE_PARTS_SYMBOL);

	//�e�}�g���b�N�X�ݒ�
	m_pShape->SetParentMtxPtr(GetMtxWorldPtr());

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
	CSceneX::Draw();
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
//�V���{���̐ݒ�
//------------------------------------------------------------------------------
void CModule_Parts_No3_Wire::SetShape(CModule_No2_ShapeKeyPad::SHAPE shape)
{
	// Shape�ݒ�
	m_Shape = shape;

	//UV�ݒ�
	m_pShape->SetAnimation(CHossoLibrary::CalcUV_StaticFunc((int)shape, CTexture::SEPARATE_TEX_MODULEPARTS_MODULE01),
							CTexture::GetSparateTex_UVSize(CTexture::SEPARATE_TEX_MODULEPARTS_MODULE01));
}
