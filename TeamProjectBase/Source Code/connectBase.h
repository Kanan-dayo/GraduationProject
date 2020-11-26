// ===================================================================
//
// �ڑ�UI�̊�Տ��� [ connectBase.h ]
// Author : KANAN NAGANAWA
//
// ===================================================================
#ifndef _CONNECTBASE_H_
#define _CONNECTBASE_H_

#define _CRT_SECURE_NO_WARNINGS // �x������

// ===================================================================
// �C���N���[�h�t�@�C��
// ===================================================================
#include "main.h"
#include "scene.h"

// ===================================================================
// �}�N����`
// ===================================================================

// ===================================================================
// �N���X��`
// ===================================================================
class CConnectUI;

class CConnectBase : public CScene
{
public:
	CConnectBase();
	~CConnectBase();

	virtual HRESULT Init(void);			// ������
	virtual void Update(void);			// �X�V
	virtual void Draw(void);			// �`��
	virtual void ShowDebugInfo() {};		//�f�o�b�O���\�L

	static std::shared_ptr<CConnectBase> Create(void);	// ����

private:
	CConnectUI *m_pUI;	// UI�̃|�C���^
};

#endif
