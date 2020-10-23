//------------------------------------------------------------------------------
//
//���W���[���̃L�[�p�b�h����  [module_keypad.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "module_keypad.h"
#include "module_parts_key.h"
#include "renderer.h"
#include "manager.h"
#include "modelinfo.h"
#include "timer.h"
#include "keyboard.h"
#include "game.h"
#include "Mylibrary.h"
#include <algorithm>
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define MAX_KEYPAD (9)
#define KEYPAD_INTERVAL (D3DXVECTOR3(20.0f,20.0f,0.0f))
#define KEYPAD_OFFSET (D3DXVECTOR3(-10.0f,0.0f,-20.0f))

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CModule_KeyPad::CModule_KeyPad()
{
	m_pKeyPadList = {};
	m_nNextSymbolNum = 0;
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CModule_KeyPad::~CModule_KeyPad()
{
	m_pKeyPadList.clear();
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CModule_KeyPad::Init()
{
	//���f�����ݒ�
	BindModelInfo(CModelInfo::GetModelInfo(CModelInfo::MODEL_MODULE_KEYPAD));

	//�����v����
	CModule_Base::CreateLamp();

	//�L�[�p�b�h����
	CreateKeyPad(CModule_KeyPad::ANSWER_1);

	CSceneX::Init();
	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CModule_KeyPad::Uninit()
{
	CSceneX::Uninit();
}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CModule_KeyPad::Update()
{
	CSceneX::Update();
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CModule_KeyPad::Draw()
{
	CSceneX::Draw();
}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CModule_KeyPad::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}
//------------------------------------------------------------------------------
//�L�[�p�b�h����
//------------------------------------------------------------------------------
void CModule_KeyPad::Operation()
{
	static int nSelectNum = 0;

	int nSelectNumOld = nSelectNum;
	int nCntClearPad = 0;

	//���͂�������������break
	CHossoLibrary::Selecting(nSelectNum, nSelectNumOld, 3, 3);

	for (size_t nCnt = 0; nCnt < m_pKeyPadList.size(); nCnt++)
	{
		//nullcheck
		if (m_pKeyPadList[nCnt].get())
		{
			//���݂̑I��ԍ��Ɠ������m����true�ɂ��Ă���
			nCnt == nSelectNum ?
				m_pKeyPadList[nCnt]->SetSelect(true) :
				m_pKeyPadList[nCnt]->SetSelect(false);

			//�N���A���Ă�����
			if (m_pKeyPadList[nCnt]->GetKeyPadState() == CModule_Parts_Key::KEYPAD_STATE::CLEAR)
			{
				//�N���A�J�E���g++
				nCntClearPad++;
			}
		}
	}

	if (nCntClearPad >= 4)
	{
		CModule_Base::Module_Clear();
	}

	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		if (m_pKeyPadList[nSelectNum].get())
		{
			if (m_nNextSymbolNum == m_pKeyPadList[nSelectNum]->GetSymbolNum())
			{
				m_pKeyPadList[nSelectNum]->SetKeypadState(CModule_Parts_Key::KEYPAD_STATE::CLEAR);
				m_nNextSymbolNum++;
			}
			else
			{
				m_pKeyPadList[nSelectNum]->SetKeypadState(CModule_Parts_Key::KEYPAD_STATE::FAILED);
				CModule_Base::Module_Failed();

			}

		}
	}

	//nullcheck
	if (CManager::GetKeyboard()->GetTrigger(DIK_BACKSPACE))
	{
		for (size_t nCnt = 0; nCnt < m_pKeyPadList.size(); nCnt++)
		{
			if (m_pKeyPadList[nCnt].get())
			{
				//���݂̑I��ԍ��Ɠ������m����true�ɂ��Ă���
				m_pKeyPadList[nCnt]->SetSelect(false);

				CManager::GetGame()->SetGaze(CGame::GAZE_BOMB);
			}
		}
	}

}
//------------------------------------------------------------------------------
//�L�[�p�b�h����
//------------------------------------------------------------------------------
void CModule_KeyPad::CreateKeyPad(ANSWER_PATTERN answer)
{
	//�V���{���̃i���o�[�̃��X�g
	std::vector<int> nAllSymbolPatternList(24);
	std::vector<int> nSymbolNumList = {};

	//������
	for (int nCnt = 0; nCnt < (int)nAllSymbolPatternList.size(); nCnt++)
	{
		nAllSymbolPatternList[nCnt] = nCnt;
	}

	//�����ݒ�
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		//�z��ɒǉ�
		nSymbolNumList.emplace_back(nAllSymbolPatternList[answer * 4]);

		//�폜
		nAllSymbolPatternList.erase(nAllSymbolPatternList.begin() + (answer * 4));
	}

	while (nSymbolNumList.size() <= 9)
	{
		int nNum = rand() % nAllSymbolPatternList.size();

		//�����_���Ŕԍ��ݒ�
		nSymbolNumList.emplace_back(nAllSymbolPatternList[nNum]);
		nAllSymbolPatternList.erase(nAllSymbolPatternList.begin() + nNum);
	}



	//for (auto iterator = nAllSymbolPatternList.begin(); iterator != nAllSymbolPatternList.end(); iterator++)
	//{
	//	//std::find_if()
	//}

	////�����̐ݒ�
	//for (int nCnt = 0; nCnt < 4; nCnt++)
	//{
	//	//�����̕���ݒ�
	//	nSymbolNumList.emplace_back();
	//	nAllSymbolPatternList.erase(nAllSymbolPatternList.begin() + nCnt + answer * 4);
	//}


	for (int nCnt = 0; nCnt < MAX_KEYPAD; nCnt++)
	{
		INTEGER2 Value;

		Value.nX = nCnt % 3;
		Value.nY = nCnt / 3;

		m_pKeyPadList.emplace_back(CModule_Parts_Base::Create_ModuleParts<CModule_Parts_Key>
			(KEYPAD_OFFSET + D3DXVECTOR3(	-KEYPAD_INTERVAL.x + KEYPAD_INTERVAL.x * Value.nX,
											KEYPAD_INTERVAL.y - KEYPAD_INTERVAL.y * Value.nY, 0.0f), GetMtxWorldPtr()));

		m_pKeyPadList[m_pKeyPadList.size() - 1]->SetSymbol(nSymbolNumList[nCnt]);

	}
}
