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
#include "client.h"
#include "mouse.h"
#include "renderer.h"
#include "fade.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define INTERVAL_ANIM_LOADICON	(10)	// �A�j���[�V���������̊Ԋu
#define NUM_ANIMPATTER_LOADICON	(8)		// ���[�h�A�C�R���̃p�^�[����

#define TIME_FLOW_INTERVAL		(30)	// �t���[�ؑ֎��̃C���^�[�o��
#define TIME_ALPHA_COMMENT		(10)	// �R�����g�𓧉߂�����܂ł̎���

#define FILENAME_UIINFO			("data/TEXT/ConnectUIInfo.txt")	// UI���̃t�@�C��
#define UV_BUTTON				(D3DXVECTOR2(1.0f, 1.0f / 3))	// �{�^����UV�ݒ�p

//=============================================================================
// �ÓI�����o�ϐ��̏�����
//=============================================================================
CPolygon2D *CConnectUI::m_pUIBoth[2][CONNECTUI_BOTH_MAX] = {};
CPolygon2D *CConnectUI::m_pUIOnly[CONNECTUI_ONLY_MAX] = {};

CConnectUI::CONNECTUI_INFO CConnectUI::m_UIInfoBoth[2][CONNECTUI_BOTH_MAX] = {};
CConnectUI::CONNECTUI_INFO CConnectUI::m_UIInfoOnly[CONNECTUI_ONLY_MAX] = {};
CConnectUI::CONNECTFLOW_TYPE CConnectUI::m_flow = CONNECTFLOW_CONNECTING;
int CConnectUI::m_nSelectMode[PLAYER_MAX] = {};
int CConnectUI::m_nSelectLevel[PLAYER_MAX] = {};
bool CConnectUI::m_bGuestWait = false;

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
	m_state = FLOWSTATE_BEGIN;
	m_bGuestWait = false;

	for (int nPlayer = 0; nPlayer < PLAYER_MAX; nPlayer++)
	{
		m_bConnect[nPlayer] = false;
		m_nSelectMode[PLAYER_TWO] = SELECTMODE_NONE;
		m_nSelectLevel[PLAYER_ONE] = SELECTLEVEL_NONE;
	}

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
		SelectLevel();
		break;
	}

	for (int nPlayer = 0; nPlayer < 2; nPlayer++)
	{
		for (int nUI = 0; nUI < CONNECTUI_BOTH_MAX; nUI++)
		{
			if (m_pUIBoth[nPlayer][nUI])
				m_pUIBoth[nPlayer][nUI]->Update();
		}
	}

	for (int nUI = 0; nUI < CONNECTUI_ONLY_MAX; nUI++)
	{
		if (m_pUIOnly[nUI])
			m_pUIOnly[nUI]->Update();
	}


	//�t�F�[�h���ĂȂ���
	if (CManager::GetRenderer()->GetFade()->GetFadeState() == CFade::FADE_NONE)
	{
		if (m_flow == CONNECTFLOW_END)
		{
			//�X�e�[�g�ύX
			if (m_nSelectMode[PLAYER_ONE] == SELECTMODE_REMOVE)
				CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_GAME);
			else if (m_nSelectMode[PLAYER_ONE] == SELECTMODE_SOLVE)
				CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_DECODING);
		}
#ifdef _DEBUG
		if (CManager::GetKeyboard()->GetPress(DIK_LSHIFT) && CManager::GetKeyboard()->GetPress(DIK_RETURN))
		{
			//�X�e�[�g�ύX
			if (m_nSelectMode[PLAYER_ONE] == SELECTMODE_REMOVE)
				CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_GAME);
			else if (m_nSelectMode[PLAYER_ONE] == SELECTMODE_SOLVE)
				CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_DECODING);
		}
#endif
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

	// �{�^����UI��UV���W��ݒ肷��
	if (type == CONNECTUI_BOTH_MODE_REMOVE ||
		type == CONNECTUI_BOTH_MODE_SOLVE ||
		type == CONNECTUI_BOTH_LEVEL_EASY ||
		type == CONNECTUI_BOTH_LEVEL_NORMAL ||
		type == CONNECTUI_BOTH_LEVEL_HARD)
	{
		pPolygon->SetAnim(ZeroVector2, D3DXVECTOR2(1.0f, 1.0f / 3));
	}
	
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

	// �{�^����UI��UV���W��ݒ肷��
	if (type == CONNECTUI_ONLY_BUTTON_DESIDE)
	{
		pPolygon->SetAnim(ZeroVector2, D3DXVECTOR2(1.0f, 1.0f / 3));
	}

	// �l��Ԃ�
	return pPolygon;
}

//=============================================================================
// UI�j��
//=============================================================================
void CConnectUI::DeleteBothUI(int nPlayer, CONNECTUITYPE_BOTH type)
{
	delete m_pUIBoth[nPlayer][type];
	m_pUIBoth[nPlayer][type] = nullptr;
}

void CConnectUI::DeleteOnlyUI(CONNECTUITYPE_ONLY type)
{
	delete m_pUIOnly[type];
	m_pUIOnly[type] = nullptr;
}

//=============================================================================
// �ڑ����̏���
//=============================================================================
void CConnectUI::Connecting(void)
{
	if (FLOWSTATE_BEGIN == m_state)
	{
		// �t���[�J�n
		Begin(CONNECTFLOW_CONNECTING);
		return;
	}
	if (FLOWSTATE_END == m_state)
	{
		// �t���[�I��
		End(CONNECTFLOW_CONNECTING);
		return;
	}

#ifdef _DEBUG
	// �蓮�ŃQ�X�g�̐ڑ�����
	if (CManager::GetKeyboard()->GetPress(DIK_LSHIFT))
	{
		if (CManager::GetKeyboard()->GetTrigger(DIK_1))
			m_bConnect[PLAYER_ONE] = true;
		if (CManager::GetKeyboard()->GetTrigger(DIK_2))
			m_bConnect[PLAYER_TWO] = true;
	}
#endif

	// �ڑ�����Ă��邩�m�F
	CheckConnect();

	// ���Ґڑ��ł��Ă���΁A�t���[�̏I��
	if (m_bConnect[PLAYER_ONE] && m_bConnect[PLAYER_TWO])
		m_state = FLOWSTATE_END;

	// ���[�h�A�C�R���̃A�j���[�V����
	LoadIconAnim();
	return;
}

