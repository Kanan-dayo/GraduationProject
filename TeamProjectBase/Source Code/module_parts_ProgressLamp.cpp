//------------------------------------------------------------------------------
//
//���W���[���̐i���x�̃����v  [module_parts_Progresslamp.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "module_parts_ProgressLamp.h"
#include "modelinfo.h"
#include "scene3D.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define PROGRESS_LAMP_OFFSET			(D3DXVECTOR3(0.0f,0.0f,-2.0f))		//�i���x�����v�̊Ԋu
#define PROGRESS_LAMP_INTERVAL			(D3DXVECTOR3(10.0f,0.0f,0.0f))		//�i���x�����v�̊Ԋu
#define PROGRESS_LAMP_SIZE				(D3DXVECTOR3(7.0f,10.0f,0.0f))		//�i���x�����v�̑傫��
#define PROGRESS_LAMP_NUM				(4)

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CModule_Parts_ProgressLamp::CModule_Parts_ProgressLamp()
{
	m_nProgress = 0;
	m_pProgressLamp.clear();
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CModule_Parts_ProgressLamp::~CModule_Parts_ProgressLamp()
{
	m_pProgressLamp.clear();
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CModule_Parts_ProgressLamp::Init()
{
	//���f�����ݒ�
	BindModelInfo(CModelInfo::GetModelInfo(CModelInfo::MODEL_MODULEPARTS_PROGRESSLAMP));

	//�����v�̐���
	CreateProgressLamp();

	CSceneX::Init();
	return S_OK;
}

//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CModule_Parts_ProgressLamp::Update()
{
	CSceneX::Update();
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CModule_Parts_ProgressLamp::Draw()
{
	CSceneX::Draw();
}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CModule_Parts_ProgressLamp::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}

//------------------------------------------------------------------------------
//�i���̃����v����
//------------------------------------------------------------------------------
void CModule_Parts_ProgressLamp::CreateProgressLamp()
{
	//�����v����
	for (size_t nCnt = 0; nCnt < PROGRESS_LAMP_NUM; nCnt++)
	{
		//�����v����
		m_pProgressLamp.emplace_back(CSceneBase::ScenePolygonCreateShared<CScene3D>
			(PROGRESS_LAMP_OFFSET - D3DXVECTOR3(CHossoLibrary::CalcEvenPosition(PROGRESS_LAMP_NUM, nCnt, PROGRESS_LAMP_INTERVAL.x), 0.0f, 0.0f),
				PROGRESS_LAMP_SIZE,
				BlackColor,
				nullptr,
				CScene::OBJTYPE_MODULE_PARTS_SYMBOL));

		//�e�̃}�g���b�N�X�ݒ�
		m_pProgressLamp[m_pProgressLamp.size() - 1]->SetParentMtxPtr(GetMtxWorldPtr());
		m_pProgressLamp[m_pProgressLamp.size() - 1]->SetLighting(false);
	}
}

//------------------------------------------------------------------------------
//�i���x�ݒ�
//------------------------------------------------------------------------------
void CModule_Parts_ProgressLamp::SetProgress(int nProgress)
{
	m_nProgress = nProgress;

	for (int nCnt = 0; nCnt < m_nProgress; nCnt++)
	{
		m_pProgressLamp[nCnt]->SetColor(GreenColor);
	}

}
