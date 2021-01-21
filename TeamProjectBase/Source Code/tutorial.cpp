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
#include "client.h"

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------
bool CTutorial::m_bGuestFlag = false;

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CTutorial::CTutorial()
{
	m_nCntState = 0;
	m_pTutorialPolygon.reset();
	m_type = (CTutorial::TUTORIL_TYPE)CConnectUI::GetSelectMode();
	m_bTutorialEndFlag = false;
	m_bGuestFlag = false;
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CTutorial::~CTutorial()
{
	m_pTutorialPolygon.reset();
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

	Collision();

	//�t�F�[�h���ĂȂ���
	if (CManager::GetRenderer()->GetFade()->GetFadeState() == CFade::FADE_NONE)
	{
		//�Q�X�g�E�v���C���[���ҋ@���̂Ƃ�
		if (m_bGuestFlag && m_bTutorialEndFlag)
		{
			// �Q�[���֑J��
			if (m_type == CTutorial::TUTORIAL_REMOVE)
				CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_GAME);
			else if (m_type == CTutorial::TUTORIAL_SOLVE)
				CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_DECODING);
			// SE
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

	m_pReady = CSceneBase::ScenePolygonCreateShared<CScene2D>
		(D3DXVECTOR3(1110.0f, 140.0f, 0.0f), D3DXVECTOR3(250.0f, 100.0f, 0.0f), WhiteColor, CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_PREPARE), CScene::OBJTYPE_FRONT);


	switch (m_type)
	{
		//����
	case CTutorial::TUTORIAL_REMOVE:
		m_pTutorialPolygon = CSceneBase::ScenePolygonCreateShared<CScene2D>
			(SCREEN_CENTER_POS, SCREEN_SIZE, WhiteColor, CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_REMOVE01), CScene::OBJTYPE_UI);
		break;

		//���
	case CTutorial::TUTORIAL_SOLVE:
		m_pTutorialPolygon = CSceneBase::ScenePolygonCreateShared<CScene2D>
			(SCREEN_CENTER_POS, SCREEN_SIZE, WhiteColor, CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_SOLVE01), CScene::OBJTYPE_UI);

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

	static int nMousePressCnt = 0;

	//���N���b�N
	if(pMouse->GetTrigger(0))
	{
		m_nPage--;
		if (!CHossoLibrary::RangeLimit_Equal(m_nPage, 0, 3))
		{
			CManager::GetSound()->Play(CSound::LABEL_SE_TUTORIALPAGE);
		}
	}
	//�E�N���b�N
	if (pMouse->GetTrigger(1))
	{
		m_nPage++;
		if (!CHossoLibrary::RangeLimit_Equal(m_nPage, 0, 3))
		{
			CManager::GetSound()->Play(CSound::LABEL_SE_TUTORIALPAGE);
		}
	}

	//������
	if (pMouse->GetPress(0) || pMouse->GetPress(1))
	{
		//�J�E���g�A�b�v
		nMousePressCnt++;
	}
	//�����ĂȂ������Z�b�g
	else
	{
		nMousePressCnt = 0;
	}

	//������x�������ŏ�������
	if (nMousePressCnt >= 60)
	{
		//�t���O�����ĂȂ���
		if (!m_bTutorialEndFlag)
		{
			//���������傤
			Ready();
		}
		//�t���O�𗧂Ă�
		m_bTutorialEndFlag = true;
	}



	//�y�[�W�ύX
	PageChange();

}


//------------------------------------------------------------------------------
//�y�[�W�ύX
//------------------------------------------------------------------------------
void CTutorial::PageChange()
{
	switch (m_type)
	{
		//����
	case CTutorial::TUTORIAL_REMOVE:
		m_pTutorialPolygon->BindTexture(CTexture::GetTexture((CTexture::TEX_TYPE)(m_nPage + CTexture::TEX_UI_TUTORIAL_REMOVE01)));
		break;

		//���
	case CTutorial::TUTORIAL_SOLVE:
		m_pTutorialPolygon->BindTexture(CTexture::GetTexture((CTexture::TEX_TYPE)(m_nPage + CTexture::TEX_UI_TUTORIAL_SOLVE01)));

		break;
	}


}

//------------------------------------------------------------------------------
//��������
//------------------------------------------------------------------------------
void CTutorial::Ready()
{
	//�e�N�X�`�������ւ�
	m_pReady->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TUTORIAL_ENDPREPARE));
	// �҂���Ԃ̑��M
	CClient::SendWait();
}
