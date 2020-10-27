//------------------------------------------------------------------------------
//
//���W���[���̐}�`�̃L�[�p�b�h����  [module_ShapeKeypad.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "module_No2_ShapeKeypad.h"
#include "module_parts_No2_ShapeKey.h"
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
#define KEYPAD_OFFSET					(D3DXVECTOR3(0.0f,-15.0f,-20.0f))	//�p�b�h�̃I�t�Z�b�g���W
#define DISPLAY_SHAPE_OFFSET			(D3DXVECTOR3(-7.5f,20.0f,-25.0f))	//�f�B�X�v���C�̋L���̃I�t�Z�b�g�Ԋu
#define DISPLAY_SHAPE_SIZE				(D3DXVECTOR3(20.0f,20.0f,0.0f))		//�f�B�X�v���C�̋L���̃T�C�Y


//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CModule_No2_ShapeKeyPad::CModule_No2_ShapeKeyPad()
{
	m_pKeyPadList = {};
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

	////�����̃p�^�[���������_���Őݒ�
	//m_Answer = (CModule_No2_ShapeKeyPad::ANSWER_PATTERN)(rand() & CModule_No2_ShapeKeyPad::ANSWER_6);

	//�L�[�p�b�h����
	CreateKeyPad();

	//�f�B�X�v���C�̋L������
	m_pDisplayShape = CSceneBase::ScenePolygonCreateSelfManagement<CScene3D>
		(DISPLAY_SHAPE_OFFSET, DISPLAY_SHAPE_SIZE, GreenColor, CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_MODULEPARTS_MODULE01));

	//�e�}�g���b�N�X�ݒ�
	m_pDisplayShape->SetParentMtxPtr(GetMtxWorldPtr());


	ShapeShuffle();
	//�t�u�ݒ�

	////���̓����ݒ�
	//m_nNextSymbolNum = m_Answer * KEYPAD_NEED_CLEAR_KEY_NUM;

	CSceneX::Init();
	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CModule_No2_ShapeKeyPad::Uninit()
{
	CSceneX::Uninit();
}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CModule_No2_ShapeKeyPad::Update()
{
	CSceneX::Update();

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

#endif //DEBUG
}
//------------------------------------------------------------------------------
//�L�[�p�b�h����
//------------------------------------------------------------------------------
void CModule_No2_ShapeKeyPad::Operation()
{
	static int nSelectNum = 0;

	int nSelectNumOld = nSelectNum;
	int nCntClearPad = 0;

	//���͂�������������break
	CHossoLibrary::Selecting(nSelectNum, nSelectNumOld, 4, 1);

	for (size_t nCnt = 0; nCnt < m_pKeyPadList.size(); nCnt++)
	{
		//nullcheck
		if (m_pKeyPadList[nCnt].get())
		{
			//���݂̑I��ԍ��Ɠ������m����true�ɂ��Ă���
			nCnt == nSelectNum ?
				m_pKeyPadList[nCnt]->SetSelect(true) :
				m_pKeyPadList[nCnt]->SetSelect(false);
		}
	}

	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		//if (m_pKeyPadList[nSelectNum].get())
		//{
		//	//���̃V���{���Ɠ����V���{����������
		//	if (m_nNextSymbolNum == m_pKeyPadList[nSelectNum]->GetSymbolNum())
		//	{
		//		m_pKeyPadList[nSelectNum]->SetKeypadState(CModule_Parts_No1_SymbolKey::KEYPAD_STATE::CLEAR);
		//		m_nNextSymbolNum++;

		//		//�N���A�������`�F�b�N
		//		CheckClear();
		//	}
		//	else
		//	{	//���s
		//		m_pKeyPadList[nSelectNum]->SetKeypadState(CModule_Parts_No1_SymbolKey::KEYPAD_STATE::FAILED);
		//		CModule_Base::Module_Failed();
		//	}
		//}

		//�N���A�������`�F�b�N
		CheckClear();

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
void CModule_No2_ShapeKeyPad::CreateKeyPad()
{
	//�S�ẴL�[�Ɋ��蓖�Ă�
	for (size_t nCnt = 0; nCnt < KEYPAD_NUM; nCnt++)
	{
		//�L�[����
		m_pKeyPadList.emplace_back(CModule_Parts_Base::Create_ModuleParts<CModule_Parts_No2_ShapeKey>
			(KEYPAD_OFFSET + D3DXVECTOR3(-((KEYPAD_INTERVAL.x) * (KEYPAD_NUM / 2)) + (KEYPAD_INTERVAL.x * 0.5f) + (KEYPAD_INTERVAL.x * nCnt), 0.0f, 0.0f), GetMtxWorldPtr()));

		m_pKeyPadList[m_pKeyPadList.size() - 1]->SetShape(nCnt);
	}
}

//------------------------------------------------------------------------------
//�N���A�������`�F�b�N
//------------------------------------------------------------------------------
void CModule_No2_ShapeKeyPad::CheckClear()
{
	////�N���A�ɕK�v�ȃL�[���ɒB�������ǂ���
	//if (std::count_if(m_pKeyPadList.begin(), m_pKeyPadList.end(),
	//	[](std::shared_ptr<CModule_Parts_No1_SymbolKey> &vec) {return (vec->GetClearFlag()); }) >= KEYPAD_NEED_CLEAR_KEY_NUM)
	//{
		//���W���[���N���A
		CModule_Base::Module_Clear();
	//}
}
//------------------------------------------------------------------------------
//�}�`���V���b�t��
//------------------------------------------------------------------------------
void CModule_No2_ShapeKeyPad::ShapeShuffle()
{
	//�ԍ��������Ă�z��
	std::vector<int> nShapeList = { 0, 1, 2, 3 };

	//�ԍ��V���b�t��
	CHossoLibrary::Vec_Shuffle(nShapeList);

	for (size_t nCnt = 0; nCnt < nShapeList.size(); nCnt++)
	{
		//�}�`�ݒ�
		m_pKeyPadList[nCnt]->SetShape(nShapeList[nCnt]);
	}

	SetDisplayShape(rand() % KEYPAD_NUM);

}
//------------------------------------------------------------------------------
//�A�j���[�V�����ݒ�
//------------------------------------------------------------------------------
void CModule_No2_ShapeKeyPad::SetDisplayShape(int nShape)
{
	m_pDisplayShape->SetAnimation(CHossoLibrary::CalcUV_StaticFunc(nShape, CTexture::SEPARATE_TEX_MODULEPARTS_MODULE01),
		CTexture::GetSparateTex_UVSize(CTexture::SEPARATE_TEX_MODULEPARTS_MODULE01));
}

//------------------------------------------------------------------------------
//���̉����L�[�ݒ�
//------------------------------------------------------------------------------
void CModule_No2_ShapeKeyPad::SetNextPushKey()
{


}

//------------------------------------------------------------------------------
//���̉����L�[�ݒ�@�}�`����ɐݒ�
//------------------------------------------------------------------------------
void CModule_No2_ShapeKeyPad::SetNextPushKey_FromShape(SHAPE shape)
{
	//���͂��ꂽshape�Ɠ����L�[����
	auto itr = std::find_if(m_pKeyPadList.begin(), m_pKeyPadList.end(),
		[shape](std::shared_ptr<CModule_Parts_No2_ShapeKey> pPtr) {return (SHAPE)pPtr->GetShape() == shape; });

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
void CModule_No2_ShapeKeyPad::SetNextPushKey_FromPlace(int nPlace)
{
	m_pKeyPadList[nPlace]->SetClearFlag(true);
}
