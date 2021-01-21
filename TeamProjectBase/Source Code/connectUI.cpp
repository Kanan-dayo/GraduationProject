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
#include "Debug\debugproc.h"
#include "game.h"
#include "Bomb.h"
#include "sound.h"

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

bool CConnectUI::m_bCreateFlagBoth[2][CONNECTUI_BOTH_MAX] = {};
bool CConnectUI::m_bCreateFlagOnly[CONNECTUI_ONLY_MAX] = {};
bool CConnectUI::m_bDeleteFlagBoth[2][CONNECTUI_BOTH_MAX] = {};
bool CConnectUI::m_bDeleteFlagOnly[CONNECTUI_ONLY_MAX] = {};

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

		for (int nUI = 0; nUI < CONNECTUI_BOTH_MAX; nUI++)
		{
			m_bCreateFlagBoth[nPlayer][nUI] = false;
			m_bDeleteFlagBoth[nPlayer][nUI] = false;
			m_UIInfoBoth[nPlayer][nUI].buttonState = BUTTON_NORMAL;
		}
	}

	for (int nUI = 0; nUI < CONNECTUI_ONLY_MAX; nUI++)
	{
		m_bCreateFlagOnly[nUI] = false;
		m_bDeleteFlagOnly[nUI] = false;
		m_UIInfoOnly[nUI].buttonState = BUTTON_NORMAL;
	}

	return S_OK;
}

//=============================================================================
// �X�V
//=============================================================================
void CConnectUI::Update(void)
{
	// UI����
	CreateUI();
	// UI�j��
	DeleteUI();

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
			{
				if (m_UIInfoBoth[nPlayer][nUI].type == UITYPE_BUTTON)
					ButtonAnimBoth(nPlayer, nUI);

				m_pUIBoth[nPlayer][nUI]->Update();
			}
		}
	}

	for (int nUI = 0; nUI < CONNECTUI_ONLY_MAX; nUI++)
	{
		if (m_pUIOnly[nUI])
		{
			if (m_UIInfoOnly[nUI].type == UITYPE_BUTTON)
				ButtonAnimOnly(nUI);

			m_pUIOnly[nUI]->Update();
		}
	}


	//�t�F�[�h���ĂȂ���
	if (CManager::GetRenderer()->GetFade()->GetFadeState() == CFade::FADE_NONE)
	{
		if (m_flow == CONNECTFLOW_END)
		{
			//�X�e�[�g�ύX
			CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_TUTORIAL);
		}
#ifdef _DEBUG
		if (CManager::GetKeyboard()->GetPress(DIK_LSHIFT) && CManager::GetKeyboard()->GetPress(DIK_RETURN))
		{
			//�X�e�[�g�ύX
			CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_TUTORIAL);
		}
#endif
	}
}

//=============================================================================
// �{�^���̃A�j���[�V����
//=============================================================================
void CConnectUI::ButtonAnimBoth(int nPlayer, int type)
{
	switch (m_UIInfoBoth[nPlayer][type].buttonState)
	{
	case BUTTON_NORMAL: m_pUIBoth[nPlayer][type]->SetAnim(D3DXVECTOR2(0.0f, 0.0f + (1.0f / 3) * 0), UV_BUTTON); break;
	case BUTTON_PRESS:	m_pUIBoth[nPlayer][type]->SetAnim(D3DXVECTOR2(0.0f, 0.0f + (1.0f / 3) * 1), UV_BUTTON); break;
	case BUTTON_SELECT: m_pUIBoth[nPlayer][type]->SetAnim(D3DXVECTOR2(0.0f, 0.0f + (1.0f / 3) * 2), UV_BUTTON); break;
	}
}

