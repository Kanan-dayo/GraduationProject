//*************************************************************************************************************
//
// ��Ǐ��E�B���h�E[���� [DecodingWindow.h]
// Author:IKUTO SEKINE
//
//*************************************************************************************************************
#ifndef _DECODINGWINDOW_H_
#define _DECODINGWINDOW_H_

//-------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------------------
#include "scene.h"
#include "Mylibrary.h"
#include "DecodingTypes.h"

//-------------------------------------------------------------------------------------------------------------
// �O���錾
//-------------------------------------------------------------------------------------------------------------
class CDecodingUI;
class CHash;
class CMouse;

//-------------------------------------------------------------------------------------------------------------
// �N���X��`
//-------------------------------------------------------------------------------------------------------------
class CDecodingWindow
{
public:
	enum
	{
		TYPE_WINDOW = 0,		// �E�B���h�E
		TYPE_CLOSEBUTTON,		// ����{�^��
		TYPE_SCROLLBAR,			// �X�N���[���o�[
		TYPE_SCROLLHANDLE,		// �X�N���[���n���h��
		TYPE_MAX				// �ő�
	};

	enum
	{
		TEX_NONE = -1,			// �Ȃ�
		TEX_TELLTHEPICTURE,		// �ʐ^�������Ă�������
		TEX_SHAPEMEMORIZATION,	// �`�̈ËL
		TEX_CORDCUTTING,		// �R�[�h��؂�
		TEX_MAZE,				// ���H
		TEX_SIMON,				// �T�C�����Q�[��
		TEX_NOWMAKING,			// ���쒆
		TEX_MAX					// �ő�
	};

	CDecodingWindow();										// �R���X�g���N�^
	~CDecodingWindow();										// �f�X�g���N�^

	static void    MakeHash(void);						// �n�b�V���̍쐬
	static void    ReleaseHash(void);					// �n�b�V���̊J��
	static HRESULT Load(void);								// �ǂݍ���
	static void UnLoad(void);							// �J��

	static CDecodingWindow *Create(void);	// ����

	HRESULT        Init();									//������
	void           Update();								//�X�V
	void           Draw();									//�`��

	void           Appearance(void);						// �o��
	void           Disappearance(void);						// ����

	void           Display(void);							// �\��������
	void           DoNotDisplay(void);						// �\�������Ȃ�

	inline void    SetSign(int nSign) { if (nSign != 0)m_nSign = abs(nSign) / nSign; }
	inline void    SetScal(float fScal) { m_fScal = fScal; }
private:
	/* �����o�֐� */
	void InitSeting(void);								// �ݒ�̏�����
	void MakeUI(void);									// UI�̍쐬
	void SetPosAccordingParent(void);					// �e�ɏ]���Ĉʒu��ݒ肷��


	static void ReadFromLine(CONST_STRING cnpLine, CONST_STRING cnpEntryType, CONST_STRING cnpEntryData);	// 1�s�������ǂݎ��

	/* �����o�ϐ� */
	static LPDIRECT3DTEXTURE9    m_pTexture[TEX_MAX];	// �e�N�X�`�����
	static SETINGINFO            m_InitSeting[TYPE_MAX];// �����ݒ���
	static CHash *               m_pHash;				// �n�b�V���̃|�C���^
	std::shared_ptr<CDecodingUI> m_pUi[TYPE_MAX];		// UI

	SETINGINFO                  m_Seting[TYPE_MAX];		// �ݒ���

	int                          m_nSign;				// ����
	float                        m_fScalValue;			// �g��l�ω��l
	float                        m_fScal;				// �g��l

	// �X�N���[��
	VEC2                         m_VecPinch_center;		// �܂񂾓_���璆�S�ւ̂̃x�N�g��
	CRange<float>                m_ScrollRange;			// �X�N���[���̉��̈�
	float                        m_fScrollRangeValue;	// �X�N���[���̉���l
};

#endif