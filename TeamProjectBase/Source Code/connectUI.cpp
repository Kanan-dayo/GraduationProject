//=============================================================================
//
// �ڑ���UI���� [ connectUI.cpp ]
// Author : KANAN NAGANAWA
//
//=============================================================================
#include "connectUI.h"
#include "polygon2D.h"
#include "keyboard.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define INTERVAL_ANIM_LOADICON	(10)	// �A�j���[�V���������̊Ԋu
#define NUM_ANIMPATTER_LOADICON	(8)		// ���[�h�A�C�R���̃p�^�[����

#define TIME_FLOW_INTERVAL		(30)	// �t���[�ؑ֎��̃C���^�[�o��

#define FILENAME_UIINFO			("data/TEXT/ConnectUIInfo.txt")	// UI���̃t�@�C��

//=============================================================================
// �ÓI�����o�ϐ��̏�����
//=============================================================================
CPolygon2D *CConnectUI::m_pUIBoth[2][CONNECTUI_BOTH_MAX] = {};
CPolygon2D *CConnectUI::m_pUIOnly[CONNECTUI_ONLY_MAX] = {};

CConnectUI::CONNECTUI_INFO CConnectUI::m_UIInfoBoth[2][CONNECTUI_BOTH_MAX] = {};
CConnectUI::CONNECTUI_INFO CConnectUI::m_UIInfoOnly[CONNECTUI_ONLY_MAX] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CConnectUI::CConnectUI()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CConnectUI::~CConnectUI()
{
	for (int nPlayer = 0; nPlayer < 2; nPlayer++)
	{
		for (int nUI = 0; nUI < CONNECTUI_BOTH_MAX; nUI++)
		{
			if (!m_pUIBoth[nPlayer][nUI])
			{
				continue;
			}
			delete m_pUIBoth[nPlayer][nUI];
			m_pUIBoth[nPlayer][nUI] = nullptr;
		}
	}

	for (int nUI = 0; nUI < CONNECTUI_ONLY_MAX; nUI++)
	{
		if (!m_pUIOnly[nUI])
		{
			continue;
		}
		delete m_pUIOnly[nUI];
		m_pUIOnly[nUI] = nullptr;
	}
}

//=============================================================================
// ����
//=============================================================================
CConnectUI *CConnectUI::Create(void)
{
	// �������m��
	CConnectUI* pUI = new CConnectUI;

	// �m�ێ��s
	if (!pUI)
		return nullptr;

	CConnectUI::Load();

	// ������
	pUI->Init();

	// �l��Ԃ�
	return pUI;
}

//=============================================================================
// ���[�h
//=============================================================================
HRESULT CConnectUI::Load(void)
{
	// �t�@�C������1�s���f�[�^�ǂݍ���
	if (CLoadFile::ReadLineByLineFromFile(FILENAME_UIINFO, ReadFromLine) != CLoadFile::LR_SUCCESS)
	{
#ifdef _DEBUG
		std::cout << "�ڑ����[�h�̃t�@�C���ǂݍ��݂Ɏ��s���܂����B" << std::endl;
#endif
		return E_FAIL;
	}
	return S_OK;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CConnectUI::Init(void)
{
	// �v�f�̏�����
	m_nCntAnim = 0;
	m_nCntPattern = 0;
	m_nCntState = 0;
	m_flow = CONNECTFLOW_CONNECTING;

	// ����
	for (int nPlayer = 0; nPlayer < 2; nPlayer++)
	{
		// �w�i
		m_pUIBoth[nPlayer][CONNECTUI_BOTH_BACK] = CreateBothUI(nPlayer, CONNECTUI_BOTH_BACK);
		// ���[�h�A�C�R��
		m_pUIBoth[nPlayer][CONNECTUI_BOTH_LOADICON] = CreateBothUI(nPlayer, CONNECTUI_BOTH_LOADICON);
		m_pUIBoth[nPlayer][CONNECTUI_BOTH_LOADICON]->SetAnim(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f / NUM_ANIMPATTER_LOADICON, 1.0f));
		// �ڑ���
		m_pUIBoth[nPlayer][CONNECTUI_BOTH_STATE_CONNECTING] = CreateBothUI(nPlayer, CONNECTUI_BOTH_STATE_CONNECTING);
	}

	// �e�N�X�`���̃o�C���h
	m_pUIBoth[0][CONNECTUI_BOTH_BACK]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_BACK_00));
	m_pUIBoth[1][CONNECTUI_BOTH_BACK]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_BACK_01));
	m_pUIBoth[0][CONNECTUI_BOTH_LOADICON]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_LOAD));
	m_pUIBoth[1][CONNECTUI_BOTH_LOADICON]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_LOAD));
	m_pUIBoth[0][CONNECTUI_BOTH_STATE_CONNECTING]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_CONNECTING));
	m_pUIBoth[1][CONNECTUI_BOTH_STATE_CONNECTING]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_CONNECTING));

	return S_OK;
}