//=============================================================================
// �ڑ����ꂽ���m�F
//=============================================================================
void CConnectUI::CheckConnect(void)
{
	for (int nPlayer = 0; nPlayer < PLAYER_MAX; nPlayer++)
	{
		// �ڑ����Ă��Ȃ���΁A�ڑ��󋵂��擾
		if (!m_bConnect[nPlayer])
		{
			nPlayer == PLAYER_ONE ?
				m_bConnect[PLAYER_ONE] = CClient::GetAccept() :
				m_bConnect[PLAYER_TWO] = CClient::GetAcceptOther();
		}

		// [�ڑ�����Ă��Ȃ�] [ UI���\������Ă���] �Ȃ�A�������Ȃ�
		if (!m_bConnect[nPlayer] || m_pUIBoth[nPlayer][CONNECTUI_BOTH_STATE_CONNECTED])
			continue;

		// ���[�h�A�C�R���E�ڑ�����UI��j��
		if (m_pUIBoth[nPlayer][CONNECTUI_BOTH_LOADICON])
			DeleteBothUI(nPlayer, CONNECTUI_BOTH_LOADICON);
		if (m_pUIBoth[nPlayer][CONNECTUI_BOTH_STATE_CONNECTING])
			DeleteBothUI(nPlayer, CONNECTUI_BOTH_STATE_CONNECTING);


		// �ڑ�����UI�𐶐�
		m_pUIBoth[nPlayer][CONNECTUI_BOTH_STATE_CONNECTED] = CreateBothUI(nPlayer, CONNECTUI_BOTH_STATE_CONNECTED);
		m_pUIBoth[nPlayer][CONNECTUI_BOTH_STATE_CONNECTED]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_CONNECTED));
	}
}

//=============================================================================
// �ڑ������̏���
//=============================================================================
void CConnectUI::Connected(void)
{
	if (FLOWSTATE_BEGIN == m_state)
	{
		// ���ʏ��
		m_state = FLOWSTATE_NORMAL;
		return;
	}
	if (FLOWSTATE_END == m_state)
	{
		// �t���[�I��
		End(CONNECTFLOW_CONNECTED);
		return;
	}

	// ��ԃJ�E���^�����Z
	m_nCntState++;

	// ���ԂŏI��
	if (m_nCntState >= TIME_FLOW_INTERVAL)
		m_state = FLOWSTATE_END;
}

//=============================================================================
// ���[�h�̑I������
//=============================================================================
void CConnectUI::SelectMode(void)
{
	if (FLOWSTATE_BEGIN == m_state)
	{
		// �t���[�J�n
		Begin(CONNECTFLOW_SELECT_MODE);
		return;
	}
	if (FLOWSTATE_END == m_state)
	{
		End(CONNECTFLOW_SELECT_MODE);
		return;
	}
	if (FLOWSTATE_WAIT == m_state)
	{
		Wait(CONNECTFLOW_SELECT_MODE);
		return;
	}

#ifdef _DEBUG
	// �蓮�ŃQ�X�g�̃��[�h�ݒ�
	if (CManager::GetKeyboard()->GetPress(DIK_LSHIFT))
	{
		if (CManager::GetKeyboard()->GetTrigger(DIK_1))
			SetGuestMode(SELECTMODE_REMOVE);
		else if (CManager::GetKeyboard()->GetTrigger(DIK_2))
			SetGuestMode(SELECTMODE_SOLVE);
	}
#endif

	// �{�^���̃A�j���[�V����
	ButtonAnim();

	// �}�E�X�̃|�C���^�擾
	CMouse *pMouse = CManager::GetMouse();
	// �}�E�X���W���擾
	D3DXVECTOR2 mousePos = pMouse->GetMousePos();

	// �J�[�\���ʒu��UI�Əd�Ȃ��Ă���
	if (m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_MODE_REMOVE]->ReturnHit(mousePos))
	{
		// �i�X�\��
		D3DXCOLOR col = m_pUIOnly[CONNECTUI_ONLY_COMMENT_REMOVE]->GetCol();
		if (col.a < 1.0f)
			m_pUIOnly[CONNECTUI_ONLY_COMMENT_REMOVE]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a + (1.0f / TIME_ALPHA_COMMENT)));

		// �N���b�N���ĂȂ���΁A�������Ȃ�
		if (pMouse->GetPress(0))
		{
			// �A�j���[�V������ݒ�
			m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_MODE_REMOVE]->SetAnim(D3DXVECTOR2(0.0f, 1.0f / 3), UV_BUTTON);
			m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_MODE_SOLVE]->SetAnim(D3DXVECTOR2(0.0f, 0.0f), UV_BUTTON);
			m_nSelectMode[PLAYER_ONE] = SELECTMODE_REMOVE;
		}
	}
	else
	{
		// �i�X������
		D3DXCOLOR col = m_pUIOnly[CONNECTUI_ONLY_COMMENT_REMOVE]->GetCol();
		if (col.a > 0.0f)
			m_pUIOnly[CONNECTUI_ONLY_COMMENT_REMOVE]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a - (1.0f / TIME_ALPHA_COMMENT)));
	}

	// �}�E�X�J�[�\����UI���d�Ȃ��Ă���
	if (m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_MODE_SOLVE]->ReturnHit(mousePos))
	{
		// �i�X�\��
		D3DXCOLOR col = m_pUIOnly[CONNECTUI_ONLY_COMMENT_SOLVE]->GetCol();
		if (col.a < 1.0f)
			m_pUIOnly[CONNECTUI_ONLY_COMMENT_SOLVE]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a + (1.0f / TIME_ALPHA_COMMENT)));

		// �N���b�N���ĂȂ���΁A�������Ȃ�
		if (pMouse->GetPress(0))
		{
			m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_MODE_SOLVE]->SetAnim(D3DXVECTOR2(0.0f, 1.0f / 3), UV_BUTTON);
			m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_MODE_REMOVE]->SetAnim(D3DXVECTOR2(0.0f, 0.0f), UV_BUTTON);
			m_nSelectMode[PLAYER_ONE] = SELECTMODE_SOLVE;
		}
	}
	else
	{
		// �i�X������
		D3DXCOLOR col = m_pUIOnly[CONNECTUI_ONLY_COMMENT_SOLVE]->GetCol();
		if (col.a > 0.0f)
			m_pUIOnly[CONNECTUI_ONLY_COMMENT_SOLVE]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a - (1.0f / TIME_ALPHA_COMMENT)));
	}

	// �������[�h��I�����Ă��Ȃ����m�F
	CheckSameMode();

	// ����{�^��������΁A�N���b�N�̊m�F
	if (m_pUIOnly[CONNECTUI_ONLY_BUTTON_DESIDE])
		ClickDecide(pMouse);
}

