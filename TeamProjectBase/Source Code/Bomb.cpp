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
#include "module_No1_SymbolKeyPad.h"
#include "module_No2_ShapeKeypad.h"
#include "module_No4_4ColButton.h"

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
	m_nSelectModuleNum = 0;
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
//�X�V����
//------------------------------------------------------------------------------
void CBomb::Update()
{
	CSceneX::Update();

	CBomb::Operator();

	//////std::cout << typeid(m_pModuleList[0].get());
	//std::cout << "m_pModuleList[0]" << "Name >> " << typeid(m_pModuleList[0]).name() << NEWLINE;
	//std::cout << "m_pModuleList[0]" << "RawName >> " << typeid(m_pModuleList[0]).raw_name() << NEWLINE;

	//std::cout << "m_pModuleList[0].get()" << "Name >> " <<typeid(m_pModuleList[0].get()).name() << NEWLINE;
	//std::cout << "m_pModuleList[0].get()" << "RawName > " << typeid(m_pModuleList[0].get()).raw_name() << NEWLINE;

	//std::cout << "*m_pModuleList[0]" << "Name >> " << typeid(*m_pModuleList[0]).name() << NEWLINE;
	//std::cout << "*m_pModuleList[0]" << "RawName >> " << typeid(*m_pModuleList[0]).raw_name() << NEWLINE;

	//std::cout << "*m_pModuleList[0].get()" << "Name >> " << typeid(*m_pModuleList[0].get()).name() << NEWLINE;
	//std::cout << "*m_pModuleList[0].get()" << "RawName >> " << typeid(*m_pModuleList[0].get()).raw_name() << NEWLINE;

	//std::cout << NEWLINE;
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

	CDebugProc::Print(CDebugProc::PLACE_LEFT, "-------------������@----------------\n");
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "[��][��][��][��] �J�[�\���ړ� \n");
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "[Enter] ����{�^�� \n");
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "[BackSpace] �߂�{�^�� \n");

#endif //DEBUG
}

//------------------------------------------------------------------------------
//�����֐�
//------------------------------------------------------------------------------
S_ptr<CBomb> CBomb::CreateBomb(D3DXVECTOR3 const pos, D3DXVECTOR3 const rot, int const nModuleNum)
{
	//�������m��
	S_ptr<CBomb> pBomb = std::make_shared<CBomb>();

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
//���삷��
//------------------------------------------------------------------------------
void CBomb::Operator()
{
	//�I��ԍ�
	//1F�O�̑I��ԍ�
	int m_SelectNumOld = m_nSelectModuleNum;

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
			//���W���[���I������
			//���͂�������������break
			if (!CHossoLibrary::Selecting(m_nSelectModuleNum, m_SelectNumOld, 3, 4))
			{
				break;
			}

			//nullcheck
			if (m_pModuleList[m_nSelectModuleNum].get())
			{
				if (m_pModuleList[m_nSelectModuleNum]->GetCanModuleSelect())
				{
					break;
				}
			}
		}

		for (int nCnt = 0; nCnt < (int)m_pModuleList.size(); nCnt++)
		{
			//nullcheck
			if (m_pModuleList[nCnt].get())
			{
				//���݂̑I��ԍ��Ɠ������m����true�ɂ��Ă���
				nCnt == m_nSelectModuleNum ?
					m_pModuleList[nCnt]->SetSelect(true) :
					m_pModuleList[nCnt]->SetSelect(false);
			}
		}


		if (pKeyboard->GetTrigger(DIK_RETURN))
		{
			CManager::GetGame()->SetGaze(CGame::GAZE::GAZE_MODULE);

			//�J�������߂Â���
			m_pModuleList[m_nSelectModuleNum]->CameraApproach();
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
		if (m_pModuleList[m_nSelectModuleNum].get())
		{
			m_pModuleList[m_nSelectModuleNum]->Operation();
		}

		break;

	default:
		break;
	}
}

//------------------------------------------------------------------------------
//���W���[���N���A�������`�F�b�N
//------------------------------------------------------------------------------
void CBomb::ModuleClearCheck()
{
	//�N���A�t���O�̌������W���[�����ȏ�ɂȂ�����
	if (std::count_if(m_pModuleList.begin(), m_pModuleList.end(),
		[](S_ptr<CModule_Base> pModule) {return pModule->GetModuleClearFlag(); }) >= m_nModuleNum)
	{
		CManager::GetGame()->SetState(CGame::STATE_GAMECLEAR);
	}
}

