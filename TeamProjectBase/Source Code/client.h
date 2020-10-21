// ===================================================================
//
// �N���C�A���g���� [ client.h ]
// Author : KANAN NAGANAWA
//
// ===================================================================
#ifndef _CLIENT_H_
#define _CLIENT_H_

#define _CRT_SECURE_NO_WARNINGS // �x������

// ===================================================================
// �C���N���[�h�t�@�C��
// ===================================================================
#include "main.h"

// ===================================================================
// �}�N����`
// ===================================================================

// ===================================================================
// �N���X��`
// ===================================================================
class CClient
{
public:
	CClient() {};	// �R���X�g���N�^
	~CClient() {};		// �f�X�g���N�^

	static int main(void);				// ���C������
	static HRESULT InitClient(void);	// ������
	static void UninitClient(void);		// �����I��
	static void ErrorReport(int err);	// �G���[���|�[�g

	static bool &GetAccepting(void) { return m_bAccepting; }
	static void SetAccepting(bool bAccept) { m_bAccepting = bAccept; }

private:
	static bool m_bAccepting;			// �N���C�A���g�󂯓���̃t���O
};

#endif
