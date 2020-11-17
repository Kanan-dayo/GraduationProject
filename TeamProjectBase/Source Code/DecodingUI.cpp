//*************************************************************************************************************
//
// ��Ǐ���UI[���� [DecodingUI.h]
// Author:IKUTO SEKINE
//
//*************************************************************************************************************
//-------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------------------
#include "DecodingUI.h"
#include "manager.h"
#include "renderer.h"

//-------------------------------------------------------------------------------------------------------------
// �ÓI�����o�̏�����
//-------------------------------------------------------------------------------------------------------------
const float      CDecodingUI::m_fHalfPi    = D3DX_PI * MYLIB_HALF_SIZE;		// �~�����̔����̒l
const float      CDecodingUI::m_fMinHalfPi = D3DX_PI * -MYLIB_HALF_SIZE;	// �~�����̔����̕��̒l

//-------------------------------------------------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------------------------------------------------
CDecodingUI::CDecodingUI()
{
}

//-------------------------------------------------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------------------------------------------------
CDecodingUI::~CDecodingUI()
{
}

//-------------------------------------------------------------------------------------------------------------
// ����
//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<CDecodingUI> CDecodingUI::Create(SETINGINFO Seting)
{
	// �X�}�[�g�|�C���^�̐���
	std::shared_ptr<CDecodingUI> pPicture = std::make_shared<CDecodingUI>();
	// �ݒ�p��񂩂�ݒ肷��
	pPicture->SetFromSetingInfo(Seting);
	// ������
	pPicture->Init();

	//Scene�ŊǗ�
	pPicture->SetObjType(OBJTYPE_UI);
	pPicture->AddSharedList(pPicture);
	return pPicture;
}

//-------------------------------------------------------------------------------------------------------------
// ������
//-------------------------------------------------------------------------------------------------------------
HRESULT CDecodingUI::Init()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	try
	{// ���_���̍쐬
		MakeVertex(pDevice);
	}
	catch (HRESULT rh)
	{
		return rh;
	}
	return S_OK;
}

//-------------------------------------------------------------------------------------------------------------
// �X�V
//-------------------------------------------------------------------------------------------------------------
void CDecodingUI::Update()
{
}

//-------------------------------------------------------------------------------------------------------------
// �`��
//-------------------------------------------------------------------------------------------------------------
void CDecodingUI::Draw()
{
	if (m_bDisp)
	{
		//�f�o�C�X�擾
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, GetTexture());

		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
			0,										//�J�n����C���f�b�N�X(���_)
			2);										//�|���S���̖���
	}
}

//-------------------------------------------------------------------------------------------------------------
// ���_���̍X�V
//-------------------------------------------------------------------------------------------------------------
void CDecodingUI::UpdateVertex(bool bPos, bool bCol)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;
	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (bPos)
	{//���_�̍��W
		SetVatexPos(pVtx, m_OriginType, &m_pos, &m_size, m_fAngle);
	}

	if (bCol)
	{//���_�̐F
		SetVatexCol(pVtx);
	}

	//���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();
}

//-------------------------------------------------------------------------------------------------------------
// ���_���̍X�V
//-------------------------------------------------------------------------------------------------------------
void CDecodingUI::UpdateVertex(D3DXVECTOR3 * pPos, D3DXVECTOR2 * pSize, D3DXCOLOR * pCol)
{
	// ���_���̍X�V
	UpdateVertex(SetWithPosPtr(pPos) || SetWithSizePtr(pSize), SetWithColPtr(pCol));
}

//-------------------------------------------------------------------------------------------------------------
// �ݒ�p���̐ݒ�
//-------------------------------------------------------------------------------------------------------------
void CDecodingUI::SetFromSetingInfo(CONST SETINGINFO & Seting)
{
	m_pos = Seting.pos;
	m_size = Seting.size;
	m_col = Seting.col;
	m_fAngle = Seting.fAngle;
	m_OriginType = Seting.OriginType;
	m_bDisp = Seting.bDisp;
}

//-------------------------------------------------------------------------------------------------------------
// ���_���̍쐬
//-------------------------------------------------------------------------------------------------------------
void CDecodingUI::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	//�m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL)))
	{
		//���_�o�b�t�@�쐬���s
		throw E_FAIL;
	}

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�̍��W
	SetVatexPos(pVtx, m_OriginType, &m_pos, &m_size, m_fAngle);

	//���_�̓������W
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�̐F
	SetVatexCol(pVtx);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();
}

