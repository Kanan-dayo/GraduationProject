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
#define PICTURE_FILENAME		"data/TEXT/PictureInfo.txt"
#define PICTURE_WRITINGPASS		"data/SAVEDATA/PictureTextures/"
#define PICTURE_WRITINGNAME		"PicTex.txt"

//-------------------------------------------------------------------------------------------------------------
// �ÓI�����o�ϐ��̏�����
//-------------------------------------------------------------------------------------------------------------
INTEGER2      CPicture::m_nNumPixelBlock  = MYLIB_INT2_UNSET;						// �s�N�Z����
FLOAT2        CPicture::m_size            = MYLIB_2DVECTOR_ZERO;					// �傫��
D3DXVECTOR3   CPicture::m_PlaneNor        = D3DXVECTOR3(0.0f, 0.0f, -1.0f);			// ���ʂ̖@��
D3DXVECTOR2   CPicture::m_PixelSize       = MYLIB_VEC2_UNSET;						// �s�N�Z���T�C�Y
UINT          CPicture::m_nNumDataMax     = MYLIB_INT_UNSET;						// �ő�f�[�^���ő�f�[�^��
CPaintingPen* CPicture::m_pPen            = nullptr;								// �y���̃|�C���^
D3DXVECTOR2   CPicture::m_PixelSizehalf   = MYLIB_VEC2_UNSET;						// �s�N�Z���T�C�Y�̔���
D3DXVECTOR2*  CPicture::m_pPixelPos       = nullptr;								// �s�N�Z���ʒu�̃|�C���^
UINT          CPicture::m_nNumMakeFile    = MYLIB_INT_UNSET;						// �t�@�C�����������
CString       CPicture::m_WriteToFile;												// �������ݐ�̃@�C����

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
	if (m_nNumPixelBlock.OneIsZero() == true)
	{
#ifdef _DEBUG
		std::cout << "<<<<<<CPicture�̂ǂ��炩�̃|���S������0�ł����B>>>>>>\n";
#endif // _DEBUG
		return E_FAIL;
	}
	// �ÓI�����o�̏�����
	InitStaticMember();
	return S_OK;
}

//-------------------------------------------------------------------------------------------------------------
// �ÓI�����o�̏�����
//-------------------------------------------------------------------------------------------------------------
void CPicture::InitStaticMember(void)
{
	m_PixelSize = m_size / m_nNumPixelBlock;
	m_PixelSizehalf = m_PixelSize * MYLIB_HALF_SIZE;
	m_nNumDataMax = m_nNumPixelBlock.nY * m_nNumPixelBlock.nX;
	m_nNumMakeFile = MYLIB_INT_UNSET;
	// �s�N�Z���ʒu�̊J��
	ReleasePixelPos();
	// �s�N�Z���ʒu�̐���
	CreatePixelPos();
	// �y���̊J��
	ReleasePen();
	// �y���̐���
	m_pPen = CPaintingPen::Create();
}

