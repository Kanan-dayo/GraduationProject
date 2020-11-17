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

//-------------------------------------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------------------------------------
#define DECODINGMANA_FILENAME "data/TEXT/DecodingUI_Info.txt"

//-------------------------------------------------------------------------------------------------------------
// �ÓI�����o�̏�����
//-------------------------------------------------------------------------------------------------------------
CHash *    CDecodingManager::m_pHash = nullptr;										// �n�b�V���|�C���^
LPDIRECT3DTEXTURE9 CDecodingManager::m_pTexture[UI_MAX] = Mybfunc_array(nullptr);	// �e�N�X�`�����
SETINGINFO CDecodingManager::m_Seting[UI_MAX];										// �ݒ���

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
	char * Key[UI_MAX] =
	{
		{ "Backlight" },
		{ "TellThePicture" },
		{ "ShapeMemorization" },
		{ "CordCutting" },
		{ "Maze" },
		{ "Simon" },
		{ "Nowmaking" },
	};
	// �f�[�^
	char * Data[UI_MAX] =
	{
		{ "0" },
		{ "1" },
		{ "2" },
		{ "3" },
		{ "4" },
		{ "5" },
		{ "6" },
	};
	// �n�b�V���̍쐬
	m_pHash = CHash::Create();

	// �n�b�V���ɑ}������
	for (int nCntHash = 0; nCntHash < UI_MAX; nCntHash++)
	{
		m_pHash->Insert(Key[nCntHash], Data[nCntHash]);
	}

}

//-------------------------------------------------------------------------------------------------------------
// �n�b�V���̊J��
//-------------------------------------------------------------------------------------------------------------
void CDecodingManager::ReleaseHash(void)
{
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
	m_pTexture[UI_TELLTHEPICTURE]    = CTexture::GetTexture(CTexture::TEX_UI_DECODING_T00);
	m_pTexture[UI_SHAPEMEMORIZATION] = CTexture::GetTexture(CTexture::TEX_UI_DECODING_T01);
	m_pTexture[UI_CORDCUTTING]       = CTexture::GetTexture(CTexture::TEX_UI_DECODING_T02);
	m_pTexture[UI_MAZE]              = CTexture::GetTexture(CTexture::TEX_UI_DECODING_T03);
	m_pTexture[UI_SIMON]             = CTexture::GetTexture(CTexture::TEX_UI_DECODING_T04);
	m_pTexture[UI_NOWMAKING]         = CTexture::GetTexture(CTexture::TEX_UI_DECODING_T05);
	m_pTexture[UI_BACKLIGHT]         = CTexture::GetTexture(CTexture::TEX_UI_DECODING_BACKLIGHT);

	// �t�@�C���ǂݍ���
	if (CLoadFile::ReadLineByLineFromFile(DECODINGMANA_FILENAME, ReadFromLine) != CLoadFile::LR_SUCCESS)
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
	for (int nCntUI = 0; nCntUI < UI_MAX; nCntUI++)
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
	for (int nCntUI = 0; nCntUI < UI_MAX; nCntUI++)
	{
		// UI�̐���
		m_pUi[nCntUI] = CDecodingUI::Create(m_Seting[nCntUI]);
		// �e�N�X�`���̘A��
		m_pUi[nCntUI]->BindTexture(m_pTexture[nCntUI]);
	}

	m_mode = MODE_SELECT;

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
		MLB_CASE(CDecodingManager::MODE_SELECT)UpdateSelect();
		MLB_CASE(CDecodingManager::MODE_SHOW)  UpdateShow();
		MLB_CASEEND;
	}
}

//-------------------------------------------------------------------------------------------------------------
// �`��
//-------------------------------------------------------------------------------------------------------------
void CDecodingManager::Draw()
{
}

//-------------------------------------------------------------------------------------------------------------
// �I�����鎞�̍X�V����
//-------------------------------------------------------------------------------------------------------------
void CDecodingManager::UpdateSelect(void)
{
	// �ϐ��錾
	CMouse *    pMouse = CManager::GetMouse();	// �}�E�X�̃|�C���^
	D3DXVECTOR2 MousePos = pMouse->GetMousePos();	// �}�E�X�̈ʒu

	for (int nCntUi = 0; nCntUi < UI_MAX; nCntUi++)
	{

	}
}

//-------------------------------------------------------------------------------------------------------------
// ��ǈ⏑�\�����Ă���Ƃ��̏���
//-------------------------------------------------------------------------------------------------------------
void CDecodingManager::UpdateShow(void)
{
}

//-------------------------------------------------------------------------------------------------------------
// 1�s�������ǂݎ��
//-------------------------------------------------------------------------------------------------------------
void CDecodingManager::ReadFromLine(CONST_STRING cnpLine, CONST_STRING cnpEntryType, CONST_STRING cnpEntryData)
{
	// �ϐ��錾
	D3DXVECTOR3 pos   = MYLIB_3DVECTOR_ZERO;										// �ʒu
	D3DXVECTOR2 size  = MYLIB_2DVECTOR_ZERO;										// �傫��
	D3DXCOLOR   col   = MYLIB_D3DXCOR_SET;											// �F
	float       fData = MYLIB_FLOAT_UNSET;											// float�^�̃f�[�^
	int         nData = MYLIB_INT_UNSET;											// int�^�̃f�[�^
	SETINGINFO* pSet  = &m_Seting[atoi(m_pHash->Search((char*)cnpEntryType))];		// �ݒ���̃|�C���^

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
}
