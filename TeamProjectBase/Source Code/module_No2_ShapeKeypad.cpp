//------------------------------------------------------------------------------
//
//���W���[���̐}�`�̃L�[�p�b�h����  [module_No2_ShapeKeypad.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "module_No2_ShapeKeypad.h"
#include "module_parts_No2_ShapeKey.h"
#include "module_parts_ProgressLamp.h"
#include "renderer.h"
#include "manager.h"
#include "modelinfo.h"
#include "timer.h"
#include "keyboard.h"
#include "game.h"
#include "Mylibrary.h"
#include "scene3D.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define KEYPAD_NUM						(4)									//�p�b�h�̑���
#define KEYPAD_INTERVAL					(D3DXVECTOR3(25.0f,0.0f,0.0f))		//�p�b�h�̊Ԋu
#define KEYPAD_OFFSET					(D3DXVECTOR3(1.0f,-15.0f,-25.0f))	//�p�b�h�̃I�t�Z�b�g���W
#define DISPLAY_SHAPE_OFFSET			(D3DXVECTOR3(-18.0f,18.0f,-25.0f))	//�f�B�X�v���C�̋L���̃I�t�Z�b�g�Ԋu
#define DISPLAY_SHAPE_SIZE				(D3DXVECTOR3(20.0f,20.0f,0.0f))		//�f�B�X�v���C�̋L���̃T�C�Y
#define PROGRESS_LAMP_OFFSET			(D3DXVECTOR3(29.0f,7.0f,-25.0f))	//�i���x�����v�̃I�t�Z�b�g

