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
#define DECODINGMANA_FILENAME "data/TEXT/DecodingUI_Info.txt"

//-------------------------------------------------------------------------------------------------------------
// �ÓI�����o�̏�����
//-------------------------------------------------------------------------------------------------------------
CHash *            CDecodingManager::m_pHash = nullptr;										// �n�b�V���|�C���^
LPDIRECT3DTEXTURE9 CDecodingManager::m_pTexture[TEX_MAX] = Mybfunc_array(nullptr);	// �e�N�X�`�����
SETINGINFO         CDecodingManager::m_Seting[UI_MAX];										// �ݒ���
int                CDecodingManager::m_nFrameMax = MYLIB_INT_UNSET;

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
		{ "Document" },
		{ "Close" },
		{ "ScrollBar" },
		{ "ScrollHandle" },
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
		{ "7" },
		{ "8" },
		{ "9" },
		{ "10" },
	};
	// �n�b�V���̍쐬
	m_pHash = CHash::Create();

	// �n�b�V���ɑ}������
	for (int nCntHash = 0; nCntHash < UI_MAX; nCntHash++)
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
	// 


	// �e�N�X�`�������擾����
	m_pTexture[TEX_TELLTHEPICTURE]      = CTexture::GetTexture(CTexture::TEX_UI_DECODING_T00);
	m_pTexture[TEX_SHAPEMEMORIZATION]   = CTexture::GetTexture(CTexture::TEX_UI_DECODING_T01);
	m_pTexture[TEX_CORDCUTTING]         = CTexture::GetTexture(CTexture::TEX_UI_DECODING_T02);
	m_pTexture[TEX_MAZE]                = CTexture::GetTexture(CTexture::TEX_UI_DECODING_T03);
	m_pTexture[TEX_SIMON]               = CTexture::GetTexture(CTexture::TEX_UI_DECODING_T04);
	m_pTexture[TEX_NOWMAKING]           = CTexture::GetTexture(CTexture::TEX_UI_DECODING_T05);
	m_pTexture[TEX_BACKLIGHT]           = CTexture::GetTexture(CTexture::TEX_UI_DECODING_BACKLIGHT);
	m_pTexture[TEX_D_TELLTHEPICTURE]    = CTexture::GetTexture(CTexture::TEX_UI_DECODING_D00);
	m_pTexture[TEX_D_SHAPEMEMORIZATION] = CTexture::GetTexture(CTexture::TEX_UI_DECODING_D01);
	m_pTexture[TEX_D_CORDCUTTING]       = CTexture::GetTexture(CTexture::TEX_UI_DECODING_D02);
	m_pTexture[TEX_D_MAZE]              = CTexture::GetTexture(CTexture::TEX_UI_DECODING_D03);
	m_pTexture[TEX_D_SIMON]             = CTexture::GetTexture(CTexture::TEX_UI_DECODING_D04);
	m_pTexture[TEX_D_NOWMAKING]         = CTexture::GetTexture(CTexture::TEX_UI_DECODING_D05);
	m_pTexture[TEX_CLOSE]               = CTexture::GetTexture(CTexture::TEX_UI_DECODING_CLOSE);
	m_pTexture[TEX_SCROLLBAR]           = CTexture::GetTexture(CTexture::TEX_UI_DECODING_S_BAR);
	m_pTexture[TEX_SCROLLHANDLE]        = CTexture::GetTexture(CTexture::TEX_UI_DECODING_S_HANDLE);

	// �ݒ���̏�����
	for (int nCntSet = 0; nCntSet < UI_MAX ; nCntSet++)
	{
		m_Seting[nCntSet] = SETINGINFO();
	}

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

	RANGE ra;
	// �X�N���[���n���h���̑傫���̐ݒ��ύX
	m_pUi[UI_SCROLLHANDLE]->SetSize(D3DXVECTOR2(m_pUi[UI_SCROLLHANDLE]->GetSize().x, m_Seting[UI_SCROLLBAR].size.y * 0.75f));
	m_Seting[UI_SCROLLHANDLE].size.y = m_Seting[UI_SCROLLBAR].size.y * 0.75f;

	// ����̌v�Z
	m_ScrollRange.fMax = m_Seting[UI_SCROLLBAR].size.y*MYLIB_HALF_SIZE - (m_Seting[UI_SCROLLHANDLE].size.y*MYLIB_HALF_SIZE);
	m_ScrollRange.fMin = -m_Seting[UI_SCROLLBAR].size.y*MYLIB_HALF_SIZE + (m_Seting[UI_SCROLLHANDLE].size.y*MYLIB_HALF_SIZE);
	m_fScrollRangeValue = m_ScrollRange.GetFloatValue();

	// �X�N���[���n���h���̈ʒu�̐ݒ��ύX
	m_Seting[UI_SCROLLHANDLE].pos.y = m_Seting[UI_SCROLLBAR].pos.y + m_ScrollRange.fMin - m_Seting[UI_SCROLLBAR].pos.y;

	// �e�����ƂɈʒu��ݒ肷��
	SetPosAccordingParent();

	// �h�L�������g��UV���̏�����
	InitDocumentUVInfo();

	// �I�����Ă���ԍ��̏�����
	m_nSelectIndex = -1;

	// ���[�h�̏�����
	m_mode = MODE_SELECT;
	m_modeNext = m_mode;

	// �ڑ����[�h�̏�����
	InitConnect();

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
		MLB_CASE(CDecodingManager::MODE_SELECT) UpdateSelect();
		MLB_CASE(CDecodingManager::MODE_CONNECT)UpdateConnect();
		MLB_CASE(CDecodingManager::MODE_SHOW)   UpdateShow();
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
// ���[�h�̐ݒ�
//-------------------------------------------------------------------------------------------------------------
void CDecodingManager::SstMode(MODE mode)
{
	m_mode = CDecodingManager::MODE_CONNECT;
	m_modeNext = mode;
	// �ڑ����[�h�̏�����
	InitConnect();
}

