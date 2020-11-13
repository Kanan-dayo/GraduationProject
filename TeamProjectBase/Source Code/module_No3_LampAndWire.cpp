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
#include "particle.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define WURE_OFFSET					(D3DXVECTOR3(-37.0f,0.0f,-23.0f))
#define WURE_ITNERVAL				(D3DXVECTOR3(12.0f,0.0f,0.0f))
#define WIRE_NUM					(6)
#define LAMP_OFFSET					(D3DXVECTOR3(-28.0f,-5.0f,-30.0f))
#define LAMP_INTERVAL				(D3DXVECTOR3(9.0f,0.0f,0.0f))
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

	//���W���[�����̃����v����
	CreateModuleLamp();

	//�N���A�����v����
	CModule_Base::CreateLamp();

	//�J�b�g���郏�C���[�ݒ�
	SetToCutWire();

	//������
	CSceneX::Init();

	return S_OK;
}

//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CModule_No3_LampAndWire::Update()
{
	D3DXVECTOR3 posorigin = CHossoLibrary::CalcMtxToVector3(*GetMtxWorldPtr());

	for (int nCnt = 0; nCnt < LAMP_NUM; nCnt++)
	{
		if (nCnt < m_nRedLampNum)
		{
			CParticle::CreateFromText(posorigin + LAMP_OFFSET + D3DXVECTOR3(LAMP_INTERVAL.x * nCnt, 0.0f, 0.0f), ZeroVector3, CParticleParam::EFFECT_MODULE_3_LED,RedColor);
		}
		else
		{
			CParticle::CreateFromText(posorigin + LAMP_OFFSET + D3DXVECTOR3(LAMP_INTERVAL.x * nCnt, 0.0f, 0.0f), ZeroVector3, CParticleParam::EFFECT_MODULE_3_LED,BlueColor);
		}
	}

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

	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		//nullcheck
		if (m_pWireList[m_nSelectPlace].get())
		{
			//���C���[�J�b�g����ĂȂ���
			if (!m_pWireList[m_nSelectPlace]->GetWireCut())
			{
				//�ԈႦ�����C���[��������
				if (!m_pWireList[m_nSelectPlace]->GetClearFlag())
				{
					//���s
					Module_Failed();
				}

				//���C���[�J�b�g
				WireCut();

				//�N���A�������`�F�b�N
				CheckClear();
			}
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


	CDebugProc::Print(CDebugProc::PLACE_LEFT, "-------------Module_No_3----------------\n");
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "RedLampNum >> [%d]\n", m_nRedLampNum);
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "BlueLampNum >> [%d]\n", m_nBlueLampNum);
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "Flag >>> [%d]  [%d]  [%d]  [%d]  [%d]  [%d]\n",
		m_pWireList[0]->GetClearFlag(), m_pWireList[1]->GetClearFlag(), m_pWireList[2]->GetClearFlag(),
		m_pWireList[3]->GetClearFlag(), m_pWireList[4]->GetClearFlag(), m_pWireList[5]->GetClearFlag());

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

		m_pWireList[m_pWireList.size() - 1]->SetWire(wirecol[nCnt]);
	}

}
//------------------------------------------------------------------------------
//�����v����
//------------------------------------------------------------------------------
void CModule_No3_LampAndWire::CreateModuleLamp()
{
	//�Ԃ������v�������_���ݒ�
	m_nRedLampNum = CHossoLibrary::RandomRangeUnsigned(0, LAMP_NUM);

	//�Ԃ������v������t�Z���Đ������v�ݒ�
	m_nBlueLampNum = LAMP_NUM - m_nRedLampNum;




}

