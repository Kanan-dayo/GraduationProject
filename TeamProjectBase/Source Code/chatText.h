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

	void Init(void);					// ������
	void Uninit(void);					// �I��
	void Update(void);			// �X�V
	void Draw(void);				// �`��
	void ShowDebugInfo() {};			//�f�o�b�O���\�L

	static CChatText *Create(void);
	static HRESULT LoadFont(void);
	static void UnloadFont(void);

	// �e�L�X�g�̎擾
	std::string &GetChatText(void) { return m_text; }
	// �e�L�X�g�̐ݒ�
	void SetChatText(char *cText) 
	{ 
		m_text.clear();
		m_text = cText; 
	}
	// �ێ�����e�L�X�g�̈ʒu�ݒ�
	void SetKeepRectBegin(D3DXVECTOR2 rectBegin)
	{ m_rect = { (LONG)rectBegin.x, (LONG)rectBegin.y, SCREEN_WIDTH, SCREEN_HEIGHT }; }
	RECT GetRect(void)
	{ return m_rect; }
	// �ێ�����e�L�X�g�̃J���[�ݒ�
	void SetKeepColor(D3DXCOLOR col)
	{ m_col = col; }

private:
	static LPD3DXFONT	m_pFont;	// �t�H���g���i�[�p
	int			m_nIndex;
	std::string m_text;
	RECT		m_rect;
	int			m_nLine;
	D3DXCOLOR	m_col;
};

#endif