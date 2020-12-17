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
#include "PaintingPen.h"
#include "chatTab.h"

//-------------------------------------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------------------------------------
#define TABLET_FILENAME    "data/TEXT/TabletInfo.txt"

//-------------------------------------------------------------------------------------------------------------
// �ÓI�����o�ϐ��̏�����
//-------------------------------------------------------------------------------------------------------------
D3DXVECTOR3 CTablet::m_aSetingModelPos[POS_MAX] = Mlf_array(MYLIB_VEC3_UNSET);		// �ݒ�p�̈ʒu
D3DXVECTOR3 CTablet::m_aSetingPosDest[SET_MAX]  = Mlf_array(MYLIB_VEC3_UNSET);		// �ݒ�p�̖ړI�n
float       CTablet::m_fMoveCoeff               = MYLIB_FLOAT_UNSET;					// �ړ�����
int         CTablet::m_nDestFrame               = MYLIB_INT_UNSET;						// �ړI�n�܂ł̃t���[��

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
// �ǂݍ���
//-------------------------------------------------------------------------------------------------------------
HRESULT CTablet::Load(void)
{
	// �t�@�C���ǂݍ���
	if (CLoadFile::ReadLineByLineFromFile(TABLET_FILENAME, ReadFromLine) != CLoadFile::LR_SUCCESS)
	{
#ifdef _DEBUG
		std::cout << "<<<<<<CPicture�̃t�@�C���ǂݍ��݂����s���܂����B>>>>>>\n";
#endif // _DEBUG
		return E_FAIL;
	}
	if (CTablet::LoadError() != S_OK)
	{
		return E_FAIL;
	}
	if (CTabletButton::LoadError() != S_OK)
	{
		return E_FAIL;
	}
	if (CPaintingPen::LoadError() != S_OK)
	{
		return E_FAIL;
	}
	if (CPicture::LoadError() != S_OK)
	{
		return E_FAIL;
	}
	return S_OK;
}

//-------------------------------------------------------------------------------------------------------------
// �G���[�̌��o
//-------------------------------------------------------------------------------------------------------------
HRESULT CTablet::LoadError(void)
{
	return S_OK;
}

