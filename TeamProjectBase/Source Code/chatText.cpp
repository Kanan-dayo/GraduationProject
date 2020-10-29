//==========================================================================================================================================================
//
// �`���b�g�p�e�L�X�g���� [ chatText.cpp ]
// Author : KANAN NAGANAWA
//
//==========================================================================================================================================================
#include "chatText.h"
#include "renderer.h"
#include "manager.h"
#include "keyboard.h"
#include "input.h"
#include "client.h"
#include "chatTab.h"

//==========================================================================================================================================================
// �}�N����`
//==========================================================================================================================================================
#define CHARACTER_HEIGHT		(18)				// �����̍���
#define CHARACTER_WIDTH			(0)					// �����̕�
#define CHARACTER_LINE_WEIGHT	(1)					// �����̑���
#define CHARACTER_FONTNAME		("�l�r �S�V�b�N")	// �����̃t�H���g��
#define TIME_PRESSKEY			(40)				// �L�[�̒���������

//==========================================================================================================================================================
// �ÓI�����o�ϐ�
//==========================================================================================================================================================
LPD3DXFONT		CChatText::m_pFont						= NULL;
char			CChatText::m_aStr[MAX_CHARACTER]		= {};
std::string		CChatText::m_cSendText					= {};
D3DXCOLOR		CChatText::m_textColor					= WhiteColor;
char			CChatText::m_cKeepText[MAX_KEEPTEXT][SIZE_CHATTEXT] = {};
int				CChatText::m_nCntPress = 0;
int			CChatText::m_nPressKey = 0;

//==========================================================================================================================================================
// ������
//==========================================================================================================================================================
void CChatText::Init(void)
{
	// �f�o�b�O�\���p�t�H���g��ݒ�
	D3DXCreateFont(CManager::GetRenderer()->GetDevice(),	// �f�o�C�X
		CHARACTER_HEIGHT,		// �����̍���
		CHARACTER_WIDTH,		// �����̕�
		CHARACTER_LINE_WEIGHT,	// �����̑���
		0,						// �~�b�v�}�b�v���x���̐�
		FALSE,					// �����̎Α̉�
		SHIFTJIS_CHARSET,		// �t�H���g�̕����Z�b�g
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		CHARACTER_FONTNAME,		// �����̃t�H���g��
		&m_pFont);				// �i�[��

	m_textColor = WhiteColor;
	m_nCntPress = 0;

	// ������̏�����
	for (int nCnt = 0; nCnt < MAX_KEEPTEXT; nCnt++)
	{
		strcpy(m_cKeepText[nCnt], "");
	}
}

//==========================================================================================================================================================
// �I��
//==========================================================================================================================================================
void CChatText::Uninit(void)
{
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
}

//==========================================================================================================================================================
// �\��
//==========================================================================================================================================================
void CChatText::Print(char* fmt, ...)
{
	va_list args;

	// ����܂ł̂��ׂĂ̕��������v�Z
	int nStrLength = (int)strlen(m_aStr);
	// �ǉ��ŕ\�����镶�������v�Z
	int nFmtLehgth = (int)strlen(fmt);
	int nCnt;
	char *pFmt;

	// ���������ő�𒴂�����
	if (nStrLength + nFmtLehgth > MAX_CHARACTER)
	{
		std::cout << "�������z��" << std::endl;
		return;
	}

	// fmt�̏�����
	va_start(args, fmt);

	for (pFmt = (char *)fmt, nCnt = 0; *pFmt != '\0'; pFmt++, nCnt++)
	{
		// fmt�̌^�E�����������肷��
		vsprintf(&m_aStr[nStrLength], fmt, args);
	}

	// args���g���Ȃ���Ԃɂ���
	va_end(args);
}

//==========================================================================================================================================================
// �`��
//==========================================================================================================================================================
void CChatText::Draw(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	// �e�L�X�g�`��
	m_pFont->DrawText(NULL,
		&m_cSendText[0],
		-1,
		&rect,
		DT_LEFT,
		m_textColor);

	// �A�����ĕ������v�Z�����Ȃ��悤\0��u��
	//m_cSendText[0] = '\0';

	CDebugProc::Print(CDebugProc::PLACE_RIGHT, (char*)m_cSendText.c_str());
}

