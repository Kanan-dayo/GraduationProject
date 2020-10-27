//*************************************************************************************************************
//
// �G�̏��� [picture.cpp]
// Author:IKUTO SEKINE
//
//*************************************************************************************************************
//-------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------------------
#include "picture.h"
#include "manager.h"
#include "renderer.h"
#include "mouse.h"
#include "camera.h"
#include "PaintingPen.h"

//-------------------------------------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------------------------------------
#define PICTURE_FILENAME  "data/TEXT/PictureInfo.txt"

//-------------------------------------------------------------------------------------------------------------
// �}�N���֐�
//-------------------------------------------------------------------------------------------------------------
#define Paint(col) Mybfunc_bit_set(col,0)
#define Clear(col) Mybfunc_bit_clear(col,0)

//-------------------------------------------------------------------------------------------------------------
// �ÓI�����o�ϐ��̏�����
//-------------------------------------------------------------------------------------------------------------
INTEGER2      CPicture::m_nNumPolyBlock   = MYLIB_INT2_UNSET;							// �|���S����(���炷�傫���̐ݒ��2�{�ɂ���)
FLOAT2        CPicture::m_size            = MYLIB_2DVECTOR_ZERO;						// �傫��
D3DXVECTOR3   CPicture::m_PlaneNor        = D3DXVECTOR3(0.0f, 0.0f, 1.0f);				// ���ʂ̖@��
D3DXVECTOR2   CPicture::m_PixelSize       = MYLIB_VEC2_UNSET;							// �s�N�Z���T�C�Y
UINT          CPicture::m_nNumDataMax     = MYLIB_INT_UNSET;							// �ő�f�[�^���ő�f�[�^��
CPaintingPen* CPicture::m_pPen            = nullptr;									// �y���̃|�C���^
D3DXVECTOR2   CPicture::m_PixelSizehalf   = MYLIB_VEC2_UNSET;							// �s�N�Z���T�C�Y�̔���
//-------------------------------------------------------------------------------------------------------------
// �ǂݍ���
//-------------------------------------------------------------------------------------------------------------
HRESULT CPicture::Load(void)
{
	// * ���� [Parameter]
	// �t�@�C���ǂݍ���
	if (CLoadFile::ReadLineByLineFromFile(PICTURE_FILENAME, ReadFromLine) != CLoadFile::LR_SUCCESS)
	{
#ifdef _DEBUG
		std::cout << "<<<<<<CPicture�̃t�@�C���ǂݍ��݂����s���܂����B>>>>>>\n";
#endif // _DEBUG
		return E_FAIL;
	}
	// �ǂ�����[���̎�
	if (m_nNumPolyBlock.OneIsZero() == true)
	{
#ifdef _DEBUG
		std::cout << "<<<<<<CPicture�̂ǂ��炩�̃|���S������0�ł����B>>>>>>\n";
#endif // _DEBUG
		return E_FAIL;
	}

	m_PixelSize = m_size / m_nNumPolyBlock;
	m_PixelSizehalf = m_PixelSize* MYLIB_HALF_SIZE;
	m_nNumDataMax = m_nNumPolyBlock.nY * m_nNumPolyBlock.nX;

	// �y���̐���
	m_pPen = CPaintingPen::Create();
	return S_OK;
}

//-------------------------------------------------------------------------------------------------------------
// �ÓI�����o�ϐ��̏�����
//-------------------------------------------------------------------------------------------------------------
void CPicture::InitStaticMember(void)
{
	m_nNumPolyBlock = MYLIB_INT2_UNSET;		// �|���S����(���炷�傫���̐ݒ��2�{�ɂ���)
	m_size          = MYLIB_2DVECTOR_ZERO;	// �傫��

	if (m_pPen)
	{
		m_pPen->Uninit();
		delete m_pPen;
		m_pPen = nullptr;
	}
}

//-------------------------------------------------------------------------------------------------------------
// �}�g���b�N�X�̌v�Z
//-------------------------------------------------------------------------------------------------------------
void CPicture::MatrixCal(void)
{
	// �ϐ��錾
	D3DXMATRIX mtxRot, mtxTrans;

	// �}�g���b�N�X�̏�����
	m_trans.Identity();

	// �X�P�[���̔��f
	m_trans.mtxWorld.m[0][0] = m_trans.scal.x;
	m_trans.mtxWorld.m[1][1] = m_trans.scal.y;
	m_trans.mtxWorld.m[2][2] = m_trans.scal.z;

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_trans.rot.y, m_trans.rot.x, m_trans.rot.z);
	D3DXMatrixMultiply(&m_trans.mtxWorld, &m_trans.mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_trans.pos.x, m_trans.pos.y, m_trans.pos.z);
	D3DXMatrixMultiply(&m_trans.mtxWorld, &m_trans.mtxWorld, &mtxTrans);
}

