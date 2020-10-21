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


//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CModule_Parts_Key::CModule_Parts_Key()
{
	m_LampState = KEYPAD_STATE::NORMAL;
	m_nCntLampCnt = 0;
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CModule_Parts_Key::~CModule_Parts_Key()
{

}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CModule_Parts_Key::Init()
{
	//���f�����ݒ�
	BindModelInfo(CModelInfo::GetModelInfo(CModelInfo::MODEL_MODULEPARTS_KEYPAD));

	//�p�b�h�̃��C�g����
	m_pLight = CSceneBase::ScenePolygonCreateSelfManagement<CScene3D>(KEYPAD_LIGHT_OFFSET, KEYPAD_LIGHTPOLYGON_SIZE, BlackColor, CTexture::TEX_TYPE::TEX_NONE);

	//�}�g���b�N�X�ݒ�
	m_pLight->SetParentMtxPtr(GetMtxWorldPtr());

	//���C�e�B���Ooff
	m_pLight->SetLighting(false);

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
	if (CManager::GetKeyboard()->GetTrigger(DIK_5))
	{
		SetLampState(KEYPAD_STATE::CLEAR);
	}
	if (CManager::GetKeyboard()->GetTrigger(DIK_6))
	{
		SetLampState(KEYPAD_STATE::FAILED);
	}

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
