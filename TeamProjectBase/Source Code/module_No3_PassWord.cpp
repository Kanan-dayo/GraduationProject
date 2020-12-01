//------------------------------------------------------------------------------
//
//���W���[���̃����v�ƃ��C���[�̂�̏���  [Module_No2_LampAndWire.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "module_parts_No3_Button.h"
#include "module_No3_PassWord.h"
#include "modelinfo.h"
#include "manager.h"
#include "keyboard.h"
#include "game.h"
#include "particle.h"
#include "mouse.h"
#include "sound.h"
#include "scene3D.h"

//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define BUTTON_OFFSET					(D3DXVECTOR3(-3.1f,0.0f,-20.0f))
#define BUTTON_ITNERVAL					(D3DXVECTOR3(14.0f,18.0f,0.0f))
#define BUTTON_NUM						(10)
#define NUMBER_NUM						(5)

#define DISPLAYNUM_OFFSET				(D3DXVECTOR3(-3.1f,0.0f,-20.0f))
#define DISPLAYNUM_INTERVAL				(D3DXVECTOR3(14.0f,0.0f,0.0f))
#define DISPLAYNUM_SIZE					(D3DXVECTOR3(11.0f,18.0f,0.0f))

#define DECITION_BUTTON_OFFSET			(D3DXVECTOR3(0.0f,-30.0f,-20.0f))


//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CModule_No3_PassWord::CModule_No3_PassWord()
{
	m_nSelectNum = 0;
	m_pDecitionButton.reset();
	m_pDisplayNum = {};
	m_nDisplayNum = { 0,0,0,0,0 };
	m_nAnswerNum = 0;
	m_AnswerPattern = ANSWER_PATTERN::ANSWER_1;
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CModule_No3_PassWord::~CModule_No3_PassWord()
{
	m_pDecitionButton.reset();
	m_pDisplayNum = {};
	m_nDisplayNum = {};
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CModule_No3_PassWord::Init()
{
	//���f�����ݒ�
	BindModelInfo(CModelInfo::GetModelInfo(CModelInfo::MODEL_MODULE_NO3));

	//�{�^������
	CreateButton();

	//�N���A�����v����
	CModule_Base::CreateLamp();

	//�f�B�X�v���C�̐��l����
	CreateDisplayNum();

	//�����ݒ�
	SetAnswer();

	//������
	CSceneX::Init();

	return S_OK;
}

//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CModule_No3_PassWord::Update()
{
	CSceneX::Update();

	CDebugProc::Print(CDebugProc::PLACE_LEFT, "DisplayNum >> [%d] [%d] [%d] [%d] [%d]\n", m_nDisplayNum[0], m_nDisplayNum[1], m_nDisplayNum[2], m_nDisplayNum[3], m_nDisplayNum[4]);
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "AnswerPattern >> [%d]\n", m_AnswerPattern);
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "AnswerNum >> [%d]\n", m_nAnswerNum);

}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CModule_No3_PassWord::Draw()
{
	CSceneX::Draw();
}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CModule_No3_PassWord::ShowDebugInfo()
{
#ifdef _DEBUG
	CModule_Base::ShowDebugInfo();

#endif //DEBUG
}

//------------------------------------------------------------------------------
//���W���[������
//------------------------------------------------------------------------------
void CModule_No3_PassWord::Operation_Keyboard()
{
	int nSelectNumOld = m_nSelectNum;

	//�I������
	CHossoLibrary::Selecting(m_nSelectNum, nSelectNumOld, 5, 2);

	//���W���[������
	CModule_Base::Operation_Keyboard();

}


//------------------------------------------------------------------------------
//���W���[������@�}�E�X
//------------------------------------------------------------------------------
void CModule_No3_PassWord::Operation_Mouse()
{
	//���C�̔���
	CHossoLibrary::RayCollision_ModuleSelect(m_pButtonList.begin(), m_pButtonList.end(), (int&)m_nSelectNum);

	//�}�E�X����
	CModule_Base::Operation_Mouse();

	if (CHossoLibrary::MouseRayCollision_Boolean(m_pDecitionButton->GetMtxWorldPtr(), m_pDecitionButton->GetModelInfo()->GetMesh()))
	{
		m_pDecitionButton->SetSelect(true);
	}
	else
	{
		m_pDecitionButton->SetSelect(false);
	}
}

//------------------------------------------------------------------------------
//���W���[���A�N�V����
//------------------------------------------------------------------------------
void CModule_No3_PassWord::ModuleAction()
{
	//����{�^�����I������Ă�����
	if (m_pDecitionButton->GetSelect())
	{
		//�N���A�`�F�b�N
		CheckClear();
	}

	//�I��ԍ���-1�Ƃ���������
	if (m_nSelectNum < 0)
	{
		return;
	}

	//nullcheck
	if (m_pButtonList[m_nSelectNum].get())
	{
		//�����ڂ��Z�o
		int nLocalValue = m_nSelectNum % 5;

		//���������ŉ��Z���邩���Z���邩
		m_nSelectNum / 5 == 0 ? m_nDisplayNum[nLocalValue]++ : m_nDisplayNum[nLocalValue]--;

		//0����9�̊ԂŃ��[�v������
		CHossoLibrary::RangeLimit_Loop(m_nDisplayNum[nLocalValue], 0, 9);

		//�f�B�X�v���C�̔ԍ��ύX
		ChangeDisplayNum();

	}
}

