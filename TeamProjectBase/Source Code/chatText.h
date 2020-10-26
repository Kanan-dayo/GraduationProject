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
class CChatText
{
public:
	typedef enum
	{	// �L�[
		// ����
		CHATKEY_0, CHATKEY_1, CHATKEY_2, CHATKEY_3, CHATKEY_4,
		CHATKEY_5, CHATKEY_6, CHATKEY_7, CHATKEY_8, CHATKEY_9,
		// �A���t�@�x�b�g
		CHATKEY_A, CHATKEY_B, CHATKEY_C, CHATKEY_D, CHATKEY_E,
		CHATKEY_F, CHATKEY_G, CHATKEY_H, CHATKEY_I, CHATKEY_J,
		CHATKEY_K, CHATKEY_L, CHATKEY_M, CHATKEY_N, CHATKEY_O,
		CHATKEY_P, CHATKEY_Q, CHATKEY_R, CHATKEY_S, CHATKEY_T,
		CHATKEY_U, CHATKEY_V, CHATKEY_W, CHATKEY_X, CHATKEY_Y,
		CHATKEY_Z,
		// �L��
		CHATEKY_DASH,					// -
		CHATEKY_CIRCUMFLEX_ACCENT,		// ^
		CHATEKY_YEN,					// \�}�[�N
		CHATEKY_AT,						// @
		CHATEKY_LEFT_SQUARE_BRACKET,	// [
		CHATEKY_SEMICOLON,				// ;
		CHATEKY_COLON,					// :
		CHATEKY_RIGHT_SQUARE_BRACKET,	// ]
		CHATEKY_COMMA,					// ,
		CHATEKY_FULL_STOP,				// .
		CHATEKY_SOLIDUS,				// /
		CHATEKY_BACK_SOLIDUS,			// \�}�[�N
		CHATKEY_SPACE,					// �� �X�y�[�X�L�[
		// �e���L�[
		CHATKEY_NUMKEY_0, CHATKEY_NUMKEY_1, CHATKEY_NUMKEY_2, CHATKEY_NUMKEY_3, CHATKEY_NUMKEY_4,
		CHATKEY_NUMKEY_5, CHATKEY_NUMKEY_6, CHATKEY_NUMKEY_7, CHATKEY_NUMKEY_8, CHATKEY_NUMKEY_9,
		CHATKEY_NUMKEY_FULL_STOP,		// . (�e���L�[)
		CHATKEY_NUMKEY_SOLIDUS,			// / (�e���L�[)
		CHATKEY_NUMKEY_ASTERISK,		// * (�e���L�[)
		CHATKEY_NUMKEY_DASH,			// - (�e���L�[)
		CHATKEY_NUMKEY_PLUS,			// + (�e���L�[)
		CHATKEY_MAX
	} CHATKEY;

	typedef enum
	{	// �L�[ + Shift
		// ����
		CHATKEY_SHIFT_EXCLAMATION,			// !
		CHATKEY_SHIFT_BOUBLE_QUOTATION,		// "
		CHATKEY_SHIFT_HASH,					// #
		CHATKEY_SHIFT_DOLLAR,				// $
		CHATKEY_SHIFT_PERCENT,				// %
		CHATKEY_SHIFT_AMPERSAND,			// &
		CHATKEY_SHIFT_QUOTATION,			// '
		CHATKEY_SHIFT_LEFT_PARENTHESIS,		// (
		CHATKEY_SHIFT_RIGHT_PARENTHESIS,	// )
		// �A���t�@�x�b�g
		CHATKEY_SHIFT_A, CHATKEY_SHIFT_B, CHATKEY_SHIFT_C, CHATKEY_SHIFT_D, CHATKEY_SHIFT_E,
		CHATKEY_SHIFT_F, CHATKEY_SHIFT_G, CHATKEY_SHIFT_H, CHATKEY_SHIFT_I, CHATKEY_SHIFT_J,
		CHATKEY_SHIFT_K, CHATKEY_SHIFT_L, CHATKEY_SHIFT_M, CHATKEY_SHIFT_N, CHATKEY_SHIFT_O,
		CHATKEY_SHIFT_P, CHATKEY_SHIFT_Q, CHATKEY_SHIFT_R, CHATKEY_SHIFT_S, CHATKEY_SHIFT_T,
		CHATKEY_SHIFT_U, CHATKEY_SHIFT_V, CHATKEY_SHIFT_W, CHATKEY_SHIFT_X, CHATKEY_SHIFT_Y,
		CHATKEY_SHIFT_Z,
		// �L��
		CHATEKY_SHIFT_EQUAL,				// =
		CHATEKY_SHIFT_TILDE,				// ~
		CHATEKY_SHIFT_VERTICAL_LINE,		// |
		CHATEKY_SHIFT_GRAVE_ACCENT,			// `
		CHATEKY_SHIFT_LEFT_CURLY_BRACKET,	// {
		CHATEKY_SHIFT_PLUS,					// +
		CHATEKY_SHIFT_ASTERISK,				// *
		CHATEKY_SHIFT_RIGHT_CURLY_BRACKET,	// }
		CHATEKY_SHIFT_LESS_THAN,			// <
		CHATEKY_SHIFT_GREATER_THAN,			// >
		CHATEKY_SHIFT_QUESTION,				// ?
		CHATEKY_SHIFT_UNDER_LINE,			// _
		CHATKEY_SHIFT_MAX
	} CHATKEY_SHIFT;

	CChatText() {};		// �R���X�g���N�^
	~CChatText() {};	// �f�X�g���N�^

	void Init(void);					// ������
	void Uninit(void);					// �I��
	void static Print(char* fmt, ...);	// �e�L�X�g�̐ݒ� (������...�ɂ���Ή��ł��󂯎���)
	void Draw(void);				// �`��
	void ShowDebugInfo() {};		//�f�o�b�O���\�L

	D3DXCOLOR &GetTextColor(void) { return m_textColor; } // �e�L�X�g�J���[�̎擾
	void SetTextColor(D3DXCOLOR &col) { m_textColor = col; } // �e�L�X�g�J���[�̐ݒ�

private:
	static LPD3DXFONT	m_pFont;				// �t�H���g���i�[�p
	static char			m_aStr[MAX_CHARACTER];	// �e�L�X�g�̊i�[�p�z��
	char				m_cKeepText[MAX_KEEPTEXT][SIZE_CHATTEXT];	// �ێ��ł���e�L�X�g
	D3DXCOLOR			m_textColor;			// �e�L�X�g�̃J���[
};

#endif