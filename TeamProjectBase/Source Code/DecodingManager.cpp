//*************************************************************************************************************
//
// ��Ǐ��̃}�l�[�W���[[���� [DecodingManager.h]
// Author:IKUTO SEKINE
//
//*************************************************************************************************************
//-------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------------------
#include "DecodingManager.h"
#include "DecodingUI.h"
#include "myhash.h"
#include "texture.h"
#include "mouse.h"
#include "manager.h"
#include "DecodingWindow.h"

//-------------------------------------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------------------------------------
#define DECODINGMANA_UIINFO_FILENAME   "data/TEXT/DecodingUI_Info.txt"
#define DECODINGMANA_WINDINFO_FILENAME "data/TEXT/DecodingWind_Info.txt"

//-------------------------------------------------------------------------------------------------------------
// �ÓI�����o�̏�����
//-------------------------------------------------------------------------------------------------------------
CHash *            CDecodingManager::m_pHash = nullptr;								// �n�b�V���|�C���^
LPDIRECT3DTEXTURE9 CDecodingManager::m_pTexture[TEX_MAX] = Mlf_array(nullptr);	// �e�N�X�`�����
SETINGINFO         CDecodingManager::m_Seting[UI_MAX];								// �ݒ���
WINDOW_SETING      CDecodingManager::m_WindSeting[WIND_MAX];						// �E�B���h�E�̐ݒ���

//-------------------------------------------------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------------------------------------------------
CDecodingManager::CDecodingManager()
{
}

//-------------------------------------------------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------------------------------------------------
CDecodingManager::~CDecodingManager()
{
}

//-------------------------------------------------------------------------------------------------------------
// �n�b�V���̍쐬
//-------------------------------------------------------------------------------------------------------------
void CDecodingManager::MakeHash(void)
{
	// �L�[�f�[�^
	char * Key[UI_MAX + WIND_MAX] =
	{
		{ "Backlight" },
		{ "TellThePicture" },
		{ "ShapeMemorization" },
		{ "CordCutting" },
		{ "Maze" },
		{ "Simon" },
		{ "TellThePicture_Wind" },
		{ "ShapeMemorization_Wind" },
		{ "CordCutting_Wind" },
		{ "Maze_Wind" },
		{ "Simon_Wind" },
	};
	// �f�[�^
	char * Data[UI_MAX + WIND_MAX] =
	{
		{ "0" },
		{ "1" },
		{ "2" },
		{ "3" },
		{ "4" },
		{ "5" },
		{ "0" },
		{ "1" },
		{ "2" },
		{ "3" },
		{ "4" },
	};
	// �n�b�V���̍쐬
	m_pHash = CHash::Create();

	// �n�b�V���ɑ}������
	for (int nCntHash = 0; nCntHash < UI_MAX + WIND_MAX; nCntHash++)
	{
		m_pHash->Insert(Key[nCntHash], Data[nCntHash]);
	}

	// �E�B���h�̃n�b�V���̍쐬
	CDecodingWindow::MakeHash();
}

//-------------------------------------------------------------------------------------------------------------
// �n�b�V���̊J��
//-------------------------------------------------------------------------------------------------------------
void CDecodingManager::ReleaseHash(void)
{
	// �E�B���h�E�̃n�b�V���̊J��
	CDecodingWindow::ReleaseHash();

	// null�`�F�b�N
	if (m_pHash != nullptr)
	{
		// �n�b�V���e�[�u���̊J��
		m_pHash->ReleaseHashtable();
		// �n�b�V���̔j��
		delete m_pHash;
		m_pHash = nullptr;
	}
}

