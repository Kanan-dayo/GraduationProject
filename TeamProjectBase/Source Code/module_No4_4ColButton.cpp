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
#include "module_parts_ProgressLamp.h"
#include "Bomb.h"
#include "Bomb_Exterior.h"
#include "renderer.h"
#include "manager.h"
#include "keyboard.h"
#include "modelinfo.h"
#include "timer.h"
#include "game.h"
#include "mouse.h"
#include "sound.h"

//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define COL_BUTTON_NUM									(4)										//�{�^����
#define COL_BUTTON_OFFSET								(D3DXVECTOR3(-10.0f,0.0f,-14.5f))			//�{�^���̃I�t�Z�b�g���W
#define COL_BUTTON_LIGHT_FLASH_INTERVAL					(45)									//�{�^���̓_���̊��o
#define COL_BUTTON_LIGHT_LOOP_INTERVAL					(180)									//�{�^���̃��[�v�Ԋu
#define PROGRESSLAMP_OFFSET								(D3DXVECTOR3(35.0f,-10.0f,-15.0f))		//�i���x�����v�̃I�t�Z�b�g���W
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
	m_nNowFlashNumber = -1;
	m_nClearNum = 0;
	m_pProgressLamp.reset();
	m_nPlayerPushNum = 0;
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CModule_No4_4ColButton::~CModule_No4_4ColButton()
{
	m_pColButtonList.clear();
	m_pProgressLamp.reset();

}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CModule_No4_4ColButton::Init()
{
	//���f�����ݒ�
	BindModelInfo(CModelInfo::GetModelInfo(CModelInfo::MODEL_MODULE_NO4));

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
		m_QuestionButtonList.emplace_back((BUTTON)CHossoLibrary::RandomRangeUnsigned(0, 3));

		nCnt++;
	}

	//���̃{�^���ݒ�
	NextButtonSet();

	//�����v����
	CModule_Base::CreateLamp();
	m_pProgressLamp = CModule_Parts_Base::Create_ModuleParts<CModule_Parts_ProgressLamp>(PROGRESSLAMP_OFFSET, GetMtxWorldPtr());
	m_pProgressLamp->SetRot(D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI * 0.5f));

	//������
	CSceneX::Init();

	return S_OK;
}

//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CModule_No4_4ColButton::Update()
{
	CSceneX::Update();

	//�{�^���̃X�e�[�g���I�����Ă鎞
	if (m_buttonState == CModule_No4_4ColButton::STATE::END)
	{
		//return
		return;
	}

	//�_���J�E���g�_�E��
	m_nButtonLightingCnt--;

	//�{�^���̏�Ԃɉ����ď�����ς���
	switch (m_buttonState)
	{
	case CModule_No4_4ColButton::STATE::START:
	case CModule_No4_4ColButton::STATE::INTERVAL:
		if (m_nButtonLightingCnt <= 0)
		{
			//�_����Ԃɂ���
			SetButtonState(STATE::LIGHTING);
		}
		break;

	case CModule_No4_4ColButton::STATE::PLAYER_INPUT:
	case CModule_No4_4ColButton::STATE::RESET_INTERVAL:
		if (m_nButtonLightingCnt <= 0)
		{
			//�X�^�[�g��Ԃɂ���
			SetButtonState(STATE::START);
		}
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
		//return;
	}
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "-------------Module_No_4----------------\n");
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "m_nButtonLightingCnt [%d]\n", m_nButtonLightingCnt);
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "m_nNowFlashNumber [%d]\n", m_nNowFlashNumber);
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "m_nNowSelectButton [%d]\n", m_nNowSelectButton);
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "m_nClearNum [%d]\n", m_nClearNum);
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "m_buttonState [%d]\n", m_buttonState);

	CDebugProc::Print(CDebugProc::PLACE_LEFT, "m_nPlayerPushNum [%d]\n", m_nPlayerPushNum);

	for (size_t nCnt = 0; nCnt < m_pColButtonList.size(); nCnt++)
	{
		CDebugProc::Print(CDebugProc::PLACE_LEFT, "[%d] ", m_pColButtonList[nCnt]->GetClearFlag());
	}

	CDebugProc::Print(CDebugProc::PLACE_LEFT,NEWLINE);

	CModule_Base::ShowDebugInfo();

