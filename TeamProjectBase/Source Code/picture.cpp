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

//-------------------------------------------------------------------------------------------------------------
//�}�N����`
//-------------------------------------------------------------------------------------------------------------
#define PICTURE_FILENAME  "data/TEXT/PictureInfo.txt"

//-------------------------------------------------------------------------------------------------------------
// �ÓI�����o�ϐ��̏�����
//-------------------------------------------------------------------------------------------------------------
INTEGER2    CPicture::m_nNumPolyBlock   = MYLIB_INT2_UNSET;		// �|���S����(���炷�傫���̐ݒ��2�{�ɂ���)
UINT        CPicture::m_nNumVertex      = MYLIB_INT_UNSET;		// �����_��
UINT        CPicture::m_nNumIndex       = MYLIB_INT_UNSET;		// ���C���f�b�N�X��
UINT        CPicture::m_nNumPolygon     = MYLIB_INT_UNSET;		// ���|���S����
FLOAT2      CPicture::m_size            = MYLIB_2DVECTOR_ZERO;	// �傫��
FLOAT2      CPicture::m_sizeShift       = MYLIB_2DVECTOR_ZERO;	// ���炷�傫��

//-------------------------------------------------------------------------------------------------------------
// ���b�V�����̃R���X�g���N�^
//-------------------------------------------------------------------------------------------------------------
CPicture::MESHINFO::MESHINFO()
{
	pVtexBuff = nullptr;								// ���_�o�b�t�@�̃|�C���^
	pIdxBuff = nullptr;								// �C���f�b�N�X�̃o�b�t�@�̃|�C���^
	pTexture = nullptr;								// �e�N�X�`���̃|�C���^}
}

//-------------------------------------------------------------------------------------------------------------
// ���b�V�����̃f�X�g���N�^
//-------------------------------------------------------------------------------------------------------------
CPicture::MESHINFO::~MESHINFO()
{
	// ���_�o�b�t�@�̊J��
	if (pVtexBuff != nullptr)
	{
		pVtexBuff->Release();
		pVtexBuff = nullptr;
	}
	// �C���f�b�N�X�o�b�t�@�̊J��
	if (pIdxBuff != nullptr)
	{
		pIdxBuff->Release();
		pIdxBuff = nullptr;
	}
}

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
		cout << "<<<<<<CPicture�̃t�@�C���ǂݍ��݂����s���܂����B>>>>>>\n";
#endif // _DEBUG
		return E_FAIL;
	}
	// �ǂ�����[���̎�
	if (m_nNumPolyBlock.OneIsZero() == true)
	{
#ifdef _DEBUG
		cout << "<<<<<<CPicture�̂ǂ��炩�̃|���S������0�ł����B>>>>>>\n";
#endif // _DEBUG
		return E_FAIL;
	}

	// ���炷�傫����ݒ�
	m_sizeShift = m_size / m_nNumPolyBlock;

	// �|���S������2�{�ɂ���
	m_nNumPolyBlock *= 2;
	
	// �����̐ݒ�
	m_nNumVertex  = (m_nNumPolyBlock.nX + 1) * (m_nNumPolyBlock.nY + 1);								// �����_��
	m_nNumIndex   = (m_nNumPolyBlock.nX * 2 + 2) * m_nNumPolyBlock.nY + ((m_nNumPolyBlock.nY - 1) * 2);	// ���C���f�b�N�X��
	m_nNumPolygon = (m_nNumPolyBlock.nX * m_nNumPolyBlock.nY) * 2 + (m_nNumPolyBlock.nY - 1) * 4;		// ���|���S����

	return S_OK;
}