//-------------------------------------------------------------------------------------------------------------
// UI�̐���
//-------------------------------------------------------------------------------------------------------------
void CDecodingManager::CreateUi(void)
{
	for (int nCntUI = 0; nCntUI < UI_MAX; nCntUI++)
	{
		// UI�̐���
		m_pUi[nCntUI] = CDecodingUI::Create(m_Seting[nCntUI]);
		if (nCntUI > UI_DOCUMENT)
		{
			// �e�N�X�`���̘A��
			m_pUi[nCntUI]->BindTexture(m_pTexture[nCntUI + 5]);
		}
		else {
			// �e�N�X�`���̘A��
			m_pUi[nCntUI]->BindTexture(m_pTexture[nCntUI]);
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
// �e�ɏ]���Ĉʒu��ݒ肷��
//-------------------------------------------------------------------------------------------------------------
void CDecodingManager::SetPosAccordingParent(void)
{
	for (int nCntUI = 0; nCntUI < UI_MAX; nCntUI++)
	{
		int nParentID = m_Seting[nCntUI].nParentID;
		if (nParentID != -1)
		{
			m_pUi[nCntUI]->SetPos(m_pUi[nParentID]->GetPos() + m_Seting[nCntUI].pos);
			m_pUi[nCntUI]->SetParent(m_pUi[nParentID].get());
			m_pUi[nCntUI]->UpdateVertex(true);
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
// �h�L�������g��UV���̏�����
//-------------------------------------------------------------------------------------------------------------
void CDecodingManager::InitDocumentUVInfo(void)
{
	CDecodingUI::POLYVERTEXSUVINFO SetingTex;
	SetingTex.pos.u = 0.5f;
	SetingTex.pos.v = 0.75f * 0.5f;
	SetingTex.size.u = 1.0f;
	SetingTex.size.v = 0.75f;
	m_pUi[UI_DOCUMENT]->UpdateVertex(NULL, NULL, NULL, &SetingTex);
}

//-------------------------------------------------------------------------------------------------------------
// �ڑ����[�h�̏�����
//-------------------------------------------------------------------------------------------------------------
void CDecodingManager::InitConnect(void)
{
	switch (m_modeNext)
	{
		MLB_CASE(CDecodingManager::MODE_SELECT) m_nSign = -1;
		MLB_CASE(CDecodingManager::MODE_SHOW)   m_nSign = 1;
		MLB_CASEEND;
	}

	m_nFrame = 0;
	m_fScalValue = (1.0f / (m_nFrameMax + 1) * m_nSign);
	if (m_fScalValue >= 0)
	{
		m_fScal = 0.0f;
	}
	else
	{
		m_fScal = 1.0f;
	}
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
	for (int nCntUi = UI_TELLTHEPICTURE; nCntUi < UI_DOCUMENT; nCntUi++)
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
			AppeaDocument(nCntUi);
			SstMode(MODE_SHOW);
		}
	}
	// �d�Ȃ��Ă��Ȃ������Ƃ�
	if (bOverlap == false)
	{// �`��t���O������
		m_pUi[UI_BACKLIGHT]->SetDispFlag(false);
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
	// �t���[�������Z����
	m_nFrame++;

	// �t���[�����ő�ȏ�̎�
	if (m_nFrame > m_nFrameMax)
	{
		// �t���[����������
		m_nFrame = 0;
		// ���̃��[�h�ɐݒ�
		m_mode = m_modeNext;

		switch (m_mode)
		{
			MLB_CASE(CDecodingManager::MODE_SELECT)
				// �E�B���h�E�̍X�V
				m_pUi[UI_DOCUMENT]->SetDispFlag(false);
				// ���̂ق��̍X�V
				for (int nCntUi = UI_CLOSE; nCntUi < UI_MAX; nCntUi++)
				{
					m_pUi[nCntUi]->SetDispFlag(false);
				}
			MLB_CASE(CDecodingManager::MODE_SHOW)   DisplayDocumentsInPlace();
			MLB_CASEEND;
		}
	}

	// �g��l�����Z
	m_fScal += m_fScalValue;
	// �E�B���h�E�̍X�V
	m_pUi[UI_DOCUMENT]->SetSize(m_Seting[UI_DOCUMENT].size *m_fScal);
	m_pUi[UI_DOCUMENT]->UpdateVertex(true);
	// ���̂ق��̍X�V
	for (int nCntUi = UI_CLOSE; nCntUi < UI_MAX; nCntUi++)
	{
		m_pUi[nCntUi]->SetPos(m_pUi[nCntUi]->GetParent()->pParent->GetPos() + m_pUi[nCntUi]->GetParent()->vecParent * m_fScal);
		m_pUi[nCntUi]->SetSize(m_Seting[nCntUi].size *m_fScal);
		m_pUi[nCntUi]->UpdateVertex(true);
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
	CloseButtonProc(pMouse, &MousePos);
	// �X�N���[������
	ScrollProc(pMouse, &MousePos);
}

//-------------------------------------------------------------------------------------------------------------
// ����{�^���̏���
//-------------------------------------------------------------------------------------------------------------
void CDecodingManager::CloseButtonProc(CMouse *pMouse, D3DXVECTOR2 *pMousePos)
{
	// 2D�̏Փ˔���
	if (m_pUi[UI_CLOSE]->Collision2D(*pMousePos) == false)
	{
		if (m_nSelectIndex != UI_SCROLLHANDLE)
		{
			m_nSelectIndex = -1;
		}
		return;
	}

	// �I���t���O�������Ă��鎞
	if (m_pUi[UI_CLOSE]->GetSelectFlag() == false)
	{// �I���t���O�𗧂Ă�
		m_pUi[UI_CLOSE]->SetSelectFlag(true);
	}
	// �E�N���b�N�𗣂��������I�����ꂽ�ԍ��Ɠ����Ƃ�
	if (pMouse->GetRelease(0) &&
		m_nSelectIndex == UI_CLOSE)
	{
		SstMode(MODE_SELECT);
	}
	// �}�E�X���������Ƃ�
	if (pMouse->GetTrigger(0))
	{
		m_nSelectIndex = UI_CLOSE;
	}

}

//-------------------------------------------------------------------------------------------------------------
// �X�N���[������
//-------------------------------------------------------------------------------------------------------------
void CDecodingManager::ScrollProc(CMouse * pMouse, D3DXVECTOR2 * pMousePos)
{
	// �X�N���[���n���h�����܂�
	PinchScrollHandle(pMouse, pMousePos);

	// �X�N���[���n���h���𓮂���
	MoveScrollHandle(pMouse, pMousePos);

	// �}�E�X�z�C�[���X�N���[��
	MouseWheelScroll(pMousePos);
}

//-------------------------------------------------------------------------------------------------------------
// �X�N���[���n���h�����܂�
//-------------------------------------------------------------------------------------------------------------
void CDecodingManager::PinchScrollHandle(CMouse * pMouse, D3DXVECTOR2 * pMousePos)
{
	// �X�N���[���o�[�𓮂�������
	if (m_pUi[UI_SCROLLHANDLE]->Collision2D(*pMousePos) == true &&
		pMouse->GetTrigger(0))
	{
		m_VecPinch_center = VEC2(m_pUi[UI_SCROLLHANDLE]->GetPos().x - pMousePos->x, m_pUi[UI_SCROLLHANDLE]->GetPos().y - pMousePos->y);
		m_nSelectIndex = UI_SCROLLHANDLE;
	}
}

//-------------------------------------------------------------------------------------------------------------
// �X�N���[���n���h���𓮂���
//-------------------------------------------------------------------------------------------------------------
void CDecodingManager::MoveScrollHandle(CMouse * pMouse, D3DXVECTOR2 * pMousePos)
{
	if (!pMouse->GetPress(0))
	{
		m_nSelectIndex = -1;
		return;
	}
	if (m_nSelectIndex == UI_SCROLLHANDLE)
	{
		m_pUi[UI_SCROLLHANDLE]->SetPosY(ScrollClamp(pMousePos, pMousePos->y + m_VecPinch_center.y));
		m_pUi[UI_SCROLLHANDLE]->UpdateVertex(true);
		// �h�L�������g���X�N���[������
		ScrollThroughDocument();
	}
}

//-------------------------------------------------------------------------------------------------------------
// �}�E�X�z�C�[���X�N���[��
//-------------------------------------------------------------------------------------------------------------
void CDecodingManager::MouseWheelScroll(D3DXVECTOR2 * pMousePos)
{
	if (m_nSelectIndex != -1)
	{
		return;
	}

	int nScrollValu = CMouse::GetScrollValue();
	if (nScrollValu == 0)
	{
		return;
	}
	m_pUi[UI_SCROLLHANDLE]->SetPosY(ScrollClamp(pMousePos, m_pUi[UI_SCROLLHANDLE]->GetPos().y -= nScrollValu *30.0f));
	m_pUi[UI_SCROLLHANDLE]->UpdateVertex(true);
	// �h�L�������g���X�N���[������
	ScrollThroughDocument();
}

//-------------------------------------------------------------------------------------------------------------
// �X�N���[���N�����v
//-------------------------------------------------------------------------------------------------------------
float CDecodingManager::ScrollClamp(D3DXVECTOR2 *pMousePos,float fPosY)
{
	// �ϐ��錾
	CDecodingUI * pScrollBar = m_pUi[UI_SCROLLBAR].get();
	CDecodingUI * pScrollHandle = m_pUi[UI_SCROLLHANDLE].get();

	// �g���Ɏ��߂�
	if (pScrollBar->GetPos().y + pScrollBar->GetSize().y *MYLIB_HALF_SIZE <= fPosY + pScrollHandle->GetSize().y*MYLIB_HALF_SIZE)
	{
		fPosY = (pScrollBar->GetPos().y + pScrollBar->GetSize().y*MYLIB_HALF_SIZE - (pScrollHandle->GetSize().y*MYLIB_HALF_SIZE));
		m_VecPinch_center = VEC2(pScrollHandle->GetPos().x - pMousePos->x, fPosY - pMousePos->y);
	}
	if (pScrollBar->GetPos().y - pScrollBar->GetSize().y *MYLIB_HALF_SIZE >= fPosY - pScrollHandle->GetSize().y*MYLIB_HALF_SIZE)
	{
		fPosY = (pScrollBar->GetPos().y - pScrollBar->GetSize().y*MYLIB_HALF_SIZE + (pScrollHandle->GetSize().y*MYLIB_HALF_SIZE));
		m_VecPinch_center = VEC2(pScrollHandle->GetPos().x - pMousePos->x, fPosY - pMousePos->y);
	}
	return fPosY;
}

//-------------------------------------------------------------------------------------------------------------
// �h�L�������g���X�N���[������
//-------------------------------------------------------------------------------------------------------------
void CDecodingManager::ScrollThroughDocument(void)
{
	// �x�N�g�����v�Z����
	float fVec = m_pUi[UI_SCROLLHANDLE]->GetPos().y - (m_pUi[UI_SCROLLBAR]->GetPos().y + m_ScrollRange.fMin);
	CDecodingUI::POLYVERTEXSUVINFO *pSetingTex = m_pUi[UI_DOCUMENT]->GetTex();
	float fBasePosY = (0.75f * 0.5f);
	float fScal = 1.0f - (fBasePosY + fBasePosY);
	pSetingTex->pos.v = (fBasePosY)+(fScal *  (fVec / m_fScrollRangeValue));
	m_pUi[UI_DOCUMENT]->UpdateVertex(false, false, true);
}

//-------------------------------------------------------------------------------------------------------------
// �h�L�������g�����̈ʒu�ɕ\������
//-------------------------------------------------------------------------------------------------------------
void CDecodingManager::DisplayDocumentsInPlace(void)
{
	m_pUi[UI_DOCUMENT]->SetDispFlag(true);
	m_pUi[UI_DOCUMENT]->SetSize(m_Seting[UI_DOCUMENT].size);
	m_pUi[UI_DOCUMENT]->UpdateVertex(true);

	for (int nCntUi = UI_CLOSE; nCntUi < UI_MAX; nCntUi++)
	{
		m_pUi[nCntUi]->SetDispFlag(true);
		m_pUi[nCntUi]->SetPos(m_pUi[nCntUi]->GetParent()->pParent->GetPos() + m_Seting[nCntUi].pos);
		m_pUi[nCntUi]->SetSize(m_Seting[nCntUi].size);
		m_pUi[nCntUi]->UpdateVertex(true);
	}
}

//-------------------------------------------------------------------------------------------------------------
// �h�L�������g�̏o��
//-------------------------------------------------------------------------------------------------------------
void CDecodingManager::AppeaDocument(int nCntUi)
{
	m_pUi[UI_DOCUMENT]->BindTexture(m_pTexture[nCntUi + 6]);
	m_pUi[UI_DOCUMENT]->SetDispFlag(true);
	m_pUi[UI_DOCUMENT]->SetSize(D3DXVECTOR2(0.0f, 0.0f));
	m_pUi[UI_DOCUMENT]->UpdateVertex(true);

	for (int nCntUi = UI_CLOSE; nCntUi < UI_MAX; nCntUi++)
	{
		m_pUi[nCntUi]->SetDispFlag(true);
		m_pUi[nCntUi]->SetPos(m_pUi[nCntUi]->GetParent()->pParent->GetPos());
		m_pUi[nCntUi]->SetSize(D3DXVECTOR2(0.0f, 0.0f));
		m_pUi[nCntUi]->UpdateVertex(true);
	}
}

//-------------------------------------------------------------------------------------------------------------
// �h�L�������g�̏���
//-------------------------------------------------------------------------------------------------------------
void CDecodingManager::DisAppeaDocument(void)
{
	m_pUi[UI_DOCUMENT]->SetDispFlag(false);
	for (int nCntUi = UI_CLOSE; nCntUi < UI_MAX; nCntUi++)
	{
		m_pUi[nCntUi]->SetDispFlag(false);
	}
}

//-------------------------------------------------------------------------------------------------------------
// 1�s�������ǂݎ��
//-------------------------------------------------------------------------------------------------------------
void CDecodingManager::ReadFromLine(CONST_STRING cnpLine, CONST_STRING cnpEntryType, CONST_STRING cnpEntryData)
{
	// �ϐ��錾
	D3DXVECTOR3 pos   = MYLIB_3DVECTOR_ZERO;	// �ʒu
	D3DXVECTOR2 size  = MYLIB_2DVECTOR_ZERO;	// �傫��
	D3DXCOLOR   col   = MYLIB_D3DXCOR_SET;		// �F
	float       fData = MYLIB_FLOAT_UNSET;		// float�^�̃f�[�^
	int         nData = MYLIB_INT_UNSET;		// int�^�̃f�[�^
	char        sData[MYLIB_STRINGSIZE] = { 0 };
	SETINGINFO* pSet  = nullptr;				// �ݒ���̃|�C���^
	if (strcmp(cnpEntryType, "SetUp") != 0)
	{
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
	else
	{
		if (sscanf(cnpLine, "ModeCount = %d", &nData) == 1)
		{
			m_nFrameMax = nData;
		}
	}
}
