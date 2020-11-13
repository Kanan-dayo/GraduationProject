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
#include "manager.h"
#include "renderer.h"
#include "client.h"
#include "chatTab.h"
#include "picture.h"

// ===================================================================
// �}�N����`
// ===================================================================
#define IPADDRESS_SERVER	("172.16.11.199")	// �T�[�o��IP�A�h���X
#define PORT_SERVER			(12345)				// �T�[�o�̃|�[�g�ԍ�
#define VERSION_WINSOCK		(2)					// winsock�̃o�[�W����
#define LINK_SENDPICTURE	("data/SAVEDATA/PictureTextures/PicTex.txt")	// ���M�p�s�N�`���̃p�X

// ===================================================================
// �ÓI�����o�ϐ��̏�����
// ===================================================================
bool CClient::m_bConnecting = false;
SOCKET CClient::m_socket = NULL;

// ===================================================================
// ���C���֐�
// ===================================================================
int CClient::ConnectServer(void)
{
	struct sockaddr_in server;
	int err = 0;

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

	while (!m_bConnecting)
	{
		// �ڑ�
		err = connect(m_socket, (struct sockaddr *)&server, sizeof(server));

		// �G���[����
		if (err == -1)
		{
#ifdef _DEBUG
			printf("�ڑ����c\n");
#endif 
			// �Đڑ�
			continue;
		}

		// �ڑ�����
#ifdef _DEBUG
		printf("�ڑ�����\n");
#endif
		m_bConnecting = true;
	}

	return 0;
}

// ===================================================================
// ��M�҂�����
// ===================================================================
void CClient::WaitRecieve(void)
{
	char buf[256] = {};					// �e�L�X�g���i�[����ϐ�
	size_t bufSize = sizeof(buf);	// �T�C�Y���i�[����ϐ�

	while (1)
	{
		// �ڑ����Ȃ�
		if (!m_bConnecting)
		{
			break;
		}

		// �������u���b�N�����Z�b�g
		memset(buf, 0, bufSize);

		// �ڑ��҂�
		if (recv(m_socket, buf, bufSize, 0) == -1)
		{
#ifdef _DEBUG
			// �G���[���|�[�g
			ErrorReport();
#endif
			continue;
		}

		// �e�L�X�g�̎�M
		if (strlen(buf) > 0)
			RecvText(buf);

		RecvPicture();
	}
}

// ===================================================================
// �T�[�o�[�̏�����
// ===================================================================
HRESULT CClient::InitClient(void)
{
	WSADATA wsaData;	// winsock�̃f�[�^

	// �T�[�o�E�N���C�A���g���ʂŊJ�n���̂݁A�K���s��
	int err = WSAStartup(MAKEWORD(VERSION_WINSOCK, 0), &wsaData);

	// �G���[����
	if (err == 0)
	{
		// ����
		return S_OK;
	}

#ifdef _DEBUG
	// �G���[���b�Z�[�W
	ErrorReport();
#endif

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
	// �ڑ��I��
	if (m_bConnecting)
		m_bConnecting = false;
	// winsock2�̏I������
	WSACleanup();
}

// ===================================================================
// �e�L�X�g�̑��M
// ===================================================================
void CClient::SendText(char * cSendText)
{
	if (!m_bConnecting)
	{
#ifdef _DEBUG
		printf("�T�[�o�[�ɐڑ�����Ă��܂���\n");
#endif
		return;
	}

	char Text[65];
	strcpy(Text, cSendText);
	int nLen = strlen(Text);

#ifdef _DEBUG
	printf("���M > %s [%d��]\n", Text, nLen);
#endif
	// �e�L�X�g���M
	if (send(m_socket, Text, nLen, 0) == -1)
	{
#ifdef _DEBUG
		ErrorReport();
#endif
	}
}

// ===================================================================
// �e�L�X�g�̎�M
// ===================================================================
void CClient::RecvText(char * cRecvText)
{
	int nLen = strlen(cRecvText);
#ifdef _DEBUG
	printf("��M > %s [%d��]\n", cRecvText, nLen);
#endif
	// �`���b�g�Ƀe�L�X�g��ǉ�
	CChatTab::RecvChatText(cRecvText);
}