//=============================================================================
// ���x���̑I������
//=============================================================================
void CConnectUI::SelectLevel(void)
{
	if (FLOWSTATE_BEGIN == m_state)
	{
		Begin(CONNECTFLOW_SELECT_LEVEL);
		return;
	}
	if (FLOWSTATE_END == m_state)
	{
		End(CONNECTFLOW_SELECT_LEVEL);
		return;
	}
	if (FLOWSTATE_WAIT == m_state)
	{
		Wait(CONNECTFLOW_SELECT_LEVEL);
		return;
	}

	// �}�E�X�̃|�C���^�擾
	CMouse *pMouse = CManager::GetMouse();
	// �}�E�X���W���擾
	D3DXVECTOR2 mousePos = pMouse->GetMousePos();

	if (m_nSelectMode[PLAYER_ONE] == SELECTMODE_REMOVE)
	{
		// �{�^���̃A�j���[�V����
		ButtonAnim();

		// �J�[�\���ʒu��UI�Əd�Ȃ��Ă���
		if (m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_EASY]->ReturnHit(mousePos))
		{
			// �i�X�\��
			D3DXCOLOR col = m_pUIOnly[CONNECTUI_ONLY_COMMENT_EASY]->GetCol();
			if (col.a < 1.0f)
				m_pUIOnly[CONNECTUI_ONLY_COMMENT_EASY]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a + (1.0f / TIME_ALPHA_COMMENT)));

			// �N���b�N���ĂȂ���΁A�������Ȃ�
			if (pMouse->GetPress(0))
			{
				// �A�j���[�V������ݒ�
				m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_EASY]->SetAnim(D3DXVECTOR2(0.0f, 1.0f / 3), UV_BUTTON);
				m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_NORMAL]->SetAnim(D3DXVECTOR2(0.0f, 0.0f), UV_BUTTON);
				m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_HARD]->SetAnim(D3DXVECTOR2(0.0f, 0.0f), UV_BUTTON);
				m_nSelectLevel[PLAYER_ONE] = SELECTLEVEL_EASY;
			}
		}
		else
		{
			// �i�X������
			D3DXCOLOR col = m_pUIOnly[CONNECTUI_ONLY_COMMENT_EASY]->GetCol();
			if (col.a > 0.0f)
				m_pUIOnly[CONNECTUI_ONLY_COMMENT_EASY]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a - (1.0f / TIME_ALPHA_COMMENT)));
		}

		// �}�E�X�J�[�\����UI���d�Ȃ��Ă���
		if (m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_NORMAL]->ReturnHit(mousePos))
		{
			// �i�X�\��
			D3DXCOLOR col = m_pUIOnly[CONNECTUI_ONLY_COMMENT_NORMAL]->GetCol();
			if (col.a < 1.0f)
				m_pUIOnly[CONNECTUI_ONLY_COMMENT_NORMAL]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a + (1.0f / TIME_ALPHA_COMMENT)));

			// �N���b�N���ĂȂ���΁A�������Ȃ�
			if (pMouse->GetPress(0))
			{
				m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_NORMAL]->SetAnim(D3DXVECTOR2(0.0f, 1.0f / 3), UV_BUTTON);
				m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_EASY]->SetAnim(D3DXVECTOR2(0.0f, 0.0f), UV_BUTTON);
				m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_HARD]->SetAnim(D3DXVECTOR2(0.0f, 0.0f), UV_BUTTON);
				m_nSelectLevel[PLAYER_ONE] = SELECTLEVEL_NORMAL;
			}
		}
		else
		{
			// �i�X������
			D3DXCOLOR col = m_pUIOnly[CONNECTUI_ONLY_COMMENT_NORMAL]->GetCol();
			if (col.a > 0.0f)
				m_pUIOnly[CONNECTUI_ONLY_COMMENT_NORMAL]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a - (1.0f / TIME_ALPHA_COMMENT)));
		}

		// �}�E�X�J�[�\����UI���d�Ȃ��Ă���
		if (m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_HARD]->ReturnHit(mousePos))
		{
			// �i�X�\��
			D3DXCOLOR col = m_pUIOnly[CONNECTUI_ONLY_COMMENT_HARD]->GetCol();
			if (col.a < 1.0f)
				m_pUIOnly[CONNECTUI_ONLY_COMMENT_HARD]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a + (1.0f / TIME_ALPHA_COMMENT)));

			// �N���b�N���ĂȂ���΁A�������Ȃ�
			if (pMouse->GetPress(0))
			{
				m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_HARD]->SetAnim(D3DXVECTOR2(0.0f, 1.0f / 3), UV_BUTTON);
				m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_EASY]->SetAnim(D3DXVECTOR2(0.0f, 0.0f), UV_BUTTON);
				m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_NORMAL]->SetAnim(D3DXVECTOR2(0.0f, 0.0f), UV_BUTTON);
				m_nSelectLevel[PLAYER_ONE] = SELECTLEVEL_HARD;
			}
		}
		else
		{
			// �i�X������
			D3DXCOLOR col = m_pUIOnly[CONNECTUI_ONLY_COMMENT_HARD]->GetCol();
			if (col.a > 0.0f)
				m_pUIOnly[CONNECTUI_ONLY_COMMENT_HARD]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a - (1.0f / TIME_ALPHA_COMMENT)));
		}

		if (!m_pUIOnly[CONNECTUI_ONLY_BUTTON_DESIDE])
		{
			if (m_nSelectLevel[PLAYER_ONE])
			{
				// ����{�^���𐶐�
				m_pUIOnly[CONNECTUI_ONLY_BUTTON_DESIDE] = CreateOnlyUI(CONNECTUI_ONLY_BUTTON_DESIDE);
				m_pUIOnly[CONNECTUI_ONLY_BUTTON_DESIDE]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_DECIDE));
				m_pUIOnly[CONNECTUI_ONLY_BUTTON_DESIDE]->SetAnim(D3DXVECTOR2(0.0f, 0.0f), UV_BUTTON);

				// ���ӏ�����j��
				if (m_pUIOnly[CONNECTUI_ONLY_CAUTION_LEVEL])
					DeleteOnlyUI(CONNECTUI_ONLY_CAUTION_LEVEL);
			}
		}
	}
	else
	{
#ifdef _DEBUG
		// �蓮�ŃQ�X�g�̃��[�h�ݒ�
		if (CManager::GetKeyboard()->GetPress(DIK_LSHIFT))
		{
			if (CManager::GetKeyboard()->GetTrigger(DIK_1))
				SetGuestLevel(SELECTLEVEL_EASY);
			else if (CManager::GetKeyboard()->GetTrigger(DIK_2))
				SetGuestLevel(SELECTLEVEL_NORMAL);
			else if (CManager::GetKeyboard()->GetTrigger(DIK_3))
				SetGuestLevel(SELECTLEVEL_HARD);
		}
#endif
		if (!m_pUIOnly[CONNECTUI_ONLY_BUTTON_DESIDE])
		{
			// ����{�^���𐶐�
			if (m_nSelectLevel[PLAYER_TWO] != SELECTLEVEL_NONE)
			{
				m_pUIOnly[CONNECTUI_ONLY_BUTTON_DESIDE] = CreateOnlyUI(CONNECTUI_ONLY_BUTTON_DESIDE);
				m_pUIOnly[CONNECTUI_ONLY_BUTTON_DESIDE]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_DECIDE));
				m_pUIOnly[CONNECTUI_ONLY_BUTTON_DESIDE]->SetAnim(D3DXVECTOR2(0.0f, 0.0f), UV_BUTTON);
			}

			// ����{�^����j��
			if (m_pUIOnly[CONNECTUI_ONLY_CAUTION_LEVEL])
				DeleteOnlyUI(CONNECTUI_ONLY_CAUTION_LEVEL);
		}
	}

	// ����{�^��������΁A�N���b�N�̊m�F
	if (m_pUIOnly[CONNECTUI_ONLY_BUTTON_DESIDE])
		ClickDecide(pMouse);
}

