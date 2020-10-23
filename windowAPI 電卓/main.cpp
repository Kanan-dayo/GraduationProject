//-------------------------------------------------------------------------------
//
//�����Z�̏���[main.cpp]
//Author:Yoshiki Hosoya
//
//-------------------------------------------------------------------------------
#include<windows.h>		//�C���N���[�h�t�@�C�� 
//-------------------------------------------------------------------------------
//�}�N����`
//-------------------------------------------------------------------------------
#define CLASS_NAME		"WindowClass"			//�E�B���h�E�N���X�̖��O      
#define WINDOW_NAME		"�E�B���h�E�\������"	//�E�B���h�E�̖��O�i�L���v�V�����\���j
#define SCREEN_WIDTH	(500)					//�E�B���h�E�̕�
#define SCREEN_HEIGHT	(400)					//�E�B���h�E�̍���
#define ID_BUTTON000	(101)					//�{�^��000�̃E�B���h�EID
#define ID_BUTTON001	(102)					//�{�^��001�̃E�B���h�EID
#define ID_BUTTON002	(103)					//�{�^��002�̃E�B���h�EID
#define ID_BUTTON003	(104)					//�{�^��003�̃E�B���h�EID
#define ID_BUTTON004	(105)					//�{�^��004�̃E�B���h�EID
#define ID_BUTTON005	(106)					//�{�^��005�̃E�B���h�EID
#define ID_BUTTON006	(107)					//�{�^��006�̃E�B���h�EID
#define ID_BUTTON007	(108)					//�{�^��007�̃E�B���h�EID
#define ID_EDIT000		(111)					//�G�f�B�b�g000�E�B���h�E��ID
#define ID_EDIT001		(112)					//�G�f�B�b�g001�E�B���h�E��ID
#define ID_EDIT002		(113)					//�G�f�B�b�g002�E�B���h�E��ID
#define ID_TIMER		(121)					//�^�C�}�[ID
#define TIMER_INTERVAL	(1000/60)				//1�t���b�v������̎���
#define RESET_COLOR		(300)					//�F�̃��Z�b�g�̃^�C�~���O
//-------------------------------------------------------------------------------
//�v���g�^�C�v�錾
//-------------------------------------------------------------------------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMSG, WPARAM wParam, LPARAM lParam);
//-------------------------------------------------------------------------------
//
//���C���֐�
//
//-------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int CmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),					//WNDCLASSEX�̃������T�C�Y���w��
		CS_CLASSDC,							//�\������E�B���h�E�̃X�^�C����ݒ�
		WindowProc,							//�E�B���h�E�v���V�[�W���̃A�h���X(�֐���)���w��
		0,									//�ʏ�͎g�p���Ȃ��̂�0
		0,									//�ʏ�͎g�p���Ȃ��̂�0
		hInstance,							//windows�̈����̃C���X�^���X�n���h���w��
		LoadIcon(NULL,IDI_APPLICATION),		//�^�X�N�o�[�Ɏg�p�҂̃A�C�R���ݒ�
		LoadCursor(NULL,IDC_ARROW),			//�g�p����}�E�X�J�[�\���w��
		(HBRUSH)(COLOR_WINDOW + 1),			//�E�B���h�E�N���C�A���g�̈�̐F�w��
		NULL,								//���j���[���w��
		CLASS_NAME,							//�E�B���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION)		//�������A�C�R���̎w��
	};

	HWND hWnd;		//�E�B���h�E�n���h��
	MSG msg;		//���b�Z�[�W���i�[����ϐ�

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�E�B���h�E�̐���
	hWnd = CreateWindowEx(0,					//�g���E�B���h�E�X�^�C��
						CLASS_NAME,				//�E�B���h�E�N���X��
						WINDOW_NAME,			//�E�B���h�E�̖��O
						WS_OVERLAPPEDWINDOW,	//�E�B���h�E�X�^�C��
						CW_USEDEFAULT,			//�E�B���h�E�����X���W
						CW_USEDEFAULT,			//�E�B���h�E�����Y���W
						SCREEN_WIDTH,			//�E�B���h�E�̕�
						SCREEN_HEIGHT,			//�E�B���h�E�̍��� 
						NULL,					//�e�E�B���h�E�̃n���h��
						NULL,					//���j���[�������͎q�E�B���h�EID
						hInstance,				//�C���X�^���X�n���h��
						NULL);					//�E�B���h�E�쐬�f�[�^

	//�E�B���h�E�̕\��
	ShowWindow(hWnd, CmdShow);
	UpdateWindow(hWnd);

	//���b�Z�[�W���[�v(���b�Z�[�W�L���[����̃��b�Z�[�W�擾)
	while (GetMessage(&msg, NULL, 0, 0) != 0)
	{
		//���b�Z�[�W�̖|��Ƒ��o
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//�E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);
	return (int)msg.wParam;
}

