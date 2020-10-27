//------------------------------------------------------------------------------
//
//�������̐��l�̏���  [multinumber.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "multinumber.h"
#include "scene2D.h"
#include "scene3D.h"
#include "manager.h"
#include "renderer.h"

//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define DISAPPEAR_COUNT			(60)
#define DISAPPEAR_SCALE_VALUE	(1.0f)
//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CMultiNumber::CMultiNumber()
{
	//������
	m_pNumberList.clear();
	m_nCnt = 0;
	m_nValue = 0;
	m_NumberEffect = NUMBER_EFFECT::NONE;
}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CMultiNumber::~CMultiNumber()
{
	m_pNumberList.clear();
}

//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CMultiNumber::Init()
{
	//������
	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CMultiNumber::Uninit()
{

}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CMultiNumber::Update()
{
	//�J�E���g���Z
	m_nCnt++;

	// �^�C�v�ɂ���ď�����ς���
	switch (m_NumberEffect)
	{
		//�_�Ł@�ԂƉ��F
	case NUMBER_EFFECT::FLASHING_RED_YELLOW:
		//2F���ƂɐF��ς���
		if (m_nCnt % 4 == 0)
		{
			//��
			SetColor(RedColor);
		}
		else if (m_nCnt % 4 == 2)
		{
			//��
			SetColor(YellowColor);
		}
		break;

		//�_��
	case NUMBER_EFFECT::FLASHING:
		//2F���Ƃɓ_��
		if (m_nCnt % 4 == 0)
		{
			SetDisp(true);
		}
		else if (m_nCnt % 4 == 2)
		{
			SetDisp(false);
		}
		break;
	}

	//nullcheck
	if (!m_pNumberList.empty())
	{
		//�T�C�Y��
		for (size_t nCnt = 0; nCnt < m_pNumberList.size(); nCnt++)
		{
			//nullcheck
			if (m_pNumberList[nCnt])
			{
				//�X�V
				m_pNumberList[nCnt]->Update();
			}
		}
	}
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CMultiNumber::Draw()
{
	//�`�悵�Ȃ���
	if (!GetDisp())
	{
		return;
	}

	//���[���h�}�g���b�N�X�v�Z
	CHossoLibrary::CalcMatrix(GetMtxWorldPtr(), GetPos(), GetRot(), OneVector3);

	//nullcheck
	if (GetParentMtxPtr())
	{
		//�e�̃}�g���b�N�X���|�����킹��
		*GetMtxWorldPtr() *= *GetParentMtxPtr();
	}

	//nullcheck
	if (!m_pNumberList.empty())
	{
		//�T�C�Y��
		for (size_t nCnt = 0; nCnt < m_pNumberList.size(); nCnt++)
		{
			//nullcheck
			if (m_pNumberList[nCnt])
			{
				//�`��
				m_pNumberList[nCnt]->Draw();
			}
		}
	}
}

//------------------------------------------------------------------------------
//��������
//------------------------------------------------------------------------------
void CMultiNumber::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //_DEBUG
}

//------------------------------------------------------------------------------
//��������
//------------------------------------------------------------------------------
std::shared_ptr<CMultiNumber> CMultiNumber::Create(D3DXVECTOR3 const & pos, D3DXVECTOR3 const & onesize, int const nValue, int const nDigits, NUMBER_TYPE const type, CScene::OBJTYPE const objtype)
{
	//�������m��
	std::shared_ptr<CMultiNumber> pMultiNumber(new CMultiNumber);

	//nullcheck
	if (pMultiNumber)
	{
		//����������
		pMultiNumber->Init();

		//Number�̐���
		for (int nCnt = 0; nCnt < nDigits; nCnt++)
		{
			if (type == CMultiNumber::NUMBER_TYPE::NUMBER_2D)
			{
				//�z��ɒǉ�
				//���l�̕��Ԓ��S��pos�Ƃ���
				//pMultiNumber->m_pNumberList.emplace_back(CScene2D::Create_SelfManagement(pos + D3DXVECTOR3(-onesize.x * (nDigits - 1) * 0.5f + onesize.x * nCnt, 0.0f, 0.0f), onesize, WhiteColor));
			}
			else if (type == CMultiNumber::NUMBER_TYPE::NUMBER_3D)
			{
				//�z��ɒǉ�
				//���l�̕��Ԓ��S��pos�Ƃ���
				pMultiNumber->m_pNumberList.emplace_back(CScene3D::ScenePolygonCreateSelfManagement<CScene3D>(D3DXVECTOR3(-onesize.x * (nDigits - 1) * 0.5f + onesize.x * nCnt, 0.0f, 0.0f), onesize, WhiteColor, CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_UI_NUMBER)));
				pMultiNumber->m_pNumberList[pMultiNumber->m_pNumberList.size() - 1]->SetParentMtxPtr(pMultiNumber->GetMtxWorldPtr());
				pMultiNumber->m_pNumberList[pMultiNumber->m_pNumberList.size() - 1]->SetLighting(false);

			}
		}

		pMultiNumber->SetPos(pos);
		pMultiNumber->SetSize(onesize);

		//���l�̏�����
		pMultiNumber->SetMultiNumber(nValue);

		//Scene�̃��X�g�ŊǗ�
		pMultiNumber->SetObjType(objtype);
		pMultiNumber->AddSharedList(pMultiNumber);

		//���^�[��
		return pMultiNumber;
	}
	return nullptr;
}
//------------------------------------------------------------------------------
//�X�R�A���Z����
//------------------------------------------------------------------------------
void CMultiNumber::SetMultiNumber(int nValue)
{
	//�����������Ă��錅��
	int nDigits = 0;

	//�l�����Z
	m_nValue = nValue;

	//�J�E���g�X�g�b�v�@��������Ɍv�Z
	if (m_nValue >= (int)powf(10.0f, (float)m_pNumberList.size()))
	{
		m_nValue = (int)powf(10.0f, (float)m_pNumberList.size()) - 1;
	}
	//0�ȉ��ɂ��Ȃ�
	else if (m_nValue < 0)
	{
		m_nValue = 0;
	}

	//�e���̌v�Z
	for (size_t nCnt = 0; nCnt < m_pNumberList.size(); nCnt++)
	{
		//���l���o��
		int nMultiNumber = m_nValue % (int)powf(10.0f, m_pNumberList.size() - (float)nCnt) / (int)powf(10.0f, m_pNumberList.size() - (float)nCnt - 1.0f);
		float fMultiNumber = (float)nMultiNumber / 10.0f;

		//UV���W�ݒ�
		m_pNumberList[nCnt]->SetAnimation(D3DXVECTOR2(fMultiNumber, 0.0f), D3DXVECTOR2(0.1f, 1.0f));

		//���݂̌��Ő؂�̂Ă����ɒl��0�ȏ�ꍇ
		if (fabs(m_nValue / (int)powf(10.0f, m_pNumberList.size() - (float)nCnt - 1.0f)) > 0)
		{
			//�����J�E���g
			nDigits++;
		}
	}
	//����0�̂Ƃ���1�ɐݒ�
	if (nDigits == 0)
	{
		nDigits = 1;
	}

	//�����ɉ����ĕ\����\���̐ݒ�
	for (size_t nCnt = 0; nCnt < m_pNumberList.size(); nCnt++)
	{
		//�ő包�� - ���݂̌������J�E���g��菬�����ꍇ��true
		m_pNumberList[nCnt]->SetDisp(nCnt >= m_pNumberList.size() - nDigits ? true : false);
	}
}