//=============================================================================
// �X�V
//=============================================================================
void CConnectUI::Update(void)
{
	switch (m_flow)
	{
		// �ڑ����̏���
	case CONNECTFLOW_CONNECTING:
		Connecting();
		break;
		// �ڑ������̏���
	case CONNECTFLOW_CONNECTED:
		Connected();
		break;
		// ���[�h�̑I������
	case CONNECTFLOW_SELECT_MODE:
		SelectMode();
		break;
	case CONNECTFLOW_SELECT_LEVEL:
		break;
	}

	for (int nPlayer = 0; nPlayer < 2; nPlayer++)
	{
		for (int nUI = 0; nUI < CONNECTUI_BOTH_MAX; nUI++)
		{
			// ���݂��Ȃ��Ȃ�A����
			if (!m_pUIBoth[nPlayer][nUI])
				continue;

			// ���[�h�A�C�R���̃A�j���[�V����
			if (nUI == CONNECTUI_BOTH_LOADICON)
				m_pUIBoth[nPlayer][nUI]->SetAnim(D3DXVECTOR2(0.0f + (1.0f / NUM_ANIMPATTER_LOADICON * m_nCntPattern), 0.0f), D3DXVECTOR2(1.0f / NUM_ANIMPATTER_LOADICON, 1.0f));

			// �X�V
			m_pUIBoth[nPlayer][nUI]->Update();
		}
	}
}

//=============================================================================
// �`��
//=============================================================================
void CConnectUI::Draw(void)
{
	for (int nPlayer = 0; nPlayer < 2; nPlayer++)
	{
		for (int nUI = 0; nUI < CONNECTUI_BOTH_MAX; nUI++)
		{
			if (m_pUIBoth[nPlayer][nUI])
				m_pUIBoth[nPlayer][nUI]->Draw();
		}
	}

	for (int nUI = 0; nUI < CONNECTUI_ONLY_MAX; nUI++)
	{
		if (m_pUIOnly[nUI])
			m_pUIOnly[nUI]->Draw();
	}
}

//=============================================================================
// �ǂݍ��񂾍s�̏�������
//=============================================================================
void CConnectUI::ReadFromLine(CONST_STRING cnpLine, CONST_STRING cnpEntryType, CONST_STRING cnpEntryData)
{
	// 1P2P����UI���ݒ�
	if (strcmp(cnpEntryType, "BothUI") == 0)
	{
		SetBothInfo(cnpLine, cnpEntryData);
	}
	// �P�����g��Ȃ�UI�̏��ݒ�
	else if (strcmp(cnpEntryType, "OnlyUI") == 0)
	{
		SetOnlyInfo(cnpLine, cnpEntryData);
	}
}

//=============================================================================
// 1P2P����UI���
//=============================================================================
void CConnectUI::SetBothInfo(CONST_STRING str, CONST_STRING type)
{
	// UI�̃^�C�v���擾
	int nType = -1;
	sscanf(type, "%d", &nType);

	if (nType <= -1)
		return;

	D3DXVECTOR2 Data = ZeroVector3;
	D3DXCOLOR Col = WhiteColor;

	// �ʒu
	if (sscanf(str, "pos(1P) = %f %f", &Data.x, &Data.y) == 2)
	{
		m_UIInfoBoth[0][nType].pos = Data;
	}
	if (sscanf(str, "pos(2P) = %f %f", &Data.x, &Data.y) == 2)
	{
		m_UIInfoBoth[1][nType].pos = Data;
	}
	// �T�C�Y
	if (sscanf(str, "size(1P) = %f %f", &Data.x, &Data.y) == 2)
	{
		m_UIInfoBoth[0][nType].size = Data;
	}
	if (sscanf(str, "size(2P) = %f %f", &Data.x, &Data.y) == 2)
	{
		m_UIInfoBoth[1][nType].size = Data;
	}

	// �J���[
	if (sscanf(str, "color(1P) = %f %f %f %f", &Col.r, &Col.g, &Col.b, &Col.a) == 4)
	{
		m_UIInfoBoth[0][nType].color = Col;
	}
	if (sscanf(str, "color(2P) = %f %f %f %f", &Col.r, &Col.g, &Col.b, &Col.a) == 4)
	{
		m_UIInfoBoth[1][nType].color = Col;
	}
}

