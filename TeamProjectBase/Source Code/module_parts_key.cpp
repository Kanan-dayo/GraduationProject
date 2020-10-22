//------------------------------------------------------------------------------
//
//���W���[���̏���  [module.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "module_parts_key.h"
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
#define KEYPAD_LIGHT_OFFSET					(D3DXVECTOR3(0.0f,2.0f,-3.0f))
#define KEYPAD_LIGHTPOLYGON_SIZE			(D3DXVECTOR3(10.0f,7.0f,0.0f))
#define KEYPAD_SYMBOL_OFFSET				(D3DXVECTOR3(0.0f,-2.0f,-5.0f))
#define KEYPAD_SYMBOLPOLYGON_SIZE			(D3DXVECTOR3(8.0f,8.0f,0.0f))

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CModule_Parts_Key::CModule_Parts_Key()
{
	m_LampState = KEYPAD_STATE::NORMAL;
	m_nCntLampCnt = 0;
	m_pLight.reset();
	m_pSymbol.reset();
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CModule_Parts_Key::~CModule_Parts_Key()
{
	m_pLight.reset();
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CModule_Parts_Key::Init()
{
	//���f�����ݒ�
	BindModelInfo(CModelInfo::GetModelInfo(CModelInfo::MODEL_TEST_BUTTONPARTS));

	//�p�b�h�̃��C�g����
	m_pLight = CSceneBase::ScenePolygonCreateSelfManagement<CScene3D>(KEYPAD_LIGHT_OFFSET, KEYPAD_LIGHTPOLYGON_SIZE, BlackColor, nullptr);

	//�}�g���b�N�X�ݒ�
	m_pLight->SetParentMtxPtr(GetMtxWorldPtr());

	//���C�e�B���Ooff
	m_pLight->SetLighting(false);

	//�����̐���
	m_pSymbol = CSceneBase::ScenePolygonCreateShared<CScene3D>(KEYPAD_SYMBOL_OFFSET, KEYPAD_SYMBOLPOLYGON_SIZE, WhiteColor, CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_MODULEPARTS_MODULE00), CScene::OBJTYPE_MODULE_PARTS_SYMBOL);
	m_pSymbol->SetParentMtxPtr(GetMtxWorldPtr());
	m_pSymbol->SetAnimation(CHossoLibrary::CalcUV_StaticFunc(0, CTexture::SEPARATE_TEX_MODULEPARTS_MODULE00), CTexture::GetSparateTex_UVSize(CTexture::SEPARATE_TEX_MODULEPARTS_MODULE00));

	CSceneX::Init();

	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CModule_Parts_Key::Uninit()
{
	CSceneX::Uninit();
}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CModule_Parts_Key::Update()
{
	D3DXVECTOR3 vec;

	switch (m_LampState)
	{
	case CModule_Parts_Key::KEYPAD_STATE::NORMAL:
		break;
	case CModule_Parts_Key::KEYPAD_STATE::FAILED:
		m_nCntLampCnt--;

		if (m_nCntLampCnt < 0)
		{
			SetLampState(KEYPAD_STATE::NORMAL);
		}
		break;
	}

	if (m_pLight)
	{
		m_pLight->Update();
	}

	CSceneX::Update();
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CModule_Parts_Key::Draw()
{
	if (m_pLight)
	{
		m_pLight->Draw();
	}
	CSceneX::Draw();
}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CModule_Parts_Key::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}


//------------------------------------------------------------------------------
//�����v�̏�Ԑ؂�ւ�
//------------------------------------------------------------------------------
void CModule_Parts_Key::SetLampState(KEYPAD_STATE lampstate)
{
	//�����X�e�[�g����������return
	if (m_LampState == lampstate)
	{
		return;
	}

	//�X�e�[�g�؂�ւ�
	m_LampState = lampstate;

	//�؂�ւ�����X�e�[�g�ɉ����ď���
	switch (lampstate)
	{
	case CModule_Parts_Key::KEYPAD_STATE::NORMAL:
		m_pLight->SetColor(BlackColor);
		break;
	case CModule_Parts_Key::KEYPAD_STATE::FAILED:
		m_pLight->SetColor(RedColor);
		m_nCntLampCnt = 120;
		break;
	case CModule_Parts_Key::KEYPAD_STATE::CLEAR:
		m_pLight->SetColor(GreenColor);
		break;

	}
}