void CConnectUI::ButtonAnimOnly(int type)
{
	switch (m_UIInfoOnly[type].buttonState)
	{
	case BUTTON_NORMAL: m_pUIOnly[type]->SetAnim(D3DXVECTOR2(0.0f, 0.0f + (1.0f / 3) * 0), UV_BUTTON); break;
	case BUTTON_PRESS:	m_pUIOnly[type]->SetAnim(D3DXVECTOR2(0.0f, 0.0f + (1.0f / 3) * 1), UV_BUTTON); break;
	case BUTTON_SELECT: m_pUIOnly[type]->SetAnim(D3DXVECTOR2(0.0f, 0.0f + (1.0f / 3) * 2), UV_BUTTON); break;
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

#ifdef _DEBUG
//=============================================================================
// �f�o�b�O�R�}���h
//=============================================================================
void CConnectUI::DebugCommand(void)
{
	if (m_flow == CONNECTFLOW_CONNECTING)
	{
		CDebugProc::Print(CDebugProc::PLACE_LEFT, "1P�ڑ����� [��Shift + 1]\n");
		CDebugProc::Print(CDebugProc::PLACE_LEFT, "2P�ڑ����� [��Shift + 2]\n");

		// �蓮�ŃQ�X�g�̐ڑ�����
		if (CManager::GetKeyboard()->GetPress(DIK_LSHIFT))
		{
			if (CManager::GetKeyboard()->GetTrigger(DIK_1))
				m_bConnect[PLAYER_ONE] = true;
			if (CManager::GetKeyboard()->GetTrigger(DIK_2))
				m_bConnect[PLAYER_TWO] = true;
		}
	}
	// ���[�h�I��
	if (m_flow == CONNECTFLOW_SELECT_MODE)
	{
		// �ʏ�
		if (m_state == FLOWSTATE_NORMAL)
		{
			CDebugProc::Print(CDebugProc::PLACE_LEFT, "�Q�X�g�����I�� [��Shift + 1]\n");
			CDebugProc::Print(CDebugProc::PLACE_LEFT, "�Q�X�g��ǑI�� [��Shift + 2]\n");

			// �蓮�ŃQ�X�g�̃��[�h�ݒ�
			if (CManager::GetKeyboard()->GetPress(DIK_LSHIFT))
			{
				if (CManager::GetKeyboard()->GetTrigger(DIK_1))
					SetGuestMode(SELECTMODE_REMOVE);
				else if (CManager::GetKeyboard()->GetTrigger(DIK_2))
					SetGuestMode(SELECTMODE_SOLVE);
			}
		}
		else if (m_state == FLOWSTATE_WAIT)
		{
			CDebugProc::Print(CDebugProc::PLACE_LEFT, "�Q�X�g�����I�� [��Shift + 1]\n");
			CDebugProc::Print(CDebugProc::PLACE_LEFT, "�Q�X�g��ǑI�� [��Shift + 2]\n");
			CDebugProc::Print(CDebugProc::PLACE_LEFT, "���̃��[�h�ց@ [��Shift + 3]\n");

			// �蓮�ŃQ�X�g�̃��[�h�ݒ�
			if (CManager::GetKeyboard()->GetPress(DIK_LSHIFT))
			{
				if (CManager::GetKeyboard()->GetTrigger(DIK_1))
					SetGuestMode(SELECTMODE_REMOVE);
				else if (CManager::GetKeyboard()->GetTrigger(DIK_2))
					SetGuestMode(SELECTMODE_SOLVE);
			}

			if (CManager::GetKeyboard()->GetPress(DIK_LSHIFT) &&
				CManager::GetKeyboard()->GetTrigger(DIK_3))
			{
				// ������������
				m_nSelectMode[PLAYER_ONE] == SELECTMODE_REMOVE ?
					m_nSelectMode[PLAYER_TWO] = SELECTMODE_SOLVE :
					m_nSelectMode[PLAYER_TWO] = SELECTMODE_REMOVE;
				// ����
				m_state = FLOWSTATE_END;
			}
		}
	}
	else if (m_flow == CONNECTFLOW_SELECT_LEVEL)
	{
		if (m_state == FLOWSTATE_NORMAL)
		{
			if (m_nSelectMode[PLAYER_ONE] == SELECTMODE_SOLVE)
			{
				CDebugProc::Print(CDebugProc::PLACE_LEFT, "�Q�X�g�I��EASY   [��Shift + 1]\n");
				CDebugProc::Print(CDebugProc::PLACE_LEFT, "�Q�X�g�I��NORMAL [��Shift + 2]\n");
				CDebugProc::Print(CDebugProc::PLACE_LEFT, "�Q�X�g�I��HARD   [��Shift + 3]\n");

				if (CManager::GetKeyboard()->GetPress(DIK_LSHIFT))
				{
					// �蓮�ŃQ�X�g�̃��[�h�ݒ�
					if (CManager::GetKeyboard()->GetTrigger(DIK_1))
						SetGuestLevel(SELECTLEVEL_EASY);
					else if (CManager::GetKeyboard()->GetTrigger(DIK_2))
						SetGuestLevel(SELECTLEVEL_NORMAL);
					else if (CManager::GetKeyboard()->GetTrigger(DIK_3))
						SetGuestLevel(SELECTLEVEL_HARD);
				}
			}
			else if (m_nSelectMode[PLAYER_ONE] == SELECTMODE_REMOVE)
			{
				CDebugProc::Print(CDebugProc::PLACE_LEFT, "���̃��[�h��     [��Shift + 4]\n");

				// �蓮�ŃQ�X�g�����F
				if (CManager::GetKeyboard()->GetTrigger(DIK_4))
					m_bGuestWait = true;
			}
		}
		else if (m_state == FLOWSTATE_WAIT)
		{
			if (m_nSelectMode[PLAYER_ONE] == SELECTMODE_SOLVE)
			{
				CDebugProc::Print(CDebugProc::PLACE_LEFT, "�Q�X�g�I��EASY   [��Shift + 1]\n");
				CDebugProc::Print(CDebugProc::PLACE_LEFT, "�Q�X�g�I��NORMAL [��Shift + 2]\n");
				CDebugProc::Print(CDebugProc::PLACE_LEFT, "�Q�X�g�I��HARD   [��Shift + 3]\n");

				if (CManager::GetKeyboard()->GetPress(DIK_LSHIFT))
				{
					// �蓮�ŃQ�X�g�̓�Փx�ݒ�
					if (CManager::GetKeyboard()->GetTrigger(DIK_1))
						SetGuestLevel(SELECTLEVEL_EASY);
					else if (CManager::GetKeyboard()->GetTrigger(DIK_2))
						SetGuestLevel(SELECTLEVEL_NORMAL);
					else if (CManager::GetKeyboard()->GetTrigger(DIK_3))
						SetGuestLevel(SELECTLEVEL_HARD);
					// ��Փx���I������Ă���΁A�蓮�ŃQ�[���J�n
					if (m_nSelectLevel[PLAYER_TWO] != SELECTLEVEL_NONE)
					{
						CDebugProc::Print(CDebugProc::PLACE_LEFT, "���̃��[�h��     [��Shift + 4]\n");

						if (CManager::GetKeyboard()->GetTrigger(DIK_4))
						{
							m_state = FLOWSTATE_END;
						}
					}
				}
			}
			else if (m_nSelectMode[PLAYER_ONE] == SELECTMODE_REMOVE)
			{
				CDebugProc::Print(CDebugProc::PLACE_LEFT, "���̃��[�h��     [��Shift + 4]\n");

				if (CManager::GetKeyboard()->GetTrigger(DIK_4))
					m_bGuestWait = true;
			}
		}
	}
}
#endif

//=============================================================================
// UI����
//=============================================================================
void CConnectUI::CreateUI(void)
{
	for (int nPlayer = 0; nPlayer < 2; nPlayer++)
	{
		for (int nUI = 0; nUI < CONNECTUI_BOTH_MAX; nUI++)
		{
			// ���݂����A�����t���O�L��
			if (m_bCreateFlagBoth[nPlayer][nUI] && !m_pUIBoth[nPlayer][nUI])
			{
				// ����
				m_pUIBoth[nPlayer][nUI] = CreateBothUI(nPlayer, (CONNECTUITYPE_BOTH)nUI);
				m_pUIBoth[nPlayer][nUI]->BindTexture(CTexture::GetTexture((CTexture::TEX_TYPE)GetTexNumberBoth(nPlayer, (CONNECTUITYPE_BOTH)nUI)));
			}
			// �t���O����
			m_bCreateFlagBoth[nPlayer][nUI] = false;
		}
	}

	for (int nUI = 0; nUI < CONNECTUI_ONLY_MAX; nUI++)
	{
		// ���݂����A�����t���O�L��
		if (m_bCreateFlagOnly[nUI] && !m_pUIOnly[nUI])
		{
			// ����
			m_pUIOnly[nUI] = CreateOnlyUI((CONNECTUITYPE_ONLY)nUI);
			m_pUIOnly[nUI]->BindTexture(CTexture::GetTexture((CTexture::TEX_TYPE)GetTexNumberOnly((CONNECTUITYPE_ONLY)nUI)));
		}
		// �t���O����
		m_bCreateFlagOnly[nUI] = false;
	}
}

//=============================================================================
// UI�j��
//=============================================================================
void CConnectUI::DeleteUI(void)
{
	for (int nPlayer = 0; nPlayer < 2; nPlayer++)
	{
		for (int nUI = 0; nUI < CONNECTUI_BOTH_MAX; nUI++)
		{
			// ���݂��A�t���O�L��
			if (m_bDeleteFlagBoth[nPlayer][nUI] && m_pUIBoth[nPlayer][nUI])
			{
				// �j��
				DeleteBothUI(nPlayer, (CONNECTUITYPE_BOTH)nUI);
			}
			// �t���O����
			m_bDeleteFlagBoth[nPlayer][nUI] = false;
		}
	}

	for (int nUI = 0; nUI < CONNECTUI_ONLY_MAX; nUI++)
	{
		// ���݂��A�t���O�L��
		if (m_bDeleteFlagOnly[nUI] && m_pUIOnly[nUI])
		{
			// �j��
			DeleteOnlyUI((CONNECTUITYPE_ONLY)nUI);
		}
		// �t���O����
		m_bDeleteFlagOnly[nUI] = false;
	}
}

//=============================================================================
// UI�̃e�N�X�`���ԍ��擾
//=============================================================================
int CConnectUI::GetTexNumberBoth(int nPlayer, CONNECTUITYPE_BOTH type)
{
	if (nPlayer == 0)
	{
		switch (type)
		{
		case CONNECTUI_BOTH_BACK:				return CTexture::TEX_CONNECT_BACK_00; break;			// �w�i
		case CONNECTUI_BOTH_LOADICON:			return CTexture::TEX_CONNECT_LOAD; break;				// ���[�h�A�C�R��
		case CONNECTUI_BOTH_STATE_CONNECTING:	return CTexture::TEX_CONNECT_CONNECTING; break;			// �ڑ���
		case CONNECTUI_BOTH_STATE_CONNECTED:	return CTexture::TEX_CONNECT_CONNECTED; break;			// �ڑ�����
		case CONNECTUI_BOTH_STATE_SELECTING:	return CTexture::TEX_CONNECT_GUEST_SELECTING; break;	// �I��
		case CONNECTUI_BOTH_STATE_SELECTED:		return CTexture::TEX_CONNECT_GUEST_SELECTED; break;		// �I������
		case CONNECTUI_BOTH_SELECT_MODE:		return CTexture::TEX_CONNECT_SELECT_MODE; break;		// �I�� ���[�h
		case CONNECTUI_BOTH_SELECT_LEVEL:		return CTexture::TEX_CONNECT_SELECT_LEVEL; break;		// �I�� ���x��
		case CONNECTUI_BOTH_MODE_REMOVE:		return CTexture::TEX_CONNECT_SELECT_REMOVE; break;		// ���[�h ����
		case CONNECTUI_BOTH_MODE_SOLVE:			return CTexture::TEX_CONNECT_SELECT_SOLVE; break;		// ���[�h ���
		case CONNECTUI_BOTH_LEVEL_EASY:			return CTexture::TEX_CONNECT_SELECT_EASY; break;		// ��Փx �C�[�W�[
		case CONNECTUI_BOTH_LEVEL_NORMAL:		return CTexture::TEX_CONNECT_SELECT_NORMAL; break;		// ��Փx �m�[�}��
		case CONNECTUI_BOTH_LEVEL_HARD:			return CTexture::TEX_CONNECT_SELECT_HARD; break;		// ��Փx �n�[�h
		}
	}
	else if (nPlayer == 1)
	{
		switch (type)
		{
		case CONNECTUI_BOTH_BACK:				return CTexture::TEX_CONNECT_BACK_01; break;			// �w�i
		case CONNECTUI_BOTH_LOADICON:			return CTexture::TEX_CONNECT_LOAD; break;				// ���[�h�A�C�R��
		case CONNECTUI_BOTH_STATE_CONNECTING:	return CTexture::TEX_CONNECT_CONNECTING; break;			// �ڑ���
		case CONNECTUI_BOTH_STATE_CONNECTED:	return CTexture::TEX_CONNECT_CONNECTED; break;			// �ڑ�����
		case CONNECTUI_BOTH_STATE_SELECTING:	return CTexture::TEX_CONNECT_GUEST_SELECTING; break;	// �I��
		case CONNECTUI_BOTH_STATE_SELECTED:		return CTexture::TEX_CONNECT_GUEST_SELECTED; break;		// �I������
		case CONNECTUI_BOTH_SELECT_MODE:		return CTexture::TEX_CONNECT_SELECT_MODE; break;		// �I�� ���[�h
		case CONNECTUI_BOTH_SELECT_LEVEL:		return CTexture::TEX_CONNECT_SELECT_LEVEL; break;		// �I�� ���x��
		case CONNECTUI_BOTH_MODE_REMOVE:		return CTexture::TEX_CONNECT_SELECT_REMOVE; break;		// ���[�h ����
		case CONNECTUI_BOTH_MODE_SOLVE:			return CTexture::TEX_CONNECT_SELECT_SOLVE; break;		// ���[�h ���
		case CONNECTUI_BOTH_LEVEL_EASY:			return CTexture::TEX_CONNECT_SELECT_EASY; break;		// ��Փx �C�[�W�[
		case CONNECTUI_BOTH_LEVEL_NORMAL:		return CTexture::TEX_CONNECT_SELECT_NORMAL; break;		// ��Փx �m�[�}��
		case CONNECTUI_BOTH_LEVEL_HARD:			return CTexture::TEX_CONNECT_SELECT_HARD; break;		// ��Փx �n�[�h
		}
	}

	return 0;
}

//=============================================================================
// UI�̃e�N�X�`���ԍ��擾
//=============================================================================
int CConnectUI::GetTexNumberOnly(CONNECTUITYPE_ONLY type)
{
	switch (type)
	{
	case CONNECTUI_ONLY_BUTTON_DESIDE:	return CTexture::TEX_CONNECT_DECIDE; break;				// ����{�^��
	case CONNECTUI_ONLY_COMMENT_REMOVE:	return CTexture::TEX_CONNECT_COMMENT_REMOVE; break;		// �R�����g ����
	case CONNECTUI_ONLY_COMMENT_SOLVE:	return CTexture::TEX_CONNECT_COMMENT_SOLVE; break;		// �R�����g ���
	case CONNECTUI_ONLY_COMMENT_EASY:	return CTexture::TEX_CONNECT_COMMENT_EASY; break;		// �R�����g �C�[�W�[
	case CONNECTUI_ONLY_COMMENT_NORMAL:	return CTexture::TEX_CONNECT_COMMENT_NORMAL; break;		// �R�����g �m�[�}��
	case CONNECTUI_ONLY_COMMENT_HARD:	return CTexture::TEX_CONNECT_COMMENT_HARD; break;		// �R�����g �n�[�h
	case CONNECTUI_ONLY_CAUTION_MODE:	return CTexture::TEX_CONNECT_CAUTION_MODE; break;		// ���[�h�I���̒���
	case CONNECTUI_ONLY_CAUTION_LEVEL:	return CTexture::TEX_CONNECT_CAUTION_LEVEL; break;		// ���x���I���̒���
	}
	return 0;
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

	if (type == CONNECTUI_BOTH_MODE_REMOVE ||
		type == CONNECTUI_BOTH_MODE_SOLVE ||
		type == CONNECTUI_BOTH_LEVEL_EASY ||
		type == CONNECTUI_BOTH_LEVEL_NORMAL ||
		type == CONNECTUI_BOTH_LEVEL_HARD)
	{
		m_UIInfoBoth[nPlayer][type].type = UITYPE_BUTTON;
	}
	else if (type == CONNECTUI_BOTH_LOADICON)
	{
		m_UIInfoBoth[nPlayer][type].type = UITYPE_LOADICON;
	}

	// �{�^����UV�l��ύX
	if (m_UIInfoBoth[nPlayer][type].type == UITYPE_BUTTON)
		pPolygon->SetAnim(ZeroVector2, D3DXVECTOR2(1.0f, 1.0f / 3));

	// ���[�h�A�C�R����UV�l��ύX
	if (m_UIInfoBoth[nPlayer][type].type == UITYPE_LOADICON)
		pPolygon->SetAnim(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f / NUM_ANIMPATTER_LOADICON, 1.0f));

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

	if (type == CONNECTUI_ONLY_BUTTON_DESIDE)
		m_UIInfoOnly[type].type = UITYPE_BUTTON;

	if (m_UIInfoOnly[type].type == UITYPE_BUTTON)
		pPolygon->SetAnim(ZeroVector2, D3DXVECTOR2(1.0f, 1.0f / 3));

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
#ifdef _DEBUG
	DebugCommand();
#endif

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
		m_bDeleteFlagBoth[nPlayer][CONNECTUI_BOTH_LOADICON] = true;
		m_bDeleteFlagBoth[nPlayer][CONNECTUI_BOTH_STATE_CONNECTING] = true;

		// �ڑ�����UI�𐶐�
		m_bCreateFlagBoth[nPlayer][CONNECTUI_BOTH_STATE_CONNECTED] = true;
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
#ifdef _DEBUG
	DebugCommand();
#endif
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

	// �}�E�X�̃|�C���^�擾
	CMouse *pMouse = CManager::GetMouse();
	// �}�E�X���W���擾
	D3DXVECTOR2 mousePos = pMouse->GetMousePos();

	if (m_nSelectMode[PLAYER_ONE] != SELECTMODE_NONE)
	{
		m_UIInfoBoth[PLAYER_ONE][CONNECTUI_BOTH_MODE_REMOVE - 1 + m_nSelectMode[PLAYER_ONE]].buttonState = BUTTON_SELECT;
	}

	// �J�[�\���ʒu��UI�Əd�Ȃ��Ă���
	if (m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_MODE_REMOVE]->ReturnHit(mousePos))
	{
		// �i�X�\��
		D3DXCOLOR col = m_pUIOnly[CONNECTUI_ONLY_COMMENT_REMOVE]->GetCol();
		if (col.a < 1.0f)
			m_pUIOnly[CONNECTUI_ONLY_COMMENT_REMOVE]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a + (1.0f / TIME_ALPHA_COMMENT)));

		// �N���b�N���ĂȂ���΁A�������Ȃ�
		if (pMouse->GetTrigger(0))
		{
			m_UIInfoBoth[PLAYER_ONE][CONNECTUI_BOTH_MODE_REMOVE].buttonState = BUTTON_PRESS;
			m_UIInfoBoth[PLAYER_ONE][CONNECTUI_BOTH_MODE_SOLVE].buttonState = BUTTON_NORMAL;

			//���Đ�
			CManager::GetSound()->Play(CSound::LABEL_SE_SELECT);

			if (m_nSelectMode[PLAYER_ONE] != SELECTMODE_REMOVE)
			{
				m_nSelectMode[PLAYER_ONE] = SELECTMODE_REMOVE;
				CClient::SendSelect(m_nSelectMode[PLAYER_ONE]);
			}
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
		if (pMouse->GetTrigger(0))
		{
			m_UIInfoBoth[PLAYER_ONE][CONNECTUI_BOTH_MODE_SOLVE].buttonState = BUTTON_PRESS;
			m_UIInfoBoth[PLAYER_ONE][CONNECTUI_BOTH_MODE_REMOVE].buttonState = BUTTON_NORMAL;
			//���Đ�
			CManager::GetSound()->Play(CSound::LABEL_SE_SELECT);

			if (m_nSelectMode[PLAYER_ONE] != SELECTMODE_SOLVE)
			{
				m_nSelectMode[PLAYER_ONE] = SELECTMODE_SOLVE;
				CClient::SendSelect(m_nSelectMode[PLAYER_ONE]);
			}
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
#ifdef _DEBUG
	DebugCommand();
#endif

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
		if (m_nSelectLevel[PLAYER_ONE] != SELECTLEVEL_NONE)
		{
			m_UIInfoBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_EASY - 1 + m_nSelectLevel[PLAYER_ONE]].buttonState = BUTTON_SELECT;
		}

		// �J�[�\���ʒu��UI�Əd�Ȃ��Ă���
		if (m_pUIBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_EASY]->ReturnHit(mousePos))
		{
			// �i�X�\��
			D3DXCOLOR col = m_pUIOnly[CONNECTUI_ONLY_COMMENT_EASY]->GetCol();
			if (col.a < 1.0f)
				m_pUIOnly[CONNECTUI_ONLY_COMMENT_EASY]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a + (1.0f / TIME_ALPHA_COMMENT)));

			// �N���b�N���ĂȂ���΁A�������Ȃ�
			if (pMouse->GetTrigger(0))
			{
				m_UIInfoBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_EASY].buttonState = BUTTON_PRESS;
				m_UIInfoBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_NORMAL].buttonState = BUTTON_NORMAL;
				m_UIInfoBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_HARD].buttonState = BUTTON_NORMAL;

				//���Đ�
				CManager::GetSound()->Play(CSound::LABEL_SE_SELECT);

				if (m_nSelectLevel[PLAYER_ONE] != SELECTLEVEL_EASY)
				{
					m_nSelectLevel[PLAYER_ONE] = SELECTLEVEL_EASY;
					CClient::SendSelect(m_nSelectLevel[PLAYER_ONE]);
				}
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
			if (pMouse->GetTrigger(0))
			{
				m_UIInfoBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_NORMAL].buttonState = BUTTON_PRESS;
				m_UIInfoBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_EASY].buttonState = BUTTON_NORMAL;
				m_UIInfoBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_HARD].buttonState = BUTTON_NORMAL;

				//���Đ�
				CManager::GetSound()->Play(CSound::LABEL_SE_SELECT);

				if (m_nSelectLevel[PLAYER_ONE] != SELECTLEVEL_NORMAL)
				{
					m_nSelectLevel[PLAYER_ONE] = SELECTLEVEL_NORMAL;
					CClient::SendSelect(m_nSelectLevel[PLAYER_ONE]);
				}
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
			if (pMouse->GetTrigger(0))
			{
				m_UIInfoBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_HARD].buttonState = BUTTON_PRESS;
				m_UIInfoBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_EASY].buttonState = BUTTON_NORMAL;
				m_UIInfoBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_NORMAL].buttonState = BUTTON_NORMAL;

				//���Đ�
				CManager::GetSound()->Play(CSound::LABEL_SE_SELECT);

				if (m_nSelectLevel[PLAYER_ONE] != SELECTLEVEL_HARD)
				{
					m_nSelectLevel[PLAYER_ONE] = SELECTLEVEL_HARD;
					CClient::SendSelect(m_nSelectLevel[PLAYER_ONE]);
				}
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
				m_bCreateFlagOnly[CONNECTUI_ONLY_BUTTON_DESIDE] = true;

				// ���ӏ�����j��
				if (m_pUIOnly[CONNECTUI_ONLY_CAUTION_LEVEL])
					DeleteOnlyUI(CONNECTUI_ONLY_CAUTION_LEVEL);
			}
		}
	}
	else
	{
		if (!m_pUIOnly[CONNECTUI_ONLY_BUTTON_DESIDE])
		{
			// ����{�^���𐶐�
			if (m_nSelectLevel[PLAYER_TWO] != SELECTLEVEL_NONE)
			{
				m_bCreateFlagOnly[CONNECTUI_ONLY_BUTTON_DESIDE] = true;

				// ����{�^����j��
				if (m_pUIOnly[CONNECTUI_ONLY_CAUTION_LEVEL])
					DeleteOnlyUI(CONNECTUI_ONLY_CAUTION_LEVEL);
			}
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
		m_bCreateFlagBoth[PLAYER_TWO][CONNECTUI_BOTH_STATE_SELECTED] = true;
		m_bDeleteFlagBoth[PLAYER_TWO][CONNECTUI_BOTH_STATE_SELECTING] = true;
	}

	// ����
	if (mode == SELECTMODE_REMOVE)
	{
		m_bCreateFlagBoth[PLAYER_TWO][CONNECTUI_BOTH_MODE_REMOVE] = true;
		m_UIInfoBoth[PLAYER_TWO][CONNECTUI_BOTH_MODE_REMOVE].buttonState = BUTTON_SELECT;

		m_bDeleteFlagBoth[PLAYER_TWO][CONNECTUI_BOTH_MODE_SOLVE] = true;
	}
	// ���
	if (mode == SELECTMODE_SOLVE)
	{
		m_bCreateFlagBoth[PLAYER_TWO][CONNECTUI_BOTH_MODE_SOLVE] = true;
		m_UIInfoBoth[PLAYER_TWO][CONNECTUI_BOTH_MODE_SOLVE].buttonState = BUTTON_SELECT;

		m_bDeleteFlagBoth[PLAYER_TWO][CONNECTUI_BOTH_MODE_REMOVE] = true;
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
		m_bCreateFlagBoth[PLAYER_TWO][CONNECTUI_BOTH_STATE_SELECTED] = true;
		m_bDeleteFlagBoth[PLAYER_TWO][CONNECTUI_BOTH_STATE_SELECTING] = true;
	}

	// �C�[�W�[
	if (level == SELECTLEVEL_EASY)
	{
		m_bCreateFlagBoth[PLAYER_TWO][CONNECTUI_BOTH_LEVEL_EASY] = true;
		m_UIInfoBoth[PLAYER_TWO][CONNECTUI_BOTH_LEVEL_EASY].buttonState = BUTTON_SELECT;

		m_bDeleteFlagBoth[PLAYER_TWO][CONNECTUI_BOTH_LEVEL_NORMAL] = true;
		m_bDeleteFlagBoth[PLAYER_TWO][CONNECTUI_BOTH_LEVEL_HARD] = true;
	}
	// ���
	if (level == SELECTLEVEL_NORMAL)
	{
		m_bCreateFlagBoth[PLAYER_TWO][CONNECTUI_BOTH_LEVEL_NORMAL] = true;
		m_UIInfoBoth[PLAYER_TWO][CONNECTUI_BOTH_LEVEL_NORMAL].buttonState = BUTTON_SELECT;

		m_bDeleteFlagBoth[PLAYER_TWO][CONNECTUI_BOTH_LEVEL_EASY] = true;
		m_bDeleteFlagBoth[PLAYER_TWO][CONNECTUI_BOTH_LEVEL_HARD] = true;
	}
	if (level == SELECTLEVEL_HARD)
	{
		m_bCreateFlagBoth[PLAYER_TWO][CONNECTUI_BOTH_LEVEL_HARD] = true;
		m_UIInfoBoth[PLAYER_TWO][CONNECTUI_BOTH_LEVEL_HARD].buttonState = BUTTON_SELECT;

		m_bDeleteFlagBoth[PLAYER_TWO][CONNECTUI_BOTH_LEVEL_NORMAL] = true;
		m_bDeleteFlagBoth[PLAYER_TWO][CONNECTUI_BOTH_LEVEL_EASY] = true;
	}
}

