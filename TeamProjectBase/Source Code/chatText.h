// ===================================================================
//
// �`���b�g�p�e�L�X�g���� [ chatText.h ]
// Author : KANAN NAGANAWA
//
// ===================================================================
#ifndef _CHATTEXT_H_
#define _CHATTEXT_H_

#define _CRT_SECURE_NO_WARNINGS // �x������

// ===================================================================
// �C���N���[�h�t�@�C��
// ===================================================================
#include <stdarg.h>
#include <assert.h>
#include "main.h"
#include "dinput.h"

// ===================================================================
// �}�N����`
// ===================================================================
#define MAX_CHARACTER		(2048)	// �����̍ő吔
#define MAX_KEEPTEXT		(20)	// �ێ��ł���e�L�X�g�̍ő吔
#define SIZE_CHATTEXT		(256)	// �`���b�g�e�L�X�g�̍ő�T�C�Y

// ===================================================================
// �N���X��`
// ===================================================================
class CPolygon2D;
class CKeyboard;

class CChatText
{
public:
	CChatText() {};		// �R���X�g���N�^
	~CChatText() {};	// �f�X�g���N�^

	void Init(void);				// ������
	void Uninit(void);				// �I��
	static void Draw(void);			// �`��
	void ShowDebugInfo() {};		//�f�o�b�O���\�L

	D3DXCOLOR &GetTextColor(void) { return m_textColor; } // �e�L�X�g�J���[�̎擾
	void SetTextColor(D3DXCOLOR &col) { m_textColor = col; } // �e�L�X�g�J���[�̐ݒ�

	static void InputText(void);
	static void SetChatKeyInfo(int nKeyID);
	static void SetChatShiftKeyInfo(int nKeyID);
	static void PressKey(int nKeyID, bool bShift);

private:
	static LPD3DXFONT	m_pFont;				// �t�H���g���i�[�p
	static char			m_aStr[MAX_CHARACTER];	// �e�L�X�g�̊i�[�p�z��
	static char			m_cKeepText[MAX_KEEPTEXT][SIZE_CHATTEXT];	// �ێ��ł���e�L�X�g
	static std::string	m_cSendText;			// ���邽�߂̕�����
	static D3DXCOLOR	m_textColor;			// �e�L�X�g�̃J���[
	static int			m_nCntPress;			// �������̃J�E���^
	static int			m_nPressKey;
};

#endif