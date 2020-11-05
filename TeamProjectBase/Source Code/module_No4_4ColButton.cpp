//------------------------------------------------------------------------------
//
//���W���[���̐}�`�̃L�[�p�b�h����  [module_ShapeKeypad.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "module_No4_4ColButton.h"
#include "module_parts_No4_ColButton.h"
#include "renderer.h"
#include "manager.h"
#include "keyboard.h"
#include "modelinfo.h"
#include "timer.h"
#include "game.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define COL_BUTTON_NUM									(4)										//�{�^����
#define COL_BUTTON_OFFSET								(D3DXVECTOR3(0.0f,0.0f,-25.0f))			//�{�^���̃I�t�Z�b�g���W
#define COL_BUTTON_LIGHT_FLASH_TIME						(20)									//�{�^���̓_������
#define COL_BUTTON_LIGHT_FLASH_INTERVAL					(40)									//�{�^���̓_���̊��o
#define COL_BUTTON_LIGHT_LOOP_INTERVAL					(150)									//�{�^���̃��[�v�Ԋu

#define INPUT_GRACE										(180)									//�v���C���[���{�^������͂��Ă��烊�Z�b�g�����܂ł̗P�\


//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CModule_No4_4ColButton::CModule_No4_4ColButton()
{
	m_pColButtonList.clear();
	m_nNowSelectButton = BUTTON::RED;
	m_buttonState = STATE::START;
	m_nButtonLightingCnt = 0;
	m_nNowFlashNumber = 0;
	m_nClearNum = 3;
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CModule_No4_4ColButton::~CModule_No4_4ColButton()
{
	m_pColButtonList.clear();
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CModule_No4_4ColButton::Init()
{
	//���f�����ݒ�
	BindModelInfo(CModelInfo::GetModelInfo(CModelInfo::MODEL_MODULE_DEFAULT));

	int nCnt = 0;

	while (m_pColButtonList.size() < COL_BUTTON_NUM)
	{
		//�E��肩����肩�̕ϐ�
		int nValue = nCnt <= 1 ? 1 : -1;

		//�{�^������
		m_pColButtonList.emplace_back(CModule_Parts_Base::Create_ModuleParts<CModule_Parts_No4_ColButton>(COL_BUTTON_OFFSET, GetMtxWorldPtr()));
		m_pColButtonList[nCnt]->SetRot(D3DXVECTOR3(0.0f, 0.0f,
			((-D3DX_PI * 0.5f) * (nCnt % 2) * nValue) + ((D3DX_PI * 0.5f) * (nCnt / 2))));

		//�{�^���F�ݒ�
		m_pColButtonList[nCnt]->SetButtonCol((BUTTON)nCnt);

		//�����̃p�^�[������
		m_QuestionButtonList.emplace_back((BUTTON)nCnt);

		nCnt++;
	}

	//�����v����
	CModule_Base::CreateLamp();

	CSceneX::Init();

	return S_OK;
}

//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CModule_No4_4ColButton::Update()
{
	CSceneX::Update();

	m_nButtonLightingCnt--;

	switch (m_buttonState)
	{
	case CModule_No4_4ColButton::STATE::START:
		if (m_nButtonLightingCnt <= 0)
		{
			SetButtonState(STATE::LIGHTING);
		}

		break;

	case CModule_No4_4ColButton::STATE::INTERVAL:
		if (m_nButtonLightingCnt <= 0)
		{
			SetButtonState(STATE::LIGHTING);
		}

		break;


	case CModule_No4_4ColButton::STATE::LIGHTING:
		if (m_nButtonLightingCnt <= 0)
		{
			//�_���񐔂��K��܂ł��������ǂ���
			m_nClearNum > m_nNowFlashNumber ?
				SetButtonState(STATE::INTERVAL) :		//�_���̃C���^�[�o��
				SetButtonState(STATE::END);				//�_���I��
		}



		break;

	case CModule_No4_4ColButton::STATE::END:
		if (m_nButtonLightingCnt <= 0)
		{
			SetButtonState(STATE::START);
		}
		break;
	default:
		break;
	}

	//if()


}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CModule_No4_4ColButton::Draw()
{
	CSceneX::Draw();

}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CModule_No4_4ColButton::ShowDebugInfo()
{
#ifdef _DEBUG
	if (!GetSelect())
	{
		return;
	}
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "-------------Module_No_4----------------\n");
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "m_nButtonLightingCnt [%d]\n ", m_nButtonLightingCnt);
	CDebugProc::Print(CDebugProc::PLACE_LEFT, " m_nNowFlashNumber [%d]\n ", m_nNowFlashNumber);
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "m_nNowSelectButton [%d]\n ", m_nNowSelectButton);
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "m_nClearNum [%d]\n ", m_nClearNum);
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "m_buttonState [%d]\n ", m_buttonState);

