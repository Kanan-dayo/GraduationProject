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
#include "picture.h"
#include "game.h"
#include "keyboard.h"

//-------------------------------------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------------------------------------
// �萔
#define TABLET_INIMOVECOFF (0.25f)		// �ړ��W���̏����l

// �֐�
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

	// �����o�ϐ��̏�����
	InitMemberVariables();

	return S_OK;
}

//-------------------------------------------------------------------------------------------------------------
// �X�V
//-------------------------------------------------------------------------------------------------------------
void CTablet::Update()
{
	// ���[�h�ʂ̏���
	switch (m_mode)
	{
		MLB_CASE(MODE_NORMAL)  NormalProc();	// �ʏ폈��
		MLB_CASE(MODE_MOVEING) MoveingProc();	// �ړ�����
		MLB_CASEEND;							// �P�[�X�I��
	}

	if (CManager::GetKeyboard()->GetTrigger(DIK_M))
	{
		this->SetDestinationProc(D3DXVECTOR3(0.0f, 0.0f, -300.0f));
	}
	// �ϐ��錾
	FLOAT3* pPos = (FLOAT3 *)this->GetPosPtr();
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "���݈ʒu == [%.5f][%.5f][%.5f]\n", pPos->x, pPos->y, pPos->z);
}

//-------------------------------------------------------------------------------------------------------------
// �`��
//-------------------------------------------------------------------------------------------------------------
void CTablet::Draw()
{
	CSceneX::Draw();
}

//-------------------------------------------------------------------------------------------------------------
// �{�^���������Ă��邩
//-------------------------------------------------------------------------------------------------------------
bool CTablet::ItIsPressingButtons(void)
{
	// �ϐ��錾
	CTabletButton* pButton;	// �{�^�����

	for (int nCntTtpe = 0; nCntTtpe < CTabletButton::TYPE_MAX; nCntTtpe++)
	{
		// �{�^�����̎擾
		pButton = m_Button[nCntTtpe].get();
		// �����ꂽ�t���O���擾
		if (pButton->GetChangeFlag() ||
			pButton->GetInPressFlag())
		{
			return true;
		}
	}
	return false;
}

//-------------------------------------------------------------------------------------------------------------
// �����o�ϐ��̏�����
//-------------------------------------------------------------------------------------------------------------
void CTablet::InitMemberVariables(void)
{
	m_mode           = MODE_NORMAL;				// ���[�h
	m_fMoveCoeff     = TABLET_INIMOVECOFF;		// �ړ��W��
	m_posDest        = this->GetPos();			// �ړI�n
	m_bConstVelocity = false;					// �����t���O
	m_move           = MYLIB_VEC3_UNSET;		// �ړ���
	m_nDestFrame     = MYLIB_INT_UNSET;			// �ړI�n�܂ł̃t���[��
	m_nCntFrame      = MYLIB_INT_UNSET;			// �t���[�����̃J�E���g
}

