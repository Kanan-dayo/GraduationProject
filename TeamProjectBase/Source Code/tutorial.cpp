//------------------------------------------------------------------------------
//
//�`���[�g���A������  [tutorial.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "manager.h"
#include "renderer.h"
#include "tutorial.h"
#include "camera.h"
#include "fade.h"
#include "result.h"
#include "sound.h"
#include "scene2D.h"
#include "connectUI.h"
#include "mouse.h"
#include "UI_Base.h"
//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CTutorial::CTutorial()
{
	m_nCntState = 0;
	m_pPolygonList.clear();
	m_state = (CTutorial::TUTORIL_TYPE)CConnectUI::GetSelectMode();



	//m_state = CTutorial::TUTORIAL_REMOVE;
	m_state = CTutorial::TUTORIAL_SOLVE;

}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CTutorial::~CTutorial()
{
	m_pPolygonList.clear();
}

//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CTutorial::Init(HWND hWnd)
{

	//�J�������W�ݒ�
	CManager::GetRenderer()->GetCamera()->SetState(CCamera::CAMERA_DEBUG);

	CreateUI();

	return S_OK;
}

//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CTutorial::Update()
{
	//�X�e�[�g�ɉ������X�V
	UpdateState();

	//�t�F�[�h���ĂȂ���
	if (CManager::GetRenderer()->GetFade()->GetFadeState() == CFade::FADE_NONE)
	{
		//�����{�^���������Ƃ�
		if (CHossoLibrary::CheckAnyButton())
		{
				//�X�e�[�g�ύX
				CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_TITLE);

				CManager::GetSound()->Play(CSound::LABEL_SE_DECISION);
		}
	}
}

//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CTutorial::Draw()
{

}
//------------------------------------------------------------------------------
//UI����
//------------------------------------------------------------------------------
void CTutorial::CreateUI()
{
	switch (m_state)
	{
		//����
	case CTutorial::TUTORIAL_REMOVE:
		m_pPolygonList.emplace_back(CSceneBase::ScenePolygonCreateShared<CScene2D>
			(SCREEN_CENTER_POS, SCREEN_SIZE, WhiteColor, CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_REMOVE01), CScene::OBJTYPE_UI));
		break;

		//���
	case CTutorial::TUTORIAL_SOLVE:
		m_pPolygonList.emplace_back(CSceneBase::ScenePolygonCreateShared<CScene2D>
			(SCREEN_CENTER_POS, SCREEN_SIZE, WhiteColor, CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_SOLVE01), CScene::OBJTYPE_UI));

		break;
	}
}
//------------------------------------------------------------------------------
//�X�e�[�g�X�V
//------------------------------------------------------------------------------
void CTutorial::UpdateState()
{

}
//------------------------------------------------------------------------------
//�����蔻��
//------------------------------------------------------------------------------
void CTutorial::Collision()
{

	CMouse *pMouse = CManager::GetMouse();
	D3DXVECTOR3 pos = pMouse->GetMousePos();

}
