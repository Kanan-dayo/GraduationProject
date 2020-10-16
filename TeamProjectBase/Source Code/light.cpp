//-----------------------------------------------------------------------------
//
// ���C�g���� [light.cpp]
// Author : Yosihiki Hosoya
//
//-----------------------------------------------------------------------------
#include "light.h"
#include "manager.h"
#include "renderer.h"
//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
CLight::CLight()
{
}
//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
CLight::~CLight()
{
}
//-----------------------------------------------------------------------------
// ������
//-----------------------------------------------------------------------------

void CLight::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾

	m_vecDir[0] = D3DXVECTOR3(0.20f, -0.80f, 0.40f);
	m_vecDir[1] = D3DXVECTOR3(-0.20f, 0.80f, -0.40f);
	m_vecDir[2] = D3DXVECTOR3(0.10f, -0.10f, -0.40f);


	m_LightCol[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_LightCol[1] = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
	m_LightCol[2] = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);


	//---------------------------------------------
	// ���C�g0�̐ݒ�
	//---------------------------------------------

	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		// ���C�g���N���A����
		ZeroMemory(&m_aLight[nCnt], sizeof(D3DLIGHT9));

		// ���C�g�̎�ނ�ݒ�
		m_aLight[nCnt].Type = D3DLIGHT_DIRECTIONAL;

		// ���C�g�̊g�U����ݒ�
		m_aLight[nCnt].Diffuse = m_LightCol[nCnt];
		m_aLight[nCnt].Specular = m_LightCol[nCnt];		//�X�y�L�����[(���ˌ�)

		// ���C�g�̕����̐ݒ�
		D3DXVec3Normalize(&m_vecDir[nCnt], &m_vecDir[nCnt]);		//���K��
		m_aLight[nCnt].Direction = m_vecDir[nCnt];

		// ���C�g��ݒ肷��
		pDevice->SetLight(nCnt, &m_aLight[nCnt]);
		// ���C�g��L���ɂ���
		pDevice->LightEnable(nCnt, TRUE);
	}
}
//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void CLight::Uninit()
{
}
//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void CLight::Update()
{

}
//-----------------------------------------------------------------------------
// ���C�g�̏��
//-----------------------------------------------------------------------------
void CLight::ShowLightInfo()
{


	if (ImGui::CollapsingHeader("LightInfo"))
	{
		char aName[MAX_TEXT] = {};
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾

		for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
		{

			sprintf(aName, "Light [%d]", nCnt);

			if (ImGui::TreeNode(aName))
			{
				//���������
				sprintf(aName, "Direction [%d]", nCnt);
				ImGui::SliderFloat3(aName, m_vecDir[nCnt], -1.0f, 1.0f);

				//�F�̃|�C���^
				float *rCol = m_LightCol[nCnt];

				//�F�̐ݒ�
				sprintf(aName, "Color [%d]", nCnt);
				ImGui::ColorEdit4(aName, rCol);

				//���K��
				D3DXVec3Normalize(&m_vecDir[nCnt], &m_vecDir[nCnt]);

				//���C�g�̕ϐ��ɑ��
				m_aLight[nCnt].Direction = m_vecDir[nCnt];

				//���C�g�ݒ�
				pDevice->SetLight(nCnt, &m_aLight[nCnt]);
				ImGui::TreePop();
			}
		}
	}
}
//-----------------------------------------------------------------------------
// ���C�g�̌����擾
//-----------------------------------------------------------------------------
D3DXVECTOR3 CLight::GetLightDir(int nLightNum)
{
	return m_vecDir[nLightNum];
}
//-----------------------------------------------------------------------------
// ���C�g�F�擾
//-----------------------------------------------------------------------------
D3DXCOLOR CLight::GetLightColor(int nLightNum)
{
	return m_LightCol[nLightNum];
}