//==========================================================================================================================================================
// �L�[�{�[�h����
//==========================================================================================================================================================
void CChatText::InputText(void)
{
	bool bPress = false;

	// �L�[�{�[�h�̎擾
	CKeyboard *pKey = CManager::GetKeyboard();

	for (int nCnt = 0; nCnt < NUM_KEY_MAX; nCnt++)
	{
		// ������Ă��Ȃ��Ȃ�΁A�I��
		if (pKey->GetPress(nCnt) != true ||
			nCnt == DIK_LSHIFT || nCnt == DIK_RSHIFT)
			continue;

		// ���͂���
		bPress = true;

		// ���̃L�[����͂��Ă�����A�J�E���^���Z�b�g
		if (m_nPressKey != nCnt)
			m_nCntPress = 0;
		// �L�[�ԍ���ۑ�
		m_nPressKey = nCnt;

		// �L�[����
		PressKey(nCnt, (pKey->GetPress(DIK_LSHIFT) || pKey->GetPress(DIK_RSHIFT)));

		// �������J�E���^���Z
		if (m_nCntPress < TIME_PRESSKEY)
			m_nCntPress++;
	}

	if (!bPress)
	{
		m_nCntPress = 0;
		m_nPressKey = 0;
	}

	if (pKey->GetTrigger(DIK_RETURN) && strlen(m_cSendText.c_str()) > 0)
	{
		SendChatText();
	}
}

//==========================================================================================================================================================
// �`���b�g�̃L�[���̐ݒ�
//==========================================================================================================================================================
void CChatText::SetChatKeyInfo(int nKeyID)
{
	switch (nKeyID)
	{
	case DIK_1:				m_cSendText.push_back('1'); break;
	case DIK_2:				m_cSendText.push_back('2'); break;
	case DIK_3:				m_cSendText.push_back('3'); break;
	case DIK_4:				m_cSendText.push_back('4'); break;
	case DIK_5:				m_cSendText.push_back('5'); break;
	case DIK_6:				m_cSendText.push_back('6'); break;
	case DIK_7:				m_cSendText.push_back('7'); break;
	case DIK_8:				m_cSendText.push_back('8'); break;
	case DIK_9:				m_cSendText.push_back('9'); break;
	case DIK_0:				m_cSendText.push_back('0'); break;
	case DIK_A:				m_cSendText.push_back('a'); break;
	case DIK_B:				m_cSendText.push_back('b'); break;
	case DIK_C:				m_cSendText.push_back('c'); break;
	case DIK_D:				m_cSendText.push_back('d'); break;
	case DIK_E:				m_cSendText.push_back('e'); break;
	case DIK_F:				m_cSendText.push_back('f'); break;
	case DIK_G:				m_cSendText.push_back('g'); break;
	case DIK_H:				m_cSendText.push_back('h'); break;
	case DIK_I:				m_cSendText.push_back('i'); break;
	case DIK_J:				m_cSendText.push_back('j'); break;
	case DIK_K:				m_cSendText.push_back('k'); break;
	case DIK_L:				m_cSendText.push_back('l'); break;
	case DIK_M:				m_cSendText.push_back('m'); break;
	case DIK_N:				m_cSendText.push_back('n'); break;
	case DIK_O:				m_cSendText.push_back('o'); break;
	case DIK_P:				m_cSendText.push_back('p'); break;
	case DIK_Q:				m_cSendText.push_back('q'); break;
	case DIK_R:				m_cSendText.push_back('r'); break;
	case DIK_S:				m_cSendText.push_back('s'); break;
	case DIK_T:				m_cSendText.push_back('t'); break;
	case DIK_U:				m_cSendText.push_back('u'); break;
	case DIK_V:				m_cSendText.push_back('v'); break;
	case DIK_W:				m_cSendText.push_back('w'); break;
	case DIK_X:				m_cSendText.push_back('x'); break;
	case DIK_Y:				m_cSendText.push_back('y'); break;
	case DIK_Z:				m_cSendText.push_back('z'); break;
	case DIK_MINUS:			m_cSendText.push_back('-'); break;
	case DIK_CIRCUMFLEX:	m_cSendText.push_back('^'); break;
	case DIK_YEN:			m_cSendText.push_back('\\'); break;
	case DIK_AT:			m_cSendText.push_back('@'); break;
	case DIK_LBRACKET:		m_cSendText.push_back('['); break;
	case DIK_SEMICOLON:		m_cSendText.push_back(';'); break;
	case DIK_COLON:			m_cSendText.push_back(':'); break;
	case DIK_RBRACKET:		m_cSendText.push_back(']'); break;
	case DIK_COMMA:			m_cSendText.push_back(','); break;
	case DIK_PERIOD:		m_cSendText.push_back('.'); break;
	case DIK_SLASH:			m_cSendText.push_back('/'); break;
	case DIK_BACKSLASH:		m_cSendText.push_back('\\'); break;
	case DIK_SPACE:			m_cSendText.push_back(' '); break;
	case DIK_NUMPAD0:		m_cSendText.push_back('0'); break;
	case DIK_NUMPAD1:		m_cSendText.push_back('1'); break;
	case DIK_NUMPAD2:		m_cSendText.push_back('2'); break;
	case DIK_NUMPAD3:		m_cSendText.push_back('3'); break;
	case DIK_NUMPAD4:		m_cSendText.push_back('4'); break;
	case DIK_NUMPAD5:		m_cSendText.push_back('5'); break;
	case DIK_NUMPAD6:		m_cSendText.push_back('6'); break;
	case DIK_NUMPAD7:		m_cSendText.push_back('7'); break;
	case DIK_NUMPAD8:		m_cSendText.push_back('8'); break;
	case DIK_NUMPAD9:		m_cSendText.push_back('9'); break;
	case DIK_DECIMAL:		m_cSendText.push_back('.'); break;
	case DIK_ADD:			m_cSendText.push_back('+'); break;
	case DIK_SUBTRACT:		m_cSendText.push_back('-'); break;
	case DIK_MULTIPLY:		m_cSendText.push_back('*'); break;
	case DIK_DIVIDE:		m_cSendText.push_back('/'); break;
	}
}

