//------------------------------------------------------------------------------
//
//X�t�@�C�����f������  [SceneX.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "sceneX.h"
#include "renderer.h"
#include "manager.h"
#include "keyboard.h"
#include "light.h"
#include "modelinfo.h"

//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------
int CSceneX::m_nNumSceneX = 0;

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define SHADOW_COLOR (D3DXCOLOR(0.0f,0.0f,0.0f,0.5f))
#define STENCIL_COLOR (D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))
#define HARDEDGE_SCALE (D3DXVECTOR3(1.1f,1.1f,1.1f))
//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CSceneX::CSceneX()
{
	//������
	m_SceneXInfo = nullptr;
	m_bSelecting = false;
	m_bEmissive = false;

	//�������Z
	m_nNumSceneX++;
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CSceneX::~CSceneX()
{
	//�|�C���^�̊J��
	m_SceneXInfo = nullptr;

	//�������Z
	m_nNumSceneX--;
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CSceneX::Init()
{

	return S_OK;
}

//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CSceneX::Update()
{
}
//------------------------------------------------------------------------------
//�`�揈��
//�e�̃}�g���b�N�X�����݂����Ƃ��ɂ͐e�̃}�g���b�N�X���|�����킹��
//------------------------------------------------------------------------------
void CSceneX::Draw()
{
	//�n�[�h�G�b�W�`��
	//�I������Ă��郂�f���̂�
	DrawHardEdgeStencil();

	//���[���h�}�g���b�N�X�̌v�Z
	CalcMtx_IncludeParentMtx();

	//���b�V���`��
	DrawMesh();

}

//------------------------------------------------------------------------------
//���_�������Ƀ��b�V���̕`��
//------------------------------------------------------------------------------
void CSceneX::DrawMesh()
{
	//nullcehck
	if (!m_SceneXInfo)
	{
		return;
	}

	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATERIAL		*pMat;
	D3DMATERIAL9		matDef;
	D3DMATERIAL9		DrawMat;

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, GetMtxWorldPtr());

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A�����ɑ΂���|�C���^���擾
	pMat = (D3DXMATERIAL*)m_SceneXInfo->GetMatBuff()->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_SceneXInfo->GetMatNum(); nCntMat++)
	{
		//�`��p�̃}�e���A���擾
		DrawMat = pMat[nCntMat].MatD3D;

		//a�l��0�̂Ƃ���return
		if (DrawMat.Diffuse.a <= 0)
		{
			continue;
		}

		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&DrawMat);

		// �`��
		m_SceneXInfo->GetMesh()->DrawSubset(nCntMat);
	}
	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
}

//------------------------------------------------------------------------------
//�X�e���V���p�̕`�揈��
//------------------------------------------------------------------------------
void CSceneX::DrawStencil()
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, GetMtxWorldPtr());

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	for (int nCntMat = 0; nCntMat < (int)m_SceneXInfo->GetMatNum(); nCntMat++)
	{
		// �`��
		m_SceneXInfo->GetMesh()->DrawSubset(nCntMat);
	}
}