#endif //DEBUG
}
//------------------------------------------------------------------------------
//�L�[�p�b�h����
//------------------------------------------------------------------------------
void CModule_No4_4ColButton::Operation()
{
	int nSelectNumOld = m_nNowSelectButton;

	//���͂�������������break
	CHossoLibrary::Selecting((int&)m_nNowSelectButton, nSelectNumOld, 2, 2);

	for (size_t nCnt = 0; nCnt < m_pColButtonList.size(); nCnt++)
	{
		//nullcheck
		if (m_pColButtonList[nCnt].get())
		{
			//���݂̑I��ԍ��Ɠ������m����true�ɂ��Ă���
			nCnt == m_nNowSelectButton ?
				m_pColButtonList[nCnt]->SetSelect(true) :
				m_pColButtonList[nCnt]->SetSelect(false);
		}
	}

	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		if (m_pColButtonList[m_nNowSelectButton].get())
		{
			//Module_Clear();

			//�������{�^�����N���A�{�^���������ꍇ
			if (m_pColButtonList[m_nNowSelectButton]->GetClearFlag())
			{

				////�N���A
				//QuestionClear();

				////�N���A�������`�F�b�N
				//CheckClear();

			}
			else
			{
				//���s
				Module_Failed();
			}
		}
	}

	//nullcheck
	if (CManager::GetKeyboard()->GetTrigger(DIK_BACKSPACE))
	{
		for (size_t nCnt = 0; nCnt < m_pColButtonList.size(); nCnt++)
		{
			if (m_pColButtonList[nCnt].get())
			{
				//���݂̑I��ԍ��Ɠ������m����true�ɂ��Ă���
				m_pColButtonList[nCnt]->SetSelect(false);

			}
		}
		CManager::GetGame()->SetGaze(CGame::GAZE_BOMB);
	}
}

//------------------------------------------------------------------------------
//�{�^���̃X�e�[�g�ݒ�
//------------------------------------------------------------------------------
void CModule_No4_4ColButton::SetButtonState(STATE state)
{
	//�����X�e�[�g��������
	if (m_buttonState == state)
	{
		return;
	}

	m_buttonState = state;

	switch (state)
	{
	case CModule_No4_4ColButton::STATE::START:
		m_nNowFlashNumber = 0;
		break;

	case CModule_No4_4ColButton::STATE::INTERVAL:
		m_pColButtonList[m_QuestionButtonList[m_nNowFlashNumber]]->SetLighting(false);
		m_nButtonLightingCnt = COL_BUTTON_LIGHT_FLASH_INTERVAL;
		m_nNowFlashNumber++;

		CHossoLibrary::RangeLimit_Equal(m_nNowFlashNumber, 0, 3);

		break;

	case CModule_No4_4ColButton::STATE::LIGHTING:
		m_pColButtonList[m_QuestionButtonList[m_nNowFlashNumber]]->SetLighting(true);
		m_nButtonLightingCnt = COL_BUTTON_LIGHT_FLASH_TIME;

		break;

	case CModule_No4_4ColButton::STATE::END:
		m_pColButtonList[m_QuestionButtonList[m_nNowFlashNumber]]->SetLighting(false);
		m_nButtonLightingCnt = COL_BUTTON_LIGHT_LOOP_INTERVAL;

		break;
	}
}

//------------------------------------------------------------------------------
//���̃N���A�{�^���ݒ�
//------------------------------------------------------------------------------
void CModule_No4_4ColButton::NextButtonSet()
{
	for (size_t nCnt = 0; nCnt < m_pColButtonList.size(); nCnt++)
	{
		//�t���O������
		m_pColButtonList[nCnt]->SetClearFlag(false);
	}

	BUTTON NextButton = BUTTON::RED;

	switch (m_QuestionButtonList[m_nNowFlashNumber])
	{
	case BUTTON::RED:
		NextButton = BUTTON::GREEN;
		break;

	case BUTTON::GREEN:
		NextButton = BUTTON::YELLOW;
		break;

	case BUTTON::BLUE:
		NextButton = BUTTON::RED;
		break;

	case BUTTON::YELLOW:
		NextButton = BUTTON::BLUE;
		break;
	}

	//���̃{�^���Ɠ����{�^��������
	auto itr = std::find_if(m_pColButtonList.begin(), m_pColButtonList.end(),
		[NextButton](S_ptr<CModule_Parts_No4_ColButton> &ColButton) {return ColButton->GetButton() == NextButton; });

	//���ʂ��o����
	if (itr != m_pColButtonList.end())
	{
		//�N���A�t���O�ݒ�
		itr->get()->SetClearFlag(true);
	}


}

