//------------------------------------------------------------------------------
//
//���W���[���p�[�c�̐F�̃{�^��  [module_parts_No4_ColButton.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "module_parts_No4_ColButton.h"
#include "module_No4_4ColButton.h"
#include "manager.h"
#include "modelinfo.h"
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
#define LIGHT_FLASH_TIME					(30)
#define LIGHT_ADD_COLOR						(D3DXCOLOR(0.2f,0.2f,0.2f,1.0f))

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CModule_Parts_No4_ColButton::CModule_Parts_No4_ColButton()
{
	m_ButtonCol = WhiteColor;
	m_bLight = false;
	m_nCntLight = 0;
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CModule_Parts_No4_ColButton::~CModule_Parts_No4_ColButton()
{

}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CModule_Parts_No4_ColButton::Init()
{
	//���f�����ݒ�
	BindModelInfo(CModelInfo::GetModelInfo(CModelInfo::MODEL_MODULEPARTS_NO4_BUTTON));

	CSceneX::Init();

	return S_OK;
}

//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CModule_Parts_No4_ColButton::Update()
{
	CSceneX::Update();

	//���C�g���_�����Ă���Ƃ�
	if (m_bLight)
	{
		//�J�E���g�_�E������0�ȉ��ɂȂ�����
		if (m_nCntLight-- <= 0)
		{
			//���C�gOFF
			SetLighting(false);
		}
	}
}
//------------------------------------------------------------------------------
//�`�揈��
//CSceneX�I�[�o�[���C�h
//------------------------------------------------------------------------------
void CModule_Parts_No4_ColButton::Draw()
{
	//�n�[�h�G�b�W�`��
	//�I������Ă��郂�f���̂�
	CSceneX::DrawHardEdgeStencil();

	//���[���h�}�g���b�N�X�̌v�Z
	CSceneX::CalcMtx_IncludeParentMtx();

	if (m_bLight)
	{
		//���b�V���`��@�}�e���A���F��ݒ�
		CSceneX::SetEmissive(true);
		CSceneX::DrawMesh_SetMaterial(m_ButtonCol + LIGHT_ADD_COLOR , true);

	}
	else
	{
		//���b�V���`��@�}�e���A���F��ݒ�
		CSceneX::SetEmissive(false);
		CSceneX::DrawMesh_SetMaterial(m_ButtonCol, true);
	}

	//CSceneX::Draw();
}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CModule_Parts_No4_ColButton::ShowDebugInfo()
{
#ifdef _DEBUG



#endif //DEBUG
}

//------------------------------------------------------------------------------
//�{�^���̐F�ݒ�
//------------------------------------------------------------------------------
void CModule_Parts_No4_ColButton::SetButtonCol(CModule_No4_4ColButton::BUTTON col)
{
	m_Button = col;

	switch (col)
	{
	case CModule_No4_4ColButton::BUTTON::RED:
		m_ButtonCol = RedColor;
		break;
	case CModule_No4_4ColButton::BUTTON::GREEN:
		m_ButtonCol = GreenColor;
		break;
	case CModule_No4_4ColButton::BUTTON::BLUE:
		m_ButtonCol = BlueColor;
		break;
	case CModule_No4_4ColButton::BUTTON::YELLOW:
		m_ButtonCol = YellowColor;
		break;

	}
}

//------------------------------------------------------------------------------
//���C�g�̐ݒ�
//------------------------------------------------------------------------------
void CModule_Parts_No4_ColButton::SetButtonLighting(bool bLight)
{
	m_bLight = bLight;
	m_nCntLight = LIGHT_FLASH_TIME;
}