//=============================================================================
// �Q�X�g�̃��[�h�I��
//=============================================================================
void CConnectUI::SetGuestMode(SELECTMODE mode)
{
	// �t���[���Ⴆ�Ώ������Ȃ�
	if (m_flow != CONNECTFLOW_SELECT_MODE)
		return;

	m_nSelectMode[PLAYER_TWO] = mode;

	// �I��
	if (!m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_STATE_SELECTED])
	{
		m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_STATE_SELECTED] = CreateBothUI(PLAYER_TWO, CONNECTUI_BOTH_STATE_SELECTED);
		m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_STATE_SELECTED]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_GUEST_SELECTED));

		// �I�𒆂�j��
		if (m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_STATE_SELECTING])
			DeleteBothUI(PLAYER_TWO, CONNECTUI_BOTH_STATE_SELECTING);
	}

	// ����
	if (mode == SELECTMODE_REMOVE)
	{
		m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_MODE_REMOVE] = CreateBothUI(PLAYER_TWO, CONNECTUI_BOTH_MODE_REMOVE);
		m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_MODE_REMOVE]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_SELECT_REMOVE));
		m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_MODE_REMOVE]->SetAnim(D3DXVECTOR2(0.0f, 1.0f / 3 * 2), UV_BUTTON);

		// ��ǂ�j��
		if (m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_MODE_SOLVE])
			DeleteBothUI(PLAYER_TWO, CONNECTUI_BOTH_MODE_SOLVE);
	}
	// ���
	if (mode == SELECTMODE_SOLVE)
	{
		m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_MODE_SOLVE] = CreateBothUI(PLAYER_TWO, CONNECTUI_BOTH_MODE_SOLVE);
		m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_MODE_SOLVE]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_SELECT_SOLVE));
		m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_MODE_SOLVE]->SetAnim(D3DXVECTOR2(0.0f, 1.0f / 3 * 2), UV_BUTTON);

		// ������j��
		if (m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_MODE_REMOVE])
			DeleteBothUI(PLAYER_TWO, CONNECTUI_BOTH_MODE_REMOVE);
	}
}

