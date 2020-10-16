//------------------------------------------------------------------------------
//
//���W���[���̏���  [module.cpp]
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
	CSceneX::Init();
	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CModule_Parts_Lamp::Uninit()
{
	CSceneX::Uninit();
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
		m_nCntLampCnt = 180;
		break;
	case CModule_Parts_Lamp::LAMP_STATE::GREEN:
		break;

	}
}

//------------------------------------------------------------------------------
//�����֐�
//Bomb���Ǘ�
//------------------------------------------------------------------------------
std::shared_ptr<CModule_Parts_Lamp> CModule_Parts_Lamp::Create(D3DXVECTOR3 const pos, D3DXMATRIX * const pBomb)
{
	//�������m��
	std::shared_ptr<CModule_Parts_Lamp> pModuleTimer = std::make_shared<CModule_Parts_Lamp>();

	//������
	pModuleTimer->Init();

	//���W�ƃT�C�Y�ݒ�
	pModuleTimer->SetPos(pos);
	pModuleTimer->SetParentMtxPtr(pBomb);

	//���f�����ݒ�
	pModuleTimer->BindModelInfo(CModelInfo::GetModelInfo(CModelInfo::MODEL_BOMBOBJECT_CLEARLAMP));

	//Scene���ŊǗ�
	pModuleTimer->SetObjType(CScene::OBJTYPE_MODULE);
	pModuleTimer->AddSharedList(pModuleTimer);

	return pModuleTimer;
}