//-------------------------------------------------------------------------------------------------------------
// �ÓI�����o�ϐ��̏�����
//-------------------------------------------------------------------------------------------------------------
void CPicture::InitStaticMember(void)
{
	m_nNumPolyBlock = MYLIB_INT2_UNSET;		// �|���S����(���炷�傫���̐ݒ��2�{�ɂ���)
	m_nNumVertex    = MYLIB_INT_UNSET;		// �����_��
	m_nNumIndex     = MYLIB_INT_UNSET;		// ���C���f�b�N�X��
	m_nNumPolygon   = MYLIB_INT_UNSET;		// ���|���S����
	m_size          = MYLIB_2DVECTOR_ZERO;	// �傫��
	m_sizeShift     = MYLIB_2DVECTOR_ZERO;	// ���炷�傫��
}

//-------------------------------------------------------------------------------------------------------------
// �}�g���b�N�X�̌v�Z
//-------------------------------------------------------------------------------------------------------------
void CPicture::MatrixCal(void)
{
	// �ϐ��錾
	D3DXMATRIX mtxRot, mtxTrans;

	// �}�g���b�N�X�̏�����
	m_mesh.trans.Identity();

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_mesh.trans.rot.y, m_mesh.trans.rot.x, m_mesh.trans.rot.z);
	D3DXMatrixMultiply(&m_mesh.trans.mtxWorld, &m_mesh.trans.mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_mesh.trans.pos.x, m_mesh.trans.pos.y, m_mesh.trans.pos.z);
	D3DXMatrixMultiply(&m_mesh.trans.mtxWorld, &m_mesh.trans.mtxWorld, &mtxTrans);
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
	m_Flags.cValue = 3;

	try
	{	// ���_���̍쐬
		MakeVertex(pDevice);
		// �C���f�b�N�X���̍쐬
		MakeIndex(pDevice);
	}
	catch (HRESULT rh)
	{// ��O��Ԃ�
		return rh;
	}
	return S_OK;
}

//-------------------------------------------------------------------------------------------------------------
// �I��
//-------------------------------------------------------------------------------------------------------------
void CPicture::Uninit()
{
	if (m_mesh.pVtexBuff != nullptr)
	{
		m_mesh.pVtexBuff->Release();
		m_mesh.pVtexBuff = nullptr;
	}
	if (m_mesh.pIdxBuff != nullptr)
	{
		m_mesh.pIdxBuff->Release();
		m_mesh.pIdxBuff = nullptr;
	}
}

//-------------------------------------------------------------------------------------------------------------
// �X�V
//-------------------------------------------------------------------------------------------------------------
void CPicture::Update()
{
}

//-------------------------------------------------------------------------------------------------------------
// �`��
//-------------------------------------------------------------------------------------------------------------
void CPicture::Draw()
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mesh.trans.mtxWorld);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_mesh.pVtexBuff, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetIndices(m_mesh.pIdxBuff);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_mesh.pTexture);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0,
		m_nNumVertex,			//�g�p���钸�_��
		0,						//���_�̓ǂݎ����J�n����ʒu
		m_nNumPolygon);			//�|���S���̖���
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
	return pPicture;
}

