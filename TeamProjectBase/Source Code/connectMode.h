// ===================================================================
//
// �ڑ����[�h���� [ connectMode.h ]
// Author : KANAN NAGANAWA
//
// ===================================================================
#ifndef _CONNECTMODE_H_
#define _CONNECTMODE_H_

#define _CRT_SECURE_NO_WARNINGS // �x������

// ===================================================================
// �C���N���[�h�t�@�C��
// ===================================================================
#include "main.h"
#include "basemode.h"

// ===================================================================
// �}�N����`
// ===================================================================

// ===================================================================
// �N���X��`
// ===================================================================
class CPolygon2D;

class CConnectMode : public CBaseMode
{
public:
	typedef enum
	{
		CONNECTUI_BACK_0,	// �w�i1
		CONNECTUI_BACK_1,	// �w�i2
		CONNECTUI_STATE_0,	// ���1
		CONNECTUI_STATE_1,	// ���2
		CONNECTUI_MAX
	} CONNECTUITYPE;

	CConnectMode();
	~CConnectMode();
	HRESULT Init(HWND hWnd);								//������
	void Update();											//�X�V
	void Draw();											//�`��
	void ShowDebugInfo();									//�f�o�b�O���\�L

private:
	CPolygon2D *m_pConnectUI[CONNECTUI_MAX];
	//static D3DXVECTOR3 m_posUI[CONNECTUI_MAX];
	//static D3DXVECTOR3 m_sizeUI[CONNECTUI_MAX];
};

#endif