//------------------------------------------------------------------------------
//���W���[���~�X��
//------------------------------------------------------------------------------
void CBomb::ModuleMiss()
{
	//�^�C�}�[�̃N���X�̃C�e���[�^�擾
	auto itr = std::find_if(m_pModuleList.begin(), m_pModuleList.end(),
		[](S_ptr<CModule_Base> const ptr) {return typeid(*ptr.get()) == typeid(CModule_Timer); });

	//�C�e���[�^�����������`�F�b�N
	if (itr != m_pModuleList.end())
	{
		//�^�C�}�[�^�ɕϊ�
		CModule_Timer *pTimer = dynamic_cast<CModule_Timer*>(itr->get());  // �_�E���L���X�g

		//�~�X�J�E���g�A�b�v
		//�S���~�X�����Ƃ�
		if (pTimer->MissCountUp())
		{
			CManager::GetGame()->SetState(CGame::STATE_GAMEOVER);
		}
	}
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

	//CreateModule_Random(m_nModuleNum);


//Debug�p
#ifdef _DEBUG
	CreateModuleDebug();
#endif //_DEBUG





	////1�Ԗ�
	//CBomb::CreateModuleOne<CModule_Timer>();
	////2�Ԗ�
	//CBomb::CreateModuleOne<CModule_No1_SymbolKeyPad>();
	////3�Ԗ�
	//CBomb::CreateModuleOne<CModule_No2_ShapeKeyPad>();
	////4�Ԗ�
	//CBomb::CreateModuleOne<CModule_None>();
	////5�Ԗ�
	//CBomb::CreateModuleOne<CModule_None>();
	////6�Ԗ�
	//CBomb::CreateModuleOne<CModule_None>();

	////7�Ԗ�
	//CBomb::CreateModuleOne<CModule_None>();
	////8�Ԗ�
	//CBomb::CreateModuleOne<CModule_None>();
	////9�Ԗ�
	//CBomb::CreateModuleOne<CModule_None>();
	////10�Ԗ�
	//CBomb::CreateModuleOne<CModule_None>();
	////11�Ԗ�
	//CBomb::CreateModuleOne<CModule_None>();
	////12�Ԗ�
	//CBomb::CreateModuleOne<CModule_None>();





	//�����������X�g�S�Ă�
	for (auto &ptr : m_pModuleList)
	{
		//�{���̃|�C���^�ݒ�
		ptr->SetBombPtr(shared_from_this());
	}

	//�ŏ��̑I��ԍ��ݒ�
	for (size_t nCnt = 0; nCnt < m_pModuleList.size(); nCnt++)
	{
		if (m_pModuleList[nCnt]->GetCanModuleSelect())
		{
			m_nSelectModuleNum = nCnt;
			break;
		}
	}
}

//------------------------------------------------------------------------------
//���W���[�������@�����_������
//------------------------------------------------------------------------------
void CBomb::CreateModule_Random(int const nModuleNum)
{
	//�^�C�}�[����
	CBomb::CreateModuleOne<CModule_Timer>();

	int nCntModule = 0;

	//���W���[�������ɒB����܂�
	while ((int)m_pModuleList.size() < MAX_MODULE_NUM)
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
		case CModule_Base::MODULE_TYPE::NO1_SYMBOL:
			if (nCntModule < m_nModuleNum)
			{
				CBomb::CreateModuleOne<CModule_No1_SymbolKeyPad>();
				m_nModuleNum++;
			}
			break;
		case CModule_Base::MODULE_TYPE::NO2_SHAPE:
			if (nCntModule < m_nModuleNum)
			{
				CBomb::CreateModuleOne<CModule_No2_ShapeKeyPad>();
				m_nModuleNum++;
			}
			break;
		}
	}
}


#ifdef _DEBUG
//------------------------------------------------------------------------------
//���W���[�������@�f�o�b�O�p�@�����Ń��W���[�������߂��
//------------------------------------------------------------------------------
void CBomb::CreateModuleDebug()
{
	//���W���[�����������Ō��߂� debug�p
	m_nModuleNum = 2;


	//1�Ԗ�
	CBomb::CreateModuleOne<CModule_Timer>();
	//2�Ԗ�
	CBomb::CreateModuleOne<CModule_No1_SymbolKeyPad>();
	//3�Ԗ�
	CBomb::CreateModuleOne<CModule_No2_ShapeKeyPad>();
	//4�Ԗ�
	CBomb::CreateModuleOne<CModule_None>();
	//5�Ԗ�
	CBomb::CreateModuleOne<CModule_No4_4ColButton>();
	//6�Ԗ�
	CBomb::CreateModuleOne<CModule_None>();

	//7�Ԗ�
	CBomb::CreateModuleOne<CModule_None>();
	//8�Ԗ�
	CBomb::CreateModuleOne<CModule_None>();
	//9�Ԗ�
	CBomb::CreateModuleOne<CModule_None>();
	//10�Ԗ�
	CBomb::CreateModuleOne<CModule_None>();
	//11�Ԗ�
	CBomb::CreateModuleOne<CModule_None>();
	//12�Ԗ�
	CBomb::CreateModuleOne<CModule_None>();
}
#endif //_DEBUG
