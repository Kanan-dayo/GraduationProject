//------------------------------------------------------------------------------
//
//�^�C�}�[����  [tiemr.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "timer.h"
#include "game.h"
#include "manager.h"
#include "scene2D.h"
#include "multinumber.h"

//------------------------------------------------------------------------------
//�}�N����`
//------------------------------------------------------------------------------
#define DEFAULT_TIMER (300)
#define TIMER_SIZE					(D3DXVECTOR3(10.0f,20.0f,0.0f))
#define TIMER_H_M_S_INTERVAL_X		(12.0f)
#define TIMER_H_M_S_INTERVAL_Z		(-10.0f)

//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------
int CTimer::m_nTimer = 0;
//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CTimer::CTimer()
{
	m_nTimer = DEFAULT_TIMER;
	m_nCntFlame = DEFAULT_TIMER * 60;
	m_bStop = false;
	m_pMultiNumber = {};
}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CTimer::~CTimer()
{
	m_pMultiNumber = {};
}

//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CTimer::UpdateTimer()
{
	//�^�C�}�[�������Ă��鎞
	if (m_nTimer > 0 && m_bStop == false)
	{
		//�t���[�����Z
		m_nCntFlame--;

		m_pMultiNumber[CTimer::TIMER_TYPE::MINUTE]->SetMultiNumber(m_nCntFlame / 60 / 60);
		m_pMultiNumber[CTimer::TIMER_TYPE::SECOND]->SetMultiNumber(m_nCntFlame / 60 % 60);
		m_pMultiNumber[CTimer::TIMER_TYPE::COMMA]->SetMultiNumber((int)((m_nCntFlame % 60) * (10.0f / 6.0f)));
		//1�b����
		if (m_nCntFlame % 60 == 0)
		{
			//�^�C�}�[�J�E���g�_�E��
			m_nTimer--;

		}
	}
}

//------------------------------------------------------------------------------
//�f�o�b�O���\��
//------------------------------------------------------------------------------
void CTimer::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //_DEBUG
}

//------------------------------------------------------------------------------
//��������
//------------------------------------------------------------------------------
std::unique_ptr<CTimer> CTimer::Create(D3DXVECTOR3 const & TimerCenterPos, int const nTimer, D3DXMATRIX * pMtx)
{
	//�������m��
	std::unique_ptr<CTimer>pTimer(new CTimer);

	//���Ԑݒ�
	m_nTimer = nTimer;

	for (int nCnt = 0; nCnt < CTimer::TIMER_TYPE::MAX; nCnt++)
	{
		//����
		pTimer->m_pMultiNumber.emplace_back(
			CMultiNumber::Create(TimerCenterPos + D3DXVECTOR3(-TIMER_H_M_S_INTERVAL_X + TIMER_H_M_S_INTERVAL_X * nCnt, 0.0f, TIMER_H_M_S_INTERVAL_Z),
								TIMER_SIZE, nTimer, 2, CMultiNumber::NUMBER_TYPE::NUMBER_3D, CScene::OBJTYPE_UI));

		pTimer->m_pMultiNumber[nCnt]->SetParentMtxPtr(pMtx);
		pTimer->m_pMultiNumber[nCnt]->SetColor(RedColor);
	}

	//���^�[��
	return pTimer;
}