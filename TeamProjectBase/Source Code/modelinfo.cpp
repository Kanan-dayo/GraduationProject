//-----------------------------------------------------------------------------
//
//���f�����Ǘ�  [modelinfo.cpp]
// Author : Yoshiki Hosoya
//
//-----------------------------------------------------------------------------
#include "modelinfo.h"
#include "manager.h"
#include "renderer.h"
//-----------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//-----------------------------------------------------------------------------
std::vector<std::shared_ptr<CModelInfo>> CModelInfo::m_apModelList = {};

//�e�N�X�`�����̐ݒ�
std::vector<CModelInfo::MODELNAME> CModelInfo::m_aModelFileNameList =
{
	//�}�b�v���f��
	{ "data/MODEL/Map/Block.x" ,			MODEL_MAPOBJECT_BLOCK },				//������
	{ "data/MODEL/Map/Sphere.x" ,			MODEL_MAPOBJECT_SPHERE },				//����

	//���e�֌W
	{ "data/MODEL/Bomb/Bomb.x" ,			MODEL_BOMBOBJECT_BOMB },				//���e
	{ "data/MODEL/Bomb/Module.x" ,			MODEL_BOMBOBJECT_MODULE },				//���W���[��
	{ "data/MODEL/Bomb/Lamp.x" ,			MODEL_BOMBOBJECT_CLEARLAMP },			//�����v
	{ "data/MODEL/Bomb/Timer.x" ,			MODEL_BOMBOBJECT_TIMER },				//�^�C�}�[

};

//-----------------------------------------------------------------------------
//�R���X�g���N�^
//-----------------------------------------------------------------------------
CModelInfo::CModelInfo()
{
	//������
	m_aName = {};
	m_matBuff = nullptr;
	m_mesh = nullptr;
	m_matNum = 0;
};

//-----------------------------------------------------------------------------
//�f�X�g���N�^
//-----------------------------------------------------------------------------
CModelInfo::~CModelInfo()
{
	//�o�b�t�@�J��
	if (m_matBuff)
	{
		m_matBuff->Release();
		m_matBuff = nullptr;
	}
	//���b�V���J��
	if (m_mesh)
	{
		m_mesh->Release();
		m_mesh = nullptr;
	}
}

//-----------------------------------------------------------------------------
//���f���ǂݍ���
//----------------------------------------------------------------------------
void CModelInfo::ModelLoad(HWND hwnd)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (size_t nCnt = 0; nCnt < m_aModelFileNameList.size(); nCnt++)
	{
		//debug
		std::cout << "Model Load - " << nCnt << m_aModelFileNameList[nCnt].modelname.data() << NEWLINE;

		m_apModelList.emplace_back(std::make_shared<CModelInfo>());
		m_apModelList[nCnt]->m_modeltype = m_aModelFileNameList[nCnt].modeltype;

		// X�t�@�C���̓ǂݍ���
		if (FAILED(D3DXLoadMeshFromX(m_aModelFileNameList[nCnt].modelname.data(),
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_apModelList[nCnt]->m_matBuff,
			NULL,
			&m_apModelList[nCnt]->m_matNum,
			&m_apModelList[nCnt]->m_mesh)))
		{
			//���s�����Ƃ�
			std::cout << "LOAD FAILED!!!! >> " << m_aModelFileNameList[nCnt].modelname.data() << NEWLINE;
		}
	}
}

//-----------------------------------------------------------------------------
//���f���j��
//----------------------------------------------------------------------------
void CModelInfo::ModelUnload()
{
	m_apModelList.clear();
}

//-----------------------------------------------------------------------------
//���f���擾
//----------------------------------------------------------------------------
std::shared_ptr<CModelInfo> CModelInfo::GetModelInfo(CModelInfo::MODEL_TYPE modeltype)
{
	//�T�C�Y���J��Ԃ�
	for (size_t nCnt = 0; nCnt < m_apModelList.size(); nCnt++)
	{
		//nullcheck
		if (m_apModelList[nCnt])
		{
			//���f���^�C�v����v���Ă��邩�ǂ���
			if (m_apModelList[nCnt]->GetModelType() == modeltype)
			{
				return m_apModelList[nCnt];
			}
		}
	}
	return nullptr;
}
