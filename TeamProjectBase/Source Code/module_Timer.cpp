//------------------------------------------------------------------------------
//
//���W���[���̏���  [module.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "module_timer.h"
#include "renderer.h"
#include "manager.h"
#include "modelinfo.h"
#include "scene3D.h"
#include "timer.h"

//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define TIMER_OFFSET_POS			(D3DXVECTOR3(0.0f,-8.0f,-2.0f))
#define MISSCOUNTER_OFFSET_POS		(D3DXVECTOR3(-5.0f,22.0f,-33.0f))
#define MISSCOUNTER_SIZE			(D3DXVECTOR3(10.0f,10.0f,0.0f))


//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CModule_Timer::CModule_Timer()
{
	m_pTimer.reset();
	m_pMissCounter.clear();
	m_nMissCount = 0;
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CModule_Timer::~CModule_Timer()
{
	m_pTimer.reset();
	m_pMissCounter.clear();
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CModule_Timer::Init()
{
	//���f�����ݒ�
	BindModelInfo(CModelInfo::GetModelInfo(CModelInfo::MODEL_MODULE_TIMER));

	//���W���[���I��s��
	CModule_Base::SetCanModuleSelect(false);

	//�^�C�}�[�̐���
	m_pTimer = CTimer::Create(TIMER_OFFSET_POS, 360, GetMtxWorldPtr());

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_pMissCounter.emplace_back(CSceneBase::ScenePolygonCreateShared<CScene3D>(MISSCOUNTER_OFFSET_POS + D3DXVECTOR3(nCnt * 12.0f,0.0f,0.0f), MISSCOUNTER_SIZE, RedColor, nullptr, OBJTYPE_MODULE_PARTS_SYMBOL));
		m_pMissCounter[m_pMissCounter.size() - 1]->SetParentMtxPtr(GetMtxWorldPtr());
		m_pMissCounter[m_pMissCounter.size() - 1]->SetLighting(false);

	}


	CSceneX::Init();
	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CModule_Timer::Uninit()
{
	CSceneX::Uninit();
}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CModule_Timer::Update()
{
	m_pTimer->UpdateTimer();

	CSceneX::Update();
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CModule_Timer::Draw()
{
	CSceneX::Draw();
}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CModule_Timer::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}