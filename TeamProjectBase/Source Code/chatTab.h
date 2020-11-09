// ===================================================================
//
// �`���b�g�̃^�u���� [ chatTab.h ]
// Author : KANAN NAGANAWA
//
// ===================================================================
#ifndef _CHATTAB_H_
#define _CHATTAB_H_

#define _CRT_SECURE_NO_WARNINGS // �x������

// ===================================================================
// �C���N���[�h�t�@�C��
// ===================================================================
#include "main.h"
#include "chatBase.h"

// ===================================================================
// �}�N����`
// ===================================================================

// ===================================================================
// �N���X��`
// ===================================================================
class CPolygon2D;
class CChatText;

class CChatTab : public CChatBase
{
public:
	typedef struct
	{	// �`���b�g�L�[�v�̏��
		CChatText *pKeepText;
		CPolygon2D *pPolyBack;
	} CHATKEEP;

	typedef enum
	{	// �`���b�g�^�u�̃e�N�X�`���^�C�v
		CHATTAB_BACK,	// �w�i
		CHATTAB_OPEN,	// �J��
		CHATTAB_CLOSE,	// ����
		CHATTAB_MAX
	} CHATTAB_TEXTYPE;

	typedef enum
	{	// �^�u�̏��
		TABSTATE_NONE,		// �����Ȃ�
		TABSTATE_CLOSING,	// ������
		TABSTATE_CLOSED,	// �������
		TABSTATE_OPENNING,	// �J�����
		TABSTATE_OPENED,	// �J�������
		TABSTATE_MAX
	} TABSTATE;

	CChatTab();
	~CChatTab();

	HRESULT Init(void);			// ������
	void Update(void);			// �X�V
	void Draw(void);			// �`��
	void ShowDebugInfo() {};		//�f�o�b�O���\�L

	static CChatTab * Create(void);	// ����

	static D3DXVECTOR2 &GetTabPos(void)			{ return m_TabPos; }			// �^�u���W�̎擾
	static TABSTATE &GetTabState(void)			{ return m_tabState; }			// �^�u�̏�Ԃ̎擾
	static CHATKEEP *GetChatKeep(int nIndex)	{ return &m_chatKeep[nIndex]; }	// �e�L�X�g�̔w�i�|���S���擾
	static void SetTabPos(D3DXVECTOR2 &pos)		{ m_TabPos = pos; }				// �^�u���W�̐ݒ�
	static int AddTextBox(int nIndex);											// �e�L�X�g�{�b�N�X�ǉ�
	static void InputText(void);
	static void PressKey(int nKeyID, bool bShift);
	static void SetChatKeyInfo(int nKeyID);
	static void SetChatShiftKeyInfo(int nKeyID);
	static void SendChatText(void);
	static void RecvChatText(void);

private:
	void ClickTab(void);	// �^�u�N���b�N
	void SlideTab(void);	// �^�u�X���C�h
	static void CreateKeep(TEXTOWNER owner);	// �`���b�g�L�[�v�̐���

	CPolygon2D	*m_pPolyBack;		// �w�i�^�u�̃|���S��
	CPolygon2D	*m_pPolyTab;		// �J�^�u�̃|���S��
	static CChatText	*m_pChatText;		// �e�L�X�g
	static TABSTATE m_tabState;		// �^�u�̏��
	int m_nCntState;				// ��ԊǗ��̃J�E���^
	static D3DXVECTOR2 m_TabPos;	// �^�u�̐e���W
	D3DXVECTOR2 m_moveDest;			// �^�u�ړ��̗�
	static int			m_nCntPress;				// �������̃J�E���^
	static int			m_nPressKey;
	static std::vector<CHATKEEP>	m_chatKeep;	// �ێ��ł���e�L�X�g
	static CChatText	*m_leftText;					// �c�莞����\������e�L�X�g
	static CChatText	*m_SendText;				// ����e�L�X�g
};

#endif