//=============================================================================
// �Q�X�g�̃��x���I��
//=============================================================================
void CConnectUI::SetGuestLevel(SELECTLEVEL level)
{
	// �t���[���Ⴆ�Ώ������Ȃ�
	if (m_flow != CONNECTFLOW_SELECT_LEVEL)
		return;

	m_nSelectLevel[PLAYER_TWO] = level;

	// �I��
	if (!m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_STATE_SELECTED])
	{
		m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_STATE_SELECTED] = CreateBothUI(PLAYER_TWO, CONNECTUI_BOTH_STATE_SELECTED);
		m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_STATE_SELECTED]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_GUEST_SELECTED));

		// �I�𒆂�j��
		if (m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_STATE_SELECTING])
			DeleteBothUI(PLAYER_TWO, CONNECTUI_BOTH_STATE_SELECTING);
	}

	// �C�[�W�[
	if (level == SELECTLEVEL_EASY)
	{
		m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_LEVEL_EASY] = CreateBothUI(PLAYER_TWO, CONNECTUI_BOTH_LEVEL_EASY);
		m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_LEVEL_EASY]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_SELECT_EASY));
		m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_LEVEL_EASY]->SetAnim(D3DXVECTOR2(0.0f, 1.0f / 3 * 2), UV_BUTTON);

		// ���̓�Փx��j��
		if (m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_LEVEL_NORMAL])
			DeleteBothUI(PLAYER_TWO, CONNECTUI_BOTH_LEVEL_NORMAL);
		if (m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_LEVEL_HARD])
			DeleteBothUI(PLAYER_TWO, CONNECTUI_BOTH_LEVEL_HARD);
	}
	// ���
	if (level == SELECTLEVEL_NORMAL)
	{
		m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_LEVEL_NORMAL] = CreateBothUI(PLAYER_TWO, CONNECTUI_BOTH_LEVEL_NORMAL);
		m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_LEVEL_NORMAL]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_SELECT_NORMAL));
		m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_LEVEL_NORMAL]->SetAnim(D3DXVECTOR2(0.0f, 1.0f / 3 * 2), UV_BUTTON);

		// ���̓�Փx��j��
		if (m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_LEVEL_EASY])
			DeleteBothUI(PLAYER_TWO, CONNECTUI_BOTH_LEVEL_EASY);
		if (m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_LEVEL_HARD])
			DeleteBothUI(PLAYER_TWO, CONNECTUI_BOTH_LEVEL_HARD);
	}
	if (level == SELECTLEVEL_HARD)
	{
		m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_LEVEL_HARD] = CreateBothUI(PLAYER_TWO, CONNECTUI_BOTH_LEVEL_HARD);
		m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_LEVEL_HARD]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_SELECT_HARD));
		m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_LEVEL_HARD]->SetAnim(D3DXVECTOR2(0.0f, 1.0f / 3 * 2), UV_BUTTON);

		// ���̓�Փx��j��
		if (m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_LEVEL_NORMAL])
			DeleteBothUI(PLAYER_TWO, CONNECTUI_BOTH_LEVEL_NORMAL);
		if (m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_LEVEL_EASY])
			DeleteBothUI(PLAYER_TWO, CONNECTUI_BOTH_LEVEL_EASY);
	}
}

//=============================================================================
// �t���[���Ƃ̊J�n���̏���
//=============================================================================
void CConnectUI::Begin(CONNECTFLOW_TYPE flow)
{
	switch (flow)
	{
		// �ڑ���
	case CONNECTFLOW_CONNECTING:
		// ����
		for (int nPlayer = 0; nPlayer < PLAYER_MAX; nPlayer++)
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
		m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_BACK]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_BACK_00));
		m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_BACK]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_BACK_01));
		m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_LOADICON]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_LOAD));
		m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_LOADICON]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_LOAD));
		m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_STATE_CONNECTING]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_CONNECTING));
		m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_STATE_CONNECTING]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_CONNECTING));
		break;

		// ���[�h�I��
	case CONNECTFLOW_SELECT_MODE:
		// �v���C���[��UI
		m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_SELECT_MODE] = CreateBothUI(PLAYER_ONE, CONNECTUI_BOTH_SELECT_MODE);
		m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_MODE_REMOVE] = CreateBothUI(PLAYER_ONE, CONNECTUI_BOTH_MODE_REMOVE);
		m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_MODE_SOLVE] = CreateBothUI(PLAYER_ONE, CONNECTUI_BOTH_MODE_SOLVE);
		m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_SELECT_MODE]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_SELECT_MODE));
		m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_MODE_REMOVE]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_SELECT_REMOVE));
		m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_MODE_SOLVE]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_SELECT_SOLVE));
		// �Q�X�g��UI
		m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_STATE_SELECTING] = CreateBothUI(PLAYER_TWO, CONNECTUI_BOTH_STATE_SELECTING);
		m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_STATE_SELECTING]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_GUEST_SELECTING));
		// ����UI
		m_pUIOnly[CONNECTUI_ONLY_CAUTION_MODE] = CreateOnlyUI(CONNECTUI_ONLY_CAUTION_MODE);
		m_pUIOnly[CONNECTUI_ONLY_COMMENT_REMOVE] = CreateOnlyUI(CONNECTUI_ONLY_COMMENT_REMOVE);
		m_pUIOnly[CONNECTUI_ONLY_COMMENT_SOLVE] = CreateOnlyUI(CONNECTUI_ONLY_COMMENT_SOLVE);
		m_pUIOnly[CONNECTUI_ONLY_CAUTION_MODE]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_CAUTION_MODE));
		m_pUIOnly[CONNECTUI_ONLY_COMMENT_REMOVE]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_COMMENT_REMOVE));
		m_pUIOnly[CONNECTUI_ONLY_COMMENT_SOLVE]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_COMMENT_SOLVE));
		break;

		// ���x���I����
	case CONNECTFLOW_SELECT_LEVEL:
		// �v���C���[��UI
		if (m_nSelectMode[PLAYER_ONE] == SELECTMODE_REMOVE)
		{
			m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_SELECT_LEVEL]	= CreateBothUI(PLAYER_ONE, CONNECTUI_BOTH_SELECT_LEVEL);
			m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_EASY]	= CreateBothUI(PLAYER_ONE, CONNECTUI_BOTH_LEVEL_EASY);
			m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_NORMAL]	= CreateBothUI(PLAYER_ONE, CONNECTUI_BOTH_LEVEL_NORMAL);
			m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_HARD]	= CreateBothUI(PLAYER_ONE, CONNECTUI_BOTH_LEVEL_HARD);
			m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_SELECT_LEVEL]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_SELECT_LEVEL));
			m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_EASY]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_SELECT_EASY));
			m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_NORMAL]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_SELECT_NORMAL));
			m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_HARD]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_SELECT_HARD));
		}
		// �Q�X�g��UI
		else if (m_nSelectMode[PLAYER_TWO] == SELECTMODE_REMOVE)
		{
			m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_STATE_SELECTING] = CreateBothUI(PLAYER_TWO, CONNECTUI_BOTH_STATE_SELECTING);
			m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_STATE_SELECTING]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_GUEST_SELECTING));
		}

		// ����UI
		m_pUIOnly[CONNECTUI_ONLY_CAUTION_LEVEL] = CreateOnlyUI(CONNECTUI_ONLY_CAUTION_LEVEL);
		m_pUIOnly[CONNECTUI_ONLY_COMMENT_EASY] = CreateOnlyUI(CONNECTUI_ONLY_COMMENT_EASY);
		m_pUIOnly[CONNECTUI_ONLY_COMMENT_NORMAL] = CreateOnlyUI(CONNECTUI_ONLY_COMMENT_NORMAL);
		m_pUIOnly[CONNECTUI_ONLY_COMMENT_HARD] = CreateOnlyUI(CONNECTUI_ONLY_COMMENT_HARD);
		m_pUIOnly[CONNECTUI_ONLY_CAUTION_LEVEL]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_CAUTION_LEVEL));
		m_pUIOnly[CONNECTUI_ONLY_COMMENT_EASY]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_COMMENT_EASY));
		m_pUIOnly[CONNECTUI_ONLY_COMMENT_NORMAL]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_COMMENT_NORMAL));
		m_pUIOnly[CONNECTUI_ONLY_COMMENT_HARD]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_COMMENT_HARD));

		break;
	}

	// ���̏�Ԃ�
	m_state = FLOWSTATE_NORMAL;
}

