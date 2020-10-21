//------------------------------------------------------------------------------
//
//�V�[��3D����  [scene3D.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "scene3D.h"
#include "renderer.h"
#include "manager.h"

//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------
int CScene3D::m_nNumScene3D = 0;
//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CScene3D::CScene3D()
{
	//������
	m_bBillBoard = false;

	//�������Z
	m_nNumScene3D++;
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CScene3D::~CScene3D()
{
	//�������Z
	m_nNumScene3D--;
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CScene3D::Init()
{
	MakeVertex();

	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CScene3D::Uninit()
{

}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CScene3D::Update()
{

	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//���_�̍��W
	//X�����ɂ��ă|���S���𐶐����邱��
	pVtx[0].pos = D3DXVECTOR3(-GetSize().x * 0.5f, +GetSize().y * 0.5f, +GetSize().z * 0.5f);
	pVtx[1].pos = D3DXVECTOR3(+GetSize().x * 0.5f, +GetSize().y * 0.5f, +GetSize().z * 0.5f);
	pVtx[2].pos = D3DXVECTOR3(-GetSize().x * 0.5f, -GetSize().y * 0.5f, -GetSize().z * 0.5f);
	pVtx[3].pos = D3DXVECTOR3(+GetSize().x * 0.5f, -GetSize().y * 0.5f, -GetSize().z * 0.5f);

	//���_�̐F
	pVtx[0].col = GetColor();
	pVtx[1].col = GetColor();
	pVtx[2].col = GetColor();
	pVtx[3].col = GetColor();

	//���_�f�[�^���A�����b�N
	GetVtxBuff()->Unlock();

}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CScene3D::Draw()
{
	//���[���h�}�g���b�N�X�v�Z
	CHossoLibrary::CalcMatrix(GetMtxWorldPtr(), GetPos(), GetRot(), GetScale());

	//�r���{�[�h���ǂ���
	if (m_bBillBoard)
	{
		//�r���{�[�h�ݒ�
		CHossoLibrary::SetBillboard(GetMtxWorldPtr());
	}
	//���C�e�B���O���Ȃ���
	if (!GetLighting())
	{
		//���C�e�B���Ooff
		CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_LIGHTING_OFF);
	}

	//nullcheck
	if (GetParentMtxPtr())
	{
		//�e�̃}�g���b�N�X���|�����킹��
		*GetMtxWorldPtr() *= *GetParentMtxPtr();
	}

	//�|���S���`��
	DrawPolygon();

	//���C�e�B���O�ݒ�����ɖ߂�
	CHossoLibrary::CheckLighting();
}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CScene3D::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}
//------------------------------------------------------------------------------
//�ݒ菈��
//------------------------------------------------------------------------------
void CScene3D::DrawSettingMtx(D3DXMATRIX const &Mtx)
{
	//������mtx�𗘗p
	SetMtxWorld(Mtx);

	//�|���S���`��
	DrawPolygon();
}
//------------------------------------------------------------------------------
//�ݒ菈��
//------------------------------------------------------------------------------
void CScene3D::DrawPolygon()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD,GetMtxWorldPtr());

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, GetTexture());

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
							0,					//�J�n����C���f�b�N�X(���_)
							2);					//�|���S���̖���

}

//------------------------------------------------------------------------------
//�e�N�X�`���A�j���[�V�����̍X�V
//------------------------------------------------------------------------------
void CScene3D::SetAnimation(D3DXVECTOR2 const UV, D3DXVECTOR2 const size)
{
	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(UV.x, UV.y);
	pVtx[1].tex = D3DXVECTOR2(UV.x + size.x, UV.y);
	pVtx[2].tex = D3DXVECTOR2(UV.x, UV.y + size.y);
	pVtx[3].tex = D3DXVECTOR2(UV.x + size.x, UV.y + size.y);

	//���_�f�[�^���A�����b�N
	GetVtxBuff()->Unlock();
}

//------------------------------------------------------------------------------
//���_�o�b�t�@����
//------------------------------------------------------------------------------
HRESULT CScene3D::MakeVertex()
{

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;	//���_�o�b�t�@

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,	//�m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,			//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&pVtxBuff,
		NULL)))
	{
		//���_�o�b�t�@�쐬���s
		return E_FAIL;
	}

	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�̍��W
	//X�����ɂ��ă|���S���𐶐����邱��
	pVtx[0].pos = D3DXVECTOR3(-GetSize().x * 0.5f, +GetSize().y * 0.5f, +GetSize().z * 0.5f);
	pVtx[1].pos = D3DXVECTOR3(+GetSize().x * 0.5f, +GetSize().y * 0.5f, +GetSize().z * 0.5f);
	pVtx[2].pos = D3DXVECTOR3(-GetSize().x * 0.5f, -GetSize().y * 0.5f, -GetSize().z * 0.5f);
	pVtx[3].pos = D3DXVECTOR3(+GetSize().x * 0.5f, -GetSize().y * 0.5f, -GetSize().z * 0.5f);

	//���_�̓������W
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�̐F
	pVtx[0].col = GetColor();
	pVtx[1].col = GetColor();
	pVtx[2].col = GetColor();
	pVtx[3].col = GetColor();

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�f�[�^���A�����b�N
	pVtxBuff->Unlock();

	//���_�o�b�t�@�ݒ�
	BindVtxBuff(pVtxBuff);

	return S_OK;

}