// ===================================================================
// �s�N�`���̑��M
// ===================================================================
void CClient::SendPicture(void)
{
	// �ڑ����Ă��Ȃ�
	if (!m_bConnecting)
	{
#ifdef _DEBUG
		printf("�T�[�o�[�ɐڑ�����Ă��܂���\n");
#endif
		//return;
	}

	// �ϐ��錾
	CLoadFile Load;
	CLoadFile::LOADRESULT result;	// ����

	// �ǂݍ��݃t�@�C���̏����쐬
	if ((result = Load.LoadFileIntoString(LINK_SENDPICTURE)) != CLoadFile::LR_SUCCESS)
	{
		// �G���[
	}

#ifdef _DEBUG
	printf("�s�N�`�����M > [%d byte]\n", Load.m_nuFileSize);
#endif

	// �s�N�`�����M��`����
	char sendTitle[16] = "SEND_PICTURE";
	send(m_socket, sendTitle, strlen(sendTitle), 0);

	// �e�L�X�g���M
	if (send(m_socket, Load.m_pFileData, Load.m_nuFileSize, 0) == -1)
	{
		// �G���[���|�[�g
#ifdef _DEBUG
		ErrorReport();
#endif
		// �t�@�C���f�[�^�̔j��
		//Load.DeleteFileData();
		//return;
	}

	LPDIRECT3DTEXTURE9 pTexture = NULL;

	if (FAILED(CManager::GetRenderer()->GetDevice()->CreateTexture(128, 128, 1, 0, D3DFMT_A32B32G32R32F,
		D3DPOOL_MANAGED, &pTexture, NULL)))
	{
		throw E_FAIL;
	}

	CString link;
	link = LINK_SENDPICTURE;
	CPicture::Reading(pTexture, link);

	CChatTab::AddPicture(CChatBase::OWNER_OWN, pTexture);

	// �t�@�C���f�[�^�̔j��
	Load.DeleteFileData();
}

// ===================================================================
// �s�N�`���̎�M
// ===================================================================
void CClient::RecvPicture(void)
{
	// �i�[�p
	LPDIRECT3DTEXTURE9 pTexture = NULL;

	if (FAILED(CManager::GetRenderer()->GetDevice()->CreateTexture(128, 128, 1, 0, D3DFMT_A32B32G32R32F,
		D3DPOOL_MANAGED, &pTexture, NULL)))
	{
		throw E_FAIL;
	}

	//CString link;
	//link = LINK_SENDPICTURE;
	//CPicture::Reading(pTexture, link);

	CChatTab::AddPicture(CChatBase::OWNER_GUEST, pTexture);
}