//-------------------------------------------------------------------------------------------------------------
// ���_�ʒu�̐ݒ�
//-------------------------------------------------------------------------------------------------------------
void CDecodingUI::SetVatexPos(VERTEX_2D *pVtx, ORIGINVERTEXTYPE type, D3DXVECTOR3 * pPos, D3DXVECTOR2 * pSize, float fRotation)
{
	// �ϐ��錾
	D3DXVECTOR2 halfSize = *pSize * MYLIB_HALF_SIZE;	// �����̑傫��
	switch (type)
	{
	case ORIGINVERTEXTYPE_LOWERLEFT:
		pVtx[0].pos = D3DXVECTOR3(pPos->x,            pPos->y - pSize->y, MYLIB_FLOAT_UNSET);
		pVtx[1].pos = D3DXVECTOR3(pPos->x + pSize->x, pPos->y - pSize->y, MYLIB_FLOAT_UNSET);
		pVtx[2].pos = D3DXVECTOR3(pPos->x,            pPos->y,            MYLIB_FLOAT_UNSET);
		pVtx[3].pos = D3DXVECTOR3(pPos->x + pSize->x, pPos->y,            MYLIB_FLOAT_UNSET);
		break;
	case ORIGINVERTEXTYPE_LOWERCENTER:
		pVtx[0].pos = D3DXVECTOR3(pPos->x - halfSize.x, pPos->y - pSize->y, MYLIB_FLOAT_UNSET);
		pVtx[1].pos = D3DXVECTOR3(pPos->x + halfSize.x, pPos->y - pSize->y, MYLIB_FLOAT_UNSET);
		pVtx[2].pos = D3DXVECTOR3(pPos->x - halfSize.x, pPos->y,            MYLIB_FLOAT_UNSET);
		pVtx[3].pos = D3DXVECTOR3(pPos->x + halfSize.x, pPos->y,            MYLIB_FLOAT_UNSET);
		break;
	case ORIGINVERTEXTYPE_LOWERRIGHT:
		pVtx[0].pos = D3DXVECTOR3(pPos->x - pSize->x, pPos->y - pSize->y, MYLIB_FLOAT_UNSET);
		pVtx[1].pos = D3DXVECTOR3(pPos->x, pPos->y - pSize->y,            MYLIB_FLOAT_UNSET);
		pVtx[2].pos = D3DXVECTOR3(pPos->x - pSize->x, pPos->y,            MYLIB_FLOAT_UNSET);
		pVtx[3].pos = D3DXVECTOR3(pPos->x, pPos->y,                       MYLIB_FLOAT_UNSET);
		break;
	case ORIGINVERTEXTYPE_CENTERLEFT:
		pVtx[0].pos = D3DXVECTOR3(pPos->x,            pPos->y - halfSize.y, MYLIB_FLOAT_UNSET);
		pVtx[1].pos = D3DXVECTOR3(pPos->x + pSize->x, pPos->y - halfSize.y, MYLIB_FLOAT_UNSET);
		pVtx[2].pos = D3DXVECTOR3(pPos->x,            pPos->y + halfSize.y, MYLIB_FLOAT_UNSET);
		pVtx[3].pos = D3DXVECTOR3(pPos->x + pSize->x, pPos->y + halfSize.y, MYLIB_FLOAT_UNSET);
		break;
	case ORIGINVERTEXTYPE_CENTER:
		pVtx[0].pos = D3DXVECTOR3(pPos->x - halfSize.x, pPos->y - halfSize.y, MYLIB_FLOAT_UNSET);
		pVtx[1].pos = D3DXVECTOR3(pPos->x + halfSize.x, pPos->y - halfSize.y, MYLIB_FLOAT_UNSET);
		pVtx[2].pos = D3DXVECTOR3(pPos->x - halfSize.x, pPos->y + halfSize.y, MYLIB_FLOAT_UNSET);
		pVtx[3].pos = D3DXVECTOR3(pPos->x + halfSize.x, pPos->y + halfSize.y, MYLIB_FLOAT_UNSET);
		break;
	case ORIGINVERTEXTYPE_CENTERRIGHT:
		pVtx[0].pos = D3DXVECTOR3(pPos->x - pSize->x, pPos->y - halfSize.y, MYLIB_FLOAT_UNSET);
		pVtx[1].pos = D3DXVECTOR3(pPos->x,            pPos->y - halfSize.y, MYLIB_FLOAT_UNSET);
		pVtx[2].pos = D3DXVECTOR3(pPos->x - pSize->x, pPos->y - halfSize.y, MYLIB_FLOAT_UNSET);
		pVtx[3].pos = D3DXVECTOR3(pPos->x,            pPos->y - halfSize.y, MYLIB_FLOAT_UNSET);
		break;
	case ORIGINVERTEXTYPE_UPPERLEFT:
		pVtx[0].pos = D3DXVECTOR3(pPos->x,            pPos->y,            MYLIB_FLOAT_UNSET);
		pVtx[1].pos = D3DXVECTOR3(pPos->x + pSize->x, pPos->y,            MYLIB_FLOAT_UNSET);
		pVtx[2].pos = D3DXVECTOR3(pPos->x,            pPos->y + pSize->y, MYLIB_FLOAT_UNSET);
		pVtx[3].pos = D3DXVECTOR3(pPos->x + pSize->x, pPos->y + pSize->y, MYLIB_FLOAT_UNSET);
		break;
	case ORIGINVERTEXTYPE_UPPERCENTER:
		pVtx[0].pos = D3DXVECTOR3(pPos->x - pSize->x, pPos->y,            MYLIB_FLOAT_UNSET);
		pVtx[1].pos = D3DXVECTOR3(pPos->x + pSize->x, pPos->y,            MYLIB_FLOAT_UNSET);
		pVtx[2].pos = D3DXVECTOR3(pPos->x - pSize->x, pPos->y + pSize->y, MYLIB_FLOAT_UNSET);
		pVtx[3].pos = D3DXVECTOR3(pPos->x + pSize->x, pPos->y + pSize->y, MYLIB_FLOAT_UNSET);
		break;
	case ORIGINVERTEXTYPE_UPPERRIGHT:
		pVtx[0].pos = D3DXVECTOR3(pPos->x - pSize->x, pPos->y,            MYLIB_FLOAT_UNSET);
		pVtx[1].pos = D3DXVECTOR3(pPos->x,            pPos->y,            MYLIB_FLOAT_UNSET);
		pVtx[2].pos = D3DXVECTOR3(pPos->x - pSize->x, pPos->y + pSize->y, MYLIB_FLOAT_UNSET);
		pVtx[3].pos = D3DXVECTOR3(pPos->x,            pPos->y + pSize->y, MYLIB_FLOAT_UNSET);
		break;
	case ORIGINVERTEXTYPE_ROTCENTER:
		pVtx[0].pos.x = pPos->x + sinf(D3DX_PI + fRotation)*halfSize.y + sinf(m_fMinHalfPi + fRotation)*halfSize.x;
		pVtx[0].pos.y = pPos->y + cosf(D3DX_PI + fRotation)*halfSize.y + cosf(m_fMinHalfPi + fRotation)*halfSize.x;
		pVtx[1].pos.x = pPos->x + sinf(D3DX_PI + fRotation)*halfSize.y + sinf(m_fHalfPi + fRotation)*halfSize.x;
		pVtx[1].pos.y = pPos->y + cosf(D3DX_PI + fRotation)*halfSize.y + cosf(m_fHalfPi + fRotation)*halfSize.x;
		pVtx[2].pos.x = pPos->x + sinf(fRotation)*halfSize.y           + sinf(m_fMinHalfPi + fRotation)*halfSize.x;
		pVtx[2].pos.y = pPos->y + cosf(fRotation)*halfSize.y           + cosf(m_fMinHalfPi + fRotation)*halfSize.x;
		pVtx[3].pos.x = pPos->x + sinf(fRotation)*halfSize.y           + sinf(m_fHalfPi + fRotation)*halfSize.x;
		pVtx[3].pos.y = pPos->y + cosf(fRotation)*halfSize.y           + cosf(m_fHalfPi + fRotation)*halfSize.x;
		pVtx[0].pos.z = MYLIB_FLOAT_UNSET;
		pVtx[1].pos.z = MYLIB_FLOAT_UNSET;
		pVtx[2].pos.z = MYLIB_FLOAT_UNSET;
		pVtx[3].pos.z = MYLIB_FLOAT_UNSET;
		break;
	case ORIGINVERTEXTYPE_ROTCENTERLEFT:
		pVtx[0].pos.x = pPos->x + sinf(D3DX_PI + fRotation)*halfSize.y;
		pVtx[0].pos.y = pPos->y + cosf(D3DX_PI + fRotation)*halfSize.y;
		pVtx[1].pos.x = pPos->x + sinf(D3DX_PI + fRotation)*halfSize.y + sinf(m_fHalfPi + fRotation)*(pSize->x);
		pVtx[1].pos.y = pPos->y + cosf(D3DX_PI + fRotation)*halfSize.y + cosf(m_fHalfPi + fRotation)*(pSize->x);
		pVtx[2].pos.x = pPos->x + sinf(fRotation)*halfSize.y;
		pVtx[2].pos.y = pPos->y + cosf(fRotation)*halfSize.y;
		pVtx[3].pos.x = pPos->x + sinf(fRotation)*halfSize.y + sinf(m_fHalfPi + fRotation)*(pSize->x);
		pVtx[3].pos.y = pPos->y + cosf(fRotation)*halfSize.y + cosf(m_fHalfPi + fRotation)*(pSize->x);
		pVtx[0].pos.z = MYLIB_FLOAT_UNSET;
		pVtx[1].pos.z = MYLIB_FLOAT_UNSET;
		pVtx[2].pos.z = MYLIB_FLOAT_UNSET;
		pVtx[3].pos.z = MYLIB_FLOAT_UNSET;
		break;

	case ORIGINVERTEXTYPE_ROTLOWERCENTER:
		pVtx[2].pos.x = pPos->x + sinf(m_fMinHalfPi + fRotation)*halfSize.x;
		pVtx[2].pos.y = pPos->y + cosf(m_fMinHalfPi + fRotation)*halfSize.x;
		pVtx[3].pos.x = pPos->x + sinf(m_fHalfPi + fRotation)*halfSize.x;
		pVtx[3].pos.y = pPos->y + cosf(m_fHalfPi + fRotation)*halfSize.x;
		pVtx[0].pos.x = pVtx[2].pos.x + sinf(D3DX_PI + fRotation)*(pSize->y);
		pVtx[0].pos.y = pVtx[2].pos.y + cosf(D3DX_PI + fRotation)*(pSize->y);
		pVtx[1].pos.x = pVtx[3].pos.x + sinf(D3DX_PI + fRotation)*(pSize->y);
		pVtx[1].pos.y = pVtx[3].pos.y + cosf(D3DX_PI + fRotation)*(pSize->y);

		pVtx[0].pos.z = MYLIB_FLOAT_UNSET;
		pVtx[1].pos.z = MYLIB_FLOAT_UNSET;
		pVtx[2].pos.z = MYLIB_FLOAT_UNSET;
		pVtx[3].pos.z = MYLIB_FLOAT_UNSET;
		break;
	case ORIGINVERTEXTYPE_ROTCENTERRIGHT:
		pVtx[0].pos.x = pPos->x + sinf(D3DX_PI + fRotation)*halfSize.y + sinf(m_fMinHalfPi + fRotation)*(pSize->x);
		pVtx[0].pos.y = pPos->y + cosf(D3DX_PI + fRotation)*halfSize.y + cosf(m_fMinHalfPi + fRotation)*(pSize->x);
		pVtx[1].pos.x = pPos->x + sinf(D3DX_PI + fRotation)*halfSize.y;
		pVtx[1].pos.y = pPos->y + cosf(D3DX_PI + fRotation)*halfSize.y;
		pVtx[2].pos.x = pPos->x + sinf(fRotation)*halfSize.y + sinf(m_fMinHalfPi + fRotation)*(pSize->x);
		pVtx[2].pos.y = pPos->y + cosf(fRotation)*halfSize.y + cosf(m_fMinHalfPi + fRotation)*(pSize->x);
		pVtx[3].pos.x = pPos->x + sinf(fRotation)*halfSize.y;
		pVtx[3].pos.y = pPos->y + cosf(fRotation)*halfSize.y;
		pVtx[0].pos.z = MYLIB_FLOAT_UNSET;
		pVtx[1].pos.z = MYLIB_FLOAT_UNSET;
		pVtx[2].pos.z = MYLIB_FLOAT_UNSET;
		pVtx[3].pos.z = MYLIB_FLOAT_UNSET;
		break;
	case ORIGINVERTEXTYPE_ROTUPPERCENTER:
		pVtx[0].pos.x = pPos->x + sinf(m_fMinHalfPi + fRotation)*halfSize.x;
		pVtx[0].pos.y = pPos->y + cosf(m_fMinHalfPi + fRotation)*halfSize.x;
		pVtx[1].pos.x = pPos->x + sinf(m_fHalfPi + fRotation)*halfSize.x;
		pVtx[1].pos.y = pPos->y + cosf(m_fHalfPi + fRotation)*halfSize.x;
		pVtx[2].pos.x = pVtx[0].pos.x + sinf(fRotation)*(pSize->y);
		pVtx[2].pos.y = pVtx[0].pos.y + cosf(fRotation)*(pSize->y);
		pVtx[3].pos.x = pVtx[1].pos.x + sinf(fRotation)*(pSize->y);
		pVtx[3].pos.y = pVtx[1].pos.y + cosf(fRotation)*(pSize->y);
		pVtx[0].pos.z = MYLIB_FLOAT_UNSET;
		pVtx[1].pos.z = MYLIB_FLOAT_UNSET;
		pVtx[2].pos.z = MYLIB_FLOAT_UNSET;
		pVtx[3].pos.z = MYLIB_FLOAT_UNSET;
		break;
	}
}

//-------------------------------------------------------------------------------------------------------------
// ���_�J���[�̐ݒ�
//-------------------------------------------------------------------------------------------------------------
void CDecodingUI::SetVatexCol(VERTEX_2D * pVtx)
{
	//���_�̐F
	pVtx[0].col =
		pVtx[1].col =
		pVtx[2].col =
		pVtx[3].col = m_col;
}
