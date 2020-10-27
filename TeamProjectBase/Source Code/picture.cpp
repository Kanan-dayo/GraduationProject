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
INTEGER2    CPicture::m_nNumPolyBlock   = MYLIB_INT2_UNSET;		// �|���S����(���炷�傫���̐ݒ��2�{�ɂ���)
FLOAT2      CPicture::m_size            = MYLIB_2DVECTOR_ZERO;	// �傫��
D3DXMATRIX* CPicture::m_pMtxView = nullptr;
D3DXMATRIX* CPicture::m_pMtxProj = nullptr;
INTEGER2    CPicture::m_MousePos = MYLIB_INT2_UNSET;
INTEGER2    CPicture::m_ScreenPos = INTEGER2(SCREEN_WIDTH, SCREEN_HEIGHT);
D3DXVECTOR3 CPicture::m_PlaneNor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
D3DXVECTOR2 CPicture::m_PixelSize = MYLIB_VEC2_UNSET;

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
	CCamera *pCamera = CManager::GetRenderer()->GetCamera();
	m_pMtxView = pCamera->GetMtxView();
	m_pMtxProj = pCamera->GetMtxProjection();

	m_PixelSize = m_size / m_nNumPolyBlock;
	return S_OK;
}

//-------------------------------------------------------------------------------------------------------------
// �ÓI�����o�ϐ��̏�����
//-------------------------------------------------------------------------------------------------------------
void CPicture::InitStaticMember(void)
{
	m_nNumPolyBlock = MYLIB_INT2_UNSET;		// �|���S����(���炷�傫���̐ݒ��2�{�ɂ���)
	m_size          = MYLIB_2DVECTOR_ZERO;	// �傫��
	m_pMtxView = nullptr;
	m_pMtxProj = nullptr;
}

//-------------------------------------------------------------------------------------------------------------
// �}�g���b�N�X�̌v�Z
//-------------------------------------------------------------------------------------------------------------
void CPicture::MatrixCal(void)
{
	// �ϐ��錾
	D3DXMATRIX mtxRot, mtxTrans;

	// �}�g���b�N�X�̏�����
	trans.Identity();

	// �X�P�[���̔��f
	trans.mtxWorld.m[0][0] = trans.scal.x;
	trans.mtxWorld.m[1][1] = trans.scal.y;
	trans.mtxWorld.m[2][2] = trans.scal.z;

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, trans.rot.y, trans.rot.x, trans.rot.z);
	D3DXMatrixMultiply(&trans.mtxWorld, &trans.mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, trans.pos.x, trans.pos.y, trans.pos.z);
	D3DXMatrixMultiply(&trans.mtxWorld, &trans.mtxWorld, &mtxTrans);
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
	if (pVtexBuff != nullptr)
	{
		pVtexBuff->Release();
		pVtexBuff = nullptr;
	}
}

//-------------------------------------------------------------------------------------------------------------
// �X�V
//-------------------------------------------------------------------------------------------------------------
void CPicture::Update()
{
	// �ϐ��錾
	CMouse  *pMouse = CManager::GetMouse();
	INTEGER2 MousePos(pMouse->GetMousePoint().x, pMouse->GetMousePoint().y);
	FLOAT3 StartPos;
	FLOAT3 EndPos;
	VEC3 Ray;
	CMylibrary::CalScreenRay(&Ray, &StartPos, &EndPos,&MousePos, &m_ScreenPos, (MATRIX*)m_pMtxView,(MATRIX*)m_pMtxProj);
	D3DXVECTOR3 pos;
	CMylibrary::CalIntersectionPointToPlaneAndLine(&pos, &trans.pos, &m_PlaneNor, &StartPos, &Ray);

	if (pMouse->GetPress(0))
	{

#ifdef _DEBUG
		CDebugProc::Print(CDebugProc::PLACE_LEFT, "�}�E�X�̃��[���h���W == [%.3f][%.3f][%.3f]\n", pos.x, pos.y, pos.z);
#endif

		if (trans.pos.x < pos.x && pos.x < trans.pos.x + m_size.x &&
			trans.pos.y > pos.y && pos.y > trans.pos.y - m_size.y)
		{
#ifdef _DEBUG
			CDebugProc::Print(CDebugProc::PLACE_LEFT, "X��Y���ɓ����Ă���\n");
#endif
			D3DXVECTOR2 PicturePos = { pos.x - trans.pos.x,trans.pos.y - pos.y };

			CDebugProc::Print(CDebugProc::PLACE_LEFT, "�}�E�X�̊G��̍��W == [%.3f][%.3f]\n", PicturePos.x, PicturePos.y);

			float fNumX = PicturePos.x / m_PixelSize.x;
			float fNumY = PicturePos.y / m_PixelSize.y;
			int nNumX = (int)fNumX;
			int nNumY = (int)fNumY;

			D3DXCOLOR *data;
			D3DLOCKED_RECT LockRect;
			m_pTexture->LockRect(0, &LockRect, NULL, 0);
			data = (D3DXCOLOR*)LockRect.pBits;
			for (int nY = 0; nY < m_nNumPolyBlock.nY; nY++)
			{
				for (int nX = 0; nX < m_nNumPolyBlock.nX; nX++)
				{
					D3DXVECTOR2 PixelPos = {
						nX * m_PixelSize.x + m_PixelSize.x * 0.5f,
						nY * m_PixelSize.y + m_PixelSize.y * 0.5f };
					D3DXVECTOR2 Dist = PixelPos - PicturePos;
					float fSize = 20.0f;
					if (Dist.x * Dist.x + Dist.y * Dist.y <= fSize)
					{
						*data = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
					}
					data++;
				}
			}
			m_pTexture->UnlockRect(0);
		}
	}
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
	pDevice->SetTransform(D3DTS_WORLD, &trans.mtxWorld);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, pVtexBuff, 0, sizeof(VERTEX_3D));

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
#if 1
	if (FAILED(pDevice->CreateTexture(m_nNumPolyBlock.nX, m_nNumPolyBlock.nY, 1, 0, D3DFMT_A32B32G32R32F,
		D3DPOOL_MANAGED, &m_pTexture, NULL)))
	{
		throw E_FAIL;
	}
#else
	if (D3DXCreateTextureFromFile(pDevice, m_TextureFile.Get(), &m_pTexture) != S_OK)
	{
		throw E_FAIL;
	}
#endif
	D3DXCOLOR *data;
	//RECT           Rect;
	D3DLOCKED_RECT LockRect;
	HRESULT hr = m_pTexture->LockRect(0, &LockRect, NULL, 0);
	data = (D3DXCOLOR*)LockRect.pBits;
	for (int nY = 0; nY < m_nNumPolyBlock.nY; nY++)
	{
		for (int nX = 0; nX < m_nNumPolyBlock.nX; nX++)
		{
			if (nX == 0 || nX == m_nNumPolyBlock.nX - 1 ||
				nX == 0 || nY == m_nNumPolyBlock.nY - 1)
			{
				*data = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			}
			else
			{
				*data = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
			data++;
		}
	}
	m_pTexture->UnlockRect(0);
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
		&pVtexBuff,
		NULL)))
	{
		throw E_FAIL;
	}

	// �ϐ��錾
	VERTEX_3D *pVtx;								// ���_���̐ݒ�
	FLOAT2    sizeUpdate = MYLIB_2DVECTOR_ZERO;		// �X�V����傫��

	// ���_�f�[�^�͈̔̓��b�N���A���_�o�b�t�@�ւ̃|�C���^�擾
	pVtexBuff->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtexBuff->Unlock();
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
