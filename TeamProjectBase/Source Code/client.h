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
		ORDER_GUEST_BE_ACCEPT,	// �ڑ�����
		ORDER_SENDTEXT,			// �e�L�X�g���M
		ORDER_SENDPICTURE,		// �s�N�`�����M
		ORDER_SENDSELECT,		// �I���𑗐M
		ORDER_SENDWAIT,			// �҂���Ԃ̑��M
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

	typedef struct
	{	// �\�P�b�g���
		char ip_Addr[64];	// IP�A�h���X
		u_short port;		// �|�[�g�ԍ�
	} SOCKINFO;

	CClient() {};	// �R���X�g���N�^
	~CClient() {};		// �f�X�g���N�^

	static HRESULT LoadIP(void);		// IP�A�h���X�̃��[�h
	static int ConnectServer(void);		// �T�[�o�[�ڑ�����
	static void WaitRecieve(void);		// ��M�҂�����
	static HRESULT InitClient(void);	// ������
	static void UninitClient(void);		// �����I��

#ifdef _DEBUG
	static void ErrorReport(void);		// �G���[���|�[�g
#endif

	static bool &GetAccept(void)					{ return m_bAccept; }		// �ڑ��̎擾
	static bool &GetAcceptOther(void)				{ return m_bAcceptOther; }	// ��������̃v���C���[�̐ڑ��̎擾
	static CLIENTSTATE &GetClientState(void)		{ return m_state; }			// ��Ԃ̎擾
	static void SetAccepting(bool bAccept)			{ m_bAccept = bAccept; }	// �ڑ��̐ݒ�
	static void SetClientState(CLIENTSTATE state)	{ m_state = state; }		// ��Ԃ̐ݒ�

	static void SendText(void);													// ���͂̑��M
	static void SendPicture(void);												// �s�N�`���̑��M
	static void RecvText(char *data);											// ���͂̎�M
	static void RecvPicture(char *data);										// �s�N�`���̎�M
	static void SendSelect(int nSelect);										// �I���̑��M
	static void RecvSelect(char *data);											// �I���̎�M
	static void SendWait(void);													// �҂���Ԃ̑��M
	static void RecvWait(void);													// �҂���Ԃ̎�M

private:
	static CLIENTSTATE m_state;			// �N���C�A���g�̏��
	static bool m_bAccept;			// �N���C�A���g�󂯓���̃t���O
	static bool m_bAcceptOther;		// ��������̃v���C���[�̐ڑ��t���O
	static SOCKET m_socket;				// �ʐM�Ɏg���\�P�b�g
	static SOCKINFO m_sockInfo;			// �\�P�b�g�̏��
};

#endif