//=============================================================================
// ������g��UI���
//=============================================================================
void CConnectUI::SetOnlyInfo(CONST_STRING str, CONST_STRING type)
{
	// UI�̃^�C�v���擾
	int nType = -1;
	sscanf(type, "%d", &nType);

	if (nType <= -1)
		return;

	D3DXVECTOR2 Data = ZeroVector3;
	D3DXCOLOR Col = WhiteColor;

	// �ʒu
	if (sscanf(str, "pos = %f %f", &Data.x, &Data.y) == 2)
	{
		m_UIInfoOnly[nType].pos = Data;
	}
	// �T�C�Y
	if (sscanf(str, "size = %f %f", &Data.x, &Data.y) == 2)
	{
		m_UIInfoOnly[nType].size = Data;
	}
	// �J���[
	if (sscanf(str, "color = %f %f %f %f", &Col.r, &Col.g, &Col.b, &Col.a) == 4)
	{
		m_UIInfoOnly[nType].color = Col;
	}
}

//=============================================================================
// 1P2P���Ɏg��UI����
//=============================================================================
CPolygon2D * CConnectUI::CreateBothUI(int nPlayer, CONNECTUITYPE_BOTH type)
{
	// ����
	CPolygon2D *pPolygon = CPolygon2D::Create();

	// ���ݒ�
	pPolygon->SetPos(m_UIInfoBoth[nPlayer][type].pos);
	pPolygon->SetSize(m_UIInfoBoth[nPlayer][type].size);
	pPolygon->SetPosStart(CPolygon2D::POSSTART_CENTRAL_CENTRAL);
	pPolygon->SetCol(m_UIInfoBoth[nPlayer][type].color);
	
	// �l��Ԃ�
	return pPolygon;
}

//=============================================================================
// ������g��UI����
//=============================================================================
CPolygon2D * CConnectUI::CreateOnlyUI(CONNECTUITYPE_ONLY type)
{
	// ����
	CPolygon2D *pPolygon = CPolygon2D::Create();

	// ���ݒ�
	pPolygon->SetPos(m_UIInfoOnly[type].pos);
	pPolygon->SetSize(m_UIInfoOnly[type].size);
	pPolygon->SetPosStart(CPolygon2D::POSSTART_CENTRAL_CENTRAL);
	pPolygon->SetCol(m_UIInfoOnly[type].color);

	// �l��Ԃ�
	return pPolygon;
}

//=============================================================================
// �ڑ����̏���
//=============================================================================
void CConnectUI::Connecting(void)
{
	// �i���j �ڑ�����
	if (CManager::GetKeyboard()->GetTrigger(DIK_1))
		ConnectPlayer(0);
	if (CManager::GetKeyboard()->GetTrigger(DIK_2))
		ConnectPlayer(1);

	// ���[�h�A�C�R���̃A�j���[�V����
	Anim();
}

//=============================================================================
// �v���C���[���ڑ������Ƃ��̏���
//=============================================================================
void CConnectUI::ConnectPlayer(int nPlayer)
{
	// �ēx�������Ȃ��悤��������
	if (m_pUIBoth[nPlayer][CONNECTUI_BOTH_STATE_CONNECTED])
		return;

	// ������UI�̔j��
	if (m_pUIBoth[nPlayer][CONNECTUI_BOTH_LOADICON])
	{
		delete m_pUIBoth[nPlayer][CONNECTUI_BOTH_LOADICON];
		m_pUIBoth[nPlayer][CONNECTUI_BOTH_LOADICON] = nullptr;
	}
	if (m_pUIBoth[nPlayer][CONNECTUI_BOTH_STATE_CONNECTING])
	{
		delete m_pUIBoth[nPlayer][CONNECTUI_BOTH_STATE_CONNECTING];
		m_pUIBoth[nPlayer][CONNECTUI_BOTH_STATE_CONNECTING] = nullptr;
	}

	// �ڑ������𐶐�
	m_pUIBoth[nPlayer][CONNECTUI_BOTH_STATE_CONNECTED] = CreateBothUI(nPlayer, CONNECTUI_BOTH_STATE_CONNECTED);
	m_pUIBoth[nPlayer][CONNECTUI_BOTH_STATE_CONNECTED]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_CONNECTED));

	// ���҂Ƃ��ڑ��o������A�t���[������
	if (nPlayer == 0 && m_pUIBoth[1][CONNECTUI_BOTH_STATE_CONNECTED])
		m_flow = CONNECTFLOW_CONNECTED;
	else if (nPlayer == 1 && m_pUIBoth[0][CONNECTUI_BOTH_STATE_CONNECTED])
		m_flow = CONNECTFLOW_CONNECTED;
}

