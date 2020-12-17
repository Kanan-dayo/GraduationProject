//------------------------------------------------------------------------------
//
//UI�̃x�[�X  [UI_Base.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "UI_Base.h"
#include "manager.h"
#include "renderer.h"

//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CUI_Base::CUI_Base()
{
	//������
	m_fChangeValue = 0.0f;
	m_nCnt = 0;
	m_nTotalTime = 0;

}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CUI_Base::~CUI_Base()
{

}

//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CUI_Base::Init()
{
	CScene2D::Init();

	//������
	return S_OK;
}

//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CUI_Base::Update()
{
	m_nCnt++;

	m_fChangeValue;

	if (m_nCnt < m_nTotalTime)
	{
		switch (m_pattern)
		{
		case CUI_Base::RIGHT_TO_CENTER:
			GetPos().x -= m_fChangeValue;

			break;
		case CUI_Base::TRANSPARENT_TO_APPEAR:
			GetColor().a += m_fChangeValue;

			break;
		default:
			break;
		}
	}

	CScene2D::Update();

}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CUI_Base::Draw()
{

	CScene2D::Draw();

}


//------------------------------------------------------------------------------
//����
//------------------------------------------------------------------------------
S_ptr<CUI_Base> CUI_Base::Create(D3DXVECTOR3 const & pos, D3DXVECTOR3 const & size, D3DXCOLOR const & col,LPDIRECT3DTEXTURE9 const tex, CScene::OBJTYPE const objtype, APPEAR_PATTERN pattern, int nTotalTime)
{
	//�������m��
	S_ptr<CUI_Base> ptr = std::make_shared<CUI_Base>();

	//���ݒ�
	ptr->SetPos(pos);
	ptr->SetSize(size);
	ptr->SetColor(col);
	ptr->BindTexture(tex);

	//����������
	ptr->Init();


	ptr->SetAppearPattern(pattern, nTotalTime);

	//Scene�Ƀ|�C���^��n��
	ptr->SetObjType(objtype);
	ptr->AddSharedList(ptr);

	return ptr;
}

//------------------------------------------------------------------------------
//��������
//------------------------------------------------------------------------------
void CUI_Base::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //_DEBUG
}

//------------------------------------------------------------------------------
//�o���p�^�[���ݒ�
//------------------------------------------------------------------------------
void CUI_Base::SetAppearPattern(APPEAR_PATTERN pattern, int nTotalTime)
{
	m_pattern = pattern;
	m_nTotalTime = nTotalTime;
	float fDefaultValue, fAfterValue;


	switch (pattern)
	{
	case CUI_Base::RIGHT_TO_CENTER:

		fDefaultValue = GetPos().x;

		GetPos().x += GetSize().x;

		fAfterValue = GetPos().x;

		m_fChangeValue = fabsf(fAfterValue - fDefaultValue) / m_nTotalTime;



		break;
	case CUI_Base::TRANSPARENT_TO_APPEAR:
		GetColor().a = 0.0f;

		m_fChangeValue = 1.0f / m_nTotalTime;



		break;
	default:
		break;
	}

}
