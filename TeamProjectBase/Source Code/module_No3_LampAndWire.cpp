//------------------------------------------------------------------------------
//
//���W���[���̃����v�ƃ��C���[�̂�̏���  [Module_No3_LampAndWire.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "module_No3_LampAndWire.h"
#include "module_parts_No3_Wire.h"
#include "modelinfo.h"
#include "manager.h"
#include "keyboard.h"
#include "game.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define WURE_OFFSET					(D3DXVECTOR3(-37.0f,0.0f,-23.0f))
#define WURE_ITNERVAL				(D3DXVECTOR3(12.0f,0.0f,0.0f))
#define WIRE_NUM					(6)
#define LAMP_NUM					(8)
//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CModule_No3_LampAndWire::CModule_No3_LampAndWire()
{
	m_NowSelectWire = WIRE::RED;
	m_nSelectPlace = 0;

	m_nRedLampNum = 0;
	m_nBlueLampNum = 0;
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CModule_No3_LampAndWire::~CModule_No3_LampAndWire()
{

}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CModule_No3_LampAndWire::Init()
{
	//���f�����ݒ�
	BindModelInfo(CModelInfo::GetModelInfo(CModelInfo::MODEL_MODULE_NO3));

	//���C���[����
	CreateWire();

	//�����v����
	CreateLamp();

	//������
	CSceneX::Init();

	return S_OK;
}

//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CModule_No3_LampAndWire::Update()
{
	CSceneX::Update();
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CModule_No3_LampAndWire::Draw()
{
	CSceneX::Draw();
}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CModule_No3_LampAndWire::ShowDebugInfo()
{
#ifdef _DEBUG
#endif //DEBUG
}

//------------------------------------------------------------------------------
//���W���[������
//------------------------------------------------------------------------------
void CModule_No3_LampAndWire::Operation()
{
	int nSelectNumOld = m_nSelectPlace;

	//�I������
	CHossoLibrary::Selecting(m_nSelectPlace, nSelectNumOld, 6, 1);

	for (size_t nCnt = 0; nCnt < m_pWireList.size(); nCnt++)
	{
		//nullcheck
		if (m_pWireList[nCnt].get())
		{
			//���݂̑I��ԍ��Ɠ������m����true�ɂ��Ă���
			nCnt == m_nSelectPlace ?
				m_pWireList[nCnt]->SetSelect(true) :
				m_pWireList[nCnt]->SetSelect(false);
		}
	}


	//nullcheck
	if (CManager::GetKeyboard()->GetTrigger(DIK_BACKSPACE))
	{
		//�I������
		CModule_Base::SelectRelease<CModule_Parts_No3_Wire>(m_pWireList);

		//�Q�[���̎��_�ύX
		CManager::GetGame()->SetGaze(CGame::GAZE_BOMB);
	}
}

//------------------------------------------------------------------------------
//���C���[����
//------------------------------------------------------------------------------
void CModule_No3_LampAndWire::CreateWire()
{
	//���[�J���ϐ��@���C���[��6�{��6�F�o���o��
	Vec<WIRE> wirecol = { WIRE::RED,WIRE::BLUE,WIRE::GREEN ,WIRE::YELLOW,WIRE::WHITE, WIRE::BLACK };

	//�V���b�t��
	CHossoLibrary::Vec_Shuffle(wirecol);

	for(int nCnt = 0;  nCnt < WIRE_NUM; nCnt++)
	{
		m_pWireList.emplace_back(CModule_Parts_Base::Create_ModuleParts<CModule_Parts_No3_Wire>
			(WURE_OFFSET + D3DXVECTOR3(nCnt * WURE_ITNERVAL.x, 0.0f, 0.0f), GetMtxWorldPtr()));

		m_pWireList[m_pWireList.size() - 1]->SetWireCol(wirecol[nCnt]);
	}

}
//------------------------------------------------------------------------------
//�����v����
//------------------------------------------------------------------------------
void CModule_No3_LampAndWire::CreateLamp()
{
	m_nRedLampNum = CHossoLibrary::RandomRangeUnsigned(0, LAMP_NUM);
	m_nBlueLampNum = LAMP_NUM - m_nRedLampNum;


}

//------------------------------------------------------------------------------
//�؂�ׂ����C���[�ݒ�
//------------------------------------------------------------------------------
void CModule_No3_LampAndWire::SetToCutWire()
{
	//�Ԃ������v������ɐ؂�R�[�h�ݒ�
	//�ڍׂ͎d�l���Q�l
	switch (m_nRedLampNum)
	{
	case 4:

		break;

	case 1:

		break;

	case 6:

		break;


		//�r���I�p�^�[��
	default:
		//�����v�̕���������
		if (m_nRedLampNum < m_nBlueLampNum)
		{

		}
		//�ԃ����v��������
		else
		{

		}

		break;
	}


	//�����v���[������ɐ؂�R�[�h�ݒ�


}

//------------------------------------------------------------------------------
//�؂�ׂ����C���[�ݒ� ���C���[�̐F����ɐݒ�
//------------------------------------------------------------------------------
void CModule_No3_LampAndWire::SetCutWire_FromColor(WIRE wire)
{

}

//------------------------------------------------------------------------------
//�؂�ׂ����C���[�ݒ� �ꏊ����ɐݒ�
//------------------------------------------------------------------------------
void CModule_No3_LampAndWire::SetCutWire_FromPlace(int nPlace)
{


}
