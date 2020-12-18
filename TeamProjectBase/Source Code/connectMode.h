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
class CConnectBase;
class CChatBase;

class CConnectMode : public CBaseMode
{
public:
	CConnectMode();
	~CConnectMode();
	HRESULT Init(HWND hWnd);								//������
	void Update();											//�X�V
	void Draw();											//�`��
	void ShowDebugInfo();									//�f�o�b�O���\�L

private:
	std::shared_ptr<CConnectBase> m_pConnectBase;
	S_ptr<CChatBase> m_pChatBase;							// �`���b�g�̃|�C���^
};

#endif