#endif //DEBUG
}

//------------------------------------------------------------------------------
//�L�[�p�b�h����
//------------------------------------------------------------------------------
void CModule_No4_4ColButton::Operation_Keyboard()
{
	int nSelectNumOld = m_nNowSelectButton;

	//���͂�������������break
	CHossoLibrary::Selecting((int&)m_nNowSelectButton, nSelectNumOld, 2, 2);

	//�I������
	CModule_Base::ModuleParts_Select<CModule_Parts_No4_ColButton>(m_pColButtonList, m_nNowSelectButton);

	//���W���[������
	CModule_Base::Operation_Keyboard();
}

//------------------------------------------------------------------------------
//���W���[������@�}�E�X
//------------------------------------------------------------------------------
void CModule_No4_4ColButton::Operation_Mouse()
{
	//���C�̔���
	CHossoLibrary::RayCollision_ModuleSelect(m_pColButtonList.begin(), m_pColButtonList.end(), (int&)m_nNowSelectButton);

	//�}�E�X����
	CModule_Base::Operation_Mouse();

}

//------------------------------------------------------------------------------
//���W���[���A�N�V����
//------------------------------------------------------------------------------
void CModule_No4_4ColButton::ModuleAction()
{
	//�I��ԍ���-1�Ƃ���������
	if (m_nNowSelectButton < 0)
	{
		return;
	}
	//���łɏI�����Ă����ꍇ
	if (m_buttonState == STATE::END)
	{
		//�~�X
		Module_Failed();
		return;
	}

	//nullcheck
	if (m_pColButtonList[m_nNowSelectButton].get())
	{
		//�v���C���[�̓��͏��
		SetButtonState(STATE::PLAYER_INPUT);
		m_pColButtonList[m_nNowSelectButton]->SetButtonLighting(true);

		//�������{�^�����N���A�{�^���������ꍇ
		if (m_pColButtonList[m_nNowSelectButton]->GetClearFlag())
		{
			//�����̃{�^��������
			ButtonPushSuccess();

			//���Đ�
			CManager::GetSound()->Play(CSound::LABEL_SE_MODULE_PUSH);

		}
		else
		{
			//���s
			Module_Failed();
		}
	}
}

//------------------------------------------------------------------------------
//���W���[���̑I������
//------------------------------------------------------------------------------
void CModule_No4_4ColButton::ModuleCancel()
{
	//�I������
	CModule_Base::ModuleParts_Select<CModule_Parts_No4_ColButton>(m_pColButtonList, -1);
}