//==========================================================================================================================================================
// �`���b�g�̃V�t�g�L�[���̐ݒ�
//==========================================================================================================================================================
void CChatText::SetChatShiftKeyInfo(int nKeyID)
{
	switch (nKeyID)
	{
	case DIK_1:				m_cSendText.push_back('!'); break;
	case DIK_2:				m_cSendText.push_back('"'); break;
	case DIK_3:				m_cSendText.push_back('#'); break;
	case DIK_4:				m_cSendText.push_back('$'); break;
	case DIK_5:				break;
	case DIK_6:				m_cSendText.push_back('&'); break;
	case DIK_7:				break;
	case DIK_8:				m_cSendText.push_back('('); break;
	case DIK_9:				m_cSendText.push_back(')'); break;
	case DIK_0:				break;
	case DIK_A:				m_cSendText.push_back('A'); break;
	case DIK_B:				m_cSendText.push_back('B'); break;
	case DIK_C:				m_cSendText.push_back('C'); break;
	case DIK_D:				m_cSendText.push_back('D'); break;
	case DIK_E:				m_cSendText.push_back('E'); break;
	case DIK_F:				m_cSendText.push_back('F'); break;
	case DIK_G:				m_cSendText.push_back('G'); break;
	case DIK_H:				m_cSendText.push_back('H'); break;
	case DIK_I:				m_cSendText.push_back('I'); break;
	case DIK_J:				m_cSendText.push_back('J'); break;
	case DIK_K:				m_cSendText.push_back('K'); break;
	case DIK_L:				m_cSendText.push_back('L'); break;
	case DIK_M:				m_cSendText.push_back('M'); break;
	case DIK_N:				m_cSendText.push_back('N'); break;
	case DIK_O:				m_cSendText.push_back('O'); break;
	case DIK_P:				m_cSendText.push_back('P'); break;
	case DIK_Q:				m_cSendText.push_back('Q'); break;
	case DIK_R:				m_cSendText.push_back('R'); break;
	case DIK_S:				m_cSendText.push_back('S'); break;
	case DIK_T:				m_cSendText.push_back('T'); break;
	case DIK_U:				m_cSendText.push_back('U'); break;
	case DIK_V:				m_cSendText.push_back('V'); break;
	case DIK_W:				m_cSendText.push_back('W'); break;
	case DIK_X:				m_cSendText.push_back('X'); break;
	case DIK_Y:				m_cSendText.push_back('Y'); break;
	case DIK_Z:				m_cSendText.push_back('Z'); break;
	case DIK_MINUS:			m_cSendText.push_back('='); break;
	case DIK_CIRCUMFLEX:	m_cSendText.push_back('~'); break;
	case DIK_YEN:			m_cSendText.push_back('|'); break;
	case DIK_AT:			m_cSendText.push_back('`'); break;
	case DIK_LBRACKET:		m_cSendText.push_back('{'); break;
	case DIK_SEMICOLON:		m_cSendText.push_back('+'); break;
	case DIK_COLON:			m_cSendText.push_back('*'); break;
	case DIK_RBRACKET:		m_cSendText.push_back('}'); break;
	case DIK_COMMA:			m_cSendText.push_back('<'); break;
	case DIK_PERIOD:		m_cSendText.push_back('>'); break;
	case DIK_SLASH:			m_cSendText.push_back('?'); break;
	case DIK_BACKSLASH:		m_cSendText.push_back('_'); break;
	case DIK_SPACE:			break;
	case DIK_NUMPAD0:		break;
	case DIK_NUMPAD1:		break;
	case DIK_NUMPAD2:		break;
	case DIK_NUMPAD3:		break;
	case DIK_NUMPAD4:		break;
	case DIK_NUMPAD5:		break;
	case DIK_NUMPAD6:		break;
	case DIK_NUMPAD7:		break;
	case DIK_NUMPAD8:		break;
	case DIK_NUMPAD9:		break;
	case DIK_DECIMAL:		break;
	case DIK_ADD:			break;
	case DIK_SUBTRACT:		break;
	case DIK_MULTIPLY:		break;
	case DIK_DIVIDE:		break;
	}
}

