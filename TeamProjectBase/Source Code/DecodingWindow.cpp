//*************************************************************************************************************
//
// ��Ǐ��̃}�l�[�W���[[���� [DecodingManager.h]
// Author:IKUTO SEKINE
//
//*************************************************************************************************************
//-------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------------------
#include "DecodingWindow.h"
#include "DecodingUI.h"
#include "myhash.h"
#include "texture.h"
#include "mouse.h"
#include "manager.h"

//-------------------------------------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------------------------------------
#define DECODINGWINDOW_FILENAME "data/TEXT/InitWindowInfo.txt"

//-------------------------------------------------------------------------------------------------------------
// �ÓI�����o�ϐ��̏�����
//-------------------------------------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CDecodingWindow::m_pTexture[TEX_MAX] = Mybfunc_array(nullptr);
CHash *            CDecodingWindow::m_pHash	            = nullptr;
SETINGINFO         CDecodingWindow::m_Seting[TYPE_MAX];

//-------------------------------------------------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------------------------------------------------
CDecodingWindow::CDecodingWindow()
{
}

//-------------------------------------------------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------------------------------------------------
CDecodingWindow::~CDecodingWindow()
{
}

//-------------------------------------------------------------------------------------------------------------
// �n�b�V���̍쐬
//-------------------------------------------------------------------------------------------------------------
void CDecodingWindow::MakeHash(void)
{
	// �L�[�f�[�^
	char * Key[TYPE_MAX] =
	{
		{ "Window" },
		{ "Close" },
		{ "ScrollBar" },
		{ "ScrollHandle" },
	};
	// �f�[�^
	char * Data[TYPE_MAX] =
	{
		{ "0" },
		{ "1" },
		{ "2" },
		{ "3" },
	};
	// �n�b�V���̍쐬
	m_pHash = CHash::Create();

	// �n�b�V���ɑ}������
	for (int nCntHash = 0; nCntHash < TYPE_MAX; nCntHash++)
	{
		m_pHash->Insert(Key[nCntHash], Data[nCntHash]);
	}

}