#define QUESTION_CHANGE_TIME			(40)								//���ύX���ɂ����鎞��

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CModule_No2_ShapeKeyPad::CModule_No2_ShapeKeyPad()
{
	//������
	m_pKeyPadList = {};
	m_pProgressLamp = {};

	m_nSelectNum = PLACE::LEFT_TO_1ST;
	m_NowQuestion = QUESTION::Q_1;
	m_DisplayShape = SHAPE::CIRCLE;
	m_state = STATE::NORMAL;
	m_nQuestionChangeCnt = 0;

	//�z��̑傫���ݒ�
	m_Memories.resize((int)CModule_No2_ShapeKeyPad::QUESTION::MAX);
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CModule_No2_ShapeKeyPad::~CModule_No2_ShapeKeyPad()
{
	m_pKeyPadList.clear();
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CModule_No2_ShapeKeyPad::Init()
{
	//���f�����ݒ�
	BindModelInfo(CModelInfo::GetModelInfo(CModelInfo::MODEL_MODULE_NO2));

	//�����v����
	CModule_Base::CreateLamp();

	//�L�[�p�b�h����
	CreateKeyPad();

	//�f�B�X�v���C�̐}�`����
	CreateDisplayShape();

	//�i���x�̃����v����
	CreateProgressLamp();

	//�}�`�V���b�t��
	ShapeShuffle();

	//�������{�^���Z�b�g
	SetNextPushKey();

	CSceneX::Init();

	return S_OK;
}

//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CModule_No2_ShapeKeyPad::Update()
{
	CSceneX::Update();

	//�X�e�[�g�X�V
	UpdateState();

	//nullcheck
	if (m_pDisplayShape)
	{
		m_pDisplayShape->Update();
	}

}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CModule_No2_ShapeKeyPad::Draw()
{
	CSceneX::Draw();

	//nullcheck
	if (m_pDisplayShape)
	{
		m_pDisplayShape->Draw();
	}
}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CModule_No2_ShapeKeyPad::ShowDebugInfo()
{
#ifdef _DEBUG

	//CDebugProc::Print(CDebugProc::PLACE_LEFT, "State >> [%d]\n", m_state);
	//CDebugProc::Print(CDebugProc::PLACE_LEFT, "CntState >> [%d]\n", m_nQuestionChangeCnt);


	//ImGui::DragFloat3("pos1", m_pKeyPadList[0]->GetPos(),0.05f);
	//ImGui::DragFloat3("pos2", m_pKeyPadList[1]->GetPos(), 0.05f);
	//ImGui::DragFloat3("pos3", m_pKeyPadList[2]->GetPos(), 0.05f);
	//ImGui::DragFloat3("pos4", m_pKeyPadList[3]->GetPos(), 0.05f);

	//�I������Ă���Ƃ�
	if (GetSelect())
	{
		CDebugProc::Print(CDebugProc::PLACE_LEFT, "-------------Module_No_2----------------\n");

		CDebugProc::Print(CDebugProc::PLACE_LEFT, "Flag >> ");

		for (size_t nCnt = 0; nCnt < m_pKeyPadList.size(); nCnt++)
		{
			CDebugProc::Print(CDebugProc::PLACE_LEFT, "[%d] ", m_pKeyPadList[nCnt]->GetClearFlag());
		}

		CDebugProc::Print(CDebugProc::PLACE_LEFT, NEWLINE);

		for (size_t nCnt = 0; nCnt < m_Memories.size(); nCnt++)
		{
			CDebugProc::Print(CDebugProc::PLACE_LEFT, "Memories >> Place[%d] Shape[%d]\n", m_Memories[nCnt].place, m_Memories[nCnt].shape);
		}
	}

#endif //DEBUG
}
//------------------------------------------------------------------------------
//�L�[�p�b�h����
//------------------------------------------------------------------------------
void CModule_No2_ShapeKeyPad::Operation()
{
	int nSelectNumOld = m_nSelectNum;

	if (m_state != STATE::NORMAL)
	{
		for (size_t nCnt = 0; nCnt < m_pKeyPadList.size(); nCnt++)
		{
			//nullcheck
			if (m_pKeyPadList[nCnt].get())
			{
				m_pKeyPadList[nCnt]->SetSelect(false);
			}
		}
		//return
		return;
	}

	//���͂�������������break
	CHossoLibrary::Selecting((int&)m_nSelectNum, nSelectNumOld, 4, 1);

	for (size_t nCnt = 0; nCnt < m_pKeyPadList.size(); nCnt++)
	{
		//nullcheck
		if (m_pKeyPadList[nCnt].get())
		{
			//���݂̑I��ԍ��Ɠ������m����true�ɂ��Ă���
			nCnt == m_nSelectNum ?
				m_pKeyPadList[nCnt]->SetSelect(true) :
				m_pKeyPadList[nCnt]->SetSelect(false);
		}
	}

	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		if (m_pKeyPadList[m_nSelectNum].get())
		{
			//�������{�^�����N���A�{�^���������ꍇ
			if (m_pKeyPadList[m_nSelectNum]->GetClearFlag())
			{
				//�N���A
				QuestionClear();

				//�N���A�������`�F�b�N
				CheckClear();
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
		//�I������
		CModule_Base::SelectRelease<CModule_Parts_No2_ShapeKey>(m_pKeyPadList);

		//�Q�[���̎��_�ύX
		CManager::GetGame()->SetGaze(CGame::GAZE_BOMB);
	}

}

//------------------------------------------------------------------------------
//�X�e�[�g�X�V
//------------------------------------------------------------------------------
void CModule_No2_ShapeKeyPad::UpdateState()
{

	switch (m_state)
	{
	case STATE::NORMAL:

		break;

	case STATE::DISAPPEAR:
		m_nQuestionChangeCnt--;

		for (int nCnt = 0; nCnt < (int)m_pKeyPadList.size(); nCnt++)
		{
			if ((QUESTION_CHANGE_TIME - m_nQuestionChangeCnt) / (QUESTION_CHANGE_TIME / 4) >= nCnt)
			{
				m_pKeyPadList[nCnt]->GetPos().z += 1.0f;
				CHossoLibrary::RangeLimit_Equal(m_pKeyPadList[nCnt]->GetPos().z, DISPLAY_SHAPE_OFFSET.z,-10.0f );
			}
		}

		if (m_nQuestionChangeCnt <= 0)
		{
			SetState(STATE::APPEAR);

			//�}�`�V���b�t��
			ShapeShuffle();

			//���̖��ݒ�
			SetNextPushKey();
		}

		break;

	case STATE::APPEAR:

		m_nQuestionChangeCnt--;

		for (int nCnt = 0; nCnt < (int)m_pKeyPadList.size(); nCnt++)
		{
			if ((QUESTION_CHANGE_TIME - m_nQuestionChangeCnt) / (QUESTION_CHANGE_TIME / 4) >= nCnt)
			{
				m_pKeyPadList[nCnt]->GetPos().z -= 1.0f;
				CHossoLibrary::RangeLimit_Equal(m_pKeyPadList[nCnt]->GetPos().z, DISPLAY_SHAPE_OFFSET.z, -10.0f);
			}
		}

		if (m_nQuestionChangeCnt <= 0)
		{
			SetState(STATE::NORMAL);
		}
		break;
	}

}

//------------------------------------------------------------------------------
//���N���A
//------------------------------------------------------------------------------
void CModule_No2_ShapeKeyPad::QuestionClear()
{
	//�������{�^����ۑ�
	m_Memories[(int)m_NowQuestion].place = m_nSelectNum;
	m_Memories[(int)m_NowQuestion].shape = m_pKeyPadList[m_nSelectNum]->GetShape();

	for (size_t nCnt = 0; nCnt < m_pKeyPadList.size(); nCnt++)
	{
		//�t���O������
		m_pKeyPadList[nCnt]->SetClearFlag(false);
	}

	//���̖��Ɉڍs
	int nValue = (int)m_NowQuestion;
	nValue++;
	m_NowQuestion = (QUESTION)nValue;

	//�i�������v�̍X�V
	m_pProgressLamp->SetProgress(nValue);

	//���S�ďI���Ă����ꍇ
	if (m_NowQuestion >= QUESTION::MAX)
	{
		return;
	}


	//�X�e�[�g�؂�ւ�
	SetState(STATE::DISAPPEAR);
}

//------------------------------------------------------------------------------
//�f�B�X�v���C�̐}�`����
//------------------------------------------------------------------------------
void CModule_No2_ShapeKeyPad::CreateDisplayShape()
{
	//�f�B�X�v���C�̋L������
	m_pDisplayShape = CSceneBase::ScenePolygonCreateSelfManagement<CScene3D>
		(DISPLAY_SHAPE_OFFSET, DISPLAY_SHAPE_SIZE, GreenColor, CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_MODULEPARTS_MODULE01));

	//�e�}�g���b�N�X�ݒ�
	m_pDisplayShape->SetParentMtxPtr(GetMtxWorldPtr());

	//���C�e�B���Ooff
	m_pDisplayShape->SetLighting(false);
}

//------------------------------------------------------------------------------
//�L�[�p�b�h����
//------------------------------------------------------------------------------
void CModule_No2_ShapeKeyPad::CreateKeyPad()
{
	//�S�ẴL�[�Ɋ��蓖�Ă�
	for (size_t nCnt = 0; nCnt < KEYPAD_NUM; nCnt++)
	{
		//�L�[����
		m_pKeyPadList.emplace_back(CModule_Parts_Base::Create_ModuleParts<CModule_Parts_No2_ShapeKey>
			(KEYPAD_OFFSET + D3DXVECTOR3(-((KEYPAD_INTERVAL.x) * (KEYPAD_NUM / 2)) + (KEYPAD_INTERVAL.x * 0.5f) + (KEYPAD_INTERVAL.x * nCnt), 0.0f, 0.0f), GetMtxWorldPtr()));
	}
}

//------------------------------------------------------------------------------
//�i���x�̃����v����
//------------------------------------------------------------------------------
void CModule_No2_ShapeKeyPad::CreateProgressLamp()
{
	m_pProgressLamp = CModule_Parts_Base::Create_ModuleParts<CModule_Parts_ProgressLamp>(PROGRESS_LAMP_OFFSET, GetMtxWorldPtr());
}

//------------------------------------------------------------------------------
//�N���A�������`�F�b�N
//------------------------------------------------------------------------------
void CModule_No2_ShapeKeyPad::CheckClear()
{
	//����S�ďI������
	if (m_NowQuestion >= QUESTION::MAX)
	{
		//���W���[���N���A
		CModule_Base::Module_Clear();
	}
}
//------------------------------------------------------------------------------
//�}�`���V���b�t��
//------------------------------------------------------------------------------
void CModule_No2_ShapeKeyPad::ShapeShuffle()
{
	//�ԍ��������Ă�z��
	Vec<SHAPE> nShapeList = { SHAPE::CIRCLE,SHAPE::CROSS ,SHAPE::TRIANGLE ,SHAPE::SQUARE };

	//�V���b�t��
	CHossoLibrary::Vec_Shuffle(nShapeList);

	for (size_t nCnt = 0; nCnt < nShapeList.size(); nCnt++)
	{
		//�}�`�ݒ�
		m_pKeyPadList[nCnt]->SetShape(nShapeList[nCnt]);
	}

	//�f�B�X�v���C�̐}�`�������_���Őݒ�
	SetDisplayShape(rand() % KEYPAD_NUM);

}
//------------------------------------------------------------------------------
//�A�j���[�V�����ݒ�
//------------------------------------------------------------------------------
void CModule_No2_ShapeKeyPad::SetDisplayShape(int nShape)
{
	//�}�`�ݒ�
	m_DisplayShape = (SHAPE)nShape;

	//UV�ݒ�
	m_pDisplayShape->SetAnimation(CHossoLibrary::CalcUV_StaticFunc(nShape, CTexture::SEPARATE_TEX_MODULEPARTS_MODULE01),
		CTexture::GetSparateTex_UVSize(CTexture::SEPARATE_TEX_MODULEPARTS_MODULE01));
}

//------------------------------------------------------------------------------
//���̉����L�[�ݒ�
//------------------------------------------------------------------------------
void CModule_No2_ShapeKeyPad::SetNextPushKey()
{
	//���݂�����ڂ�
	switch (m_NowQuestion)
	{
	case CModule_No2_ShapeKeyPad::QUESTION::Q_1:
		switch (m_DisplayShape)
		{
		case CModule_No2_ShapeKeyPad::SHAPE::CIRCLE:
			SetNextPushKey_FromPlace(PLACE::LEFT_TO_2ND);
			break;

		case CModule_No2_ShapeKeyPad::SHAPE::CROSS:
			SetNextPushKey_FromPlace(PLACE::LEFT_TO_4TH);
			break;

		case CModule_No2_ShapeKeyPad::SHAPE::TRIANGLE:
			SetNextPushKey_FromShape(SHAPE::TRIANGLE);
			break;

		case CModule_No2_ShapeKeyPad::SHAPE::SQUARE:
			SetNextPushKey_FromShape(SHAPE::CROSS);
			break;
		}
		break;

	case CModule_No2_ShapeKeyPad::QUESTION::Q_2:
		switch (m_DisplayShape)
		{
		case CModule_No2_ShapeKeyPad::SHAPE::CIRCLE:
			SetNextPushKey_FromPlace(m_Memories[(int)QUESTION::Q_1].place);
			break;

		case CModule_No2_ShapeKeyPad::SHAPE::CROSS:
			SetNextPushKey_FromPlace(PLACE::LEFT_TO_4TH);
			break;

		case CModule_No2_ShapeKeyPad::SHAPE::TRIANGLE:
			SetNextPushKey_FromPlace(PLACE::LEFT_TO_2ND);
			break;

		case CModule_No2_ShapeKeyPad::SHAPE::SQUARE:
			SetNextPushKey_FromShape(SHAPE::CIRCLE);
			break;
		}
		break;

	case CModule_No2_ShapeKeyPad::QUESTION::Q_3:
		switch (m_DisplayShape)
		{
		case CModule_No2_ShapeKeyPad::SHAPE::CIRCLE:
			SetNextPushKey_FromPlace(PLACE::LEFT_TO_3RD);
			break;

		case CModule_No2_ShapeKeyPad::SHAPE::CROSS:
			SetNextPushKey_FromShape(m_Memories[(int)QUESTION::Q_1].shape);
			break;

		case CModule_No2_ShapeKeyPad::SHAPE::TRIANGLE:
			SetNextPushKey_FromShape(SHAPE::SQUARE);
			break;

		case CModule_No2_ShapeKeyPad::SHAPE::SQUARE:
			SetNextPushKey_FromPlace(PLACE::LEFT_TO_1ST);
			break;
		}
		break;

	case CModule_No2_ShapeKeyPad::QUESTION::Q_4:
		switch (m_DisplayShape)
		{
		case CModule_No2_ShapeKeyPad::SHAPE::CIRCLE:
			SetNextPushKey_FromPlace(m_Memories[(int)QUESTION::Q_2].place);
			break;

		case CModule_No2_ShapeKeyPad::SHAPE::CROSS:
			SetNextPushKey_FromPlace(PLACE::LEFT_TO_2ND);
			break;

		case CModule_No2_ShapeKeyPad::SHAPE::TRIANGLE:
			SetNextPushKey_FromShape(SHAPE::CIRCLE);
			break;

		case CModule_No2_ShapeKeyPad::SHAPE::SQUARE:
			SetNextPushKey_FromPlace(PLACE::LEFT_TO_4TH);
			break;
		}
		break;

	}
}

//------------------------------------------------------------------------------
//���̉����L�[�ݒ�@�}�`����ɐݒ�
//------------------------------------------------------------------------------
void CModule_No2_ShapeKeyPad::SetNextPushKey_FromShape(SHAPE shape)
{
	//���͂��ꂽshape�Ɠ����L�[����
	auto itr = std::find_if(m_pKeyPadList.begin(), m_pKeyPadList.end(),
		[shape](S_ptr<CModule_Parts_No2_ShapeKey> pPtr) {return pPtr->GetShape() == shape; });

	//nullcheck
	if (itr != m_pKeyPadList.end())
	{
		//�N���A�t���O�ݒ�
		itr->get()->SetClearFlag(true);
	}
}

//------------------------------------------------------------------------------
//���̉����L�[�ݒ�@�ꏊ����ɐݒ�
//------------------------------------------------------------------------------
void CModule_No2_ShapeKeyPad::SetNextPushKey_FromPlace(PLACE place)
{
	//nullcheck
	if (m_pKeyPadList[place])
	{
		//�N���A�t���O�ݒ�
		m_pKeyPadList[place]->SetClearFlag(true);
	}
}


//------------------------------------------------------------------------------
//�X�e�[�g�ݒ�
//------------------------------------------------------------------------------
void CModule_No2_ShapeKeyPad::SetState(STATE state)
{

	m_state = state;

	switch (m_state)
	{
	case STATE::NORMAL:

		break;

	case STATE::DISAPPEAR:
		m_nQuestionChangeCnt = QUESTION_CHANGE_TIME;
		break;

	case STATE::APPEAR:
		m_nQuestionChangeCnt = QUESTION_CHANGE_TIME;
		break;

	default:
		break;
	}

}
