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
#define TIME_ANIM_LOADICON	(7)	// �A�j���[�V���������̊Ԋu
#define NUM_ANIMPATTER_LOADICON	(8)	// ���[�h�A�C�R���̃p�^�[����

//=============================================================================
// �ÓI�����o�ϐ��̏�����
//=============================================================================

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
	// UI����
	CreateUI();

	return S_OK;
}

//=============================================================================
// �X�V
//=============================================================================
void CConnectUI::Update(void)
{
	for (int nCnt = 0; nCnt < CONNECTUI_MAX; nCnt++)
	{
		if (!m_pConnectUI[nCnt])
			return;

		if (nCnt == CONNECTUI_LOADICON)
			LoadAnim(m_pConnectUI[nCnt]);

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
void CConnectUI::CreateUI(void)
{
	m_pConnectUI[CONNECTUI_LOADICON] = CPolygon2D::Create();
	m_pConnectUI[CONNECTUI_LOADICON]->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	m_pConnectUI[CONNECTUI_LOADICON]->SetSize(D3DXVECTOR3(50.0f, 50.0f, 0.0f));
	m_pConnectUI[CONNECTUI_LOADICON]->SetAnim(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f / NUM_ANIMPATTER_LOADICON, 1.0f));
	m_pConnectUI[CONNECTUI_LOADICON]->SetPosStart(CPolygon2D::POSSTART_CENTRAL_CENTRAL);
	m_pConnectUI[CONNECTUI_LOADICON]->BindTexture(CTexture::GetTexture(CTexture::TEX_CONNECT_LOAD));
}

//=============================================================================
// ���[�h�A�C�R���̃A�j���[�V����
//=============================================================================
void CConnectUI::LoadAnim(CPolygon2D *pUI)
{
	static int nCntAnim = 0;
	static int nCntPat = 0;

	// ���ԂłȂ��Ȃ�A�������I����
	nCntAnim++;
	if (nCntAnim < TIME_ANIM_LOADICON)
		return;

	// ���t���[�������ɃA�j���[�V����
	nCntPat++;
	if (nCntPat >= NUM_ANIMPATTER_LOADICON)
		nCntPat = 0;
	nCntAnim = 0;
	pUI->SetAnim(D3DXVECTOR2(0.0f + (1.0f / NUM_ANIMPATTER_LOADICON * nCntPat), 0.0f), D3DXVECTOR2(1.0f / NUM_ANIMPATTER_LOADICON, 1.0f));
}
