//------------------------------------------------------------------------------
//
//���e�̏���  [Bomb.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "Bomb.h"
#include "renderer.h"
#include "manager.h"
#include "keyboard.h"
#include "game.h"
#include "modelinfo.h"
#include "module_none.h"
#include "module_timer.h"
#include "module_Button.h"
#include "module_keypad.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CBomb::CBomb()
{
	m_nModuleNum = 0;
	m_pModuleList = {};
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CBomb::~CBomb()
{

}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CBomb::Init()
{
	CSceneX::Init();
	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CBomb::Uninit()
{
	CSceneX::Uninit();
}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CBomb::Update()
{
	CSceneX::Update();
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CBomb::Draw()
{
	CSceneX::Draw();

}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CBomb::ShowDebugInfo()
{
#ifdef _DEBUG

	//�I��ԍ�
	static  int nSelectNum = 0;
	//1F�O�̑I��ԍ�
	int nSelectNumOld = nSelectNum;

	//�z�񂪋󂾂�����return
	if (m_pModuleList.empty())
	{
		return;
	}

	//�L�[�{�[�h�̃|�C���^
	CKeyboard *pKeyboard = CManager::GetKeyboard();

	switch (CManager::GetGame()->GetGaze())
	{
	case CGame::GAZE_DEFAULT:
		break;

	case CGame::GAZE_BOMB:
		while (1)
		{
			//���͂�������������break
			if (!CHossoLibrary::Selecting(nSelectNum, nSelectNumOld, 3, 4))
			{
				break;
			}

			//nullcheck
			if (m_pModuleList[nSelectNum].get())
			{
				if (m_pModuleList[nSelectNum]->GetCanModuleSelect())
				{
					break;
				}
			}
		}

		for (int nCnt = 0; nCnt < 12; nCnt++)
		{
			//nullcheck
			if (m_pModuleList[nCnt].get())
			{
				//���݂̑I��ԍ��Ɠ������m����true�ɂ��Ă���
				nCnt == nSelectNum ?
					m_pModuleList[nCnt]->SetSelect(true) :
					m_pModuleList[nCnt]->SetSelect(false);
			}
		}


		if (pKeyboard->GetTrigger(DIK_RETURN))
		{
			CManager::GetGame()->SetGaze(CGame::GAZE::GAZE_MODULE);

			//�J�������߂Â���
			m_pModuleList[nSelectNum]->CameraApproach();
		}

		break;

	case CGame::GAZE_MODULE:
		for (int nCnt = 0; nCnt < 12; nCnt++)
		{
			//nullcheck
			if (m_pModuleList[nCnt].get())
			{
				m_pModuleList[nCnt]->SetSelect(false);

			}
		}
		//nullcheck
		if (m_pModuleList[nSelectNum].get())
		{
			m_pModuleList[nSelectNum]->Operation();
		}

		break;

	default:
		break;
	}



	//����Ctrl�L�[
	if (pKeyboard->GetPress(DIK_LCONTROL))
	{
		for (int nCnt = 0; nCnt < 12; nCnt++)
		{
			//����
			if (pKeyboard->GetTrigger(0x01 + nCnt))
			{
				//nullcheck
				if (m_pModuleList[nCnt].get())
				{
					//���W���[���N���A
					m_pModuleList[nCnt]->Module_Clear();
				}
			}
		}
	}

#endif //DEBUG
}

//------------------------------------------------------------------------------
//�����֐�
//------------------------------------------------------------------------------
std::shared_ptr<CBomb> CBomb::CreateBomb(D3DXVECTOR3 const pos, D3DXVECTOR3 const rot, int const nModuleNum)
{
	//�������m��
	std::shared_ptr<CBomb> pBomb = std::make_shared<CBomb>();

	//������
	pBomb->Init();

	//���W�ƃT�C�Y�ݒ�
	pBomb->SetPos(pos);
	pBomb->SetRot(rot);

	//���f�����ݒ�
	pBomb->BindModelInfo(CModelInfo::GetModelInfo(CModelInfo::MODEL_BOMBBOX));

	//���W���[������
	pBomb->CreateModule(nModuleNum);

	//Scene���ŊǗ�
	pBomb->SetObjType(CScene::OBJTYPE_BOMB);
	pBomb->AddSharedList(pBomb);

	return pBomb;
}

//------------------------------------------------------------------------------
//���W���[������
//------------------------------------------------------------------------------
void CBomb::CreateModule(int const nModuleNum)
{
	//���f�������
	m_nModuleNum = nModuleNum;

	//�������W���[����\���ł���͈͊O�̎��͎��߂�
	CHossoLibrary::RangeLimit_Equal(m_nModuleNum, 0, MAX_MODULE_NUM);

	//�^�C�}�[����
	CBomb::CreateModuleOne<CModule_Timer>();

	//���W���[�������ɒB����܂�
	while ((int)m_pModuleList.size() < m_nModuleNum)
	{
		//���W���[���^�C�v�������_����
		CModule_Base::MODULE_TYPE type = (CModule_Base::MODULE_TYPE)(rand() % (int)CModule_Base::MODULE_TYPE::MAX);

		//���W���[���^�C�v�ɉ����Đ���
		switch (type)
		{
			//���W���[������
		case CModule_Base::MODULE_TYPE::NONE:
			CBomb::CreateModuleOne<CModule_None>();
			break;

		//	//�{�^�����W���[��
		//case CModule_Base::MODULE_TYPE::BUTTON:
		//	CBomb::CreateModuleOne<CModule_Button>();
		//	break;

			//�L�[�p�b�h
		case CModule_Base::MODULE_TYPE::KEYPAD:
			CBomb::CreateModuleOne<CModule_KeyPad>();
			break;
		}
	}
//Debug�p
#ifdef _DEBUG
	////1�Ԗ�
	//CBomb::CreateModuleOne<CModule_Timer>();
	////2�Ԗ�
	//CBomb::CreateModuleOne<CModule_Button>();
	////3�Ԗ�
	//CBomb::CreateModuleOne<CModule_Button>();
	////4�Ԗ�
	//CBomb::CreateModuleOne<CModule_Button>();
	////5�Ԗ�
	//CBomb::CreateModuleOne<CModule_Button>();
	////6�Ԗ�
	//CBomb::CreateModuleOne<CModule_Button>();

	////7�Ԗ�
	//CBomb::CreateModuleOne<CModule_Button>();
	////8�Ԗ�
	//CBomb::CreateModuleOne<CModule_Button>();
	////9�Ԗ�
	//CBomb::CreateModuleOne<CModule_Button>();
	////10�Ԗ�
	//CBomb::CreateModuleOne<CModule_Button>();
	////11�Ԗ�
	//CBomb::CreateModuleOne<CModule_Button>();
	////12�Ԗ�
	//CBomb::CreateModuleOne<CModule_Button>();

#endif //_DEBUG
}