//-------------------------------------------------------------------------------------------------------------
// �ʏ폈��
//-------------------------------------------------------------------------------------------------------------
void CTablet::NormalProc(void)
{
	// �ϐ��錾
	D3DXVECTOR3*   pNearPos = &CManager::GetRay()->NearPos;	// ���C�̋߂��ʒu
	D3DXVECTOR3*   pFarPos  = &CManager::GetRay()->FarPos;	// ���C�̉����ʒu
	BOOL           bHit     = FALSE;						// �q�b�g�t���O
	D3DXMATRIX     invmat;									// �Z�o�����t�s��
	D3DXVECTOR3    ray;										// ���C
	D3DXVECTOR3    InvNirePos;								// �Z�o�����߂��ʒu
	D3DXVECTOR3    InvForePos;								// �Z�o���������ʒu
	CTabletButton* pButton;									// �{�^�����
	LPD3DXMESH     pMesh;									// ���b�V�����

	for (int nCntTtpe = 0; nCntTtpe < CTabletButton::TYPE_MAX; nCntTtpe++)
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
		{// ���[�h��ύX���邽�߂̃t���O����
			pButton->FlagProcToChangeMode();
			CDebugProc::Print(CDebugProc::PLACE_LEFT, "[%d]�����������̂����݂��܂����B\n", nCntTtpe);
		}
		else
		{// �����ꂽ�t���O�������ݒ�
			pButton->SetToOffPressFlag();
			// �ύX�t���O�̐ݒ菈��
			pButton->SetChangeFlagProc();
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
// �ړ�����
//-------------------------------------------------------------------------------------------------------------
void CTablet::MoveingProc(void)
{
	// �����t���O���򏈗�
	switch (m_bConstVelocity) {
		MLB_CASE(true) ConstantVelocityProc();		// ��������
		MLB_DEFAULT    NonConstantVelocityProc();	// �s��������
	}
}

//-------------------------------------------------------------------------------------------------------------
// ��������
//-------------------------------------------------------------------------------------------------------------
void CTablet::ConstantVelocityProc(void)
{
	// �ϐ��錾
	FLOAT3* pPos = (FLOAT3 *)this->GetPosPtr();	// �ʒu�̎擾
	// �ʒu�̍X�V
	*pPos += m_move;
	// �t���[�������X�V
	m_nCntFrame++;
	// �t���[�����Ɠ����ɂȂ����Ƃ�
	if (m_nCntFrame == m_nDestFrame)
	{// �t���[���J�E���g�̏�����
		m_nCntFrame = MYLIB_INT_UNSET;
		// �ʒu��ړI�n�ɐݒ�
		*pPos = m_posDest;
		// �ʏ탂�[�h�ɐݒ�
		m_mode = MODE_NORMAL;
	}
}

//-------------------------------------------------------------------------------------------------------------
// �s��������
//-------------------------------------------------------------------------------------------------------------
void CTablet::NonConstantVelocityProc(void)
{
	// �ϐ��錾
	FLOAT3* pPos = (FLOAT3 *)this->GetPosPtr();
	// �ʒu�̍���
	VEC3 posDiff = m_posDest - *pPos;

	// �����������Ȃ����Ƃ�
	if (posDiff.LengthSq() < MYLIB_OX_EPSILON)
	{// �ʒu��ړI�n�ɐݒ�
		*pPos = m_posDest;
		// �ʏ탂�[�h�ɐݒ�
		m_mode = MODE_NORMAL;
		return;
	}
	// �ʒu�̍X�V
	*pPos += posDiff* m_fMoveCoeff;
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

//-------------------------------------------------------------------------------------------------------------
// ���������̐ݒ� �i�ړI�n��ݒ肷��O�j
//-------------------------------------------------------------------------------------------------------------
void CTablet::SetConstVelocityProc(const bool bConstVelocity, const int nDestFrame)
{
	// �ʏ펞�ȊO�̎��͐ݒ�ł��Ȃ�
	if (m_mode != MODE_NORMAL) {
		return;
	}
	// �����t���O�̐ݒ�
	SetConstVelocity(bConstVelocity);
	// �ړI�n�܂ł̃t���[���̐ݒ�
	SetDestFrame(nDestFrame);
}

//-------------------------------------------------------------------------------------------------------------
// �ړI�n��ݒ肷�鏈��
//-------------------------------------------------------------------------------------------------------------
void CTablet::SetDestinationProc(CONST D3DXVECTOR3 & posDest)
{
	// �ϐ��錾
	FLOAT3 &pos = (FLOAT3 &)this->GetPos();

	// �����ƈʒu�������Ƃ�
	if (VEC3(posDest - pos).LengthSq() < MYLIB_OX_EPSILON)
	{// �����𔲂���
		return;
	}

	// �ړ����[�h�ɐݒ�
	m_mode = CTablet::MODE_MOVEING;

	// �ړI�n�̐ݒ�
	SetPosDest(posDest);

	// �����t���O�������Ă��Ȃ������ړI�n�܂ł̃t���[����0�ȉ��̎�
	if (m_bConstVelocity == false ||
		m_nDestFrame <= MYLIB_INT_UNSET)
	{// �����𔲂���
		m_bConstVelocity = false;
		return;
	}
	// �ړ��ʂ�ݒ�
	m_move = (m_posDest - pos) / (float)m_nDestFrame;
}