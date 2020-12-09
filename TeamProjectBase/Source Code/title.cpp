//------------------------------------------------------------------------------
//
//�^�C�g������  [title.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "fade.h"
#include "title.h"
#include "Bomb.h"
#include "Map.h"
#include "light.h"
#include "ParticleManager.h"
#include "scene2D.h"
#include "module_Timer.h"
#include "timer.h"
//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CTitle::CTitle()
{

	m_nCntState = 0;
	m_titlestate = STATE_NORMAL;

}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CTitle::~CTitle()
{

}

//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CTitle::Init(HWND hWnd)
{
	//�J�������W�ݒ�
	CManager::GetRenderer()->GetCamera()->SetState(CCamera::CAMERA_TITLE);
	//CManager::GetRenderer()->GetCamera()->SetState(CCamera::CAMERA_DEBUG);

	//�p�[�e�B�N���̃}�l�[�W��
	CParticleManager::Create();


	//�|���S������
	CSceneBase::ScenePolygonCreateSceneManagement<CScene2D>(D3DXVECTOR3(640.0f, 170.0f, 0.0f), D3DXVECTOR3(850.0f, 200.0f, 0.0f), WhiteColor, CTexture::GetTexture(CTexture::TEX_UI_TITLE), CScene::OBJTYPE_UI);
	CSceneBase::ScenePolygonCreateSceneManagement<CScene2D>(D3DXVECTOR3(640.0f, 600.0f, 0.0f), D3DXVECTOR3(800.0f, 100.0f, 0.0f), WhiteColor, CTexture::GetTexture(CTexture::TEX_UI_PRESSBUTTON), CScene::OBJTYPE_UI);

	//���e����
	m_pBomb = CBomb::CreateBomb(D3DXVECTOR3(0.0f, 200.0f, 0.0f), ZeroVector3, CBomb::TITLE);

	//���W���[������
	m_pBomb->CreateModule();

	//�}�b�v����
	CMap::Create();


	return S_OK;
}


//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CTitle::Update()
{

	StateUpdate();

}

//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CTitle::Draw()
{
}

//------------------------------------------------------------------------------
//�X�e�[�g�X�V
//------------------------------------------------------------------------------
void CTitle::StateUpdate()
{
	//�J�E���g�_�E��
	m_nCntState--;

	switch (m_titlestate)
	{
	case CTitle::STATE_NONE:
		break;
	case CTitle::STATE_START:
		break;
	case CTitle::STATE_NORMAL:
		//�Ȃ񂩃{�^�������ꂽ�Ƃ�
		if (CHossoLibrary::CheckAnyButton())
		{
			SetState(STATE_BLACKOUT);
		}
		break;

	case CTitle::STATE_BLACKOUT:
		if (m_nCntState < 0)
		{
			SetState(STATE_FADE);
		}
		break;
	case CTitle::STATE_FADE:
		break;
	default:
		break;
	}
}

//------------------------------------------------------------------------------
//�X�e�[�g�ؑ�
//------------------------------------------------------------------------------
void CTitle::SetState(STATE state)
{
	m_titlestate = state;

	switch (m_titlestate)
	{
	case CTitle::STATE_NONE:

		break;
	case CTitle::STATE_START:

		break;
	case CTitle::STATE_NORMAL:

		break;
	case CTitle::STATE_BLACKOUT:
		CManager::GetRenderer()->GetLight()->SetBlackLight();
		m_pBomb->GetModuleTimerPtr()->GetTimerPtr()->SetStop(false);
		m_nCntState = 90;
		break;
	case CTitle::STATE_FADE:
		//�`���[�g���A���ɑJ��
		CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_DECODING);
		SetState(STATE_NONE);
		break;
	default:
		break;
	}
}
