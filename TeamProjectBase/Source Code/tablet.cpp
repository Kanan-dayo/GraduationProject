//*************************************************************************************************************
//
// �^�u���b�g���� [tablet.cpp]
// Author:IKUTO SEKINE
//
//*************************************************************************************************************
//-------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------------------
#include "tablet.h"
#include "modelinfo.h"
#include "TabletButton.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"

//-------------------------------------------------------------------------------------------------------------
// �}�N���֐���`
//-------------------------------------------------------------------------------------------------------------
#define TabletButtonSetPos(cnt) D3DXVECTOR3(100.0f, 0.0f - 30.0f *cnt, -8.0f)

//-------------------------------------------------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------------------------------------------------
CTablet::CTablet()
{
}

//-------------------------------------------------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------------------------------------------------
CTablet::~CTablet()
{
}

//-------------------------------------------------------------------------------------------------------------
// ������
//-------------------------------------------------------------------------------------------------------------
HRESULT CTablet::Init()
{
	//���f�����ݒ�
	BindModelInfo(CModelInfo::GetModelInfo(CModelInfo::MODEL_TABLET));
	CSceneX::Init();

	// �e�ʂ�ύX
	m_Button.reserve(CTabletButton::TYPE_MAX);
	// �^�C�v�������[�v
	for (int nCntTtpe = 0; nCntTtpe < CTabletButton::TYPE_MAX; nCntTtpe++)
	{// �V�����v�f�𖖔��ɒǉ�
		m_Button.push_back();
		// �����ɐ���
		m_Button.back() =
			CTabletButton::Create(
				this->GetMtxWorldPtr(),
				TabletButtonSetPos(nCntTtpe),
				(CTabletButton::TYPE)nCntTtpe);
	}

	return E_NOTIMPL;
}

//-------------------------------------------------------------------------------------------------------------
// �X�V
//-------------------------------------------------------------------------------------------------------------
void CTablet::Update()
{
	D3DXVECTOR3* pRayDir = &CManager::GetRay()->vec;
	BOOL bHit = 0;
	int nHitTypr = -1;

	CDebugProc::Print(CDebugProc::PLACE_LEFT, "���C�̌���[%f][%f][%f]\n", pRayDir->x, pRayDir->y, pRayDir->z);

	D3DXVECTOR3 pos;
	D3DXVECTOR3 CameraPos = CManager::GetRenderer()->GetCamera()->GetCameraPosV();

	for (int nCntTtpe = 0; nCntTtpe < CTabletButton::TYPE_MAX; nCntTtpe++)
	{
		CTabletButton* pButton = m_Button[nCntTtpe].get();
		CModelInfo * pModelInfo = pButton->GetModelInfo();
		LPD3DXMESH pMesh = pModelInfo->GetMesh();

		pos.x = CameraPos.x - pButton->GetMtxWorldPtr()->_41;
		pos.y = CameraPos.y - pButton->GetMtxWorldPtr()->_42;
		pos.z = CameraPos.z -pButton->GetMtxWorldPtr()->_43;

		D3DXIntersect(pMesh, &pos, pRayDir, &bHit, NULL, NULL, NULL, NULL, NULL, NULL);

		if (bHit == 1)
		{
			nHitTypr = nCntTtpe;
		}
	}
	if (nHitTypr != -1)
	{
		CDebugProc::Print(CDebugProc::PLACE_LEFT, "[%d]��������\n", nHitTypr);
	}
}

//-------------------------------------------------------------------------------------------------------------
// �`��
//-------------------------------------------------------------------------------------------------------------
void CTablet::Draw()
{
	CSceneX::Draw();
}

//-------------------------------------------------------------------------------------------------------------
// ����
//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<CTablet> CTablet::Create(CONST D3DXVECTOR3 & pos)
{
	// �X�}�[�g�|�C���^�̐���
	std::shared_ptr<CTablet> pTablet = std::make_shared<CTablet>();
	pTablet->SetPos(pos);
	pTablet->Init();

	//Scene�ŊǗ�
	pTablet->SetObjType(OBJTYPE_PICTURE);
	pTablet->AddSharedList(pTablet);
	return pTablet;
}
