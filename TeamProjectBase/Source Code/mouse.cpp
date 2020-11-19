//*************************************************************************************************************
//
// �}�E�X���͏��� [mouse.cpp]
// Author:IKUTO SEKINE
//
//*************************************************************************************************************
//-------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------------------
#include "mouse.h"
#include "keyboard.h"
#include "manager.h"

//-------------------------------------------------------------------------------------------------------------
// �ÓI�����o�ϐ��̏�����
//-------------------------------------------------------------------------------------------------------------
CMouse::MOUSE_SCROLL CMouse::m_scroll = SCROLL_NONE;	// �}�E�X�̃X�N���[���̏��

//-------------------------------------------------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------------------------------------------------
CMouse::CMouse()
{
}

//-------------------------------------------------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------------------------------------------------
CMouse::~CMouse()
{
}

//-------------------------------------------------------------------------------------------------------------
// ������
//-------------------------------------------------------------------------------------------------------------
HRESULT CMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);
	m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL);

	m_pDevice->SetDataFormat(&c_dfDIMouse2); // �}�E�X�p�̃f�[�^�E�t�H�[�}�b�g��ݒ�

	m_pDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	// �f�o�C�X�̐ݒ�
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL; // ���Βl���[�h�Őݒ�i��Βl��DIPROPAXISMODE_ABS�j
	m_pDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph);

	// ���͐���J�n
	m_pDevice->Acquire();

	// ���
	m_hWnd = hWnd;

	// �J�[�\����\��
	ShowCursor(TRUE);

	m_hCursor[CUR_PEN] = LoadCursorFromFile("data/TEXTURE/CUR/pen.cur"); 
	m_hCursor[CUR_ERASER] = LoadCursorFromFile("data/TEXTURE/CUR/eraser.cur");

	m_type = CURTYPE::CUR_NONE;

	m_bDisp = false;

	return S_OK;
}

//-------------------------------------------------------------------------------------------------------------
// �X�V����
//-------------------------------------------------------------------------------------------------------------
void CMouse::Update(void)
{
	// �{�^���̏�����
	m_mouse.state.rgbButtons[0] = 0;

	// �}�E�X�̍��W���擾
	GetCursorPos(&m_mouse.point);
	ScreenToClient(m_hWnd, &m_mouse.point);

	// �l�̍X�V
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE2), &m_mouse.state)))
	{
		for (int nCntButton = 0; nCntButton < NUM_BUTTON_MAX; nCntButton++)
		{
			// �r���I�_���a���ǂ������f
			m_aButtonStateTrigger[nCntButton] = (m_aButtonState[nCntButton] ^ m_mouse.state.rgbButtons[nCntButton]) & m_mouse.state.rgbButtons[nCntButton];
			m_aButtonStateRelease[nCntButton] = (m_aButtonState[nCntButton] ^ m_mouse.state.rgbButtons[nCntButton]) & m_aButtonState[nCntButton];
			// �L�[�v���X���ۑ�
			m_aButtonState[nCntButton] = m_mouse.state.rgbButtons[nCntButton];
		}
	}
	else
	{
 		m_pDevice->Acquire();
	}

}

//-------------------------------------------------------------------------------------------------------------
// �`�揈��
//-------------------------------------------------------------------------------------------------------------
void CMouse::Draw(void)
{
	if (m_type == CURTYPE::CUR_NONE ||
		m_bDisp == false)
	{
		return;
	}
	// �J�[�\���n���h���̐ݒ�
	SetCursor(m_hCursor[m_type]);
}

//-------------------------------------------------------------------------------------------------------------
// �X�N���[�������l���擾����
//-------------------------------------------------------------------------------------------------------------
int CMouse::GetScrollValue(void)
{
	switch (m_scroll)
	{
		MLB_CASE(SCROLL_NONE) return 0;			// �X�N���[�����Ă��Ȃ�
		MLB_CASE(SCROLL_UP)   return 1;			// ��ɃX�N���[��
		MLB_CASE(SCROLL_DOWN) return -1;		// ���ɃX�N���[��
		MLB_CASEEND;
	}
	return 0;
}
