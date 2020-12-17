//------------------------------------------------------------------------------
//
//�}�b�v����  [map.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "Map.h"
#include "renderer.h"
#include "manager.h"
#include "meshfield.h"
#include "sound.h"
#include "sceneX.h"
#include "modelinfo.h"
//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define MESH_SIZE		(100.0f)
#define MESH_BLOCK_NUM	(INTEGER2(40,40))

#define BG_ORIGIN_POS	(D3DXVECTOR3(0.0f,-600.0f,0.0f))
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CMap::CMap()
{
}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CMap::~CMap()
{
}
//------------------------------------------------------------------------------
//��������
//------------------------------------------------------------------------------
std::unique_ptr<CMap> CMap::Create()
{
	//�������m��
	std::unique_ptr<CMap> pMap(new CMap);

	//�t�B�[���h����
	//CreateField(D3DXVECTOR3(MESH_SIZE, 0.0f, MESH_SIZE), INTEGER2(MESH_BLOCK_NUM.nX, MESH_BLOCK_NUM.nY));

	S_ptr<CSceneX> LocalPtr;
	Vec<int> LocalVec = { 0,CTexture::TEX_MATERIAL_FIELD004 };

	//�}�b�v���f������
	LocalPtr = CSceneX::CreateShared(BG_ORIGIN_POS, ZeroVector3, nullptr, CScene::OBJTYPE::OBJTYPE_BACK, CModelInfo::MODEL_BG);
	LocalPtr->SetTextureNum(LocalVec);

	CSceneX::CreateShared(BG_ORIGIN_POS, ZeroVector3, nullptr, CScene::OBJTYPE::OBJTYPE_BACK, CModelInfo::MODEL_BG_TABLE);

	return pMap;
}
//------------------------------------------------------------------------------
//�t�B�[���h�̍L���擾
//------------------------------------------------------------------------------
D3DXVECTOR3 CMap::GetFieldSize()
{
	return D3DXVECTOR3(MESH_SIZE * MESH_BLOCK_NUM.nX, 0.0f, MESH_SIZE * MESH_BLOCK_NUM.nY);
}
//------------------------------------------------------------------------------
//�t�B�[���h�쐬
//------------------------------------------------------------------------------
void CMap::CreateField(D3DXVECTOR3 size, INTEGER2 BlockNum)
{
	//�t�B�[���h
	CMeshField::Create(ZeroVector3, size, BlockNum);

}