//------------------------------------------------------------------------------
//���W���[���̑I������
//------------------------------------------------------------------------------
void CModule_No3_PassWord::ModuleCancel()
{
	//�I������
	//CModule_Base::ModuleParts_Select<CModule_Parts_No2_Wire>(m_pButtonList, -1);
}

//------------------------------------------------------------------------------
//�����ݒ�
//------------------------------------------------------------------------------
void CModule_No3_PassWord::SetAnswer()
{
	//�����̃p�^�[���������_���Őݒ�
	m_AnswerPattern = (ANSWER_PATTERN)CHossoLibrary::RandomRangeUnsigned(ANSWER_PATTERN::ANSWER_1, ANSWER_PATTERN::ANSWER_MAX);

	switch (m_AnswerPattern)
	{
	case CModule_No3_PassWord::ANSWER_1:
		m_nAnswerNum = 26816;
		break;
	case CModule_No3_PassWord::ANSWER_2:
		m_nAnswerNum = 48390;
		break;
	case CModule_No3_PassWord::ANSWER_3:
		m_nAnswerNum = 55163;
		break;
	case CModule_No3_PassWord::ANSWER_4:
		m_nAnswerNum = 72843;
		break;
	case CModule_No3_PassWord::ANSWER_5:
		m_nAnswerNum = 80390;
		break;
	case CModule_No3_PassWord::ANSWER_6:
		m_nAnswerNum = 92864;
		break;
	default:
		break;
	}
}

//------------------------------------------------------------------------------
//�f�B�X�v���C�ɕ\�L����鐔�l
//------------------------------------------------------------------------------
void CModule_No3_PassWord::CreateDisplayNum()
{
	for (int nCnt = 0; nCnt < NUMBER_NUM ; nCnt++)
	{
		m_pDisplayNum.emplace_back(CSceneBase::ScenePolygonCreateShared<CScene3D>(DISPLAYNUM_OFFSET + D3DXVECTOR3(CHossoLibrary::CalcEvenPosition(5, nCnt, DISPLAYNUM_INTERVAL.x), 0.0f, 0.0f),
			DISPLAYNUM_SIZE, BlackColor, CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_UI_NUMBER), CScene::OBJTYPE_MODULE_PARTS_SYMBOL));
		m_pDisplayNum[nCnt]->SetParentMtxPtr(GetMtxWorldPtr());

		//UV���W�ݒ�
		m_pDisplayNum[nCnt]->SetAnimation(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.1f, 1.0f));

	}
}

//------------------------------------------------------------------------------
//�{�^������
//------------------------------------------------------------------------------
void CModule_No3_PassWord::CreateButton()
{

	for (int nCnt = 0; nCnt < BUTTON_NUM; nCnt++)
	{
		//���ϐ�
		INTEGER3 Value = { 0,0,0 };
		Value.x = nCnt % 5;
		Value.y = nCnt < 5 ? 1 : -1;

		//���W���[���p�[�c����
		m_pButtonList.emplace_back(CModule_Parts_Base::Create_ModuleParts<CModule_Parts_No3_Button>
		(BUTTON_OFFSET + D3DXVECTOR3(CHossoLibrary::CalcEvenPosition(5, Value.x, BUTTON_ITNERVAL.x), BUTTON_ITNERVAL.y / Value.y, 0.0f), GetMtxWorldPtr()));

		//�{�^���^�C�v�ݒ�
		m_pButtonList[nCnt]->SetButtonType(Value.y > 0 ? CModule_Parts_No3_Button::BUTTONTYPE::UP : CModule_Parts_No3_Button::BUTTONTYPE::DOWN);
	}

	//���M�{�^������
	m_pDecitionButton = CSceneX::CreateShared(DECITION_BUTTON_OFFSET, ZeroVector3, GetMtxWorldPtr(), OBJTYPE_MODULE_PARTS, CModelInfo::MODEL_MODULEPARTS_NO3_DECITION_BUTTON);

}

//------------------------------------------------------------------------------
//�N���A�������`�F�b�N
//�e���������Ă��邩�`�F�b�N
//------------------------------------------------------------------------------
void CModule_No3_PassWord::CheckClear()
{
	for (int nCnt = 0; nCnt < (int)m_nDisplayNum.size(); nCnt++)
	{
		//���l���o��
		int nValue = m_nAnswerNum % (int)powf(10.0f, m_nDisplayNum.size() - (float)nCnt) / (int)powf(10.0f, m_nDisplayNum.size() - (float)nCnt - 1.0f);

		//�f�B�X�v���C�̐��l�ƒl�̔�r
		if (m_nDisplayNum[nCnt] != nValue)
		{
			//��������̓��W���[���~�X
			Module_Failed();
			return;
		}
	}

	//�S�Ă����Ă����ꍇ�̓��W���[���N���A
	Module_Clear();
}

//------------------------------------------------------------------------------
//�f�B�X�v���C�̔ԍ��ύX
//------------------------------------------------------------------------------
void CModule_No3_PassWord::ChangeDisplayNum()
{
	//�e���̌v�Z
	for (size_t nCnt = 0; nCnt < NUMBER_NUM; nCnt++)
	{
		float fValue = (float)m_nDisplayNum[nCnt] / 10.0f;

		//UV���W�ݒ�
		m_pDisplayNum[nCnt]->SetAnimation(D3DXVECTOR2(fValue, 0.0f), D3DXVECTOR2(0.1f, 1.0f));
	}

}
