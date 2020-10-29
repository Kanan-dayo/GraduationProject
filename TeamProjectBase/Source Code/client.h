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

// ===================================================================
// �}�N����`
// ===================================================================

// ===================================================================
// �N���X��`
// ===================================================================
class CClient
{
public:
	CClient() {};	// �R���X�g���N�^
	~CClient() {};		// �f�X�g���N�^

	static int main(void);				// ���C������
	static HRESULT InitClient(void);	// ������
	static void UninitClient(void);		// �����I��
	static void ErrorReport(void);	// �G���[���|�[�g

	static bool &GetAccepting(void) { return m_bConnecting; }
	static void SetAccepting(bool bConnect) { m_bConnecting = bConnect; }
	static void Send(char* cSendText);
private:
	static bool m_bConnecting;			// �N���C�A���g�󂯓���̃t���O
	static char m_cSendText[256];		// ����e�L�X�g
	static SOCKET m_socket;				// �ʐM�Ɏg���\�P�b�g
};

#endif
