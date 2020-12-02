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
#include "chatText.h"
#include "picture.h"
#include <sys/stat.h>

// ===================================================================
// �}�N����`
// ===================================================================
#define IPADDRESS_SERVER	("25.10.240.177")	// �T�[�o��IP�A�h���X
#define PORT_SERVER			(12345)				// �T�[�o�̃|�[�g�ԍ�
#define VERSION_WINSOCK		(2)					// winsock�̃o�[�W����

#define LINK_SENDTEXT		("data/SAVEDATA/SendText.txt")						// ���M�p�e�L�X�g�̃p�X
#define LINK_RECVTEXT		("data/SAVEDATA/RecvText.txt")						// ��M�p�e�L�X�g�̃p�X
#define LINK_SENDPICTURE	("data/SAVEDATA/PictureTextures/PicTex.txt")		// ���M�p�s�N�`���̃p�X
#define LINK_RECVPICTURE	("data/SAVEDATA/PictureTextures/RecvPicTex.txt")	// ��M�p�s�N�`���̃p�X

#define SIZE_SEND_TEXT		(9)					// SEND_TEXT�̃T�C�Y
#define SIZE_SEND_PICTURE	(12)				// SEND_PICTURE�̃T�C�Y
#define SIZE_SPACE			(2)					// ������̃X�y�[�X�̃T�C�Y

