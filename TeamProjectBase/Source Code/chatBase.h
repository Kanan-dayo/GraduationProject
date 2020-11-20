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
#define SIZE_CHATTEXT			(64)	// �`���b�g�e�L�X�g�̍ő�T�C�Y

// ===================================================================
// �N���X��`
// ===================================================================
class CChatTab;

class CChatBase : public CScene
{
public:
	typedef enum
	{	// �`���b�g���L��
		OWNER_OWN,		// ���g
		OWNER_GUEST,	// �Q�X�g
		OWNER_MAX
	} TEXTOWNER;

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
