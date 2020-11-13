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
#include "camera.h"
#include "keyboard.h"
#include "game.h"
#include "modelinfo.h"
#include "Bomb_Exterior.h"
#include "module_none.h"
#include "module_timer.h"
#include "module_Button.h"
#include "module_No0_SymbolKeyPad.h"
#include "module_No1_ShapeKeypad.h"
#include "module_No2_LampAndWire.h"
#include "module_No4_4ColButton.h"

//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------
#ifdef _DEBUG
bool CBomb::m_bCanExplosion = false;
#endif // _DEBUG


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
	m_pBombExterior.reset();
	m_bCameraDir = true;
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CBomb::~CBomb()
{
	m_pModuleList = {};
	m_pBombExterior.reset();
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

	const D3DXVECTOR3 &CameraRot = CManager::GetRenderer()->GetCamera()->GetCameraRot();

	fabsf(CameraRot.y) >= D3DX_PI * 0.5f ?
		m_bCameraDir = true :
		m_bCameraDir = false;

	CDebugProc::Print(CDebugProc::PLACE_LEFT, "bCamera >> %d\n", m_bCameraDir);

	int nMin = 6 * (m_bCameraDir);
	int nMax = nMin + 5;

	//���\�؂�ւ������
	if (CHossoLibrary::RangeLimit_Equal(m_nSelectModuleNum, nMin, nMax))
	{
		SearchHeadCanSelectNum(nMin);
		CManager::GetGame()->SetGaze(CGame::GAZE_BOMB);
	}

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
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "[F7] �������邩�ǂ����ݒ� >> [%d] \n",m_bCanExplosion);

	if (CManager::GetKeyboard()->GetTrigger(DIK_F7))
	{
		m_bCanExplosion ^= 1;
	}

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

	//�{���̊O������
	pBomb->m_pBombExterior = CBomb_Exterior::CreateBombExterior(pBomb->GetMtxWorldPtr());

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
	//�z�񂪋󂾂�����return
	if (m_pModuleList.empty())
	{
		return;
	}

	//�L�[�{�[�h�̃|�C���^
	CKeyboard *pKeyboard = CManager::GetKeyboard();

	//Game�̎��_�ɂ���Ĕ���̑����ς���
	switch (CManager::GetGame()->GetGaze())
	{
	case CGame::GAZE_DEFAULT:
		break;

	case CGame::GAZE_BOMB:

		//���W���[���I��
		ModuleSelect();

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
		for (auto & rPtr : m_pModuleList)
		{
			//�I������
			rPtr->SetSelect(false);
		}

		//nullcheck
		if (m_pModuleList[m_nSelectModuleNum].get())
		{
			//���ݑI������Ă��郂�W���[���𑀍�
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
#ifdef _DEBUG
	if (!m_bCanExplosion) return;
#endif // _DEBUG

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
			//�Q�[���I�[�o�[
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

	//CreateModule_Random();


//Debug�p
#ifdef _DEBUG
	CreateModuleDebug();
#endif //_DEBUG

	////1�Ԗ�
	//CBomb::CreateModuleOne<CModule_Timer>();
	////2�Ԗ�
	//CBomb::CreateModuleOne<CModule_No0_SymbolKeyPad>();
	////3�Ԗ�
	//CBomb::CreateModuleOne<CModule_No1_ShapeKeyPad>();
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

	SearchHeadCanSelectNum(0);
}

//------------------------------------------------------------------------------
//���W���[�������@�����_������
//------------------------------------------------------------------------------
void CBomb::CreateModule_Random()
{
	//���[�J���̃��X�g
	Vec<CModule_Base::MODULE_TYPE> LocalList = {};

	//�^�C�}�[����
	CBomb::CreateModuleOne<CModule_Timer>();
\
	//���W���[��������Ȃ�����NONE�̃��W���[�������Ă���
	while ((int)LocalList.size() < MAX_MODULE_NUM - m_nModuleNum - 1)
	{
		LocalList.emplace_back(CModule_Base::MODULE_TYPE::NONE);
	}
	//�ő吔�ɂȂ�܂Ń��W���[��������
	while (LocalList.size() < MAX_MODULE_NUM - 1)
	{
		//Button����4Button�܂ł̃����_��
		LocalList.emplace_back((CModule_Base::MODULE_TYPE)CHossoLibrary::RandomRangeUnsigned((int)CModule_Base::MODULE_TYPE::NO1_SYMBOL, (int)CModule_Base::MODULE_TYPE::MAX));
	}

	//�v�f�̃V���b�t��
	CHossoLibrary::Vec_Shuffle(LocalList);

	int nCntModule = 0;

	//���W���[�������ɒB����܂�
	while ((int)m_pModuleList.size() < MAX_MODULE_NUM)
	{
		//���W���[���^�C�v�ɉ����Đ���
		switch (LocalList[nCntModule])
		{
			//���W���[������
		case CModule_Base::MODULE_TYPE::NONE:
			CBomb::CreateModuleOne<CModule_None>();
			nCntModule++;

			break;

			//	//�{�^�����W���[��
			//case CModule_Base::MODULE_TYPE::BUTTON:
			//	CBomb::CreateModuleOne<CModule_Button>();
			//	break;

				//�L�[�p�b�h
		case CModule_Base::MODULE_TYPE::NO1_SYMBOL:
			//if (nCntModule < nCntModule)
			{
				CBomb::CreateModuleOne<CModule_No0_SymbolKeyPad>();
				nCntModule++;
			}
			break;
		case CModule_Base::MODULE_TYPE::NO2_SHAPE:
			//if (nCntModule < nCntModule)
			{
				CBomb::CreateModuleOne<CModule_No1_ShapeKeyPad>();
				nCntModule++;
			}
			break;
		case CModule_Base::MODULE_TYPE::NO4_4COLBUTTON:
			//if (nCntModule < nCntModule)
			{
				CBomb::CreateModuleOne<CModule_No4_4ColButton>();
				nCntModule++;
			}
			break;
		}
	}
}

//------------------------------------------------------------------------------
//���W���[���I��
//------------------------------------------------------------------------------
void CBomb::ModuleSelect()
{
	//�I��ԍ�
	//1F�O�̑I��ԍ�
	int m_SelectNumOld = m_nSelectModuleNum;


	//�L�[�{�[�h�̃|�C���^
	CKeyboard *pKeyboard = CManager::GetKeyboard();

	int nNumX = 3;
	int nNumY = 2;

	int nMin = (nNumX * nNumY) * m_bCameraDir;
	int nMax = nMin + (nNumX * nNumY) - 1;

	//���W���[���I������
	//���͂�������������break
	//���������ǂꂩ���͂���Ă����ꍇ
	if (pKeyboard->GetTrigger(DIK_LEFT) || pKeyboard->GetTrigger(DIK_RIGHT) ||
		pKeyboard->GetTrigger(DIK_UP) || pKeyboard->GetTrigger(DIK_DOWN))
	{
		while (1)
		{
			//��
			if (pKeyboard->GetTrigger(DIK_LEFT))
			{
				//�I��ԍ�--
				m_nSelectModuleNum--;

				//�͈͓��ɗ}����
				if (CHossoLibrary::RangeLimit_Equal(m_nSelectModuleNum, nMin, nMax))
				{
					//���̒l�ɖ߂�
					m_nSelectModuleNum = m_SelectNumOld;
					break;
				}

				//�񂪕ς��Ƃ�
				if (m_SelectNumOld / nNumX != m_nSelectModuleNum / nNumX)
				{
					//���̒l�ɖ߂�
					m_nSelectModuleNum = m_SelectNumOld;
					break;
				}

				//�I���ł��鎞
				if (m_pModuleList[m_nSelectModuleNum]->GetCanModuleSelect())
				{
					//break
					break;
				}
			}

			//��
			else if (pKeyboard->GetTrigger(DIK_RIGHT))
			{
				//�I��ԍ�++
				m_nSelectModuleNum++;


				//�͈͓��ɗ}����
				if (CHossoLibrary::RangeLimit_Equal(m_nSelectModuleNum, nMin, nMax))
				{
					//���̒l�ɖ߂�
					m_nSelectModuleNum = m_SelectNumOld;
					break;
				}

				//�񂪕ς��Ƃ�
				if (m_SelectNumOld / nNumX != m_nSelectModuleNum / nNumX)
				{
					//���̒l�ɖ߂�
					m_nSelectModuleNum = m_SelectNumOld;
					break;
				}

				//�I���ł��鎞
				if (m_pModuleList[m_nSelectModuleNum]->GetCanModuleSelect())
				{
					//break
					break;
				}
			}

			//��
			else if (pKeyboard->GetTrigger(DIK_UP))
			{
				//�I��ԍ� -= ������
				m_nSelectModuleNum -= nNumX;

				//�͈͓��ɗ}����
				if (CHossoLibrary::RangeLimit_Equal(m_nSelectModuleNum, nMin, nMax))
				{
					//���̒l�ɖ߂�
					m_nSelectModuleNum = m_SelectNumOld;
					break;
				}

				//�I���\�ȃ��W���[����������
				if (m_pModuleList[m_nSelectModuleNum]->GetCanModuleSelect())
				{
					//break
					break;
				}
				else
				{
					//�ړ���̗�̍��[�ɖ߂�
					int nValue = m_nSelectModuleNum / nNumX;
					m_nSelectModuleNum = nValue * nNumX;

					while (m_nSelectModuleNum <= nValue * nNumX + nNumX)
					{
						//�I���\�Ȏ�
						if (m_pModuleList[m_nSelectModuleNum]->GetCanModuleSelect())
						{
							//������
							break;
						}

						//�J�E���g�A�b�v
						m_nSelectModuleNum++;
					}

					//���̗�ɓ˓����Ă��܂����ꍇ
					if (nValue != m_nSelectModuleNum / nNumX)
					{
						//�߂�
						m_nSelectModuleNum = m_SelectNumOld;
					}
					break;
				}
			}

			//��
			else if (pKeyboard->GetTrigger(DIK_DOWN))
			{
				//�I��ԍ� += ������
				m_nSelectModuleNum += nNumX;

				//�͈͓��ɗ}����
				if (CHossoLibrary::RangeLimit_Equal(m_nSelectModuleNum, nMin, nMax))
				{
					//���̒l�ɖ߂�
					m_nSelectModuleNum = m_SelectNumOld;
					break;
				}

				//�I���\�ȃ��W���[����������
				if (m_pModuleList[m_nSelectModuleNum]->GetCanModuleSelect())
				{
					//break
					break;
				}

				else
				{
					//�ړ���̗�̍��[�ɖ߂�
					int nValue = m_nSelectModuleNum / nNumX;
					m_nSelectModuleNum = nValue * nNumX;

					while (m_nSelectModuleNum <= nValue * nNumX + nNumX)
					{
						//�I���\�Ȏ�
						if (m_pModuleList[m_nSelectModuleNum]->GetCanModuleSelect())
						{
							//������
							break;
						}

						//�J�E���g�A�b�v
						m_nSelectModuleNum++;
					}

					//���̗�ɓ˓����Ă��܂����ꍇ
					if (nValue != m_nSelectModuleNum / nNumX)
					{
						//�߂�
						m_nSelectModuleNum = m_SelectNumOld;
					}
					break;
				}

			}
		}
	}
}

//------------------------------------------------------------------------------
//�I���\�ȃ��W���[������
//��ԍŏ��ɐ��������Ƃ��Ɨ��\�؂�ւ����Ɏg��
//------------------------------------------------------------------------------
void CBomb::SearchHeadCanSelectNum(int nStartNum)
{
	//�ŏ��̑I��ԍ��ݒ�
	for (int nCnt = nStartNum; nCnt < (int)m_pModuleList.size(); nCnt++)
	{
		//�I���\��������
		if (m_pModuleList[nCnt]->GetCanModuleSelect())
		{
			//���݂̑I��ԍ��ɐݒ�
			m_nSelectModuleNum = nCnt;
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
	m_nModuleNum = 3;


	//1�Ԗ�
	CBomb::CreateModuleOne<CModule_Timer>();
	//2�Ԗ�
	CBomb::CreateModuleOne<CModule_No0_SymbolKeyPad>();
	//3�Ԗ�
	CBomb::CreateModuleOne<CModule_No1_ShapeKeyPad>();
	//4�Ԗ�
	CBomb::CreateModuleOne<CModule_No2_LampAndWire>();
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

	//���W���[�����m�F
	m_nModuleNum = std::count_if(m_pModuleList.begin(), m_pModuleList.end(),
		[](S_ptr<CModule_Base> const &ptr) {return ptr->GetCanModuleSelect(); });

}
#endif //_DEBUG