//=============================================================================
// �ڑ������̏���
//=============================================================================
void CConnectUI::Connected(void)
{
	// ��ԃJ�E���^�����Z
	m_nCntState++;

	// ���ԂłȂ���΁A�������I����
	if (m_nCntState < TIME_FLOW_INTERVAL)
		return;

	// �ڑ�������UI��j��
	if (m_pUIBoth[0][CONNECTUI_BOTH_STATE_CONNECTED])
	{
		delete m_pUIBoth[0][CONNECTUI_BOTH_STATE_CONNECTED];
		m_pUIBoth[0][CONNECTUI_BOTH_STATE_CONNECTED] = nullptr;
	}
	if (m_pUIBoth[1][CONNECTUI_BOTH_STATE_CONNECTED])
	{
		delete m_pUIBoth[1][CONNECTUI_BOTH_STATE_CONNECTED];
		m_pUIBoth[1][CONNECTUI_BOTH_STATE_CONNECTED] = nullptr;
	}

	// ���̃t���[��
	m_flow = CONNECTFLOW_SELECT_MODE;
	m_nCntState = 0;
}

//=============================================================================
// ���[�h�̑I������
//=============================================================================
void CConnectUI::SelectMode(void)
{
	// UI�̐���
	if (!m_pUIBoth[0][CONNECTUI_BOTH_SELECT_MODE])
	{
		m_pUIBoth[0][CONNECTUI_BOTH_SELECT_MODE] = CreateBothUI(0, CONNECTUI_BOTH_SELECT_MODE);
		m_pUIBoth[0][CONNECTUI_BOTH_SELECT_MODE]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_SELECT_MODE));
	}
	if (!m_pUIBoth[0][CONNECTUI_BOTH_MODE_REMOVE])
	{
		m_pUIBoth[0][CONNECTUI_BOTH_MODE_REMOVE] = CreateBothUI(0, CONNECTUI_BOTH_MODE_REMOVE);
		m_pUIBoth[0][CONNECTUI_BOTH_MODE_REMOVE]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_SELECT_REMOVE));
	}
	if (!m_pUIBoth[0][CONNECTUI_BOTH_MODE_SOLVE])
	{
		m_pUIBoth[0][CONNECTUI_BOTH_MODE_SOLVE] = CreateBothUI(0, CONNECTUI_BOTH_MODE_SOLVE);
		m_pUIBoth[0][CONNECTUI_BOTH_MODE_SOLVE]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_SLECT_SOLVE));
	}

	// �Q�X�g��UI
	if (!m_pUIBoth[1][CONNECTUI_BOTH_STATE_SELECTING])
	{
		m_pUIBoth[1][CONNECTUI_BOTH_STATE_SELECTING] = CreateBothUI(1, CONNECTUI_BOTH_STATE_SELECTING);
		m_pUIBoth[1][CONNECTUI_BOTH_STATE_SELECTING]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_GUEST_SELECTING));
	}
}

//=============================================================================
// �A�j���[�V����
//=============================================================================
void CConnectUI::Anim(void)
{
	if (m_pUIBoth[0][CONNECTUI_BOTH_LOADICON])
		UpdateCntAnim();
	else if (m_pUIBoth[1][CONNECTUI_BOTH_LOADICON])
		UpdateCntAnim();
}

//=============================================================================
// �A�j���[�V�����J�E���^�̍X�V
//=============================================================================
void CConnectUI::UpdateCntAnim(void)
{
	// ���ԂłȂ��Ȃ�A�������I����
	m_nCntAnim++;
	if (m_nCntAnim < INTERVAL_ANIM_LOADICON)
		return;

	// ���t���[�������ɃA�j���[�V����
	m_nCntPattern++;
	if (m_nCntPattern >= NUM_ANIMPATTER_LOADICON)
		m_nCntPattern = 0;
	m_nCntAnim = 0;
}