//-------------------------------------------------------------------------------------------------------------
// ������
//-------------------------------------------------------------------------------------------------------------
HRESULT CTablet::Init()
{
	// �ʒu�̐ݒ�
	SetPos(m_aSetingPosDest[CManager::GetMode() == CManager::MODE_GAME ? SET_GAME_NEUT : SET_DECODING_NEUT]);

	//���f�����ݒ�
	BindModelInfo(CModelInfo::GetModelInfo(CModelInfo::MODEL_TABLET));
	CSceneX::Init();

	// �e�ʂ�ύX
	m_Button.reserve(CTabletButton::TYPE_MAX);

	// �{�^���ʒu�̎擾
	D3DXVECTOR3 *pButtonPos = &m_aSetingModelPos[CTablet::POS_PEN];

	// �^�C�v�������[�v
	for (int nCntTtpe = 0; nCntTtpe < CTabletButton::TYPE_MAX; nCntTtpe++)
	{// �V�����v�f�𖖔��ɒǉ�
		m_Button.push_back();
		// �����ɐ���
		m_Button.back() =
			CTabletButton::Create(
				this->GetMtxWorldPtr(),
				pButtonPos[nCntTtpe],
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
	// �`���b�g�^�u����ʒu��ݒ肷��
	SetPosFromChattabInfo();

	// ���[�h�ʂ̏���
	switch (m_mode)
	{
		ML_CASE(MODE_NORMAL)  NormalProc();		// �ʏ폈��
		ML_CASE(MODE_MOVEING) MoveingProc();	// �ړ�����
		ML_CASEEND;								// �P�[�X�I��
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
		ML_CASE(true) ConstantVelocityProc();		// ��������
		ML_DEFAULT    NonConstantVelocityProc();	// �s��������
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
		// ���������̃��[�h�ؑ�
		VelocityProcModeChange();
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
		// ���������̃��[�h�ؑ�
		VelocityProcModeChange();
		return;
	}
	// �ʒu�̍X�V
	*pPos += posDiff* m_fMoveCoeff;
}

//-------------------------------------------------------------------------------------------------------------
// ���������̃��[�h�`�F���W
//-------------------------------------------------------------------------------------------------------------
void CTablet::VelocityProcModeChange(void)
{
	if (CChatTab::GetTabState() == CChatTab::TABSTATE_CLOSED)
	{
		// �j���[�g�������[�h�ɐݒ�
		m_mode = MODE_NEUTRAL;
	}
	else
	{
		// �ʏ탂�[�h�ɐݒ�
		m_mode = MODE_NORMAL;
	}
}

//-------------------------------------------------------------------------------------------------------------
// ����
//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<CTablet> CTablet::Create(void)
{
	// �X�}�[�g�|�C���^�̐���
	std::shared_ptr<CTablet> pTablet = std::make_shared<CTablet>();
	pTablet->Init();

	//Scene�ŊǗ�
	pTablet->SetObjType(OBJTYPE_PICTURE);
	pTablet->AddSharedList(pTablet);
	return pTablet;
}

//-------------------------------------------------------------------------------------------------------------
// ���������̐ݒ� �i�ړI�n��ݒ肷��O�j
//-------------------------------------------------------------------------------------------------------------
void CTablet::SetConstVelocityProc(const bool bConstVelocity)
{
	// �ʏ펞�ȊO�̎��͐ݒ�ł��Ȃ�
	if (m_mode != MODE_NORMAL) {
		return;
	}
	// �����t���O�̐ݒ�
	SetConstVelocity(bConstVelocity);
}

//-------------------------------------------------------------------------------------------------------------
// �ړI�n��ݒ肷�鏈��
//-------------------------------------------------------------------------------------------------------------
void CTablet::SetDestinationProc(CONST D3DXVECTOR3 & posDest)
{
	// �ϐ��錾
	FLOAT3 &pos = (FLOAT3 &)this->GetPos();

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

//-------------------------------------------------------------------------------------------------------------
// �`���b�g�^�u�̏�񂩂�ʒu��ݒ肷��
//-------------------------------------------------------------------------------------------------------------
void CTablet::SetPosFromChattabInfo(void)
{
	// �Q�[�����[�h�̎擾
	CManager::MODE ManaMode = CManager::GetMode();

	// �N���b�N���ꂽ�Ƃ�
	if (!CChatTab::GetTabClick())
	{
		return;
	}
	// �Q�[�����[��
	switch (ManaMode)
	{
		// ��Ǒ��̎�
		ML_CASE(CManager::MODE_DECODING)
			// ���Ă��鎞
			if (CChatTab::GetTabState() == CChatTab::TABSTATE_CLOSED)
			{
				this->SetDestinationProc(m_aSetingPosDest[SET_DECODING_NEUT]);
			}
			else
			{
				this->SetDestinationProc(m_aSetingPosDest[SET_DECODING]);
			}
		// �Q�[���̎�
		ML_CASE(CManager::MODE_GAME)
			// ���Ă��鎞
			if (CChatTab::GetTabState() == CChatTab::TABSTATE_CLOSED)
			{
				this->SetDestinationProc(m_aSetingPosDest[SET_GAME_NEUT]);
			}
			else
			{

				this->SetDestinationProc(m_aSetingPosDest[SET_GAME] + CManager::GetRenderer()->GetCamera()->GetCameraPosV());
			}
		ML_CASEEND;
	}
}

//-------------------------------------------------------------------------------------------------------------
// 1�s�������ǂݎ��
//-------------------------------------------------------------------------------------------------------------
void CTablet::ReadFromLine(CONST_STRING cnpLine, CONST_STRING cnpEntryType, CONST_STRING cnpEntryData)
{
	if (strcmp(cnpEntryType, "Tablet") == 0)
	{
		CTablet::SetFromString(cnpLine);
	}
	else if (strcmp(cnpEntryType, "TabletButton") == 0)
	{
		CTabletButton::SetFromString(cnpLine);
	}
	else if (strcmp(cnpEntryType, "Pen") == 0)
	{
		CPaintingPen::SetFromString(cnpLine);
	}
	else if (strcmp(cnpEntryType, "Picture") == 0)
	{
		CPicture::SetFromString(cnpLine);
	}
}

//-------------------------------------------------------------------------------------------------------------
// �����񂩂�ݒ肷��
//-------------------------------------------------------------------------------------------------------------
void CTablet::SetFromString(CONST_STRING str)
{
	// �ϐ��錾
	float       fData  = MYLIB_FLOAT_UNSET;
	int         nData  = MYLIB_INT_UNSET;
	D3DXVECTOR3 F3Data = MYLIB_2DVECTOR_ZERO;
	// �ʒu
	if (sscanf(str, "pos = %f %f %f", &F3Data.x, &F3Data.y, &F3Data.z) == 3)
	{
		m_aSetingModelPos[CTablet::POS_TABLET] = F3Data;
	}
	// �ړ��W��
	else if (sscanf(str, "MoveCoeff = %f", &fData) == 1)
	{
		m_fMoveCoeff = fData;
	}
	else if (sscanf(str, "FrameDest = %d", &nData) == 1)
	{
		m_nDestFrame = nData;
	}
	// �Q�[�����̖ړI�n
	else if (sscanf(str, "GamePosDest = %f %f %f", &F3Data.x, &F3Data.y, &F3Data.z) == 3)
	{
		m_aSetingPosDest[SET_GAME] = F3Data;
	}
	// �Q�[���̃j���[�g�������̖ړI�n
	else if (sscanf(str, "GameNeutralPosDest = %f %f %f", &F3Data.x, &F3Data.y, &F3Data.z) == 3)
	{
		m_aSetingPosDest[SET_GAME_NEUT] = F3Data;
	}
	// ��ǎґ����̖̂ړI�n
	else if (sscanf(str, "DecodingPosDest = %f %f %f", &F3Data.x, &F3Data.y, &F3Data.z) == 3)
	{
		m_aSetingPosDest[SET_DECODING] = F3Data;
	}
	// ��ǎґ��̃j���[�g�������̖ړI�n
	else if (sscanf(str, "DecodingNeutralPosDest = %f %f %f", &F3Data.x, &F3Data.y, &F3Data.z) == 3)
	{
		m_aSetingPosDest[SET_DECODING_NEUT] = F3Data;
	}
	// �y���{�^���̈ʒu
	else if (sscanf(str, "PenButtonPos = %f %f %f", &F3Data.x, &F3Data.y, &F3Data.z) == 3)
	{
		m_aSetingModelPos[CTablet::POS_PEN] = F3Data;
	}
	// �����S���{�^���̈ʒu
	else if (sscanf(str, "EraserButtonPos = %f %f %f", &F3Data.x, &F3Data.y, &F3Data.z) == 3)
	{
		m_aSetingModelPos[CTablet::POS_ERASER] = F3Data;
	}
	// ���M�{�^���̈ʒu
	else if (sscanf(str, "SendButtonPos = %f %f %f", &F3Data.x, &F3Data.y, &F3Data.z) == 3)
	{
		m_aSetingModelPos[CTablet::POS_SEND] = F3Data;
	}
}
