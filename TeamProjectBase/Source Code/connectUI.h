// ===================================================================
//
// �ڑ���UI���� [ connectUI.h ]
// Author : KANAN NAGANAWA
//
// ===================================================================
#ifndef _CONNECTUI_H_
#define _CONNECTUI_H_

#define _CRT_SECURE_NO_WARNINGS // �x������

// ===================================================================
// �C���N���[�h�t�@�C��
// ===================================================================
#include "main.h"
#include "connectBase.h"

// ===================================================================
// �}�N����`
// ===================================================================

// ===================================================================
// �N���X��`
// ===================================================================
class CPolygon2D;

class CConnectUI
{
public:
	typedef enum
	{
		CONNECTUI_BACK_00,		// 1P�̔w�i
		CONNECTUI_BACK_01,		// 2P�̔w�i
		CONNECTUI_LOADICON_00,	// ���[�h�A�C�R��
		CONNECTUI_LOADICON_01,	// ���[�h�A�C�R��
		CONNECTUI_MAX
	} CONNECTUITYPE;

	CConnectUI();
	~CConnectUI();

	HRESULT Init(void);			// ������
	void Update(void);			// �X�V
	void Draw(void);			// �`��
	void ShowDebugInfo() {};		//�f�o�b�O���\�L

	static CConnectUI * Create(void);	// ����
private:
	void UpdateCntAnim(void);			// �A�j���[�V�����J�E���^�̍X�V
	void CreateBackTab(void);			// �w�i�^�u�̐���
	void CreateLoadIcon(void);			// ���[�h�A�C�R���̐���
	void LoadIconAnim(CPolygon2D *pUI);		// ���[�h�A�C�R���̃A�j���[�V����
	static CPolygon2D *m_pConnectUI[CONNECTUI_MAX];
	static D3DXVECTOR2 m_UIPos[CONNECTUI_MAX];
	static D3DXVECTOR2 m_UISize[CONNECTUI_MAX];

	int m_nCntAnim;
	int m_nCntPattern;
};

#endif
