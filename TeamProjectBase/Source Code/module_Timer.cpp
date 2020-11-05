//------------------------------------------------------------------------------
//
//���W���[���̃^�C�}�[����  [module_timer.cpp]
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
#define MISSCOUNTER_OFFSET_POS		(D3DXVECTOR3(-5.0f,22.0f,-32.0f))
#define MISSCOUNTER_SIZE			(D3DXVECTOR3(10.0f,10.0f,0.0f))
#define MISSCOUNTER_INTERVAL		(D3DXVECTOR3(13.0f,0.0f,0.0f))


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
		m_pMissCounter.emplace_back(CSceneBase::ScenePolygonCreateShared<CScene3D>(MISSCOUNTER_OFFSET_POS + D3DXVECTOR3(nCnt * MISSCOUNTER_INTERVAL.x,0.0f,0.0f), MISSCOUNTER_SIZE, RedColor, nullptr, OBJTYPE_MODULE_PARTS_SYMBOL));
		m_pMissCounter[m_pMissCounter.size() - 1]->SetParentMtxPtr(GetMtxWorldPtr());
		m_pMissCounter[m_pMissCounter.size() - 1]->SetLighting(false);
		m_pMissCounter[m_pMissCounter.size() - 1]->SetDisp(false);

	}


	CSceneX::Init();
	return S_OK;
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
//�~�X�̃J�E���g�A�b�v
//------------------------------------------------------------------------------
bool CModule_Timer::MissCountUp()
{
	m_nMissCount++;

	//����܂ōs�����Ƃ���return
	if (CHossoLibrary::RangeLimit_Equal(m_nMissCount,0,2))
	{
		return true;
	}
	else
	{
		//�~�X������
		for (int nCnt = 0; nCnt < m_nMissCount; nCnt++)
		{
			//�\������
			m_pMissCounter[nCnt]->SetDisp(true);
		}
	}
	return false;
}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CModule_Timer::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}