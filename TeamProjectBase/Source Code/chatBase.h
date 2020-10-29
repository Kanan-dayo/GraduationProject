// ===================================================================
//
// �`���b�g�̊�Տ��� [ chatBase.h ]
// Author : KANAN NAGANAWA
//
// ===================================================================
#ifndef _CHATBASE_H_
#define _CHATBASE_H_

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
class CChatTab;

class CChatBase : public CScene
{
public:
	CChatBase();
	~CChatBase();

	virtual HRESULT Init(void);			// ������
	virtual void Update(void);			// �X�V
	virtual void Draw(void);			// �`��
	virtual void ShowDebugInfo() {};		//�f�o�b�O���\�L

	static std::shared_ptr<CChatBase> Create(void);	// ����

private:
	CChatTab *m_pTab;	// �^�u�̃|�C���^
};

#endif