//=============================================================================
// �t���[���Ƃ̏I�����̏���
//=============================================================================
void CConnectUI::End(CONNECTFLOW_TYPE flow)
{
	switch (flow)
	{
		// �ڑ���
	case CONNECTFLOW_CONNECTING:
		// ���̃t���[��
		m_flow = CONNECTFLOW_CONNECTED;
		break;

	case CONNECTFLOW_CONNECTED:
		// �ڑ�������UI��j��
		if (m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_STATE_CONNECTED])
			DeleteBothUI(PLAYER_ONE, CONNECTUI_BOTH_STATE_CONNECTED);
		if (m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_STATE_CONNECTED])
			DeleteBothUI(PLAYER_TWO, CONNECTUI_BOTH_STATE_CONNECTED);
		// �J�E���^�����Z�b�g
		m_nCntState = 0;
		// ���̃t���[��
		m_flow = CONNECTFLOW_SELECT_MODE;
		break;

	case CONNECTFLOW_SELECT_MODE:
		// �v���C���[
		if (m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_SELECT_MODE])
			DeleteBothUI(PLAYER_ONE, CONNECTUI_BOTH_SELECT_MODE);
		if (m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_MODE_REMOVE])
			DeleteBothUI(PLAYER_ONE, CONNECTUI_BOTH_MODE_REMOVE);
		if (m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_MODE_SOLVE])
			DeleteBothUI(PLAYER_ONE, CONNECTUI_BOTH_MODE_SOLVE);
		// �Q�X�g
		if (m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_STATE_SELECTED])
			DeleteBothUI(PLAYER_TWO, CONNECTUI_BOTH_STATE_SELECTED);
		if (m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_STATE_SELECTING])
			DeleteBothUI(PLAYER_TWO, CONNECTUI_BOTH_STATE_SELECTING);
		if (m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_MODE_REMOVE])
			DeleteBothUI(PLAYER_TWO, CONNECTUI_BOTH_MODE_REMOVE);
		if (m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_MODE_SOLVE])
			DeleteBothUI(PLAYER_TWO, CONNECTUI_BOTH_MODE_SOLVE);
		// �R�����g
		if (m_pUIOnly[CONNECTUI_ONLY_BUTTON_DESIDE])
			DeleteOnlyUI(CONNECTUI_ONLY_BUTTON_DESIDE);
		if (m_pUIOnly[CONNECTUI_ONLY_CAUTION_MODE])
			DeleteOnlyUI(CONNECTUI_ONLY_CAUTION_MODE);
		if (m_pUIOnly[CONNECTUI_ONLY_COMMENT_REMOVE])
			DeleteOnlyUI(CONNECTUI_ONLY_COMMENT_REMOVE);
		if (m_pUIOnly[CONNECTUI_ONLY_COMMENT_SOLVE])
			DeleteOnlyUI(CONNECTUI_ONLY_COMMENT_SOLVE);
		// ���̃t���[��
		m_flow = CONNECTFLOW_SELECT_LEVEL;
		break;
	case CONNECTFLOW_SELECT_LEVEL:
		// �v���C���[
		if (m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_SELECT_LEVEL])
			DeleteBothUI(PLAYER_ONE, CONNECTUI_BOTH_SELECT_LEVEL);
		if (m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_EASY])
			DeleteBothUI(PLAYER_ONE, CONNECTUI_BOTH_LEVEL_EASY);
		if (m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_NORMAL])
			DeleteBothUI(PLAYER_ONE, CONNECTUI_BOTH_LEVEL_NORMAL);
		if (m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_HARD])
			DeleteBothUI(PLAYER_ONE, CONNECTUI_BOTH_LEVEL_HARD);
		// �Q�X�g
		if (m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_LEVEL_EASY])
			DeleteBothUI(PLAYER_TWO, CONNECTUI_BOTH_LEVEL_EASY);
		if (m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_LEVEL_NORMAL])
			DeleteBothUI(PLAYER_TWO, CONNECTUI_BOTH_LEVEL_NORMAL);
		if (m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_LEVEL_HARD])
			DeleteBothUI(PLAYER_TWO, CONNECTUI_BOTH_LEVEL_HARD);
		if (m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_STATE_SELECTED])
			DeleteBothUI(PLAYER_TWO, CONNECTUI_BOTH_STATE_SELECTED);
		if (m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_STATE_SELECTED])
			DeleteBothUI(PLAYER_TWO, CONNECTUI_BOTH_STATE_SELECTED);
		// ����UI
		if (m_pUIOnly[CONNECTUI_ONLY_CAUTION_LEVEL])
			DeleteOnlyUI(CONNECTUI_ONLY_CAUTION_LEVEL);
		if (m_pUIOnly[CONNECTUI_ONLY_COMMENT_EASY])
			DeleteOnlyUI(CONNECTUI_ONLY_COMMENT_EASY);
		if (m_pUIOnly[CONNECTUI_ONLY_COMMENT_NORMAL])
			DeleteOnlyUI(CONNECTUI_ONLY_COMMENT_NORMAL);
		if (m_pUIOnly[CONNECTUI_ONLY_COMMENT_HARD])
			DeleteOnlyUI(CONNECTUI_ONLY_COMMENT_HARD);
		if (m_pUIOnly[CONNECTUI_ONLY_BUTTON_DESIDE])
			DeleteOnlyUI(CONNECTUI_ONLY_BUTTON_DESIDE);
		m_flow = CONNECTFLOW_END;
		break;
	}

	// ���̏�Ԃ�
	m_state = FLOWSTATE_BEGIN;
}

