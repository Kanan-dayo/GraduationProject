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
LPDIRECT3DTEXTURE9 CDecodingWindow::m_pTexture[TEX_MAX]      = Mlf_array(nullptr);
LPDIRECT3DTEXTURE9 CDecodingWindow::m_pDocTexture[TEX_W_MAX] = Mlf_array(nullptr);
CHash *            CDecodingWindow::m_pHash	                 = nullptr;
SETINGINFO         CDecodingWindow::m_InitSeting[TYPE_MAX];
int                CDecodingWindow::m_nFrameMax              = MYLIB_INT_UNSET;
float              CDecodingWindow::m_fSclaMax               = 1.0f;

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
		{ "Window"       },
		{ "Close"        },
		{ "ScrollBar"    },
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
	{// �n�b�V���e�[�u���̊J��
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
	m_pDocTexture[TEX_W_TELLTHEPICTURE]    = CTexture::GetTexture(CTexture::TEX_UI_DECODING_D00);
	m_pDocTexture[TEX_W_SHAPEMEMORIZATION] = CTexture::GetTexture(CTexture::TEX_UI_DECODING_D01);
	m_pDocTexture[TEX_W_CORDCUTTING]       = CTexture::GetTexture(CTexture::TEX_UI_DECODING_D02);
	m_pDocTexture[TEX_W_MAZE]              = CTexture::GetTexture(CTexture::TEX_UI_DECODING_D03);
	m_pDocTexture[TEX_W_SIMON]             = CTexture::GetTexture(CTexture::TEX_UI_DECODING_D04);
	m_pDocTexture[TEX_W_NOWMAKING]         = CTexture::GetTexture(CTexture::TEX_UI_DECODING_D05);

	m_pTexture[TEX_CLOSEBUTTON]            = CTexture::GetTexture(CTexture::TEX_UI_DECODING_CLOSE);
	m_pTexture[TEX_SCROLLBAR]              = CTexture::GetTexture(CTexture::TEX_UI_DECODING_S_BAR);
	m_pTexture[TEX_SCROLLHANDLE]           = CTexture::GetTexture(CTexture::TEX_UI_DECODING_S_HANDLE);

	// �ݒ���̏�����
	for (int nCntSet = 0; nCntSet < TYPE_MAX; nCntSet++)
	{
		m_InitSeting[nCntSet] = SETINGINFO();
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
std::shared_ptr<CDecodingWindow> CDecodingWindow::Create(WINDOW_SETING &Seting)
{
	// �X�}�[�g�|�C���^�̐���
	std::shared_ptr<CDecodingWindow> pWindow = std::make_shared<CDecodingWindow>();

	// ������
	pWindow->Init(Seting);
	return pWindow;
}

//-------------------------------------------------------------------------------------------------------------
// ������
//-------------------------------------------------------------------------------------------------------------
HRESULT CDecodingWindow::Init(WINDOW_SETING &Seting)
{
	// �ݒ�̏�����
	InitSeting(Seting);

	// UI�̍쐬
	MakeUI();

	// �h�L�������g��UV���̏�����
	InitDocumentUVInfo(Seting);

	// UV�̑傫���̎擾
	float *pSizeV = &m_pUi[TYPE_WINDOW]->GetTex()->size.v;

	// �X�N���[���n���h���̑傫���̐ݒ��ύX
	m_pUi[TYPE_SCROLLHANDLE]->SetSize(D3DXVECTOR2(m_pUi[TYPE_SCROLLHANDLE]->GetSize().x, m_Seting[TYPE_SCROLLBAR].size.y * *pSizeV));
	m_Seting[TYPE_SCROLLHANDLE].size.y = m_Seting[TYPE_SCROLLBAR].size.y * *pSizeV;

	// ����̌v�Z
	m_ScrollRange.max   =  m_Seting[TYPE_SCROLLBAR].size.y * MYLIB_HALF_SIZE - (m_Seting[TYPE_SCROLLHANDLE].size.y * MYLIB_HALF_SIZE);
	m_ScrollRange.min   = -m_Seting[TYPE_SCROLLBAR].size.y * MYLIB_HALF_SIZE + (m_Seting[TYPE_SCROLLHANDLE].size.y * MYLIB_HALF_SIZE);
	m_fScrollRangeValue =  m_ScrollRange.GetDifference();

	// �X�N���[���n���h���̈ʒu�̐ݒ��ύX
	m_Seting[TYPE_SCROLLHANDLE].pos.y = m_Seting[TYPE_SCROLLBAR].pos.y + m_ScrollRange.min - m_Seting[TYPE_SCROLLBAR].pos.y;

		// �e�̐ݒ�
	SetPosAccordingParent();

	// �����̐ݒ�
	SetSign(1);
	// �o�����̏�����
	InitAppearInfo();

	m_nSelectIndex = MYLIB_INT_UNSET;
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
// �o�����̏�����
//-------------------------------------------------------------------------------------------------------------
void CDecodingWindow::InitAppearInfo(void)
{
	m_nFrame = 0;
	m_fScalValue = (m_fSclaMax / (m_nFrameMax + 1) * m_nSign);

	if (m_nSign > 0)
	{
		m_fScal = 0.0f;
	}
	else
	{
		m_fScal = m_fSclaMax;
	}

}

//-------------------------------------------------------------------------------------------------------------
// �h�L�������g��UV���̏�����
//-------------------------------------------------------------------------------------------------------------
void CDecodingWindow::InitDocumentUVInfo(WINDOW_SETING &Seting)
{
	// �A�X�y�N�g��̐ݒ�
	m_AspectRatio = Seting.AspectRatio;
	// �傫���̊g�k���̐ݒ�
	m_SizeScal    = Seting.SizeScal;

	// �ϐ��錾
	POLYVERTEXSUVINFO SetingTex;	// �e�N�X�`��UV���
	float             fBaseRat;		// �x�[�X�̔䗦

	// �x�[�X�̔䗦���Z�o
	fBaseRat         = (m_AspectRatio.x < m_AspectRatio.y) ? m_AspectRatio.x : m_AspectRatio.y;
	// UV���W�̑傫�����v�Z
	SetingTex.size.u = m_SizeScal.x * (fBaseRat / m_AspectRatio.x);
	SetingTex.size.v = m_SizeScal.y * (fBaseRat / m_AspectRatio.y);
	// UV���W�̏����ʒu���Z�o(*0.5�͑傫���𒆉��ɂ��邽��)
	SetingTex.pos.u  = SetingTex.size.u * 0.5f;
	SetingTex.pos.v  = SetingTex.size.v * 0.5f;
	// ���_���̍X�V
	m_pUi[TYPE_WINDOW]->UpdateVertex(NULL, NULL, NULL, &SetingTex);

	// �X�N���[�������l�ʒu�̐ݒ�
	m_fScrInitPos    = SetingTex.pos.v;
}

//-------------------------------------------------------------------------------------------------------------
// �o������
//-------------------------------------------------------------------------------------------------------------
void CDecodingWindow::PreparingAppear(int nCntUi)
{
	m_pUi[TYPE_WINDOW]->BindTexture(m_pDocTexture[nCntUi - 1]);
	m_pUi[TYPE_WINDOW]->SetDispFlag(true);
	m_pUi[TYPE_WINDOW]->SetSize(D3DXVECTOR2(0.0f, 0.0f));
	m_pUi[TYPE_WINDOW]->UpdateVertex(true);

	for (int nCntUi = TYPE_CLOSEBUTTON; nCntUi < TYPE_MAX; nCntUi++)
	{
		m_pUi[nCntUi]->SetDispFlag(true);
		m_pUi[nCntUi]->SetPos(m_pUi[nCntUi]->GetParent()->pParent->GetPos());
		m_pUi[nCntUi]->SetSize(D3DXVECTOR2(0.0f, 0.0f));
		m_pUi[nCntUi]->UpdateVertex(true);
	}
}

//-------------------------------------------------------------------------------------------------------------
// �o��
//-------------------------------------------------------------------------------------------------------------
bool CDecodingWindow::Appearance(void)
{
	// �t���[���J�E���g�����Z
	m_nFrame++;
	// �t���[�����ő�ȏ�̎�
	if (m_nFrame > m_nFrameMax)
	{// �t���[���̏�����
		m_nFrame = 0;
		// �O�ʂ�\��
		Display();
		return true;
	}

	// �g��l�����Z
	m_fScal += m_fScalValue;
	// �E�B���h�E�̍X�V
	m_pUi[TYPE_WINDOW]->SetSize(m_Seting[TYPE_WINDOW].size *m_fScal);
	m_pUi[TYPE_WINDOW]->UpdateVertex(true);
	// ���̂ق��̍X�V
	for (int nCntUi = TYPE_CLOSEBUTTON; nCntUi < TYPE_MAX; nCntUi++)
	{
		m_pUi[nCntUi]->SetPos(m_pUi[nCntUi]->GetParent()->pParent->GetPos() + m_pUi[nCntUi]->GetParent()->vecParent * m_fScal);
		m_pUi[nCntUi]->SetSize(m_Seting[nCntUi].size *m_fScal);
		m_pUi[nCntUi]->UpdateVertex(true);
	}

	return false;
}

//-------------------------------------------------------------------------------------------------------------
// ����
//-------------------------------------------------------------------------------------------------------------
bool CDecodingWindow::Disappearance(void)
{
	// �t���[���J�E���g�����Z
	m_nFrame++;
	// �t���[�����ő�ȏ�̎�
	if (m_nFrame > m_nFrameMax)
	{// �t���[���̏�����
		m_nFrame = 0;
		// �O�ʂ�\�������Ȃ�
		DoNotDisplay();
		return true;
	}

	// �g��l�����Z
	m_fScal += m_fScalValue;
	// �E�B���h�E�̍X�V
	m_pUi[TYPE_WINDOW]->SetSize(m_Seting[TYPE_WINDOW].size *m_fScal);
	m_pUi[TYPE_WINDOW]->UpdateVertex(true);
	// ���̂ق��̍X�V
	for (int nCntUi = TYPE_CLOSEBUTTON; nCntUi < TYPE_MAX; nCntUi++)
	{
		m_pUi[nCntUi]->SetPos(m_pUi[nCntUi]->GetParent()->pParent->GetPos() + m_pUi[nCntUi]->GetParent()->vecParent * m_fScal);
		m_pUi[nCntUi]->SetSize(m_Seting[nCntUi].size *m_fScal);
		m_pUi[nCntUi]->UpdateVertex(true);
	}
	return false;
}

//-------------------------------------------------------------------------------------------------------------
// �\��������
//-------------------------------------------------------------------------------------------------------------
void CDecodingWindow::Display(void)
{
	// �E�B���h�E�̍X�V
	m_pUi[TYPE_WINDOW]->SetSize(m_Seting[TYPE_WINDOW].size);
	m_pUi[TYPE_WINDOW]->UpdateVertex(true);
	// ���̂ق��̍X�V
	for (int nCntUi = TYPE_CLOSEBUTTON; nCntUi < TYPE_MAX; nCntUi++)
	{
		m_pUi[nCntUi]->SetPos(m_pUi[nCntUi]->GetParent()->pParent->GetPos() + m_pUi[nCntUi]->GetParent()->vecParent);
		m_pUi[nCntUi]->SetSize(m_Seting[nCntUi].size);
		m_pUi[nCntUi]->UpdateVertex(true);
	}
}

//-------------------------------------------------------------------------------------------------------------
// �\�������Ȃ�
//-------------------------------------------------------------------------------------------------------------
void CDecodingWindow::DoNotDisplay(void)
{
	// �E�B���h�E�̍X�V
	m_pUi[TYPE_WINDOW]->SetDispFlag(false);
	// ���̂ق��̍X�V
	for (int nCntUi = TYPE_CLOSEBUTTON; nCntUi < TYPE_MAX; nCntUi++)
	{
		m_pUi[nCntUi]->SetDispFlag(false);
	}
}

//-------------------------------------------------------------------------------------------------------------
// ����{�^���̏���
//-------------------------------------------------------------------------------------------------------------
bool CDecodingWindow::CloseButtonProc(CMouse *pMouse, D3DXVECTOR2 *pMousePos)
{
	// 2D�̏Փ˔���
	if (m_pUi[TYPE_CLOSEBUTTON]->Collision2D(*pMousePos) == false)
	{
		if (m_nSelectIndex != TYPE_SCROLLHANDLE)
		{
			m_nSelectIndex = -1;
		}
		// �E�N���b�N�𗣂�����
		if (pMouse->GetRelease(0))
		{
			ChangeColor(m_pUi[TYPE_CLOSEBUTTON].get(), m_Seting[TYPE_CLOSEBUTTON].col);
			return false;
		}
	}
	else
	{
		// �}�E�X���������Ƃ�
		if (pMouse->GetTrigger(0))
		{
			ChangeColor(m_pUi[TYPE_CLOSEBUTTON].get(), D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
			m_nSelectIndex = TYPE_CLOSEBUTTON;
		}
		// �E�N���b�N�𗣂��������I�����ꂽ�ԍ��Ɠ����Ƃ�
		if (pMouse->GetRelease(0) &&
			m_nSelectIndex == TYPE_CLOSEBUTTON)
		{
			ChangeColor(m_pUi[TYPE_CLOSEBUTTON].get(), m_Seting[TYPE_CLOSEBUTTON].col);
			return true;
		}
	}

	return false;
}

//-------------------------------------------------------------------------------------------------------------
// �X�N���[������
//-------------------------------------------------------------------------------------------------------------
void CDecodingWindow::ScrollProc(CMouse * pMouse, D3DXVECTOR2 * pMousePos)
{
	// �X�N���[���n���h���𓮂���
	MoveScrollHandle(pMouse, pMousePos);
	// �}�E�X�z�C�[���X�N���[��
	MouseWheelScroll(pMousePos);
}

//-------------------------------------------------------------------------------------------------------------
// �X�N���[���n���h���𓮂���
//-------------------------------------------------------------------------------------------------------------
void CDecodingWindow::MoveScrollHandle(CMouse * pMouse, D3DXVECTOR2 * pMousePos)
{
	// �}�E�X���n���h���ɐڐG���Ă��邩�ǂ���
	if (m_pUi[TYPE_SCROLLHANDLE]->Collision2D(*pMousePos) == true)
	{
		// �}�E�X�������ꂽ�Ƃ�
		if (pMouse->GetTrigger(0))
		{
			// �I������Ă���ԍ��ɑ��
			m_nSelectIndex = TYPE_SCROLLHANDLE;
			// �F��ύX
			ChangeColor(m_pUi[TYPE_SCROLLHANDLE].get(), m_Seting[TYPE_SCROLLHANDLE].col);
			m_VecPinch_Center = VEC2(m_pUi[TYPE_SCROLLHANDLE]->GetPos().x - pMousePos->x, m_pUi[TYPE_SCROLLHANDLE]->GetPos().y - pMousePos->y);
		}
		// ����ȊO
		else if (m_nSelectIndex != TYPE_SCROLLHANDLE)
		{
			if (m_pUi[TYPE_SCROLLHANDLE]->GetStateSwitchFlag() == true)
			{
				// �F��ύX
				ChangeColor(m_pUi[TYPE_SCROLLHANDLE].get(), D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f));
			}
		}
	}


	// �}�E�X��������Ă��鎞���I������Ă���ԍ����n���h���̎�
	if (pMouse->GetPress(0) && m_nSelectIndex == TYPE_SCROLLHANDLE)
	{
		m_pUi[TYPE_SCROLLHANDLE]->SetPosY(ScrollClamp(pMousePos, pMousePos->y + m_VecPinch_Center.y));
		m_pUi[TYPE_SCROLLHANDLE]->SetParent(m_pUi[TYPE_SCROLLHANDLE].get());
		m_pUi[TYPE_SCROLLHANDLE]->UpdateVertex(true);
		// �h�L�������g���X�N���[������
		ScrollScreen();
	}
	// �I������Ă���ԍ����n���h���̎�
	else if (pMouse->GetRelease(0) && m_nSelectIndex == TYPE_SCROLLHANDLE)
	{
		if (m_pUi[TYPE_SCROLLHANDLE]->GetState() == CDecodingUI::STATE_OVERLAP)
		{
			// �F��ύX
			ChangeColor(m_pUi[TYPE_SCROLLHANDLE].get(), D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f));
		}
		else
		{
			// �F��ύX
			ChangeColor(m_pUi[TYPE_SCROLLHANDLE].get(), D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		}
		m_nSelectIndex = -1;
	}
	else if(m_pUi[TYPE_SCROLLHANDLE]->GetState() == CDecodingUI::STATE_NORMAL &&
		m_pUi[TYPE_SCROLLHANDLE]->GetStateSwitchFlag() == true)
	{
		// �F��ύX
		ChangeColor(m_pUi[TYPE_SCROLLHANDLE].get(), D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
	}
}

//-------------------------------------------------------------------------------------------------------------
// �}�E�X�z�C�[���ŃX�N���[��
//-------------------------------------------------------------------------------------------------------------
void CDecodingWindow::MouseWheelScroll(D3DXVECTOR2 * pMousePos)
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
	m_pUi[TYPE_SCROLLHANDLE]->SetPosY(ScrollClamp(pMousePos, m_pUi[TYPE_SCROLLHANDLE]->GetPos().y -= nScrollValu *30.0f));
	m_pUi[TYPE_SCROLLHANDLE]->SetParent(m_pUi[TYPE_SCROLLHANDLE].get());
	m_pUi[TYPE_SCROLLHANDLE]->UpdateVertex(true);
	// �h�L�������g���X�N���[������
	ScrollScreen();
}

//-------------------------------------------------------------------------------------------------------------
// �X�N���[���̃N�����v
//-------------------------------------------------------------------------------------------------------------
float CDecodingWindow::ScrollClamp(D3DXVECTOR2 * pMousePos, float fPosY)
{
	// �ϐ��錾
	CDecodingUI * pScrollBar = m_pUi[TYPE_SCROLLBAR].get();
	CDecodingUI * pScrollHandle = m_pUi[TYPE_SCROLLHANDLE].get();

	// �g���Ɏ��߂�
	if (pScrollBar->GetPos().y + pScrollBar->GetSize().y *MYLIB_HALF_SIZE <= fPosY + pScrollHandle->GetSize().y*MYLIB_HALF_SIZE)
	{
		fPosY = (pScrollBar->GetPos().y + pScrollBar->GetSize().y*MYLIB_HALF_SIZE - (pScrollHandle->GetSize().y*MYLIB_HALF_SIZE));
		m_VecPinch_Center = VEC2(pScrollHandle->GetPos().x - pMousePos->x, fPosY - pMousePos->y);
	}
	if (pScrollBar->GetPos().y - pScrollBar->GetSize().y *MYLIB_HALF_SIZE >= fPosY - pScrollHandle->GetSize().y*MYLIB_HALF_SIZE)
	{
		fPosY = (pScrollBar->GetPos().y - pScrollBar->GetSize().y*MYLIB_HALF_SIZE + (pScrollHandle->GetSize().y*MYLIB_HALF_SIZE));
		m_VecPinch_Center = VEC2(pScrollHandle->GetPos().x - pMousePos->x, fPosY - pMousePos->y);
	}
	return fPosY;
}

//-------------------------------------------------------------------------------------------------------------
// ��ʂ��X�N���[��
//-------------------------------------------------------------------------------------------------------------
void CDecodingWindow::ScrollScreen(void)
{
	// �e�N�X�`��UV�����擾
	POLYVERTEXSUVINFO *pTex = m_pUi[TYPE_WINDOW]->GetTex();
	// �x�N�g�����v�Z
	float fVec              = m_pUi[TYPE_SCROLLHANDLE]->GetPos().y - (m_pUi[TYPE_SCROLLBAR]->GetPos().y + m_ScrollRange.min);
	// �X�P�[�����v�Z
	float fScal             = 1.0f - (m_fScrInitPos + m_fScrInitPos);
	// UV�ʒu��ݒ�
	pTex->pos.v             = m_fScrInitPos + (fScal *  (fVec / m_fScrollRangeValue));
	// ���_���̍X�V
	m_pUi[TYPE_WINDOW]->UpdateVertex(false, false, true);
}

//-------------------------------------------------------------------------------------------------------------
// �ݒ�̏�����
//-------------------------------------------------------------------------------------------------------------
void CDecodingWindow::InitSeting(WINDOW_SETING &Seting)
{
	// ������
	SETINGINFO *pInit = &m_InitSeting[0];		// �����ݒ���̃|�C���^
	SETINGINFO *pSet  = &m_Seting[0];			// �ݒ���̃|�C���^

	pSet[TYPE_WINDOW] = Seting;

	for (int nCntType = TYPE_CLOSEBUTTON; nCntType < TYPE_MAX; nCntType++)
	{
		pSet[nCntType] = pInit[nCntType];
	}
}

//-------------------------------------------------------------------------------------------------------------
// UI�̍쐬
//-------------------------------------------------------------------------------------------------------------
void CDecodingWindow::MakeUI(void)
{
	m_pUi[TYPE_WINDOW] = CDecodingUI::Create(m_Seting[TYPE_WINDOW]);
	m_pUi[TYPE_WINDOW]->BindTexture(m_pDocTexture[TEX_W_TELLTHEPICTURE]);
	// ���[�v
	for (int nCntType = TYPE_CLOSEBUTTON; nCntType < TYPE_MAX; nCntType++)
	{// UI�̐���
		m_pUi[nCntType] = CDecodingUI::Create(m_Seting[nCntType]);
		m_pUi[nCntType]->BindTexture(m_pTexture[nCntType - 1]);
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
// �F��ύX
//-------------------------------------------------------------------------------------------------------------
void CDecodingWindow::ChangeColor(CDecodingUI * pUi, D3DXCOLOR & col)
{
	// ���_���̍X�V
	pUi->UpdateVertex(NULL, NULL, &col);
}

//-------------------------------------------------------------------------------------------------------------
// 1�s�������ǂݎ��
//-------------------------------------------------------------------------------------------------------------
void CDecodingWindow::ReadFromLine(CONST_STRING cnpLine, CONST_STRING cnpEntryType, CONST_STRING cnpEntryData)
{
	// �ϐ��錾
	D3DXVECTOR3 pos                     = MYLIB_3DVECTOR_ZERO;				// �ʒu
	D3DXVECTOR2 size                    = MYLIB_2DVECTOR_ZERO;				// �傫��
	D3DXCOLOR   col                     = MYLIB_D3DXCOR_SET;				// �F
	float       fData                   = MYLIB_FLOAT_UNSET;				// float�^�̃f�[�^
	int         nData                   = MYLIB_INT_UNSET;					// int�^�̃f�[�^
	char        sData[MYLIB_STRINGSIZE] = Mlf_array(MYLIB_CHAR_UNSET);	// ������̃f�[�^
	SETINGINFO* pSet                    = nullptr;							// �ݒ���̃|�C���^

	if (strcmp(cnpEntryType, "SetUp") == 0)
	{
		if (sscanf(cnpLine, "ModeCount = %d", &nData) == 1)
		{
			m_nFrameMax = nData;
		}
	}
	else
	{
		pSet = &m_InitSeting[atoi(m_pHash->Search((char*)cnpEntryType))];
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
}
