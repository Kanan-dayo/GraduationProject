// ===================================================================
//
// �ڑ���UI���� [ connectUI.h ]
// Author : KANAN NAGANAWA
//
// ===================================================================
#ifndef _CONNECTUI_H_
#define _CONNECTUI_H_

#define _CRT_SECURE_NO_WARNINGS // �x������

// ===================================================================
// �C���N���[�h�t�@�C��
// ===================================================================
#include "main.h"
#include "connectBase.h"
#include "Mylibrary.h"

// ===================================================================
// �}�N����`
// ===================================================================

// ===================================================================
// �N���X��`
// ===================================================================
class CPolygon2D;
class CMouse;

class CConnectUI
{
public:
	typedef enum
	{	// 1P2P�����Ŏg��UI
		CONNECTUI_BOTH_BACK,				// �w�i
		CONNECTUI_BOTH_LOADICON,			// ���[�h�A�C�R��
		CONNECTUI_BOTH_STATE_CONNECTING,	// �ڑ���
		CONNECTUI_BOTH_STATE_CONNECTED,		// �ڑ�����
		CONNECTUI_BOTH_STATE_SELECTING,		// �I��
		CONNECTUI_BOTH_STATE_SELECTED,		// �I������
		CONNECTUI_BOTH_SELECT_MODE,			// �I�� ���[�h
		CONNECTUI_BOTH_SELECT_LEVEL,		// �I�� ���x��
		CONNECTUI_BOTH_MODE_REMOVE,			// ���[�h ����
		CONNECTUI_BOTH_MODE_SOLVE,			// ���[�h ���
		CONNECTUI_BOTH_LEVEL_EASY,			// ��Փx �C�[�W�[
		CONNECTUI_BOTH_LEVEL_NORMAL,		// ��Փx �m�[�}��
		CONNECTUI_BOTH_LEVEL_HARD,			// ��Փx �n�[�h
		CONNECTUI_BOTH_MAX
	} CONNECTUITYPE_BOTH;

	typedef enum
	{	// ������g��UI
		CONNECTUI_ONLY_BUTTON_DESIDE,	// ����{�^��
		CONNECTUI_ONLY_COMMENT_REMOVE,	// �R�����g ����
		CONNECTUI_ONLY_COMMENT_SOLVE,	// �R�����g ���
		CONNECTUI_ONLY_COMMENT_EASY,	// �R�����g �C�[�W�[
		CONNECTUI_ONLY_COMMENT_NORMAL,	// �R�����g �m�[�}��
		CONNECTUI_ONLY_COMMENT_HARD,	// �R�����g �n�[�h
		CONNECTUI_ONLY_CAUTION_MODE,	// ���[�h�I���̒���
		CONNECTUI_ONLY_CAUTION_LEVEL,	// ���x���I���̒���
		CONNECTUI_ONLY_MAX
	} CONNECTUITYPE_ONLY;

	typedef enum
	{	// �ڑ����[�h�̃t���[
		CONNECTFLOW_CONNECTING = 0,	// �ڑ���
		CONNECTFLOW_CONNECTED,		// �ڑ�����
		CONNECTFLOW_SELECT_MODE,	// ���[�h�I��
		CONNECTFLOW_SELECT_LEVEL,	// ��Փx�I��
		CONNECTFLOW_END
	} CONNECTFLOW_TYPE;

	typedef enum
	{	// �t���[�̏�ԊǗ�
		FLOWSTATE_BEGIN,	// �J�n��
		FLOWSTATE_NORMAL,	// �ʏ펞
		FLOWSTATE_END,		// �I����
		FLOWSTATE_WAIT,		// �҂����
	} FLOW_STATE;

	typedef struct
	{	// UI�̏��
		D3DXVECTOR2 pos;			// ���W
		D3DXVECTOR2 size;			// �T�C�Y
		D3DXCOLOR color;			// �J���[
	} CONNECTUI_INFO;

	typedef enum
	{
		PLAYER_ONE = 0,	// �v���C���[1
		PLAYER_TWO,		// �v���C���[2
		PLAYER_MAX		// �ő�v���C���[
	} NUM_PLAYER;