//=============================================================================
// �Q�X�g�̑I��������
//=============================================================================
void CConnectUI::RecvGuestSelect(int nSelect)
{
	printf("�Q�X�g����I������M\n");
	// ���[�h�ʂőI��
	if (m_flow == CONNECTFLOW_SELECT_MODE)
		SetGuestMode((SELECTMODE)nSelect);
	if (m_flow == CONNECTFLOW_SELECT_LEVEL)
		SetGuestLevel((SELECTLEVEL)nSelect);
}

//=============================================================================
// �Q�X�g�̑҂���Ԃ�����
//=============================================================================
void CConnectUI::RecvGuestWait(void)
{
	printf("�Q�X�g����҂���Ԃ���M\n");
	// �҂���Ԃ�on
	m_bGuestWait = true;
}

//=============================================================================
// �t���[���Ƃ̊J�n���̏���
//=============================================================================
void CConnectUI::Begin(CONNECTFLOW_TYPE flow)
{
	m_bGuestWait = false;

	switch (flow)
	{
		// �ڑ���
	case CONNECTFLOW_CONNECTING:
		// ����
		for (int nPlayer = 0; nPlayer < PLAYER_MAX; nPlayer++)
		{
			m_bCreateFlagBoth[nPlayer][CONNECTUI_BOTH_BACK] = true;
			m_bCreateFlagBoth[nPlayer][CONNECTUI_BOTH_LOADICON] = true;
			m_bCreateFlagBoth[nPlayer][CONNECTUI_BOTH_STATE_CONNECTING] = true;
		}
		break;

		// ���[�h�I��
	case CONNECTFLOW_SELECT_MODE:
		m_bCreateFlagBoth[PLAYER_ONE][CONNECTUI_BOTH_SELECT_MODE] = true;
		m_bCreateFlagBoth[PLAYER_ONE][CONNECTUI_BOTH_MODE_REMOVE] = true;
		m_bCreateFlagBoth[PLAYER_ONE][CONNECTUI_BOTH_MODE_SOLVE] = true;
		m_bCreateFlagBoth[PLAYER_TWO][CONNECTUI_BOTH_STATE_SELECTING] = true;
		m_bCreateFlagOnly[CONNECTUI_ONLY_CAUTION_MODE] = true;
		m_bCreateFlagOnly[CONNECTUI_ONLY_COMMENT_REMOVE] = true;
		m_bCreateFlagOnly[CONNECTUI_ONLY_COMMENT_SOLVE] = true;
		break;

		// ���x���I����
	case CONNECTFLOW_SELECT_LEVEL:
		m_UIInfoOnly[CONNECTUI_ONLY_BUTTON_DESIDE].buttonState = BUTTON_NORMAL;
		// �v���C���[��UI
		if (m_nSelectMode[PLAYER_ONE] == SELECTMODE_REMOVE)
		{
			m_bCreateFlagBoth[PLAYER_ONE][CONNECTUI_BOTH_SELECT_LEVEL] = true;
			m_bCreateFlagBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_EASY] = true;
			m_bCreateFlagBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_NORMAL] = true;
			m_bCreateFlagBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_HARD] = true;
		}
		// �Q�X�g��UI
		else if (m_nSelectMode[PLAYER_TWO] == SELECTMODE_REMOVE)
		{
			m_bCreateFlagBoth[PLAYER_TWO][CONNECTUI_BOTH_STATE_SELECTING] = true;
		}

		m_bCreateFlagOnly[CONNECTUI_ONLY_CAUTION_LEVEL] = true;
		m_bCreateFlagOnly[CONNECTUI_ONLY_COMMENT_EASY] = true;
		m_bCreateFlagOnly[CONNECTUI_ONLY_COMMENT_NORMAL] = true;
		m_bCreateFlagOnly[CONNECTUI_ONLY_COMMENT_HARD] = true;
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
		m_bDeleteFlagBoth[PLAYER_ONE][CONNECTUI_BOTH_STATE_CONNECTED] = true;
		m_bDeleteFlagBoth[PLAYER_TWO][CONNECTUI_BOTH_STATE_CONNECTED] = true;
		// �J�E���^�����Z�b�g
		m_nCntState = 0;
		// ���̃t���[��
		m_flow = CONNECTFLOW_SELECT_MODE;
		break;

	case CONNECTFLOW_SELECT_MODE:
		m_bDeleteFlagBoth[PLAYER_ONE][CONNECTUI_BOTH_SELECT_MODE] = true;
		m_bDeleteFlagBoth[PLAYER_ONE][CONNECTUI_BOTH_MODE_REMOVE] = true;
		m_bDeleteFlagBoth[PLAYER_ONE][CONNECTUI_BOTH_MODE_SOLVE] = true;

		m_bDeleteFlagBoth[PLAYER_TWO][CONNECTUI_BOTH_STATE_SELECTED] = true;
		m_bDeleteFlagBoth[PLAYER_TWO][CONNECTUI_BOTH_STATE_SELECTING] = true;
		m_bDeleteFlagBoth[PLAYER_TWO][CONNECTUI_BOTH_MODE_REMOVE] = true;
		m_bDeleteFlagBoth[PLAYER_TWO][CONNECTUI_BOTH_MODE_SOLVE] = true;
		
		m_bDeleteFlagOnly[CONNECTUI_ONLY_BUTTON_DESIDE] = true;
		m_bDeleteFlagOnly[CONNECTUI_ONLY_CAUTION_MODE] = true;
		m_bDeleteFlagOnly[CONNECTUI_ONLY_COMMENT_REMOVE] = true;
		m_bDeleteFlagOnly[CONNECTUI_ONLY_COMMENT_SOLVE] = true;
		// ���̃t���[��
		m_flow = CONNECTFLOW_SELECT_LEVEL;
		break;
	case CONNECTFLOW_SELECT_LEVEL:
		m_bDeleteFlagBoth[PLAYER_ONE][CONNECTUI_BOTH_SELECT_LEVEL] = true;
		m_bDeleteFlagBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_EASY] = true;
		m_bDeleteFlagBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_NORMAL] = true;
		m_bDeleteFlagBoth[PLAYER_ONE][CONNECTUI_BOTH_LEVEL_HARD] = true;

		m_bDeleteFlagBoth[PLAYER_TWO][CONNECTUI_BOTH_LEVEL_EASY] = true;
		m_bDeleteFlagBoth[PLAYER_TWO][CONNECTUI_BOTH_LEVEL_NORMAL] = true;
		m_bDeleteFlagBoth[PLAYER_TWO][CONNECTUI_BOTH_LEVEL_HARD] = true;
		m_bDeleteFlagBoth[PLAYER_TWO][CONNECTUI_BOTH_STATE_SELECTED] = true;
		m_bDeleteFlagBoth[PLAYER_TWO][CONNECTUI_BOTH_STATE_SELECTED] = true;

		m_bDeleteFlagOnly[CONNECTUI_ONLY_CAUTION_LEVEL] = true;
		m_bDeleteFlagOnly[CONNECTUI_ONLY_COMMENT_EASY] = true;
		m_bDeleteFlagOnly[CONNECTUI_ONLY_COMMENT_NORMAL] = true;
		m_bDeleteFlagOnly[CONNECTUI_ONLY_COMMENT_HARD] = true;
		m_bDeleteFlagOnly[CONNECTUI_ONLY_BUTTON_DESIDE] = true;

		m_flow = CONNECTFLOW_END;
		// ��Փx��ݒ�
		m_nSelectMode[PLAYER_ONE] == SELECTMODE_REMOVE ?
			CGame::SetDifficulty((CBomb::DIFFICULTY)m_nSelectLevel[PLAYER_ONE]) :
			CGame::SetDifficulty((CBomb::DIFFICULTY)m_nSelectLevel[PLAYER_TWO]);
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
		// ���҂Ƃ��҂���Ԃ����A�I�����d������
		if ((m_nSelectMode[PLAYER_ONE] == SELECTMODE_REMOVE && m_nSelectMode[PLAYER_TWO] == SELECTMODE_REMOVE) ||
			(m_nSelectMode[PLAYER_ONE] == SELECTMODE_SOLVE && m_nSelectMode[PLAYER_TWO] == SELECTMODE_SOLVE))
		{
			// �I�тȂ���
			m_bGuestWait = false;
			m_state = FLOWSTATE_NORMAL;
		}
		// ���҂Ƃ��҂���ԂŁA�I�����d�����Ȃ�
		if (m_bGuestWait &&
			((m_nSelectMode[PLAYER_ONE] == SELECTMODE_REMOVE && m_nSelectMode[PLAYER_TWO] == SELECTMODE_SOLVE) ||
			(m_nSelectMode[PLAYER_ONE] == SELECTMODE_SOLVE && m_nSelectMode[PLAYER_TWO] == SELECTMODE_REMOVE)))
		{
			// ����
			m_state = FLOWSTATE_END;
		}
		break;
	case CONNECTFLOW_SELECT_LEVEL:
		// ������
		if (m_nSelectMode[PLAYER_ONE] == SELECTMODE_REMOVE)
		{
			// �Q�X�g�̏��F�𓾂���΁A�Q�[���J�n
			if (m_bGuestWait)
				m_state = FLOWSTATE_END;
		}
		// ��Ǒ�
		else if (m_nSelectMode[PLAYER_ONE] == SELECTMODE_SOLVE)
		{
			// �Q�X�g�����[�h��I��ł���΁A�Q�[���J�n
			if (m_bGuestWait && m_nSelectLevel[PLAYER_TWO] != SELECTLEVEL_NONE)
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
			m_bCreateFlagOnly[CONNECTUI_ONLY_BUTTON_DESIDE] = true;
		}

		// ����{�^����j��
		if (m_pUIOnly[CONNECTUI_ONLY_CAUTION_MODE])
			m_bDeleteFlagOnly[CONNECTUI_ONLY_CAUTION_MODE] = true;
		return;
	}

	// ����{�^����j��
	if (m_pUIOnly[CONNECTUI_ONLY_BUTTON_DESIDE])
		m_bDeleteFlagOnly[CONNECTUI_ONLY_BUTTON_DESIDE] = true;

	// ���ӏ����𐶐�
	if (!m_pUIOnly[CONNECTUI_ONLY_CAUTION_MODE])
		m_bCreateFlagOnly[CONNECTUI_ONLY_CAUTION_MODE] = true;
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
		//�I����
		CManager::GetSound()->Play(CSound::LABEL_SE_DECISION);

		// �Q�X�g��҂�Ԃ�
		m_UIInfoOnly[CONNECTUI_ONLY_BUTTON_DESIDE].buttonState = BUTTON_PRESS;
		// �T�[�o�[�֑҂���Ԃ𑗐M
		if (m_state != FLOWSTATE_WAIT)
		{
			CClient::SendWait();
		}
		// �҂���Ԃ�
		m_state = FLOWSTATE_WAIT;
	}
}