#ifdef _DEBUG
// ===================================================================
// �G���[���b�Z�[�W
// ===================================================================
void CClient::ErrorReport(void)
{
	// �G���[�R�[�h���擾
	int err = WSAGetLastError();
	printf("�I�I�I�G���[�����I�I�I\n");
	printf("ErrorCode : %d\n", err);

	// �G���[�̌�����\��
	switch (err)
	{
	case WSASYSNOTREADY:
		printf("�l�b�g���[�N�T�u�V�X�e�����l�b�g���[�N�ւ̐ڑ��������ł��Ă��܂���B\n");
		break;
	case WSAVERNOTSUPPORTED:
		printf("�v�����ꂽwinsock�̃o�[�W�������T�|�[�g����Ă��܂���B\n");
		break;
	case WSAEINPROGRESS:
		printf("�u���b�L���O����̎��s���ł��邩�A �܂��̓T�[�r�X�v���o�C�_���R�[���o�b�N�֐����������Ă��܂��B\n");
		break;
	case WSAEPROCLIM:
		printf("winsock�������ł���ő�v���Z�X���ɒB���܂����B\n");
		break;
	case WSAEFAULT:
		printf("�������ł��� lpWSAData �͗L���ȃ|�C���^�ł͂���܂���B\n");
		break;
	case EBADF:
		printf("�\�P�b�g�������\�P�b�g�L�q�q�ł��B\n");
		break;
	case ECONNRESET:
		printf("�ڑ��̓s�A�ɂ���ċ����I�ɃN���[�Y����܂����B\n");
		break;
	case EFAULT:
		printf("buf�����len�p�����[�^���g�p����ƁA\n");
		printf("�Ăяo�����̃A�h���X�E�X�y�[�X�̊O���̃X�g���[�W�ɃA�N�Z�X���邱�ƂɂȂ�܂��B\n");
		break;
	case EINTR:
		printf("recv()�̌Ăяo���́A�f�[�^�̎g�p�\�ɂȂ�O��\n");
		printf("�L���b�`���ꂽ�V�O�i���ɂ���Ċ��荞�܂�܂����B\n");
		break;
	case EINVAL:
		printf("�v�����������A�܂��̓T�|�[�g����Ă��܂���B\n");
		printf("MSG_OOB�t���O���ݒ肳��A�A�E�g�E�I�u�E�o���h�̃f�[�^���g�p�ł��܂���B\n");
		break;
	case EIO:
		printf("�l�b�g���[�N�܂��̓g�����X�|�[�g�ŏ�Q���������܂����B\n");
		break;
	case ENOTCONN:
		printf("�ڑ�����Ă��Ȃ��ڑ��w���\�P�b�g�ɑ΂����M�����݂Ă��܂��B\n");
		break;
	case ENOTSOCK:
		printf("�L�q�q�̓t�@�C���p�ł���A�\�P�b�g�p�ł͂���܂���B\n");
		break;
	case EOPNOTSUPP:
		printf("�w�肵���t���O�́A���̃\�P�b�g�E�^�C�v�΂��̓v���g�R���̏ꍇ�̓T�|�[�g����Ă��܂���B\n");
		break;
	case ETIMEDOUT:
		printf("�ڑ��̐ݒ蒆�܂��̓A�N�e�B�u�Ȑڑ��ł̓`���̃^�C���A�E�g�̂��߂ɁA\n");
		printf("�ڑ����^�C���A�E�g�ɂȂ�܂����B\n");
		break;
	case EWOULDBLOCK:
		printf("socket�́A��u���b�N�E���[�h�ɂȂ��Ă��邽�߁A�f�[�^�̓ǂݎ��͂ł��܂���B\n");
		printf("�܂��́ASO_RCVTIMEO�^�C���A�E�g�l�ɒB�������߃f�[�^�͎g�p�ł��܂���ł����B");
		break;
	case WSAEINTR:
		printf("�u���b�L���OWindows Sockets 1.1�Ăяo���� WSACancelBlockingCall ��ʂ��ăL�����Z������܂����B\n");
		break;
	case WSAEACCES:
		printf("setsockeopt�I�v�V����SO_BROADCAST���L���łȂ����߁A�_�C�A�O�����\�P�b�g�̃u���[�h�L���X�g�ւ�\n");
		printf("�ڑ����s�����s���܂����B\n");
		break;
	case WSAEINVAL:
		printf("�p�����[�^s�̓��X�j���O�\�P�b�g�ł��B\n");
		break;
	case WSAEWOULDBLOCK:
		printf("���̃\�P�b�g�͔�u���b�L���O�Ƃ��ă}�[�N����Ă���A�ڑ��������Ɋ������܂���ł����B\n");
		break;
	case WSAEALREADY:
		printf("��u���b�L���Oconnect�Ăяo�������ē��ꂽ�\�P�b�g�Ŏ��s���ł��B\n");
		break;
	case WSAENOTSOCK:
		printf("s�p�����[�^�Ŏw�肳�ꂽ�f�B�X�N���v�^�̓\�P�b�g�ł͂���܂���B\n");
		break;
	case WSAEAFNOSUPPORT:
		printf("�w�肳�ꂽ�t�@�~���̃A�h���X�����̃\�P�b�g�Ŏg�p���邱�Ƃ͂ł��܂���B\n");
		break;
	case WSAEADDRINUSE:
		printf("�\�P�b�g�̃��[�J���A�h���X�����Ɏg�p����Ă���A�\�P�b�g���A�h���X���ė��p�\�ƂȂ�悤��\n");
		printf("SO_REUSEADDR�\�P�b�g�I�v�V�����������Ă��܂���B\n");
		printf("���̃G���[�͒ʏ�bind�֐������s���Ă���ۂɔ������܂����Abind�������I�ȃ��C���h�J�[�h�A�h���X(ADDR_ANY)��\n");
		printf("�w�肵�A���A����̃A�h���X�����̊֐��̎��_�ŃR�~�b�g�����K�v������ꍇ�ɂ��̊֐��܂Ő扄�΂������\n");
		printf("�\��������܂��B\n");
		break;
	case WSAEADDRNOTAVAIL:
		printf("�����[�g�A�h���X���L���ł͂���܂���B\n");
		break;
	case WSAENETDOWN:
		printf("�l�b�g���[�N�T�u�V�X�e�������s���܂����B\n");
		break;
	case WSAENETUNREACH:
		printf("�����_�ł��̃z�X�g����l�b�g���[�N�ɓ��B���邱�Ƃ��ł��܂���B\n");
		break;
	case WSAENOBUFS:
		printf("���p�\�ȃo�b�t�@��Ԃ�����܂���B�\�P�b�g��ڑ��ł��܂���B\n");
		break;
	case WSAEISCONN:
		printf("�w�肳�ꂽ�\�P�b�g�͊��ɐڑ�����Ă��܂�(�R�l�N�V�����w���̃\�P�b�g�̂�)�B\n");
		break;
	case WSAETIMEDOUT:
		printf("�ڑ����s�͐ڑ����m�����邱�ƂȂ��^�C���A�E�g���܂����B\n");
		break;
	case WSAECONNREFUSED:
		printf("�ڑ��̎��s���������ۂ���܂����B\n");
		break;
	case WSAEHOSTUNREACH:
		printf("���B�s�\�ȃz�X�g�ɑ΂��ă\�P�b�g���삪���s����܂����B\n");
		break;
	case WSANOTINITIALISED:
		printf("���̊֐����Ăяo���O��WSAStartup�֐��̌Ăяo�����������Ă��Ȃ���΂Ȃ�܂���B\n");
		break;
	}
}
#endif