//-------------------------------------------------------------------------------------------------------------
// �n�b�V���̊J��
//-------------------------------------------------------------------------------------------------------------
void CDecodingWindow::ReleaseHash(void)
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
HRESULT CDecodingWindow::Load(void)
{
	// �e�N�X�`�������擾����
	m_pTexture[TEX_TELLTHEPICTURE]    = CTexture::GetTexture(CTexture::TEX_UI_DECODING_D00);
	m_pTexture[TEX_SHAPEMEMORIZATION] = CTexture::GetTexture(CTexture::TEX_UI_DECODING_D01);
	m_pTexture[TEX_CORDCUTTING]       = CTexture::GetTexture(CTexture::TEX_UI_DECODING_D02);
	m_pTexture[TEX_MAZE]              = CTexture::GetTexture(CTexture::TEX_UI_DECODING_D03);
	m_pTexture[TEX_SIMON]             = CTexture::GetTexture(CTexture::TEX_UI_DECODING_D04);
	m_pTexture[TEX_NOWMAKING]         = CTexture::GetTexture(CTexture::TEX_UI_DECODING_D05);

	// �ݒ���̏�����
	for (int nCntSet = 0; nCntSet < TYPE_MAX; nCntSet++)
	{
		m_Seting[nCntSet] = SETINGINFO();
	}

	// �t�@�C���ǂݍ���
	if (CLoadFile::ReadLineByLineFromFile(DECODINGWINDOW_FILENAME, ReadFromLine) != CLoadFile::LR_SUCCESS)
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
void CDecodingWindow::UnLoad(void)
{
	for (int nCntUI = 0; nCntUI < TEX_MAX; nCntUI++)
	{
		m_pTexture[nCntUI] = nullptr;
	}
}

//-------------------------------------------------------------------------------------------------------------
// ����
//-------------------------------------------------------------------------------------------------------------
CDecodingWindow* CDecodingWindow::Create(void)
{
	// �X�}�[�g�|�C���^�̐���
	CDecodingWindow* pWindow = new CDecodingWindow;
	// ������
	pWindow->Init();
	return pWindow;
}

//-------------------------------------------------------------------------------------------------------------
// ������
//-------------------------------------------------------------------------------------------------------------
HRESULT CDecodingWindow::Init()
{
	// UI�̍쐬
	MakeUI();

	// �X�N���[���n���h���̑傫���̐ݒ��ύX
	m_pUi[TYPE_SCROLLHANDLE]->SetSize(D3DXVECTOR2(m_pUi[TYPE_SCROLLHANDLE]->GetSize().x, m_Seting[TYPE_SCROLLBAR].size.y * 0.75f));
	m_Seting[TYPE_SCROLLHANDLE].size.y = m_Seting[TYPE_SCROLLBAR].size.y * 0.75f;

	// ����̌v�Z
	//m_ScrollRange.fMax = m_Seting[TYPE_SCROLLBAR].size.y*MYLIB_HALF_SIZE - (m_Seting[TYPE_SCROLLHANDLE].size.y*MYLIB_HALF_SIZE);
	//m_ScrollRange.fMin = -m_Seting[TYPE_SCROLLBAR].size.y*MYLIB_HALF_SIZE + (m_Seting[TYPE_SCROLLHANDLE].size.y*MYLIB_HALF_SIZE);
	//m_fScrollRangeValue = m_ScrollRange.GetFloatValue();

	// �X�N���[���n���h���̈ʒu�̐ݒ��ύX
	//m_Seting[TYPE_SCROLLHANDLE].pos.y = m_Seting[TYPE_SCROLLBAR].pos.y + m_ScrollRange.fMin - m_Seting[TYPE_SCROLLBAR].pos.y;

	// �e�̐ݒ�
	SetPosAccordingParent();
	return S_OK;
}

//-------------------------------------------------------------------------------------------------------------
// �X�V
//-------------------------------------------------------------------------------------------------------------
void CDecodingWindow::Update()
{
}

//-------------------------------------------------------------------------------------------------------------
// �`��
//-------------------------------------------------------------------------------------------------------------
void CDecodingWindow::Draw()
{
}

//-------------------------------------------------------------------------------------------------------------
// UI�̍쐬
//-------------------------------------------------------------------------------------------------------------
void CDecodingWindow::MakeUI(void)
{
	// ���[�v
	for (int nCntType = 0; nCntType < TYPE_MAX; nCntType++)
	{// UI�̐���
		m_pUi[nCntType] = CDecodingUI::Create(m_Seting[nCntType]);
		m_pUi[nCntType]->BindTexture(m_pTexture[nCntType]);
	}
}

//-------------------------------------------------------------------------------------------------------------
// �e�ɏ]���Ĉʒu��ݒ肷��
//-------------------------------------------------------------------------------------------------------------
void CDecodingWindow::SetPosAccordingParent(void)
{
	// �ϐ��錾
	SETINGINFO* pSet = &m_Seting[0];				// �ݒ���̃|�C���^
	// ���[�v
	for (int nCntType = 0; nCntType < TYPE_MAX; nCntType++)
	{
		// �eID�̎擾
		int nParentID = pSet[nCntType].nParentID;
		if (nParentID != -1)
		{	// �ʒu��ݒ肷��
			m_pUi[nCntType]->SetPos(m_pUi[nParentID]->GetPos() + pSet[nCntType].pos);
			// �e���̐ݒ�
			m_pUi[nCntType]->SetParent(m_pUi[nParentID].get());
			// ���_���̍X�V
			m_pUi[nCntType]->UpdateVertex(true);
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
// 1�s�������ǂݎ��
//-------------------------------------------------------------------------------------------------------------
void CDecodingWindow::ReadFromLine(CONST_STRING cnpLine, CONST_STRING cnpEntryType, CONST_STRING cnpEntryData)
{
	// �ϐ��錾
	D3DXVECTOR3 pos = MYLIB_3DVECTOR_ZERO;	// �ʒu
	D3DXVECTOR2 size = MYLIB_2DVECTOR_ZERO;	// �傫��
	D3DXCOLOR   col = MYLIB_D3DXCOR_SET;		// �F
	float       fData = MYLIB_FLOAT_UNSET;		// float�^�̃f�[�^
	int         nData = MYLIB_INT_UNSET;		// int�^�̃f�[�^
	char        sData[MYLIB_STRINGSIZE] = { 0 };
	SETINGINFO* pSet = nullptr;				// �ݒ���̃|�C���^

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