//------------------------------------------------------------------------------
//�{�^���̃X�e�[�g�ݒ�
//------------------------------------------------------------------------------
void CModule_No4_4ColButton::SetButtonState(STATE state)
{
	//�X�e�[�g�؂�ւ�
	m_buttonState = state;

	switch (state)
	{
	case CModule_No4_4ColButton::STATE::START:
		m_nNowFlashNumber = -1;

		//�v���C���[�̓��͏�񃊃Z�b�g
		PlayerInputReset();
		break;

	case CModule_No4_4ColButton::STATE::INTERVAL:
		//�{�^���̓_���̊Ԋu�ݒ�
		m_nButtonLightingCnt = COL_BUTTON_LIGHT_FLASH_INTERVAL;

		break;

	case CModule_No4_4ColButton::STATE::LIGHTING:
		m_nNowFlashNumber++;

		//���񐔈ȏ�ɂȂ�Ȃ��悤�ɐݒ�
		CHossoLibrary::RangeLimit_Equal(m_nNowFlashNumber, 0, 3);

		//�{�^�������点��
		m_pColButtonList[m_QuestionButtonList[m_nNowFlashNumber]]->SetButtonLighting(true);


		//�_���񐔂��K��܂ł��������ǂ���
		m_nClearNum > m_nNowFlashNumber ?
			SetButtonState(STATE::INTERVAL) :				//�_���̃C���^�[�o��
			SetButtonState(STATE::RESET_INTERVAL);			//�_���I��

		break;

	case CModule_No4_4ColButton::STATE::PLAYER_INPUT:
		m_nButtonLightingCnt = INPUT_GRACE;

		break;

	case CModule_No4_4ColButton::STATE::RESET_INTERVAL:
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

	//���ɉ����{�^���ݒ�
	BUTTON NextButton = BUTTON::NONE;

	////�o�b�e���[�����Ă����ꍇ
	//if (CModule_Base::GetBombWeakPtr()._Get()->GetBombExterior()->CountExteriorNum(CBomb_Exterior::BATTERY_BIG) ||
	//	CModule_Base::GetBombWeakPtr()._Get()->GetBombExterior()->CountExteriorNum(CBomb_Exterior::BATTERY_SMALL))
	//{
	//	SetNextButton_YesBattery_NotSerialNo(NextButton);
	//}
	//else
	{
		SetNextButton_NotBattery_NotSerialNo(NextButton);

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
//------------------------------------------------------------------------------
//�v���C���[�̓��͊֌W�̕ϐ����Z�b�g
//------------------------------------------------------------------------------
void CModule_No4_4ColButton::PlayerInputReset()
{
	m_nPlayerPushNum = 0;
	NextButtonSet();

}

//------------------------------------------------------------------------------
//�����̃{�^����������
//------------------------------------------------------------------------------
void CModule_No4_4ColButton::ButtonPushSuccess()
{
	//�v���C���[�̃{�^���N���A��++
	m_nPlayerPushNum++;

	//�N���A�񐔂ɓ��B�����Ƃ�
	if (m_nPlayerPushNum > m_nClearNum)
	{
		//�N���A�ɕK�v�ȃL�[���ǉ�
		m_nClearNum++;

		//�i�������v�X�V
		m_pProgressLamp->SetProgress(m_nClearNum);
	}

	//���W���[���N���A���ĂȂ���
	if (!CheckModuleClear())
	{
		//���̃{�^���ݒ�
		NextButtonSet();
	}
}


//------------------------------------------------------------------------------
//���W���[���N���A�������m�F
//------------------------------------------------------------------------------
bool CModule_No4_4ColButton::CheckModuleClear()
{
	//�o�萔�ƃN���A�����{�^������r
	if (m_nClearNum >= (int)m_QuestionButtonList.size())
	{
		//���W���[���N���A
		Module_Clear();

		//�I��
		SetButtonState(STATE::END);
		return true;
	}
	return false;
}

//------------------------------------------------------------------------------
//���ɉ����{�^���ݒ�
//�o�b�e���L
//�V���A���i���o�[�ꉹ����
//------------------------------------------------------------------------------
void CModule_No4_4ColButton::SetNextButton_YesBattery_NotSerialNo(BUTTON & NextButton)
{
	switch (m_QuestionButtonList[m_nPlayerPushNum])
	{
	case BUTTON::RED:
		NextButton = BUTTON::YELLOW;
		break;

	case BUTTON::BLUE:
		NextButton = BUTTON::GREEN;
		break;

	case BUTTON::YELLOW:
		NextButton = BUTTON::BLUE;
		break;

	case BUTTON::GREEN:
		NextButton = BUTTON::RED;
		break;
	}
}

//------------------------------------------------------------------------------
//���ɉ����{�^���ݒ�
//�o�b�e����
//�V���A���i���o�[�ꉹ����
//------------------------------------------------------------------------------
void CModule_No4_4ColButton::SetNextButton_NotBattery_NotSerialNo(BUTTON & NextButton)
{
	switch (m_QuestionButtonList[m_nPlayerPushNum])
	{
	case BUTTON::RED:
		NextButton = BUTTON::GREEN;
		break;

	case BUTTON::BLUE:
		NextButton = BUTTON::RED;
		break;

	case BUTTON::YELLOW:
		NextButton = BUTTON::YELLOW;
		break;

	case BUTTON::GREEN:
		NextButton = BUTTON::BLUE;
		break;

	}
}

