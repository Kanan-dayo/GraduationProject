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
#include "game.h"

//-------------------------------------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------------------------------------
#define TABLETBUTTON_NOTPRESS_POS_Z	(-8.0f)		// ������Ă��Ȃ����̈ʒu��Z�l
#define TABLETBUTTON_PRESS_POS_Z	(-1.0f)		// ������Ă��鎞�̈ʒuZ�l

//-------------------------------------------------------------------------------------------------------------
// �ÓI�����o�ϐ��̏�����
//-------------------------------------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CTabletButton::m_aTexture[CTabletButton::TYPE_MAX] = {};	// �e�N�X�`�����

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
	// �ϐ��錾
	CMouse*       pMouse   = CManager::GetMouse();					// �}�E�X�̎擾
	CPaintingPen* pPen     = CPicture::GetPaintPen();				// �y���̎擾
	CPicture*     pPicture = CManager::GetGame()->GetPicture();		// �s�N�`���̎擾
	// �t���O�������Ă��鎞���}�E�X��������Ă��Ȃ���
	if (m_bPress && !pMouse->GetPress(0) && m_bChange)
	{
		// �^�C�v���򏈗�
		switch (m_Type)
		{
			MLB_CASE(TYPE_PEN)   pPen->SetMode(CPaintingPen::MODE_BRUSH);	// �y��
			MLB_CASE(TYPE_ERASER)pPen->SetMode(CPaintingPen::MODE_ERASER);	// �����S��
			MLB_CASE(TYPE_SEND)  pPicture->Writing();						// ���M
			MLB_CASEEND;													// �P�[�X�I��
		}
		// �����ꂽ�t���O������
		m_bPress = false;
	}

	// �^�C�v�ƃ��[�h����v���Ă�����
	if (pPen->GetMode() == m_Type)
	{
		// �ʒu�̎擾
		D3DXVECTOR3 *pos = GetPosPtr();
		// Z�l��ύX
		pos->z = TABLETBUTTON_PRESS_POS_Z;
	}
	else
	{
		// �ʒu�̎擾
		D3DXVECTOR3 *pos = GetPosPtr();
		// Z�l��ύX
		pos->z = (m_bPress == true) ? TABLETBUTTON_PRESS_POS_Z : TABLETBUTTON_NOTPRESS_POS_Z;
	}

	CDebugProc::Print(CDebugProc::PLACE_LEFT, "\n�����ꂽ�t���O       == [%d]\n", (m_bPress) ? TRUE : FALSE);
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "�ύX�t���O           == [%d]\n", (m_bChange) ? TRUE : FALSE);
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "�����ŉ����ꂽ�t���O == [%d]\n", (m_bInPress) ? TRUE : FALSE);
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
void CTabletButton::FlagProcToChangeMode(void)
{
	// �ϐ��錾
	CMouse *pMouse = CManager::GetMouse();// �}�E�X�̎擾

	// �}�E�X��������Ă��Ȃ���
	if (!pMouse->GetPress(0))
	{// �ύX�t���O�𗧂Ă�
		SetToSetChangeFlag();
		// �����ŉ����ꂽ�t���O������
		SetToOffInPressFlag();
	}
	else
	{
	}

	// ������Ă���t���O�������Ă��鎞���̓}�E�X��������Ă��Ȃ���
	if (m_bPress || !pMouse->GetPress(0) || !m_bChange)
	{// �����𔲂���
		return;
	}
	// �����ŉ����ꂽ�t���O�𗧂Ă�
	SetToSetInPressFlag();
	// �t���O�𗧂Ă�
	m_bPress = true;
}

//-------------------------------------------------------------------------------------------------------------
// �ύX�t���O�̐ݒ�
//-------------------------------------------------------------------------------------------------------------
void CTabletButton::SetChangeFlagProc(void)
{
	// �}�E�X��������Ă��鎞�������ŉ����ꂽ�t���O�������Ă��Ȃ���
	if(CManager::GetMouse()->GetPress(0) && !m_bInPress)
	{// �ύX�t���O������
		SetToOffChangeFlag();
		return;
	}
	if (!CManager::GetMouse()->GetPress(0))
	{
		// �����ŉ����ꂽ�t���O������
		SetToOffInPressFlag();
	}

	// �ύX�t���O�𗧂Ă�
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

