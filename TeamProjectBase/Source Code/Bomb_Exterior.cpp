//------------------------------------------------------------------------------
//
//���W���[���̃{�^������  [module_Button.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "Bomb_Exterior.h"
#include "modelinfo.h"
#include "Mylibrary.h"
#include "scene3D.h"
#include "sceneX.h"

//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define EXTERIOR_OFFSET_TOP				(D3DXVECTOR3(145.0f,123.0f,0.0f))			//�O���̃I�t�Z�b�g �㉺�̂ق�
#define EXTERIOR_OFFSET_SIDE			(D3DXVECTOR3(420.0f,70.0f,0.0f))			//�O���̃I�t�Z�b�g ���E�̂ق�

#define MAX_EXTERIOR_NUM				(10)										//�O���̑���

#define MAX_BUTTERY_NUM					(MAX_EXTERIOR_NUM)							//�o�b�e���[�̍ő吔

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CBomb_Exterior::CBomb_Exterior()
{
	m_pBatteryList.clear();
	m_ExteriorList.clear();
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CBomb_Exterior::~CBomb_Exterior()
{
	m_pBatteryList.clear();
	m_ExteriorList.clear();
}

//------------------------------------------------------------------------------
//���e�̊O������
//------------------------------------------------------------------------------
U_ptr<CBomb_Exterior> CBomb_Exterior::CreateBombExterior(D3DXMATRIX * pBombMtx)
{
	//�������m��
	U_ptr<CBomb_Exterior> pPtr = std::make_unique<CBomb_Exterior>();

	//nullcheck
	if (pPtr)
	{
		//����
		pPtr->Create(pBombMtx);

		//return
		return std::move(pPtr);
	}

	//return
	return nullptr;
}

//------------------------------------------------------------------------------
//�O���̐��𐔂���
//------------------------------------------------------------------------------
int CBomb_Exterior::CountExteriorNum(EXTERIOR_TYPE type)
{
	return std::count(m_ExteriorList.begin(), m_ExteriorList.end(), type);
}

//------------------------------------------------------------------------------
//�O���ɉ����Z�b�g���邩���߂�
//------------------------------------------------------------------------------
void CBomb_Exterior::SetExterior()
{
	//�o�b�e���[
	for (int nCnt = 0; nCnt < (rand() % MAX_BUTTERY_NUM); nCnt++)
	{
		//�o�b�e���[�ǉ�
		//�傫���o�b�e���[���������o�b�e���[�������_��
		rand() % 2 == 0 ?
			m_ExteriorList.emplace_back(EXTERIOR_TYPE::BATTERY_SMALL) :
			m_ExteriorList.emplace_back(EXTERIOR_TYPE::BATTERY_BIG);
	}

	//�ő吔�ɂȂ�܂�
	while ((int)m_ExteriorList.size() < MAX_EXTERIOR_NUM)
	{
		//�����Ȃ����
		m_ExteriorList.emplace_back(EXTERIOR_TYPE::NONE);
	}
}

//------------------------------------------------------------------------------
//�����֐�
//------------------------------------------------------------------------------
void CBomb_Exterior::Create(D3DXMATRIX * pBombMtx)
{
	//�����Z�b�g���邩���߂�
	SetExterior();

	//���X�g�V���b�t��
	CHossoLibrary::Vec_Shuffle(m_ExteriorList);

	//�v�Z�p�̃��[�J���ϐ�
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;

	//�ő吔�ɂȂ�܂�
	for (int nCnt = 0; nCnt < (int)m_ExteriorList.size(); nCnt++)
	{
		//�O���̍��W�v�Z
		CalcExteriorPosition(nCnt, pos, rot);

		//��ނɉ����ăI�u�W�F�N�g��ς���
		switch (m_ExteriorList[nCnt])
		{
		case EXTERIOR_TYPE::BATTERY_SMALL:

			//���o�b�e���[����
			m_pBatteryList.emplace_back(CSceneX::CreateShared(pos, rot,
				pBombMtx, CScene::OBJTYPE_BOMB_EXTERIOR, CModelInfo::MODEL_BATTERY_SMALL));
			break;

		case EXTERIOR_TYPE::BATTERY_BIG:

			//��o�b�e���[����
			m_pBatteryList.emplace_back(CSceneX::CreateShared(pos, rot,
				pBombMtx, CScene::OBJTYPE_BOMB_EXTERIOR, CModelInfo::MODEL_BATTERY_BIG));
			break;
		}
	}
}

//------------------------------------------------------------------------------
//�O���̍��W���]�ʂ��v�Z
//------------------------------------------------------------------------------
void CBomb_Exterior::CalcExteriorPosition(int const nCnt,D3DXVECTOR3 & pos, D3DXVECTOR3 & rot)
{
	//������
	pos = ZeroVector3;
	rot = ZeroVector3;

	//0-2
	if (nCnt < 3)
	{
		pos.x = CHossoLibrary::CalcEvenPosition(3, nCnt, EXTERIOR_OFFSET_TOP.x);
		pos.y = EXTERIOR_OFFSET_TOP.y;
	}
	//3-7
	else if (nCnt >= 3 && nCnt < 7)
	{
		pos.x = CHossoLibrary::CalcEvenPosition(2, (nCnt - 3) % 2, EXTERIOR_OFFSET_SIDE.x);
		pos.y = CHossoLibrary::CalcEvenPosition(2, (nCnt - 3) / 2, EXTERIOR_OFFSET_SIDE.y);
		rot.z = (nCnt - 3) % 2 ? -D3DX_PI * 0.5f : D3DX_PI * 0.5f;
	}
	//8-10
	else if (nCnt >= 7)
	{
		pos.x = CHossoLibrary::CalcEvenPosition(3, (nCnt - 7), EXTERIOR_OFFSET_TOP.x);
		pos.y = -EXTERIOR_OFFSET_TOP.y;
		rot.z = D3DX_PI;
	}
}
