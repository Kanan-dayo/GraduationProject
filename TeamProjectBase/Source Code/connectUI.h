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
		CONNECTUI_LOADICON,	// ���[�h�A�C�R��
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
	void CreateUI(void);		// UI����
	void LoadAnim(CPolygon2D *pUI);		// ���[�h�A�C�R���̃A�j���[�V����
	CPolygon2D *m_pConnectUI[CONNECTUI_MAX];
};

#endif
