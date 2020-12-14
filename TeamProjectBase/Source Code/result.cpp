//------------------------------------------------------------------------------
//
//���U���g����  [result.cpp]
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
#include "result.h"
#include "sound.h"
#include "scene2D.h"
#include "game.h"
//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CResult::CResult()
{
	m_nCntResult = 0;
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CResult::~CResult()
{
}

//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CResult::Init(HWND hWnd)
{
	//�J�������W�ݒ�
	CManager::GetRenderer()->GetCamera()->SetState(CCamera::CAMERA_DEBUG);

	//���S
	CSceneBase::ScenePolygonCreateSceneManagement<CScene2D>(D3DXVECTOR3(640.0f, 100.0f, 0.0f), D3DXVECTOR3(1000.0f, 300.0f, 0.0f), WhiteColor, CTexture::GetTexture(CTexture::TEX_UI_RESULT_LOGO), CScene::OBJTYPE_UI);

	//�o�[
	CSceneBase::ScenePolygonCreateSceneManagement<CScene2D>(D3DXVECTOR3(640.0f, 150.0f, 0.0f), D3DXVECTOR3(1300.0f, 5.0f, 0.0f), WhiteColor, CTexture::GetTexture(CTexture::TEX_UI_RESULT_BAR), CScene::OBJTYPE_UI);

	//�N���A������
	CGame::GetClearFlag() ?
		CSceneBase::ScenePolygonCreateSceneManagement<CScene2D>(D3DXVECTOR3(640.0f, 200.0f, 0.0f), D3DXVECTOR3(300.0f, 100.0f, 0.0f), WhiteColor, CTexture::GetTexture(CTexture::TEX_UI_RESULT_CLEAR), CScene::OBJTYPE_UI) :
		CSceneBase::ScenePolygonCreateSceneManagement<CScene2D>(D3DXVECTOR3(640.0f, 200.0f, 0.0f), D3DXVECTOR3(300.0f, 100.0f, 0.0f), WhiteColor, CTexture::GetTexture(CTexture::TEX_UI_RESULT_FAILED), CScene::OBJTYPE_UI);


	//�v���C�^�C��
	CSceneBase::ScenePolygonCreateSceneManagement<CScene2D>(D3DXVECTOR3(300.0f, 500.0f, 0.0f), D3DXVECTOR3(300.0f, 100.0f, 0.0f), WhiteColor, CTexture::GetTexture(CTexture::TEX_UI_RESULT_TIMER), CScene::OBJTYPE_UI);

	//�o�[
	CSceneBase::ScenePolygonCreateSceneManagement<CScene2D>(D3DXVECTOR3(640.0f, 550.0f, 0.0f), D3DXVECTOR3(1300.0f, 5.0f, 0.0f), WhiteColor, CTexture::GetTexture(CTexture::TEX_UI_RESULT_BAR), CScene::OBJTYPE_UI);




	//CSceneBase::ScenePolygonCreateSceneManagement<CScene2D>(D3DXVECTOR3(640.0f, 600.0f, 0.0f), D3DXVECTOR3(800.0f, 100.0f, 0.0f), WhiteColor, CTexture::GetTexture(CTexture::TEX_UI_PRESSBUTTON), CScene::OBJTYPE_UI);

	return S_OK;
}

//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CResult::Update()
{
	//�J�E���^++
	m_nCntResult++;

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
void CResult::Draw()
{

}