//-------------------------------------------------------------------------------------------------------------
// ���_���̍쐬
//-------------------------------------------------------------------------------------------------------------
void CPicture::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * m_nNumVertex,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,									// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&m_mesh.pVtexBuff,
		NULL)))
	{
		throw E_FAIL;
	}

	// �ϐ��錾
	VERTEX_3D *pVtx;								// ���_���̐ݒ�
	FLOAT2    sizeUpdate = MYLIB_2DVECTOR_ZERO;		// �X�V����傫��

	// ���_�f�[�^�͈̔̓��b�N���A���_�o�b�t�@�ւ̃|�C���^�擾
	m_mesh.pVtexBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �c�̎l�p�`�̌���
	for (int nCntVertical = 0; nCntVertical < m_nNumPolyBlock.nY + 1; nCntVertical++)
	{
		// ���̎l�p�`�̌���
		for (int nCntHeng = 0; nCntHeng < m_nNumPolyBlock.nX + 1; nCntHeng++)
		{
			// �ʒu�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(sizeUpdate.x, sizeUpdate.y, MYLIB_INT_UNSET);
			// �@���̐ݒ�
			pVtx[0].nor = MYLIB_VEC3_ZONE;
			// �F�̐ݒ�
			pVtx[0].col = MYLIB_D3DXCOR_SET;
			// UV���̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(1.0f*nCntHeng, 1.0f*nCntVertical);
			// ���_�|�C���^�̃C���N�������g
			pVtx++;
			// �X�V����傫��X�������Z
			if (nCntHeng % 2 == 0)sizeUpdate.x += m_sizeShift.x;
		}
		// �X�V����傫��X���̏�����
		sizeUpdate.x = MYLIB_FLOAT_UNSET;
		// �X�V����傫��Y�������Z
		if (nCntVertical % 2 == 0)sizeUpdate.y += m_sizeShift.y;
	}
	// ���_�f�[�^���A�����b�N
	m_mesh.pVtexBuff->Unlock();
}

//-------------------------------------------------------------------------------------------------------------
// �C���f�b�N�X���̍쐬
//-------------------------------------------------------------------------------------------------------------
void CPicture::MakeIndex(LPDIRECT3DDEVICE9 pDevice)
{
	// �C���f�b�N�X�o�b�t�@�̐���
	if (FAILED(pDevice->CreateIndexBuffer(
		sizeof(WORD) * m_nNumIndex,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_mesh.pIdxBuff,
		NULL)))
	{
		throw E_FAIL;
	}

	// �C���f�b�N�X�f�[�^�ւ̃|�C���^
	WORD *pIdx;

	// �C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�o�b�t�@�̃|�C���^�擾
	m_mesh.pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	// �C���f�b�N�X�̐ݒ�
	// ���s�̌�
	for (int nCntVertical = 0; nCntVertical < m_nNumPolyBlock.nY ; nCntVertical++)
	{
		// �ŏ������͂���Ȃ��悤�ɂ��邽��
		if (nCntVertical > 0)
		{
			// �k�ރ|���S����
			pIdx[0] = (nCntVertical*(m_nNumPolyBlock.nX + 1) + m_nNumPolyBlock.nX + 1);
			pIdx++;
		}
		// ���̌�
		for (int nCntInd = 0; nCntInd < m_nNumPolyBlock.nX + 1; nCntInd++)
		{
			// �k�ރ|���S������������
			pIdx[0] = nCntVertical*(m_nNumPolyBlock.nX + 1) + nCntInd + m_nNumPolyBlock.nX + 1;
			pIdx[1] = nCntVertical*(m_nNumPolyBlock.nX + 1) + nCntInd;
			pIdx += 2;
		}
		// �Ōゾ������Ȃ��悤�ɂ���
		if (nCntVertical < m_nNumPolyBlock.nY - 1)
		{
			// �k�ރ|���S����
			pIdx[0] = (nCntVertical*(m_nNumPolyBlock.nX + 1) + m_nNumPolyBlock.nX);
			pIdx++;
		}
	}
	// �C���f�b�N�X�o�b�t�@���A�����b�N
	m_mesh.pIdxBuff->Unlock();
}

//-------------------------------------------------------------------------------------------------------------
// 1�s���ǂ݂���
//-------------------------------------------------------------------------------------------------------------
void CPicture::ReadFromLine(CONST_STRING Line)
{
	INTEGER2    NumPoly = MYLIB_INT2_UNSET;
	D3DXVECTOR2 size    = MYLIB_2DVECTOR_ZERO;
	if (sscanf(Line, "NumPolygon = %d %d", &NumPoly.nX , &NumPoly.nY) == 2)
	{
		m_nNumPolyBlock = NumPoly;
	}
	else if (sscanf(Line, "Size = %f %f",&size.x, &size.y) == 2)
	{
		m_size = size;
	}
}