//=============================================================================
// �t���[���Ƃ̑҂���Ԃ̏���
//=============================================================================
void CConnectUI::Wait(CONNECTFLOW_TYPE flow)
{
	switch (flow)
	{
	case CONNECTFLOW_SELECT_MODE:
		// ���҂Ƃ��҂���ԂŁA�I�����d�����Ȃ�
		if (m_bGuestWait && 
			((m_nSelectMode[PLAYER_ONE] == SELECTMODE_REMOVE && m_nSelectMode[PLAYER_TWO] == SELECTMODE_SOLVE) ||
			(m_nSelectMode[PLAYER_ONE] == SELECTMODE_SOLVE && m_nSelectMode[PLAYER_TWO] == SELECTMODE_REMOVE)))
		{
			// ����
			m_state = FLOWSTATE_END;
		}
#ifdef _DEBUG
		else if (CManager::GetKeyboard()->GetPress(DIK_LSHIFT) &&
			CManager::GetKeyboard()->GetTrigger(DIK_3))
		{
			// ������������
			m_nSelectMode[PLAYER_ONE] == SELECTMODE_REMOVE ?
				m_nSelectMode[PLAYER_TWO] = SELECTMODE_SOLVE :
				m_nSelectMode[PLAYER_TWO] = SELECTMODE_REMOVE;
			// ����
			m_state = FLOWSTATE_END;
		}
#endif
		break;
	case CONNECTFLOW_SELECT_LEVEL:
		if (m_nSelectMode[PLAYER_ONE] == SELECTMODE_REMOVE)
		{
			if (m_bGuestWait)
				m_state = FLOWSTATE_END;
#ifdef _DEBUG
			else if (CManager::GetKeyboard()->GetPress(DIK_LSHIFT) &&
				CManager::GetKeyboard()->GetTrigger(DIK_4))
			{
				// ������������
				m_nSelectMode[PLAYER_ONE] == SELECTMODE_REMOVE ?
					m_nSelectMode[PLAYER_TWO] = SELECTMODE_SOLVE :
					m_nSelectMode[PLAYER_TWO] = SELECTMODE_REMOVE;
				// ����
				m_state = FLOWSTATE_END;
			}
#endif
		}
		else if (m_nSelectMode[PLAYER_ONE] == SELECTMODE_SOLVE)
		{
			if (m_nSelectLevel[PLAYER_TWO] != SELECTLEVEL_NONE)
				m_state = FLOWSTATE_END;
		}
		break;
	}
}

//=============================================================================
// ���[�h�A�C�R���̃A�j���[�V����
//=============================================================================
void CConnectUI::LoadIconAnim(void)
{
	// ���[�h�A�C�R�������݂���΁A�J�E���^���Z
	if (m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_LOADICON])
		m_nCntAnim++;
	else if (m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_LOADICON])
		m_nCntAnim++;

	// ��莞�ԓ��Ȃ�A�������I����
	if (m_nCntAnim < INTERVAL_ANIM_LOADICON)
		return;

	// ���t���[�������ɃA�j���[�V����
	m_nCntPattern++;
	if (m_nCntPattern >= NUM_ANIMPATTER_LOADICON)
		m_nCntPattern = 0;
	m_nCntAnim = 0;

	if (m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_LOADICON])
		m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_LOADICON]->SetAnim(D3DXVECTOR2(0.0f + (1.0f / NUM_ANIMPATTER_LOADICON * m_nCntPattern), 0.0f), D3DXVECTOR2(1.0f / NUM_ANIMPATTER_LOADICON, 1.0f));
	if (m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_LOADICON])
		m_pUIBoth[PLAYER_TWO][CONNECTUI_BOTH_LOADICON]->SetAnim(D3DXVECTOR2(0.0f + (1.0f / NUM_ANIMPATTER_LOADICON * m_nCntPattern), 0.0f), D3DXVECTOR2(1.0f / NUM_ANIMPATTER_LOADICON, 1.0f));

}