//------------------------------------------------------------------------------
//�e�̃}�g���b�N�X�`��
//------------------------------------------------------------------------------
void CSceneX::DrawShadow()
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATERIAL		*pMat;
	D3DMATERIAL9		matDef;
	D3DMATERIAL9		matBlack;

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//������
	matBlack = matDef;

	//���ݒ�
	matBlack.Diffuse = SHADOW_COLOR;

	// �}�e���A�����ɑ΂���|�C���^���擾
	pMat = (D3DXMATERIAL*)m_SceneXInfo->GetMatBuff()->GetBufferPointer();

	//�X�e���V���L���@0�̂Ƃ���ɂ̂ݕ`��\
	pDevice->SetRenderState(D3DRS_STENCILREF, 0);					//�X�e���V���̏����̒l
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);		//�X�e���V���̏��� ==
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);				//�X�e���V����o�b�t�@�L��

	//�y�e�X�goff
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_OFF_ZWRITING_ON);
	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, GetMtxWorldPtr());


	for (int nCntMat = 0; nCntMat < (int)m_SceneXInfo->GetMatNum(); nCntMat++)
	{
		//�X�e���V���ݒ�
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);

		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&matBlack);

		// �`��
		m_SceneXInfo->GetMesh()->DrawSubset(nCntMat);
	}

	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);	// �X�e���V����o�b�t�@����

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
}
//------------------------------------------------------------------------------
//�n�[�h�G�b�W�`��p�̃X�e���V���`��
//------------------------------------------------------------------------------
void CSceneX::DrawHardEdgeStencil()
{
	//�I������Ă��Ȃ�����return
	if (!m_bSelecting)
	{
		return;
	}
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�X�e���V���L���@0�̂Ƃ���ɂ̂ݕ`��\
	pDevice->SetRenderState(D3DRS_STENCILREF, 0);					//�X�e���V���̏����̒l
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);		//�X�e���V���̏��� ==
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);				//�X�e���V����o�b�t�@�L��

	//ZWriteoff
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_ON_ZWRITING_OFF);

	//�X�e���V���p�̕`��
	CSceneX::DrawStencil();

	//Zwrite���ɖ߂�
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_DEFAULT);


	//�}�g���b�N�X�v�Z
	CHossoLibrary::CalcMatrix(GetMtxWorldPtr(), GetPos(), GetRot(), HARDEDGE_SCALE);

	//nullcheck
	if (GetParentMtxPtr())
	{
		//�e�̃}�g���b�N�X���|�����킹��
		*GetMtxWorldPtr() *= *GetParentMtxPtr();
	}

	////�X�e���V���L���@0�̂Ƃ���ɂ̂ݕ`��\
	//pDevice->SetRenderState(D3DRS_STENCILREF, 0);					//�X�e���V���̏����̒l
	//pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);		//�X�e���V���̏��� ==
	//pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);				//�X�e���V����o�b�t�@�L��

	//���C�e�B���OOFF
	//CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_LIGHTING_OFF);

	//�n�[�h�G�b�W�p�̕`��
	CSceneX::SetEmissive(true);
	CSceneX::DrawMesh_SetMaterial(STENCIL_COLOR, true);
	CSceneX::SetEmissive(false);

	//���C�e�B���O����ɖ߂�
	CHossoLibrary::CheckLighting();

	// �X�e���V����o�b�t�@����
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);


}
//------------------------------------------------------------------------------
//���͂��ꂽ�F�ɉ������}�e���A���ŕ`��
//------------------------------------------------------------------------------
void CSceneX::DrawMesh_SetMaterial(D3DXCOLOR col, bool bAllCol, Vec<int> const&ChangeColMatNum)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DMATERIAL9		MatDef;		//�f�t�H���g�̃}�e���A��
	D3DMATERIAL9		MatInput;	//���͂��ꂽ�F�Ő������ꂽ�}�e���A��
	D3DMATERIAL9		MatModel;	//���f���̑҂Ă�����

	D3DXMATERIAL		*pMat = (D3DXMATERIAL*)m_SceneXInfo->GetMatBuff()->GetBufferPointer();


	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&MatDef);

	//���݂̃}�e���A���ŏ�����
	MatInput = MatDef;

	//�F�̐ݒ�
	MatInput.Diffuse = col;

	//���������n�m�̎�
	if (m_bEmissive)
	{
		MatInput.Emissive = col;
	}

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, GetMtxWorldPtr());

	for (int nCntMat = 0; nCntMat < (int)m_SceneXInfo->GetMatNum(); nCntMat++)
	{
		//�X�e���V���ݒ�
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);

		//�S���F��ς��鎞
		if (bAllCol == true)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&MatInput);
		}
		//�ꕔ�̃}�e���A���̐F��ς��鎞
		else
		{
			//�z��̔ԍ��ƃJ�E���g���������l�̎�
			auto itr = std::find_if(ChangeColMatNum.begin(), ChangeColMatNum.end(),
				[nCntMat](int const &nValue) {return nCntMat == nValue; });

			//�C�e���[�^���擾�ł����ꍇ
			if (itr != ChangeColMatNum.end())
			{
				//�}�e���A���ݒ�
				pDevice->SetMaterial(&MatInput);
			}
			else
			{
				//�`��p�̃}�e���A���擾
				MatModel = pMat[nCntMat].MatD3D;

				//�}�e���A���ݒ�
				pDevice->SetMaterial(&MatModel);
			}
		}

		// �`��
		m_SceneXInfo->GetMesh()->DrawSubset(nCntMat);
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&MatDef);


}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CSceneX::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}

S_ptr<CSceneX> CSceneX::CreateShared(D3DXVECTOR3 const & pos, D3DXVECTOR3 const & rot, D3DXMATRIX * pParentMtx, CScene::OBJTYPE objtype, int nModelType)
{
	//�������m��
	S_ptr<CSceneX> pPtr = std::make_shared<CSceneX>();

	//������
	pPtr->Init();

	//���ݒ肓
	pPtr->SetPos(pos);
	pPtr->SetRot(rot);
	pPtr->SetParentMtxPtr(pParentMtx);
	pPtr->BindModelInfo(CModelInfo::GetModelInfo((CModelInfo::MODEL_TYPE)nModelType));


	//Scene���ŊǗ�
	pPtr->SetObjType(objtype);
	pPtr->AddSharedList(pPtr);

	return pPtr;
}