//-------------------------------------------------------------------------------------------------------------
// ������
//-------------------------------------------------------------------------------------------------------------
HRESULT CPicture::Init()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ������
	MatrixCal();
	m_Flags.cValue = MASK_DISP;

	try
	{	// �e�N�X�`���̍쐬
		MakeTexture(pDevice);
		// ���_���̍쐬
		MakeVertex(pDevice);
	}
	catch (HRESULT rh)
	{// ��O��Ԃ�
		std::cout << "��O���������܂����B\n";
		return rh;
	}
	return S_OK;
}

//-------------------------------------------------------------------------------------------------------------
// �I��
//-------------------------------------------------------------------------------------------------------------
void CPicture::Uninit()
{
	// ���_�o�b�t�@�̎擾
	if (m_pVtexBuff != nullptr)
	{
		m_pVtexBuff->Release();
		m_pVtexBuff = nullptr;
	}
}

//-------------------------------------------------------------------------------------------------------------
// �X�V
//-------------------------------------------------------------------------------------------------------------
void CPicture::Update()
{
	// �G��`��
	PaintProc();

}

//-------------------------------------------------------------------------------------------------------------
// �`��
//-------------------------------------------------------------------------------------------------------------
void CPicture::Draw()
{
	//CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_COMMAND::RENDERER_WIRE_ON);
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_trans.mtxWorld);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtexBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
		0,					//�J�n����C���f�b�N�X(���_)
		2);					//�|���S���̖���

	//CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_COMMAND::RENDERER_WIRE_OFF);
}

//-------------------------------------------------------------------------------------------------------------
// ����
//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<CPicture> CPicture::Create(CONST D3DXVECTOR3 &pos, CONST D3DXVECTOR3 &rot)
{
	// �X�}�[�g�|�C���^�̐���
	std::shared_ptr<CPicture> pPicture = std::make_shared<CPicture>();
	// �ʒu�̐ݒ�
	pPicture->SetPos(pos);
	// �����̐ݒ�
	pPicture->SetRot(rot);
	// ������
	pPicture->Init();

	//Scene�ŊǗ�
	pPicture->SetObjType(OBJTYPE_MESHFIELD);
	pPicture->AddSharedList(pPicture);
	return pPicture;
}

//-------------------------------------------------------------------------------------------------------------
// �e�N�X�`���̍쐬
//-------------------------------------------------------------------------------------------------------------
void CPicture::MakeTexture(LPDIRECT3DDEVICE9 pDevice)
{
	if (FAILED(pDevice->CreateTexture(m_nNumPolyBlock.nX, m_nNumPolyBlock.nY, 1, 0, D3DFMT_A32B32G32R32F,
		D3DPOOL_MANAGED, &m_pTexture, NULL)))
	{
		throw E_FAIL;
	}
	// �e�N�X�`���J���[�̏�����
	InitTextureColor();
}

//-------------------------------------------------------------------------------------------------------------
// ���_���̍쐬
//-------------------------------------------------------------------------------------------------------------
void CPicture::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,									// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pVtexBuff,
		NULL)))
	{
		throw E_FAIL;
	}

	// �ϐ��錾
	VERTEX_3D *pVtx;								// ���_���̐ݒ�
	FLOAT2    sizeUpdate = MYLIB_2DVECTOR_ZERO;		// �X�V����傫��

	// ���_�f�[�^�͈̔̓��b�N���A���_�o�b�t�@�ւ̃|�C���^�擾
	m_pVtexBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �c�̎l�p�`�̌���
	for (int nCntVertical = 0; nCntVertical < 2; nCntVertical++)
	{
		// ���̎l�p�`�̌���
		for (int nCntHeng = 0; nCntHeng < 2; nCntHeng++)
		{
			// �ʒu�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(sizeUpdate.x, sizeUpdate.y, MYLIB_INT_UNSET);
			// �@���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			// �F�̐ݒ�
			pVtx[0].col = MYLIB_D3DXCOR_SET;
			// UV���̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(1.0f*nCntHeng, 1.0f*nCntVertical);
			// ���_�|�C���^�̃C���N�������g
			pVtx++;
			// �X�V����傫��X�������Z
			sizeUpdate.x += m_size.x;
		}
		// �X�V����傫��X���̏�����
		sizeUpdate.x = MYLIB_FLOAT_UNSET;
		// �X�V����傫��Y�������Z
		sizeUpdate.y -= m_size.y;
	}
	// ���_�f�[�^���A�����b�N
	m_pVtexBuff->Unlock();
}

