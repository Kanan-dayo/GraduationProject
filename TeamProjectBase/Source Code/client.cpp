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
#include "connectUI.h"
#include "basemode.h"
#include "result.h"
#include "tutorial.h"
#include "timer.h"
#include "Decoding.h"

// ===================================================================
// �}�N����`
// ===================================================================
#define VERSION_WINSOCK		(2)					// winsock�̃o�[�W����

#define LINK_IPADDRESS		("data/TEXT/IP.txt")								// IP�A�h���X�̃p�X
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
bool CClient::m_bAccept					= false;
bool CClient::m_bAcceptOther			= false;
SOCKET CClient::m_socket				= NULL;
CClient::SOCKINFO CClient::m_sockInfo	= {};

// ===================================================================
// IP�A�h���X�̃��[�h
// ===================================================================
HRESULT CClient::LoadIP(void)
{
	// �ϐ��錾
	FILE *pFile;
	char cReadText[MAX_TEXT];
	char cHeadText[MAX_TEXT] = "\0";
	char cAddress[64] = "\0";
	u_short port = 0;

	// �t�@�C�����J��
	pFile = fopen(LINK_IPADDRESS, "r");

#ifdef _DEBUG
	std::cout << "IP�A�h���X�E�|�[�g�ԍ��̎擾���J�n\n";
#endif

	// ���s
	if (!pFile)
	{
#ifdef _DEBUG
		std::cout << "�t�@�C���I�[�v���Ɏ��s\n";
#endif
		return E_FAIL;
	}

	// �X�N���v�g������܂ŌJ��Ԃ�
	while (strcmp(cHeadText, "SCRIPT") != 0)
	{
		fgets(cReadText, sizeof(cReadText), pFile);
		sscanf(cReadText, "%s", &cHeadText);
	}
	// �X�N���v�g��������
	if (strcmp(cHeadText, "SCRIPT") == 0)
	{
		// �G���h�X�N���v�g������܂ŌJ��Ԃ�
		while (strcmp(cHeadText, "END_SCRIPT") != 0)
		{
			strcpy(cHeadText, "");
			fgets(cReadText, sizeof(cReadText), pFile);
			sscanf(cReadText, "%s", &cHeadText);
			// ���s
			if (strcmp(cHeadText, "\n") == 0)
				continue;
			// IP�A�h���X
			if (strcmp(cHeadText, "IP�A�h���X") == 0)
				sscanf(cReadText, "IP�A�h���X : %s", cAddress);
			// �|�[�g�ԍ�
			if (strcmp(cHeadText, "�|�[�g�ԍ�") == 0)
				sscanf(cReadText, "�|�[�g�ԍ� : %hd", &port);
		}
	}

	// �t�@�C�������
	fclose(pFile);

	// �����i�[
	strcpy(m_sockInfo.ip_Addr, cAddress);
	m_sockInfo.port = port;

#ifdef _DEBUG
	std::cout << "�擾����\n";
	std::cout << "IP�A�h���X : " << m_sockInfo.ip_Addr << std::endl;
	std::cout << "�|�[�g�ԍ� : " << m_sockInfo.port << std::endl;
#endif

	// ����
	return S_OK;
}

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

	// IP�A�h���X���擾
	LoadIP();

	// �\�P�b�g�̍쐬
	m_socket = socket(AF_INET, SOCK_STREAM, 0);

	// �ڑ���w��p�\���̂̏���
	server.sin_family = AF_INET;
	server.sin_port = htons(m_sockInfo.port);
	server.sin_addr.S_un.S_addr = inet_addr(m_sockInfo.ip_Addr);

	while (!m_bAccept)
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
		m_bAccept = true;
	}
	

	// ��M�҂�
	std::thread threadRecv(CClient::WaitRecieve);
	threadRecv.detach();

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
		if (!m_bAccept)
		{
			break;
		}

		char cData[16600];
		memset(cData, 0, sizeof(cData));

		// ��M�҂�
		if (recv(m_socket, cData, 16600, 0) <= 0)
		{
			// ��M���Ă��Ȃ�
			continue;
		}

		if (cData[0] == ORDER_GUEST_BE_ACCEPT)
		{
			printf("�Q�X�g�Ƃ̐ڑ����m�F\n");
			m_bAcceptOther = true;
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
		// �I����M
		if (cData[0] == ORDER_SENDSELECT)
		{
			RecvSelect(cData);
		}
		// �҂���Ԏ�M
		if (cData[0] == ORDER_SENDWAIT)
		{
			RecvWait();
		}
		// ���g���C��M
		if (cData[0] == ORDER_RETRY)
		{
			RecvRetry();
		}
		// �I����M
		if (cData[0] == ORDER_END_GAME)
		{
			RecvEndGame();
		}
		// �Q�[���I�[�o�[��M
		if (cData[0] == ORDER_GAMEOVER)
		{
			RecvGameOver(cData);
		}
		// �Q�[���N���A��M
		if (cData[0] == ORDER_GAMECLEAR)
		{
			RecvGameClear(cData);
		}
	}
}