//------------------------------------------------------------------------------
//�؂�ׂ����C���[�ݒ�
//------------------------------------------------------------------------------
void CModule_No3_LampAndWire::SetToCutWire()
{
	auto Itr_Begin = m_pWireList.begin();
	auto Itr_End = m_pWireList.end();

	//�Ԃ������v������ɐ؂�R�[�h�ݒ�
	//�ڍׂ͎d�l���Q�l
	switch (m_nRedLampNum)
	{
	case 4:
		SetCutWire_FromColor(WIRE::BLACK, Itr_Begin, Itr_End, true, false, true, true);		//���̗���
		SetCutWire_FromColor(WIRE::YELLOW, Itr_Begin, Itr_End, true, false, true, false);	//���̍�
		SetCutWire_FromColor(WIRE::RED, Itr_Begin, Itr_End, true, false, false, true);		//�Ԃ̉E
		SetCutWire_FromPlace(3);															//������4�Ԗ�

		break;

	case 1:
		SetCutWire_FromColor(WIRE::GREEN, Itr_Begin, Itr_End, true, false, true, true);		//�΂̗���
		SetCutWire_FromColor(WIRE::WHITE, Itr_Begin, Itr_End, true, false, true, true);		//���̗���
		SetCutWire_FromPlace(4);															//�E����2�Ԗ�
		SetCutWire_FromPlace(0);															//���[
		SetCutWire_FromPlace(5);															//�E�[

		break;

	case 2:
		SetCutWire_FromColor(WIRE::WHITE, Itr_Begin, Itr_End, true, false, true, true);				//���̗���
		SetCutWire_FromColor(WIRE::YELLOW, Itr_Begin, Itr_End, true, false, false, true);			//���̉E
		SetCutWire_FromPlace(4);																	//������5�Ԗ�
		break;


		//�r���I�p�^�[��
	default:
		//�����v��������
		if (m_nRedLampNum < m_nBlueLampNum)
		{
			SetCutWire_FromColor(WIRE::GREEN, Itr_Begin, Itr_End, true, true, true, true);			//�΂Ɨ΂̗���
			SetCutWire_FromColor(WIRE::BLUE, Itr_Begin, Itr_End, true);								//�̗���
			SetCutWire_FromPlace(2);																//������3�Ԗ�
		}
		//�ԃ����v��������
		else
		{
			SetCutWire_FromColor(WIRE::WHITE, Itr_Begin, Itr_End, true);							//��
			SetCutWire_FromColor(WIRE::YELLOW, Itr_Begin, Itr_End, true);							//��
			SetCutWire_FromColor(WIRE::RED, Itr_Begin, Itr_End, true, false, true, true);			//�Ԃ̗���
			SetCutWire_FromPlace(1);																//�E����5�Ԗ�

		}

		break;
	}


	//�����v���[������ɐ؂�R�[�h�ݒ�
	SetCutWire_FromLampRule();

}

//------------------------------------------------------------------------------
//�؂�ׂ����C���[�ݒ�
//------------------------------------------------------------------------------
void CModule_No3_LampAndWire::WireCut()
{
	m_pWireList[m_nSelectPlace]->SetWireCut(true);
	m_pWireList[m_nSelectPlace]->BindModelInfo(CModelInfo::GetModelInfo(CModelInfo::MODEL_MODULEPARTS_NO1_KEYPAD));
	m_pWireList[m_nSelectPlace]->SetClearFlag(false);

}

//------------------------------------------------------------------------------
//�؂�ׂ����C���[�ݒ�
//------------------------------------------------------------------------------
void CModule_No3_LampAndWire::CheckClear()
{
	int nCount = std::count_if(m_pWireList.begin(), m_pWireList.end(),
		[](S_ptr<CModule_Parts_No3_Wire> ptr) {return ptr->GetClearFlag(); });

	if (nCount <= 0)
	{
		Module_Clear();
	}
}

//------------------------------------------------------------------------------
//�؂�ׂ����C���[�ݒ� �ꏊ����ɐݒ�
//------------------------------------------------------------------------------
void CModule_No3_LampAndWire::SetCutWire_FromPlace(int nPlace)
{
	if (nPlace < WIRE_NUM)
	{
		m_pWireList[nPlace] -> SetClearFlag(true);
	}
}

//------------------------------------------------------------------------------
//�؂�ׂ����C���[�ݒ� �����v���[������ɐݒ�
//------------------------------------------------------------------------------
void CModule_No3_LampAndWire::SetCutWire_FromLampRule()
{
	auto Itr_Begin = m_pWireList.begin();
	auto Itr_End = m_pWireList.end();

	//�����v3�ȏ�
	if (m_nBlueLampNum >= 3)
	{
		SetCutWire_FromColor(WIRE::BLUE, Itr_Begin, Itr_End, false);				//��؂�Ȃ�

		//�����v5�ȏ�
		if (m_nBlueLampNum >= 5)
		{
			SetCutWire_FromColor(WIRE::RED, Itr_Begin, Itr_End, true);				//�Ԃ�؂�

			//�S�������v
			if (m_nBlueLampNum >= LAMP_NUM)
			{
				SetCutWire_FromColor(WIRE::WHITE, Itr_Begin, Itr_End, true);		//����؂�
				SetCutWire_FromColor(WIRE::BLACK, Itr_Begin, Itr_End, true);		//����؂�

			}
		}
	}

	//�ԃ����v3�ȏ�
	if (m_nRedLampNum >= 3)
	{
		SetCutWire_FromColor(WIRE::BLACK, Itr_Begin, Itr_End, false);				//����؂�Ȃ�

		//�ԃ����v5�ȏ�
		if (m_nRedLampNum >= 5)
		{
			SetCutWire_FromColor(WIRE::GREEN, Itr_Begin, Itr_End, true);			//����؂�

			//�S���ԃ����v
			if (m_nRedLampNum >= LAMP_NUM)
			{
				SetCutWire_FromColor(WIRE::RED, Itr_Begin, Itr_End, true);			//�Ԃ�؂�
				SetCutWire_FromColor(WIRE::BLUE, Itr_Begin, Itr_End, true);			//��؂�
			}
		}
	}



}
