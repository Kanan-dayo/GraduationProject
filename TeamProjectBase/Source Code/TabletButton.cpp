//*************************************************************************************************************
//
// �^�u���b�g�{�^���̊�ꏈ�� [TabletButton_Base.cpp]
// Author:IKUTO SEKINE
//
//*************************************************************************************************************
//-------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------------------
#include "TabletButton.h"
#include "modelinfo.h"
#include "scene3D.h"
#include "texture.h"
#include "picture.h"
#include "PaintingPen.h"
#include "manager.h"
#include "mouse.h"

//-------------------------------------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------------------------------------
#define TABLETBUTTON_NOTPRESS_POS_Z	(-8.0f)		// ������Ă��Ȃ����̈ʒu��Z�l
#define TABLETBUTTON_PRESS_POS_Z	(-1.0f)		// ������Ă��鎞�̈ʒuZ�l

//-------------------------------------------------------------------------------------------------------------
// �ÓI�����o�ϐ��̏�����
//-------------------------------------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CTabletButton::m_aTexture[CTabletButton::TYPE_MAX] = {};

//-------------------------------------------------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------------------------------------------------
CTabletButton::CTabletButton()
{
}

//-------------------------------------------------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------------------------------------------------
CTabletButton::~CTabletButton()
{
}

//-------------------------------------------------------------------------------------------------------------
// �ǂݍ���
//-------------------------------------------------------------------------------------------------------------
void CTabletButton::Load(void)
{
	m_aTexture[TYPE_PEN] = CTexture::GetTexture(CTexture::TEX_UI_BRUSHCURSOR);
	m_aTexture[TYPE_ERASER] = CTexture::GetTexture(CTexture::TEX_UI_ERASERCURSOR);
	m_aTexture[TYPE_SEND] = CTexture::GetTexture(CTexture::TEX_UI_SENDBUTTON);
}

//-------------------------------------------------------------------------------------------------------------
// �J��
//-------------------------------------------------------------------------------------------------------------
void CTabletButton::Unload(void)
{
	for (int nCntTex = 0; nCntTex < TYPE_MAX; nCntTex++)
	{
		m_aTexture[nCntTex] = nullptr;
	}
}

//-------------------------------------------------------------------------------------------------------------
// ������
//-------------------------------------------------------------------------------------------------------------
HRESULT CTabletButton::Init()
{
	//���f�����ݒ�
	BindModelInfo(CModelInfo::GetModelInfo(CModelInfo::MODEL_TABLET_BUTTON));
	CSceneX::Init();
	
	// 3D�摜�̐���
	m_pImage = CScene3D::ScenePolygonCreateShared<CScene3D>(D3DXVECTOR3(0.0f, 0.0f, -4.8f), D3DXVECTOR3(20.0f, 20.0f, 0.0f), MYLIB_D3DXCOR_SET,
		m_aTexture[m_Type], CScene::OBJTYPE_PICTURE_SYMBOL);
	m_pImage->SetParentMtxPtr(this->GetMtxWorldPtr());
	m_bPress = false;
	m_bChange = false;
	m_bInPress = false;
	return S_OK;
}

//-------------------------------------------------------------------------------------------------------------
// �X�V
//-------------------------------------------------------------------------------------------------------------
void CTabletButton::Update()
{
	// �}�E�X�̎擾a
	CMouse *pMouse = CManager::GetMouse();
	// �y���̎擾
	CPaintingPen *pPen = CPicture::GetPaintPen();
	// �t���O�������Ă��鎞���}�E�X��������Ă��Ȃ���
	if (m_bPress && !pMouse->GetPress(0) && m_bChange)
	{
		m_bPress = false;
		// �^�C�v���򏈗�
		switch (m_Type)
		{
			MLB_CASE(TYPE_PEN)   pPen->SetMode(CPaintingPen::MODE_BRUSH);	// �y��
			MLB_CASE(TYPE_ERASER)pPen->SetMode(CPaintingPen::MODE_ERASER);	// �����S��
			MLB_CASE(TYPE_SEND);											// ���M
			MLB_CASEEND;													// �P�[�X�I��
		}
	}

	if (pPen->GetMode() == m_Type)
	{
		// �ʒu�̎擾
		D3DXVECTOR3 *pos = GetPosPtr();
		// z�l��ύX
		pos->z = TABLETBUTTON_PRESS_POS_Z;
	}
	else
	{
		// �ʒu�̎擾
		D3DXVECTOR3 *pos = GetPosPtr();
		// z�l��ύX
		pos->z = (m_bPress == true) ? TABLETBUTTON_PRESS_POS_Z : TABLETBUTTON_NOTPRESS_POS_Z;
	}
}

//-------------------------------------------------------------------------------------------------------------
// �`��
//-------------------------------------------------------------------------------------------------------------
void CTabletButton::Draw()
{
	CSceneX::Draw();
}

//-------------------------------------------------------------------------------------------------------------
// ���[�h�̐ݒ�
//-------------------------------------------------------------------------------------------------------------
void CTabletButton::SetMode(void)
{
	// �}�E�X�̎擾
	CMouse *pMouse = CManager::GetMouse();

	// �}�E�X��������Ă��Ȃ���
	if (!pMouse->GetPress(0))
	{
		SetToSetChangeFlag();
		m_bInPress = false;
	}
	else
	{
		m_bInPress = true;
	}
	// ������Ă���t���O�������Ă��鎞���̓}�E�X��������Ă��Ȃ���
	if (m_bPress || !pMouse->GetPress(0) || !m_bChange)
	{
		// �����𔲂���
		return;
	}

	// �t���O�𗧂Ă�
	m_bPress = true;
}

//-------------------------------------------------------------------------------------------------------------
// �ύX�t���O�̐ݒ�
//-------------------------------------------------------------------------------------------------------------
void CTabletButton::SetChangeFlag(void)
{
	if(CManager::GetMouse()->GetPress(0) && !m_bInPress)
	{
		SetToOffChangeFlag();
		return;
	}
	SetToSetChangeFlag();
}

//-------------------------------------------------------------------------------------------------------------
// ����
//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<CTabletButton> CTabletButton::Create(D3DXMATRIX *pMtxParent, CONST D3DXVECTOR3 &pos, TYPE type)
{
	std::shared_ptr<CTabletButton> pTabletButton_Base = std::make_shared<CTabletButton>();
	pTabletButton_Base->SetParentMtxPtr(pMtxParent);
	pTabletButton_Base->SetPos(pos);
	pTabletButton_Base->SetType(type);
	pTabletButton_Base->Init();

	//Scene�Ƀ|�C���^��n��
	pTabletButton_Base->SetObjType(OBJTYPE_PICTURE);
	pTabletButton_Base->AddSharedList(pTabletButton_Base);

	return pTabletButton_Base;
}