// ===================================================================
// �T�[�o�[�̏�����
// ===================================================================
HRESULT CClient::InitClient(void)
{
	m_bAccept = false;
	m_bAcceptOther = false;

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
	if (m_bAccept)
		m_bAccept = false;
	// winsock2�̏I������
	WSACleanup();
}

// ===================================================================
// �e�L�X�g�̑��M
// ===================================================================
void CClient::SendText(void)
{
	if (!m_bAccept)
	{
#ifdef _DEBUG
		printf("�T�[�o�[�ɐڑ�����Ă��܂���\n");
#endif
		//return;
	}
	
	FILE *fp = fopen(LINK_SENDTEXT, "wb");
	char *buffer;
	struct stat stbuf;

	// �t�@�C�����J��
	if (!fp)
	{
		// �G���[
		printf("�e�L�X�g�ǂݍ��݃G���[\n");
		return;
	}

	// �t�@�C���Ƀf�[�^����������
	fwrite(CChatTab::GetSendText()->GetChatText().c_str(),	// �������ޕ�����
		CChatTab::GetSendText()->GetChatText().size(),		// �������ރT�C�Y
		1,													// �������ރf�[�^�̐�
		fp);												// �������ݐ�

	// �t�@�C�������
	fclose(fp);

	// �t�@�C���T�C�Y�̎擾
	stat(LINK_SENDTEXT, &stbuf);
	printf("�t�@�C���T�C�Y : %.1f byte (%d bit) \n", (float)stbuf.st_size / 8, (int)stbuf.st_size);

	// ������ + ���� + �T�C�Y + null���� �̃����������i�[
	buffer = new char[stbuf.st_size + 5 + 1];

	fp = fopen(LINK_SENDTEXT, "rb");
	// �t�@�C�����J��
	if (!fp)
	{
		// �G���[
		printf("�e�L�X�g�ǂݍ��݃G���[\n");
		return;
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
	CChatTab::AddRecvKeep(CChatBase::OWNER_OWN, &buffer[5]);

	// �L����������������Z�b�g
	CChatTab::GetSendText()->GetChatText().clear();

	delete[] buffer;
}

// ===================================================================
// �s�N�`���̑��M
// ===================================================================
void CClient::SendPicture(void)
{
	if (!m_bAccept)
	{
#ifdef _DEBUG
		printf("�T�[�o�[�ɐڑ�����Ă��܂���\n");
#endif
		//return;
	}

	FILE *fp;
	char *buffer;
	struct stat stbuf;

	// �t�@�C���T�C�Y�̎擾
	stat(LINK_SENDPICTURE, &stbuf);
	printf("�t�@�C���T�C�Y : %.1f byte (%d bit) \n", (float)stbuf.st_size / 8, (int)stbuf.st_size);

	// ������ + ���� + �T�C�Y + null���� �̃����������i�[
	buffer = new char[stbuf.st_size + 5 + 1];

	fp = fopen(LINK_SENDPICTURE, "rb");
	// �t�@�C�����J��
	if (!fp)
	{
		// �G���[
		printf("�e�L�X�g�ǂݍ��݃G���[\n");
		return;
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
	send(m_socket, buffer, 5 + stbuf.st_size + 1, 0);

	// ��̃s�N�`���𐶐�
	LPDIRECT3DTEXTURE9 pTexture = NULL;
	if (FAILED(CManager::GetRenderer()->GetDevice()->CreateTexture(128, 128, 1, 0, D3DFMT_A32B32G32R32F,
		D3DPOOL_MANAGED, &pTexture, NULL)))
	{
		std::cout << "�s�N�`���������s\n";
	}
	// �s�N�`���̏����i�[
	CString link;
	link = LINK_SENDPICTURE;
	CPicture::Reading(pTexture, link);
	// �����ɒǉ�
	CChatTab::AddRecvPicture(CChatBase::OWNER_OWN, pTexture);

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

	FILE *fp = fopen(LINK_RECVTEXT, "wb");

	// �t�@�C�����J��
	if (!fp)
	{
		// �G���[
		printf("�e�L�X�g�ǂݍ��݃G���[\n");
		return;
	}

	fwrite(cTextData, *pSize, 1, fp);

	// �t�@�C�������
	fclose(fp);

#ifdef _DEBUG
	// ���M�f�[�^���f�o�b�O�ŕ\��
	printf("�e�L�X�g��M > %s [%d��]\n", cTextData, *pSize);
#endif
	// �����ɒǉ�
	CChatTab::AddRecvKeep(CChatBase::OWNER_GUEST, cTextData);

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

	FILE *fp = fopen(LINK_RECVPICTURE, "wb");

	// �t�@�C�����J��
	if (!fp)
	{
		// �G���[
		printf("�e�L�X�g�ǂݍ��݃G���[\n");
		return;
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

	CChatTab::AddRecvPicture(CChatBase::OWNER_GUEST, pTexture);

	delete[] cPicData;
}

// ===================================================================
// �I���̑��M
// ===================================================================
void CClient::SendSelect(int nSelect)
{
	char buffer[2];

	// �I�𑗐M����
	buffer[0] = ORDER_SENDSELECT;
	buffer[1] = nSelect;

	// ���M
	send(m_socket, buffer, 2, 0);
}

// ===================================================================
// �I���̎�M
// ===================================================================
void CClient::RecvSelect(char *data)
{
	int *pSelect = (int*)&data[1];
	// �I�����i�[
	CConnectUI::RecvGuestSelect(*pSelect);
}

// ===================================================================
// �҂���Ԃ̑��M
// ===================================================================
void CClient::SendWait(void)
{
	char buffer[1];

	// �҂���Ԗ���
	buffer[0] = ORDER_SENDWAIT;

	// ���M
	send(m_socket, buffer, 1, 0);
}

// ===================================================================
// �҂���Ԃ̎�M
// ===================================================================
void CClient::RecvWait(void)
{
	// �T�[�o�[�ڑ�
	if (CManager::GetMode() == CManager::MODE_CONNECT_SERVER)
		CConnectUI::RecvGuestWait();
	// �`���[�g���A��
	else if (CManager::GetMode() == CManager::MODE_TUTORIAL)
		CTutorial::GuestEndTutorial();
}

// ===================================================================
// ���g���C�̎�M
// ===================================================================
void CClient::SendRetry(void)
{
	char buffer[1];

	buffer[0] = ORDER_RETRY;

	send(m_socket, buffer, 1, 0);
}

// ===================================================================
// ���g���C�̎�M
// ===================================================================
void CClient::RecvRetry(void)
{
	if (CManager::GetMode() == CManager::MODE_RESULT)
	{
		CResult *pResult = (CResult*)CManager::GetBaseMode();
		pResult->SetGuestMode((int)ORDER_RETRY);
	}
}

// ===================================================================
// �Q�[���I�[�o�[�̑��M
// ===================================================================
void CClient::SendGameOver(void)
{
	char buffer[2];

	buffer[0] = ORDER_GAMEOVER;
	buffer[1] = CTimer::GetClearFlame();
	printf("time : %d\n", CTimer::GetClearFlame());

	send(m_socket, buffer, 2, 0);
}

// ===================================================================
// �Q�[���I�[�o�[�̎�M
// ===================================================================
void CClient::RecvGameOver(char *data)
{
	int *pTime = (int*)&data[1];
	// �^�C����ݒ�
	CTimer::SetClearFrame(*pTime);
	// ������[�h���I��
	CDecoding::SetGameEndState(CDecoding::GAMEEND_MISS);
}

// ===================================================================
// �Q�[���N���A�̑��M
// ===================================================================
void CClient::SendGameClear(void)
{
	char buffer[2];

	buffer[0] = ORDER_GAMECLEAR;
	buffer[1] = CTimer::GetClearFlame();
	printf("time : %d\n", CTimer::GetClearFlame());

	send(m_socket, buffer, 2, 0);
}

// ===================================================================
// �Q�[���N���A�̎�M
// ===================================================================
void CClient::RecvGameClear(char *data)
{
	int *pTime = (int*)&data[1];
	// �^�C����ݒ�
	CTimer::SetClearFrame(*pTime);
	// ������[�h���I��
	CDecoding::SetGameEndState(CDecoding::GAMEEND_CLEAR);
}

// ===================================================================
// �Q�[���I���̑��M
// ===================================================================
void CClient::SendEndGame(void)
{
	char buffer[1];

	buffer[0] = ORDER_END_GAME;

	send(m_socket, buffer, 1, 0);
}

// ===================================================================
// �Q�[���I���̎�M
// ===================================================================
void CClient::RecvEndGame(void)
{
	if (CManager::GetMode() == CManager::MODE_RESULT)
	{
		CResult *pResult = (CResult*)CManager::GetBaseMode();
		pResult->SetGuestMode((int)ORDER_END_GAME);
	}
}

// ===================================================================
// �ڑ��I���̑��M
// ===================================================================
void CClient::SendEndAccept(void)
{
	char buffer[1];

	// �҂���Ԗ���
	buffer[0] = ORDER_CLOSED_SOCKET;

	// ���M
	send(m_socket, buffer, 1, 0);
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