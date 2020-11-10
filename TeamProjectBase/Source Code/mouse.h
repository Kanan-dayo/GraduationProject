//*************************************************************************************************************
//
// �}�E�X���� [mouse.h]
// Author:IKUTO SEKINE
//
//*************************************************************************************************************
#ifndef _MOUSE_H_
#define _MOUSE_H_

#define _CRT_SECURE_NO_WARNINGS

//-------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------------------
#include "main.h"
#include "input.h"

//-------------------------------------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------------------------------------
#define	NUM_BUTTON_MAX			(8)		// �{�^��(�}�E�X)�̍ő吔

//-------------------------------------------------------------------------------------------------------------
// �N���X�̒�`
//-------------------------------------------------------------------------------------------------------------
class CMouse :public CInput
{
public:
	/* �񋓌^��` */
	typedef enum
	{
		CUR_NONE = -1,	// ����
		CUR_PEN,		// �y��
		CUR_ERASER,		// �����S��
		CUR_MAX			// �ő吔
	}CURTYPE;

	/* �\���̒�` */
	typedef struct
	{
		DIMOUSESTATE2 state;	// ���
		POINT         point;		// �ʒu
	} MOUSE;

	/* �����o�֐� */
	CMouse();
	~CMouse();
	HRESULT              Init(HINSTANCE hInstance, HWND hWnd);
	void                 Update(void);
	void                 Draw(void);

	// �ݒ�֐�
	inline void          SetCursorType(CONST CURTYPE type) { if (m_type != type)m_type = type; }					// �J�[�\���^�C�v�̐ݒ�
	inline void          SetDisp(bool bDisp) { if (m_bDisp != bDisp)m_bDisp = bDisp; }								// �`��t���O�̐ݒ�

	// �擾�֐�
	inline bool          GetPress(int nButton) { return (m_aButtonState[nButton] & 0x80) ? true : false; }			// �����Ă���Ƃ�
	inline bool          GetTrigger(int nButton) { return (m_aButtonStateTrigger[nButton] & 0x80) ? true : false; }	// ��������
	inline bool          GetRelease(int nButton) { return (m_aButtonStateRelease[nButton] & 0x80) ? true : false; }	// ��������
	inline LONG          GetMouseX(void) { return m_mouse.point.x; }												// �}�E�XX��
	inline LONG          GetMouseY(void) { return m_mouse.point.y; }												// �}�E�XY��
	inline POINT         GetMousePoint(void) { return m_mouse.point; }												// �}�E�X�̈ʒu
	inline DIMOUSESTATE2 GetMouseState(void) { return m_mouse.state; }												// �}�E�X�̏�Ԃ̎擾

private:
	/* �����o�ϐ� */
	LPDIRECTINPUTDEVICE8 m_pDevice;								// �f�o�C�X
	MOUSE                m_mouse;								// �}�E�X�̏��
	BYTE                 m_aButtonState[NUM_BUTTON_MAX];		// �}�E�X�̓��͏�񃏁[�N
	BYTE                 m_aButtonStateTrigger[NUM_BUTTON_MAX];	// �}�E�X�̃g���K�[
	BYTE                 m_aButtonStateRelease[NUM_BUTTON_MAX];	// ��������
	HWND                 m_hWnd;								// �E�B���h�E�n���h��
	HCURSOR              m_hCursor[CUR_MAX];					// �J�[�\���n���h��
	CURTYPE              m_type;								// �J�[�\���^�C�v
	bool                 m_bDisp;								// �`�悵���t���O
};

#endif