//-------------------------------------------------------------------------------------------------------------
// �ǂݍ���
//-------------------------------------------------------------------------------------------------------------
HRESULT CDecodingManager::Load(void)
{
	// �e�N�X�`�������擾����
	m_pTexture[TEX_TELLTHEPICTURE]      = CTexture::GetTexture(CTexture::TEX_UI_DECODING_T00);
	m_pTexture[TEX_SHAPEMEMORIZATION]   = CTexture::GetTexture(CTexture::TEX_UI_DECODING_T01);
	m_pTexture[TEX_CORDCUTTING]         = CTexture::GetTexture(CTexture::TEX_UI_DECODING_T02);
	m_pTexture[TEX_MAZE]                = CTexture::GetTexture(CTexture::TEX_UI_DECODING_T03);
	m_pTexture[TEX_SIMON]               = CTexture::GetTexture(CTexture::TEX_UI_DECODING_T04);
	m_pTexture[TEX_BACKLIGHT]           = CTexture::GetTexture(CTexture::TEX_UI_DECODING_BACKLIGHT);

	// �ݒ���̏�����
	for (int nCntSet = 0; nCntSet < UI_MAX ; nCntSet++)
	{
		m_Seting[nCntSet] = SETINGINFO();
	}

	// �t�@�C���ǂݍ���
	if (CLoadFile::ReadLineByLineFromFile(DECODINGMANA_UIINFO_FILENAME, UiInfoReadFromLine) != CLoadFile::LR_SUCCESS)
	{
#ifdef _DEBUG
		std::cout << "<<<<<<CDecodingManager�̃t�@�C���ǂݍ��݂����s���܂����B>>>>>>\n";
#endif // _DEBUG
		return E_FAIL;
	}
	// �t�@�C���ǂݍ���
	if (CLoadFile::ReadLineByLineFromFile(DECODINGMANA_WINDINFO_FILENAME, WindInfoReadFromLine) != CLoadFile::LR_SUCCESS)
	{
#ifdef _DEBUG
		std::cout << "<<<<<<CDecodingManager�̃t�@�C���ǂݍ��݂����s���܂����B>>>>>>\n";
#endif // _DEBUG
		return E_FAIL;
	}

	return S_OK;
}

//-------------------------------------------------------------------------------------------------------------
// �J��
//-------------------------------------------------------------------------------------------------------------
void CDecodingManager::Unload(void)
{
	for (int nCntUI = 0; nCntUI < TEX_MAX; nCntUI++)
	{
		m_pTexture[nCntUI] = nullptr;
	}
}

//-------------------------------------------------------------------------------------------------------------
// ����
//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<CDecodingManager> CDecodingManager::Create(void)
{
	// �X�}�[�g�|�C���^�̐���
	std::shared_ptr<CDecodingManager> pManager = std::make_shared<CDecodingManager>();
	// ������
	pManager->Init();

	//Scene�ŊǗ�
	pManager->SetObjType(OBJTYPE_UI);
	pManager->AddSharedList(pManager);
	return pManager;
}

//-------------------------------------------------------------------------------------------------------------
// ������
//-------------------------------------------------------------------------------------------------------------
HRESULT CDecodingManager::Init()
{
	// UI�̐���
	CreateUi();
	// �E�B���h�E�̐���
	CreateWind();

	// �e�����ƂɈʒu��ݒ肷��
	SetPosAccordingParent();

	// �I�����Ă���ԍ��̏�����
	m_nSelectIndex = -1;

	// ���[�h�̏�����
	m_mode = MODE_SELECT;
	m_modeNext = m_mode;

	// �A�N�e�B�u�ȃE�B���h�E�̃|�C���^��������
	m_pActiveWind = nullptr;

	return S_OK;
}

//-------------------------------------------------------------------------------------------------------------
// �I��
//-------------------------------------------------------------------------------------------------------------
void CDecodingManager::Update()
{
	// ���[�h�ʂ̏���
	switch (m_mode)
	{
		ML_CASE(CDecodingManager::MODE_SELECT)  UpdateSelect();		// �I�����[�h
		ML_CASE(CDecodingManager::MODE_CONNECT) UpdateConnect();	// �ڑ����[�h
		ML_CASE(CDecodingManager::MODE_SHOW)    UpdateShow();		// �\�����[�h
		ML_CASEEND;
	}
}

