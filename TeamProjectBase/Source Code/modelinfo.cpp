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
Vec<S_ptr<CModelInfo>> CModelInfo::m_apModelList = {};

//�e�N�X�`�����̐ݒ�
Vec<CModelInfo::MODELNAME> CModelInfo::m_aModelFileNameList =
{
	//���e�֌W
	{ "data/MODEL/BombBox/bombbox.x" ,					MODEL_BOMBBOX },									//���e

	//���W���[��
	{ "data/MODEL/test/test_module.x" ,					MODEL_MODULE_DEFAULT },								//���W���[��
	{ "data/MODEL/test/test_module_none.x" ,			MODEL_MODULE_NONE },								//���W���[���@�����Ȃ���@���F��
	{ "data/MODEL/BombTimer/BombTimer.x" ,				MODEL_MODULE_TIMER },								//�^�C�}�[
	{ "data/MODEL/ButtonParts/ButtonParts.x" ,			MODEL_MODULE_NO1 },									//�L�[�p�b�h
	{ "data/MODEL/ButtonModule/Module3.x" ,				MODEL_MODULE_NO2 },									//�L�[�p�b�h

	//���W���[���̃p�[�c
	{ "data/MODEL/Lamp/Lamp.x" ,						MODEL_MODULEPARTS_CLEARLAMP },						//�����v
	{ "data/MODEL/ButtonParts/button.x" ,				MODEL_MODULEPARTS_NO1_KEYPAD },						//�L�[�p�b�h
	{ "data/MODEL/ButtonModule/button2.x" ,				MODEL_MODULEPARTS_NO2_KEYPAD },						//�L�[�p�b�h
	{ "data/MODEL/test/module_No4_Button.x" ,			MODEL_MODULEPARTS_NO4_BUTTON },						//�L�[�p�b�h

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
S_ptr<CModelInfo> CModelInfo::GetModelInfo(CModelInfo::MODEL_TYPE modeltype)
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
