//------------------------------------------------------------------------------
//
//���W���[���̃{�^������  [Module_No0_SymbolKeypad.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "module_No0_SymbolKeyPad.h"
#include "module_parts_No0_SymbolKey.h"
#include "renderer.h"
#include "manager.h"
#include "modelinfo.h"
#include "timer.h"
#include "Mylibrary.h"
#include "sound.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define MAX_KEYPAD						(9)									//�p�b�h�̑���
#define KEYPAD_INTERVAL					(D3DXVECTOR3(20.0f,20.0f,0.0f))		//�p�b�h�̊Ԋu
#define KEYPAD_OFFSET					(D3DXVECTOR3(-10.0f,0.0f,-20.0f))	//�p�b�h�̃I�t�Z�b�g���W
#define KEYPAD_NEED_CLEAR_KEY_NUM		(4)									//�N���A�ɕK�v�ȃL�[��

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CModule_No0_SymbolKeyPad::CModule_No0_SymbolKeyPad()
{
	m_pKeyPadList = {};
	m_nNextSymbolNum = 0;
	m_nSelectNum = 0;
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CModule_No0_SymbolKeyPad::~CModule_No0_SymbolKeyPad()
{
	m_pKeyPadList.clear();
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CModule_No0_SymbolKeyPad::Init()
{
	//���f�����ݒ�
	BindModelInfo(CModelInfo::GetModelInfo(CModelInfo::MODEL_MODULE_NO0));

	//�����v����
	CModule_Base::CreateLamp();

	//�����̃p�^�[���������_���Őݒ�
	m_Answer = (CModule_No0_SymbolKeyPad::ANSWER_PATTERN)(rand() & CModule_No0_SymbolKeyPad::ANSWER_6);

	//�L�[�p�b�h����
	CreateKeyPad(m_Answer);

	//���̓����ݒ�
	m_nNextSymbolNum = m_Answer * KEYPAD_NEED_CLEAR_KEY_NUM;

	CSceneX::Init();
	return S_OK;
}

//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CModule_No0_SymbolKeyPad::Update()
{
	CSceneX::Update();
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CModule_No0_SymbolKeyPad::Draw()
{
	CSceneX::Draw();
}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CModule_No0_SymbolKeyPad::ShowDebugInfo()
{
#ifdef _DEBUG

	//�I������Ă���Ƃ�
	if (GetSelect())
	{

		CDebugProc::Print(CDebugProc::PLACE_LEFT, "-------------Module_No_1----------------\n");

		CDebugProc::Print(CDebugProc::PLACE_LEFT, "KeyPad >> [%d] [%d] [%d]\n", m_pKeyPadList[0]->GetSymbolNum(), m_pKeyPadList[1]->GetSymbolNum(), m_pKeyPadList[2]->GetSymbolNum());
		CDebugProc::Print(CDebugProc::PLACE_LEFT, "KeyPad >> [%d] [%d] [%d]\n", m_pKeyPadList[3]->GetSymbolNum(), m_pKeyPadList[4]->GetSymbolNum(), m_pKeyPadList[5]->GetSymbolNum());
		CDebugProc::Print(CDebugProc::PLACE_LEFT, "KeyPad >> [%d] [%d] [%d]\n", m_pKeyPadList[6]->GetSymbolNum(), m_pKeyPadList[7]->GetSymbolNum(), m_pKeyPadList[8]->GetSymbolNum());

		CDebugProc::Print(CDebugProc::PLACE_LEFT, "NextSymbolNum >> [%d] \n", m_nNextSymbolNum);

	}

#endif //DEBUG
}
//------------------------------------------------------------------------------
//�L�[�p�b�h����
//------------------------------------------------------------------------------
void CModule_No0_SymbolKeyPad::Operation_Keyboard()
{
	int nSelectNumOld = m_nSelectNum;
	int nCntClearPad = 0;

	//�I������
	//���͂�������������break
	CHossoLibrary::Selecting(m_nSelectNum, nSelectNumOld, 3, 3);

	//�I�����Ă����Ԃ̃��m��ݒ�
	CModule_Base::ModuleParts_Select<CModule_Parts_No0_SymbolKey>(m_pKeyPadList, m_nSelectNum);

	//�L�[����
	CModule_Base::Operation_Keyboard();
}

//------------------------------------------------------------------------------
//���W���[������@�}�E�X
//------------------------------------------------------------------------------
void CModule_No0_SymbolKeyPad::Operation_Mouse()
{
	//���C�̔���
	CHossoLibrary::RayCollision_ModuleSelect(m_pKeyPadList.begin(),m_pKeyPadList.end(), m_nSelectNum);

	//�}�E�X����
	CModule_Base::Operation_Mouse();
}

//------------------------------------------------------------------------------
//���W���[���A�N�V����
//------------------------------------------------------------------------------
void CModule_No0_SymbolKeyPad::ModuleAction()
{
	//�I��ԍ���-1�Ƃ���������
	if (m_nSelectNum < 0)
	{
		return;
	}
	//nullcheck
	if (m_pKeyPadList[m_nSelectNum].get())
	{
		//�N���A��Ԃ̃{�^���ɂ͉����ł��Ȃ�
		if (m_pKeyPadList[m_nSelectNum]->GetKeyPadState() == CModule_Parts_No0_SymbolKey::KEYPAD_STATE::CLEAR)
		{
			return;
		}

		//���Đ�
		CManager::GetSound()->Play(CSound::LABEL_SE_MODULE_PUSH);

		//���̃V���{���Ɠ����V���{����������
		if (m_nNextSymbolNum == m_pKeyPadList[m_nSelectNum]->GetSymbolNum())
		{
			m_pKeyPadList[m_nSelectNum]->SetKeypadState(CModule_Parts_No0_SymbolKey::KEYPAD_STATE::CLEAR);
			m_nNextSymbolNum++;

			//�N���A�������`�F�b�N
			CheckClear();
		}
		else
		{	//���s
			m_pKeyPadList[m_nSelectNum]->SetKeypadState(CModule_Parts_No0_SymbolKey::KEYPAD_STATE::FAILED);
			CModule_Base::Module_Failed();
		}
	}
}

//------------------------------------------------------------------------------
//���W���[���̑I������
//------------------------------------------------------------------------------
void CModule_No0_SymbolKeyPad::ModuleCancel()
{
	//�I������
	CModule_Base::ModuleParts_Select<CModule_Parts_No0_SymbolKey>(m_pKeyPadList, -1);
}

//------------------------------------------------------------------------------
//�L�[�p�b�h����
//------------------------------------------------------------------------------
void CModule_No0_SymbolKeyPad::CreateKeyPad(ANSWER_PATTERN answer)
{
	//�V���{���̃i���o�[�̃��X�g
	Vec<int> nAllSymbolPatternList(24);
	Vec<int> nSymbolNumList = {};

	//������
	for (int nCnt = 0; nCnt < (int)nAllSymbolPatternList.size(); nCnt++)
	{
		nAllSymbolPatternList[nCnt] = nCnt;
	}

	//�����ݒ�
	//Answer�̔ԍ�����4�������
	for (int nCnt = 0; nCnt < KEYPAD_NEED_CLEAR_KEY_NUM; nCnt++)
	{
		//�C�e���[�^�擾
		auto itr = std::find_if(nAllSymbolPatternList.begin(), nAllSymbolPatternList.end(),
			[nCnt, answer](int &rValue) {return (rValue == nCnt + answer * KEYPAD_NEED_CLEAR_KEY_NUM); });

		//�C�e���[�^��end�ȊO��������
		if (itr != nAllSymbolPatternList.end())
		{
			//�z��ɒǉ�
			nSymbolNumList.emplace_back(*itr);

			//�g�����ԍ��͍폜
			nAllSymbolPatternList.erase(itr);
		}
	}

	//9�ɂȂ�܂ŌJ��Ԃ�
	while (nSymbolNumList.size() < MAX_KEYPAD)
	{
		//�����_���Ő����ݒ�
		int nNum = rand() % nAllSymbolPatternList.size();

		//�����_���Ŕԍ��ݒ�
		nSymbolNumList.emplace_back(nAllSymbolPatternList[nNum]);

		//�g�����ԍ��͍폜
		nAllSymbolPatternList.erase(nAllSymbolPatternList.begin() + nNum);
	}

	//�V���{�����V���b�t��
	CHossoLibrary::Vec_Shuffle(nSymbolNumList);

	//�S�ẴL�[�Ɋ��蓖�Ă�
	for (size_t nCnt = 0; nCnt < nSymbolNumList.size(); nCnt++)
	{
		//���W�v�Z�p
		INTEGER2 Value;
		Value.nX = nCnt % 3;
		Value.nY = nCnt / 3;

		//�L�[����
		m_pKeyPadList.emplace_back(CModule_Parts_Base::Create_ModuleParts<CModule_Parts_No0_SymbolKey>
			(KEYPAD_OFFSET + D3DXVECTOR3(	-KEYPAD_INTERVAL.x + KEYPAD_INTERVAL.x * Value.nX,
											KEYPAD_INTERVAL.y - KEYPAD_INTERVAL.y * Value.nY, 0.0f), GetMtxWorldPtr()));

		//�V���{���ݒ�
		m_pKeyPadList[m_pKeyPadList.size() - 1]->SetSymbol(nSymbolNumList[nCnt]);

	}
}

//------------------------------------------------------------------------------
//�N���A�������`�F�b�N
//------------------------------------------------------------------------------
void CModule_No0_SymbolKeyPad::CheckClear()
{
	//�N���A�ɕK�v�ȃL�[���ɒB�������ǂ���
	if (std::count_if(m_pKeyPadList.begin(), m_pKeyPadList.end(),
		[](S_ptr<CModule_Parts_No0_SymbolKey> &vec) {return (vec->GetClearFlag()); }) >= KEYPAD_NEED_CLEAR_KEY_NUM)
	{
		//���W���[���N���A
		CModule_Base::Module_Clear();

		//���̓����������Ƃ�
		m_nNextSymbolNum = -1;
	}
}