//------------------------------------------------------------------------------
//���W�ݒ�
//------------------------------------------------------------------------------
void CMultiNumber::SetPos(D3DXVECTOR3 const &pos)
{
	//���W���
	CSceneBase::SetPos(pos);

	//�������J��Ԃ�
	for (size_t nCnt = 0; nCnt < m_pNumberList.size(); nCnt++)
	{
		//nullcheck
		if (m_pNumberList[nCnt])
		{
			//���W�ݒ�
			m_pNumberList[nCnt]->SetPos(pos + D3DXVECTOR3(-m_pNumberList[nCnt]->GetSize().x * (m_pNumberList.size() - 1) * 0.5f + m_pNumberList[nCnt]->GetSize().x * nCnt, 0.0f, 0.0f));
		}
	}
}

//------------------------------------------------------------------------------
//�T�C�Y�ݒ�
//------------------------------------------------------------------------------
void CMultiNumber::SetSize(D3DXVECTOR3 const &size)
{
	//���W���
	CSceneBase::SetSize(size);

	//�������J��Ԃ�
	for (size_t nCnt = 0; nCnt < m_pNumberList.size(); nCnt++)
	{
		//nullcheck
		if (m_pNumberList[nCnt])
		{
			//���W�ݒ�
			m_pNumberList[nCnt]->SetSize(size);
		}
	}
	SetPos(GetPos());
}

//------------------------------------------------------------------------------
//�F�ݒ�
//------------------------------------------------------------------------------
void CMultiNumber::SetColor(D3DXCOLOR const &col)
{
	CSceneBase::SetColor(col);

	if (!m_pNumberList.empty())
	{
		//�������J��Ԃ�
		for (size_t nCnt = 0; nCnt < m_pNumberList.size(); nCnt++)
		{
			//nullcheck
			if (m_pNumberList[nCnt])
			{
				//�F�ݒ�
				m_pNumberList[nCnt]->SetColor(col);
			}
		}
	}
}

//------------------------------------------------------------------------------
//�^�C�v�ݒ�
//------------------------------------------------------------------------------
void CMultiNumber::Settype(NUMBER_EFFECT effect)
{
	// �^�C�v�ɂ���ď�����ς���
	switch (m_NumberEffect)
	{
		case NUMBER_EFFECT::NONE:
			SetDisp(false);
			break;

		case NUMBER_EFFECT::FLASHING:

			break;

		case NUMBER_EFFECT::FLASHING_RED_YELLOW:

			break;

	}
}

