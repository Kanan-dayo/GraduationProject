//------------------------------------------------------------------------------
//
//���W���[���̃����v  [module_parts_lamp.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "module_parts_lamp.h"
#include "renderer.h"
#include "manager.h"
#include "modelinfo.h"
#include "particle.h"
#include "timer.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define LAMP_OFFSET (D3DXVECTOR3(0.0f,0.0f,-15.0f))

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CModule_Parts_Lamp::CModule_Parts_Lamp()
{
	m_LampState = LAMP_STATE::OFF;
	m_nCntLampCnt = 0;
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CModule_Parts_Lamp::~CModule_Parts_Lamp()
{

}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CModule_Parts_Lamp::Init()
{
	//���f�����ݒ�
	BindModelInfo(CModelInfo::GetModelInfo(CModelInfo::MODEL_MODULEPARTS_CLEARLAMP));

	CSceneX::Init();
	return S_OK;
}

//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CModule_Parts_Lamp::Update()
{
	D3DXVECTOR3 vec;

	switch (m_LampState)
	{
	case CModule_Parts_Lamp::LAMP_STATE::OFF:
		break;
	case CModule_Parts_Lamp::LAMP_STATE::RED:
		m_nCntLampCnt--;

		//�Ԃ��p�[�e�B�N������
		CParticle::CreateFromText(*D3DXVec3TransformCoord(&vec,&LAMP_OFFSET, GetMtxWorldPtr()), ZeroVector3, CParticleParam::EFFECT_LED_LIGHT, RedColor);

		if (m_nCntLampCnt < 0)
		{
			//�N���A�ςȂ�΁A�����łȂ��Ȃ����
			GetClearFlag() ?
				SetLampState(LAMP_STATE::GREEN) :
				SetLampState(LAMP_STATE::OFF);
		}
		break;
	case CModule_Parts_Lamp::LAMP_STATE::GREEN:

		//�΂̃p�[�e�B�N������
 		CParticle::CreateFromText(*D3DXVec3TransformCoord(&vec, &LAMP_OFFSET, GetMtxWorldPtr()), ZeroVector3, CParticleParam::EFFECT_LED_LIGHT, GreenColor);
		break;
	}
	CSceneX::Update();
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CModule_Parts_Lamp::Draw()
{
	CSceneX::Draw();
}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CModule_Parts_Lamp::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}

//------------------------------------------------------------------------------
//�����v�̏�Ԑ؂�ւ�
//------------------------------------------------------------------------------
void CModule_Parts_Lamp::SetLampState(LAMP_STATE lampstate)
{
	//�����X�e�[�g����������return
	if (m_LampState == lampstate)
	{
		return;
	}

	//�X�e�[�g�؂�ւ�
	m_LampState = lampstate;

	//�؂�ւ�����X�e�[�g�ɉ����ď���
	switch (lampstate)
	{
	case CModule_Parts_Lamp::LAMP_STATE::OFF:
		break;
	case CModule_Parts_Lamp::LAMP_STATE::RED:
		m_nCntLampCnt = 90;
		break;
	case CModule_Parts_Lamp::LAMP_STATE::GREEN:
		SetClearFlag(true);
		break;

	}
}