//-------------------------------------------------------------------------------------------------------------
// �`��
//-------------------------------------------------------------------------------------------------------------
void CDecodingManager::Draw()
{
}

//-------------------------------------------------------------------------------------------------------------
// ���[�h�̐ݒ�
//-------------------------------------------------------------------------------------------------------------
void CDecodingManager::SstMode(MODE mode)
{
	// �ő傩��ڑ����[�h�͈͓̔��̎�
	if (Mlf_InRange(mode, MODE_MAX, MODE_CONNECT))
	{
		// �ڑ����[�h�ɐݒ�
		m_mode = CDecodingManager::MODE_CONNECT;
		// �����̃��[�h�ɐݒ�
		m_modeNext = mode;
		// �ڑ����[�h�̏�����
		InitConnect();
	}
}

//-------------------------------------------------------------------------------------------------------------
// UI�̐���
//-------------------------------------------------------------------------------------------------------------
void CDecodingManager::CreateUi(void)
{
	for (int nCntUI = 0; nCntUI < UI_MAX; nCntUI++)
	{// UI�̐���
		m_pUi[nCntUI] = CDecodingUI::Create(m_Seting[nCntUI]);
		// �e�N�X�`���̘A��
		m_pUi[nCntUI]->BindTexture(m_pTexture[nCntUI]);
	}
}

//-------------------------------------------------------------------------------------------------------------
// �E�B���h�E�̐���
//-------------------------------------------------------------------------------------------------------------
void CDecodingManager::CreateWind(void)
{
	// �E�B���h�E�̃X�P�[���̍ő�̐ݒ�
	CDecodingWindow::SetScalMax(1.0f);

	for (int nCntWind = 0; nCntWind < WIND_MAX; nCntWind++)
	{// �E�B���h�E�̐���
		m_pWind[nCntWind] = CDecodingWindow::Create(m_WindSeting[nCntWind]);
		// �E�B���h�E�e�N�X�`���̐ݒ�
		m_pWind[nCntWind]->SetWindowTexture(nCntWind);
	}
}