//-------------------------------------------------------------------------------------------------------------
// �e�N�X�`���J���[�̏�����
//-------------------------------------------------------------------------------------------------------------
void CPicture::InitTextureColor(void)
{
	// �ϐ��錾
	D3DXCOLOR *    pData;			// �J���[�f�[�^�|�C���^
	D3DLOCKED_RECT LockRect;		// ���b�N�����e�N�X�`�����

	// �e�N�X�`���̃��b�N
	m_pTexture->LockRect(0, &LockRect, NULL, 0);

	// �f�[�^�̐擪����
	pData = (D3DXCOLOR*)LockRect.pBits;
	// �f�[�^�̐ݒ�
	for (int nY = 0; nY < m_nNumPolyBlock.nY; nY++)
	{
		for (int nX = 0; nX < m_nNumPolyBlock.nX; nX++)
		{
			*pData = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pData++;
		}
	}
	// �e�N�X�`���̃A�����b�N
	m_pTexture->UnlockRect(0);

}

//-------------------------------------------------------------------------------------------------------------
// 1�s���ǂ݂���
//-------------------------------------------------------------------------------------------------------------
void CPicture::ReadFromLine(CONST_STRING Line)
{
	INTEGER2    NumPoly = MYLIB_INT2_UNSET;
	D3DXVECTOR2 size    = MYLIB_2DVECTOR_ZERO;
	char aFileName[MYLIB_STRINGSIZE] = { '\0' };

	if (sscanf(Line, "NumPolygon = %d %d", &NumPoly.nX , &NumPoly.nY) == 2)
	{
		m_nNumPolyBlock = NumPoly;
	}
	else if (sscanf(Line, "Size = %f %f",&size.x, &size.y) == 2)
	{
		m_size = size;
	}
}

//-------------------------------------------------------------------------------------------------------------
// �h�鏈��
//-------------------------------------------------------------------------------------------------------------
void CPicture::PaintProc(void)
{
	// �G��̈ʒu�̎擾
	if (GetMousePosOnPicture() == false)
	{// �擾���s
		return;
	}
	// �J�v�Z���̐ݒ�
	m_pPen->SetCapsule();
	// �J�v�Z�����̎擾
	CAPSULE_2D *pCap = m_pPen->GetCapsule();
	// ���b�N�������
	D3DLOCKED_RECT LockRect;
	D3DXVECTOR2 PixelPos;
	// ���b�N
	m_pTexture->LockRect(0, &LockRect, NULL, 0);
	// �J���[�f�[�^�̎擾(�Ō��)
	D3DXCOLOR *pData = (D3DXCOLOR*)LockRect.pBits + m_nNumDataMax - 1;
	for (int nY = m_nNumPolyBlock.nY - 1; nY >= 0; nY--)
	{
		for (int nX = m_nNumPolyBlock.nX - 1; nX >= 0; nX--)
		{
			PixelPos.x = nX * m_PixelSize.x + m_PixelSizehalf.x;
			PixelPos.y = nY * m_PixelSize.y + m_PixelSizehalf.y;
			if (CMylibrary::calCapsuleSphere2D(*pCap, PixelPos))
			{
				pData->r = pData->g = pData->b = 0.0f;
			}
			pData--;
		}
	}
	// �A�����b�N
	m_pTexture->UnlockRect(0);
}

//-------------------------------------------------------------------------------------------------------------
// �G��̃}�E�X�ʒu�̎擾
//-------------------------------------------------------------------------------------------------------------
bool CPicture::GetMousePosOnPicture(void)
{
	// �O��̈ʒu�̐ݒ�
	m_pPen->SetPosOld();
	// �}�E�X�̎擾
	CMouse  *pMouse = CManager::GetMouse();
	// ���C�̎Z�o
	m_pPen->RayCalculation(pMouse);
	// �ʒu�̎Z�o
	m_pPen->PosCalculation(&m_trans.pos, &m_PlaneNor);
	// ��_�̎擾
	D3DXVECTOR2 *pCrossPos = m_pPen->GetPos();
	// �G��̈ʒu�̎擾
	*pCrossPos = { pCrossPos->x - m_trans.pos.x,m_trans.pos.y - pCrossPos->y };

	// �}�E�X�̍��N���b�N��������Ă��Ȃ���
	if (pMouse->GetPress(0) == false)
	{
		return false;
	}
	return true;
}