//-------------------------------------------------------------------------------------------------------------
// �ÓI�����o�ϐ��̏I��
//-------------------------------------------------------------------------------------------------------------
void CPicture::UninitStaticMember(void)
{
	// �y���̊J��
	ReleasePen();
	// �s�N�Z���ʒu�̊J��
	ReleasePixelPos();
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
// �f�X�g���N�^
//-------------------------------------------------------------------------------------------------------------
inline CPicture::~CPicture()
{
	this->Writing();
	// ���_�o�b�t�@�̎擾
	if (m_pVtexBuff != nullptr)
	{
		m_pVtexBuff->Release();
		m_pVtexBuff = nullptr;
	}
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
// �X�V
//-------------------------------------------------------------------------------------------------------------
void CPicture::Update()
{
	// �y���̍X�V
	m_pPen->Update();
	// �G��`��
	PaintProc();
}

//-------------------------------------------------------------------------------------------------------------
// �`��
//-------------------------------------------------------------------------------------------------------------
void CPicture::Draw()
{
	if (Mybfunc_bit_comp(m_Flags.cValue, CPicture::FLAG_DISP))
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
}

//-------------------------------------------------------------------------------------------------------------
// ����
//-------------------------------------------------------------------------------------------------------------
std::shared_ptr<CPicture> CPicture::Create(CONST D3DXVECTOR3 &pos, CONST D3DXVECTOR3 &rot, CONST MODE mode)
{
	// �X�}�[�g�|�C���^�̐���
	std::shared_ptr<CPicture> pPicture = std::make_shared<CPicture>();

	// ���[�h�̐ݒ�
	pPicture->SetMode(mode);
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
	if (FAILED(pDevice->CreateTexture(m_nNumPixelBlock.nX, m_nNumPixelBlock.nY, 1, 0, D3DFMT_A32B32G32R32F,
		D3DPOOL_MANAGED, &m_pTexture, NULL)))
	{
		throw E_FAIL;
	}
	// �e�N�X�`���J���[�̏�����
	//InitTextureColor();

	Reading(m_WriteToFile);
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
	for (UINT nCntPixel = 0; nCntPixel < m_nNumDataMax; nCntPixel++)
	{
		*pData = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pData++;
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
	// �|���S����
	if (sscanf(Line, "NumPolygon = %d %d", &NumPoly.nX , &NumPoly.nY) == 2)
	{
		m_nNumPixelBlock = NumPoly;
	}
	// �|���S���T�C�Y
	else if (sscanf(Line, "Size = %f %f",&size.x, &size.y) == 2)
	{
		m_size = size;
	}
	// �������ݐ�̃t�@�C��
	else if (sscanf(Line, "WriteToFile = %s", aFileName) == 1)
	{
		m_WriteToFile = aFileName;
	}
}

//-------------------------------------------------------------------------------------------------------------
// �s�N�Z���ʒu�̐���
//-------------------------------------------------------------------------------------------------------------
void CPicture::CreatePixelPos(void)
{
	// �ő�f�[�^����0�ȉ��̎�
	if (m_nNumDataMax <= MYLIB_INT_UNSET)
	{// null��ݒ�
		m_pPixelPos = nullptr;
	}

	// �s�N�Z���ʒu�̐���
	m_pPixelPos = new D3DXVECTOR2[m_nNumDataMax];

	// �|�C���^�n��
	D3DXVECTOR2* pPixelPos = m_pPixelPos;

	// �ʒu�̐ݒ�
	for (int nY = 0; nY < m_nNumPixelBlock.nY; nY++) {
		for (int nX = 0; nX < m_nNumPixelBlock.nX; nX++) {
			pPixelPos->x = nX * m_PixelSize.x + m_PixelSizehalf.x;
			pPixelPos->y = nY * m_PixelSize.y + m_PixelSizehalf.y;
			pPixelPos++;
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
// �s�N�Z���ʒu�̊J��
//-------------------------------------------------------------------------------------------------------------
void CPicture::ReleasePixelPos(void)
{
	if (m_pPixelPos)
	{
		delete m_pPixelPos;
		m_pPixelPos = nullptr;
	}
}

//-------------------------------------------------------------------------------------------------------------
// �y���̊J��
//-------------------------------------------------------------------------------------------------------------
void CPicture::ReleasePen(void)
{
	if (m_pPen)
	{
		m_pPen->Uninit();
		delete m_pPen;
		m_pPen = nullptr;
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
	CAPSULE_2D *pCap = m_pPen->GetCapsule();					// �J�v�Z�����̎擾

	// ���b�N�������
	D3DLOCKED_RECT LockRect;
	// ���b�N
	m_pTexture->LockRect(0, &LockRect, NULL, 0);
	// �J���[�f�[�^�̎擾
	D3DXCOLOR *pData = (D3DXCOLOR*)LockRect.pBits;

	D3DXVECTOR2 *pPixelPos = m_pPixelPos;						// �s�N�Z���ʒu�̎擾

	const float fRadius = pCap->fRadius * pCap->fRadius;		// ��r�p�̔��a���Z�o
	const float fSegLeng = pCap->Segment.vec.Length();			// �J�v�Z���̐����̒������擾

	int nPenMode = m_pPen->GetMode();							// ���[�h�̎擾

	// �����̒��������e�ȉ��̎�
	if (fSegLeng <= MYLIB_OX_EPSILON)
	{
		for (UINT nCntPixel = 0; nCntPixel < m_nNumDataMax; nCntPixel++, pPixelPos++, pData++)
		{
			// (���̎� == 1�A���̎� == 0) == ���[�h(�u���V == 0�A�����S�� == 1)�̎�
			if ((pData->r > 0.5f) == nPenMode)
			{// �������X�L�b�v����
				continue;
			}
			// �ʒu�̍������Z�o
			D3DXVECTOR2 DiffPos = pCap->Segment.pos - *pPixelPos;
			// �������r
			if (DiffPos.x * DiffPos.x + DiffPos.y * DiffPos.y <= fRadius)
			{// �y���ŐF��h��
				m_pPen->PaintCol(pData);
			}
		}
	}
	else
	{
		// �����̏I�[���擾
		CONST FLOAT2 SegEndPoint = pCap->Segment.GetEndPoint();

		for (UINT nCntPixel = 0; nCntPixel < m_nNumDataMax; nCntPixel++, pPixelPos++, pData++)
		{
			// (���̎� == 1�A���̎� == 0) == ���[�h(�u���V == 0�A�����S�� == 1)�̎�
			if ((pData->r > 0.5f) == nPenMode)
			{// �������X�L�b�v����
				continue;
			}
			// �s�p����Ȃ���
			if (CMylibrary::IsSharpAngle(*pPixelPos, pCap->Segment.pos, SegEndPoint) == false)
			{// �ʒu�̍������Z�o
				D3DXVECTOR2 DiffPos = pCap->Segment.pos - *pPixelPos;
				// �������r
				if (DiffPos.x * DiffPos.x + DiffPos.y * DiffPos.y <= fRadius)
				{// �y���ŐF��h��
					m_pPen->PaintCol(pData);
				}
			}
			// �s�p����Ȃ���
			else if (CMylibrary::IsSharpAngle(*pPixelPos, SegEndPoint, pCap->Segment.pos) == false)
			{// �ʒu�̍������Z�o
				D3DXVECTOR2 DiffPos = SegEndPoint - *pPixelPos;
				// �������r
				if (DiffPos.x * DiffPos.x + DiffPos.y * DiffPos.y <= fRadius)
				{// �y���ŐF��h��
					m_pPen->PaintCol(pData);
				}
			}
			else
			{// �����Ɠ_�̒������v�Z
				float fLegth = pCap->Segment.vec.Cross(*pPixelPos - pCap->Segment.pos) / fSegLeng;
				// �������r
				if (fLegth <= pCap->fRadius && fLegth >= -pCap->fRadius)
				{// �y���ŐF��h��
					m_pPen->PaintCol(pData);
				}
			}
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
	// �ʒu�̎Z�o
	m_pPen->PosCalculation(&m_trans.pos, &m_PlaneNor);
	// ��_�̎擾
	D3DXVECTOR2 *pCrossPos = m_pPen->GetPos();
	// �G��̈ʒu�̎擾
	*pCrossPos = { pCrossPos->x - m_trans.pos.x,m_trans.pos.y - pCrossPos->y };
	// �}�E�X�̍��N���b�N��������Ă��鎞
	return pMouse->GetPress(0);
}

//-------------------------------------------------------------------------------------------------------------
// ��������
//-------------------------------------------------------------------------------------------------------------
void CPicture::Writing(void)
{
	// �t�@�C�����J��
	FILE *pFile = fopen(m_WriteToFile.Get(), "w");
	// null�`�F�b�N
	if (pFile == NULL)
	{// �J���Ȃ������Ƃ�
		return;
	}

	// ���b�N�������
	D3DLOCKED_RECT LockRect;

	// ���b�N
	m_pTexture->LockRect(0, &LockRect, NULL, 0);

	D3DXCOLOR *pData = (D3DXCOLOR*)LockRect.pBits;				// �J���[�f�[�^�̎擾

	// �ő吔�̏�������
	fprintf(pFile, "max = %d\n", m_nNumDataMax);

	// �J���[�t���O�̏�������
	for (UINT nCntPixel = 0; nCntPixel < m_nNumDataMax; nCntPixel++, pData++)
	{
		fprintf(pFile, "%d%s", (pData->r > 0.5f) ? 1 : 0, ((nCntPixel % 128) == 127) ? "\n" : "");
	}

	// �A�����b�N
	m_pTexture->UnlockRect(0);

	// �t�@�C�������
	fclose(pFile);
}

//-------------------------------------------------------------------------------------------------------------
// �ǂݍ���
//-------------------------------------------------------------------------------------------------------------
void CPicture::Reading(CString & file)
{
	// �f�[�^�i�[
	MyVector<bool> bData;
	// �t�@�C���ǂݍ���
	if (CLoadFile::ReadLineByLineFromFile(file.Get(), TexterReadFromLine, &bData) != CLoadFile::LR_SUCCESS)
	{
		std::cout << "�ǂݍ��ݎ��s���܂����B\n";
	}

	// ���b�N�������
	D3DLOCKED_RECT LockRect;
	// ���b�N
	m_pTexture->LockRect(0, &LockRect, NULL, 0);

	D3DXCOLOR *pData = (D3DXCOLOR*)LockRect.pBits;				// �J���[�f�[�^�̎擾
	// �ǂݍ��݃T�C�Y�̎擾
	UINT nReadSize = bData.size();
	// �ő吔���[�v
	for (UINT nCntPixel = 0; nCntPixel < m_nNumDataMax; nCntPixel++, pData++)
	{
		// �ǂݍ��݃T�C�Y���J�E���g���傫���Ƃ�
		if (nReadSize <= nCntPixel)
		{// ���[�v�𔲂���
			break;
		}
		// �f�[�^�t���O�������Ă��鎞�A���ɂ���B����ȊO�̎��A���ɂ���B
		*pData = (bData[nCntPixel] == true) ? D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) : D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	}

	// �A�����b�N
	m_pTexture->UnlockRect(0);
	// �N���A
	bData.clear();
}

//-------------------------------------------------------------------------------------------------------------
// �e�N�X�`������1�s�������ǂݎ��
//-------------------------------------------------------------------------------------------------------------
void CPicture::TexterReadFromLine(CONST_STRING cnpLine, void*pOut)
{
	// �ϐ��錾
	char aData[129]       = {};							// ������f�[�^
	int nData             = MYLIB_INT_UNSET;			// INT�^�f�[�^
	MyVector<bool> *pData = (MyVector<bool> *)pOut;		// �L���X�g�f�[�^���擾

	// �f�[�^�ő吔
	if (sscanf(cnpLine, "max = %d", &nData) == 1)
	{// ���e�ʂ�ύX
		pData->reserve(nData);
	}
	// �t���O���𕶎���Ƃ��Ď擾
	else if (sscanf(cnpLine, "%s",&aData[0]) == 1)
	{
		for (int nCnt = 0; nCnt < 128; nCnt++)
		{// ���ɒǉ����Ă���
			pData->push_back(aData[nCnt] == '1');
		}
	}
}
