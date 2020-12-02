// ===================================================================
//
// �N���C�A���g���� [ client.h ]
// Author : KANAN NAGANAWA
//
// ===================================================================
#ifndef _CLIENT_H_
#define _CLIENT_H_

#define _CRT_SECURE_NO_WARNINGS // �x������

// ===================================================================
// �C���N���[�h�t�@�C��
// ===================================================================
#include "main.h"
#include "Mylibrary.h"

// ===================================================================
// �}�N����`
// ===================================================================

// ===================================================================
// �N���X��`
// ===================================================================
class CClient
{
public:
	typedef enum
	{
		ORDER_NONE = 0,	// �w���Ȃ�
		ORDER_SENDTEXT = 1,		// �e�L�X�g���M
		ORDER_SENDPICTURE,		// �s�N�`�����M
	} SERVER_ORDER;

	typedef enum
	{
		CLIENT_CONNECT,	// �ڑ�
		CLIENT_CLOSE,	// �ڑ������
	} CLIENTSTATE;

	typedef enum
	{
		SEND_OBJECT,	// ���M���镨�̃^�C�v
		SEND_DATA,		// ���M����f�[�^
		SEND_MAX
	} SENDINFO;

	CClient() {};	// �R���X�g���N�^
	~CClient() {};		// �f�X�g���N�^

	static int ConnectServer(void);		// �T�[�o�[�ڑ�����
	static void WaitRecieve(void);		// ��M�҂�����
	static HRESULT InitClient(void);	// ������
	static void UninitClient(void);		// �����I��

#ifdef _DEBUG
	static void ErrorReport(void);		// �G���[���|�[�g
#endif

	static bool &GetAccepting(void)					{ return m_bConnecting; }		// �ڑ��̎擾
	static CLIENTSTATE &GetClientState(void)		{ return m_state; }				// ��Ԃ̎擾
	static void SetAccepting(bool bConnect)			{ m_bConnecting = bConnect; }	// �ڑ��̐ݒ�
	static void SetClientState(CLIENTSTATE state)	{ m_state = state; }			// ��Ԃ̐ݒ�
	static void SendText(void);														// ���͂̑��M
	static void SendPicture(void);													// �s�N�`���̑��M
	static void RecvText(char *data);												// ���͂̎�M
	static void RecvPicture(char *data);											// �s�N�`���̎�M

private:
	static CLIENTSTATE m_state;			// �N���C�A���g�̏��
	static bool m_bConnecting;			// �N���C�A���g�󂯓���̃t���O
	static SOCKET m_socket;				// �ʐM�Ɏg���\�P�b�g
};

#endif
