//------------------------------------------------------------------------------
//
//���e�̏���  [Bomb.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "Bomb.h"
#include "renderer.h"
#include "manager.h"
#include "keyboard.h"
#include "modelinfo.h"
#include "module_none.h"
#include "module_timer.h"
#include "module_Button.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
//#define MODULE_INTERVAL (D3DXVECTOR3(120.0f,50.0f,60.0f))
//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CBomb::CBomb()
{
	m_nModuleNum = 0;
	m_pModuleList = {};
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CBomb::~CBomb()
{

}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CBomb::Init()
{
	CSceneX::Init();
	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CBomb::Uninit()
{
	CSceneX::Uninit();
}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CBomb::Update()
{
	CSceneX::Update();
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CBomb::Draw()
{
	CSceneX::Draw();

}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CBomb::ShowDebugInfo()
{
#ifdef _DEBUG

	static  int nSelectNum = 0;


	//�z�񂪋󂾂�����return
	if (m_pModuleList.empty())
	{
		return;
	}

	//�L�[�{�[�h�̃|�C���^
	CKeyboard *pKeyboard = CManager::GetKeyboard();

	if (pKeyboard->GetTrigger(DIK_LEFT))
	{
		nSelectNum--;
	}
	if (pKeyboard->GetTrigger(DIK_RIGHT))
	{
		nSelectNum++;
	}

	//�͈͓��ɗ}����
	CHossoLibrary::RangeLimit_Equal(nSelectNum, 0, (int)m_pModuleList.size() - 1);

	for (int nCnt = 0; nCnt < 12; nCnt++)
	{

		//nullcheck
		if (m_pModuleList[nCnt].get())
		{
			//���݂̑I��ԍ��Ƃ����Ă����ꍇ��true�ɂ��Ă���
			nCnt == nSelectNum ?
				m_pModuleList[nCnt]->SetSelect(true) :
				m_pModuleList[nCnt]->SetSelect(false);

		}
	}


	//����Ctrl�L�[
	if (pKeyboard->GetPress(DIK_LCONTROL))
	{
		for (int nCnt = 0; nCnt < 12; nCnt++)
		{
			//����
			if (pKeyboard->GetTrigger(0x01 + nCnt))
			{
				//nullcheck
				if (m_pModuleList[nCnt].get())
				{
					//���W���[���N���A
					m_pModuleList[nCnt]->Module_Clear();
				}
			}
		}
	}

#endif //DEBUG
}

//------------------------------------------------------------------------------
//�����֐�
//------------------------------------------------------------------------------
std::shared_ptr<CBomb> CBomb::Create(D3DXVECTOR3 const pos, D3DXVECTOR3 const rot, int const nModuleNum)
{
	//�������m��
	std::shared_ptr<CBomb> pBomb = std::make_shared<CBomb>();

	//������
	pBomb->Init();

	//���W�ƃT�C�Y�ݒ�
	pBomb->SetPos(pos);
	pBomb->SetRot(rot);

	//���f�����ݒ�
	pBomb->BindModelInfo(CModelInfo::GetModelInfo(CModelInfo::MODEL_BOMBOBJECT_BOMB));

	//���W���[������
	pBomb->CreateModule(nModuleNum);

	//Scene���ŊǗ�
	pBomb->SetObjType(CScene::OBJTYPE_BOMB);
	pBomb->AddSharedList(pBomb);

	return pBomb;
}

//------------------------------------------------------------------------------
//���W���[������
//------------------------------------------------------------------------------
void CBomb::CreateModule(int const nModuleNum)
{
//	int nCnt = 0;
//	m_nModuleNum = nModuleNum;
//
//	while(nCnt < nModuleNum)
//	{
//		int nSetNumber = nCnt;
//
//		int nX = nSetNumber % 3;
//		int nY = nSetNumber / 3;
//		int nZ = nSetNumber / 6;
//
//		m_pModuleList.emplace_back(CModule_Base::Create<CModule_Timer>
//		(D3DXVECTOR3(	(-MODULE_INTERVAL.x + (MODULE_INTERVAL.x * nX) ) * (1 - (nZ * 2)),
//					MODULE_INTERVAL.y - (MODULE_INTERVAL.y * ((nY % 2) * 2)),
//					-MODULE_INTERVAL.z + (MODULE_INTERVAL.z * nZ * 2)),
//		D3DXVECTOR3(0.0f,(D3DX_PI) * nZ,0.0f),GetMtxWorldPtr()));
//
//		nCnt++;
//	}

//Debug�p
#ifdef _DEBUG
	//1�Ԗ�
	CBomb::CreateModuleOne<CModule_Timer>(0);
	//2�Ԗ�
	CBomb::CreateModuleOne<CModule_Button>(1);
	//3�Ԗ�
	m_pModuleList.emplace_back(CModule_Base::Create<CModule_None>(D3DXVECTOR3(MODULE_INTERVAL.x,		MODULE_INTERVAL.y,	-MODULE_INTERVAL.z), ZeroVector3, GetMtxWorldPtr()));
	//4�Ԗ�
	m_pModuleList.emplace_back(CModule_Base::Create<CModule_Button>(D3DXVECTOR3(-MODULE_INTERVAL.x,		-MODULE_INTERVAL.y, -MODULE_INTERVAL.z), ZeroVector3, GetMtxWorldPtr()));
	//5�Ԗ�
	m_pModuleList.emplace_back(CModule_Base::Create<CModule_Button>(D3DXVECTOR3(0.0f,					-MODULE_INTERVAL.y, -MODULE_INTERVAL.z), ZeroVector3, GetMtxWorldPtr()));
	//6�Ԗ�
	m_pModuleList.emplace_back(CModule_Base::Create<CModule_Button>(D3DXVECTOR3(MODULE_INTERVAL.x,		-MODULE_INTERVAL.y, -MODULE_INTERVAL.z), ZeroVector3, GetMtxWorldPtr()));

	//7�Ԗ�
	m_pModuleList.emplace_back(CModule_Base::Create<CModule_Button>(D3DXVECTOR3(MODULE_INTERVAL.x,		MODULE_INTERVAL.y,	MODULE_INTERVAL.z), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), GetMtxWorldPtr()));
	//8�Ԗ�
	m_pModuleList.emplace_back(CModule_Base::Create<CModule_Button>(D3DXVECTOR3(0.0f,					MODULE_INTERVAL.y,	MODULE_INTERVAL.z), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), GetMtxWorldPtr()));
	//9�Ԗ�
	m_pModuleList.emplace_back(CModule_Base::Create<CModule_Button>(D3DXVECTOR3(-MODULE_INTERVAL.x,		MODULE_INTERVAL.y,	MODULE_INTERVAL.z), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), GetMtxWorldPtr()));
	//10�Ԗ�
	m_pModuleList.emplace_back(CModule_Base::Create<CModule_Button>(D3DXVECTOR3(MODULE_INTERVAL.x,		-MODULE_INTERVAL.y, MODULE_INTERVAL.z), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), GetMtxWorldPtr()));
	//11�Ԗ�
	m_pModuleList.emplace_back(CModule_Base::Create<CModule_Button>(D3DXVECTOR3(0.0f,					-MODULE_INTERVAL.y, MODULE_INTERVAL.z), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), GetMtxWorldPtr()));
	//12�Ԗ�
	m_pModuleList.emplace_back(CModule_Base::Create<CModule_Button>(D3DXVECTOR3(-MODULE_INTERVAL.x,		-MODULE_INTERVAL.y, MODULE_INTERVAL.z), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), GetMtxWorldPtr()));

#endif //_DEBUG
}
