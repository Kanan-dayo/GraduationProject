//------------------------------------------------------------------------------
//
//���W���[���̊��N���X  [module_base.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "module_base.h"
#include "module_parts_lamp.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "mouse.h"
#include "camera.h"
#include "Bomb.h"
#include "game.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define LAMP_OFFSET_POS (D3DXVECTOR3(40.0f, 30.0f, -20.0f))
//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CModule_Base::CModule_Base()
{
	m_bModuleClearFlag = false;
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CModule_Base::~CModule_Base()
{
	m_pLamp.reset();
}

//------------------------------------------------------------------------------
//�����v����
//------------------------------------------------------------------------------
void CModule_Base::Operation_Keyboard()
{
	//����L�[
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		//���W���[���̃A�N�V����
		ModuleAction();
	}

	//�L�����Z��
	if (CManager::GetKeyboard()->GetTrigger(DIK_BACKSPACE))
	{
		//���W���[���̑I������
		ModuleCancel();

		//�Q�[���̎��_�ύX
		CManager::GetGame()->SetGaze(CGame::GAZE_BOMB);
	}
}

//------------------------------------------------------------------------------
//�����v����
//------------------------------------------------------------------------------
void CModule_Base::Operation_Mouse()
{
	//���N���b�N
	if (CManager::GetMouse()->GetTrigger(0))
	{
		ModuleAction();
	}

	//�L�����Z��
	if (CManager::GetKeyboard()->GetTrigger(DIK_BACKSPACE))
	{
		//���W���[���̑I������
		ModuleCancel();

		//�Q�[���̎��_�ύX
		CManager::GetGame()->SetGaze(CGame::GAZE_BOMB);
	}

}

//------------------------------------------------------------------------------
//�����v����
//------------------------------------------------------------------------------
void CModule_Base::CreateLamp()
{
	//�����v����
	m_pLamp = CModule_Parts_Base::Create_ModuleParts<CModule_Parts_Lamp>(LAMP_OFFSET_POS, GetMtxWorldPtr());
}

//------------------------------------------------------------------------------
//�J�������߂Â���
//------------------------------------------------------------------------------
void CModule_Base::CameraApproach()
{
	//�J�������߂Â���
	CManager::GetRenderer()->GetCamera()->ApproachCamera(CHossoLibrary::CalcMtxToVector3(*GetMtxWorldPtr()));
}

//------------------------------------------------------------------------------
//���W���[���N���A
//------------------------------------------------------------------------------
void CModule_Base::Module_Clear()
{
	//�N���A�t���Otrue
	m_bModuleClearFlag = true;

	//nullcheck
	if (m_pLamp)
	{
		m_pLamp->SetLampState(CModule_Parts_Lamp::LAMP_STATE::GREEN);
	}

	//�{���̃|�C���^���J������Ă��Ȃ���
	if (!m_pBomb.expired())
	{
		//�N���A�`�F�b�N
		m_pBomb.lock()->ModuleClearCheck();
	}
}

//------------------------------------------------------------------------------
//���W���[�����s
//------------------------------------------------------------------------------
void CModule_Base::Module_Failed()
{
	//nullcheck
	if (m_pLamp)
	{
		m_pLamp->SetLampState(CModule_Parts_Lamp::LAMP_STATE::RED);
	}

	//�{���̃|�C���^���J������Ă��Ȃ���
	if (!m_pBomb.expired())
	{
		//���W���[���~�X����
		m_pBomb.lock()->ModuleMiss();
	}
}

