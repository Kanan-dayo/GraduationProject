//=============================================================================
//
// �ڑ��̊�Տ��� [ connectBase.cpp ]
// Author : KANAN NAGANAWA
//
//=============================================================================
#include "connectBase.h"
#include "connectUI.h"
#include "scene.h"

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �ÓI�����o�ϐ��̏�����
//=============================================================================

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CConnectBase::CConnectBase()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CConnectBase::~CConnectBase()
{
	if (m_pUI)
	{
		delete m_pUI;
		m_pUI = nullptr;
	}
}

//=============================================================================
// ����
//=============================================================================
std::shared_ptr<CConnectBase> CConnectBase::Create(void)
{
	// �������m��
	std::shared_ptr<CConnectBase> pBase = std::make_shared<CConnectBase>();

	// �m�ێ��s
	if (!pBase)
		return nullptr;

	// ������
	pBase->Init();

	//Scene�Ƀ|�C���^��n��
	pBase->SetObjType(OBJTYPE_UI);
	pBase->AddSharedList(pBase);

	// �l��Ԃ�
	return pBase;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CConnectBase::Init(void)
{
	m_pUI = CConnectUI::Create();

	return S_OK;
}

//=============================================================================
// �X�V
//=============================================================================
void CConnectBase::Update(void)
{
	if (m_pUI)
		m_pUI->Update();
}

//=============================================================================
// �`��
//=============================================================================
void CConnectBase::Draw(void)
{
	if (m_pUI)
		m_pUI->Draw();
}