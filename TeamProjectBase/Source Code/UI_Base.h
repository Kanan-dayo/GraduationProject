//------------------------------------------------------------------------------
//
//UI�̃x�[�X  [UI_Base.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _UI_Base_H_
#define _UI_Base_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "scene2D.h"
//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CUI_Base : public CScene2D
{
public:

	enum APPEAR_PATTERN
	{
		NORMAL,						//�ʏ�
		RIGHT_TO_CENTER,			//�E����Z���^�[�ɏo��
		TRANSPARENT_TO_APPEAR,		//�������珙�X�Ɍ�����悤�ɂȂ�
	};

	CUI_Base();
	~CUI_Base();
	virtual HRESULT Init()						override;				//������
	virtual void Update()						override;				//�X�V
	virtual void Draw()							override;				//�`��
	virtual void ShowDebugInfo()				override;				//�f�o�b�O���\�L

	static S_ptr<CUI_Base> Create(D3DXVECTOR3 const & pos, D3DXVECTOR3 const & size, D3DXCOLOR const & col, LPDIRECT3DTEXTURE9 const tex, CScene::OBJTYPE const objtype, APPEAR_PATTERN pattern, int nTotalTime);

	void SetAppearPattern(APPEAR_PATTERN pattern, int nTotalTime);		//�p�^�[���ݒ�

private:
	APPEAR_PATTERN m_pattern;											//�o���p�^�[��
	int m_nCnt;															//�J�E���^�[
	int m_nTotalTime;													//�ő厞��
	float m_fChangeValue;												//�ω�����p�^�[��
};

#endif