//-------------------------------------------------------------------------------
//
//�E�B���h�E�v���V�[�W���֐�
//
//-------------------------------------------------------------------------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//�ϐ��錾
	int nID;									//YES��NO��
	HWND hWndButton000;							//�I���{�^��
	//�d��֌W
	HWND hWndButton001;							//[+]�{�^��
	HWND hWndButton002;							//[-]�{�^��
	HWND hWndButton003;							//[*]�{�^��
	HWND hWndButton004;							//[/]�{�^��
	HWND hWndButton005;							//�����{�^��1
	HWND hWndButton006;							//�����{�^��2
	HWND hWndButton007;							//�S�����{�^��
	static HWND hWndEdit000;					//���l���͗�1
	static HWND hWndEdit001;					//���l���͗�2
	static HWND hWndEdit002;					//���l�o�͗�
	char aData000[64], aData001[64];			//���͂��ꂽ���l
	char aAnswer[64];							//�o�͂��鐔�l
	int nData000, nData001;						//�v�Z�p�̕ϐ�
	int nAnswer;								//�v�Z�p�̕ϐ�
	//��ʕ`�ʊ֌W
	HDC hDC;									//�f�o�C�X�R���e�L�X�g�̃n���h��(GDI)
	PAINTSTRUCT ps;								//�E�B���h�E�̃N���C�A���g�̈��`�悷�鎞�Ɏg�p������
	HPEN hPen000, hPenOld;						//�y���̃n���h��
	static int aPosX[3] = {10,300,100};			//�O�p�`�̒��_��X���W
	static int aPosY[3] = {10,20,200};			//�O�p�`�̒��_��Y���W
	static int aSpeedX[3] = {6, 5, 9};			//X�����̈ړ��̑���
	static int aSpeedY[3] = {3, 6, 2};			//Y�����̈ړ��̑���
	static int nRed = 0;						//��
	static int nGreen = 0;						//��
	static int nBlue = 0;						//��
	static int nColorCount = 0;					//�F�̕ς�����񐔂��J�E���g
	int nCount;									//for���̃J�E���g

	const RECT rect = { 0,0,SCREEN_WIDTH , SCREEN_HEIGHT };

	switch (uMsg)
	{
		//��񂾂�����
	case WM_CREATE:
		//�^�C�}�[�̐ݒ�(WM_TIMER���b�Z�[�W�����I�ɔ���)
		SetTimer(hWnd, ID_TIMER, TIMER_INTERVAL, NULL);

		//�{�^��000(�I���{�^��)�̍쐬
		hWndButton000 = CreateWindowEx(0,
									"BUTTON",
									" ",
									(WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON),		//�q�E�B���h�E|��������|�����{�^��
									360, 300, 100, 40,								//���W�Ƙg�̑傫��	
									hWnd,											//�e�E�B���h�E
									(HMENU)ID_BUTTON000,							//ID
									(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),	//�C���X�^���X�n���h��(�A�v���̎��ʎq)
									NULL);
		//�{�^��000�E�B���h�E�ɕ\�����镶����
		SetWindowText(hWndButton000, "�I��");

		//�{�^��001([+]�{�^��)�̍쐬
		hWndButton001 = CreateWindowEx(0,
									"BUTTON", 
									" ",
									(WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON),		//�q�E�B���h�E|��������|�����{�^��
									50, 100, 50, 50,								//���W�Ƙg�̑傫��	
									hWnd,											//�e�E�B���h�E
									(HMENU)ID_BUTTON001,							//ID
									(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),	//�C���X�^���X�n���h��(�A�v���̎��ʎq)
									NULL);
		//�{�^��001�E�B���h�E�ɕ\�����镶����
		SetWindowText(hWndButton001, "+");

		//�{�^��002([-]�{�^��)�̍쐬
		hWndButton002 = CreateWindowEx(0,
									"BUTTON",
									" ",
									(WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON),		//�q�E�B���h�E|��������|�����{�^��
									120, 100, 50, 50,								//���W�Ƙg�̑傫��	
									hWnd,											//�e�E�B���h�E
									(HMENU)ID_BUTTON002,							//ID
									(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),	//�C���X�^���X�n���h��(�A�v���̎��ʎq)
									NULL);
		//�{�^��002�E�B���h�E�ɕ\�����镶����
		SetWindowText(hWndButton002, "-");

		//�{�^��003([*]�{�^��)�̍쐬
		hWndButton003 = CreateWindowEx(0,
									"BUTTON",
									" ",
									(WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON),		//�q�E�B���h�E|��������|�����{�^��
									190, 100, 50, 50,								//���W�Ƙg�̑傫��	
									hWnd,											//�e�E�B���h�E
									(HMENU)ID_BUTTON003,							//ID
									(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),	//�C���X�^���X�n���h��(�A�v���̎��ʎq)
									NULL);
		//�{�^��003�E�B���h�E�ɕ\�����镶����
		SetWindowText(hWndButton003, "*");

		//�{�^��004([/]�{�^��)�̍쐬
		hWndButton004 = CreateWindowEx(0,
									"BUTTON",
									" ",
									(WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON),		//�q�E�B���h�E|��������|�����{�^��
									260, 100, 50, 50,								//���W�Ƙg�̑傫��	
									hWnd,											//�e�E�B���h�E
									(HMENU)ID_BUTTON004,							//ID
									(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),	//�C���X�^���X�n���h��(�A�v���̎��ʎq)
									NULL);
		//�{�^��004�E�B���h�E�ɕ\�����镶����
		SetWindowText(hWndButton004, "/");

		//�{�^��005(�����{�^��1)�̍쐬
		hWndButton005 = CreateWindowEx(0,
									"BUTTON",
									" ",
									(WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON),		//�q�E�B���h�E|��������|�����{�^��
									350, 50, 100, 25,								//���W�Ƙg�̑傫��	
									hWnd,											//�e�E�B���h�E
									(HMENU)ID_BUTTON005,							//ID
									(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),	//�C���X�^���X�n���h��(�A�v���̎��ʎq)
									NULL);
		//�{�^��005�E�B���h�E�ɕ\�����镶����
		SetWindowText(hWndButton005, "������");

		//�{�^��006(�����{�^��2)�̍쐬
		hWndButton006 = CreateWindowEx(0,
									"BUTTON",
									" ",
									(WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON),		//�q�E�B���h�E|��������|�����{�^��
									350, 175, 100, 25,								//���W�Ƙg�̑傫��	
									hWnd,											//�e�E�B���h�E
									(HMENU)ID_BUTTON006,							//ID
									(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),	//�C���X�^���X�n���h��(�A�v���̎��ʎq)
									NULL);
		//�{�^��006�E�B���h�E�ɕ\�����镶����
		SetWindowText(hWndButton006, "������");

		//�{�^��007(�S�����{�^��)�̍쐬
		hWndButton007 = CreateWindowEx(0,
									"BUTTON",
									" ",
									(WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON),		//�q�E�B���h�E|��������|�����{�^��
									350, 250, 100, 25,								//���W�Ƙg�̑傫��	
									hWnd,											//�e�E�B���h�E
									(HMENU)ID_BUTTON007,							//ID
									(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),	//�C���X�^���X�n���h��(�A�v���̎��ʎq)
									NULL);
		//�{�^��007�E�B���h�E�ɕ\�����镶����
		SetWindowText(hWndButton007, "�S����");


		//�G�f�B�b�g000(���l���͗�1)���쐬
		hWndEdit000 = CreateWindowEx(0,
									"EDIT",
									" ",
									(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT),	//�q�E�B���h�E|��������|���E��|�E��
									100, 50, 200, 25,								//���W�Ƙg�̑傫��
									hWnd,											//�e�E�B���h�E
									(HMENU)ID_EDIT000,								//ID
									(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),	//�C���X�^���X�n���h��(�A�v���̎��ʎq)
									NULL);

		//�G�f�B�b�g001(���l���͗�2)���쐬
		hWndEdit001 = CreateWindowEx(0,
									"EDIT",
									" ",
									(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT),	//�q�E�B���h�E|��������|���E��|�E��
									100, 175, 200, 25,								//���W�Ƙg�̑傫��
									hWnd,											//�e�E�B���h�E
									(HMENU)ID_EDIT001,								//ID
									(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),	//�C���X�^���X�n���h��(�A�v���̎��ʎq)
									NULL);

		//�G�f�B�b�g002(���l�o�͗�)���쐬
		hWndEdit002 = CreateWindowEx(0,
									"EDIT",
									" ",
									(WS_CHILD | WS_VISIBLE | WS_BORDER | WS_DISABLED |ES_RIGHT),	//�q�E�B���h�E|��������|���E��|���������s��|�E��
									100, 250, 200, 25,												//���W�Ƙg�̑傫��
									hWnd,															//�e�E�B���h�E
									(HMENU)ID_EDIT002,												//ID
									(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),					//�C���X�^���X�n���h��(�A�v���̎��ʎq)
									NULL);
		break;

		//�E�B���h�E�j�����b�Z�[�W
	case WM_DESTROY:
		//WM_QUIT ���b�Z�[�W��Ԃ� (�v���O�����I��)
		PostQuitMessage(0);
		break;

		//�L�[�����ꂽ�ۂ̃��b�Z�[�W
	case WM_KEYDOWN:
		//�L�[�����݂�
		switch (wParam)
		{
			//ESC�L�[�������ꂽ�ۂ̃��b�Z�[�W
		case VK_ESCAPE:
			//���b�Z�[�W�̕\��
			nID = MessageBox(hWnd, "�I���H", "�I�����܂����H", MB_YESNO);
			//[YES]��I�����ꂽ�ꍇ
			if (nID == IDYES)
			{
				//�E�B���h�E��j��(WM_DESTROY�𔭐�)
				DestroyWindow(hWnd);
			}
			break;
		}
		break;

		//�{�^���������ꂽ�ۂ̃��b�Z�[�W
	case WM_COMMAND:
		//�I���{�^���������ꂽ�ꍇ
		if (LOWORD(wParam) == ID_BUTTON000)
		{
			//���b�Z�[�W�̕\��
			nID = MessageBox(hWnd, "�I���H", "�I���܂����H", MB_YESNO);
			//[YES]��I�����ꂽ�ꍇ
			if (nID == IDYES)
			{
				//�E�B���h�E��j��(WM_DESTROY�𔭐�)
				DestroyWindow(hWnd);
			}
		}
		else if (LOWORD(wParam) == ID_BUTTON001 || LOWORD(wParam) == ID_BUTTON002 ||
				LOWORD(wParam) == ID_BUTTON003 || LOWORD(wParam) == ID_BUTTON004)
		{	//�v�Z�{�^���������ꂽ�ꍇ

			//�G�f�B�b�g�E�B���h�E000,001����e�L�X�g�擾
			GetWindowText(hWndEdit000, &aData000[0], 256);
			GetWindowText(hWndEdit001, &aData001[0], 256);

			//������𐔒l�ɕϊ�
			nData000 = atoi(&aData000[0]);
			nData001 = atoi(&aData001[0]);

			//[+]���������ꍇ
			if (LOWORD(wParam) == ID_BUTTON001)
			{
				nAnswer = nData000 + nData001;
			}
			else if (LOWORD(wParam) == ID_BUTTON002)
			{	//[-]���������ꍇ
				nAnswer = nData000 - nData001;
			}
			else if (LOWORD(wParam) == ID_BUTTON003)
			{	//[*]���������ꍇ
				nAnswer = nData000 * nData001;
			}
			else if (LOWORD(wParam) == ID_BUTTON004)
			{	//[/]���������ꍇ
				//���l���͗�2��0�������Ă����ꍇ
				if (nData001 == 0)
				{
					//������0�ɂ���
					nAnswer = 0;
				}
				else
				{
					//�v�Z������
					nAnswer = nData000 / nData001;
				}
			}
			//�ϐ��Ƀe�L�X�g�Őݒ�
			wsprintf(&aAnswer[0], "%d", nAnswer);
			//�G�f�B�b�g002�E�B���h�E(�o�͗�)�Ƀe�L�X�g�ݒ�
			SetWindowText(hWndEdit002, &aAnswer[0]);
		}
		else if (LOWORD(wParam) == ID_BUTTON005)
		{	//�����{�^��1�������ꂽ�ꍇ
			//���l���͗�1����������
			SetWindowText(hWndEdit000, "");
		}
		else if (LOWORD(wParam) == ID_BUTTON006)
		{	//�����{�^��2�������ꂽ�ꍇ
			//���l���͗�2����������
			SetWindowText(hWndEdit001, "");
		}
		else if (LOWORD(wParam) == ID_BUTTON007)
		{	//�S�����{�^��2�������ꂽ�ꍇ
			//���l���͗������ׂď�������
			SetWindowText(hWndEdit000, "");
			SetWindowText(hWndEdit001, "");
			SetWindowText(hWndEdit002, "");
		}
		break;

		//�~�{�^���������ꂽ�ۂ̃��b�Z�[�W
	case WM_CLOSE:
		//���b�Z�[�W��\��
		nID = MessageBox(hWnd, "��߂�H", "��߂܂����H", MB_YESNO);
		//YES��I�����ꂽ�ꍇ
		if (nID == IDYES)
		{
			//�E�B���h�E��j��(WM_DESTROY�𔭐�)
			DestroyWindow(hWnd);
		}
		else
		{
			//�����I�ɔ�����
			return 0;
		}
		break;

		//�^�C�}�[�̍ۂ̃��b�Z�[�W
	case WM_TIMER:
		//���_�̐��J��Ԃ�
		for (nCount = 0; nCount < 3; nCount++)
		{
			//X���W����ʒ[�ɍs�����Ƃ�
			if (aPosX[nCount] <= 0 || aPosX[nCount] >= SCREEN_WIDTH - 10)
			{
				//��ʊO�ɍs�����Ƃ��ɉ�ʒ[�Ɉړ�����
				if (aPosX[nCount] >= SCREEN_WIDTH - 10)
				{
					aPosX[nCount] = SCREEN_WIDTH - 10;
				}
				else if (aPosX[nCount] >= 0)
				{
					aPosX[nCount] = 0;
				}
				//�ړ��̕������t�����ɂ���
				aSpeedX[nCount] *= -1;
			}

			//Y���W����ʒ[�ɍs�����Ƃ�
			if (aPosY[nCount] <= 0 || aPosY[nCount] >= SCREEN_HEIGHT - 30)
			{
				//��ʊO�ɍs�����Ƃ��ɉ�ʒ[�Ɉړ�����
				if (aPosY[nCount] >= SCREEN_HEIGHT - 30)
				{
					aPosY[nCount] = SCREEN_HEIGHT - 30;
				}
				else if (aPosY[nCount] >= 0)
				{
					aPosY[nCount] = 0;
				}
				//�ړ��̕������t�����ɂ���
				aSpeedY[nCount] *= -1;
			}
			//X���W��aSpeedX��������
			aPosX[nCount] += aSpeedX[nCount];
			//Y���W��aSpeedY��������
			aPosY[nCount] += aSpeedY[nCount];
		}
		nRed +=2 ;		//�Ԃ̐F��ω�����
		nGreen += 3;	//�΂̐F��ω�����
		nBlue += 5;		//�̐F��ω�����
		nColorCount++;	//�F�̕ς�����񐔂��J�E���g����

		//�����̈�̋�������(WM_PAINT���b�Z�[�W�𔭐�)
		InvalidateRect(hWnd, &rect, FALSE);
		break;

		//��ʕ`�惁�b�Z�[�W
	case WM_PAINT:
		//�`��J�n
		hDC = BeginPaint(hWnd, &ps);
		//�F�̕ς�����񐔂�[RESET_COLOR]�ɂȂ�����
		if (nColorCount == RESET_COLOR)
		{
			//�h��Ԃ�����
			FillRect(hDC, &rect, NULL);
			//�J�E���g��0�ɂ���
			nColorCount = 0;
		}
		//�y���𐶐�����
		hPen000 = CreatePen(PS_SOLID, 1, RGB(nRed, nBlue, nGreen));
		//�y����I������
		hPenOld = (HPEN)SelectObject(hDC, hPen000);

		//�����`�� (�O�p�`)
		MoveToEx(hDC, aPosX[0], aPosY[0], NULL);
		LineTo(hDC, aPosX[1], aPosY[1]);
		LineTo(hDC, aPosX[2], aPosY[2]);
		LineTo(hDC, aPosX[0], aPosY[0]);

		//�y����I������
		SelectObject(hDC, hPenOld);

		//�y����j������
		DeleteObject(hPen000);

		//�`��I��
		EndPaint(hWnd, &ps);
		break;

		//�E�N���b�N���������ۂ̃��b�Z�[�W
	case WM_LBUTTONDOWN:
		//�E�B���h�E�Ƀt�H�[�J�X�����킹��
		SetFocus(hWnd);
		break;

	default:
		break;
	}
		//�K��̏������
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
}