//==========================================================================================================================================================
// �L�[����
//==========================================================================================================================================================
void CChatText::PressKey(int nKeyID, bool bShift)
{
	// �V�t�g�L�[���L��
	if (bShift)
	{
		// �P������
		if (m_nCntPress == 1)
			SetChatShiftKeyInfo(nKeyID);
		// �A������
		if (m_nCntPress >= TIME_PRESSKEY)
			SetChatShiftKeyInfo(nKeyID);
		// �������I����
		return;
	}

	if (nKeyID != DIK_BACKSPACE)
	{
		// �P������
		if (m_nCntPress == 1)
			SetChatKeyInfo(nKeyID);
		// �A������
		if (m_nCntPress >= TIME_PRESSKEY)
			SetChatKeyInfo(nKeyID);
	}
	else
	{
		// �P������
		if (m_nCntPress == 1 && m_cSendText.size() > 0)
			m_cSendText.pop_back();
		// �A������
		if (m_nCntPress >= TIME_PRESSKEY && m_cSendText.size() > 0)
			m_cSendText.pop_back();
	}
}

//==========================================================================================================================================================
// ���b�Z�[�W�̑��M
//==========================================================================================================================================================
void CChatText::SendChatText(void)
{
	// ���X�̕������������ɂ��炷
	for (int nCnt = MAX_KEEPTEXT - 1; nCnt > -1; nCnt--)
	{
		// �������i�[����Ă���Ȃ�A�������Ȃ�
		if (strlen(m_cKeepText[nCnt]) > 0)
			continue;

		// �����͏���
		if (nCnt == MAX_KEEPTEXT - 1)
			strcpy(m_cKeepText[nCnt], "");
		// �����ȊO�́A���̕�������i�[
		else
			strcpy(m_cKeepText[nCnt + 1], m_cKeepText[nCnt]);
	}

	// �擪�̕�������㏑��
	strcpy(m_cKeepText[0], m_cSendText.c_str());
	// ���M
	std::thread t2(CClient::Send, (char*)m_cSendText.c_str());
	t2.detach();

	// �`���b�g�^�u�ɕۑ�
	CChatTab::AddTextBox((char*)m_cSendText.c_str());
	// �������j��
	m_cSendText.clear();
}