//=============================================================================
// �{�^���̃A�j���[�V����
//=============================================================================
void CConnectUI::ButtonAnim(void)
{
	if (m_flow == CONNECTFLOW_SELECT_MODE)
	{
		// ����
		if (m_nSelectMode[PLAYER_ONE] == SELECTMODE_REMOVE)
			m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_MODE_REMOVE]->SetAnim(D3DXVECTOR2(0.0f, 1.0f / 3 * 2), UV_BUTTON);
		// ���
		if (m_nSelectMode[PLAYER_ONE] == SELECTMODE_SOLVE)
			m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_MODE_SOLVE]->SetAnim(D3DXVECTOR2(0.0f, 1.0f / 3 * 2), UV_BUTTON);
		// �ǂ���ł��Ȃ�
		if (m_nSelectMode[PLAYER_ONE] == SELECTMODE_NONE)
		{
			m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_MODE_REMOVE]->SetAnim(D3DXVECTOR2(0.0f, 0.0f), UV_BUTTON);
			m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_MODE_SOLVE]->SetAnim(D3DXVECTOR2(0.0f, 0.0f), UV_BUTTON);
		}
	}
	if (m_flow == CONNECTFLOW_SELECT_LEVEL)
	{
		// �C�[�W�[
		if (m_nSelectLevel[PLAYER_ONE] == SELECTLEVEL_EASY)
		{
			m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_EASY]->SetAnim(D3DXVECTOR2(0.0f, 1.0f / 3 * 2), UV_BUTTON);
			m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_NORMAL]->SetAnim(D3DXVECTOR2(0.0f, 0.0f), UV_BUTTON);
			m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_HARD]->SetAnim(D3DXVECTOR2(0.0f, 0.0f), UV_BUTTON);
		}
		// �m�[�}��
		if (m_nSelectLevel[PLAYER_ONE] == SELECTLEVEL_NORMAL)
		{
			m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_NORMAL]->SetAnim(D3DXVECTOR2(0.0f, 1.0f / 3 * 2), UV_BUTTON);
			m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_EASY]->SetAnim(D3DXVECTOR2(0.0f, 0.0f), UV_BUTTON);
			m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_HARD]->SetAnim(D3DXVECTOR2(0.0f, 0.0f), UV_BUTTON);
		}
		// �n�[�h
		if (m_nSelectLevel[PLAYER_ONE] == SELECTLEVEL_HARD)
		{
			m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_HARD]->SetAnim(D3DXVECTOR2(0.0f, 1.0f / 3 * 2), UV_BUTTON);
			m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_EASY]->SetAnim(D3DXVECTOR2(0.0f, 0.0f), UV_BUTTON);
			m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_NORMAL]->SetAnim(D3DXVECTOR2(0.0f, 0.0f), UV_BUTTON);
		}
	}
}

//=============================================================================
// �������[�h��I�����Ă��Ȃ����m�F����
//=============================================================================
void CConnectUI::CheckSameMode(void)
{
	// �ʁX�̃��[�h�ł���΁A�������Ȃ�
	if ((m_nSelectMode[PLAYER_ONE] == SELECTMODE_REMOVE && m_nSelectMode[PLAYER_TWO] == SELECTMODE_SOLVE) ||
		(m_nSelectMode[PLAYER_ONE] == SELECTMODE_SOLVE && m_nSelectMode[PLAYER_TWO] == SELECTMODE_REMOVE))
	{
		// ����{�^���𐶐�
		if (!m_pUIOnly[CONNECTUI_ONLY_BUTTON_DESIDE])
		{
			m_pUIOnly[CONNECTUI_ONLY_BUTTON_DESIDE] = CreateOnlyUI(CONNECTUI_ONLY_BUTTON_DESIDE);
			m_pUIOnly[CONNECTUI_ONLY_BUTTON_DESIDE]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_DECIDE));
			m_pUIOnly[CONNECTUI_ONLY_BUTTON_DESIDE]->SetAnim(D3DXVECTOR2(0.0f, 0.0f), UV_BUTTON);
		}

		// ����{�^����j��
		if (m_pUIOnly[CONNECTUI_ONLY_CAUTION_MODE])
			DeleteOnlyUI(CONNECTUI_ONLY_CAUTION_MODE);
		return;
	}

	// ����{�^����j��
	if (m_pUIOnly[CONNECTUI_ONLY_BUTTON_DESIDE])
		DeleteOnlyUI(CONNECTUI_ONLY_BUTTON_DESIDE);


	// ���ӏ����𐶐�
	if (!m_pUIOnly[CONNECTUI_ONLY_CAUTION_MODE])
	{
		m_pUIOnly[CONNECTUI_ONLY_CAUTION_MODE] = CreateOnlyUI(CONNECTUI_ONLY_CAUTION_MODE);
		m_pUIOnly[CONNECTUI_ONLY_CAUTION_MODE]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_CAUTION_MODE));
	}
}

//=============================================================================
// ����{�^�����N���b�N
//=============================================================================
void CConnectUI::ClickDecide(CMouse *pMouse)
{
	// �}�E�X�J�[�\����UI���d�Ȃ��Ă���
	if (!m_pUIOnly[CONNECTUI_ONLY_BUTTON_DESIDE]->ReturnHit(pMouse->GetMousePos()))
		return;

	// �N���b�N���Ă���
	if (pMouse->GetPress(0))
	{
		// �Q�X�g��҂�Ԃ�
		m_pUIOnly[CONNECTUI_ONLY_BUTTON_DESIDE]->SetAnim(D3DXVECTOR2(0.0f, 1.0f / 3), UV_BUTTON);
		m_state = FLOWSTATE_WAIT;
	}
}
