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
#define TabletButtonSetPos(cnt) D3DXVECTOR3(100.0f, 0.0f - 30.0f * cnt, -8.0f)

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
	// �ϐ��錾
	D3DXVECTOR3*   pNearPos   = &CManager::GetRay()->NearPos;	// ���C�̋߂��ʒu
	D3DXVECTOR3*   pFarPos    = &CManager::GetRay()->FarPos;	// ���C�̉����ʒu
	BOOL           bHit       = 0;								// �q�b�g�t���O
	D3DXMATRIX     invmat;										// �Z�o�����t�s��
	D3DXVECTOR3    ray;											// ���C
	D3DXVECTOR3    InvNirePos;									// �Z�o�����߂��ʒu
	D3DXVECTOR3    InvForePos;									// �Z�o���������ʒu
	CTabletButton* pButton;										// �{�^�����
	LPD3DXMESH     pMesh;										// ���b�V�����
	int nCntTtpe;
	for (nCntTtpe = 0; nCntTtpe < CTabletButton::TYPE_MAX; nCntTtpe++)
	{
		// �{�^�����̎擾
		pButton = m_Button[nCntTtpe].get();
		// ���b�V�����̎擾
		pMesh = pButton->GetModelInfo()->GetMesh();

		/* �Ώ�����������݂����C�ɕϊ����� */
		//	�t�s��̎擾
		D3DXMatrixInverse(&invmat, NULL, pButton->GetMtxWorldPtr());
		//	�t�s����g�p���A���C�n�_����ϊ��@�ʒu�ƌ����ŕϊ�����֐����قȂ�̂ŗv����
		D3DXVec3TransformCoord(&InvNirePos, pNearPos, &invmat);
		//	���C�I�_����ϊ�
		D3DXVec3TransformCoord(&InvForePos, pFarPos, &invmat);
		//	���C��������ϊ�
		D3DXVec3Normalize(&ray, &(InvForePos - InvNirePos));
		//Ray���΂�
		D3DXIntersect(pMesh, &InvNirePos, &ray, &bHit, NULL, NULL, NULL, NULL, NULL, NULL);
		// HIT���Ă��鎞
		if (bHit == 1)
		{
			// ���[�h�̐ݒ�
			pButton->SetMode();
			CDebugProc::Print(CDebugProc::PLACE_LEFT, "[%d]�����������̂����݂��܂����B\n", nCntTtpe);
		}
		else
		{
			pButton->SetToOffPressFlag();
			pButton->SetChangeFlag();
		}
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
