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
	{ "data/MODEL/BombBox/bombbox.x" ,										MODEL_BOMBBOX },									//���e
	{ "data/MODEL/Battery/Battery_1.x" ,									MODEL_BATTERY_SMALL },								//���o�b�e���[
	{ "data/MODEL/Battery/Battery_2.x" ,									MODEL_BATTERY_BIG },								//��o�b�e���[
	{ "data/MODEL/ConnectionPort/Rca.x" ,									MODEL_RCA_PORT },									//LAN�|�[�g
	{ "data/MODEL/ConnectionPort/Usb.x" ,									MODEL_USB_PORT },									//USB�|�[�g

	//���W���[��
	{ "data/MODEL/test/test_module.x" ,										MODEL_MODULE_DEFAULT },								//���W���[��
	{ "data/MODEL/test/test_module_none.x" ,								MODEL_MODULE_NONE },								//���W���[���@�����Ȃ���@���F��
	{ "data/MODEL/BombTimer/BombTimer.x" ,									MODEL_MODULE_TIMER },								//�^�C�}�[
	{ "data/MODEL/Module0/ModuleNumber0.x" ,								MODEL_MODULE_NO0 },									//�L�[�p�b�h
	{ "data/MODEL/Module1/ModuleNumber1.x" ,								MODEL_MODULE_NO1 },									//�L�[�p�b�h
	{ "data/MODEL/Module2/ModuleNumber2.x" ,								MODEL_MODULE_NO2 },									//�L�[�p�b�h
	{ "data/MODEL/Module3/ModuleNumber3.x" ,								MODEL_MODULE_NO3 },									//�L�[�p�b�h
	{ "data/MODEL/Module4/ModuleNumber4.x" ,								MODEL_MODULE_NO4 },									//�L�[�p�b�h

	//���W���[���̃p�[�c
	{ "data/MODEL/Lamp/Lamp.x" ,											MODEL_MODULEPARTS_CLEARLAMP },						//�����v
	{ "data/MODEL/ProgressLamp/ProgressLamp.x" ,							MODEL_MODULEPARTS_PROGRESSLAMP },					//�i���x�����v

	{ "data/MODEL/Module0/ModuleNumber0_Button.x" ,							MODEL_MODULEPARTS_NO0_KEYPAD },						//�L�[�p�b�h
	{ "data/MODEL/Module1/ModuleNumber1_Button.x" ,							MODEL_MODULEPARTS_NO1_KEYPAD },						//�L�[�p�b�h
	{ "data/MODEL/Module2/ModuleNumber2_Cord.x" ,							MODEL_MODULEPARTS_NO2_WIRE },						//���C���[
	{ "data/MODEL/Module2/ModuleNumber2_CordCutting.x" ,					MODEL_MODULEPARTS_NO2_WIRE_CUT },					//���C���[�@�؂�Ă���
	{ "data/MODEL/Module3/ModuleNumber3_Button.x" ,							MODEL_MODULEPARTS_NO3_BUTTON },						//�L�[�p�b�h
	{ "data/MODEL/Module3/ModuleNumber3_Button2.x" ,						MODEL_MODULEPARTS_NO3_DECITION_BUTTON },			//�L�[�p�b�h�@���M�{�^��

	{ "data/MODEL/Module4/ModuleNumber4_Lamp.x" ,							MODEL_MODULEPARTS_NO4_BUTTON },						//�L�[�p�b�h

	// �^�u���b�g
	{ "data/MODEL/Tablet/Tablet.x" ,										MODEL_TABLET },										// �^�u���b�g
	{ "data/MODEL/Tablet/TabletButton.x" ,									MODEL_TABLET_BUTTON },								// �^�u���b�g�{�^��

	//�w�i
	{ "data/MODEL/BackGround/Bg.x" ,										MODEL_BG },									// �^�u���b�g�{�^��
	{ "data/MODEL/BackGround/Bg_Desk.x" ,										MODEL_BG_TABLE },									// �^�u���b�g�{�^��

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

		//�������m��
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
	//���f���^�C�v�ƈ�v�����̃C�e���[�^�擾
	auto itr = std::find_if(m_apModelList.begin(), m_apModelList.end(),
		[modeltype](S_ptr<CModelInfo>const &pModel) { return pModel->GetModelType() == modeltype; });

	//�C�e���[�^�擾�ł������`�F�b�N
	if (itr != m_apModelList.end())
	{
		//return
		return *itr;
	}

	return nullptr;
}