#define NUM_CMPCHAR			(6)					// ��M���̃e�L�X�g���s�N�`�����̔�r�p

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
	while (1)
	{
		// �ڑ����Ȃ�
		if (!m_bConnecting)
		{
			break;
		}

		char cData[16524];
		memset(cData, 0, sizeof(cData));

		// ��M�҂�
		if (recv(m_socket, cData, 16524, 0) <= 0)
		{
			// ��M���Ă��Ȃ�
			continue;
		}

		// �e�L�X�g��M
		if (cData[0] == ORDER_SENDTEXT)
		{
			RecvText(cData);
		}
		// �s�N�`����M
		if (cData[0] == ORDER_SENDPICTURE)
		{
			RecvPicture(cData);
		}
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
void CClient::SendText(void)
{
	if (!m_bConnecting)
	{
#ifdef _DEBUG
		printf("�T�[�o�[�ɐڑ�����Ă��܂���\n");
#endif
		//return;
	}
	
	FILE *fp;
	char *buffer;
	struct stat stbuf;
	int fd;

	// �t�@�C�����J��
	if ((fp = fopen(LINK_SENDTEXT, "wb")) == NULL)
	{
		// �G���[
		printf("�e�L�X�g�ǂݍ��݃G���[\n");
	}

	// �t�@�C���Ƀf�[�^����������
	fwrite(CChatTab::GetSendText()->GetChatText().c_str(),	// �������ޕ�����
		CChatTab::GetSendText()->GetChatText().size(),		// �������ރT�C�Y
		1,													// �������ރf�[�^�̐�
		fp);												// �������ݐ�

	// �t�@�C�������
	fclose(fp);

	// �t�@�C���T�C�Y�̎擾
	fd = stat(LINK_SENDTEXT, &stbuf);
	printf("�t�@�C���T�C�Y : %.1f byte (%d bit) \n", (float)stbuf.st_size / 8, (int)stbuf.st_size);

	// ������ + ���� + �T�C�Y + null���� �̃����������i�[
	buffer = new char[stbuf.st_size + 5 + 1];

	// �t�@�C�����J��
	if ((fp = fopen(LINK_SENDTEXT, "rb")) == NULL)
	{
		// �G���[
		printf("�e�L�X�g�ǂݍ��݃G���[\n");
	}

	// ������̃A�h���X���擾
	fread(&buffer[5], stbuf.st_size, 1, fp);
	buffer[5 + stbuf.st_size] = '\0';

	// �t�@�C�������
	fclose(fp);

	// �����񑗐M����
	buffer[0] = ORDER_SENDTEXT;

	// �t�@�C���T�C�Y���i�[
	int *pData = (int*)&buffer[1];
	*pData = stbuf.st_size;

#ifdef _DEBUG
	// ���M�f�[�^���f�o�b�O�ŕ\��
	printf("�e�L�X�g���M > %s [%d��]\n", &buffer[5], (int)stbuf.st_size);
#endif
	// ���M
	send(m_socket, buffer, 5 + stbuf.st_size, 0);

	// �����ɒǉ�
	CChatTab::CreateKeep(CChatBase::OWNER_OWN, &buffer[5]);

	// �L����������������Z�b�g
	CChatTab::GetSendText()->GetChatText().clear();

	delete[] buffer;
}

// ===================================================================
// �s�N�`���̑��M
// ===================================================================
void CClient::SendPicture(void)
{
	if (!m_bConnecting)
	{
#ifdef _DEBUG
		printf("�T�[�o�[�ɐڑ�����Ă��܂���\n");
#endif
		//return;
	}

	FILE *fp;
	char *buffer;
	struct stat stbuf;
	int fd;

	// �t�@�C���T�C�Y�̎擾
	fd = stat(LINK_SENDPICTURE, &stbuf);
	printf("�t�@�C���T�C�Y : %.1f byte (%d bit) \n", (float)stbuf.st_size / 8, (int)stbuf.st_size);

	// ������ + ���� + �T�C�Y + null���� �̃����������i�[
	buffer = new char[stbuf.st_size + 5 + 1];

	// �t�@�C�����J��
	if ((fp = fopen(LINK_SENDPICTURE, "rb")) == NULL)
	{
		// �G���[
		printf("�e�L�X�g�ǂݍ��݃G���[\n");
	}

	// ������̃A�h���X���擾
	fread(&buffer[5], stbuf.st_size, 1, fp);
	buffer[5 + stbuf.st_size] = '\0';

	// �t�@�C�������
	fclose(fp);

	// �����񑗐M����
	buffer[0] = ORDER_SENDPICTURE;

	// �t�@�C���T�C�Y���i�[
	int *pData = (int*)&buffer[1];
	*pData = stbuf.st_size;

#ifdef _DEBUG
	// ���M�f�[�^���f�o�b�O�ŕ\��
	printf("�s�N�`�����M > %s [%d��]\n", &buffer[5], (int)stbuf.st_size);
#endif
	// ���M
	send(m_socket, buffer, 5 + stbuf.st_size, 0);

	// ��̃s�N�`���𐶐�
	LPDIRECT3DTEXTURE9 pTexture = NULL;
	if (FAILED(CManager::GetRenderer()->GetDevice()->CreateTexture(128, 128, 1, 0, D3DFMT_A32B32G32R32F,
		D3DPOOL_MANAGED, &pTexture, NULL)))
	{
		throw E_FAIL;
	}
	// �s�N�`���̏����i�[
	CString link;
	link = LINK_SENDPICTURE;
	CPicture::Reading(pTexture, link);
	// �����ɒǉ�
	CChatTab::AddPicture(CChatBase::OWNER_OWN, pTexture);

	delete[] buffer;
}

// ===================================================================
// �e�L�X�g�̎�M
// ===================================================================
void CClient::RecvText(char *data)
{
	// �T�C�Y
	int *pSize = (int*)&data[1];

	char *cTextData = new char[*pSize + 1];
	memcpy(cTextData, &data[5], *pSize);
	cTextData[*pSize] = '\0';

	FILE *fp;

	// �t�@�C�����J��
	if ((fp = fopen(LINK_RECVTEXT, "wb")) == NULL)
	{
		// �G���[
		printf("�e�L�X�g�ǂݍ��݃G���[\n");
	}

	fwrite(cTextData, *pSize, 1, fp);

	// �t�@�C�������
	fclose(fp);

#ifdef _DEBUG
	// ���M�f�[�^���f�o�b�O�ŕ\��
	printf("�e�L�X�g��M > %s [%d��]\n", cTextData, *pSize);
#endif
	// �����ɒǉ�
	CChatTab::CreateKeep(CChatBase::OWNER_GUEST, cTextData);

	delete[] cTextData;
}

// ===================================================================
// �s�N�`���̎�M
// ===================================================================
void CClient::RecvPicture(char *data)
{
	// �T�C�Y
	int *pSize = (int*)&data[1];

	char *cPicData = new char[*pSize + 1];
	memcpy(cPicData, &data[5], *pSize);
	cPicData[*pSize] = '\0';

	FILE *fp;

	// �t�@�C�����J��
	if ((fp = fopen(LINK_RECVPICTURE, "wb")) == NULL)
	{
		// �G���[
		printf("�e�L�X�g�ǂݍ��݃G���[\n");
	}

	fwrite(cPicData, *pSize, 1, fp);

	// �t�@�C�������
	fclose(fp);

#ifdef _DEBUG
	// ���M�f�[�^���f�o�b�O�ŕ\��
	printf("�s�N�`����M > %s [%d��]\n", cPicData, *pSize);
#endif

	// �i�[�p
	LPDIRECT3DTEXTURE9 pTexture = NULL;

	if (FAILED(CManager::GetRenderer()->GetDevice()->CreateTexture(128, 128, 1, 0, D3DFMT_A32B32G32R32F,
		D3DPOOL_MANAGED, &pTexture, NULL)))
	{
		throw E_FAIL;
	}

	CString link;
	link = LINK_RECVPICTURE;
	CPicture::Reading(pTexture, link);

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