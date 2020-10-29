// ===================================================================
//
// �N���C�A���g���� [ client.cpp ]
// Author : KANAN NAGANAWA
//
// ===================================================================
#define _WINSOCK_DEPRECATED_NO_WARNINGS		// winsock�̌x������

// ===================================================================
// �C���N���[�h�t�@�C��
// ===================================================================
#include "client.h"

// ===================================================================
// �}�N����`
// ===================================================================
#define IPADDRESS_SERVER	("172.16.11.199")	// �T�[�o��IP�A�h���X
#define PORT_SERVER			(12345)				// �T�[�o�̃|�[�g�ԍ�
#define VERSION_WINSOCK		(2)					// winsock�̃o�[�W����

// ===================================================================
// �ÓI�����o�ϐ��̏�����
// ===================================================================
bool CClient::m_bConnecting = false;
char CClient::m_cSendText[256] = {};
SOCKET CClient::m_socket = NULL;

// ===================================================================
// ���C���֐�
// ===================================================================
int CClient::main(void)
{
	struct sockaddr_in server;
	char buf[32];

	// winsock�̏�����
	if (InitClient() == E_FAIL)
	{
		// �G���[�ɂ�鋭���I��
		return 0;
	}

	// �\�P�b�g�̍쐬
	m_socket = socket(AF_INET, SOCK_STREAM, 0);

	// �ڑ���w��p�\���̂̏���
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT_SERVER);
	server.sin_addr.S_un.S_addr = inet_addr(IPADDRESS_SERVER);

	// �T�[�o�ɐڑ�
	connect(m_socket, (struct sockaddr *)&server, sizeof(server));

	while (1)
	{
		// �ڑ����Ȃ�
		if (!m_bConnecting)
			break;

		// �T�[�o����f�[�^����M
		memset(buf, 0, sizeof(buf));
		// �ڑ��҂�
		int n = recv(m_socket, buf, sizeof(buf), 0);
		// ��M�����f�[�^��\��
		if (n > 0)
			printf("%d, %s\n", n, buf);
	}
	// winsock2�̏I������
	WSACleanup();

	return 0;
}

// ===================================================================
// �T�[�o�[�̏�����
// ===================================================================
HRESULT CClient::InitClient(void)
{
	WSADATA wsaData;	// winsock�̃f�[�^
	int err;			// �G���[�ԍ�

	// �v�f�̏�����
	m_bConnecting = true;

	// �T�[�o�E�N���C�A���g���ʂŊJ�n���̂݁A�K���s��
	err = WSAStartup(MAKEWORD(VERSION_WINSOCK, 0), &wsaData);

	// �G���[����
	if (err == 0)
	{
		// ����
		return S_OK;
	}

	// �G���[���b�Z�[�W
	ErrorReport(err);
	// winsock2�̏I������
	WSACleanup();
	// ���s
	return E_FAIL;
}

// ===================================================================
// �T�[�o�[�̏I��
// ===================================================================
void CClient::UninitClient(void)
{
	m_bConnecting = false;
	// winsock2�̏I������
	WSACleanup();
}

// ===================================================================
// �G���[���b�Z�[�W
// ===================================================================
void CClient::ErrorReport(int err)
{
	printf("�I�I�I�G���[�����I�I�I\n");

	printf("ErrorCode : %d\n", WSAGetLastError());

	switch (err)
	{
		// �l�b�g���[�N�T�u�V�X�e�����l�b�g���[�N�ւ̐ڑ��������ł��Ă��Ȃ�
	case WSASYSNOTREADY:
		printf("�l�b�g���[�N�T�u�V�X�e�����l�b�g���[�N�ւ̐ڑ��������ł��Ă��܂���B\n");
		break;
		// �v�����ꂽwinsock�̃o�[�W�������T�|�[�g����Ă��Ȃ�
	case WSAVERNOTSUPPORTED:
		printf("�v�����ꂽwinsock�̃o�[�W�������T�|�[�g����Ă��܂���B\n");
		break;
		// �u���b�L���O����̎��s���ł��邩�A �܂��̓T�[�r�X�v���o�C�_���R�[���o�b�N�֐����������Ă���
	case WSAEINPROGRESS:
		printf("�u���b�L���O����̎��s���ł��邩�A �܂��̓T�[�r�X�v���o�C�_���R�[���o�b�N�֐����������Ă��܂��B\n");
		break;
		// winsock�������ł���ő�v���Z�X���ɒB����
	case WSAEPROCLIM:
		printf("winsock�������ł���ő�v���Z�X���ɒB���܂����B\n");
		break;
		// �������ł���lpWSAData �͗L���ȃ|�C���^�ł͂Ȃ�
	case WSAEFAULT:
		printf("�������ł��� lpWSAData �͗L���ȃ|�C���^�ł͂���܂���B\n");
		break;
	}

	// �L�[���͑҂�
	printf("�I�����܂��BEnter�L�[����͂��Ă��������B\n");
	getchar();
}

// ===================================================================
// �e�L�X�g�̑��M
// ===================================================================
void CClient::Send(char * cSendText)
{
	strcpy(m_cSendText, cSendText);
	// �e�L�X�g���M
	send(m_socket, m_cSendText, strlen(m_cSendText), 0);
	strcpy(m_cSendText, "");
}
