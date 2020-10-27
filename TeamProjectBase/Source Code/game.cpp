//------------------------------------------------------------------------------
//
//�Q�[������  [game.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "game.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "fade.h"
#include "camera.h"
#include "Bomb.h"
#include "Map.h"
#include "ParticleManager.h"
#include "picture.h"
#include "chatBase.h"

//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CGame::CGame()
{
	m_nCntState = 0;
	m_State = STATE_NORMAL;
	m_Gaze = GAZE_BOMB;
	m_pBomb.reset();
}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CGame::~CGame()
{
	m_pBomb.reset();
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CGame::Init(HWND hWnd)
{
	//�J�������W�ݒ�
	CManager::GetRenderer()->GetCamera()->SetState(CCamera::CAMERA_DEBUG);

	//������
	SetState(CGame::STATE_NORMAL);

	//�p�[�e�B�N���̃}�l�[�W��
	CParticleManager::Create();

	//���e����
	m_pBomb	= CBomb::CreateBomb(D3DXVECTOR3(0.0f,120.0f,0.0f), ZeroVector3, 12);

	//�}�b�v����
	CMap::Create();

	// �s�N�`���̐���
	CPicture::Load();
	CPicture::Create(D3DXVECTOR3(300.0f, 300.0f, 0.0f), ZeroVector3);

	// �`���b�g�̐���
	m_pChatBase = CChatBase::Create();

	return S_OK;
}

//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CGame::Uninit()
{
	CPicture::InitStaticMember();

	// �`���b�g�̔j��
	m_pChatBase->Uninit();
}

//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CGame::Update()
{
	UpdateState();
}

//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CGame::Draw()
{

}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CGame::ShowDebugInfo()
{
#ifdef _DEBUG


#endif //_DEBUG
}

//------------------------------------------------------------------------------
//�X�e�[�g�̍X�V
//------------------------------------------------------------------------------
void CGame::UpdateState()
{
	m_nCntState--;

	switch (m_State)
	{
	case CGame::STATE_READY:
		break;
	case CGame::STATE_NORMAL:
		break;
	case CGame::STATE_PAUSE:
		break;
	case CGame::STATE_GAMEOVER:
		break;
	case CGame::STATE_GAMECLEAR:
		if (m_nCntState <= 0)
		{
			SetState(CGame::STATE_NONE);
			CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_RESULT);
		}
		break;
	}
}


//------------------------------------------------------------------------------
//�Q�[���X�e�[�g�Z�b�g
//------------------------------------------------------------------------------
void CGame::SetState(STATE state)
{
	//�X�e�[�g���i��ł���ꍇ
	if (m_State != CGame::STATE_NONE && m_State != state)
	{
		//�X�e�[�g�ύX
		m_State = state;

		switch (m_State)
		{
		case CGame::STATE_NONE:
			break;
		case CGame::STATE_READY:
			break;
		case CGame::STATE_NORMAL:
			break;
		case CGame::STATE_PAUSE:
			break;
		case CGame::STATE_GAMEOVER:
			break;
		case CGame::STATE_GAMECLEAR:
			m_nCntState = 120;

			break;
		case CGame::STATE_DEBUG:
			break;
		case CGame::STATE_MAX:
			break;
		default:
			break;
		}
	}
}

//------------------------------------------------------------------------------
//�����ݒ�
//------------------------------------------------------------------------------
void CGame::SetGaze(GAZE gaze)
{
	//�O�̏�ԂƈႤ��
	if (m_Gaze != gaze)
	{
		//�������ݒ�
		m_Gaze = gaze;
		switch (m_Gaze)
		{
		case CGame::GAZE_DEFAULT:

			break;
		case CGame::GAZE_BOMB:
			//CManager::GetRenderer()->GetCamera()->
			break;
		case CGame::GAZE_MODULE:

			break;
		default:
			break;
		}


	}

}
