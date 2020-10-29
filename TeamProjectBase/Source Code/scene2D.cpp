//------------------------------------------------------------------------------
//
//�V�[��2D����  [scene2D.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "keyboard.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------
int CScene2D::m_nNumScene2D = 0;

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CScene2D::CScene2D()
{
	//������
	m_fAngle = 0.0f;
	m_fLength = 0.0f;

	//�������Z
	m_nNumScene2D++;
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CScene2D::~CScene2D()
{
	//�������Z
	m_nNumScene2D--;
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CScene2D::Init()
{
	MakeVertex();

	return S_OK;
}

//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CScene2D::Update()
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//nullcheck
	if (!GetVtxBuff())
	{
		return;
	}

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//���_�̍��W
	pVtx[0].pos.x = GetPos().x + sinf(-D3DX_PI + m_fAngle + GetRot().z)	* m_fLength;
	pVtx[0].pos.y = GetPos().y + cosf(-D3DX_PI + m_fAngle + GetRot().z)	* m_fLength;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = GetPos().x + sinf(D3DX_PI - m_fAngle + GetRot().z)	* m_fLength;
	pVtx[1].pos.y = GetPos().y + cosf(D3DX_PI - m_fAngle + GetRot().z)	* m_fLength;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = GetPos().x + sinf(-m_fAngle + GetRot().z)	* m_fLength;
	pVtx[2].pos.y = GetPos().y + cosf(-m_fAngle + GetRot().z)	* m_fLength;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = GetPos().x + sinf(m_fAngle + GetRot().z)	* m_fLength;
	pVtx[3].pos.y = GetPos().y + cosf(m_fAngle + GetRot().z)	* m_fLength;
	pVtx[3].pos.z = 0.0f;

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
void CScene2D::Draw()
{
	//�ʂ����ǂ���
	if (GetDisp())
	{
		//�f�o�C�X�擾
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, GetTexture());

		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
								0,					//�J�n����C���f�b�N�X(���_)
								2);					//�|���S���̖���
	}
}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CScene2D::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}

//------------------------------------------------------------------------------
//�e�N�X�`���A�j���[�V�����̍X�V
//------------------------------------------------------------------------------
void CScene2D::SetAnimation(D3DXVECTOR2 UV, D3DXVECTOR2 size)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

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
//���_�o�b�t�@�쐬
//------------------------------------------------------------------------------
HRESULT CScene2D::MakeVertex()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;	//���_�o�b�t�@

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	//�m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&pVtxBuff,
		NULL)))
	{
		//���_�o�b�t�@�쐬���s
		return E_FAIL;
	}

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�̍��W
	pVtx[0].pos.x = GetPos().x + sinf(-D3DX_PI + m_fAngle + GetRot().z)	* m_fLength;
	pVtx[0].pos.y = GetPos().y + cosf(-D3DX_PI + m_fAngle + GetRot().z)	* m_fLength;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = GetPos().x + sinf(D3DX_PI - m_fAngle + GetRot().z)	* m_fLength;
	pVtx[1].pos.y = GetPos().y + cosf(D3DX_PI - m_fAngle + GetRot().z)	* m_fLength;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = GetPos().x + sinf(-m_fAngle + GetRot().z)	* m_fLength;
	pVtx[2].pos.y = GetPos().y + cosf(-m_fAngle + GetRot().z)	* m_fLength;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = GetPos().x + sinf(m_fAngle + GetRot().z)	* m_fLength;
	pVtx[3].pos.y = GetPos().y + cosf(m_fAngle + GetRot().z)	* m_fLength;
	pVtx[3].pos.z = 0.0f;

	//���_�̓������W
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

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

//------------------------------------------------------------------------------
//�T�C�Y�ݒ� �|���S����]�p�̕ϐ��̌v�Z�����Ă���
//------------------------------------------------------------------------------
void CScene2D::SetSize(D3DXVECTOR3 const &size)
{
	CSceneBase::SetSize(size);

	m_fAngle = atan2f(GetSize().x, GetSize().y);
	m_fLength = (float)sqrt(GetSize().x * GetSize().x + GetSize().y * GetSize().y) / 2;

}