//-------------------------------------------------------------------------------------------------------------
// �e�ɏ]���Ĉʒu��ݒ肷��
//-------------------------------------------------------------------------------------------------------------
void CDecodingManager::SetPosAccordingParent(void)
{
	for (int nCntUI = 0; nCntUI < UI_MAX; nCntUI++)
	{// �eID�̎擾
		int nParentID = m_Seting[nCntUI].nParentID;
		// �eID���ݒ肳��Ă�����
		if (nParentID != -1)
		{
			// �e�̐ݒ�
			m_pUi[nCntUI]->SetParent(m_pUi[nParentID].get());
			// �ʒu�̐ݒ�
			m_pUi[nCntUI]->SetPos(m_pUi[nParentID]->GetPos() + m_pUi[nCntUI]->GetParent()->vecParent);
			// ���_�ʒu�̍X�V
			m_pUi[nCntUI]->UpdateVertex(true);
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
// �ڑ����[�h�̏�����
//-------------------------------------------------------------------------------------------------------------
void CDecodingManager::InitConnect(void)
{
	// �����̐ݒ�
	switch (m_modeNext)
	{
		ML_CASE(CDecodingManager::MODE_SELECT) m_pActiveWind->SetSign(-1);
		ML_CASE(CDecodingManager::MODE_SHOW)   m_pActiveWind->SetSign(1);
		ML_CASEEND;
	}

	// �o�����̏�����
	m_pActiveWind->InitAppearInfo();
}

//-------------------------------------------------------------------------------------------------------------
// �I�����鎞�̍X�V����
//-------------------------------------------------------------------------------------------------------------
void CDecodingManager::UpdateSelect(void)
{
	// �ϐ��錾
	CMouse *    pMouse = CManager::GetMouse();		// �}�E�X�̃|�C���^
	D3DXVECTOR2 MousePos = pMouse->GetMousePos();	// �}�E�X�̈ʒu
	bool        bOverlap = false;					// �d�Ȃ��Ă���t���O

	// UI�����[�v
	for (int nCntUi = UI_TELLTHEPICTURE; nCntUi < UI_MAX; nCntUi++)
	{
		// 2D�̏Փ˔���
		if (m_pUi[nCntUi]->Collision2D(MousePos) == false)
		{// �I���t���O������
			m_pUi[nCntUi]->SetSelectFlag(false);
			// �������΂�
			continue;
		}
		// �I���t���O�������Ă��鎞
		if (m_pUi[nCntUi]->GetSelectFlag() == false)
		{// �I���t���O�𗧂Ă�
			m_pUi[nCntUi]->SetSelectFlag(true);
			// ���_���̍X�V
			m_pUi[UI_BACKLIGHT]->UpdateVertex((D3DXVECTOR3 *)m_pUi[nCntUi]->GetPosPtr());
			// �`��t���O��ݒ�
			m_pUi[UI_BACKLIGHT]->SetDispFlag(true);
			m_nSelectIndex = nCntUi;
		}
		bOverlap = true;
		// �E�N���b�N�𗣂��������I�����ꂽ�ԍ��Ɠ����Ƃ�
		if (pMouse->GetRelease(0) &&
			m_nSelectIndex == nCntUi)
		{
			m_pActiveWind = m_pWind[nCntUi - 1].get();
			m_pActiveWind->PreparingAppear();
			SstMode(MODE_SHOW);
		}
	}
	// �d�Ȃ��Ă��Ȃ������Ƃ�
	if (bOverlap == false)
	{// �`��t���O������
		m_pUi[UI_BACKLIGHT]->SetDispFlag(false);
		m_nSelectIndex = -1;
		// �}�E�X��������Ă��Ȃ���
		if (!pMouse->GetPress(0))
		{
			m_nSelectIndex = -1;
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
// �ڑ����[�h�̎��̍X�V����
//-------------------------------------------------------------------------------------------------------------
void CDecodingManager::UpdateConnect(void)
{
	switch (m_modeNext)
	{
		ML_CASE(CDecodingManager::MODE_SELECT)
		{
			if (m_pActiveWind->Disappearance() == true)
			{
				// ���̃��[�h�ɐݒ�
				m_mode = m_modeNext;
				// �A�N�e�B�u�ȃE�B���h�E�̃|�C���^��������
				m_pActiveWind = nullptr;
			}
		}
		ML_CASE(CDecodingManager::MODE_SHOW)
		{
			if (m_pActiveWind->Appearance() == true)
			{
				// ���̃��[�h�ɐݒ�
				m_mode = m_modeNext;
			}
		}
		ML_CASEEND;
	}
}

//-------------------------------------------------------------------------------------------------------------
// ��ǈ⏑�\�����Ă���Ƃ��̏���
//-------------------------------------------------------------------------------------------------------------
void CDecodingManager::UpdateShow(void)
{
	// �ϐ��錾
	CMouse *    pMouse = CManager::GetMouse();		// �}�E�X�̃|�C���^
	D3DXVECTOR2 MousePos = pMouse->GetMousePos();	// �}�E�X�̈ʒu

	// ����{�^���̏���
	if (m_pActiveWind->CloseButtonProc(pMouse, &MousePos) == true)
	{
		SstMode(MODE_SELECT);
	}
	else
	{
		// �X�N���[������
		m_pActiveWind->ScrollProc(pMouse, &MousePos);
	}
}

//-------------------------------------------------------------------------------------------------------------
// 1�s�������ǂݎ��
//-------------------------------------------------------------------------------------------------------------
void CDecodingManager::UiInfoReadFromLine(CONST_STRING cnpLine, CONST_STRING cnpEntryType, CONST_STRING cnpEntryData)
{
	// �ϐ��錾
	D3DXVECTOR3 pos                     = MYLIB_3DVECTOR_ZERO;				// �ʒu
	D3DXVECTOR2 size                    = MYLIB_2DVECTOR_ZERO;				// �傫��
	D3DXCOLOR   col                     = MYLIB_D3DXCOR_SET;				// �F
	float       fData                   = MYLIB_FLOAT_UNSET;				// float�^�̃f�[�^
	int         nData                   = MYLIB_INT_UNSET;					// int�^�̃f�[�^
	char        sData[MYLIB_STRINGSIZE] = Mlf_array(MYLIB_CHAR_UNSET);	// �������̃f�[�^
	SETINGINFO* pSet                    = nullptr;							// �ݒ���̃|�C���^

	pSet = &m_Seting[atoi(m_pHash->Search((char*)cnpEntryType))];
	if (sscanf(cnpLine, "pos = %f %f", &pos.x, &pos.y) == 2)
	{
		pSet->pos = pos;
	}
	else if (sscanf(cnpLine, "size = %f %f", &size.x, &size.y) == 2)
	{
		pSet->size = size;
	}
	else if (sscanf(cnpLine, "col = %f %f %f %f", &col.r, &col.g, &col.b, &col.a) == 4)
	{
		pSet->col = col;
	}
	else if (sscanf(cnpLine, "angle = %f", &fData) == 1)
	{
		pSet->fAngle = fData;
	}
	else if (sscanf(cnpLine, "originType = %d", &nData) == 1)
	{
		pSet->OriginType = (ORIGINVERTEXTYPE)nData;
	}
	else if (sscanf(cnpLine, "disp = %d", &nData) == 1)
	{
		pSet->bDisp = (nData == 1);
	}
	else if (sscanf(cnpLine, "Parent = %s", &sData[0]) == 1)
	{
		pSet->nParentID = atoi(m_pHash->Search(sData));
	}
}

//-------------------------------------------------------------------------------------------------------------
// 1�s�������ǂݎ��
//-------------------------------------------------------------------------------------------------------------
void CDecodingManager::WindInfoReadFromLine(CONST_STRING cnpLine, CONST_STRING cnpEntryType, CONST_STRING cnpEntryData)
{
	// �ϐ��錾
	D3DXVECTOR3    pos                     = MYLIB_3DVECTOR_ZERO;								// �ʒu
	D3DXVECTOR2    dataF2                  = MYLIB_2DVECTOR_ZERO;								// float�^�̃f�[�^�Q��
	D3DXCOLOR      col                     = MYLIB_D3DXCOR_SET;									// �F
	float          fData                   = MYLIB_FLOAT_UNSET;									// float�^�̃f�[�^
	int            nData                   = MYLIB_INT_UNSET;									// int�^�̃f�[�^
	char           sData[MYLIB_STRINGSIZE] = Mlf_array(MYLIB_CHAR_UNSET);					// �������̃f�[�^
	WINDOW_SETING* pSet                    = nullptr;											// �ݒ���̃|�C���^

	pSet = &m_WindSeting[atoi(m_pHash->Search((char*)cnpEntryType))];
	if (sscanf(cnpLine, "pos = %f %f", &pos.x, &pos.y) == 2)
	{
		pSet->pos = pos;
	}
	else if (sscanf(cnpLine, "size = %f %f", &dataF2.x, &dataF2.y) == 2)
	{
		pSet->size = dataF2;
	}
	else if (sscanf(cnpLine, "col = %f %f %f %f", &col.r, &col.g, &col.b, &col.a) == 4)
	{
		pSet->col = col;
	}
	else if (sscanf(cnpLine, "AspectRatio = %f %f", &dataF2.x, &dataF2.y) == 2)
	{
		pSet->AspectRatio = dataF2;
	}
	else if (sscanf(cnpLine, "SizeScal = %f %f", &dataF2.x, &dataF2.y) == 2)
	{
		pSet->SizeScal = dataF2;
	}
}