	typedef enum
	{	// �I�����Ă��郂�[�h
		SELECTMODE_NONE = 0,	// �����Ȃ�
		SELECTMODE_REMOVE,		// ����
		SELECTMODE_SOLVE,		// ���
		SELECTMODE_MAX
	} SELECTMODE;

	typedef enum
	{	// �I�����Ă��郌�x��
		SELECTLEVEL_NONE = 0,	// �����Ȃ�
		SELECTLEVEL_EASY,		// �C�[�W�[
		SELECTLEVEL_NORMAL,		// �m�[�}��
		SELECTLEVEL_HARD,		// �n�[�h
		SELECTLEVEL_MAX
	} SELECTLEVEL;

	CConnectUI();						// �R���X�g���N�^
	~CConnectUI();						// �f�X�g���N�^

	HRESULT Init(void);					// ������
	void Update(void);					// �X�V
	void Draw(void);					// �`��
	void ShowDebugInfo() {};			//�f�o�b�O���\�L

	static CConnectUI * Create(void);	// ����
	static HRESULT Load(void);			// ���[�h

	static void SetGuestMode(SELECTMODE mode);
	static void SetGuestLevel(SELECTLEVEL level);
	static void EnableGuestWait(void) { m_bGuestWait = true; }

private:
	static void ReadFromLine(CONST_STRING cnpLine, CONST_STRING cnpEntryType, CONST_STRING cnpEntryData);
	static void SetBothInfo(CONST_STRING str, CONST_STRING type);
	static void SetOnlyInfo(CONST_STRING str, CONST_STRING type);

	static CPolygon2D *CreateBothUI(int nPlayer, CONNECTUITYPE_BOTH type);
	CPolygon2D *CreateOnlyUI(CONNECTUITYPE_ONLY type);
	static void DeleteBothUI(int nPlayer, CONNECTUITYPE_BOTH type);
	void DeleteOnlyUI(CONNECTUITYPE_ONLY type);

	void Connecting(void);									// �ڑ����̏���
	void CheckConnect(void);
	void Connected(void);									// �ڑ��������̏���
	void SelectMode(void);									// ���[�h�̑I������
	void SelectLevel(void);									// ���x���̑I������

	void Begin(CONNECTFLOW_TYPE flow);						// �t���[���Ƃ̊J�n���̏���
	void End(CONNECTFLOW_TYPE flow);						// �t���[���Ƃ̏I�����̏���
	void Wait(CONNECTFLOW_TYPE flow);						// �t���[���Ƃ̑҂���Ԃ̏���

	void LoadIconAnim(void);								// ���[�h�A�C�R���̃A�j���[�V��������
	void ButtonAnim(void);									// �{�^���̃A�j���[�V��������
	void CheckSameMode(void);								// �������[�h��I�����Ă��Ȃ����m�F����
	void ClickDecide(CMouse *pMouse);						// ����{�^��������

	static CPolygon2D *m_pUIBoth[2][CONNECTUI_BOTH_MAX];	// �����Ŏg��UI�̃|�C���^
	static CPolygon2D *m_pUIOnly[CONNECTUI_ONLY_MAX];		// ������g��UI�̃|�C���^
	static CONNECTUI_INFO m_UIInfoBoth[2][CONNECTUI_BOTH_MAX];	// �����Ŏg��UI�̏��
	static CONNECTUI_INFO m_UIInfoOnly[CONNECTUI_ONLY_MAX];		// ������g��UI�̏��

	int m_nCntAnim;
	int m_nCntPattern;
	int m_nCntState;

	static CONNECTFLOW_TYPE m_flow;				// �ڑ����[�h�̃t���[
	FLOW_STATE m_state;							// �t���[�̏��

	bool m_bConnect[PLAYER_MAX];				// �ڑ��̃t���O
	static int m_nSelectMode[PLAYER_MAX];		// �v���C���[���I�𒆂̔ԍ�
	static int m_nSelectLevel[PLAYER_MAX];		// �v���C���[���I�𒆂̔ԍ�
	static bool m_bGuestWait;					// �Q�X�g�̑҂���Ԃ̃t���O
};

#endif
