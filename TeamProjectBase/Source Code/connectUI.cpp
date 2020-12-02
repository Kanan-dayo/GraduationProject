//=============================================================================
//
// �ڑ���UI���� [ connectUI.cpp ]
// Author : KANAN NAGANAWA
//
//=============================================================================
#include "connectUI.h"
#include "polygon2D.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define INTERVAL_ANIM_LOADICON	(10)	// �A�j���[�V���������̊Ԋu
#define NUM_ANIMPATTER_LOADICON	(8)	// ���[�h�A�C�R���̃p�^�[����

//=============================================================================
// �ÓI�����o�ϐ��̏�����
//=============================================================================
CPolygon2D *CConnectUI::m_pConnectUI[CConnectUI::CONNECTUI_MAX] = {};
D3DXVECTOR2 CConnectUI::m_UIPos[CConnectUI::CONNECTUI_MAX] = 
{
	D3DXVECTOR2(SCREEN_WIDTH / 2 - 260.0f, SCREEN_HEIGHT / 2),
	D3DXVECTOR2(SCREEN_WIDTH / 2 + 260.0f, SCREEN_HEIGHT / 2),
	D3DXVECTOR2(SCREEN_WIDTH / 2 - 260.0f, SCREEN_HEIGHT / 2),
	D3DXVECTOR2(SCREEN_WIDTH / 2 + 260.0f, SCREEN_HEIGHT / 2)
};

D3DXVECTOR2 CConnectUI::m_UISize[CConnectUI::CONNECTUI_MAX] =
{
	D3DXVECTOR2(500.0f, 700.0f),
	D3DXVECTOR2(500.0f, 700.0f),
	D3DXVECTOR2(50.0f, 50.0f),
	D3DXVECTOR2(50.0f, 50.0f)
};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CConnectUI::CConnectUI()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CConnectUI::~CConnectUI()
{
	for (int nCnt = 0; nCnt < CONNECTUI_MAX; nCnt++)
	{
		if (m_pConnectUI[nCnt])
		{
			delete m_pConnectUI[nCnt];
			m_pConnectUI[nCnt] = nullptr;
		}
	}
}

//=============================================================================
// ����
//=============================================================================
CConnectUI *CConnectUI::Create(void)
{
	// �������m��
	CConnectUI* pUI = new CConnectUI;

	// �m�ێ��s
	if (!pUI)
		return nullptr;

	// ������
	pUI->Init();

	// �l��Ԃ�
	return pUI;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CConnectUI::Init(void)
{
	m_nCntAnim = 0;
	m_nCntPattern = 0;
	// �w�i����
	CreateBackTab();
	// ���[�h�A�C�R������
	CreateLoadIcon();

	return S_OK;
}

//=============================================================================
// �X�V
//=============================================================================
void CConnectUI::Update(void)
{
	if (m_pConnectUI[CONNECTUI_LOADICON_00])
		UpdateCntAnim();
	else if (m_pConnectUI[CONNECTUI_LOADICON_01])
		UpdateCntAnim();

	for (int nCnt = 0; nCnt < CONNECTUI_MAX; nCnt++)
	{
		if (!m_pConnectUI[nCnt])
			return;

		// ���[�h�A�C�R���̃A�j���[�V����
		if (nCnt == CONNECTUI_LOADICON_00 || 
			nCnt == CONNECTUI_LOADICON_01)
			m_pConnectUI[nCnt]->SetAnim(D3DXVECTOR2(0.0f + (1.0f / NUM_ANIMPATTER_LOADICON * m_nCntPattern), 0.0f), D3DXVECTOR2(1.0f / NUM_ANIMPATTER_LOADICON, 1.0f));

		m_pConnectUI[nCnt]->Update();
	}
}

//=============================================================================
// �`��
//=============================================================================
void CConnectUI::Draw(void)
{
	for (int nCnt = 0; nCnt < CONNECTUI_MAX; nCnt++)
	{
		if (m_pConnectUI[nCnt])
			m_pConnectUI[nCnt]->Draw();
	}
}

//=============================================================================
// UI�̐���
//=============================================================================
void CConnectUI::CreateLoadIcon(void)
{
	for (int nCnt = CONNECTUI_LOADICON_00; nCnt < CONNECTUI_LOADICON_00 + 2; nCnt++)
	{
		m_pConnectUI[nCnt] = CPolygon2D::Create();
		m_pConnectUI[nCnt]->SetPos(m_UIPos[nCnt]);
		m_pConnectUI[nCnt]->SetSize(m_UISize[nCnt]);
		m_pConnectUI[nCnt]->SetAnim(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f / NUM_ANIMPATTER_LOADICON, 1.0f));
		m_pConnectUI[nCnt]->SetCol(BlackColor);
		m_pConnectUI[nCnt]->SetPosStart(CPolygon2D::POSSTART_CENTRAL_CENTRAL);
		m_pConnectUI[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_LOAD));
	}
}

//=============================================================================
// �w�i�̐���
//=============================================================================
void CConnectUI::CreateBackTab(void)
{
	for (int nCnt = CONNECTUI_BACK_00; nCnt < CONNECTUI_BACK_00 + 2; nCnt++)
	{
		m_pConnectUI[nCnt] = CPolygon2D::Create();
		m_pConnectUI[nCnt]->SetPos(m_UIPos[nCnt]);
		m_pConnectUI[nCnt]->SetSize(m_UISize[nCnt]);
		m_pConnectUI[nCnt]->SetPosStart(CPolygon2D::POSSTART_CENTRAL_CENTRAL);
	}

	// �e�N�X�`���̃o�C���h
	m_pConnectUI[CONNECTUI_BACK_00]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_BACK_00));
	m_pConnectUI[CONNECTUI_BACK_01]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_BACK_01));
}

//=============================================================================
// �A�j���[�V�����J�E���^�̍X�V
//=============================================================================
void CConnectUI::UpdateCntAnim(void)
{
	// ���ԂłȂ��Ȃ�A�������I����
	m_nCntAnim++;
	if (m_nCntAnim < INTERVAL_ANIM_LOADICON)
		return;

	// ���t���[�������ɃA�j���[�V����
	m_nCntPattern++;
	if (m_nCntPattern >= NUM_ANIMPATTER_LOADICON)
		m_nCntPattern = 0;
	m_nCntAnim = 0;
}
